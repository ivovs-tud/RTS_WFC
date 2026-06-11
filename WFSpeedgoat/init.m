clear all;

%% Contants
Nt = 9;        % Number of Turbines in Simulation


%% Networking Definitions
% IP Addresses
localIP = '172.19.3.42';        % IP address of the RTS
pcIP    = '172.19.3.202';       % IP address of the PC running the Flowfield simulation
plcIP   = '172.19.3.210';       % IP address of the PLC running the IEC61850 Server


% UDP/TCP ports
pcTXport = '49160';             % UDP port used by PC to transmit flowfield data to RTS
pcRXport = '49152';             % UDP port used by PC to receive turbine operational data

rtsTXFFport = '49160';          % UDP port used by RTS to transmit turbine data to PC
rtsRXFFport = '49152';          % UDP port used by RTS to receive flowfield data from PC

plcTXport = '11000';            % UDP port used by PLC to transmit turbine cmd_data to RTS
plcRXport = '11001';            % UDP port used by PLC to receive turbine op_data data from RTS

rtsTXIECport = '10000';         % UDP port used by RTS to transmit turbine op_data to PLC
rtsRXIECport = '11000';         % UDP port used by RTS to receive turbine cmd_data to PLC



%% Data Structures Definitions
TurbineDataDef
TurbineCmdDef


%% Simulation Constants
Ts_tur      = Simulink.Parameter(0.01);      % Sample frequency of the turbine simulation
Ts_FF       = Simulink.Parameter(0.5);      % Sample frequency at which flowfield information is shared
Ts_IEC      = Simulink.Parameter(0.25);      % Sample frequency at which RTS <-> PLC communication occurs

%% Turbine Param Initialization
initialize_turbine_parameters