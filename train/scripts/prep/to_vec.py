import argparse
import json
import os
import numpy as np
import snappy
import re
from tqdm import tqdm
import utils.vectorizer as uv
import utils.logHandler as ul


# def log_to_full_name(logObj,  root=''):
#     output = {}
#     for k,v in logObj.items():
#         full_name = root+"."+k
#         if root == '':
#             full_name = k
                
#         if type(v) is dict:
#             subObj = log_to_full_name(v,  full_name)
#             output.update(subObj)
#         elif type(v) is list:
#             for i in range(len(v)):
#                 key = full_name+'[%d]'%i
#                 if type(v[i]) is dict:
#                     result = log_to_full_name(v[i], key)
#                     output.update(result)
#                 else:
#                     output[key] = v[i]
#         else:
#             output[full_name] = v
#     return output

# def to_vec(logObj, name2index, max_len):
#     uv.reorder_ringbuffer(logObj)
#     expanded = log_to_full_name(logObj)
#     output = np.zeros(max_len)
#     for k,v in expanded.items():
#         if k not in name2index:
#             print("%s DOES NOT EXIST IN NAME2INDEX"%k)
#             exit("%s DOES NOT EXIST IN NAME2INDEX"%k)
#         if type(name2index[k]) is list:
#             output[name2index[k][0]:name2index[k][-1]+1] = v
#         else:
#             output[name2index[k]] = v
#     return output

def parsed_dataset(hist, name2index, max_len):
    pref_postf = []
    postf_posth = []
    for h in hist:
        pref = ul.to_vec(h['pref'],  name2index, max_len)
        postf = ul.to_vec(h['postf'], name2index, max_len)
        pref_postf.append([pref,postf])
        np.swapaxes(pref_postf, 0, 1)
        if 'posth' in h:
            posth = ul.to_vec(h['posth'], name2index, max_len)
            postf_posth.append([postf, posth])
            
    return np.array(pref_postf), np.array(postf_posth)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
                        prog = 'Log to Vec',
                        description = 'Converts JSON log into a vector of fixed size',
                        epilog = '')
    parser.add_argument('-i', '--input', type=str, help="Input JSON file path or directory")
    parser.add_argument('-o', '--output', type=str, default='data/parsed',help="Output directory path")
    parser.add_argument('-l', '--lookup', type=str, default='index/', help="Path to lookup table dir to serialize the log")
    args = parser.parse_args()

    path_to_name2index = os.path.join(args.lookup, 'nameToIndex.json')
    path_to_index2name = os.path.join(args.lookup, 'indexToName.json')
    if not os.path.isdir(args.output):
        exit('Specified output directory does not exist: %s'%args.output)
    is_dir = False
    if not os.path.isfile(args.input):
        # exit('Specified input file does not exist: %s'%args.input)
        is_dir = True
    if not os.path.isdir(args.lookup):
        exit('Specified lookup table does not exist: %s'%args.lookup)
    elif not os.path.isfile(path_to_name2index):
        exit('The following lookup table does not exist in the lookup dir: %s'%path_to_name2index)
    elif not os.path.isfile(path_to_index2name):
        exit('The following lookup table does not exist in the lookup dir: %s'%path_to_index2name)
    
    logObj = {}
    name2index = {}
    index2name = []
    output = None
    with open(path_to_name2index, "r") as f:
        name2index = json.load(f)
    with open(path_to_index2name, "r") as f:
        index2name = json.load(f)
    max_len = len(index2name)
    if is_dir:
        dir_list = os.listdir(args.input)
        pattern = re.compile(r'\b[0-9]{2}_[0-9]{2}_[0-9]{2}_[0-9]{2}_[0-9]{2}\.json.snappy\b')
        output = []
        for logName in tqdm(list(filter(pattern.match, dir_list))):
            logJson = {}
            logPath = os.path.join(args.input, logName)
            logBaseName = os.path.basename(logName).split('.')[0]
            output_path = os.path.join(args.output, logBaseName)
            with open(logPath, 'rb') as f:
                logJson = json.loads(snappy.decompress(f.read()))
            f, h = parsed_dataset(logJson['hist'], name2index, max_len)
            np.savez_compressed(output_path, f=f, h=h)
    else:
        input_file_name, input_file_ext = os.path.splitext(args.input)
        input_file_name = os.path.basename(input_file_name).split(".")[0]
        output_path = os.path.join(args.output, input_file_name)
        if input_file_ext == '.snappy':
            with open(args.input, "rb") as f:
                logObj = json.loads(snappy.decompress(f.read()))
        else:
            with open(args.input, "r") as f:
                logObj = json.load(f)
        f, h = parsed_dataset(logObj['hist'], name2index, max_len)
        np.savez_compressed(output_path, f=f, h=h)
