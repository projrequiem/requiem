
import os
import json
import numpy as np
import joblib
from pathlib import Path
import torch

_VERSION = 0.1
_NAME = 'estimator_spec'

# For training estimator surrogate models 

tau = 0.4
target_func = 'h'

_script_dir = os.path.realpath(os.path.dirname(__file__))

# Required
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

def _extract_state_gps_idx_n(i2n):
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


_state_gps_indices, _state_gps_names = _extract_state_gps_idx_n(_indexToName)


_project_root_dir = Path(_script_dir).parent.parent.resolve(())

timeIndices = []
timeIndicesNames = []
for i in range(len(_indexToName)):
    n = _indexToName[i]
    if 'uint64' in _indexToType[i]  and ('time_' in n or 'timestamp' or '_us' in n):
        timeIndices.append(i)
        timeIndicesNames.append(n)


def _extract_state_gps_idx_n(i2n):
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
def _get_ang_rate_delayed_raw_idx_n(n2i):
    output = []
    name_output = []
    for i in range(3):
        output.append(n2i['_ang_rate_delayed_raw[{}]'.format(i)])
        name_output.append('_ang_rate_delayed_raw[{}]'.format(i))
    return output, name_output
def _get_r_to_earth_idx_n(n2i):
    output = []
    names = []
    for i in range(9):
        names.append('_R_to_earth[{}]'.format(i))
        output.append(n2i['_R_to_earth[{}]'.format(i)])
    return output, names
def _get_pos_body_idx_n(n2i):
    output = []
    names = []
    for i in range(3):
        names.append('_params.imu_pos_body[{}]'.format(i))
        names.append('_params.gps_pos_body[{}]'.format(i))
        output.append(n2i['_params.imu_pos_body[{}]'.format(i)])
        output.append(n2i['_params.gps_pos_body[{}]'.format(i)])
    return output, names

def _get_gps_lateral_velpos_innov_names(n2i):
    output = []
    for i in range(2):
        output.append('_gps_vel_innov[%d]'%i)
    for i in range(2):
        output.append('_gps_vel_innov_var[%d]'%i)
    for i in range(2):
        output.append('_gps_pos_innov[%d]'%i)
    for i in range(2):
        output.append('_gps_pos_innov_var[%d]'%i)
    idx = []
    for n in output:
        idx.append(n2i[n])
    return idx, output

def _only_north_velpos_innov(n2i):
    output = []
    for i in range(1):
        output.append('_gps_vel_innov[%d]'%i)
        output.append('_gps_pos_innov[%d]'%i)
    idx = []
    for n in output:
        idx.append(n2i[n])
    return idx, output

def _get_state_q(n2i):
    name = []
    idx = []
    for i in range(4):
        name.append('_state.quat_nominal[%d]'%i)
    for n in name:
        idx.append(n2i[n])
    return idx, name

def _get_velpos(n2i):
    name = []
    idx = []
    for i in range(2):
        name.append('_gps_buffer._buffer[0].pos[%d]'%i)
        name.append('_gps_buffer._buffer[0].vel[%d]'%i)
        name.append('_state.vel[%d]'%i)
        name.append('_state.pos[%d]'%i)
    for n in name:
        idx.append(n2i[n])
    return idx, name

_state_gps_indices, _state_gps_names = _extract_state_gps_idx_n(_indexToName)
_ang_rate_delayed_raw_indicies, _ang_rate_delayed_raw_names = _get_ang_rate_delayed_raw_idx_n(_nameToIndex)

_r_to_earth_indices,_r_to_earth_names = _get_r_to_earth_idx_n(_nameToIndex)
_pos_body_indices, _pos_body_names = _get_pos_body_idx_n(_nameToIndex)
_gps_lateral_velpos_innov_idx, _gps_lateral_velpos_innov_names = _get_gps_lateral_velpos_innov_names(_nameToIndex)
_q_idx, _q_name = _get_state_q(_nameToIndex)
_velpos_idx, _velpos_name = _get_velpos(_nameToIndex)
_north_velpos_idx, _north_velpos_name = _only_north_velpos_innov(_nameToIndex)

###############################################################################################
# Method 1
###############################################################################################
m1_noise_names = None
m1_noise_idx = None

m1_input_names = None
m1_input_idx = None

m1_output_idx = None
m1_output_names = None

m1_input_name_to_idx = None
m1_output_name_to_idx = None
res_m1_input_names = None
res_m1_input_idx = None

m2_output_idx = None
m2_output_names = None
m2_output_name_to_idx = None

m2b_output_idx = None
m2b_output_names = None
m2b_output_name_to_idx = None

