#!/bin/python3
import argparse
import os
import sys
import time
import json
import math
import numpy as np
import prep.utils.fileHandler as puf
import prep.utils.logHandler as pul
import auto.utils.data  as aud
import analysis.utils.datasetWrapper  as AnaUD
from server.interface import EKFInterface
from tqdm import tqdm
import random
import multiprocessing as mp


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Collect data')
    parser.add_argument('-d', '--logdir', type=str, default='./data/log',
                    help='Directory of the log')
    parser.add_argument('-o', '--output', type=str, default=None,
                    help='Output of the analysis result')
    parser.add_argument('-l', '--lookup', type=str, default='index/', help="Path to lookup table dir to serialize the log")
    parser.add_argument('-a', '--address', type=str, default='localhost', help="Address of the EKF Server")
    parser.add_argument('-po', '--port', type=int, default=33344, help="Port of the EKF Server")
    args = parser.parse_args()

    # Load the parsed data original
    logDir = os.path.abspath(args.logdir)

    indexToName, nameToIndex, indexToType = puf.loadLookUp(args.lookup)

    fieldPaths = pul.nameToPath(indexToName)
    logFormat = {}
    logFormatPath = os.path.join(args.lookup,'logFormat.json')
    if os.path.isfile(logFormatPath):
        with open(logFormatPath, 'r') as f:
            logFormat = json.load(f)
    else:
        for p in fieldPaths:
            logFormat = pul.createStruct(p, [], logFormat)
        logFormat = pul.adjustArrayInStruct(logFormat)

    logNames = aud.get_parsed_logs(logDir)
    ekfc = EKFInterface(args.address, args.port)
    target_indices = []
    for i in range(len(indexToName)):
        if i < 112:
            continue
        n = indexToName[i]
        if 'buffer._head' in n or 'buffer._tail' in n or 'buffer._size' in n or 'buffer._first_write' in n:
            continue
        target_indices.append(i)

    influcence_dicts = []
    for lgn in logNames:
        orig = np.load(lgn)['h'][1000:-1000]
        gps_rdy_index = 1211
        baro_rdy_index= 1212
        gps_rdy_set = set(np.nonzero(orig[:,1, gps_rdy_index])[0].tolist())
        baro_rdy_set = set(np.nonzero(orig[:,1, baro_rdy_index])[0].tolist())

        both_rdy_set = gps_rdy_set.intersection(baro_rdy_set)
        gps_rdy_exclusive_set = gps_rdy_set.difference(both_rdy_set)
        baro_rdy_exclusive_set = baro_rdy_set.difference(both_rdy_set)

        gps_sam_idx = AnaUD.pop_random_element(gps_rdy_exclusive_set)
        baro_sam_idx = AnaUD.pop_random_element(baro_rdy_exclusive_set)

        gps_rdy_list = list(gps_rdy_set)
        gps_rdy_list.sort()

        test_samples={'gps':orig[gps_rdy_list]}

        saveData = {}
        influenced = {}
        influencedBy = {}
        # Inject noise for all
        for sampleType, ss in test_samples.items():
            if sampleType == 'baro':
                continue
            sampleIndex = 0
            for sample in ss:
                x = sample[0]
                y = sample[1]

                indexInLog = gps_rdy_list[sampleIndex] 
                sampleIndex += 1
                X_a = []
                for i in target_indices:
                    idx_val_min = np.min(orig[:,0,i])
                    idx_val_max = np.max(orig[:,0,i])

                    noise = np.zeros(2020)
                    noise[i] = 1
                    x_a = x.copy()
                    if 'unsigned' in indexToType[i] or 'uint' in indexToType[i]:
                        if int(noise[i]) == 0:
                            noise[i] = 1
                        x_a += noise
                    elif 'int' in indexToType[i]:
                        if int(noise[i]) == 0:
                            noise[i] = 1
                        x_a += noise
                    elif 'bool' in indexToType[i]:
                        x_a[i] = 1 - int(x_a[i])
                    else:
                        x_a += noise
                    
                    X_a.append(x_a)

                X_a_json = []
                for x_a in X_a:
                    x_a_list = x_a.tolist()
                    for idx in range(len(x_a_list)):
                        if 'unsigned' in indexToType[idx] or 'uint' in indexToType[idx]:
                            x_a_list[idx] = 0 if x_a_list[idx] < 0 else int(x_a_list[idx])
                        elif 'int' in indexToType[idx]:
                            x_a_list[idx] = int(x_a_list[idx])
                        elif 'bool' in indexToType[idx]:
                            x_a_list[idx] = bool(x_a_list[idx])
                    jsonObj =  pul.vec_to_log(x_a_list, logStruct=logFormat, nameToIndex=nameToIndex, root='')
                    X_a_json.append(jsonObj)


                Y_a_json = []
                # Query
                for i in range(0,len(X_a_json)):
                    resp = ekfc.sendRequest('h', [X_a_json[i]])['ekf']
                    Y_a_json += resp

                Y_a = {}
                # Convert to Numpy
                for i in range(len(Y_a_json)):
                    idx = target_indices[i]
                    y_a_j = Y_a_json[i]
                    y_a = pul.to_vec(y_a_j, nameToIndex, len(nameToIndex))
                    Y_a[idx] = y_a

                # Log which indices changed
                i = 0
                for idx in target_indices:
                    y_a = Y_a[idx]

                    if idx not in influenced:
                        influenced[idx]=np.nonzero(y - y_a)[0].tolist()
                    else:
                        influenced[idx] += np.nonzero(y - y_a)[0].tolist()
                    influenced[idx] = list(set(influenced[idx]))
                    influenced[idx].sort()
                    if len(influenced[idx]) > 0:
                        valDiff = np.linalg.norm(y_a -  y)
                        maxDiffIdx = np.argmax(y_a -  y)
                        if valDiff < 0.01:
                            print('No significant changes')
                    for idxb in influenced[idx]:
                        if idxb not in influencedBy:
                            influencedBy[idxb] = set()
                        influencedBy[idxb].add(idx)
                    i += 1
        for k in influencedBy.keys():
            influencedBy[k] = list(influencedBy[k])
            influencedBy[k].sort()
        saveData[sampleType]={}
        saveData[sampleType]['influence']= influenced
        saveData[sampleType]['influencedBy']= influencedBy
        outputPath = os.path.join(args.output, 'influence.json')
        with open(outputPath, 'w') as f:
            json.dump(saveData, f, indent=4)
    ekfc.close()
