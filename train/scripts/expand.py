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
from server.interface import EKFInterface
from tqdm import tqdm
import random
import multiprocessing as mp


ONE_GB = 1024 **3
NOISE_MEM_POOL = 2 * ONE_GB
JSON_PRE_Q_MEM_POOL = 3 * ONE_GB
JSON_POST_Q_MEM_POOL = 3 * ONE_GB
LOG_JSON_BYTES = 201429
VEC_BYTES = 16160
# MAX_LOG_IN_POOL = int(JSON_MEM_POOL/LOG_JSON_BYTES)
# MAX_VEC_IN_POOL = int(VEC_MEM_POOL/VEC_BYTES)

SAVE_POOL = {} # simulation name -> numpy vectors
SAVE_POOL_MAX = 6

TARGET_NAMES = []
VICTIM_INDICES = []

def addToBuffer(data, buffer, lock, limit, waitTime):
    added = False
    while True:
        with lock:
            if limit < 0 or len(buffer) < limit:
                buffer.append(data)
                added = True
        if added:
            break
        time.sleep(waitTime)


def taskLoad(outQ, poolQ, cQ, logPaths, outputDir, iois, iter, chunkSize=32):
    for logName in logPaths:
        data = np.load(logName)['h'][:,0,:]
        name = os.path.basename(logName).split('.')[0]
        
        maxVals = data.max(0) 
        minVals = data.min(0) 
        rangeVals = maxVals - minVals
        maxVals = maxVals + 0.1*rangeVals
        minVals = minVals - 0.1*rangeVals

        outputSubDir = os.path.join(outputDir, name)

        # for single index
        for i in range(len(iois)):
            index = iois[i]
            for c in range(iter):
                newName = name + "(" + str(index) + ')'+'-%d'%c
                # Check if file exists
                fileName = os.path.join(outputSubDir, newName+'.npz')
                if os.path.isfile(fileName):
                    print('File already exists: ', fileName)
                    continue
                poolPacket = {}
                poolPacket['package'] = {'count': data.shape[0], 'data': [np.zeros(data.shape),np.zeros(data.shape)], 'original':name}
                poolPacket['name'] = newName
                poolPacket['type'] = 'new'
                poolQ.put(poolPacket)
                for j in range(0, data.shape[0], chunkSize):
                    outQ.put([newName, j, data[j:j+chunkSize], [[index], minVals, maxVals] ])
                while True:
                    print('Waiting for poolControlQ')
                    poolFull = cQ.get()
                    print('Recieved for poolControlQ')
                    if not poolFull:
                        break
                    print('POOL IS FULL')
                    time.sleep(0.5)

        # for two indices
        for i in range(len(iois)-1):
            for j in range(i+1, len(iois)):
                for c in range(iter):
                    index_1 = iois[i]
                    index_2 = iois[j]
                    newName = name + "(" + str(index_1) + '_' + str(index_2) + ')'+'-%d'%c 
                    fileName = os.path.join(outputSubDir, newName+'.npz')
                    if os.path.isfile(fileName):
                        print('File already exists: ', fileName)
                        continue
                    poolPacket = {}
                    poolPacket['package'] = {'count': data.shape[0], 'data': [np.zeros(data.shape),np.zeros(data.shape)], 'original':name}
                    poolPacket['name'] = newName
                    poolPacket['type'] = 'new'
                    poolQ.put(poolPacket)
                    for k in range(0, data.shape[0], chunkSize):
                        outQ.put([newName, 0, data[k:k+chunkSize], [[index_1, index_2], minVals, maxVals] ])
                    while True:
                        print('Waiting for poolControlQ')
                        poolFull = cQ.get()
                        print('Recieved for poolControlQ')
                        if not poolFull:
                            break
                        print('POOL IS FULL')
                        time.sleep(0.5)
        for c in range(iter):
            newName = name + '(' + '_'.join([str(index) for index in iois]) + ')'+'-%d'%c
            fileName = os.path.join(outputSubDir, newName+'.npz')
            if os.path.isfile(fileName):
                print('File already exists: ', fileName)
                continue
            poolPacket = {}
            poolPacket['package'] = {'count': data.shape[0], 'data': [np.zeros(data.shape),np.zeros(data.shape)], 'original':name}
            poolPacket['name'] = newName
            poolPacket['type'] = 'new'
            poolQ.put(poolPacket)
            for j in range(0, data.shape[0], chunkSize):
                outQ.put([newName, 0, data[j:j+chunkSize], [iois, minVals, maxVals] ])
            while True:
                print('Waiting for poolControlQ')
                poolFull = cQ.get()
                print('Recieved for poolControlQ')
                if not poolFull:
                    break
                print('POOL IS FULL')
                time.sleep(0.5)
    outQ.put(None)
    return

