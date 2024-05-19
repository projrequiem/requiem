#!/bin/python3
import argparse
import json
import snappy
import os
from utils.file import loadJson, keySwap, getFileNameExt

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
                        prog = 'Log to Vec',
                        description = 'Converts JSON log into a vector of fixed size',
                        epilog = '')
    parser.add_argument('-i', '--input', type=str, help="Input JSON file path")
    parser.add_argument('-o', '--output', type=str, help="Output directory path")
    parser.add_argument('-l', '--lookup', type=str, default='index/', help="Path to lookup table dir to decode log")
    parser.add_argument('-c', '--compress', action='store_true', help="If trying to compress the log")
    args = parser.parse_args()

    if not os.path.isdir(args.output):
        exit('Specified output directory does not exist: %s'%args.output)
    if not os.path.isdir(args.lookup):
        exit('Specified lookup table does not exist: %s'%args.lookup)
    
    swapTable = {}
    tablePath = ''
    if args.compress:
        tablePath = os.path.join(args.lookup, 'nameToId.json')
    else:
        tablePath = os.path.join(args.lookup, 'idToName.json')
    with open(tablePath, 'r') as f:
        swapTable = json.load(f)
    
    logObj = loadJson(args.input)['hist']
    hist = []
    for l in logObj:
        newL = {}
        newL['pref'] = keySwap(l['pref'], swapTable)
        newL['postf'] = keySwap(l['postf'], swapTable)
        if 'posth' in l:
            newL['posth'] = keySwap(l['posth'], swapTable)
        hist.append(newL)
    outObj = {'hist':hist}
    
    fileName, _ = getFileNameExt(args.input)
    output_path = os.path.join(args.output, fileName)
    with open(output_path, "w") as f:
        json.dump(outObj, f)
    
