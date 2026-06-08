/*
 * udp1.h
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

#ifndef udp1_h_
#define udp1_h_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "verify/verifyIntrf.h"
#include "string.h"
#include "slrealtime/libsrc/IP/udp.hpp"
#include "slrealtime/libsrc/IP/ip.hpp"
#include "slrealtime/libsrc/IP/socketFactory.hpp"
#include "udp1_types.h"

extern "C"
{

#include "rt_nonfinite.h"

}

extern "C"
{

#include "rtGetInf.h"

}

extern "C"
{

#include "rtGetNaN.h"

}

#include "udp1_cal.h"
#include <cstring>

/* Macros for accessing real-time model data structure */
#ifndef rtmCounterLimit
#define rtmCounterLimit(rtm, idx)      ((rtm)->Timing.TaskCounters.cLimit[(idx)])
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmStepTask
#define rtmStepTask(rtm, idx)          ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmTaskCounter
#define rtmTaskCounter(rtm, idx)       ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

/* Block signals for system '<S1>/MATLAB Function' */
struct B_MATLABFunction_udp1_T {
  real_T xn[8];                        /* '<S1>/MATLAB Function' */
};

/* Block states (default storage) for system '<S1>/MATLAB Function' */
struct DW_MATLABFunction_udp1_T {
  int32_T sfEvent;                     /* '<S1>/MATLAB Function' */
  uint32_T method;                     /* '<S1>/MATLAB Function' */
  uint32_T state[2];                   /* '<S1>/MATLAB Function' */
  uint32_T method_l;                   /* '<S1>/MATLAB Function' */
  uint32_T state_i;                    /* '<S1>/MATLAB Function' */
  uint32_T state_b[2];                 /* '<S1>/MATLAB Function' */
  uint32_T state_f[625];               /* '<S1>/MATLAB Function' */
  boolean_T doneDoubleBufferReInit;    /* '<S1>/MATLAB Function' */
  boolean_T method_not_empty;          /* '<S1>/MATLAB Function' */
  boolean_T state_not_empty;           /* '<S1>/MATLAB Function' */
  boolean_T method_not_empty_l;        /* '<S1>/MATLAB Function' */
  boolean_T state_not_empty_n;         /* '<S1>/MATLAB Function' */
  boolean_T state_not_empty_k;         /* '<S1>/MATLAB Function' */
  boolean_T state_not_empty_f;         /* '<S1>/MATLAB Function' */
};

/* Block signals for system '<Root>/For Each Subsystem' */
struct B_CoreSubsys_udp1_T {
  B_MATLABFunction_udp1_T sf_MATLABFunction;/* '<S1>/MATLAB Function' */
};

/* Block states (default storage) for system '<Root>/For Each Subsystem' */
struct DW_CoreSubsys_udp1_T {
  DW_MATLABFunction_udp1_T sf_MATLABFunction;/* '<S1>/MATLAB Function' */
};

/* Block signals (default storage) */
struct B_udp1_T {
  real_T UnitDelay[96];                /* '<Root>/Unit Delay' */
  real_T UDPReceive_o2;                /* '<Root>/UDP Receive' */
  real_T ImpAsg_InsertedFor_xn_at_inport[96];/* '<S1>/MATLAB Function' */
  uint8_T BytePack1[768];              /* '<Root>/Byte Pack1' */
  uint8_T UDPReceive_o1[32];           /* '<Root>/UDP Receive' */
  uint8_T TmpRTBAtUDPSend1Inport1[768];/* '<Root>/Byte Pack1' */
  B_CoreSubsys_udp1_T CoreSubsys[12];  /* '<Root>/For Each Subsystem' */
};

/* Block states (default storage) for system '<Root>' */
struct DW_udp1_T {
  real_T UnitDelay_DSTATE[96];         /* '<Root>/Unit Delay' */
  void* UDPReceive_DWORK1;             /* '<Root>/UDP Receive' */
  void *UDPReceive_PWORK[2];           /* '<Root>/UDP Receive' */
  struct {
    void *LoggedData;
  } Scope1_PWORK;                      /* '<Root>/Scope1' */

  void* UDPSend1_DWORK1;               /* '<Root>/UDP Send1' */
  void *UDPSend1_PWORK;                /* '<Root>/UDP Send1' */
  int_T UDPReceive_IWORK[3];           /* '<Root>/UDP Receive' */
  int_T UDPSend1_IWORK[2];             /* '<Root>/UDP Send1' */
  uint16_T UDPSend1_DWORK2;            /* '<Root>/UDP Send1' */
  int8_T TmpRTBAtUDPSend1Inport1_RdBufId;/* synthesized block */
  int8_T TmpRTBAtUDPSend1Inport1_WrBufId;/* synthesized block */
  uint8_T TmpRTBAtUDPSend1Inport1_Buf[1536];/* synthesized block */
  DW_CoreSubsys_udp1_T CoreSubsys[12]; /* '<Root>/For Each Subsystem' */
};

/* Real-time Model Data Structure */
struct tag_RTM_udp1_T {
  const char_T *errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    struct {
      uint8_T TID[2];
      uint8_T cLimit[2];
    } TaskCounters;

    struct {
      uint8_T TID0_1;
    } RateInteraction;

    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block signals (default storage) */
#ifdef __cplusplus

extern "C"
{

#endif

  extern struct B_udp1_T udp1_B;

#ifdef __cplusplus

}

#endif

/* Block states (default storage) */
extern struct DW_udp1_T udp1_DW;

#ifdef __cplusplus

extern "C"
{

#endif

  /* Model entry point functions */
  extern void udp1_initialize(void);
  extern void udp1_step0(void);        /* Sample time: [0.1s, 0.0s] */
  extern void udp1_step1(void);        /* Sample time: [0.5s, 0.0s] */
  extern void udp1_terminate(void);

#ifdef __cplusplus

}

#endif

/* Real-time Model object */
#ifdef __cplusplus

extern "C"
{

#endif

  extern RT_MODEL_udp1_T *const udp1_M;

#ifdef __cplusplus

}

#endif

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'udp1'
 * '<S1>'   : 'udp1/For Each Subsystem'
 * '<S2>'   : 'udp1/For Each Subsystem/MATLAB Function'
 */
#endif                                 /* udp1_h_ */
