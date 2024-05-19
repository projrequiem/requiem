#!/bin/python3
import torch
import numpy as np
import os
import re
import time
import gc
import random
import multiprocessing
import functools
import json
import platform
from pathlib import Path

from importlib.machinery import SourceFileLoader
_current_script_dir = os.path.realpath(os.path.dirname(__file__))
print(_current_script_dir)

from parse import parse

DEBUG =  False

def debugPrint(*s):
    if DEBUG:
        print('DEBUG: ',*s)

def dataset_index_gen(dataset_root_dir):
    dataset_index = {'samples':[],'labels':[]}
    dir_list = os.listdir(dataset_root_dir)
    pattern_labels = re.compile(r'[0-9]{2}\_[0-9]{2}\_[0-9]{2}\_[0-9]{2}\_[0-9]{2}\-labels\-[0-9]\.pt')
    pattern_samples = re.compile(r'[0-9]{2}\_[0-9]{2}\_[0-9]{2}\_[0-9]{2}\_[0-9]{2}\-samples\-[0-9]\.pt')
    for dname in list(filter(pattern_labels.match, dir_list)):
        dataset_index['labels'].append(dname)
    for dname in list(filter(pattern_samples.match, dir_list)):
        subid, num = parse('{}-samples-{}.pt', dname)
        label_name = subid + '-labels-' + num + '.pt'
        if label_name not in dataset_index['labels']:
            raise Exception("Sample file ({dn}) does not have a corresponding label ({ln})".format(dn=dname, ln=label_name))
        dataset_index['samples'].append(dname)
    return dataset_index

def parsed_log_index(rootDir):
    index = []
    rootDirList = os.listdir(rootDir)
    origPattern = re.compile(r'[0-9]{2}\_[0-9]{2}\_[0-9]{2}\_[0-9]{2}\_[0-9]{2}.npz')
    count = 0
    logNameList = list(filter(origPattern.match, rootDirList))
    logNameList.sort()
    for logName in logNameList:
        # e.g., logName := 02_20_18_44_15.npz
        # Load the original
        logBaseName = logName.split('.')[0]
        extDir = os.path.join(rootDir, logBaseName)
        if not os.path.isdir(extDir):
            continue 
        origLogPath = os.path.join(rootDir, logName)
        parsedLog = np.load( origLogPath )['h']
        origLogExpectedFileSize = parsedLog.nbytes
        logLen = len(parsedLog)
        extPattern = re.compile(logBaseName + '\([0-9\_]+\)\-[0-9]+\.npz')
        for extName in list(filter(extPattern.match, os.listdir(extDir))):
            extLogPath = os.path.join(extDir, extName)
            # beginning indexing inclusive, ending index exclusive
            expectedFileSize = origLogExpectedFileSize
            logIndexEntry = {'extLogPath':extLogPath, 'origLogPath':origLogPath, 'startIndex':count,
                        'endIndex':count+logLen, 'expSize':expectedFileSize, 'origLogExpFileSize':origLogExpectedFileSize}
            index.append(logIndexEntry)
            count += logLen
    return index

def pop_random_element(s):
    if len(s) == 0:
        return None
    element = random.sample(sorted(s), 1)[0]
    s.discard(element)
    return element

# Cache loader task
def _fillCache(iq, oq):
    #  cached names
    cachedNames = set()
    # cache by index
    extIndexCache = {}
    origIndexCache = {}
    while True:
        req =  iq.get()
        if req is None:
            return
        if req['type'] == 'get':
            extOut = []
            origOut = []
            for i in req['indices']:
                extOut.append(extIndexCache[i])
                origOut.append(origIndexCache[i])
            oq.put({'ext':np.array(extOut),'orig':np.array(origOut),'indices':req['indices']})
        elif req['type'] == 'cache':
            ext = None
            orig = None
            if req['data']['extLogPath'] not in cachedNames:
                ext = np.load(req['data']['extLogPath'])['h']
            if req['data']['origLogPath'] not in cachedNames:
                orig = np.load(req['data']['origLogPath'])['h']
            for i in range(req['data']['startIndex'], req['data']['endIndex']):
                if ext is not None:
                    extIndexCache[i] = ext[i - req['data']['startIndex']]
                if orig is not None:
                    origIndexCache[i] = orig[i - req['data']['startIndex']]
        elif req['type'] == 'clear':
            for _,v in extIndexCache.items():
                del v
            for _,v in origIndexCache.items():
                del v
            del extIndexCache
            del origIndexCache
            del cachedNames
            gc.collect()
            extIndexCache = {}
            origIndexCache = {}
            cachedNames = {}
    return

