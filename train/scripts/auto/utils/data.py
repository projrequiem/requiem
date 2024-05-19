#!/bin/python3
import torch
import os
import json
from datetime import datetime
import re
import time
import snappy

def get_logs(dirname):
    dir_list = os.listdir(dirname)
    pattern = re.compile(r'\b[0-9]{2}_[0-9]{2}_[0-9]{2}_[0-9]{2}_[0-9]{2}\.json\b')
    return list(filter(pattern.match, dir_list))

def get_parsed_logs(dirname):
    dir_list = os.listdir(dirname)
    pattern = re.compile(r'\b[0-9]{2}_[0-9]{2}_[0-9]{2}_[0-9]{2}_[0-9]{2}\.npz\b')
    parsed_log_names =  list(filter(pattern.match, [os.path.basename(x) for x in dir_list] ))
    return [os.path.join(dirname, r) for r in parsed_log_names]

def gen_log_name():
    return datetime.fromtimestamp(time.time()).strftime('%m_%d_%H_%M_%S')

def save(savePath, logJson):
    with open(savePath, "wb") as f:
        f.write(snappy.compress(json.dumps(logJson)))

def collectLogs(dataDir):
    output = []
    # parse input file and convert it to a log
    onlyLogs = [int(f.split('.')[0]) for f in os.listdir(dataDir) if os.path.isfile(os.path.join(dataDir, f)) and f.endswith('.json')]
    onlyLogs.sort()
    errorCounter = 0
    counter = 0
    for logCounter in onlyLogs:
        try:
            logPath = os.path.join(dataDir, '%d.json'%logCounter)
            content = ''
            with open(logPath, "r") as f:
                content = f.read().split('\n')[0]
            logObj = json.loads(content)['snapshot']
            output.append(logObj)
            counter += 1
        except ValueError as e:
            print('issues with %d', logCounter)
            errorCounter+=1
            continue
    print("%d / %d "%(errorCounter, errorCounter + counter))
    return output

def cleanDir(dataDir):
    # Removes all logs in the directory
    onlyLogs = [os.path.join(dataDir, f) for f in os.listdir(dataDir) if os.path.isfile(os.path.join(dataDir, f)) and f.endswith('.json')]
    for log in onlyLogs:
        os.remove(log)
