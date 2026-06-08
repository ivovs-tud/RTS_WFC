/*
 * udp1_private.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "udp1".
 *
 * Model version              : 1.33
 * Simulink Coder version : 24.2 (R2024b) 21-Jun-2024
 * C++ source code generated on : Thu May  7 13:53:46 2026
 *
 * Target selection: speedgoat.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef udp1_private_h_
#define udp1_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "udp1.h"
#include "udp1_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"

extern real_T rt_powd_snf(real_T u0, real_T u1);
extern void udp1_MATLABFunction_Init(B_MATLABFunction_udp1_T *localB,
  DW_MATLABFunction_udp1_T *localDW);
extern void udp1_MATLABFunction(const real_T rtu_x_prev[8],
  B_MATLABFunction_udp1_T *localB, DW_MATLABFunction_udp1_T *localDW);

#endif                                 /* udp1_private_h_ */
