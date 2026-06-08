#ifndef _RTE_WTURBINES_PARAMETERS_H
#define _RTE_WTURBINES_PARAMETERS_H
#include "rtwtypes.h"
#include "SegmentInfo.hpp"
#include "multiword_types.h"
#include "wturbines_types.h"

struct RTE_Param_Service_T {
  real_T A_k;
  real_T B_k;
  real_T C_k;
  real_T Cp_mat[400];
  real_T Cp_opt;
  real_T Ct_mat[400];
  real_T K_i_gen;
  real_T K_i_pitch;
  real_T K_i_pitch_gs;
  real_T K_omega_sq;
  real_T K_p_gen;
  real_T K_p_pitch;
  real_T K_p_pitch_gs;
  real_T MIN_ROT_SPEED;
  real_T Nt;
  real_T ROT_EMG_MAX_TOL;
  real_T ROT_SPEED_MIN_TRANS;
  real_T ROT_SPEED_SP_DIFF;
  real_T air_density;
  real_T alpha_pitch_exp;
  real_T brake_torque;
  real_T cut_in_wind_speed;
  real_T cut_out_wind_speed;
  real_T dr_mode;
  real_T gearbox_ratio;
  real_T generator_eff;
  real_T inertia;
  real_T max_gen_torque;
  real_T pitch_all[23];
  real_T pitch_rate_deg;
  real_T pitch_vec[20];
  real_T rated_power;
  real_T rated_rotor_speed;
  real_T rated_rotor_speed_rads;
  real_T rated_torque;
  real_T rotor_radius;
  real_T rotor_speed_all[2];
  real_T rotor_speed_ref_mode;
  real_T tsr_opt;
  real_T tsr_vec[20];
  real_T turbineDataBytes;
  real_T u_all[23];
  real_T u_rotor_speed_all[2];
  real_T yawing_rate;
};

extern RTE_Param_Service_T RTE_Param_Service;
extern RTE_Param_Service_T *RTE_Param_Service_ptr;
real_T* get_A_k(void);
real_T* get_B_k(void);
real_T* get_C_k(void);
real_T* get_Cp_mat(void);
real_T* get_Cp_opt(void);
real_T* get_Ct_mat(void);
real_T* get_K_i_gen(void);
real_T* get_K_i_pitch(void);
real_T* get_K_i_pitch_gs(void);
real_T* get_K_omega_sq(void);
real_T* get_K_p_gen(void);
real_T* get_K_p_pitch(void);
real_T* get_K_p_pitch_gs(void);
real_T* get_MIN_ROT_SPEED(void);
real_T* get_Nt(void);
real_T* get_ROT_EMG_MAX_TOL(void);
real_T* get_ROT_SPEED_MIN_TRANS(void);
real_T* get_ROT_SPEED_SP_DIFF(void);
real_T* get_air_density(void);
real_T* get_alpha_pitch_exp(void);
real_T* get_brake_torque(void);
real_T* get_cut_in_wind_speed(void);
real_T* get_cut_out_wind_speed(void);
real_T* get_dr_mode(void);
real_T* get_gearbox_ratio(void);
real_T* get_generator_eff(void);
real_T* get_inertia(void);
real_T* get_max_gen_torque(void);
real_T* get_pitch_all(void);
real_T* get_pitch_rate_deg(void);
real_T* get_pitch_vec(void);
real_T* get_rated_power(void);
real_T* get_rated_rotor_speed(void);
real_T* get_rated_rotor_speed_rads(void);
real_T* get_rated_torque(void);
real_T* get_rotor_radius(void);
real_T* get_rotor_speed_all(void);
real_T* get_rotor_speed_ref_mode(void);
real_T* get_tsr_opt(void);
real_T* get_tsr_vec(void);
real_T* get_turbineDataBytes(void);
real_T* get_u_all(void);
real_T* get_u_rotor_speed_all(void);
real_T* get_yawing_rate(void);
namespace slrealtime
{
  SegmentVector &getSegmentVector(void);
}                                      // slrealtime

#endif
