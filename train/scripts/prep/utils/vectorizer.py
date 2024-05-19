import argparse
import json
import snappy
import os
import numpy as np
from crc import Calculator, Crc8

BUFFER_VARS=['_output_buffer','_imu_buffer','_gps_buffer','_mag_buffer','_baro_buffer','_output_vert_buffer']

# zero a struct
def zeroStruct(jsonObj):
    for k, v in jsonObj.items():
        if type(v) is list:
            for i in range(len(v)):
                e = v[i]
                if type(e) is dict:
                    jsonObj[k][i] = zeroStruct(e)
                else:
                    jsonObj[k][i] = 0
        elif type(v) is dict:
            jsonObj[k] = zeroStruct(v)
        else:
            jsonObj[k] = 0



def _reorder_ringbuffer(rbJson, zero=False):
    oldHead = rbJson['_head']
    oldTail = rbJson['_tail']

    newHead = 0
    newBuffer = []
    size = rbJson['_size']
    i = 0
    while i < size:
        index = (oldHead + i)%size
        newBuffer.append(rbJson['_buffer'][index])
        if index == oldTail:
            break
        i += 1
    newTail = i
    i+=1
    while i < size:
        index = (oldHead + i)%size
        if zero:
            zeroStruct( rbJson['_buffer'][index])
        newBuffer.append(rbJson['_buffer'][index])

        i += 1
    rbJson['_head'] = newHead
    rbJson['_tail'] = newTail
    rbJson['_buffer'] = newBuffer

def reorder_ringbuffer(logJson, bVar=BUFFER_VARS):
    for bv in bVar:
        if bv not in logJson:
            continue
        _reorder_ringbuffer(logJson[bv], zero=True)

def print_buffer(rbJson):
    checksum = []
    for b in rbJson['_buffer']:
        data = bytes(json.dumps(b).encode())
        calculator = Calculator(Crc8.CCITT, optimized=True)
        checksum.append(calculator.checksum(data))
    print('h:{h}\tt:{t}\tb:{b}'.format(h=rbJson['_head'],t=rbJson['_tail'],b=checksum))



if __name__ == '__main__':
    parser = argparse.ArgumentParser(
                        prog = 'Log to Vec',
                        description = 'Converts JSON log into a vector of fixed size',
                        epilog = '')
    parser.add_argument('-i', '--input', type=str, help="Input JSON file path")
    parser.add_argument('-o', '--output', type=str, default='data/parsed',help="Output directory path")
    parser.add_argument('-l', '--lookup', type=str, default='index/', help="Path to lookup table dir to serialize the log")
    args = parser.parse_args()

    path_to_id2name = os.path.join(args.lookup, 'idToName.json')
    path_to_name2index = os.path.join(args.lookup, 'nameToIndex.json')
    path_to_index2name = os.path.join(args.lookup, 'indexToName.json')
    if not os.path.isdir(args.output):
        exit('Specified output directory does not exist: %s'%args.output)
    if not os.path.isfile(args.input):
        exit('Specified input file does not exist: %s'%args.input)
    if not os.path.isdir(args.lookup):
        exit('Specified lookup table does not exist: %s'%args.lookup)
    elif not os.path.isfile(path_to_name2index):
        exit('The following lookup table does not exist in the lookup dir: %s'%path_to_name2index)
    elif not os.path.isfile(path_to_index2name):
        exit('The following lookup table does not exist in the lookup dir: %s'%path_to_index2name)
    
    logObj = {}
    id2name = {}
    name2index = {}
    index2name = []
    output = None
    input_file_name, input_file_ext = os.path.splitext(args.input)
    input_file_name = os.path.basename(input_file_name.split(".")[0])
    if input_file_ext == '.snappy':
        with open(args.input, "rb") as f:
            logObj = json.loads(snappy.decompress(f.read()))
    else:
        with open(args.input, "r") as f:
            logObj = json.load(f)
    with open(path_to_name2index, "r") as f:
        name2index = json.load(f)
    with open(path_to_index2name, "r") as f:
        index2name = json.load(f)
    reorder_ringbuffer(logObj['hist'][-100]['posth'])
    exit()
    
    imu_buffer = logObj['hist'][-100]['posth']['_imu_buffer']
    print_buffer(imu_buffer)
    print('after_reorder')
    _reorder_ringbuffer(imu_buffer)
    print_buffer(imu_buffer)