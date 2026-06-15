/*
 * wturbines_types.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "wturbines".
 *
 * Model version              : 1.306
 * Simulink Coder version : 24.2 (R2024b) 21-Jun-2024
 * C++ source code generated on : Mon Jun 15 21:11:38 2026
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

#ifndef DEFINED_TYPEDEF_FOR_loggingData_
#define DEFINED_TYPEDEF_FOR_loggingData_

struct loggingData
{
  real_T Cp;
  real_T Ct;
  real_T GenSpd;
  op_mode OpMode;
  real_T OrientationSpt;
  real_T Pitch;
  real_T PitchSpt;
  real_T RotSpd;
  uint8_T eCtrlMode;
  real_T TBrake;
  real_T TGen;
  real_T Ta;
  real_T WsEff;
  real_T YawTrue;
  real_T HorWdSpd;
  real_T HorWdDir;
  boolean_T bEnable;
  boolean_T bStop;
  real_T WSpt;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_loggingDataVectors_
#define DEFINED_TYPEDEF_FOR_loggingDataVectors_

struct loggingDataVectors
{
  real_T Cp[9];
  real_T Ct[9];
  real_T GenSpd[9];
  op_mode OpMode[9];
  real_T OrientationSpt[9];
  real_T Pitch[9];
  real_T PitchSpt[9];
  real_T RotSpd[9];
  int32_T eCtrlMode[9];
  real_T TBrake[9];
  real_T TGen[9];
  real_T Ta[9];
  real_T WsEff[9];
  real_T YawTrue[9];
  real_T HorWdSpd[9];
  real_T HorWdDir[9];
  boolean_T bEnable[9];
  boolean_T bStop[9];
  real_T WSpt[9];
};

#endif

#ifndef struct_cell_wrap_wturbines_T
#define struct_cell_wrap_wturbines_T

struct cell_wrap_wturbines_T
{
  uint32_T f1[8];
};

#endif                                 /* struct_cell_wrap_wturbines_T */

#ifndef struct_dsp_simulink_MovingAverage_wt_T
#define struct_dsp_simulink_MovingAverage_wt_T

struct dsp_simulink_MovingAverage_wt_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  boolean_T TunablePropsChanged;
  cell_wrap_wturbines_T inputVarSize;
  real_T ForgettingFactor;
  int32_T NumChannels;
  int32_T FrameLength;
  real_T pwN;
  real_T pmN;
  real_T plambda;
};

#endif                              /* struct_dsp_simulink_MovingAverage_wt_T */

/* Forward declaration for rtModel */
typedef struct tag_RTM_wturbines_T RT_MODEL_wturbines_T;

#endif                                 /* wturbines_types_h_ */
