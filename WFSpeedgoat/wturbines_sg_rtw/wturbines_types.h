/*
 * wturbines_types.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "wturbines".
 *
 * Model version              : 1.214
 * Simulink Coder version : 24.2 (R2024b) 21-Jun-2024
 * C++ source code generated on : Fri Jun  5 16:22:00 2026
 *
 * Target selection: speedgoat.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef wturbines_types_h_
#define wturbines_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_op_mode_
#define DEFINED_TYPEDEF_FOR_op_mode_

typedef enum {
  op_mode_None = 0,                    /* Default value */
  op_mode_parked,
  op_mode_starting_up,
  op_mode_power_production,
  op_mode_shutting_down,
  op_mode_emergency_stop
} op_mode;

#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_wturbines_T RT_MODEL_wturbines_T;

#endif                                 /* wturbines_types_h_ */
