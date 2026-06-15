%% Set initial value

% NOTE: For NREL5MW, greedy, 11 m/s, range [6, 24] rpm works, outside
% fails! <- This was resolved by the inverse
% NOTE: For NREL5MW, downregulation, 11 m/s, range [11, 24] rpm works,
% outside fails! <- Still the same even after fix!
rotor_speed_init = 12;  % In RPM | NOTE: This highly depends on the operating point and turbine type! 
rotor_speed_init = rotor_speed_init * (2 * pi) / 60;  % In rad/s

%% Set power setpoint

% P_set_val = [0.5, 0.6, 0.5];
% P_set_t = [0, 100, 150];

%% Set yaw setpoints

% yaw_set_val = [0];
% yaw_set_t = [0];

%% Set turbine parameters

air_density = 1.225;

turbine_name = 'NREL5MW';  % NREL5MW | IEA22MW

if strcmp(turbine_name, 'NREL5MW')
    rotor_diameter = 126;
    Cp_opt = 0.482;
    tsr_opt = 7.55;
    inertia = 4e6; %38677040.613; % Rotor Inertia
    gearbox_ratio = 97;
    generator_eff = 0.944;
    cut_in_wind_speed = 3.0;
    cut_out_wind_speed = 25.0;
    rated_wind_speed = 11.4;
    rated_rotor_speed = 12.1;  % In RPM
    min_rotor_speed_rads = 0.722;
    rated_power = 5E6;
    pitch_rate_deg = 10;  % In deg/s (from 0.1745 rad/s)
    brake_torque = 28116.2;  % FIXME: This is the high-speed brake torque, do I need to use the gearbox?
    yawing_rate = 5; % deg/s
    rated_torque = 31465000;
    max_gen_torque = 47402.91;
    cp_ct_file = 'Cp_Ct_IEA22MWRWT_github.csv';
    pitch_above_rated_file = 'pitch_above_rated_NREL5MW.csv';
    power_ss_file = 'power_ss_NREL5MW.csv';

elseif strcmp(turbine_name, 'IEA22MW')
    rotor_diameter = 284;
    Cp_opt = 0.482;  % FIXME: Not from paper
    tsr_opt = 9.153;
    inertia = 1.9E6;
    gearbox_ratio = 1;  % Direct drive
    generator_eff = 0.954;
    cut_in_wind_speed = 3.0;
    cut_out_wind_speed = 25.0;
    rated_wind_speed = 11.0;
    rated_rotor_speed = 6.77;  % In RPM | FIXME: There are conflicting values, 6.77 is reported at 11.0 m/s, rated wind speed
    min_rotor_speed_rads = 0.190;
    rated_power = 22E6;
    brake_torque = 28116.2;  % FIXME: Not in the report, this is from NREL
    pitch_rate_deg = 5;  % NOTE: in deg/s, FIXME: Made up value
    yawing_rate = 5; % deg/s
    rated_torque = 31465000;
    max_gen_torque = 30560000;
    % rated_gen_torque = 31465.0;
    cp_ct_file = 'Cp_Ct_IEA22MWRWT_github.csv';
    pitch_above_rated_file = 'pitch_ss_IEA22MW_report.csv';
    power_ss_file = 'power_ss_IEA22MW_hacw2_github.csv';
else
    error('Invalid turbine name supplied')
end

rated_rotor_speed_rads = rated_rotor_speed * (2 * pi) / 60;  % In rad/s
rotor_radius = rotor_diameter / 2;
brake_torque = rated_torque;
MIN_ROT_SPEED = 1e-3;
ROT_SPEED_MIN_TRANS = min_rotor_speed_rads;
ROT_SPEED_SP_DIFF = 0.1;
ROT_EMG_MAX_TOL = 1.15;

%% Set controller parameters

ctrl_mode = 1; % 1 | K_omega_sq, 2 | PI downregulation, 3 | ROSCO, 4 | Gain-scheduled H_infty

% ==== K_omega_sq ====

alpha_pitch_exp = 0;  % nan = 0 deg | 0 = no exponential smoothing | NOTE: Does cause a lot of chitter

% FIXME: I had a bug using 'rated_rotor_speed' instead of
% 'rated_rotor_speed_rads'
% different turbines/operating points, 'theory' does not seem to hold
K_omega_sq = 1/2 * (tsr_opt)^-3 * air_density * pi * (rotor_diameter / 2)^5 * Cp_opt / gearbox_ratio^3;  % NOTE: Correct one for NREL5MW
% K_omega_sq = 1/2 * (rated_rotor_speed_rads * (rotor_diameter / 2) / rated_wind_speed)^-3 * air_density * pi * (rotor_diameter / 2)^5 * Cp_opt; 
% K_omega_sq = 1E7;  % Manuel value for IEA22MW, does not seem to really work

% ==== PI downregulation ====

dr_mode = Simulink.Parameter(1);  % 1 | Max-omega, 2 | Constant-omega, 3 | Constant-TSR, 4 | Minimum Ct, 0 | Shutdown

K_p_gen = 1e6;  % 1E7
K_i_gen = 1e4;  % 1E5
K_p_pitch = 1;
K_i_pitch = 0;

% ==== ROSCO ====

% ==== Gain-scheduled H_infty ====

rotor_speed_ref_mode = 1;  % 1 | Steady-state lookup, 2 | Max-omega, 3 | Constant-TSR, 0 | Shutdown

