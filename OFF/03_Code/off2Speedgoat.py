"""Run OFF against the Speedgoat real-time target."""

import os


import argparse
import random

from itertools import count
from pathlib import Path
import tempfile

import off.off_interface as offi
import off.ambient_corrector as amb_corr
import numpy as np
import logging
lg = logging.getLogger('off')

import socket
import struct
import matplotlib.pyplot as plt
import time
from TXRXRTS import UDPComms
import yaml

np.seterr(all='raise', under='ignore')
import warnings
warnings.filterwarnings('error', category=RuntimeWarning)
warnings.filterwarnings('ignore', message='.*underflow.*', category=RuntimeWarning)
import faulthandler; faulthandler.enable()
from bisect import bisect_right

from GridPowerTransmitter import RequestedPowerTransmitter

MAX_YAW = 60
DEFAULT_CONFIG = Path(__file__).resolve().parent / "config" / "off2speedgoat.yaml"
DEFAULT_AMBIENT_CONFIG_DIR = DEFAULT_CONFIG.parent


def parse_args():
    parser = argparse.ArgumentParser(description="Run OFF while communicating with a Speedgoat real-time simulator.")
    parser.add_argument("speedgoat_ip_pos", nargs="?", help="Speedgoat target IP. Kept for backwards compatibility.")
    parser.add_argument("scada_ip_pos", nargs="?", help="SCADA target IP. Kept for backwards compatibility.")
    parser.add_argument("--speedgoat-ip", default=None, help="Speedgoat target IP.")
    parser.add_argument("--scada-ip", default=None, help="SCADA target IP.",)
    parser.add_argument("--config", type=Path, default=DEFAULT_CONFIG, help="Path to the main OFF run YAML.")
    parser.add_argument("--ambient-config", type=Path, default=None, help="Optional YAML containing only the ambient block. Replaces the ambient block in --config.")
    parser.add_argument("--loop-forever", action="store_true", help="Keep running and load a random short ambient config when the current one ends.")
    parser.add_argument("--ambient-config-dir", type=Path, default=DEFAULT_AMBIENT_CONFIG_DIR, help="Directory containing ambient configs used by --loop-forever.")
    parser.add_argument("--random-ambient-prefix", default="short", help="Filename prefix for ambient configs picked by --loop-forever.")
    parser.add_argument("--random-seed", type=int, default=None, help="Optional seed for reproducible random ambient selection.")
    parser.add_argument("--mode", choices=("Prod", "Visual"), default="Prod", help="Runtime mode.")
    return parser.parse_args()


def read_yaml(path: Path) -> dict:
    path = path.expanduser().resolve()
    with path.open("r") as stream:
        data = yaml.safe_load(stream)

    if not isinstance(data, dict):
        raise ValueError(f"YAML file is not a mapping: {path}")
    return data


def extract_ambient_block(config: dict, source: Path) -> dict:
    ambient = config.get("ambient", config)
    if not isinstance(ambient, dict):
        raise ValueError(f"Ambient config is not a YAML mapping: {source}")
    if "flow_field" not in ambient:
        raise ValueError(f"Ambient config has no flow_field block: {source}")
    return ambient


def load_run_config(config_path: Path, ambient_config_path: Path | None = None) -> Path:
    config_path = config_path.expanduser().resolve()
    if ambient_config_path is None:
        return config_path

    ambient_config_path = ambient_config_path.expanduser().resolve()
    run_config = read_yaml(config_path)
    ambient_config = read_yaml(ambient_config_path)

    run_config["ambient"] = extract_ambient_block(ambient_config, ambient_config_path)

    merged_config = tempfile.NamedTemporaryFile(
        mode="w",
        suffix=".yaml",
        prefix=f"{config_path.stem}_with_ambient_",
        delete=False,
    )
    with merged_config:
        yaml.safe_dump(run_config, merged_config, sort_keys=False)

    return Path(merged_config.name)


def find_random_ambient_configs(config_dir: Path, prefix: str) -> list[Path]:
    config_dir = config_dir.expanduser().resolve()
    candidates = sorted(
        path for pattern in (f"{prefix}*.yaml", f"{prefix}*.yml")
        for path in config_dir.glob(pattern)
        if path.is_file()
    )
    if not candidates:
        raise FileNotFoundError(f"No ambient configs matching {prefix!r} found in {config_dir}")
    return candidates