def m1_init():
    global res_m1_input_names
    global m1_noise_names, m1_noise_idx
    global m1_input_names, m1_input_idx, m1_input_name_to_idx
    global m1_output_names, m1_output_idx 
    global res_m1_input_idx
    m1_noise_idx = []
    m1_input_idx = []
    m1_output_idx = []
    m1_output_names = []
    res_m1_input_idx = []
    m1_noise_names = _state_gps_names
    m1_input_name_to_idx = {}
    m1_output_name_to_idx = {}

    for i in range(2):
        m1_output_names.append('_state.vel[%d]'%i) 
        m1_output_names.append('_state.pos[%d]'%i) 

    for n in m1_noise_names:
        m1_noise_idx.append(_nameToIndex[n])

    res_m1_input_names = _state_gps_names + _r_to_earth_names + _pos_body_names + _ang_rate_delayed_raw_names
    m1_input_names = res_m1_input_names + _gps_lateral_velpos_innov_names

    for idx, n in enumerate(m1_input_names):
        m1_input_name_to_idx[n] = idx
        m1_input_idx.append(_nameToIndex[n])
    for idx, n in enumerate(m1_output_names):
        m1_output_name_to_idx[n] = idx
        m1_output_idx.append(_nameToIndex[n])

    for idx, n in enumerate(res_m1_input_names):
        res_m1_input_idx.append(_nameToIndex[n])

def m2_init():
    global m2_output_idx, m2_output_name_to_idx, m2_output_names
    m2_output_names = []
    m2_output_idx = []
    m2_output_name_to_idx = {}

    if  m1_input_idx is None:
        m1_init()

    for i in range(2):
        m2_output_names.append('_state.vel[%d]'%i) 

    for idx, n in enumerate(m2_output_names):
        m2_output_name_to_idx[n] = idx
        m2_output_idx.append(_nameToIndex[n])

def m2b_init():
    global m2b_output_idx, m2b_output_name_to_idx, m2b_output_names
    m2b_output_names = []
    m2b_output_idx = []
    m2b_output_name_to_idx = {}

    if  m1_input_idx is None:
        m1_init()

    for i in range(2):
        m2b_output_names.append('_state.pos[%d]'%i) 

    for idx, n in enumerate(m2b_output_names):
        m2b_output_name_to_idx[n] = idx
        m2b_output_idx.append(_nameToIndex[n])


# Preprocessing method 1
# inputNames:
#   state: _state.quat, _state.vel, _state.pos, _state.delta_ang_bias, _state.delta_vel_bias
#   innov: _gps_buffer._buffer[0].pos, _gps_buffer._buffer[0].vel 
#   sensor(gps): _gps_buffer._buffer[0].pos, _gps_buffer._buffer[0].vel
# outputNames:
#   _state.vel, _state.pos
def m1_preprocess(X, Y):
    global  res_m1_input_idx, m1_input_idx 
    # X := postf
    # Y := posth
    if  m1_input_idx is None:
        m1_init()
    input = torch.cat((X[:,res_m1_input_idx], Y[:,_gps_lateral_velpos_innov_idx]), dim=1)
    label = Y[:, m1_output_idx]
    return input, label 

# Only velocity
def m2_preprocess(X, Y):
    global  res_m1_input_idx, m1_input_idx, m2_output_idx
    # X := postf
    # Y := posth
    if  m2_output_idx is None:
        m2_init()
    input = torch.cat((X[:,res_m1_input_idx], Y[:,_gps_lateral_velpos_innov_idx]), dim=1)
    label = Y[:, m2_output_idx]
    return input, label 

def m2_preprocess_output(Y):
    global  res_m1_input_idx, m1_input_idx, m2_output_idx
    # X := postf
    # Y := posth
    if  m2_output_idx is None:
        m2_init()
    label = Y[:, m2_output_idx]
    return label 

# Only position
def m2b_preprocess(X, Y):
    global  res_m1_input_idx, m1_input_idx, m2b_output_idx
    # X := postf
    # Y := posth
    if  m2b_output_idx is None:
        m2b_init()
    input = torch.cat((X[:,res_m1_input_idx], Y[:,_gps_lateral_velpos_innov_idx]), dim=1)
    label = Y[:, m2b_output_idx]
    return input, label 

def m2b_preprocess_output(Y):
    global  res_m1_input_idx, m1_input_idx, m2b_output_idx
    # X := postf
    # Y := posth
    if  m2b_output_idx is None:
        m2b_init()
    label = Y[:, m2b_output_idx]
    return label 