def _batchHelper(cqi, partitionIdx, cachedNames:list, index:list, dataIndicesRemaining:set, cachedIndices:list, currentSize:list, cacheSizeLimit):
    idx = pop_random_element(dataIndicesRemaining)
    if idx is None:
        return False
    didx = index[idx]
    sizeRequired = 0
    if didx['extLogPath'] not in cachedNames[partitionIdx]:
        cachedNames[partitionIdx].add(didx['extLogPath'])
        sizeRequired += didx['expSize'] *2
    if didx['origLogPath'] not in cachedNames[partitionIdx]:
        cachedNames[partitionIdx].add(didx['origLogPath'])
        sizeRequired += didx['origLogExpFileSize'] *2
    if currentSize[partitionIdx] + sizeRequired > cacheSizeLimit:
        dataIndicesRemaining.add(idx)
        return False
    currentSize[partitionIdx] += sizeRequired
    cachedIndices[partitionIdx] = cachedIndices[partitionIdx].union(set(list(range(didx['startIndex'], didx['endIndex'])))) 
    cqi.put({'type':'cache', 'data':didx})
    if platform.system() != 'Darwin':
        while cqi.qsize() > 50:
            debugPrint('cache {} inputQueue Full'.format(partitionIdx))
            time.sleep(0.1)
    return True


def _batchTask(outputQ, cachePartition, index, dataIndices, batchSize, cacheSizeLimit):
    dataIndicesRemaining = set(dataIndices)
    currentPartitionIdx = 0
    setOfCachedNames = [set() for _ in range(cachePartition)]
    setOfCachedIndices = [set() for _ in range(cachePartition)]
    cacheWorkers = [None for _ in range(cachePartition)]
    currentCacheSize = [0 for _ in range(cachePartition)]
    cacheQs = []

    # Start loading data to the memory
    for i in range(cachePartition):
        debugPrint('caching for patition ', i)
        cacheQI = multiprocessing.Queue()
        cacheQO = multiprocessing.Queue()
        cacheQs.append({'input':cacheQI, 'output':cacheQO})
        cacheWorkers[i] = multiprocessing.Process(target=_fillCache, args=(cacheQI, cacheQO)) # create thread for this
        cacheWorkers[i].start()
        while True:
            success = _batchHelper(cacheQI, i, setOfCachedNames, index, dataIndicesRemaining, setOfCachedIndices, currentCacheSize, cacheSizeLimit)
            if not success:
                break

    debugPrint('Batching')
    while True:
        if len(setOfCachedIndices[currentPartitionIdx]) == 0:
            debugPrint('Exhausted cache', currentPartitionIdx, '\t refilling')
            debugPrint('files left', len(dataIndicesRemaining))
            # Free the cache and reload
            cacheQI = cacheQs[currentPartitionIdx]['input']
            cacheQI.put({'type':'clear'})
            currentCacheSize[currentPartitionIdx] = 0
            if len(dataIndicesRemaining) >  0:
                while True:
                    success = _batchHelper(cacheQI, currentPartitionIdx, setOfCachedNames, index, dataIndicesRemaining, setOfCachedIndices, currentCacheSize, cacheSizeLimit)
                    if not success:
                        break
            if functools.reduce(lambda a,b: len(a) + len(b), setOfCachedIndices) == 0:
                break
            currentPartitionIdx += 1
            currentPartitionIdx %= cachePartition
            debugPrint('new partition index', currentPartitionIdx)
        outputIndices = []
        for _ in range(batchSize):
            idx = pop_random_element(setOfCachedIndices[currentPartitionIdx])
            if idx is None:
                break
            outputIndices.append(idx)
        cacheQs[currentPartitionIdx]['input'].put({'type':'get','indices': outputIndices})
        data = cacheQs[currentPartitionIdx]['output'].get()

        if platform.system() != 'Darwin':
            while outputQ.qsize() > 50:
                debugPrint('batch outputQueue Full')
                time.sleep(0.1)
        outputQ.put(data)
    for i in range(cachePartition):
        debugPrint('Joining worker', i)
        cacheQs[i]['input'].put(None)
        cacheWorkers[i].join()
    outputQ.put(None)


