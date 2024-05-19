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
    return np.array(output)

def printSpoofStatus(spoofedSnap, specs, ):
    with torch.no_grad():
        vec = specs.unPreprocess(spoofedSnap.cpu().numpy())

def hingeLossFunc(pred, label, reg=None):
    if reg is not None:
        return 1- pred * label + torch.norm(reg)
    return 1- pred * label

slow_down_count =0
slow_down_limit = 5

if __name__ == '__main__':
    parser = argparse.ArgumentParser(
                        prog = 'Test if ekf client works',
                        description = 'Send log JSON to extracted EKF',
                        epilog = '')
    parser.add_argument('-i', '--input', type=str, help="Directory with snapshots")
    parser.add_argument('-td', '--testDir', type=str, default=None, help="Directory with snapshots for testing")
    parser.add_argument('-o', '--output', type=str, help="Model save directory")
    parser.add_argument('-l', '--lookup', type=str, default='index/', help="Path to lookup directory")
    parser.add_argument('-e', '--epoch', type=int, default=1, help="epochs for training")
    parser.add_argument('-q', '--query', action='store_true', help="Enable utilizing the ekf server. Needed for calculating state deviation")
    parser.add_argument('-p', '--port', type=int, default=33344, help="Extracted EKF server port")
    parser.add_argument('-a', '--address', type=str, default='localhost', help="Extracted EKF server address")
    parser.add_argument('-b', '--batchSize', type=int, default=32, help="Mini-batch size")
    parser.add_argument('-sp', '--specDir', type=str, default=projectSpecsDir, help="Path to spec module")
    parser.add_argument('-sn', '--specName', type=str, default=None, help="Path to spec module")
    args = parser.parse_args()

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

    if args.query:
        ekfc = EKFInterface(args.address, args.port)
    res_spec =  SourceFileLoader(args.specName, os.path.join(args.specDir, args.specName+'/'+args.specName + '.py')).load_module()
    res_spec.m1_init()

    targetNames = ['_gps_buffer._buffer[0].pos[0]', "_gps_buffer._buffer[0].vel[0]", '_gps_buffer._buffer[0].pos[1]', "_gps_buffer._buffer[0].vel[1]"]

    targetIndices = []

    for tn in targetNames:
        targetIndices.append(nameToIndex[tn])
    targetIndices.sort()

    res_surrogate_args = {'dim_input': len(res_spec.m1_input_idx), 'dim_hidden':50, 'dim_output':len(res_spec.m1_output_idx), 'hidden_count':2}
    res_surrogate = aut.toDevice(saum.VariableFF(**res_surrogate_args))

    surrogate_optimizer_args = {'lr':1e-4}
    surrogate_optimizer = torch.optim.Adam(res_surrogate.parameters(), **surrogate_optimizer_args)
    loss_func = torch.nn.L1Loss(reduction='mean')
    
    loss_hist = []

    val_loss_hist = []

    random_seed = 333
    sampleLimit = -1
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

    train_sampler = SubsetRandomSampler(train_indices)
    valid_sampler = SubsetRandomSampler(val_indices)
    test_dataset =  aud.LogDataLoader(args.testDir, maxLen=32)

    trainLoader = DataLoader(dataset, batch_size=args.batchSize, num_workers=2, sampler=train_sampler)
    validationLoader = DataLoader(dataset, batch_size=32, num_workers=2, sampler=valid_sampler)
    testLoader = DataLoader(test_dataset, batch_size=128, num_workers=2, shuffle=True)

    for epoch in range(args.epoch):
        start_time = time.time()
        count = 0
        iters = 0
        losses = []
        slow_down_count = 0

        for orig_postf, orig_posth, ext_postf, ext_posth in trainLoader:
            b_size = orig_postf.shape[0]
            count += b_size

            res_surrogate.zero_grad()
            noise = aut.toDevice(torch.randn(b_size, len(res_spec._velpos_idx))) 
            noise.uniform_(-1,1)

            postf = aut.toDevice(aut.toDouble(orig_postf))
            postf[:,res_spec._velpos_idx] += noise

            query_in = torch.clone(postf)
            query_out = None
            if args.query:
                query_resp = None
                with torch.no_grad():
                    vec = query_in.cpu().numpy()
                    listSnaps = npToList(vec, indexToType)
                    jsonSnaps = toJsonFunc(listSnaps, logFormat, nameToIndex, '')
                    response = ekfc.sendRequest('h', jsonSnaps)['ekf']
                    respVec = jsonToNumpy(response, nameToIndex)

                    query_resp = aut.toDevice(aut.toDouble(torch.from_numpy(respVec)))
                    query_out = torch.squeeze(query_resp)
            X, Y = res_spec.m1_preprocess(postf, query_out)

            X = aut.toDevice(X)
            Y = aut.toDevice(Y)
            predicted_res = res_surrogate(X.detach())

            ano_loss = loss_func(predicted_res, Y.detach())

            err_surrogate = torch.sum(ano_loss)

            err_surrogate.backward()

            surrogate_optimizer.step()

            if iters % 50 == 0:
                debugPrint('[%d/%d][%d/%d][%f]\t\tLoss_G: %.4f\t'
                    % (epoch, args.epoch, iters+1, len(trainLoader), float(iters+1)/len(trainLoader),
                        err_surrogate.item()))

            losses.append(err_surrogate.item())
            vidx = random.sample(range(b_size), 2)

            del X
            del Y
            torch.cuda.empty_cache()
            iters += 1
                

        with torch.no_grad():
            val_loss = []
            for test_orig_postf, test_orig_posth, _, _ in testLoader:
                val_X, val_Y = res_spec.m1_preprocess(test_orig_postf, test_orig_posth)
                val_X = aut.toDevice(aut.toDouble(val_X))
                val_Y = aut.toDevice(aut.toDouble(val_Y))
                val_predicted_innov = res_surrogate(val_X)
                val_X = aut.toDevice(aut.toDouble(val_X))

                val_loss.append(loss_func(val_Y, val_predicted_innov).item())
                print('val_predicted', val_predicted_innov[0], 'innov')
                print('val_Y', val_Y[0], 'innov')
            print('val total val loss', np.mean(val_loss))
            val_loss_hist.append(np.mean(val_loss))
            torch.cuda.empty_cache()
            del val_X
            del val_Y
            del val_predicted_innov

        loss_hist.append(losses)

        outputPath = os.path.join(args.output, 'surrogate_checkpoint_{}.pt'.format(epoch))
        with torch.no_grad():
            auc.saveCheckpoint(outputPath, res_surrogate, res_surrogate_args,
                                surrogate_optimizer, surrogate_optimizer_args, loss_hist, epoch, targetNames=targetNames, targetIndices=targetIndices)
        end_time = time.time()
        print("Epoch duration in seconds: ", end_time - start_time)

    loss_hist_path = os.path.join(args.output, 'loss_hist')
    np.savez_compressed(loss_hist_path, g=np.array(loss_hist), val_loss=np.array(val_loss_hist))
