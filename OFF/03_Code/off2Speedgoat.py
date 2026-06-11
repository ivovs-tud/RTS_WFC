# the aim of this file is to test the implementation of the api TO connect the Off simulation with
# a flow of turbine states coming from an external source

import os
import sys

import off.off as off
import off.off_interface as offi
import numpy as np
import logging
lg = logging.getLogger('off')

import socket
import struct
import matplotlib.pyplot as plt
import time
from TXRXRTS import UDPComms

np.seterr(all='raise', under='ignore')
import warnings
warnings.filterwarnings('error', category=RuntimeWarning)
warnings.filterwarnings('ignore', message='.*underflow.*', category=RuntimeWarning)
import faulthandler; faulthandler.enable()
from bisect import bisect_right

from GridPowerTransmitter import RequestedPowerTransmitter

MAX_YAW = 60

def main():
    logging.basicConfig(filename='myapp.log', level=logging.INFO)
    
    # setting up server with one port to one port communication 
    # IP addresses
    if len(sys.argv) > 1:
        IP_address_speedgoat = sys.argv[1]  # Speedgoat target
    else:
        IP_address_speedgoat = "172.19.3.43"  # Speedgoat target
    
    IP_address_desk2 = "172.19.3.214"      
    IP_address_desk3 = "172.19.3.220"
    IP_address_PC = IP_address_desk2 # IP adress of the running PC
    localIP = "172.19.3.214"
    scadaIP = "172.19.3.220"

    # Ports
    python2simulink_port = 49160  # PC -> Speedgoat
    simulink2python_port = 49152  # Speedgoat -> PC

    rtsRX_port = 49152
    rtsTX_port = 49160

    pcRX_port = 49152
    pcTX_port = 49160

    mode = 'Prod'  # 'Visual' or 'Prod'

    udp_comm = UDPComms(remote_ip=IP_address_speedgoat, tx_port=rtsRX_port, rx_port=pcRX_port, send_interval=0.5)
    udp_comm.start()
    # lg.info("Sockets created and bound to ports : %d (Simulink->Python) and %d (Python->Simulink)", simulink2python_port, pcRX_port)
    lg.info("")
    
    # Operator EndPoint
    op = RequestedPowerTransmitter(scadaIP, "9001")
    op.connect()

    # get layout of wind farm from windfarm_information.yaml
    file_name = f'{off.OFF_PATH}\\02_Examples_and_Cases\\03_Cases\\windfarm_information_2x5.yaml'

    off_interface = offi.OFFInterface()
    off_interface.init_simulation_by_path(file_name)
    iteration = 0

    Nt = len(off_interface.off_sim.wind_farm.turbines) # number of turbines

    # intializing signals so that simulink and off can run simultaneously
    simulink_input_init_perturbine = np.array([8, 0]) # wind speed, wind direction (rad)
    simulink_input = np.array([simulink_input_init_perturbine for _ in off_interface.off_sim.wind_farm.turbines], dtype=np.float32)
    lg.info("initial simulink_input: %s", simulink_input)

    off_input_init_per_turbine = np.array([0, 0.5]) # yaw, ct
    off_input = np.zeros(2*Nt)
    lg.info("initial off_input: %s", off_input)

    

    #artifical multiplier to test speedgoat limit
    n = 1


    ## updating turbine states so that both simulink and off can run at the same time
    # since all the initial states are the same this can be done this way but only for the initial step
    for turbine in off_interface.off_sim.wind_farm.turbines:
        turbine.turbine_states.update_states(ct=off_input_init_per_turbine[1], yaw=off_input_init_per_turbine[0])
    
    INTERVAL = off_interface.off_sim.settings_sim['time step'] # seconds
    next_tick = time.perf_counter() + INTERVAL

    for t in np.arange(off_interface.off_sim.settings_sim['time start'],
                           off_interface.off_sim.settings_sim['time end'],
                           off_interface.off_sim.settings_sim['time step']):
        
        # First we read from the RTS the most up to date simulink data
        if udp_comm.get_recv_value() is not None:
            rts_tur_data = udp_comm.get_recv_value().copy()
            print("Ct, Yaw received at t = ", t , "\n", rts_tur_data)
        else:
            rts_tur_data = off_input
            
        rts_tur_data[Nt:-1] = rts_tur_data[Nt:-1] * 180 / np.pi
        #rts_tur_data[0:Nt] = np.array([0.6 for _ in range(Nt)])

        # update turbine states
        for turbine_index, turbine in enumerate(off_interface.off_sim.wind_farm.turbines):
            #rel_yaw = off_input[turbine_index, 0] - simulink_input[turbine_index, 2] * 180/np.pi
            #rel_yaw = max(min(50, rel_yaw), -50) # bounding yaw so that the comp doesnt fail
            ct = max(min(1, rts_tur_data[turbine_index]), 0.001)
            yaw = rts_tur_data[turbine_index + Nt]

            # We do a 'hotfix' here that prevents bugs regarding yaw offsets that floris cannot handle.
            # Namely, if yaw is out of the allowed range, we just set it to be example in the direction of the wind with very low Ct (so no wake generation happens)
            if (yaw < -MAX_YAW or yaw >= MAX_YAW):
                yaw = 0
                ct = 0.001

            turbine.turbine_states.update_states(ct=ct, yaw=yaw)

        # run off simulation step
        simulink_input = off_interface.off_sim.run_one_step(t)
        simulink_input = np.array(simulink_input, dtype=np.float32)

        # Transmit this data to speedgoat
        udp_comm.set_send_value(simulink_input.copy())
        print("sent to speedgoat at t = ", t , "\n", simulink_input)

        # Next, obtain requested power from grid operator and send to grid operator port
        op_time_idx = bisect_right(off_interface.off_sim.settings_cor['ambient']['requested_power_t'], t) - 1
        if op_time_idx >= 0:
            op.tx_requested_power(t, off_interface.off_sim.settings_cor['ambient']['requested_power'][op_time_idx])


        iteration += 1

        sleep_for = next_tick - time.perf_counter()
        print(f"Sleep for {sleep_for}", flush=True)
        
        if sleep_for > 0:
            time.sleep(sleep_for)
        next_tick += INTERVAL

    #py2sim_socket.close()
    # print("Simulation finished, Python process terminated.")
    

    # make graphs for all 10 columns in visual data
    if mode == 'Visual':
        #save visual data as numpy array
        visual_data = np.array(visual_data)  # shape (time_steps, num_turbines, 10 features)
        np.save('visual_data_speedgoat.npy', visual_data)


if __name__ == "__main__":
    os.system('cls')
    main()