def random_ambient_config(candidates: list[Path], rng: random.Random) -> Path:
    return rng.choice(candidates)


def replace_ambient_condition(off_interface: offi.OFFInterface, ambient_config_path: Path) -> dict:
    ambient_config = read_yaml(ambient_config_path)
    ambient = extract_ambient_block(ambient_config, ambient_config_path)
    flow_field = ambient["flow_field"]

    off_sim = off_interface.off_sim
    off_sim.settings_cor["ambient"] = flow_field
    states_name = off_sim.wind_farm.turbines[0].ambient_states.get_state_names()
    off_sim.ambient_corrector = amb_corr.AmbientCorrector(flow_field, off_sim.wind_farm, states_name)
    return flow_field


def apply_ambient_condition_at_time(off_interface: offi.OFFInterface, t: float) -> None:
    off_sim = off_interface.off_sim
    off_sim.ambient_corrector.update(t)
    for idx, turbine in enumerate(off_sim.wind_farm.turbines):
        off_sim.ambient_corrector(idx, turbine.ambient_states)


def ambient_condition_duration(flow_field: dict) -> float:
    duration = 0.0
    for key, values in flow_field.items():
        if not key.endswith("_t") or not isinstance(values, (list, tuple, np.ndarray)):
            continue
        if len(values) == 0:
            continue
        duration = max(duration, float(max(values)))

    if duration <= 0.0:
        raise ValueError("Ambient condition needs at least one positive *_t entry for --loop-forever.")
    return duration


def requested_power_at(flow_field: dict, t: float):
    power_t = flow_field.get("requested_power_t")
    power = flow_field.get("requested_power")
    if not power_t or not power:
        return None

    op_time_idx = bisect_right(power_t, t) - 1
    if op_time_idx < 0:
        return None
    return power[op_time_idx]


