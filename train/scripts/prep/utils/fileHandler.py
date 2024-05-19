#!/bin/python3
import json
import snappy 
import os
import errno

def loadJson(filePath):
    output = None
    # Check if the file exists
    if not os.path.isfile(filePath):
        raise FileNotFoundError(errno.ENOENT, os.strerror(errno.ENOENT), filePath)

    # handles snappy
    if filePath.endswith('.snappy'):
        with open(filePath, "rb") as f:
            output = json.loads(snappy.decompress(f.read()))
    else:
        with open(filePath, "r") as f:
            output = json.load(f)
    return output

def loadLookUp(lookupDir):
    path_to_indexToName = os.path.join(lookupDir, 'indexToName.json')
    path_to_nameToIndex = os.path.join(lookupDir, 'nameToIndex.json')
    path_to_indexToType = os.path.join(lookupDir, 'indexToType.json')
    return loadJson(path_to_indexToName), loadJson(path_to_nameToIndex), loadJson(path_to_indexToType)

def getFileNameExt(filePath):
    input_file_name, input_file_ext = os.path.splitext(filePath)
    input_file_name = os.path.basename(input_file_name)
    if '.' in input_file_name:
        input_file_name = input_file_name.split('.')[0]
    return input_file_name, input_file_ext

def keySwap(obj, nameMap):
    output = {}
    for k,v in obj.items():
        try:
            if type(v) is dict:
                output[nameMap[k]] = keySwap(v, nameMap)
            else:
                output[nameMap[k]] = v
        except KeyError as e:
            print("%s"%(str(obj)))
            print("key: %d does not exist in lookup"%(k))
            exit()
    return output
