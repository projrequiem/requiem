#!/usr/bin/env python3
import asyncio
import signal
import numpy as np
import subprocess
import os
import argparse
import sys
import auto.utils.mission as um
import auto.utils.data as ud
from auto.utils.px4 import PX4Proc

from mavsdk import System
from mavsdk.offboard import (OffboardError, PositionNedYaw, VelocityNedYaw, VelocityBodyYawspeed)
from mavsdk.action import ActionError

velpos = [[0,0,0,0,0,0]]
heading = [0]
angvel = [[0,0,0]]
pvlock = asyncio.Lock()
hlock = asyncio.Lock()
avlock = asyncio.Lock()
px4 = None
output_path = './'

async def run_loop(command, pargs, sp, loop_len=1, readyQ=None, delay=0):
    global px4, velpos, heading, angvel
    for i in range(loop_len):
        print('Run count %d'%i)
        px4 = PX4Proc(command, pargs)
        px4.run()
        print('Generating mission')
        await run(sp, readyQ, delay)
        px4.shutdown()
        await asyncio.sleep(5)
    print('Finished loop')

# Gracefully exit px4
def signal_handler(sig, frame):
    global PX4PROC
    if px4 is not None:
        px4.shutdown()
    else:
        print('Ending before PX4PROC started')
    exit()

signal.signal(signal.SIGINT, signal_handler)

async def record_velpos(drone):
    global velpos, pvlock
    async for odom in drone.telemetry.position_velocity_ned():
        async with pvlock:
            pos = [odom.position.north_m, odom.position.east_m, odom.position.down_m]
            vel = [odom.velocity.north_m_s, odom.velocity.east_m_s, odom.velocity.down_m_s]
            velpos.append(vel+pos)

async def record_heading(drone):
    global heading, hlock
    async for odom in drone.telemetry.heading():
        async with hlock:
            heading.append(odom.heading_deg)

async def record_angvel(drone):
    global angvel, avlock
    async for odom in drone.telemetry.attitude_angular_velocity_body():
        rpy = None
        async with avlock:
            rpy = [odom.roll_rad_s, odom.pitch_rad_s, odom.yaw_rad_s]
            angvel.append(rpy)

async def position_checkpoint_status(drone, pn, pe, pd, yaw):
    global velpos, heading, pvlock
    sp = np.array([pn, pe, pd])
    cp = None
    h = None
    await drone.offboard.set_position_ned(PositionNedYaw(pn, pe, pd, yaw))
    async with pvlock:
        cp = velpos[-1][-3:]
    async with hlock:
        h = heading[-1]
    print("set checkpoint: {pn}, {pe}, {pd}, {yaw}".format(pn=pn, pe=pe, pd=pd, yaw=yaw))

    while True:
        position_reached, pdiff = um.reached_checkpoint(cp, sp, 0.3)
        heading_reached, hdiff = um.reached_checkpoint(h, yaw, 1, 360)
        async with pvlock:
            cp = velpos[-1][-3:]
        async with hlock:
            h = heading[-1]
        sys.stdout.write('\r')
        sys.stdout.write("Position: %s, %s\tYaw: %s, %s"%(str(np.around(cp, decimals=2)), str(pdiff), str(np.around(h,decimals=2)), str(hdiff) ) )
        sys.stdout.flush()
        if position_reached and heading_reached:
            sys.stdout.write("Finished Position: %s, %s\tYaw: %s, %s"%(str(np.around(cp, decimals=2)), str(pdiff), str(np.around(h,decimals=2)), str(hdiff) ) )
            sys.stdout.flush()
            break
        await asyncio.sleep(1)
    print('')


async def velocity_checkpoint_status(drone, n, e, d, y):
    global velpos, pvlock, avlock
    sp = np.array([n, e, d])
    cp = None
    h = None
    await drone.offboard.set_velocity_ned(VelocityNedYaw(n, e, d, y))
    async with pvlock:
        cp = velpos[-1][:3]
    async with avlock:
        h = angvel[-1][-1]*180/np.pi # convert radians to degrees

    while not (um.reached_checkpoint(cp, sp, 0.3) or um.reached_checkpoint(y, h, 0.3)):
        async with pvlock:
            cp = velpos[-1][:3]
        async with hlock:
            h = angvel[-1][-1]*180/np.pi # convert radians to degrees
        print("Vel (m/s): %s , %s\tYaw (Deg/s): %s , %s"%(str(cp), str(np.linalg.norm(cp - sp), str(h), str(np.linalg.norm(y-h)))) )
        await asyncio.sleep(1)



