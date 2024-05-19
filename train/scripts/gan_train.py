#!/bin/python3
import os
import time
import argparse
from  tqdm import tqdm
import numpy as np
import torch
from torch.utils.data.sampler import SubsetRandomSampler
from torch.utils.data import DataLoader
from server.interface import EKFInterface
import analysis.utils.datasetWrapper as aud
import analysis.utils.checkpoint as auc
import analysis.utils.torchWrapper as aut
import analysis.utils.model as saum
import prep.utils.fileHandler as puf 
import prep.utils.logHandler as pul
from importlib.machinery import SourceFileLoader
import json
import random
import functools as ft
from pathlib import Path
import sys
import signal
from functools import partial

G_loss_hist = None
val_loss_hist = None
output_dir = None


def signal_handler(sig, frame):
    global G_loss_hist, val_loss_hist, output_dir
    print('You pressed Ctrl+C!')
    if output_dir is not None and G_loss_hist is not None and val_loss_hist is not None:
        loss_hist_path = os.path.join(output_dir, 'loss_hist')
        np.savez_compressed(loss_hist_path, g=np.array(G_loss_hist), val_loss=np.array(val_loss_hist))
    sys.exit(0)
signal.signal(signal.SIGINT, signal_handler)

currentScriptDir = os.path.dirname(os.path.realpath(__file__))
projectRootDir = Path(currentScriptDir).parent.resolve()
projectSpecsDir = os.path.join(projectRootDir, 'specs')

DEBUG = True
DEBUG_LEVEL = 1

torch.autograd.set_detect_anomaly(True)

def debugPrint(*args, **kwargs):
    if DEBUG:
        print(*args, **kwargs)


def npToList(vec, indexToType):
    vecCount = vec.shape[0]
    vecSize = vec.shape[1]
    output = vec.tolist()
    for i in range(vecCount):
        for j in range(vecSize):
            if 'unsigned' in indexToType[j] or 'uint' in indexToType[j]:
                output[i][j] = 0 if output[i][j] < 0 else int(output[i][j])
            elif 'int' in indexToType[j]:
                output[i][j] = int(output[i][j])
            elif 'bool' in indexToType[j]:
                output[i][j] = bool(output[i][j])
    return output

def toJsonFunc(vecList, logStruct, nameToIndex, root):
    output = []
    for l in vecList:
        jsonObj =  pul.vec_to_log(l, logStruct=logStruct, nameToIndex=nameToIndex, root=root)
        output.append(jsonObj)
    return output

def jsonToNumpy(jsonLogs, nameToIndex):
    output = []
    for logStr in jsonLogs:
        y_a = pul.to_vec(logStr, nameToIndex, len(nameToIndex))
        output.append(y_a)
    return np.array(output) # X_a, Y_a

def printSpoofStatus(spoofedSnap, specs, ):
    with torch.no_grad():
        vec = specs.unPreprocess(spoofedSnap.cpu().numpy())

def hingeLossFunc(pred, label, reg=None):
    # Hinge loss
    if reg is not None:
        return 1- pred * label + torch.norm(reg)
    return 1- pred * label

def dbm_loss(res_spec, residual, estimation, g_in):
    anomaly_loss = torch.sum(torch.square(residual[:,:2])+torch.square(residual[:,4:6]), dim=1)
    budget_loss_pos = torch.nn.functional.relu(torch.square(0.15 - torch.abs(residual[:,4])))
    budget_loss_vel = torch.nn.functional.relu(torch.square(0.15 - torch.abs(residual[:,0])))
    north_idx = res_spec.m1_input_name_to_idx['_gps_buffer._buffer[0].pos[0]']
    state_north_idx = res_spec.m1_input_name_to_idx['_state.pos[0]']
    deviation_loss = torch.square(torch.nn.functional.relu(-1*estimation[:,1] + g_in[:, state_north_idx]))
    return torch.mean(anomaly_loss - budget_loss_pos*budget_loss_vel*deviation_loss)

slow_down_count =0
slow_down_limit = 2

class Ensemble:
    def __init__(self, v_netD_cp, p_netD_cp):
        self.vD = v_netD_cp['model']
        self.vD_optim = v_netD_cp['optimizer']
        self.vD.eval()
        self.pD = p_netD_cp['model']
        self.pD_optim = p_netD_cp['optimizer']
        self.pD.eval()
    def __call__(self, input):
        v = self.vD(input)
        p = self.pD(input)
        return torch.cat([v[:,0].view(-1,1), p[:,0].view(-1,1)], dim=1)
    def zero_grad(self):
        self.vD.zero_grad()
        self.pD.zero_grad()

