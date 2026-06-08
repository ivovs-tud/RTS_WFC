/*
 * wturbines.h
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

#ifndef wturbines_h_
#define wturbines_h_
#include <logsrv.h>
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "verify/verifyIntrf.h"
#include "slrealtime/libsrc/IP/udp.hpp"
#include "slrealtime/libsrc/IP/ip.hpp"
#include "slrealtime/libsrc/IP/socketFactory.hpp"
#include "string.h"
#include "wturbines_types.h"
#include "rtsplntypes.h"
#include <cstring>

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

#include "wturbines_cal.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContStateDisabled
#define rtmGetContStateDisabled(rtm)   ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
#define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
#define rtmGetContStates(rtm)          ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
#define rtmSetContStates(rtm, val)     ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
#define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
#define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetIntgData
#define rtmGetIntgData(rtm)            ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
#define rtmSetIntgData(rtm, val)       ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
#define rtmGetOdeF(rtm)                ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
#define rtmSetOdeF(rtm, val)           ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
#define rtmGetOdeY(rtm)                ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
#define rtmSetOdeY(rtm, val)           ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
#define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
#define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
#define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
#define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
#define rtmGetZCCacheNeedsReset(rtm)   ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
#define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
#define rtmGetdX(rtm)                  ((rtm)->derivs)
#endif

#ifndef rtmSetdX
#define rtmSetdX(rtm, val)             ((rtm)->derivs = (val))
#endif

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
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

#ifndef rtmGetTStart
#define rtmGetTStart(rtm)              ((rtm)->Timing.tStart)
#endif

#ifndef rtmTaskCounter
#define rtmTaskCounter(rtm, idx)       ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

/* Block signals for system '<Root>/For Each Subsystem' */
struct B_CoreSubsys_wturbines_T {
  real_T DataTypeConversion;           /* '<S2>/Data Type Conversion' */
  real_T DataTypeConversion1;          /* '<S2>/Data Type Conversion1' */
  real_T DataTypeConversion2;          /* '<S2>/Data Type Conversion2' */
  real_T DataTypeConversion3;          /* '<S2>/Data Type Conversion3' */
  real_T IC;                           /* '<S2>/IC' */
  real_T IC1;                          /* '<S2>/IC1' */
  real_T IC5;                          /* '<S2>/IC5' */
  real_T IC6;                          /* '<S2>/IC6' */
  real_T t;                            /* '<S10>/Integrator' */
  real_T Saturation;                   /* '<S10>/Saturation' */
  real_T Product;                      /* '<S276>/Product' */
  real_T RateTransition;               /* '<S2>/Rate Transition' */
  real_T RateLimiter;                  /* '<S2>/Rate Limiter' */
  real_T RateTransition1;              /* '<S2>/Rate Transition1' */
  real_T RateLimiter1;                 /* '<S2>/Rate Limiter1' */
  real_T RateTransition6;              /* '<S2>/Rate Transition6' */
  real_T RateLimiter_p;                /* '<S272>/Rate Limiter' */
  real_T Gain1;                        /* '<S278>/Gain1' */
  real_T TrigonometricFunction;        /* '<S10>/Trigonometric Function' */
  real_T wst;                          /* '<S10>/Product' */
  real_T t_c;                          /* '<S276>/Divide' */
  real_T Gain1_f;                      /* '<S25>/Gain1' */
  real_T RateTransition6_o;            /* '<S9>/Rate Transition6' */
  real_T RateTransition_k;             /* '<S9>/Rate Transition' */
  real_T RateTransition9;              /* '<S9>/Rate Transition9' */
  real_T RateTransition2;              /* '<S9>/Rate Transition2' */
  real_T RateTransition5;              /* '<S2>/Rate Transition5' */
  real_T Saturation_i;                 /* '<S6>/Saturation' */
  real_T P_sett;                       /* '<S6>/Switch' */
  real_T Square;                       /* '<S28>/Square' */
  real_T Product1;                     /* '<S28>/Product1' */
  real_T Divide1;                      /* '<S28>/Divide1' */
  real_T ws_drt;                       /* '<S28>/Power' */
  real_T ws_drwst;                     /* '<S28>/Sum1' */
  real_T _sett;                        /* '<S28>/Derating' */
  real_T Square_b;                     /* '<S150>/Square' */
  real_T Product_b;                    /* '<S150>/Product' */
  real_T Switch;                       /* '<S149>/Switch' */
  real_T e_t;                          /* '<S28>/Sum' */
  real_T ProportionalGain;             /* '<S251>/Proportional Gain' */
  real_T Integrator;                   /* '<S246>/Integrator' */
  real_T ws_drwst_p;                   /* '<S156>/Sum' */
  real_T Divide;                       /* '<S156>/Divide' */
  real_T ws_drwst_o;                   /* '<S155>/Sum' */
  real_T ProportionalGain_d;           /* '<S198>/Proportional Gain' */
  real_T Integrator_i;                 /* '<S193>/Integrator' */
  real_T _rreft;                       /* '<S26>/Multiport Switch' */
  real_T e_rt;                         /* '<S26>/Sum' */
  real_T ProportionalGain_p;           /* '<S136>/Proportional Gain' */
  real_T Integrator_e;                 /* '<S131>/Integrator' */
  real_T Delay;                        /* '<S26>/Delay' */
  real_T Gain;                         /* '<S95>/Gain' */
  real_T GainDynamicLookup;            /* '<S42>/Gain Dynamic Lookup' */
  real_T Gain_h;                       /* '<S32>/Gain' */
  real_T PProdOut;                     /* '<S82>/PProd Out' */
  real_T Integrator_d;                 /* '<S77>/Integrator' */
  real_T Sum;                          /* '<S86>/Sum' */
  real_T MultiportSwitch[2];           /* '<S23>/Multiport Switch' */
  real_T Switch2;                      /* '<S8>/Switch2' */
  real_T RateLimiter_c;                /* '<S8>/Rate Limiter' */
  real_T RateLimiter_n;                /* '<S270>/Rate Limiter' */
  real_T Gain_n;                       /* '<S277>/Gain' */
  real_T Ct;                           /* '<S10>/Ct(&#x3BB;, &#x3B2;)' */
  real_T Saturation1;                  /* '<S10>/Saturation1' */
  real_T RateTransition8;              /* '<S2>/Rate Transition8' */
  real_T RateTransition9_m;            /* '<S2>/Rate Transition9' */
  real_T RateTransition5_i;            /* '<S9>/Rate Transition5' */
  real_T Switch4;                      /* '<S8>/Switch4' */
  real_T Saturation_p;                 /* '<S8>/Saturation' */
  real_T Product_m;                    /* '<S273>/Product' */
  real_T Multiply;                     /* '<S273>/Multiply' */
  real_T RateTransition1_h;            /* '<S9>/Rate Transition1' */
  real_T RateTransition11;             /* '<S9>/Rate Transition11' */
  real_T RateTransition4;              /* '<S9>/Rate Transition4' */
  real_T Gain_o;                       /* '<S11>/Gain' */
  real_T I[2];                         /* '<S32>/Signal Copy' */
  real_T GainDynamicLookup_f;          /* '<S41>/Gain Dynamic Lookup' */
  real_T Gain1_g;                      /* '<S32>/Gain1' */
  real_T IProdOut;                     /* '<S74>/IProd Out' */
  real_T IntegralGain;                 /* '<S128>/Integral Gain' */
  real_T Hcontroller;                  /* '<S33>/H&#x221E; controller ' */
  real_T Multiply_k;                   /* '<S157>/Multiply' */
  real_T Multiply1;                    /* '<S157>/Multiply1' */
  real_T IntegralGain_g;               /* '<S190>/Integral Gain' */
  real_T IntegralGain_a;               /* '<S243>/Integral Gain' */
  real_T _grated;                      /* '<S264>/Gain' */
  real_T Switch3;                      /* '<S8>/Switch3' */
  real_T Multiply2;                    /* '<S10>/Multiply2' */
  real_T RateTransition10;             /* '<S9>/Rate Transition10' */
  real_T RateTransition3;              /* '<S9>/Rate Transition3' */
  real_T Switch_f;                     /* '<S271>/Switch' */
  real_T Saturation_g;                 /* '<S271>/Saturation' */
  real_T Max;                          /* '<S274>/Max' */
  real_T ut;                           /* '<S274>/  ' */
  real_T Square_o;                     /* '<S274>/Square' */
  real_T Power;                        /* '<S274>/Power' */
  real_T T_at;                         /* '<S274>/Product' */
  real_T Saturation_f;                 /* '<S274>/Saturation' */
  real_T Sum_g;                        /* '<S10>/Sum' */
  real_T _dott;                        /* '<S10>/Multiply1' */
  real_T WhiteNoise;                   /* '<S266>/White Noise' */
  real_T Output;                       /* '<S266>/Output' */
  real_T RateTransition7;              /* '<S9>/Rate Transition7' */
  real_T Sum1;                         /* '<S9>/Sum1' */
  real_T WhiteNoise_p;                 /* '<S267>/White Noise' */
  real_T Output_p;                     /* '<S267>/Output' */
  real_T RateTransition8_e;            /* '<S9>/Rate Transition8' */
  real_T Sum_i;                        /* '<S9>/Sum' */
  real_T RateTransition7_p[8];         /* '<S2>/Rate Transition7' */
  real_T Switch1;                      /* '<S8>/Switch1' */
  real_T Switch_a;                     /* '<S8>/Switch' */
  real_T Product_l;                    /* '<S8>/Product' */
  real_T y;                            /* '<S8>/MATLAB Function' */
  real_T Sum_a;                        /* '<S140>/Sum' */
  real_T Derating;                     /* '<S156>/Derating' */
  real_T Derating_e;                   /* '<S155>/Derating' */
  real_T Saturation_k;                 /* '<S28>/Saturation' */
  real_T Sum_n;                        /* '<S202>/Sum' */
  real_T Sum_b;                        /* '<S255>/Sum' */
  real_T _rreft_l;                     /* '<S26>/Divide4' */
  real_T Multiply_l;                   /* '<S31>/Multiply' */
  real_T Multiply1_p;                  /* '<S31>/Multiply1' */
  real_T _sst;                         /* '<S26>/&#x3C9;_ss(u)' */
  real_T Multiply_g;                   /* '<S30>/Multiply' */
  real_T Multiply1_j;                  /* '<S30>/Multiply1' */
  real_T Multiply_p;                   /* '<S151>/Multiply' */
  real_T Multiply1_e;                  /* '<S151>/Multiply1' */
  real_T Sum_d;                        /* '<S149>/Sum' */
  real_T Product1_n;                   /* '<S149>/Product1' */
  real_T Exp;                          /* '<S149>/Exp' */
  real_T ws;                           /* '<S149>/&#x3B2;(ws)' */
  real_T Gain1_o;                      /* '<S153>/Gain1' */
  real_T Product_n;                    /* '<S149>/Product' */
  real_T _drt;                         /* '<S28>/Multiport Switch' */
  real_T _drt_o;                       /* '<S28>/Divide4' */
  real_T _drt_n;                       /* '<S28>/Divide2' */
  real_T Multiply_d;                   /* '<S154>/Multiply' */
  real_T Multiply1_g;                  /* '<S154>/Multiply1' */
  real_T Divide3;                      /* '<S28>/Divide3' */
  real_T Cpt;                          /* '<S271>/Cp(&#x3BB;, &#x3B2;) ' */
  real_T yaw;                          /* '<S10>/True Yaw Offset' */
  op_mode op_mode_m;                   /* '<S8>/Wind Turbine State Machine' */
  uint8_T IC4;                         /* '<S2>/IC4' */
  uint8_T RateTransition4_e;           /* '<S2>/Rate Transition4' */
  boolean_T IC2;                       /* '<S2>/IC2' */
  boolean_T IC3;                       /* '<S2>/IC3' */
  boolean_T RateTransition2_b;         /* '<S2>/Rate Transition2' */
  boolean_T RateTransition3_j;         /* '<S2>/Rate Transition3' */
  boolean_T Compare;                   /* '<S16>/Compare' */
  boolean_T Compare_c;                 /* '<S18>/Compare' */
  boolean_T Compare_j;                 /* '<S17>/Compare' */
  boolean_T OR1;                       /* '<S8>/OR1' */
  boolean_T IsNaN1;                    /* '<S149>/IsNaN1' */
  boolean_T is_not_nan;                /* '<S149>/NOT' */
  boolean_T Compare_n;                 /* '<S21>/Compare' */
  boolean_T Compare_k;                 /* '<S20>/Compare' */
  boolean_T AND;                       /* '<S8>/AND' */
  boolean_T Compare_d;                 /* '<S14>/Compare' */
  boolean_T Compare_ks;                /* '<S15>/Compare' */
  boolean_T OR;                        /* '<S8>/OR' */
  boolean_T Compare_b;                 /* '<S19>/Compare' */
  boolean_T Compare_p;                 /* '<S279>/Compare' */
  boolean_T Compare_a;                 /* '<S280>/Compare' */
  boolean_T OR1_g;                     /* '<S271>/OR1' */
  boolean_T Compare_i;                 /* '<S13>/Compare' */
};

