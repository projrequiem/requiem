import os
import json
import numpy as np
import joblib
from pathlib import Path

_VERSION = 0.1
_NAME = 'spec_test'

tau = 0.4
target_func = 'h'

_script_dir = os.path.realpath(os.path.dirname(__file__))

_indexToName = None
_nameToIndex = None
_indexToType = None
with open(os.path.join(_script_dir, 'indexToName.json'),'r') as f:
    _indexToName = json.load(f)
with open(os.path.join(_script_dir, 'nameToIndex.json'),'r') as f:
    _nameToIndex = json.load(f)
with open(os.path.join(_script_dir, 'indexToType.json'),'r') as f:
    _indexToType = json.load(f)
_path_to_indices = os.path.join(_script_dir, 'indices.json')

def _condition_innov_index(n):
    if 'gps' in n and '_innov[' in n:
        return True
    if 'mag' in n and '_innov[' in n:
        return True
    if '_baro_hgt_innov' == n :
        return True
    return False

def _extract_state_gps_indices(i2n):
    output = []
    name_output = []
    for i in range(len(i2n)):
        n = i2n[i]
        if '_state.' in n:
            output.append(i)
            name_output.append(n)
        elif '_gps_buffer._buffer[0]' in n:
            if 'time' in n:
                continue
            output.append(i)
            name_output.append(n)
    return output, name_output
def _get_ang_rate_delayed_raw_indices(n2i):
    output = []
    name_output = []
    for i in range(3):
        output.append(n2i['_ang_rate_delayed_raw[{}]'.format(i)])
        name_output.append('_ang_rate_delayed_raw[{}]'.format(i))
    return output, name_output
def _get_r_to_earth_indices(n2i):
    output = []
    for i in range(9):
        output.append(n2i['_R_to_earth[{}]'.format(i)])
    return output
def _get_pos_body_indices(n2i):
    output = []
    for i in range(3):
        output.append(n2i['_params.imu_pos_body[{}]'.format(i)])
        output.append(n2i['_params.gps_pos_body[{}]'.format(i)])
    return output

_state_gps_indices, _state_gps_names = _extract_state_gps_indices(_indexToName)
_ang_rate_delayed_raw_indicies, _ang_rate_delayed_raw_names = _get_ang_rate_delayed_raw_indices(_nameToIndex)
_r_to_earth_indices = _get_r_to_earth_indices(_nameToIndex)
_pos_body_indices = _get_pos_body_indices(_nameToIndex)
for i in range(len(_state_gps_names)):
    print(i, _state_gps_names[i])


_innov_indices = []
if not os.path.isfile(_path_to_indices):
    for n in _indexToName:
        if _condition_innov_index(n):
            _innov_indices.append(_nameToIndex[n])
print(len(_innov_indices))

_position_indices = [_nameToIndex['_state.pos[0]'], _nameToIndex['_state.pos[1]']]

_project_root_dir = Path(_script_dir).parent.parent.resolve(())

def _set_zeros(data, iois):
    data[:, iois] = 0
    return data

def _select_indices(data, iois):
    return data[:,iois]

def _scale(data, model):
    return model.transform(data)

def _unscale(data, model):
    return model.inverse_transform(data)

timeIndices = []
timeIndicesNames = []
for i in range(len(_indexToName)):
    n = _indexToName[i]
    if 'uint64' in _indexToType[i]  and ('time_' in n or 'timestamp' or '_us' in n):
        timeIndices.append(i)
        timeIndicesNames.append(n)

iois = _state_gps_indices + _r_to_earth_indices+_pos_body_indices+_ang_rate_delayed_raw_indicies
_relevant_indices_only = [0, 3, 14, 17, 22]
_input_len = len(iois)
_preprocess = [(_select_indices, {'iois':iois})] # 
def preprocess(data):
    output = data
    for p, pargs in _preprocess:
        output = p(data, **pargs)
    return output

_unPreprocess = []
def unPreprocess(data):
    output = data
    for p, pargs in reversed(_unPreprocess):
        output = p(data, **pargs)
    return output
    pass