def addNoiseFunc(dataPackage, startIndex, endIndex):
    vecs = dataPackage[0][startIndex:endIndex]
    indices = dataPackage[1]
    minVals = dataPackage[2]
    maxVals = dataPackage[3]
    return expander(vecs, indices, minVals, maxVals), []

def toListFunc(dataPackage, startIndex, endIndex, indexToType):
    vec = dataPackage[0][startIndex:endIndex]
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
    return output , [vec] # preserve vec

def toJsonFunc(dataPackage, startIndex, endIndex, logStruct, nameToIndex, root):
    vecList = dataPackage[0][startIndex:endIndex]
    numpyVec = dataPackage[1][startIndex:endIndex]
    output = []
    for l in vecList:
        jsonObj =  pul.vec_to_log(l, logStruct=logStruct, nameToIndex=nameToIndex, root=root)
        output.append(jsonObj)
    return output, [numpyVec]

def _toJsonFuncHelper():
    pass

def query(dataPackage, startIndex, endIndex, queryInQs, queryOutQs):
    assert len(queryInQs) == len(queryOutQs)
    queryData = dataPackage[0][startIndex:endIndex]
    numpyVec = dataPackage[1][startIndex:endIndex]
    qChunk = int(math.ceil(len(queryData)/len(queryInQs)))
    output = []
    count = 0
    for i in range(len(queryInQs)):
        si = i*qChunk
        ei = i*qChunk + qChunk
        l = len(queryData[si:ei])
        if l == 0 :
            break
        count += 1
        queryInQs[i].put(queryData[si:ei])
        # print("startIndex: {s}, endIndex: {e}, length: {l}".format(s=si, e=ei, l=l ) )
    for i in range(count):
        output += queryOutQs[i].get()
    # print(len(output), numpyVec.shape)
    return output, [numpyVec]

def _queryServer(queryInQs, queryOutQs, ekfcs, controlQ):
    assert len(queryInQs) == len(queryOutQs) == len(ekfcs)
    workers = []
    for i in range(len(queryInQs)):
        th = mp.Process(target=_queryHelper , args=(queryInQs[i], queryOutQs[i], ekfcs[i]))
        th.start()
        workers.append(th)
    controlQ.get()
    for w in workers:
        w.join()

def _queryHelper(inQ, outputQ, ekfc):
    while True:
        queryData = inQ.get()
        if type(queryData) is not list:
            print("Query data should be a list")
            print(type(queryData))
        if queryData is None:
            break
        y_a_json = ekfc.sendRequest('h', queryData)['ekf']
        outputQ.put(y_a_json)

def toNumpyFunc(dataPackage, startIndex, endIndex, nameToIndex):
    jsonLogs = dataPackage[0][startIndex:endIndex] # Y_a_json
    numpyVec = dataPackage[1][startIndex:endIndex] # X_a
    output = []
    idx = 0
    for log in jsonLogs:
        y_a = pul.to_vec(log, nameToIndex, len(nameToIndex))
        # if numpyVec[idx, 627] != 0:
        #     print(numpyVec[idx, 627], y_a[627], y_a[1211])
        output.append(y_a)
        idx+=1
    return numpyVec, np.array(output) # X_a, Y_a