/* Block states (default storage) for system '<Root>/For Each Subsystem' */
struct DW_CoreSubsys_wturbines_T {
  real_T Delay_DSTATE;                 /* '<S26>/Delay' */
  real_T PrevY;                        /* '<S2>/Rate Limiter' */
  real_T PrevY_e;                      /* '<S2>/Rate Limiter1' */
  real_T PrevY_n;                      /* '<S272>/Rate Limiter' */
  real_T PrevY_m;                      /* '<S8>/Rate Limiter' */
  real_T LastMajorTime;                /* '<S8>/Rate Limiter' */
  real_T PrevY_d;                      /* '<S270>/Rate Limiter' */
  real_T LastMajorTime_n;              /* '<S270>/Rate Limiter' */
  real_T m_bpLambda[2];                /* '<S10>/Ct(&#x3BB;, &#x3B2;)' */
  real_T m_yyA[20];                    /* '<S10>/Ct(&#x3BB;, &#x3B2;)' */
  real_T m_yyB[20];                    /* '<S10>/Ct(&#x3BB;, &#x3B2;)' */
  real_T m_yy2[20];                    /* '<S10>/Ct(&#x3BB;, &#x3B2;)' */
  real_T m_up[20];                     /* '<S10>/Ct(&#x3BB;, &#x3B2;)' */
  real_T m_y2[400];                    /* '<S10>/Ct(&#x3BB;, &#x3B2;)' */
  real_T prevBp0AndTableData[420];     /* '<S10>/Ct(&#x3BB;, &#x3B2;)' */
  real_T RateTransition5_Buf[2];       /* '<S9>/Rate Transition5' */
  real_T RateTransition1_Buf[2];       /* '<S9>/Rate Transition1' */
  real_T RateTransition7_Buf[16];      /* '<S2>/Rate Transition7' */
  real_T RateTransition7_Buf_h[2];     /* '<S9>/Rate Transition7' */
  real_T RateTransition8_Buf[2];       /* '<S9>/Rate Transition8' */
  real_T NextOutput;                   /* '<S266>/White Noise' */
  real_T NextOutput_a;                 /* '<S267>/White Noise' */
  real_T last_val;                     /* '<S8>/MATLAB Function' */
  void* m_bpDataSet[2];                /* '<S10>/Ct(&#x3BB;, &#x3B2;)' */
  void* TWork[6];                      /* '<S10>/Ct(&#x3BB;, &#x3B2;)' */
  void* SWork[9];                      /* '<S10>/Ct(&#x3BB;, &#x3B2;)' */
  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Switc;   /* synthesized block */