% H_infity controller
A_k = 2E6;  % FIXME: Temporarily used as P gain
B_k = 1E4;  % FIXME: Temporarily used as I gain
C_k = 0;
D_k = 0;

K_p_pitch_gs = 0.1;
K_i_pitch_gs = 0;

%% Create timeseries

% ws = timeseries(ws_val, ws_t);
% P_set = timeseries(P_set_val, P_set_t);
% yaw_set = timeseries(yaw_set_val, yaw_set_t);

%% Load Cp and Ct functions

% Load table
T = readtable(cp_ct_file);

% Try to find relevant column names (case-insensitive, partial match)
names = lower(T.Properties.VariableNames);
findcol = @(pat) find(contains(names,lower(pat)),1);

col_tsr  = findcol('tsr');   if isempty(col_tsr), col_tsr = findcol('lambda'); end
col_pitch= findcol('pitch'); if isempty(col_pitch), col_pitch = findcol('beta'); end
col_cp   = findcol('cp');    if isempty(col_cp), error('Cp column not found'); end
col_ct   = findcol('ct');    if isempty(col_ct), error('Ct column not found'); end

tsr_all   = T{:,col_tsr};
pitch_all = T{:,col_pitch};
Cp_all    = T{:,col_cp};
Ct_all    = T{:,col_ct};

% Unique sorted vectors
tsr_vec   = unique(tsr_all);
pitch_vec = unique(pitch_all);
tsr_vec   = sort(tsr_vec(:));
pitch_vec = sort(pitch_vec(:));

% Create matrices: rows = tsr, cols = pitch
% Use accumarray with subscripts mapping to grid indices (handles repeated entries by mean)
[~,~,i_tsr]   = unique(tsr_all);
[~,~,i_pitch] = unique(pitch_all);
subs = [i_tsr, i_pitch];

Cp_mat = nan(numel(tsr_vec), numel(pitch_vec));
Ct_mat = nan(size(Cp_mat));

% Fill using accumarray to compute mean where duplicates exist
Cp_mean = accumarray(subs, Cp_all, [numel(tsr_vec), numel(pitch_vec)], @mean, NaN);
Ct_mean = accumarray(subs, Ct_all, [numel(tsr_vec), numel(pitch_vec)], @mean, NaN);

Cp_mat(:,:) = Cp_mean;
Ct_mat(:,:) = Ct_mean;

Cp_mat(isnan(Cp_mat)) = 0;
Ct_mat(isnan(Ct_mat)) = 0;

% Create gridded interpolants: input order (tsr, pitch) | Only for
% verification
Cp_func = griddedInterpolant({tsr_vec, pitch_vec}, Cp_mat, 'linear', 'nearest');
Ct_func = griddedInterpolant({tsr_vec, pitch_vec}, Ct_mat, 'linear', 'nearest');

%% Load the blade-pitch lookup table

% Load table
T = readtable(pitch_above_rated_file);

% Try to find relevant column names (case-insensitive, partial match)
names = lower(T.Properties.VariableNames);
findcol = @(pat) find(contains(names,lower(pat)),1);

col_u = findcol('u');
col_pitch = findcol('pitch');

u_all   = T{:, col_u};
pitch_all = T{:, col_pitch};

% Create gridded interpolants based on u | Only for
% verification
pitch_func = griddedInterpolant(u_all, pitch_all, 'linear', 'nearest');

%% Load steady-state power lookup table

% Load table
T = readtable(power_ss_file);

% Try to find relevant column names (case-insensitive, partial match)
names = lower(T.Properties.VariableNames);
findcol = @(pat) find(contains(names,lower(pat)),1);

col_u = findcol('u');
col_P = findcol('P_ss');

u_P_all   = T{:, col_u};
P_all = T{:, col_P};

% Create gridded interpolants based on u | Only for
% verification
power_func = griddedInterpolant(u_P_all, P_all, 'linear', 'nearest');


%% Calculate the steady-state rotor speed lookup

rotor_speed_all = [0, rated_rotor_speed];
u_rotor_speed_all = [cut_in_wind_speed, rated_wind_speed];

%% Open Simulink file

% model_path = 'model_wt';
% 
% % Ensure file is on path or give full path to the .slx/.mdl
% if ~bdIsLoaded(model_path)
%     if exist([model_path,'.slx'],'file') || exist([model_path,'.mdl'],'file')
%         load_system(model_path);
%     else
%         error('Model file %s.slx/.mdl not found on MATLAB path.', model_path);
%     end
% end

% NOTE: You must open the model 'model_wt.slx' manually, as MATLAB
% otherwise keeps resetting the window on running this script, which is
% insanely annonying.

%% Print all referenced variables

% load_system(model_path);          % loads model (no GUI change)
% 
% % Get all referenced variables
% vars = Simulink.findVars(model_path);
% 
% % Filter for variables that come from the base workspace
% isBase = strcmp({vars.Source}, 'base workspace');
% baseVars = vars(isBase);
% 
% % Display names (and source) — adjust output as desired
% if isempty(baseVars)
%     disp('No variables referenced from base workspace.');
% else
%     fprintf('Variables referenced from base workspace:\n');
%     for k = 1:numel(baseVars)
%         fprintf('  %s\n', baseVars(k).Name);
%     end
% end