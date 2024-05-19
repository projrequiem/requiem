#!/bin/python3
# Evaluate the model performance
import os
import time
import argparse
import analysis.score as ana_sco
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
import re

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
        # log = json.loads(logStr)
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

def listCPPaths(modelDir, prefix=''):
    rootDirList = os.listdir(modelDir)
    origPattern = re.compile(r'%ssurrogate_checkpoint\_[0-9]+.pt'%prefix)
    output = []
    for modelPath in list(filter(origPattern.match, rootDirList)):
        output.append(modelPath)
    return output

def cp_extract_num(name):
    return int(name.split("_")[-1].split(".")[0])

loss_hist = []
val_loss_hist = []
noise_factor = 1

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
    parser.add_argument('-q', '--query', action='store_true', help="Enable utilizing the ekf server. Needed for calculating state deviation")
    parser.add_argument('-p', '--port', type=int, default=33344, help="Extracted EKF server port")
    parser.add_argument('-a', '--address', type=str, default='localhost', help="Extracted EKF server address")
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

    est_specs =  SourceFileLoader(args.specName, os.path.join(args.specDir, args.specName+'/'+args.specName + '.py')).load_module()
    est_specs.m2_init() # initialize method 1 preprocessing
    est_specs.m2b_init() # initialize method 1 preprocessing

    if args.query:
        ekfc = EKFInterface(args.address, args.port)

    loss_func = torch.nn.MSELoss(reduction='sum')

    test_dataset =  aud.LogDataLoader(args.testDir, maxLen=32)

    testLoader = DataLoader(test_dataset, batch_size=128, num_workers=2, shuffle=True)
    model_name_list = listCPPaths(args.input)
    result = {}

    with torch.no_grad():
        for mname in model_name_list:
            num = cp_extract_num(mname)
            mpath = os.path.join(args.input, mname)
            cp = auc.loadCheckpoint(mpath)
            est_surrogate = cp['model']

            # Start testing
            total_loss = 0
            count = 0

            # For each batch in the dataloader
            for orig_postf, orig_posth, ext_postf, ext_posth in testLoader:
                b_size = orig_postf.shape[0]
                count += b_size

                est_surrogate.zero_grad()

                postf = aut.toDevice(aut.toDouble(orig_postf))

                # Query first
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
                X, Y = est_specs.m2b_preprocess(postf, query_out)

                predicted = est_surrogate(X.detach())

                dev_loss = loss_func(predicted, Y.detach())

                # Save Losses for plotting later
                total_loss += dev_loss.item()

                del postf
                del X
                del Y
                torch.cuda.empty_cache()

            result[num] = total_loss / count

    ekfc.close()
    output = []
    for i in range(len(result)):
        output.append(result[i])
    np.save('test_loss.npy', np.array(output))