  struct {
    void *LoggedData;
  } Operationalmode_PWORK;             /* '<S8>/Operational mode' */

  struct {
    void *LoggedData;
  } Scope_PWORK;                       /* '<S8>/Scope' */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_WindT;   /* synthesized block */

  struct {
    void *LoggedData[2];
  } Setpoints_PWORK;                   /* '<S28>/Setpoints' */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_MATLA;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_des_o;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Ct_at;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Produ;   /* synthesized block */

  int32_T sfEvent;                     /* '<S8>/MATLAB Function' */
  int32_T sfEvent_g;                   /* '<S8>/Wind Turbine State Machine' */
  int32_T sfEvent_e;                   /* '<S10>/True Yaw Offset' */
  uint32_T m_bpIndex[2];               /* '<S10>/Ct(&#x3BB;, &#x3B2;)' */
  uint32_T RandSeed;                   /* '<S266>/White Noise' */
  uint32_T RandSeed_j;                 /* '<S267>/White Noise' */
  int8_T RateTransition5_RdBufIdx;     /* '<S9>/Rate Transition5' */
  int8_T RateTransition5_WrBufIdx;     /* '<S9>/Rate Transition5' */
  int8_T RateTransition1_RdBufIdx;     /* '<S9>/Rate Transition1' */
  int8_T RateTransition1_WrBufIdx;     /* '<S9>/Rate Transition1' */
  int8_T RateTransition7_RdBufIdx;     /* '<S2>/Rate Transition7' */
  int8_T RateTransition7_WrBufIdx;     /* '<S2>/Rate Transition7' */
  int8_T RateTransition7_RdBufIdx_g;   /* '<S9>/Rate Transition7' */
  int8_T RateTransition7_WrBufIdx_e;   /* '<S9>/Rate Transition7' */
  int8_T RateTransition8_RdBufIdx;     /* '<S9>/Rate Transition8' */
  int8_T RateTransition8_WrBufIdx;     /* '<S9>/Rate Transition8' */
  uint8_T reCalcSecDerivFirstDimCoeffs;/* '<S10>/Ct(&#x3BB;, &#x3B2;)' */
  uint8_T is_active_c9_wturbines;      /* '<S8>/Wind Turbine State Machine' */
  boolean_T IC_FirstOutputTime;        /* '<S2>/IC' */
  boolean_T IC1_FirstOutputTime;       /* '<S2>/IC1' */
  boolean_T IC2_FirstOutputTime;       /* '<S2>/IC2' */
  boolean_T IC3_FirstOutputTime;       /* '<S2>/IC3' */
  boolean_T IC4_FirstOutputTime;       /* '<S2>/IC4' */
  boolean_T IC5_FirstOutputTime;       /* '<S2>/IC5' */
  boolean_T IC6_FirstOutputTime;       /* '<S2>/IC6' */
  boolean_T PrevLimited;               /* '<S8>/Rate Limiter' */
  boolean_T PrevLimited_m;             /* '<S270>/Rate Limiter' */
  boolean_T doneDoubleBufferReInit;    /* '<S8>/MATLAB Function' */
  boolean_T last_val_not_empty;        /* '<S8>/MATLAB Function' */
  boolean_T doneDoubleBufferReInit_b;  /* '<S10>/True Yaw Offset' */
};