if __name__ == '__main__':
    # load a dummy log
    parser = argparse.ArgumentParser(
                        prog = 'Test if ekf client works',
                        description = 'Send log JSON to extracted EKF',
                        epilog = '')
    parser.add_argument('-i', '--input', type=str, help="Directory with snapshots")
    parser.add_argument('-td', '--testDir', type=str, default=None, help="Directory with snapshots for testing")
    parser.add_argument('-o', '--output', type=str, help="Model save directory")
    parser.add_argument('-l', '--lookup', type=str, default='index/', help="Path to lookup directory")
    parser.add_argument('-e', '--epoch', type=int, default=1, help="epochs for training")
    parser.add_argument('-p', '--port', type=int, default=33344, help="Extracted EKF server port")
    parser.add_argument('-a', '--address', type=str, default='localhost', help="Extracted EKF server address")
    parser.add_argument('-b', '--batchSize', type=int, default=32, help="Mini-batch size")
    parser.add_argument('-sp', '--specDir', type=str, default=projectSpecsDir, help="Path to spec module")
    parser.add_argument('-sn', '--specName', type=str, default=None, help="Path to spec module")
    parser.add_argument('-dm', '--discModel', type=str, default=None, help="Path to res surrogate model")
    parser.add_argument('-em', '--estModel', type=str, default=None, help="Path to update surrogate model")
    parser.add_argument('-emv', '--estModelVel', type=str, default=None, help="Path to update surrogate model")
    parser.add_argument('-emp', '--estModelPos', type=str, default=None, help="Path to update surrogate model")
    #
    parser.add_argument('-m', '--mode', type=str, default=None, help="Availiable modes: 'de' = de-escilation mode")
    parser.add_argument('-c', '--cont', type=str, default='', help="Continue Training from previous checkpoint")
    args = parser.parse_args()
    output_dir = args.output

    indexToName, nameToIndex, indexToType = puf.loadLookUp(args.lookup)
    fieldPaths = pul.nameToPath(indexToName)
    logFormatPath = os.path.join(args.lookup,'logFormat.json')
    logFormat = {}
    logFormatPath = os.path.join(args.lookup,'logFormat.json')
    if os.path.isfile(logFormatPath):
        with open(logFormatPath, 'r') as f:
            logFormat = json.load(f)
    else:
        for p in fieldPaths:
            logFormat = pul.createStruct(p, [], logFormat)
        logFormat = pul.adjustArrayInStruct(logFormat)

    ekfc = EKFInterface(args.address, args.port)

    res_spec =  SourceFileLoader('res_spec', os.path.join(args.specDir, 'res_spec'+'/'+'res_spec' + '.py')).load_module()
    res_spec.m1_init()
    est_spec =  SourceFileLoader('estimator_spec', os.path.join(args.specDir, 'estimator_spec'+'/'+'estimator_spec' + '.py')).load_module()
    est_spec.m1_init()

    pp_gps_pos_0_idx = None
    pp_gps_vel_0_idx = None
    pp_state_pos_0_idx = None
    pp_state_vel_0_idx = None

    state_north_idx = res_spec.m1_input_name_to_idx['_state.pos[0]']
    north_idx = res_spec.m1_input_name_to_idx['_gps_buffer._buffer[0].pos[0]']

    targetNames = ['_gps_buffer._buffer[0].pos[0]', "_gps_buffer._buffer[0].vel[0]"]

    targetIndices = []

    # Target indices: indices to spoof on
    for tn in targetNames:
        targetIndices.append(nameToIndex[tn])
    targetIndices.sort()

    netD = None
    res_s_netD = None
    res_s_optim = None
    up_s_netD = None
    up_s_optim = None

    method_obj = None # for method specs
    method_lf_dir = os.path.join(args.output, 'specs.py')
    if os.path.isfile(method_lf_dir):
        method_obj =  SourceFileLoader('specs', method_lf_dir).load_module()

    if args.mode == 'dbm':
        print('loading models')
        if args.discModel is None:
            exit('Res sur model not defined')
        if (args.estModel is None and not args.velposEst) or (args.velposEst and args.estModelVel is None and args.estModelPos is None):
            exit('up sur model not defined')

        res_surrogate_cp =  auc.loadCheckpoint(args.discModel)
        print('loading models')
        res_s_netD = res_surrogate_cp['model']
        res_s_netD.eval()
        res_s_netD = aut.toDevice(res_s_netD)
        res_s_optim = res_surrogate_cp['optimizer']

        if args.velposEst:
            v_up_surrogate_cp =  auc.loadCheckpoint(args.estModelVel)
            p_up_surrogate_cp =  auc.loadCheckpoint(args.estModelPos)
            up_s_netD = Ensemble(v_up_surrogate_cp, p_up_surrogate_cp)
        else:
            up_surrogate_cp =  auc.loadCheckpoint(args.estModel)
            up_s_netD = up_surrogate_cp['model']
            up_s_netD.eval()
            up_s_netD = aut.toDevice(up_s_netD)
            up_s_optim = up_surrogate_cp['optimizer']
    elif args.mode == 'nc':
        if args.discModel is None:
            exit('Res sur model not defined')
        innov_surrogate_cp =  auc.loadCheckpoint(args.discModel)
        res_s_netD = innov_surrogate_cp['model']
        res_s_netD.eval()
        res_s_netD = aut.toDevice(res_s_netD)
        res_s_optim = innov_surrogate_cp['optimizer']
    else:
        exit('Select a valid mode')

    G_loss_hist = []
    D_loss_hist = []
    val_loss_hist = []

    netG_args = None
    netG = None
    G_optimizer_args = None
    G_optimizer = None
    loss_func = torch.nn.L1Loss(reduction='mean')
    epoch_offset = 0

    if args.cont != '':
        print('Loading latest checkpoint')
        latestCPDir, cpNum = auc.getLatestCPPath(args.cont, prefix='G_')
        latestCPDir = os.path.join(args.cont, latestCPDir)
        epoch_offset = cpNum + 1
        
        cp = auc.loadCheckpoint(latestCPDir)
        netG_args = cp['model_args']
        netG = cp['model']
        G_optimizer_args = cp['optimizer_args']
        G_optimizer = cp['optimizer']
        if 'target_indices' in cp:
            targetIndices = cp['target_indices']
        if 'target_names' in cp:
            targetNames = cp['target_names']
        
        lh_dir = os.path.join(args.cont, 'loss_hist.npz')
        if os.path.isfile(lh_dir):
            lh = np.load(lh_dir)
            val_loss_hist = lh['val_loss'].tolist()
            G_loss_hist = lh['g'].tolist()
            print('loaded loss hist')
    else    :
        print('creating G')
        netG_args = {'dim_input':len(res_spec.m1_input_idx), 'dim_hidden':50, 'dim_output':len(targetIndices), 'hidden_count':5} 
        netG = aut.toDevice(saum.VariableFF(**netG_args))
        G_optimizer_args = {'lr':1e-4}
        G_optimizer = torch.optim.Adam(netG.parameters(), **G_optimizer_args)
    

    random_seed = 33
    sampleLimit = -1
    print('Loading Dataset')
    dataset =  aud.LogDataLoader(args.input, maxLen=sampleLimit)
    validation_split = .2
    shuffle_dataset=True
    dataset_size = len(dataset)
    indices = list(range(dataset_size))
    split = int(np.floor(validation_split * dataset_size))
    if shuffle_dataset :
        np.random.seed(random_seed)
        np.random.shuffle(indices)
    train_indices, val_indices = indices[split:], indices[:split]

    print('Creating Sampler')
    train_sampler = SubsetRandomSampler(train_indices)
    valid_sampler = SubsetRandomSampler(val_indices)
    test_dataset =  aud.LogDataLoader(args.testDir, maxLen=32)

    trainLoader = DataLoader(dataset, batch_size=args.batchSize, num_workers=2, sampler=train_sampler)
    validationLoader = DataLoader(dataset, batch_size=32, num_workers=2, sampler=valid_sampler)
    testLoader = DataLoader(test_dataset, batch_size=128, num_workers=2, shuffle=True)
    print('training starting')

    for epoch in range(epoch_offset, args.epoch + epoch_offset):
        start_time = time.time()
        count = 0
        iters = 0
        G_losses = []
        D_losses = []
        slow_down_count = 0
        # For each batch in the dataloader
        for orig_postf, orig_posth, ext_postf, ext_posth in trainLoader:
            b_size = orig_postf.shape[0]
            count += b_size

            X = aut.toDevice(aut.toDouble(orig_postf))
            Y = aut.toDevice(aut.toDouble(orig_posth))

            ## Train with spoof batch
            netG.zero_grad()
            noise = aut.toDevice(torch.randn(b_size, len(targetIndices)))

            X_tilde = torch.clone(X)
            g_in = None
            if False:
                noise.uniform_(-1-3*(epoch/args.epoch),1+3*(epoch/args.epoch))
                noiseMat = aut.toDevice(torch.zeros(X.shape))
                noiseMat[:,targetIndices] += noise
                noiseMat = res_spec.preprocess(noiseMat)

                g_in = res_spec.preprocess(torch.clone(X))
                g_in = g_in + noiseMat
                aut.toDevice(g_in)
                g_out = netG(g_in)
            else:
                noise.uniform_(-1,1)
                X_tilde[:,targetIndices] += noise

                q_noise = aut.toDevice(torch.randn(b_size, len(est_spec._q_idx)))
                q_noise.uniform_(-0.1,0.1)
                X_tilde[:,est_spec._q_idx] += q_noise
                X_tilde[:,est_spec._q_idx] /= torch.norm(X_tilde[:,est_spec._q_idx])
                
                g_in = res_spec.m1_preprocess_input(torch.clone(X_tilde))
                aut.toDevice(g_in)
                g_out = netG(g_in)

            spoofedSnap = torch.clone(X_tilde)
            spoofedSnap[:,targetIndices] += g_out
            output = None
            q_out = None # Estimated State

            with torch.no_grad():
                vec = torch.clone(spoofedSnap).cpu().numpy()
                listSnaps = npToList(vec, indexToType)
                jsonSnaps = toJsonFunc(listSnaps, logFormat, nameToIndex, '')
                response = ekfc.sendRequest('h', jsonSnaps)['ekf']
                respVec = jsonToNumpy(response, nameToIndex)

                    q_out = aut.toDevice(aut.toDouble(torch.from_numpy(respVec)))
            q_in = aut.toDevice(spoofedSnap)

            velpos_innov = q_out[:,res_spec.m1_output_idx]

            # Train res model
            res_s_input = None
            res_s_label = None
            if args.discModel is not None:
                res_s_input = res_spec.m1_preprocess_input(q_in.detach())
                res_s_label = velpos_innov
                for i in range(100):
                    res_s_netD.zero_grad()
                    res_s_output = res_s_netD(res_s_input.detach())
                    # Train on the example
                    errD = loss_func(res_s_label, res_s_output)
                    errD.backward()
                    res_s_optim.step()
                    if errD.item() < 0.025:
                        res_s_netD.zero_grad()
                        break

            # Train est model
            up_s_input, up_s_label = None, None
            if not args.velposEst and args.estModel is not None:
                # Manually map the outputs for now
                up_s_input, up_s_label = est_spec.m1_preprocess(q_in.detach(), q_out.detach())
                for i in range(100):
                    up_s_netD.zero_grad()
                    up_s_output = up_s_netD(up_s_input)
                    up_s_err = loss_func(up_s_label, up_s_output)
                    up_s_err.backward()
                    up_s_optim.step()
                    if up_s_err.item() < 0.025:
                        up_s_netD.zero_grad()
                        break
            elif args.velposEst:
                v_up_s_input, v_up_s_label = est_spec.m2_preprocess(q_in.detach(), q_out.detach()) # Vel
                p_up_s_input, p_up_s_label = est_spec.m2b_preprocess(q_in.detach(), q_out.detach()) # Pos
                for i in range(100):
                    up_s_netD.vD.zero_grad()
                    up_s_netD.pD.zero_grad()

                    v_out = up_s_netD.vD(v_up_s_input)
                    p_out = up_s_netD.pD(p_up_s_input)

                    v_up_s_err = loss_func(v_up_s_label, v_out)
                    v_up_s_err.backward()
                    up_s_netD.vD_optim.step()


                    p_up_s_err = loss_func(p_up_s_label, p_out)
                    p_up_s_err.backward()
                    up_s_netD.pD_optim.step()
                    if v_up_s_err.item() < 0.05 and p_up_s_err.item() < 0.05:
                        up_s_netD.zero_grad()
                        break
            res_s_netD.zero_grad()
            residual  = res_s_netD(res_spec.m1_preprocess_input(q_in))
            if up_s_netD is not None:
                up_s_netD.zero_grad()
                estimation  = up_s_netD(torch.cat([res_spec.m1_preprocess_input(q_in), residual], dim=1))

            total_loss = None
            if args.mode == 'nc':
                anomaly_loss = torch.sum(torch.square(residual[:,:2])+torch.square(residual[:,4:6]), dim=1)
                total_loss = torch.mean(anomaly_loss)
            elif args.mode == 'dbm':
                total_loss = dbm_loss(res_spec, residual, estimation, g_in)
            else:
                exit("Invalid mode")

            errG = torch.mean(total_loss)
            errG.backward()
            G_optimizer.step()

            # Output training stats
            if iters % 50 == 0:
                debugPrint('[%d/%d][%d/%d][%f]\t\tLoss_G: %.4f\t'
                    % (epoch, args.epoch, iters+1, len(trainLoader), float(iters+1)/len(trainLoader),
                        errG.item()))
                with torch.no_grad():
                    print('noise', noise[0].cpu().tolist())
                    print('innov', res_spec._only_north_velpos_output(residual[:1]).cpu().tolist())

                    print('true innov', q_out[0, est_spec._north_velpos_idx].cpu().tolist())
                    print('State delta', (estimation[0,1] - g_in[0, state_north_idx]).cpu().tolist())
                    print('True State delta', (q_out[0, 1179] - g_in[0, state_north_idx]).cpu().tolist())
                    print('deviation', (estimation[0,1] - g_in[0, north_idx]).cpu().tolist())
                    print('true deviation', (q_out[0, 1179] - g_in[0, north_idx]).cpu().tolist())
                    print('g_out', g_out[0].cpu().tolist())
            G_losses.append(errG.item())
            vidx = random.sample(range(b_size), 2)

            del X
            del Y
            del g_in
            del spoofedSnap
            torch.cuda.empty_cache()
            iters += 1
                

        with torch.no_grad():
            total_val_loss = []
            v_batch_count = 0
            for test_orig_postf, test_orig_posth, _, _ in testLoader:
                v_batch_count += len(test_orig_postf)
                val_X = aut.toDevice(aut.toDouble(test_orig_postf))
                noise = aut.toDevice(torch.randn(len(test_orig_postf), len(targetIndices))) # for the attack indices

                val_d_in = val_X
                val_d_in = aut.toDevice(val_d_in)

                val_g_in = res_spec.m1_preprocess_input(torch.clone(val_X))
            
                val_g_out = netG(val_g_in)
                val_X[:, targetIndices] += val_g_out
                
                val_residual = res_s_netD(res_spec.m1_preprocess_input(val_X))
                val_estimation = torch.cat([res_spec.m1_preprocess_input(val_X), val_residual], dim=1)

                label = []
                val_loss = None
                if args.mode == 'dbm':
                    val_loss = dbm_loss(res_spec, val_residual, val_estimation, val_g_in)

                total_val_loss.append(val_loss.item())
                print('val g_out', val_g_out[0])
            print('val total val loss', np.mean(total_val_loss))
            val_loss_hist.append(np.mean(total_val_loss))
            torch.cuda.empty_cache()
            del val_X
            del val_g_in

        G_loss_hist.append(G_losses)

        outputPath = os.path.join(args.output, 'G_checkpoint_{}.pt'.format(epoch))
        with torch.no_grad():
            if args.mode == 'de':
                auc.saveCheckpoint(outputPath, netG, netG_args,
                                    G_optimizer, G_optimizer_args, G_loss_hist, epoch, targetNames=targetNames, targetIndices=targetIndices,
                                    meta={'mode':'de'})
            else:
                auc.saveCheckpoint(outputPath,
                                   netG,
                                   netG_args,
                                   G_optimizer,
                                   G_optimizer_args,
                                   G_loss_hist,
                                   epoch,
                                   val_loss=val_loss_hist,
                                   targetNames=targetNames,
                                   targetIndices=targetIndices)
        end_time = time.time()
        print("Epoch duration in seconds: ", end_time - start_time)

    # Save the lossses and the model
    loss_hist_path = os.path.join(args.output, 'loss_hist')
    np.savez_compressed(loss_hist_path, g=np.array(G_loss_hist), val_loss=np.array(val_loss_hist))
