import mmap
import os
import time
import json
import argparse
from pathlib import Path
from typing import Any
import torch
import multiprocessing as mp # Spawn threads for PX4 Mission control
from server.interface import SimulationInterface
import mavsdk
import asyncio
import subprocess
import copy
import numpy as np
import functools as ft
import traceback

import analysis.utils.datasetWrapper as aud
import analysis.utils.torchWrapper as aut
import analysis.utils.model as saum
import analysis.utils.checkpoint as sauc
import prep.utils.fileHandler as puf 
import auto.mission as am
import auto.plot_server as ap
import auto.utils.mission as aum
import prep.utils.logHandler as pul

import signal
import sys


# Check px4 directory environemnt variable
if os.environ.get('PX4_DIR') is None:
    exit('Please define $PX4_DIR env var to the location of PX4')
ENV_PX4_DIR = os.path.abspath(os.environ.get('PX4_DIR'))
if not os.path.isdir(ENV_PX4_DIR):
    exit('Specified $PX4_DIR is not a directory')



from importlib.machinery import SourceFileLoader
currentScriptDir = os.path.dirname(os.path.realpath(__file__))
projectRootDir = Path(currentScriptDir).parent.resolve()
projectSpecsDir = os.path.join(projectRootDir, 'specs')

readyQ = mp.Queue()

hold_atk = False
prev_atk = [0 for _ in range(10)]

def run_px4(px4_dir,sim_factor, mfile,delay):
    mission_setpoints = aum.read_mission_csv_file(mfile)
    envvar = os.environ.copy()
    envvar['HEADLESS']='1'
    envvar['PX4_SIM_SPEED_FACTOR']=str(sim_factor)
    envvar['TEST_ATTK']='1'
    pargs = {'env':envvar, 'cwd':px4_dir, 'stdout':subprocess.PIPE, 'stdin': subprocess.PIPE, 'stderr':subprocess.PIPE}
    asyncio.run(am.run_loop(['bash', 'run.bash'], pargs, mission_setpoints, readyQ=readyQ, delay=delay))

def write_values(server_mm, values):
    if len(values) == 0:
        meta = format(0, '016d')
        print('wrote', meta)
        server_mm.write(meta.encode())
        return
    payload = (','.join(['%.5f'%values[i] for i in range(10)]))
    meta = format(len(payload), '016d')
    print('wrote',meta+payload)
    server_mm.write((meta+payload).encode())

def serialize_gout(values, g_out, atk_idx, name, targetNames, nameToIndex):
    if name in targetNames:
        gout_idx = targetIndices.index(nameToIndex[name])
        print(g_out, gout_idx)
        if g_out is float:
            values[atk_idx] = g_out
        else:
            values[atk_idx] = g_out[gout_idx]

ready = False

logs = {}
logs['snapshots'] = []
logs['stats'] = {}
logs['stats']['pos_dev'] = []

output_dir = None
plot_client = None
written = False

def signal_handler(sig, frame):
    print('Exiting')
    if plot_client is not None:
        plot_client.close()
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