/* Continuous states for system '<Root>/For Each Subsystem' */
struct X_CoreSubsys_wturbines_T {
  real_T Integrator_CSTATE;            /* '<S10>/Integrator' */
  real_T Integrator_CSTATE_o;          /* '<S246>/Integrator' */
  real_T Integrator_CSTATE_l;          /* '<S193>/Integrator' */
  real_T Integrator_CSTATE_e;          /* '<S131>/Integrator' */
  real_T Integrator_CSTATE_oj;         /* '<S77>/Integrator' */
  real_T Hcontroller_CSTATE;           /* '<S33>/H&#x221E; controller ' */
};

/* State derivatives for system '<Root>/For Each Subsystem' */
struct XDot_CoreSubsys_wturbines_T {
  real_T Integrator_CSTATE;            /* '<S10>/Integrator' */
  real_T Integrator_CSTATE_o;          /* '<S246>/Integrator' */
  real_T Integrator_CSTATE_l;          /* '<S193>/Integrator' */
  real_T Integrator_CSTATE_e;          /* '<S131>/Integrator' */
  real_T Integrator_CSTATE_oj;         /* '<S77>/Integrator' */
  real_T Hcontroller_CSTATE;           /* '<S33>/H&#x221E; controller ' */
};

/* State Disabled for system '<Root>/For Each Subsystem' */
struct XDis_CoreSubsys_wturbines_T {
  boolean_T Integrator_CSTATE;         /* '<S10>/Integrator' */
  boolean_T Integrator_CSTATE_o;       /* '<S246>/Integrator' */
  boolean_T Integrator_CSTATE_l;       /* '<S193>/Integrator' */
  boolean_T Integrator_CSTATE_e;       /* '<S131>/Integrator' */
  boolean_T Integrator_CSTATE_oj;      /* '<S77>/Integrator' */
  boolean_T Hcontroller_CSTATE;        /* '<S33>/H&#x221E; controller ' */
};

/* Block signals (default storage) */
struct B_wturbines_T {
  real_T UDPReceive_o2;                /* '<S3>/UDP Receive' */
  real_T UDPReceive_o2_m;              /* '<S4>/UDP Receive' */
  real_T RateTransition[72];           /* '<S5>/Rate Transition' */
  real_T RateTransition_k[18];         /* '<S1>/Rate Transition' */
  real_T ImpAsg_InsertedFor_YawTrue_at_i[9];/* '<S2>/Rate Transition9' */
  real_T ImpAsg_InsertedFor_Ct_at_inport[9];/* '<S2>/Rate Transition8' */
  real_T ImpAsg_InsertedFor_x_at_inport_[72];/* '<S2>/Rate Transition7' */
  real32_T RateTransition1[9];         /* '<S4>/Rate Transition1' */
  real32_T RateTransition2[9];         /* '<S4>/Rate Transition2' */
  real32_T RateTransition1_c[9];       /* '<S3>/Rate Transition1' */
  real32_T RateTransition2_p[9];       /* '<S3>/Rate Transition2' */
  real32_T DataTypeConversion[72];     /* '<S5>/Data Type Conversion' */
  real32_T DataTypeConversion_e[18];   /* '<S1>/Data Type Conversion' */
  real32_T ByteUnpack_o4[9];           /* '<S286>/Byte Unpack' */
  real32_T ByteUnpack_o5[9];           /* '<S286>/Byte Unpack' */
  real32_T ZeroOrderHold3[9];          /* '<S286>/Zero-Order Hold3' */
  real32_T ZeroOrderHold4[9];          /* '<S286>/Zero-Order Hold4' */
  real32_T ByteUnpack_o1[9];           /* '<S282>/Byte Unpack' */
  real32_T ByteUnpack_o2[9];           /* '<S282>/Byte Unpack' */
  real32_T UnitDelay[9];               /* '<S282>/Unit Delay' */
  real32_T UnitDelay1[9];              /* '<S282>/Unit Delay1' */
  real32_T w_filtered[9];              /* '<S282>/ZoH nan filter2' */
  real32_T w_filtered_k[9];            /* '<S282>/ZoH nan filter1' */
  op_mode ImpAsg_InsertedFor_ctrlState_at[9];
  int32_T ForEach;                     /* '<S2>/For Each' */
  uint8_T RateTransition4[9];          /* '<S4>/Rate Transition4' */
  uint8_T UDPReceive_o1[72];           /* '<S3>/UDP Receive' */
  uint8_T UDPReceive_o1_d[99];         /* '<S4>/UDP Receive' */
  uint8_T BytePack1[288];              /* '<S5>/Byte Pack1' */
  uint8_T BytePack1_d[72];             /* '<S1>/Byte Pack1' */
  uint8_T ByteUnpack_o3[9];            /* '<S286>/Byte Unpack' */
  uint8_T ZeroOrderHold2[9];           /* '<S286>/Zero-Order Hold2' */
  boolean_T RateTransition_l[9];       /* '<S4>/Rate Transition' */
  boolean_T RateTransition3[9];        /* '<S4>/Rate Transition3' */
  boolean_T Compare;                   /* '<S281>/Compare' */
  boolean_T Compare_h;                 /* '<S285>/Compare' */
  boolean_T ByteUnpack_o1_f[9];        /* '<S286>/Byte Unpack' */
  boolean_T ByteUnpack_o2_k[9];        /* '<S286>/Byte Unpack' */
  boolean_T ZeroOrderHold1[9];         /* '<S286>/Zero-Order Hold1' */
  boolean_T ZeroOrderHold[9];          /* '<S286>/Zero-Order Hold' */
  B_CoreSubsys_wturbines_T CoreSubsys[9];/* '<Root>/For Each Subsystem' */
};