def taskSave(poolQ, cQ, outputDir):
    # Only exit if the initial task ended and the save buffer is all processed
    save_pool = {}
    # backlog = {}
    paused = False
    while True:
        # print('Waiting for input Q, current pool count', len(save_pool))
        package = poolQ.get()
        if package is None:
            break
        if type(package) == dict:
            print('New dataset Request')
            request = package['type']
            if request == 'new':
                # setup save_pool
                name = package['name']
                save_pool[name] = package['package']
            paused = len(save_pool) >= SAVE_POOL_MAX
            cQ.put(paused)
            continue
        data = package
        name = data[0]
        offset = data[1]
        X_a = data[2]
        Y_a = data[3]

        # print('save: ', X_a.shape, Y_a.shape)
        assert X_a.shape == Y_a.shape
        dataLength = X_a.shape[0]

        dataToSave= None

        if name not in save_pool:
            print("{n} was not declared in save_pool.".format(n=name))
            print('Exiting')
            break
            continue

        save_pool[name]['data'][0][offset:offset+dataLength] = X_a
        save_pool[name]['data'][1][offset:offset+dataLength] = Y_a
        remaining = save_pool[name]['count'] - dataLength
        save_pool[name]['count'] = remaining

        if remaining == 0:
            dataToSave = save_pool.pop(name)
            if paused:
                paused = len(save_pool) >= SAVE_POOL_MAX 
                cQ.put(paused)
        
        if dataToSave is not None:
            originalName = dataToSave['original']
            dataToSave = np.array(dataToSave['data'])
            if dataToSave.shape[0] == 2:
                dataToSave = np.swapaxes(dataToSave, 0,1)
            saveDir = os.path.join(outputDir, originalName)
            if not os.path.isdir(saveDir):
                os.mkdir(saveDir)
            savePath = os.path.join(saveDir, name)
            while True:
                if not os.path.isfile(savePath+'.npz'):
                    print(savePath)
                    np.savez_compressed(savePath, h=dataToSave)
                    break
                tokens = savePath.split("-")
                tokens[-1] = str(int(tokens[-1])+1)
                savePath = '-'.join(tokens)

def genericTask(inputQ, outputQ, func, funcAuxArg, chunkSize, preamble=None, postamble=None):
    if preamble is not None:
        preambleFunc = preamble[0]
        preambleArgs = preamble[1]
        preambleFunc(**preambleArgs)
    while True:
        data = inputQ.get()
        if data is None:
            outputQ.put(None)
            break
        
        name = data[0]
        offset = data[1]
        funcInputs = data[2]
        funcArgs = data[3]

        currentOffset = offset
        if chunkSize < 0:
            chunkSize = len(funcInputs)
        for i in range(0, len(funcInputs), chunkSize):
            funcIn = [funcInputs] + funcArgs
            funcOut, nextContext = func(funcIn, startIndex=i, endIndex=i+chunkSize, **funcAuxArg)
            outputQ.put([name, currentOffset, funcOut, nextContext])
            currentOffset = offset + i
    if postamble is not None:
        postambleFunc = postamble[0]
        postambleArgs = postamble[1]
        postambleFunc(**postambleArgs)


def expander(vecs, ioi, minVals, maxVals):
    output = np.copy(vecs)
    noise = np.random.uniform(low=minVals[ioi] , high=maxVals[ioi], size=(output.shape[0],len(ioi)))
    output[:,ioi] += noise
    print(np.linalg.norm(vecs - output), np.linalg.norm(noise))
    return output

def getNewName(outputDir, file_name, suffix, c=0):
    while True:
        candidateName = os.path.join(outputDir, file_name + suffix+'-%d'%(count))
        if not os.path.isfile(candidateName):
            return candidateName, count
        count += 1
    
def getSizeOfDict(dictObj):
    output = sys.getsizeof(dictObj)
    if type(dictObj) is list:
        for e in dictObj:
            output += getSizeOfDict(e)
        return output
    elif type(dictObj) is dict: 
        for k, v in dictObj.items():
            output += sys.getsizeof(k)
            output += getSizeOfDict(v)
        return output
    else:
        return output

