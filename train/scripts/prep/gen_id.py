#!/bin/python3
import argparse
import json
import os
import snappy
from utils.file import loadJson

# serialize to a single array
# generate index for keys
GLOBAL_ID = 0
N2ID = {}

def generate_id(obj):
    global GLOBAL_ID, N2ID
    for k,v in obj.items():
        if k not in N2ID:
            N2ID[k] = GLOBAL_ID
            GLOBAL_ID += 1
        if type(v) is dict:
            generate_id(v)

def compress(obj):
    global N2ID
    output = {}
    for k,v in obj.items():
        if type(v) is dict:
            output[N2ID[k]] = compress(v)
        else:
            output[N2ID[k]] = v
    return output


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
                        prog = 'Generate unique IDs for each field from a log',
                        description = 'Converts JSON log into a vector of fixed size',
                        epilog = '')
    parser.add_argument('-i', '--input', type=str, help="Input name to type file")
    parser.add_argument('-o', '--output', type=str, default=None, help="Output directory path other than the lookup")
    args = parser.parse_args()


    if (args.output is not None) and (not os.path.isdir(args.output) ):
        exit('Specified output directory does not exist: %s'%args.output)

    inputObj = loadJson(args.input)
    
    generate_id(inputObj)
    with open(os.path.join(args.output, 'nameToId.json'), "w") as f:
        json.dump(N2ID, f)

    ID2N = {}
    for k,v in N2ID.items():
        ID2N[format(v, 'x')] = k
    with open(os.path.join(args.output, 'idToName.json'), "w") as f:
        json.dump(ID2N, f)