def main():
    args = parse_args()
    logging.basicConfig(filename='myapp.log', level=logging.INFO)
    rng = random.Random(args.random_seed)

    # setting up server with one port to one port communication 
    # IP addresses
    IP_address_speedgoat = args.speedgoat_ip or args.speedgoat_ip_pos or "172.19.3.43"
    scadaIP = args.scada_ip or args.scada_ip_pos or "172.19.3.220"
    
    # Ports
    python2simulink_port = 49160  # PC -> Speedgoat
    simulink2python_port = 49152  # Speedgoat -> PC

    rtsRX_port = 49152
    rtsTX_port = 49160

    pcRX_port = 49152
    pcTX_port = 49160

    mode = args.mode  # 'Visual' or 'Prod'

    udp_comm = UDPComms(remote_ip=IP_address_speedgoat, tx_port=rtsRX_port, rx_port=pcRX_port, send_interval=0.5)
    udp_comm.start()
    lg.info("Sockets created and bound to ports : %d (Simulink->Python) and %d (Python->Simulink)", simulink2python_port, pcRX_port)
    lg.info("")
    
    # Operator EndPoint
    op = RequestedPowerTransmitter(scadaIP, "9001")
    op.connect()

    random_ambient_candidates = None
    initial_ambient_config = args.ambient_config
    if args.loop_forever:
        random_ambient_candidates = find_random_ambient_configs(args.ambient_config_dir, args.random_ambient_prefix)
        if initial_ambient_config is None:
            initial_ambient_config = random_ambient_config(random_ambient_candidates, rng)
            lg.info("Initial random ambient config: %s", initial_ambient_config)

    file_name = load_run_config(args.config, initial_ambient_config)
    #print(f"OFF config: {file_name}")

    off_interface = offi.OFFInterface()
    off_interface.init_simulation_by_path(str(file_name))
    iteration = 0
    segment_start_time = off_interface.off_sim.settings_sim['time start']
    ambient_duration = ambient_condition_duration(off_interface.off_sim.settings_cor['ambient']) if args.loop_forever else None

    Nt = len(off_interface.off_sim.wind_farm.turbines) # number of turbines

    # intializing signals so that simulink and off can run simultaneously
    simulink_input_init_perturbine = np.array([8, 0]) # wind speed, wind direction (rad)
    simulink_input = np.array([simulink_input_init_perturbine for _ in off_interface.off_sim.wind_farm.turbines], dtype=np.float32)
    lg.info("initial simulink_input: %s", simulink_input)

    off_input_init_per_turbine = np.array([0, 0.5]) # yaw, ct
    off_input = np.zeros(2*Nt)
    lg.info("initial off_input: %s", off_input)

    ## updating turbine states so that both simulink and off can run at the same time
    # since all the initial states are the same this can be done this way but only for the initial step
    for turbine in off_interface.off_sim.wind_farm.turbines:
        turbine.turbine_states.update_states(ct=off_input_init_per_turbine[1], yaw=off_input_init_per_turbine[0])
    
    INTERVAL = off_interface.off_sim.settings_sim['time step'] # seconds
    next_tick = time.perf_counter() + INTERVAL

    time_start = off_interface.off_sim.settings_sim['time start']
    time_end = off_interface.off_sim.settings_sim['time end']
    time_step = off_interface.off_sim.settings_sim['time step']
    if args.loop_forever:
        time_iterator = (time_start + i * time_step for i in count())
    else:
        time_iterator = np.arange(time_start, time_end, time_step)

    for t in time_iterator:
        ambient_t = t - segment_start_time
        if args.loop_forever and ambient_t >= ambient_duration:
            ambient_config = random_ambient_config(random_ambient_candidates, rng)
            flow_field = replace_ambient_condition(off_interface, ambient_config)
            ambient_duration = ambient_condition_duration(flow_field)
            segment_start_time = t
            ambient_t = 0.0
            apply_ambient_condition_at_time(off_interface, ambient_t)
            lg.info("Loaded random ambient config: %s", ambient_config)
            print(f"Loaded random ambient config at t = {t}: {ambient_config}", flush=True)
        
        # First we read from the RTS the most up to date simulink data
        if udp_comm.get_recv_value() is not None:
            rts_tur_data = udp_comm.get_recv_value().copy()
            print("Ct, Yaw received at t = ", t , "\n", rts_tur_data)
        else:
            rts_tur_data = off_input
            
        #rts_tur_data[Nt:-1] = rts_tur_data[Nt:-1] * 180 / np.pi

        # update turbine states
        for turbine_index, turbine in enumerate(off_interface.off_sim.wind_farm.turbines):
            ct = max(min(1, rts_tur_data[turbine_index]), 0.00001)
            yaw = rts_tur_data[turbine_index + Nt]
            

            # We do a 'hotfix' here that prevents bugs regarding yaw offsets that floris cannot handle.
            # Namely, if yaw is out of the allowed range, we just set it to be example in the direction of the wind with very low Ct (so no wake generation happens)
            if (yaw < -MAX_YAW or yaw >= MAX_YAW):
                yaw = 0
                ct = 0.00001
            if ct < 0.025:
                ct = 0.00001

            turbine.turbine_states.update_states(ct=ct, yaw=yaw)

        # run off simulation step
        simulink_input = off_interface.off_sim.run_one_step(ambient_t)
        simulink_input = np.array(simulink_input, dtype=np.float32)

        # Transmit this data to speedgoat
        udp_comm.set_send_value(simulink_input.copy())
        print("sent to speedgoat at t = ", t , "\n", simulink_input)

        # Next, obtain requested power from grid operator and send to grid operator port
        requested_power = requested_power_at(off_interface.off_sim.settings_cor['ambient'], ambient_t)
        if requested_power is not None:
            op.tx_requested_power(t, requested_power)


        iteration += 1

        now = time.perf_counter()
        sleep_for = next_tick - now

        if sleep_for > 0:
            print(f"Sleep for {sleep_for}", flush=True)
            time.sleep(sleep_for)
            next_tick += INTERVAL
        else:
            missed_ticks = int((-sleep_for) // INTERVAL) + 1
            next_tick += missed_ticks * INTERVAL
            print(f"Sleep for 0.0; timing overrun by {-sleep_for}", flush=True)

    # make graphs for all 10 columns in visual data
    if mode == 'Visual':
        #save visual data as numpy array
        visual_data = np.array(visual_data)  # shape (time_steps, num_turbines, 10 features)
        np.save('visual_data_speedgoat.npy', visual_data)


if __name__ == "__main__":
    os.system('cls')
    main()