def closeAllQueriers(ekfcs):
    for e in ekfcs:
        e.close()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Collect data')
    parser.add_argument('-d', '--logdir', type=str, default='./data/log',
                    help='Directory of the log')
    parser.add_argument('-o', '--output', type=str, default=None,
                    help='Output of where the plots and statistics should be saved to')
    parser.add_argument('-l', '--lookup', type=str, default='index/', help="Path to lookup table dir to serialize the log")
    parser.add_argument('-p', '--parsed', action='store_true', help="Use the flag if the logDir is parsed (i.e., npz and not JSON)")
    parser.add_argument('-a', '--address', type=str, default='localhost', help="Address of the EKF Server")
    parser.add_argument('-po', '--port', type=int, default=33344, help="Port of the EKF Server")
    args = parser.parse_args()

    logDir = os.path.abspath(args.logdir)

    indexToName, nameToIndex, indexToType = puf.loadLookUp(args.lookup)

    influence = None
    influenceJsonPath = os.path.join(args.lookup, 'influence.json')
    with open(influenceJsonPath, 'r') as f:
        influence = json.load(f)

    if not args.parsed:
        exit('NOT SUPPORTING UNPARSED DATA')

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

    with open(os.path.join(args.lookup, 'targetNames.json'), "r") as f:
        targetNamesJson = json.load(f)
        for v in targetNamesJson.values():
            TARGET_NAMES += v
    for n in TARGET_NAMES:
        VICTIM_INDICES.append(nameToIndex[n])
    VICTIM_INDICES = list(set(VICTIM_INDICES))
    
    logNames = aud.get_parsed_logs(logDir)

    loadTaskOutQ = mp.Queue()
    saveTaskInQ = mp.Queue()
    poolControlQ = mp.Queue()

    noiseTaskOutQ = mp.Queue()
    listTaskOutQ = mp.Queue()
    jsonTaskOutQ = mp.Queue()
    queryTaskOutQ = mp.Queue()
    vecTaskOutQ = mp.Queue()

    addNoiseTaskArgs = [loadTaskOutQ, noiseTaskOutQ, addNoiseFunc, {}, -1, ]
    toListTaskArgs = [noiseTaskOutQ, listTaskOutQ, toListFunc, {'indexToType':indexToType}, -1, ]
    toJsonTaskArgs = [listTaskOutQ, jsonTaskOutQ, toJsonFunc,
                      {'logStruct':logFormat, 'nameToIndex':nameToIndex, 'root':''}, -1, ]
    ekfcs = []
    ekfcsCount = 4
    for _ in range(ekfcsCount):
        ekfcs.append(EKFInterface(args.address, args.port))

    queryInQs = [mp.Queue() for _ in range(ekfcsCount)]
    queryOutQs = [mp.Queue() for _ in range(ekfcsCount)]
    controlQ = mp.Queue()

    queryTaskArgs = [jsonTaskOutQ, queryTaskOutQ, query,
                      {"queryInQs":queryInQs, "queryOutQs":queryOutQs}, -1, None, None, ] 
    toVecTaskArgs = [queryTaskOutQ, saveTaskInQ, toNumpyFunc,
                      {'nameToIndex':nameToIndex}, -1, ]


    # spawn task threads
    startTime = time.time()
    threads = {}
    threads['queryServer'] = mp.Process(target=_queryServer, args=(queryInQs, queryOutQs, ekfcs, controlQ, ))
    threads['load'] = mp.Process(target=taskLoad , args=(loadTaskOutQ, saveTaskInQ, poolControlQ, logNames, args.output, VICTIM_INDICES, 5, 64, )) 
    threads['addNoise'] = mp.Process(target=genericTask, args=addNoiseTaskArgs)
    threads['toList'] = mp.Process(target=genericTask, args=toListTaskArgs)
    threads['toJson'] = mp.Process(target=genericTask, args=toJsonTaskArgs)
    threads['query'] = mp.Process(target=genericTask, args=queryTaskArgs)
    threads['toVec'] = mp.Process(target=genericTask, args=toVecTaskArgs)
    threads['save'] = mp.Process(target=taskSave, args=[saveTaskInQ, poolControlQ,args.output, ]) 
    for k,v in threads.items():
        print('starting: {t}'.format(t=k))
        v.start()
    joinOrder = ['save', 'toVec', 'query', 'toJson', 'toList', 'addNoise', 'load']
    for k in joinOrder:
        v = threads[k]
        print('Waiting for: {t}'.format(t=k))
        v.join()
    controlQ.put(None)
    threads['queryServer'].join()
    closeAllQueriers(ekfcs)
    print("Time eclipsed: ", time.time() - startTime)