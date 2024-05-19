#!/bin/python3
import os
import re
import torch
import numpy as np
import errno
import json
import snappy
from parse import parse
from importlib.machinery import SourceFileLoader
_current_script_dir = os.path.realpath(os.path.dirname(__file__))
vectorizer = SourceFileLoader('vectorizer',os.path.join(_current_script_dir, 'vectorizer.py')).load_module()
from tqdm import tqdm

TYPE_JSON = 'JSON'
TYPE_NUMPY = 'NUMPY'
TYPE_TORCH = 'TORCH'

def log_to_full_name(logObj,  root=''):
    output = {}
    for k,v in logObj.items():
        full_name = root+"."+k
        if root == '':
            full_name = k
        if type(v) is dict:
            subObj = log_to_full_name(v,  full_name)
            output.update(subObj)
        elif type(v) is list:
            for i in range(len(v)):
                key = full_name+'[%d]'%i
                if type(v[i]) is dict:
                    result = log_to_full_name(v[i], key)
                    output.update(result)
                else:
                    output[key] = v[i]
        else:
            output[full_name] = v
    return output

def to_vec(logObj, name2index, max_len):
    vectorizer.reorder_ringbuffer(logObj)
    expanded = log_to_full_name(logObj)
    output = np.zeros(max_len)
    for k,v in expanded.items():
        if k not in name2index:
            print("%s DOES NOT EXIST IN NAME2INDEX"%k)
            exit("%s DOES NOT EXIST IN NAME2INDEX"%k)
        if type(name2index[k]) is list:
            output[name2index[k][0]:name2index[k][-1]+1] = v
        else:
            output[name2index[k]] = v
    return output

def lookUp(path, obj):
    if len(path) == 0:
        return obj
    return lookUp(path[1:], obj[path[0]])

def vec_to_log(vec, logStruct, nameToIndex, root=''):
    output = {}
    for k,v in logStruct.items():
        full_name = root+"."+k
        if root == '':
            full_name = k
        if type(v) is dict:
            output[k] = vec_to_log(vec, v, nameToIndex, full_name)
        elif type(v) is list:
            arr = []
            for i in range(len(v)):
                key = full_name+'[%d]'%i
                if type(v[i]) is dict:
                    arr.append(vec_to_log(vec, v[i], nameToIndex, key))
                else:
                    val = vec[nameToIndex[key]]
                    arr.append(val)
            output[k] = arr
        else:
            val = vec[nameToIndex[full_name]]
            output[k] = val
    return output

def listJsonLogs(logDir):
    dir_list = os.listdir(logDir)
    pattern = re.compile(r'\b[0-9]{2}_[0-9]{2}_[0-9]{2}_[0-9]{2}_[0-9]{2}\.json.snappy\b')
    return list(filter(pattern.match, dir_list))

# Returns list of indexables
def nameToPath(indexToName):
    path = []
    for name in indexToName:
        p = []
        for t in name.split('.'):
            if '[' in t:
                n, index = parse("{}[{}]", t.strip())
                p.append(n)
                p.append(int(index))
            else:
                p.append(t)
        path.append(p)
    return path

def createStruct(walkPaths, walked=[], context=None):
    if len(walkPaths) == 0:
        return None 
    if context is None:
        context = {}
    walked.append(walkPaths[0])
    if walkPaths[0] not in context:
        context[walkPaths[0]] = createStruct(walkPaths[1:], walked)
    else:
        context[walkPaths[0]] = createStruct(walkPaths[1:], walked, context[walkPaths[0]])
    return context

def adjustArrayInStruct(logFormat):
    if logFormat is None:
        return None
    output = {}
    for k,v in logFormat.items():
        if type(v) is dict:
            isInt = False
            for n in v.keys():
                if type(n) is int:
                    isInt = True
                    break
            if isInt:
                output[k] = [adjustArrayInStruct(v[n]) for n in v.keys()]
            else:
                output[k] = adjustArrayInStruct(v)
        else:
            output[k] = v
    return output

def hasNone(logFormat):
    if logFormat is None:
        return True
    for _,v in logFormat.items():
        if type(v) is dict:
            if hasNone(v):
                return True
        elif type(v) is list:
            for i in v:
                if i is None:
                    return True
                if type(i) is dict:
                    if hasNone(i):
                        return True
        elif v is None:
            return True
    return False

class logStruct:
    def __init__(self, logPath):
        self.logPath = logPath
        self.type = None
        self.data = None

    def loadData(self):
        if self.logPath.endswith('.json') or self.logPath.endswith('.json.snappy'):
            self.type = TYPE_JSON
            self.data = spuf.loadJson(self.logPath)
        elif self.logPath.endswith('.npz'):
            self.type = TYPE_NUMPY 
            self.data = np.load(self.logPath)
        elif self.logPath.endswith('.pt'):
            self.type = TYPE_TORCH 
            self.data = torch.load(self.logPath)
        else:
            raise ValueError('This logstruct\'s type: {t} cannot be handled'.format(t=self.type))

    def toJson(self, exampleStruct, indexToName=None):
        if self.type == 'NUMPY' or self.type == 'PYTORCH':
            output = []
            for i in range(self.data.shape[0]):
                output.append(vec_to_log(self.data[i], exampleStruct, indexToName))
            return output
        if self.type == 'JSON':
            return self.data

    def toNumpy(self, nameToIndex=None):
        if self.type == 'NUMPY':
            return self.data
        if self.type == 'PYTORCH':
            return self.data.numpy()
        if self.type == 'JSON':
            output = []
            for h in self.data['hist']:
                output.append(to_vec(self.data, nameToIndex, len(nameToIndex)))

    def toTorch(self, nameToIndex=None):
        if self.type == 'NUMPY':
            return torch.from_numpy(self.data)
        if self.type == 'PYTORCH':
            return self.data
        if self.type == 'JSON':
            return torch.from_numpy(self.toNumpy(nameToIndex))

# Abstraction of log structure (i.e., handles multiple log formats)
class logManager:
    def __init__(self, logDir, lookupDir):
        self.dirs = {}
        self.nameToIndex = None
        self.indexToName = None
        logPaths = listJsonLogs(logDir)
        for p in logPaths:
            self.dirs[p] = logStruct(p)

    def listLogs(self):
        return self.dirs.keys()

    def getLogAsJson(self, logPath):
        return self.dirs[logPath].toJson()

    def getLogAsNumpy(self, logPath):
        return self.dirs[logPath].toNumpy()

    def getLogAsTensor(self, logPath):
        return self.dirs[logPath].toTensor()


if __name__ == '__main__':
    paths = ['a.b.c.d','a.b.c.e','a.c.e','a.a.b.c']
    context = {}
    for p in paths:
        context = createStruct(p, context)
