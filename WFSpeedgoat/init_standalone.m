%% Set ambient conditions

ws_val = [11, 10, 10, 12];
ws_t = [0, 80, 120, 150];

%% Set power setpoint

P_set_val = [0.5, 0.6, 0.5];
P_set_t = [0, 100, 150];

%% Set yaw setpoints

yaw_set_val = [0];
yaw_set_t = [0];

%% Create timeseries

ws = timeseries(ws_val, ws_t);
P_set = timeseries(P_set_val, P_set_t);
yaw_set = timeseries(yaw_set_val, yaw_set_t);