if __name__ == '__main__':
    # load a dummy log
    parser = argparse.ArgumentParser(
                        prog = 'Test if ekf client works',
                        description = 'Send log JSON to extracted EKF',
                        epilog = '')
    parser.add_argument('-cp', '--checkpoint', type=str, help="Directory with checkpoints")
    parser.add_argument('-o', '--output', type=str, help="Result output directory")
    parser.add_argument('-l', '--lookup', type=str, default='./index', help="Path to index json files")
    parser.add_argument('-sp', '--specDir', type=str, default=projectSpecsDir, help="Path to spec module")
    parser.add_argument('-sn', '--specName', type=str, default=None, help="Path to spec module")
    parser.add_argument('-mp', '--modelPath', type=str, default='', help="Path to the trained model")
    parser.add_argument('-m', '--mission', type=str, default='hold',
                    help='Mission file')
    parser.add_argument('-ora', '--oracle', action='store_true', help='Queries oracle for attack')
    parser.add_argument('-pl', '--plot', action='store_true', help='To send data to plotting server')
    parser.add_argument('-at', '--attackType', type=str, default='n', help='Type of attack to launch:'+
                        '\t"n" := normal/no attack\n'+
                        '\t"nc" := no correction\n'+
                        '\t"db" := directional bias\n')
    args = parser.parse_args()
    output_dir = args.output

    atk_duration = 0
    rest = False

    if args.plot:
        plot_client = ap.PlotClient()

    if args.attackType == 'n':
        hold_atk = True

    specs =  SourceFileLoader(args.specName, os.path.join(args.specDir, args.specName+'/'+args.specName + '.py')).load_module()

    indexToName, nameToIndex, indexToType = puf.loadLookUp(args.lookup)

    targetNames = ['_gps_buffer._buffer[0].pos[0]', "_gps_buffer._buffer[0].vel[0]"]
    targetIndices = []

    # Get the model
    cp = None
    netG = None
    cps = None
    if args.attackType == 'nc':
        print('Running Unbounded No Correction model')
        cp =  sauc.loadCheckpoint(args.checkpoint) # 
        netG = cp['model'].cpu()
    elif args.attackType == 'db':
        cp =  sauc.loadCheckpoint(args.checkpoint) # 
        netG = cp['model'].cpu()

    if ('nc' in args.attackType or 'db' in args.attackType) and 'target_indices' in cp:
        targetIndices = cp['target_indices']
        targetNames = cp['target_names']
        print(targetIndices)
    else:
        for tn in targetNames:
            targetIndices.append(nameToIndex[tn])
        targetIndices.sort()
    
    server_file_path = os.path.join(ENV_PX4_DIR, 'build/px4_sitl_default/tmp/rootfs/server.txt')
    client_file_path = os.path.join(ENV_PX4_DIR, 'build/px4_sitl_default/tmp/rootfs/client.txt')
    if not os.path.isfile(server_file_path):
        with open(server_file_path,"wb") as f:
            f.seek(1024*2)
            f.write(b"\0")
    if not os.path.isfile(client_file_path):
        with open(client_file_path,"wb") as f:
            f.seek(241*1024)
            f.write(b"\0")
    server_fd =  open(server_file_path, "r+b")
    client_fd =  open(client_file_path, "r+b")

    server_mm = mmap.mmap(server_fd.fileno(), 1024, access=mmap.ACCESS_WRITE, offset=0)
    client_mm = mmap.mmap(client_fd.fileno(), 240*1024, access=mmap.ACCESS_WRITE, offset=0)

    # Initialize the files
    # [(bytes):(name), (bytes):(name),...]
    # Format: [16:length, length:payload]
    server_initial_string = format(int(0), '016d')
    server_mm.write((server_initial_string + ','.join(['0.0' for _ in range(10)])).encode())
    client_mm.write((format(0, '016d')+'\n').encode())

    iter = 0

    adelay=0
    if args.mission == 'circle':
        adelay = 3

    px4_args = {'px4_dir':ENV_PX4_DIR,'sim_factor':1.0, 'mfile':'./specs/test_spec/mission/%s.csv'%(args.mission), 'delay':adelay}

    px4_proc = mp.Process(target=run_px4, kwargs=px4_args)
    px4_proc.start()
    si = SimulationInterface('localhost',12312)
    print("CONNECTED")

    goNorth = True
    
    normal_gps = None
    current_counter = -1
    try:
        with torch.no_grad():
            while True:
                log = {}
                counter = int(si._test_recv_ack())
                if counter < 0 or current_counter + 1 != counter:
                    raise Exception("Invalid counter, current counter is {cc} but recieved {c}".format(
                        cc=current_counter, c=counter)) 
                else:
                    current_counter += 1

                client_mm.seek(0)
                server_mm.seek(0)

                postf = None
                if not readyQ.empty():
                    postf = json.loads(client_mm.readline().decode())
                    print(postf['snapshot'].keys())
                    log['timestamp'] = postf['snapshot']['timestamp']
                    log['postf'] = postf['snapshot']['postf']

                    normal_gps_pos = postf['snapshot']['postf']['_gps_buffer']['_buffer'][0]['pos']
                    current_state_pos = postf['snapshot']['postf']['_state']['pos']
                    normal_gps_vel = postf['snapshot']['postf']['_gps_buffer']['_buffer'][0]['vel']
                    current_state_vel = postf['snapshot']['postf']['_state']['vel']
                    X = torch.from_numpy(
                        np.expand_dims(
                            pul.to_vec(postf['snapshot']['postf'], nameToIndex, 2020),
                            axis=0)
                        )
                    # print(X.shape)
                    g_out = None
                    if args.oracle:
                        g_out = [normal_gps_pos[0]-current_state_pos[0], normal_gps_vel[0] - current_state_vel[0]]
                        pass
                    elif not hold_atk:
                        if netG is not None:
                            g_in = specs.m1_preprocess_input(X).double()
                            print(g_in.shape)
                            g_out = torch.squeeze(netG(g_in))
                            g_out = g_out.tolist()
                        else:
                            g_out = [0 for _ in range(4)]

                    values = [float(0) for _ in range(10)]
                    if hold_atk:
                        values[0] = prev_atk[0]
                        values[1] = prev_atk[1]
                        values[3] = 0 # vel
                        values[4] = 0
                        g_out = prev_atk
                        pass
                    else:
                        iter += 1
                        if args.attackType == 'pco':
                            values[0] = 1 # pos
                            values[1] = 0
                            values[3] = 0 # vel
                            values[4] = 0
                        elif args.attackType == 'vco':
                            values[0] = 0 # pos
                            values[1] = 0
                            values[3] = 1 # vel
                            values[4] = 0
                        elif args.attackType == 'pro':
                            values[0] = np.random.uniform(-1, 1) # xpos
                            values[1] = 0
                            values[3] = 0 # xvel
                            values[4] = 0
                        elif args.attackType == 'pbf':
                            #values[0] = prev_atk[0] + 3/385 # xpos
                            values[0] = iter* 3/385 # For hold mission
                            values[1] = 0
                            values[3] = 0 # xvel
                            values[4] = 0
                        elif args.attackType == 'vro':
                            values[0] = 0 # xpos
                            values[1] = 0
                            values[3] = np.random.uniform(-1, 1) # xvel
                            values[4] = 0
                        elif args.attackType == 'vbf':
                            values[0] = 0 # xpos
                            values[1] = 0
                            values[3] = iter * 3/385 # xvel
                            values[4] = 0
                        elif args.attackType == 'co':
                            values[0] = 0.5 # xpos
                            values[1] = 0
                            values[3] = 0.5 # xvel
                            values[4] = 0
                        elif args.attackType == 'ro':
                            values[0] = np.random.uniform(-1, 1) # xpos
                            values[1] = 0
                            values[3] = np.random.uniform(-1, 1) # xvel
                            values[4] = 0
                        else:
                            serialize_gout(values, g_out, 0, '_gps_buffer._buffer[0].pos[0]', targetNames, nameToIndex)
                            serialize_gout(values, g_out, 1, '_gps_buffer._buffer[0].pos[1]', targetNames, nameToIndex)
                            #
                            serialize_gout(values, g_out, 3, '_gps_buffer._buffer[0].vel[0]', targetNames, nameToIndex)
                            serialize_gout(values, g_out, 4, '_gps_buffer._buffer[0].vel[1]', targetNames, nameToIndex)
                    log['out'] = g_out
                    write_values(server_mm, values)
                    prev_atk = values
                else:
                    write_values(server_mm, [])

                si._test_send_ack()
                print("sent")
                counter = int(si._test_recv_ack())
                if counter < 0 or current_counter + 1 != counter:
                    raise Exception("Invalid counter, current counter is {cc} but recieved {c}".format(
                        cc=current_counter, c=counter)) 
                else:
                    current_counter += 1
                print("recieved", counter)

                if not readyQ.empty():
                    client_mm.seek(0)
                    posth = json.loads(client_mm.readline().decode())
                    log['posth_a'] = posth['snapshot']['posth']

                    npos_dev = np.array(normal_gps_pos)[0] - np.array(postf['snapshot']['postf']['_state']['pos'][0])

                    print('\tatk_dur', atk_duration)
                    print('\tdeviation', npos_dev)
                    logs['stats']['pos_dev'].append(npos_dev)
                    gps_pos_innov_0 = posth['snapshot']['posth']['_gps_pos_innov'][0]
                    gps_vel_innov_0 = posth['snapshot']['posth']['_gps_vel_innov'][0]
                    print('\tinnov pos',gps_pos_innov_0)
                    print('\tinnov vel',gps_vel_innov_0)
                    print('\tGPS pos:', np.array(normal_gps_pos)[0])
                    print('\tState pos:', np.array(postf['snapshot']['postf']['_state']['pos'][0]))
                    logs['snapshots'].append(log)
                    if args.plot:
                        normal_gps_pos = postf['snapshot']['postf']['_gps_buffer']['_buffer'][0]['pos']
                        plot_client.gps_pos(normal_gps_pos)
                        plot_client.est_pos(postf['snapshot']['postf']['_state']['pos'])
                        plot_client.timestamp(postf['snapshot']['timestamp'])
                        plot_client.innov([gps_vel_innov_0, gps_pos_innov_0])
                        plot_client.send_data()
                si._test_send_ack()
                print("sent")
                print("------")
    except Exception as e:
        with open(args.output,'w') as f:
            json.dump(logs,f,indent=4)
        print(e)
        print('WRITTEN')
        written=True
        traceback.print_exc()
        px4_proc.terminate()
        px4_proc.join()
        exit("EXITING")
