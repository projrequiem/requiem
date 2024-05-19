#!/bin/python3
import argparse
import json
import os
import snappy

N2I = {}
I2N = []
GLOBAL_INDEX_COUNTER = 0

def generate_index(obj, path, index=0):
    output = {}
    inverse_output = []
    current_index = index
    for k,v in obj.items():
        full_path = path + "." + k
        if path == "":
            full_path = k
        if type(v) is dict:
            result, inverse_result, current_index = generate_index(v, full_path, current_index)
            output.update(result)
            inverse_output+=inverse_result
        elif type(v) is list:
            for i in range(len(v)):
                if type(v[i]) is dict: 
                    result, inverse_result, current_index = generate_index(v[i], full_path+'[%d]'%i, current_index)
                    output.update(result)
                    inverse_output+=inverse_result
                else:
                    output[full_path+'[%d]'%i] =current_index 
                    inverse_output.append(full_path+"[%d]"%i)
                    current_index += 1
        else:
            output[full_path] = current_index
            #I2N.append(full_path)
            inverse_output.append(full_path)
            current_index += 1
    return output, inverse_output, current_index

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
                        prog = 'Log to Vec',
                        description = 'Converts JSON log into a vector of fixed size',
                        epilog = '')
    parser.add_argument('-i', '--input', type=str, help="Input JSON file path (e.g., data/log/MM_dd_hh_mm_ss.json)")
    parser.add_argument('-o', '--output', type=str, default=None, help="Output directory path other than the lookup")
    parser.add_argument('-l', '--lookup', type=str, default='index/', help="Path to lookup directory")
    args = parser.parse_args()

    if (args.output is not None) and (not os.path.isdir(args.output) ):
        exit('Specified output directory does not exist: %s'%args.output)
    if not os.path.isfile(args.input):
        exit('Specified input file does not exist: %s'%args.input)
    if not os.path.isdir(args.lookup):
        exit('Specified lookup table does not exist: %s'%args.lookup)
    

    
    inputObj = {}
    if args.input.endswith('.snappy'):
        with open(args.input, "rb") as f:
            inputObj = json.loads(snappy.decompress(f.read()))["hist"][-100]["pref"]
    else:
        with open(args.input, "r") as f:
            inputObj = json.load(f)["hist"][0]["pref"]
    
    nameToIndex, indexToName, maxIndex = generate_index(inputObj, "")
    print(len(indexToName))

    path_to_name2index = os.path.join(args.lookup, "nameToIndex.json")
    path_to_index2name = os.path.join(args.lookup, "indexToName.json")
    with open(path_to_name2index, "w") as f:
        json.dump(nameToIndex, f, indent=4)
    with open(path_to_index2name, "w") as f:
        json.dump(indexToName, f, indent=4)