def binarySearch(logIndexTable, idx):
    head = 0
    tail = len(logIndexTable)-1
    while head < tail:
        middle = int((tail-head)/2) + head
        if idx < logIndexTable[middle]['startIndex']:
            if tail == middle:
                tail += 1
            else:
                tail = middle
            continue
        if idx >= logIndexTable[middle]['endIndex']:
            if head == middle:
                head += 1
            else:
                head = middle
            continue
        return middle
    return head

class LogDataLoader:
    def __init__(self, root_dir, maxLen = -1):
        self._root = root_dir
        rootDirList = os.listdir(self._root)
        dataNamePattern = re.compile(r'[0-9]+.pt')
        self._len = len(list(filter(dataNamePattern.match, rootDirList)))
        self._maxLen = maxLen
        self._perm = None
        if self._maxLen >= 0:
            torch.manual_seed(333)
            self._perm = torch.randperm(self._len)[:self._maxLen]


    def __len__(self):
        if self._maxLen > 0:
            return self._maxLen
        return self._len

    def __getitem__(self, idx):
        sample = None
        if self._maxLen < 0:
            sample = torch.load(os.path.join(self._root, '{:d}.pt'.format(idx)))
        else:
            newIdx = self._perm[idx]
            sample = torch.load(os.path.join(self._root, '{:d}.pt'.format(newIdx)))
        return  sample['orig_postf'], sample['orig_posth'], sample['ext_postf'], sample['ext_posth']

class LogDataset:
    def __init__(self, root_dir, transform=None, cacheCapacity=1e9, batchSize=32, randomSeed=0, cachePartition=1):
        self.root_dir = root_dir
        self.transform = transform
        self.index = parsed_log_index(root_dir)
        self._labelDistribution = None
        labelDistributionPath = os.path.join(self.root_dir, 'labelDistribution.json')
        if os.path.isfile(labelDistributionPath):
            with open(labelDistributionPath, 'r') as f:
                self._labelDistribution = json.load(f)

        # for iteration
        self._batchQueue = multiprocessing.Queue()
        self._batchWorker = None
        self._cacheCapacity = cacheCapacity
        self._cachePartition = cachePartition
        self._batchSize = batchSize

    def __len__(self):
        return self.index[-1]['endIndex']

    def __getitem__(self, idx):
        if torch.is_tensor(idx):
            idx = idx.tolist()
        debugPrint(idx)
        pass
    
    def hasLabelDist(self):
        return self._labelDistribution != None
    def getPLabelCount(self):
        return self._labelDistribution['p_count']
    def getNLabelCount(self):
        return self._labelDistribution['n_count']
    
    def _getdata(self, idx):
        print('GET DATA FUNCTION NOT SUPPORTED')
        return None
    
    def __iter__(self):
        # Spawn cache threads and send cache requests
        fileIndices = list(range(len(self.index)))
        print(len(fileIndices))
        random.shuffle(fileIndices)
        taskArgs = {'outputQ':self._batchQueue, 'cachePartition':self._cachePartition, 'index':self.index, 'dataIndices':fileIndices, 'batchSize':self._batchSize, 'cacheSizeLimit':self._cacheCapacity}
        self._batchWorker = multiprocessing.Process(target=_batchTask, kwargs=taskArgs)
        self._batchWorker.start()
        return self
    
    def __next__(self):
        b = self._batchQueue.get()
        if b is None:
            raise StopIteration
        return b['ext'], b['orig'], b['indices']