/* Block states (default storage) for system '<Root>' */
struct DW_wturbines_T {
  real_T RateTransition_Buf[36];       /* '<S1>/Rate Transition' */
  void* UDPReceive_DWORK1;             /* '<S3>/UDP Receive' */
  void *UDPReceive_PWORK[2];           /* '<S3>/UDP Receive' */
  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Compa;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_UDPRe;   /* synthesized block */

  void* UDPReceive_DWORK1_a;           /* '<S4>/UDP Receive' */
  void *UDPReceive_PWORK_k[2];         /* '<S4>/UDP Receive' */
  void* UDPSend1_DWORK1;               /* '<S5>/UDP Send1' */
  void *UDPSend1_PWORK;                /* '<S5>/UDP Send1' */
  void* UDPSend1_DWORK1_b;             /* '<S1>/UDP Send1' */
  void *UDPSend1_PWORK_g;              /* '<S1>/UDP Send1' */
  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_ByteU;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Byt_k;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_ZeroO;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Zer_e;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Zer_p;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Zer_b;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_By_kt;   /* synthesized block */

  real32_T UnitDelay_DSTATE[9];        /* '<S282>/Unit Delay' */
  real32_T UnitDelay1_DSTATE[9];       /* '<S282>/Unit Delay1' */
  real32_T RateTransition1_Buf[18];    /* '<S4>/Rate Transition1' */
  real32_T RateTransition2_Buf[18];    /* '<S4>/Rate Transition2' */
  real32_T RateTransition1_Buf_f[18];  /* '<S3>/Rate Transition1' */
  real32_T RateTransition2_Buf_k[18];  /* '<S3>/Rate Transition2' */
  int32_T sfEvent;                     /* '<S282>/ZoH nan filter2' */
  int32_T sfEvent_n;                   /* '<S282>/ZoH nan filter1' */
  int_T UDPReceive_IWORK[3];           /* '<S3>/UDP Receive' */
  int_T UDPReceive_IWORK_d[3];         /* '<S4>/UDP Receive' */
  int_T UDPSend1_IWORK[2];             /* '<S5>/UDP Send1' */
  int_T UDPSend1_IWORK_g[2];           /* '<S1>/UDP Send1' */
  uint16_T UDPSend1_DWORK2;            /* '<S5>/UDP Send1' */
  uint16_T UDPSend1_DWORK2_d;          /* '<S1>/UDP Send1' */
  int8_T RateTransition_RdBufIdx;      /* '<S4>/Rate Transition' */
  int8_T RateTransition_WrBufIdx;      /* '<S4>/Rate Transition' */
  int8_T RateTransition3_RdBufIdx;     /* '<S4>/Rate Transition3' */
  int8_T RateTransition3_WrBufIdx;     /* '<S4>/Rate Transition3' */
  int8_T RateTransition4_RdBufIdx;     /* '<S4>/Rate Transition4' */
  int8_T RateTransition4_WrBufIdx;     /* '<S4>/Rate Transition4' */
  int8_T RateTransition1_RdBufIdx;     /* '<S4>/Rate Transition1' */
  int8_T RateTransition1_WrBufIdx;     /* '<S4>/Rate Transition1' */
  int8_T RateTransition2_RdBufIdx;     /* '<S4>/Rate Transition2' */
  int8_T RateTransition2_WrBufIdx;     /* '<S4>/Rate Transition2' */
  int8_T RateTransition1_RdBufIdx_k;   /* '<S3>/Rate Transition1' */
  int8_T RateTransition1_WrBufIdx_g;   /* '<S3>/Rate Transition1' */
  int8_T RateTransition2_RdBufIdx_c;   /* '<S3>/Rate Transition2' */
  int8_T RateTransition2_WrBufIdx_g;   /* '<S3>/Rate Transition2' */
  int8_T RateTransition_RdBufIdx_e;    /* '<S1>/Rate Transition' */
  int8_T RateTransition_WrBufIdx_j;    /* '<S1>/Rate Transition' */
  int8_T EnabledSubsystem_SubsysRanBC; /* '<S4>/Enabled Subsystem' */
  int8_T EnabledSubsystem_SubsysRanBC_i;/* '<S3>/Enabled Subsystem' */
  uint8_T RateTransition4_Buf[18];     /* '<S4>/Rate Transition4' */
  boolean_T RateTransition_Buf_n[18];  /* '<S4>/Rate Transition' */
  boolean_T RateTransition3_Buf[18];   /* '<S4>/Rate Transition3' */
  boolean_T doneDoubleBufferReInit;    /* '<S282>/ZoH nan filter2' */
  boolean_T doneDoubleBufferReInit_e;  /* '<S282>/ZoH nan filter1' */
  DW_CoreSubsys_wturbines_T CoreSubsys[9];/* '<Root>/For Each Subsystem' */
};