async def run(sp, readyQ=None, delay=0):
    print('Running Script')
    """ Does Ofhfboard control using position NED coordinates. """

    drone = System()
    await drone.connect(system_address="udp://:14540")

    print("Waiting for drone to connect...")
    async for state in drone.core.connection_state():
        if state.is_connected:
            print(f"-- Connected to drone!")
            break

    print("Waiting for drone to have a global position estimate...")
    async for health in drone.telemetry.health():
        if health.is_global_position_ok and health.is_home_position_ok:
            print("-- Global position estimate OK")
            break
    print("Setting Parameters for Offboard Control")
    await drone.param.set_param_int("NAV_DLL_ACT", 0)
    await drone.param.set_param_int("NAV_RCL_ACT", 0)
    await drone.param.set_param_int("COM_RCL_EXCEPT", 4)

    asyncio.ensure_future(record_velpos(drone))
    asyncio.ensure_future(record_heading(drone))
    asyncio.ensure_future(record_angvel(drone))
            
    await asyncio.sleep(3)

    print("-- Arming")
    for i in range(10):
        try:
            await drone.action.arm()
            break
        except ActionError as error:
            print('Failed to arm, trying again')
            await asyncio.sleep(10)


    print("-- Setting initial setpoint")
    await drone.offboard.set_position_ned(PositionNedYaw(0.0, 0.0, 0.0, 0.0))

    print("-- Starting offboard")
    try:
        await drone.offboard.start()
    except OffboardError as error:
        print(f"Starting offboard mode failed with error code: {error._result.result}")
        print("-- Disarming")
        await drone.action.disarm()
        return

    if delay == 0:
        await position_checkpoint_status(drone, 0, 0, -10, 0)
        await position_checkpoint_status(drone, 10, 10, -10, 0)
        await asyncio.sleep(1)
    await position_checkpoint_status(drone, 0, 0, -10, 0)

    if delay == 0:
        if readyQ is not None:
            readyQ.put(True)

    # Run mission checkpoints
    delayed = False
    for p in sp: 
        if len(p) > 5:
            await drone.offboard.set_velocity_body(
                VelocityBodyYawspeed(p[5], 0.0, 0.0, p[6]))
            if delay != 0 and not delayed:
                await asyncio.sleep(delay)
                if readyQ is not None:
                    readyQ.put(True)
                delayed = True
                
            await asyncio.sleep(p[4])
        else:
            await position_checkpoint_status(drone, p[0], p[1], p[2], p[3])
            if len(p) > 4:
                if delay != 0 and not delayed:
                    await asyncio.sleep(delay)
                    if readyQ is not None:
                        readyQ.put(True)
                    delayed = True
                await asyncio.sleep(p[4])

    print("-- Stopping offboard")
    try:
        await drone.offboard.stop()
    except OffboardError as error:
        print(f"Stopping offboard mode failed with error code: {error._result.result}")



if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Collect data')
    parser.add_argument('-d', '--px4_dir', type=str, default='./',
                    help='Checks directory for server config (i.e., the argument values)')
    parser.add_argument('-m', '--mission', type=str, default='./specs/test_spec/mission/hold.csv',
                    help='Mission file')
    parser.add_argument('-f', '--factor', type=float, default=1,
                    help='Simulation speed factor')
    parser.add_argument('-t', '--test', action='store_true',
                    help='Mission file')
    args = parser.parse_args()

    mission_setpoints = um.read_mission_csv_file(args.mission)


    px4_run_script = os.path.join(args.px4_dir, 'run.bash')

    envvar = os.environ.copy()
    envvar['HEADLESS']='1'
    envvar['PX4_SIM_SPEED_FACTOR']=str(args.factor)
    if args.test:
        envvar['TEST_ATTK']='1'
    else:
        envvar['TEST_ATTK']='0'
    pargs = {'env':envvar, 'cwd':args.px4_dir, 'stdout':subprocess.PIPE, 'stdin': subprocess.PIPE, 'stderr':subprocess.PIPE}
    asyncio.run(run_loop(['bash', 'run.bash'], pargs, mission_setpoints))