#!/bin/python3
import sys
import os
from pathlib import Path
current_file_path = Path(os.path.realpath(__file__))
script_path = str(current_file_path.parent.parent.resolve())
sys.path.append(script_path)
import argparse
import os
import json
import prep.gen_index  as spg
import prep.utils.logHandler  as sul


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
                        prog = 'Log to Vec',
                        description = 'Converts JSON log into a vector of fixed size',
                        epilog = '')
    parser.add_argument('-l', '--lookup', type=str, default='index/', help="Path to lookup table dir to serialize the log")
    args = parser.parse_args()
    pathToNameToType = os.path.join(args.lookup, 'nameToType.json')
    pathToIndexToName = os.path.join(args.lookup, 'indexToName.json')
    pathToNameToIndex = os.path.join(args.lookup, 'nameToIndex.json')
    nameToType = {}
    nameToIndex = {}
    indexToName = []
    with open(pathToNameToType, "r") as f:
        nameToType = json.load(f)
    with open(pathToIndexToName, "r") as f:
        indexToName = json.load(f)
    with open(pathToNameToIndex, "r") as f:
        nameToIndex = json.load(f)
    fullNameType = sul.log_to_full_name(nameToType)

    indexToType = [None for _ in range(len(indexToName))]
    for k,v in nameToIndex.items():
        indexToType[v] = fullNameType[k]
    for t in indexToType:
        if t is None:
            exit('THERE IS NONE')
    
    pathToIndexToType = os.path.join(args.lookup, 'indexToType.json')
    with open(pathToIndexToType, 'w') as f:
        json.dump(indexToType, f)