/* Continuous states (default storage) */
struct X_wturbines_T {
  X_CoreSubsys_wturbines_T CoreSubsys[9];/* '<S2>/CoreSubsys' */
};

/* State derivatives (default storage) */
struct XDot_wturbines_T {
  XDot_CoreSubsys_wturbines_T CoreSubsys[9];/* '<S2>/CoreSubsys' */
};

/* State disabled  */
struct XDis_wturbines_T {
  XDis_CoreSubsys_wturbines_T CoreSubsys[9];/* '<S2>/CoreSubsys' */
};

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
struct ODE4_IntgData {
  real_T *y;                           /* output */
  real_T *f[4];                        /* derivatives */
};

#endif

/* Real-time Model Data Structure */
struct tag_RTM_wturbines_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_wturbines_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_wturbines_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[54];
  real_T odeF[4][54];
  ODE4_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    uint32_T clockTick2;
    uint32_T clockTickH2;
    uint32_T clockTick3;
    uint32_T clockTickH3;
    uint32_T clockTick4;
    uint32_T clockTickH4;
    struct {
      uint8_T TID[5];
      uint8_T cLimit[5];
    } TaskCounters;

    struct {
      uint8_T TID1_2;
      uint8_T TID1_3;
      uint8_T TID1_4;
    } RateInteraction;

    time_T tStart;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[5];
  } Timing;
};

/* Block signals (default storage) */
#ifdef __cplusplus

extern "C"
{

#endif

  extern struct B_wturbines_T wturbines_B;

#ifdef __cplusplus

}

#endif

/* Continuous states (default storage) */
extern X_wturbines_T wturbines_X;

/* Disabled states (default storage) */
extern XDis_wturbines_T wturbines_XDis;

/* Block states (default storage) */
extern struct DW_wturbines_T wturbines_DW;

#ifdef __cplusplus

extern "C"
{

#endif

  /* Model entry point functions */
  extern void wturbines_initialize(void);
  extern void wturbines_step0(void);
  extern void wturbines_step2(void);   /* Sample time: [0.1s, 0.0s] */
  extern void wturbines_step3(void);   /* Sample time: [0.25s, 0.0s] */
  extern void wturbines_step4(void);   /* Sample time: [0.5s, 0.0s] */
  extern void wturbines_terminate(void);

#ifdef __cplusplus

}

#endif

/* Real-time Model object */
#ifdef __cplusplus

