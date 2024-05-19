#!/bin/python3
from parse import *
import numpy as np
import matplotlib.pyplot as plt
import os
import re
import snappy
import json

def extractPos(logDir):
    dir_list = os.listdir(logDir)
    pattern = re.compile(r'\b[0-9]{2}_[0-9]{2}_[0-9]{2}_[0-9]{2}_[0-9]{2}\.json.snappy\b')
    output = []
    for logName in list(filter(pattern.match, dir_list)):
        pos = []
        logPath = os.path.join(logDir, logName)
        logJson = {}
        with open(logPath, 'rb') as f:
            logJson = json.loads(snappy.decompress(f.read()))
        for vp in logJson['velpos']:
            pos.append(vp[-3:])
        output.append(pos)
    return output

def extractField(logJson, path):
    output = []
    for l in logJson['hist']:
        obj = l
        for k in path:
            obj = obj[k]
        output.append(obj)
    return output

def extractFields(logJson, paths):
    output = []
    for l in logJson['hist']:
        o = []
        for p in paths:
            obj = l
            for k in p:
                if type(k) is str and k not in obj:
                    obj = None
                    break
                obj = obj[k]
            o.append(obj)
        output.append(o)
    return output

def extractFromLogs(logDir, logOps, args):
    dir_list = os.listdir(logDir)
    pattern = re.compile(r'\b[0-9]{2}_[0-9]{2}_[0-9]{2}_[0-9]{2}_[0-9]{2}\.json.snappy\b')
    output = []
    logNames = list(filter(pattern.match, dir_list))
    for name in logNames:
        logPath = os.path.join(logDir, name)
        logJson = {}
        with open(logPath, 'rb') as f:
            logJson = json.loads(snappy.decompress(f.read()))
        output.append(logOps(logJson, **args))
    return zip(logNames, output)

def getParsedDataNames(logDir):
    output = {}
    dir_list = os.listdir(logDir)
    pattern = re.compile(r'\b[0-9]{2}_[0-9]{2}_[0-9]{2}_[0-9]{2}_[0-9]{2}.npz')
    parsed_log_names = list(filter(pattern.match, dir_list))
    for name in parsed_log_names:
        n = name.split('.')[0]
        output[n] = {'original':os.path.join(logDir, name)}
        extended_dir = os.path.join(logDir, n)
        if os.path.isdir(extended_dir):
            extended_pattern = re.compile(n + '[\(0-9\)]+\-[0-9]+.npz')
            extended_data_names = list(filter(extended_pattern.match, os.listdir(extended_dir)))
            output[n]['extended'] = {}
            for ename in extended_data_names:
                em, count = ename.split('.')[0].split('-')
                count = int(count)
                em = em[len(n):]
                if em not in output[n]['extended']:
                    output[n]['extended'][em] = {}
                output[n]['extended'][em][count] = os.path.join(extended_dir, ename)
    return output

def searchPath(indexToName, keyword, blacklist=[], prepend=[], postpend=[]):
    path = []
    for name in indexToName:
        if keyword in name:
            skip = False
            for b in blacklist:
                if b in name:
                    skip = True
                    break
            if skip:
                continue
            p = []
            for t in name.split('.'):
                if '[' in t:
                    n, index = parse("{}[{}]", t.strip())
                    p.append(n)
                    p.append(int(index))
                else:
                    p.append(t)
            p = prepend + p + postpend
            path.append(p)
    return path