extern "C"
{

#endif

  extern RT_MODEL_wturbines_T *const wturbines_M;

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
 * '<Root>' : 'wturbines'
 * '<S1>'   : 'wturbines/Ct,Yaw to OFF'
 * '<S2>'   : 'wturbines/For Each Subsystem'
 * '<S3>'   : 'wturbines/RX FlowField Conditions'
 * '<S4>'   : 'wturbines/Receive Turbine CMD'
 * '<S5>'   : 'wturbines/Send Turbine Data to PLC'
 * '<S6>'   : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1'
 * '<S7>'   : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/  '
 * '<S8>'   : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic'
 * '<S9>'   : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Measurements'
 * '<S10>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Turbine Dynamics'
 * '<S11>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/  /Radians to Degrees'
 * '<S12>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/     '
 * '<S13>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Compare To Constant'
 * '<S14>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Compare To Constant1'
 * '<S15>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Compare To Constant2'
 * '<S16>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Compare To Constant3'
 * '<S17>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Compare To Constant4'
 * '<S18>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Compare To Constant5'
 * '<S19>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Compare To Constant6'
 * '<S20>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Compare To Constant7'
 * '<S21>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Compare To Constant8'
 * '<S22>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/MATLAB Function'
 * '<S23>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller'
 * '<S24>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Wind Turbine State Machine'
 * '<S25>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/     /Degrees to Radians'
 * '<S26>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control '
 * '<S27>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/K&#x3C9;2 controller'
 * '<S28>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation'
 * '<S29>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/ROSCO'
 * '<S30>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control / '
 * '<S31>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /  '
 * '<S32>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller'
 * '<S33>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller'
 * '<S34>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/Gain scheduler'
 * '<S35>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller'
 * '<S36>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/rad2deg'
 * '<S37>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/Gain scheduler/DGain Lookup'
 * '<S38>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/Gain scheduler/IGain Lookup'
 * '<S39>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/Gain scheduler/NGain Lookup'
 * '<S40>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/Gain scheduler/PGain Lookup'
 * '<S41>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/Gain scheduler/IGain Lookup/Enabled'
 * '<S42>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/Gain scheduler/PGain Lookup/Enabled'
 * '<S43>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Anti-windup'
 * '<S44>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/D Gain'
 * '<S45>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/External Derivative'
 * '<S46>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Filter'
 * '<S47>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Filter ICs'
 * '<S48>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/I Gain'
 * '<S49>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Ideal P Gain'
 * '<S50>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Ideal P Gain Fdbk'
 * '<S51>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Integrator'
 * '<S52>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Integrator ICs'
 * '<S53>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/N Copy'
 * '<S54>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/N Gain'
 * '<S55>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/P Copy'
 * '<S56>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Parallel P Gain'
 * '<S57>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Reset Signal'
 * '<S58>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Saturation'
 * '<S59>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Saturation Fdbk'
 * '<S60>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Sum'
 * '<S61>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Sum Fdbk'
 * '<S62>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Tracking Mode'
 * '<S63>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Tracking Mode Sum'
 * '<S64>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Tsamp - Integral'
 * '<S65>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Tsamp - Ngain'
 * '<S66>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/postSat Signal'
 * '<S67>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/preInt Signal'
 * '<S68>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/preSat Signal'
 * '<S69>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Anti-windup/Passthrough'
 * '<S70>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/D Gain/Disabled'
 * '<S71>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/External Derivative/Disabled'
 * '<S72>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Filter/Disabled'
 * '<S73>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Filter ICs/Disabled'
 * '<S74>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/I Gain/External Parameters'
 * '<S75>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Ideal P Gain/Passthrough'
 * '<S76>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Ideal P Gain Fdbk/Disabled'
 * '<S77>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Integrator/Continuous'
 * '<S78>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Integrator ICs/Internal IC'
 * '<S79>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/N Copy/Disabled wSignal Specification'
 * '<S80>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/N Gain/Disabled'
 * '<S81>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/P Copy/Disabled'
 * '<S82>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Parallel P Gain/External Parameters'
 * '<S83>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Reset Signal/Disabled'
 * '<S84>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Saturation/Passthrough'
 * '<S85>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Saturation Fdbk/Disabled'
 * '<S86>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Sum/Sum_PI'
 * '<S87>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Sum Fdbk/Disabled'
 * '<S88>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Tracking Mode/Disabled'
 * '<S89>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Tracking Mode Sum/Passthrough'
 * '<S90>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S91>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Tsamp - Ngain/Passthrough'
 * '<S92>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/postSat Signal/Forward_Path'
 * '<S93>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/preInt Signal/Internal PreInt'
 * '<S94>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/preSat Signal/Forward_Path'
 * '<S95>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/rad2deg/Radians to Degrees'
 * '<S96>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller'
 * '<S97>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Anti-windup'
 * '<S98>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/D Gain'
 * '<S99>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/External Derivative'
 * '<S100>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Filter'
 * '<S101>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Filter ICs'
 * '<S102>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/I Gain'
 * '<S103>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Ideal P Gain'
 * '<S104>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Ideal P Gain Fdbk'
 * '<S105>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Integrator'
 * '<S106>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Integrator ICs'
 * '<S107>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/N Copy'
 * '<S108>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/N Gain'
 * '<S109>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/P Copy'
 * '<S110>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Parallel P Gain'
 * '<S111>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Reset Signal'
 * '<S112>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Saturation'
 * '<S113>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Saturation Fdbk'
 * '<S114>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Sum'
 * '<S115>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Sum Fdbk'
 * '<S116>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Tracking Mode'
 * '<S117>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Tracking Mode Sum'
 * '<S118>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Tsamp - Integral'
 * '<S119>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Tsamp - Ngain'
 * '<S120>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/postSat Signal'
 * '<S121>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/preInt Signal'
 * '<S122>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/preSat Signal'
 * '<S123>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Anti-windup/Passthrough'
 * '<S124>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/D Gain/Disabled'
 * '<S125>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/External Derivative/Disabled'
 * '<S126>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Filter/Disabled'
 * '<S127>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Filter ICs/Disabled'
 * '<S128>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/I Gain/Internal Parameters'
 * '<S129>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Ideal P Gain/Passthrough'
 * '<S130>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Ideal P Gain Fdbk/Disabled'
 * '<S131>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Integrator/Continuous'
 * '<S132>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Integrator ICs/Internal IC'
 * '<S133>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/N Copy/Disabled wSignal Specification'
 * '<S134>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/N Gain/Disabled'
 * '<S135>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/P Copy/Disabled'
 * '<S136>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Parallel P Gain/Internal Parameters'
 * '<S137>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Reset Signal/Disabled'
 * '<S138>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Saturation/Passthrough'
 * '<S139>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Saturation Fdbk/Disabled'
 * '<S140>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Sum/Sum_PI'
 * '<S141>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Sum Fdbk/Disabled'
 * '<S142>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Tracking Mode/Disabled'
 * '<S143>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Tracking Mode Sum/Passthrough'
 * '<S144>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Tsamp - Integral/TsSignalSpecification'
 * '<S145>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Tsamp - Ngain/Passthrough'
 * '<S146>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/postSat Signal/Forward_Path'
 * '<S147>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/preInt Signal/Internal PreInt'
 * '<S148>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/preSat Signal/Forward_Path'
 * '<S149>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/K&#x3C9;2 controller/Pitch controller'
 * '<S150>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/K&#x3C9;2 controller/Torque controller'
 * '<S151>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/K&#x3C9;2 controller/Pitch controller/  '
 * '<S152>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/K&#x3C9;2 controller/Pitch controller/rad2deg'
 * '<S153>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/K&#x3C9;2 controller/Pitch controller/rad2deg/Degrees to Radians'
 * '<S154>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/  '
 * '<S155>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller'
 * '<S156>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller'
 * '<S157>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/rads2rpm'
 * '<S158>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller'
 * '<S159>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Anti-windup'
 * '<S160>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/D Gain'
 * '<S161>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/External Derivative'
 * '<S162>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Filter'
 * '<S163>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Filter ICs'
 * '<S164>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/I Gain'
 * '<S165>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Ideal P Gain'
 * '<S166>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Ideal P Gain Fdbk'
 * '<S167>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Integrator'
 * '<S168>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Integrator ICs'
 * '<S169>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/N Copy'
 * '<S170>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/N Gain'
 * '<S171>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/P Copy'
 * '<S172>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Parallel P Gain'
 * '<S173>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Reset Signal'
 * '<S174>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Saturation'
 * '<S175>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Saturation Fdbk'
 * '<S176>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Sum'
 * '<S177>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Sum Fdbk'
 * '<S178>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Tracking Mode'
 * '<S179>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Tracking Mode Sum'
 * '<S180>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Tsamp - Integral'
 * '<S181>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Tsamp - Ngain'
 * '<S182>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/postSat Signal'
 * '<S183>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/preInt Signal'
 * '<S184>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/preSat Signal'
 * '<S185>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Anti-windup/Passthrough'
 * '<S186>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/D Gain/Disabled'
 * '<S187>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/External Derivative/Disabled'
 * '<S188>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Filter/Disabled'
 * '<S189>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Filter ICs/Disabled'
 * '<S190>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/I Gain/Internal Parameters'
 * '<S191>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Ideal P Gain/Passthrough'
 * '<S192>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Ideal P Gain Fdbk/Disabled'
 * '<S193>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Integrator/Continuous'
 * '<S194>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Integrator ICs/Internal IC'
 * '<S195>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/N Copy/Disabled wSignal Specification'
 * '<S196>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/N Gain/Disabled'
 * '<S197>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/P Copy/Disabled'
 * '<S198>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Parallel P Gain/Internal Parameters'
 * '<S199>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Reset Signal/Disabled'
 * '<S200>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Saturation/Passthrough'
 * '<S201>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Saturation Fdbk/Disabled'
 * '<S202>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Sum/Sum_PI'
 * '<S203>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Sum Fdbk/Disabled'
 * '<S204>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Tracking Mode/Disabled'
 * '<S205>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Tracking Mode Sum/Passthrough'
 * '<S206>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Tsamp - Integral/TsSignalSpecification'
 * '<S207>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Tsamp - Ngain/Passthrough'
 * '<S208>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/postSat Signal/Forward_Path'
 * '<S209>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/preInt Signal/Internal PreInt'
 * '<S210>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/preSat Signal/Forward_Path'
 * '<S211>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller'
 * '<S212>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Anti-windup'
 * '<S213>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/D Gain'
 * '<S214>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/External Derivative'
 * '<S215>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Filter'
 * '<S216>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Filter ICs'
 * '<S217>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/I Gain'
 * '<S218>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Ideal P Gain'
 * '<S219>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Ideal P Gain Fdbk'
 * '<S220>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Integrator'
 * '<S221>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Integrator ICs'
 * '<S222>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/N Copy'
 * '<S223>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/N Gain'
 * '<S224>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/P Copy'
 * '<S225>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Parallel P Gain'
 * '<S226>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Reset Signal'
 * '<S227>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Saturation'
 * '<S228>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Saturation Fdbk'
 * '<S229>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Sum'
 * '<S230>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Sum Fdbk'
 * '<S231>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Tracking Mode'
 * '<S232>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Tracking Mode Sum'
 * '<S233>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Tsamp - Integral'
 * '<S234>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Tsamp - Ngain'
 * '<S235>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/postSat Signal'
 * '<S236>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/preInt Signal'
 * '<S237>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/preSat Signal'
 * '<S238>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Anti-windup/Passthrough'
 * '<S239>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/D Gain/Disabled'
 * '<S240>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/External Derivative/Disabled'
 * '<S241>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Filter/Disabled'
 * '<S242>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Filter ICs/Disabled'
 * '<S243>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/I Gain/Internal Parameters'
 * '<S244>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Ideal P Gain/Passthrough'
 * '<S245>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Ideal P Gain Fdbk/Disabled'
 * '<S246>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Integrator/Continuous'
 * '<S247>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Integrator ICs/Internal IC'
 * '<S248>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/N Copy/Disabled wSignal Specification'
 * '<S249>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/N Gain/Disabled'
 * '<S250>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/P Copy/Disabled'
 * '<S251>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Parallel P Gain/Internal Parameters'
 * '<S252>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Reset Signal/Disabled'
 * '<S253>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Saturation/Passthrough'
 * '<S254>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Saturation Fdbk/Disabled'
 * '<S255>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Sum/Sum_PI'
 * '<S256>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Sum Fdbk/Disabled'
 * '<S257>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Tracking Mode/Disabled'
 * '<S258>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Tracking Mode Sum/Passthrough'
 * '<S259>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Tsamp - Integral/TsSignalSpecification'
 * '<S260>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Tsamp - Ngain/Passthrough'
 * '<S261>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/postSat Signal/Forward_Path'
 * '<S262>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/preInt Signal/Internal PreInt'
 * '<S263>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/preSat Signal/Forward_Path'
 * '<S264>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/ROSCO/Pitch controller'
 * '<S265>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/ROSCO/Torque controller'
 * '<S266>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Measurements/Band-Limited White Noise'
 * '<S267>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Measurements/Band-Limited White Noise1'
 * '<S268>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Turbine Dynamics/  '
 * '<S269>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Turbine Dynamics/     '
 * '<S270>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Turbine Dynamics/Collective Pitch Dynamics'
 * '<S271>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Turbine Dynamics/Cp(&#x3BB;, &#x3B2;)'
 * '<S272>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Turbine Dynamics/Orientation Dynamics'
 * '<S273>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Turbine Dynamics/P(t)'
 * '<S274>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Turbine Dynamics/T_a(t)'
 * '<S275>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Turbine Dynamics/True Yaw Offset'
 * '<S276>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Turbine Dynamics/&#x3BB;(t)'
 * '<S277>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Turbine Dynamics/  /Radians to Degrees'
 * '<S278>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Turbine Dynamics/     /Degrees to Radians'
 * '<S279>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Turbine Dynamics/Cp(&#x3BB;, &#x3B2;)/Compare To Constant2'
 * '<S280>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Turbine Dynamics/Cp(&#x3BB;, &#x3B2;)/Compare To Constant3'
 * '<S281>' : 'wturbines/RX FlowField Conditions/Compare To Constant'
 * '<S282>' : 'wturbines/RX FlowField Conditions/Enabled Subsystem'
 * '<S283>' : 'wturbines/RX FlowField Conditions/Enabled Subsystem/ZoH nan filter1'
 * '<S284>' : 'wturbines/RX FlowField Conditions/Enabled Subsystem/ZoH nan filter2'
 * '<S285>' : 'wturbines/Receive Turbine CMD/Compare To Constant'
 * '<S286>' : 'wturbines/Receive Turbine CMD/Enabled Subsystem'
 */
#endif                                 /* wturbines_h_ */
