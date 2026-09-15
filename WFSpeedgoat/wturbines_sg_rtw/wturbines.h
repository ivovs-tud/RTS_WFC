/*
 * wturbines.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "wturbines".
 *
 * Model version              : 1.313
 * Simulink Coder version : 24.2 (R2024b) 21-Jun-2024
 * C++ source code generated on : Wed Jun 17 16:19:19 2026
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
  loggingData BusCreator;              /* '<S7>/Bus Creator' */
  real_T DataTypeConversion;           /* '<S2>/Data Type Conversion' */
  real_T DataTypeConversion1;          /* '<S2>/Data Type Conversion1' */
  real_T DataTypeConversion2;          /* '<S2>/Data Type Conversion2' */
  real_T DataTypeConversion3;          /* '<S2>/Data Type Conversion3' */
  real_T IC;                           /* '<S2>/IC' */
  real_T IC1;                          /* '<S2>/IC1' */
  real_T IC5;                          /* '<S2>/IC5' */
  real_T IC6;                          /* '<S2>/IC6' */
  real_T t;                            /* '<S15>/Integrator' */
  real_T RotSpd;                       /* '<S15>/Saturation' */
  real_T Product;                      /* '<S284>/Product' */
  real_T RateTransition;               /* '<S2>/Rate Transition' */
  real_T RateLimiter;                  /* '<S2>/Rate Limiter' */
  real_T RateTransition1;              /* '<S2>/Rate Transition1' */
  real_T RateLimiter1;                 /* '<S2>/Rate Limiter1' */
  real_T RateTransition6;              /* '<S2>/Rate Transition6' */
  real_T IC_c;                         /* '<S12>/IC' */
  real_T RateLimiter_p;                /* '<S280>/Rate Limiter' */
  real_T IC_k;                         /* '<S280>/IC' */
  real_T Gain1;                        /* '<S286>/Gain1' */
  real_T TrigonometricFunction;        /* '<S15>/Trigonometric Function' */
  real_T Product_l;                    /* '<S15>/Product' */
  real_T WsEff;                        /* '<S15>/Saturation2' */
  real_T t_c;                          /* '<S284>/Divide' */
  real_T Gain1_f;                      /* '<S28>/Gain1' */
  real_T RateTransition13;             /* '<S13>/Rate Transition13' */
  real_T RateTransition2;              /* '<S13>/Rate Transition2' */
  real_T RateTransition5;              /* '<S2>/Rate Transition5' */
  real_T Saturation;                   /* '<S8>/Saturation' */
  real_T Pref;                         /* '<S8>/Switch' */
  real_T Square;                       /* '<S31>/Square' */
  real_T Product1;                     /* '<S31>/Product1' */
  real_T Divide1;                      /* '<S31>/Divide1' */
  real_T ws_drt;                       /* '<S31>/Power' */
  real_T ws_drwst;                     /* '<S31>/Sum1' */
  real_T _sett;                        /* '<S31>/Derating' */
  real_T RateTransition3;              /* '<S13>/Rate Transition3' */
  real_T Square_b;                     /* '<S153>/Square' */
  real_T Product_b;                    /* '<S153>/Product' */
  real_T Switch;                       /* '<S152>/Switch' */
  real_T e_t;                          /* '<S31>/Sum' */
  real_T ProportionalGain;             /* '<S254>/Proportional Gain' */
  real_T Integrator;                   /* '<S249>/Integrator' */
  real_T ws_drwst_p;                   /* '<S159>/Sum' */
  real_T Divide;                       /* '<S159>/Divide' */
  real_T Gain;                         /* '<S159>/Gain' */
  real_T ws_drwst_o;                   /* '<S158>/Sum' */
  real_T ProportionalGain_d;           /* '<S201>/Proportional Gain' */
  real_T Integrator_i;                 /* '<S196>/Integrator' */
  real_T _rreft;                       /* '<S29>/Multiport Switch' */
  real_T e_rt;                         /* '<S29>/Sum' */
  real_T ProportionalGain_p;           /* '<S139>/Proportional Gain' */
  real_T Integrator_e;                 /* '<S134>/Integrator' */
  real_T Delay;                        /* '<S29>/Delay' */
  real_T Gain_k;                       /* '<S98>/Gain' */
  real_T GainDynamicLookup;            /* '<S45>/Gain Dynamic Lookup' */
  real_T Gain_h;                       /* '<S35>/Gain' */
  real_T PProdOut;                     /* '<S85>/PProd Out' */
  real_T Integrator_d;                 /* '<S80>/Integrator' */
  real_T Sum;                          /* '<S89>/Sum' */
  real_T MultiportSwitch[2];           /* '<S26>/Multiport Switch' */
  real_T PitchSpt;                     /* '<S12>/Switch2' */
  real_T RateLimiter_n;                /* '<S278>/Rate Limiter' */
  real_T Gain_n;                       /* '<S285>/Gain' */
  real_T Ct;                           /* '<S15>/Ct(&#x3BB;, &#x3B2;)' */
  real_T Ct_n;                         /* '<S15>/Saturation1' */
  real_T RateTransition8;              /* '<S2>/Rate Transition8' */
  real_T RateTransition9;              /* '<S2>/Rate Transition9' */
  real_T RateTransition_k;             /* '<S13>/Rate Transition' */
  real_T RateTransition5_i;            /* '<S13>/Rate Transition5' */
  real_T GenSpd;                       /* '<S15>/Multiply2' */
  real_T Switch5;                      /* '<S12>/Switch5' */
  real_T Tgen;                         /* '<S12>/Saturation' */
  real_T Product_m;                    /* '<S281>/Product' */
  real_T Multiply;                     /* '<S281>/Multiply' */
  real_T RateTransition1_h;            /* '<S13>/Rate Transition1' */
  real_T Gain_i;                       /* '<S10>/Gain' */
  real_T RateTransition4;              /* '<S13>/Rate Transition4' */
  real_T Gain_o;                       /* '<S16>/Gain' */
  real_T RateTransition1_a;            /* '<S8>/Rate Transition1' */
  real_T I[2];                         /* '<S35>/Signal Copy' */
  real_T GainDynamicLookup_f;          /* '<S44>/Gain Dynamic Lookup' */
  real_T Gain1_g;                      /* '<S35>/Gain1' */
  real_T IProdOut;                     /* '<S77>/IProd Out' */
  real_T IntegralGain;                 /* '<S131>/Integral Gain' */
  real_T Hcontroller;                  /* '<S36>/H&#x221E; controller ' */
  real_T Relay;                        /* '<S153>/Relay' */
  real_T Switch_i;                     /* '<S153>/Switch' */
  real_T Multiply_k;                   /* '<S160>/Multiply' */
  real_T Multiply1;                    /* '<S160>/Multiply1' */
  real_T IntegralGain_g;               /* '<S193>/Integral Gain' */
  real_T IntegralGain_a;               /* '<S246>/Integral Gain' */
  real_T _grated;                      /* '<S267>/Gain' */
  real_T Tbrake;                       /* '<S12>/Switch3' */
  real_T Switch_f;                     /* '<S279>/Switch' */
  real_T Saturation_g;                 /* '<S279>/Saturation' */
  real_T Friction;                     /* '<S15>/Friction' */
  real_T Gain_m;                       /* '<S15>/Gain' */
  real_T Max;                          /* '<S282>/Max' */
  real_T ut;                           /* '<S282>/  ' */
  real_T Square_o;                     /* '<S282>/Square' */
  real_T Power;                        /* '<S282>/Power' */
  real_T T_at;                         /* '<S282>/Product' */
  real_T Saturation_f;                 /* '<S282>/Saturation' */
  real_T Sum_g;                        /* '<S15>/Sum' */
  real_T _dott;                        /* '<S15>/Multiply1' */
  real_T Sum1;                         /* '<S15>/Sum1' */
  real_T WhiteNoise;                   /* '<S11>/White Noise' */
  real_T Output;                       /* '<S11>/Output' */
  real_T WhiteNoise_g;                 /* '<S271>/White Noise' */
  real_T Output_l;                     /* '<S271>/Output' */
  real_T RateTransition6_o;            /* '<S13>/Rate Transition6' */
  real_T Sum2;                         /* '<S13>/Sum2' */
  real_T WhiteNoise_f;                 /* '<S269>/White Noise' */
  real_T Output_o;                     /* '<S269>/Output' */
  real_T RateTransition7;              /* '<S13>/Rate Transition7' */
  real_T Sum1_j;                       /* '<S13>/Sum1' */
  real_T WhiteNoise_a;                 /* '<S272>/White Noise' */
  real_T Output_g;                     /* '<S272>/Output' */
  real_T RateTransition9_o;            /* '<S13>/Rate Transition9' */
  real_T Sum3;                         /* '<S13>/Sum3' */
  real_T WhiteNoise_p;                 /* '<S270>/White Noise' */
  real_T Output_p;                     /* '<S270>/Output' */
  real_T RateTransition8_e;            /* '<S13>/Rate Transition8' */
  real_T Sum_i;                        /* '<S13>/Sum' */
  real_T WhiteNoise_e;                 /* '<S273>/White Noise' */
  real_T Output_h;                     /* '<S273>/Output' */
  real_T RateTransition10;             /* '<S13>/Rate Transition10' */
  real_T Sum4;                         /* '<S13>/Sum4' */
  real_T WhiteNoise_fo;                /* '<S274>/White Noise' */
  real_T Output_m;                     /* '<S274>/Output' */
  real_T RateTransition11;             /* '<S13>/Rate Transition11' */
  real_T Sum5;                         /* '<S13>/Sum5' */
  real_T WhiteNoise_i;                 /* '<S275>/White Noise' */
  real_T Output_k;                     /* '<S275>/Output' */
  real_T RateTransition12;             /* '<S13>/Rate Transition12' */
  real_T Sum6;                         /* '<S13>/Sum6' */
  real_T RateTransition2_p;            /* '<S8>/Rate Transition2' */
  real_T Sum4_n;                       /* '<S8>/Sum4' */
  real_T RateTransition7_p[8];         /* '<S2>/Rate Transition7' */
  real_T ws_drt_h;                     /* '<S14>/Power' */
  real_T Square_oq;                    /* '<S14>/Square' */
  real_T Product1_a;                   /* '<S14>/Product1' */
  real_T Min;                          /* '<S14>/Min' */
  real_T Switch_a;                     /* '<S12>/Switch' */
  real_T MovingAverage;                /* '<S12>/Moving Average' */
  real_T y;                            /* '<S12>/MATLAB Function' */
  real_T Sum_a;                        /* '<S143>/Sum' */
  real_T Derating;                     /* '<S159>/Derating' */
  real_T Derating_e;                   /* '<S158>/Derating' */
  real_T Saturation_k;                 /* '<S31>/Saturation' */
  real_T Sum_n;                        /* '<S205>/Sum' */
  real_T Sum_b;                        /* '<S258>/Sum' */
  real_T _rreft_l;                     /* '<S29>/Divide4' */
  real_T Multiply_l;                   /* '<S34>/Multiply' */
  real_T Multiply1_p;                  /* '<S34>/Multiply1' */
  real_T _sst;                         /* '<S29>/&#x3C9;_ss(u)' */
  real_T Multiply_g;                   /* '<S33>/Multiply' */
  real_T Multiply1_j;                  /* '<S33>/Multiply1' */
  real_T Multiply_p;                   /* '<S154>/Multiply' */
  real_T Multiply1_e;                  /* '<S154>/Multiply1' */
  real_T Sum_d;                        /* '<S152>/Sum' */
  real_T Product1_n;                   /* '<S152>/Product1' */
  real_T Exp;                          /* '<S152>/Exp' */
  real_T ws;                           /* '<S152>/&#x3B2;(ws)' */
  real_T Gain1_o;                      /* '<S156>/Gain1' */
  real_T Gain_c;                       /* '<S152>/Gain' */
  real_T Product_n;                    /* '<S152>/Product' */
  real_T _drt;                         /* '<S31>/Multiport Switch' */
  real_T _drt_o;                       /* '<S31>/Divide4' */
  real_T _drt_n;                       /* '<S31>/Divide2' */
  real_T Multiply_d;                   /* '<S157>/Multiply' */
  real_T Multiply1_g;                  /* '<S157>/Multiply1' */
  real_T Divide3;                      /* '<S31>/Divide3' */
  real_T Cpt;                          /* '<S279>/Cp(&#x3BB;, &#x3B2;) ' */
  real_T yaw;                          /* '<S15>/True Yaw Offset' */
  op_mode op_mode_m;                   /* '<S12>/Wind Turbine State Machine' */
  uint8_T IC4;                         /* '<S2>/IC4' */
  uint8_T RateTransition4_e;           /* '<S2>/Rate Transition4' */
  boolean_T IC2;                       /* '<S2>/IC2' */
  boolean_T IC3;                       /* '<S2>/IC3' */
  boolean_T RateTransition2_b;         /* '<S2>/Rate Transition2' */
  boolean_T RateTransition3_j;         /* '<S2>/Rate Transition3' */
  boolean_T Compare;                   /* '<S20>/Compare' */
  boolean_T Compare_c;                 /* '<S22>/Compare' */
  boolean_T Compare_j;                 /* '<S21>/Compare' */
  boolean_T OR1;                       /* '<S12>/OR1' */
  boolean_T IsNaN1;                    /* '<S152>/IsNaN1' */
  boolean_T is_not_nan;                /* '<S152>/NOT' */
  boolean_T Compare_m;                 /* '<S24>/Compare' */
  boolean_T Compare_i;                 /* '<S19>/Compare' */
  boolean_T Compare_b;                 /* '<S23>/Compare' */
  boolean_T OR2;                       /* '<S12>/OR2' */
  boolean_T Compare_p;                 /* '<S287>/Compare' */
  boolean_T Compare_a;                 /* '<S288>/Compare' */
  boolean_T OR1_g;                     /* '<S279>/OR1' */
  boolean_T Compare_ie;                /* '<S18>/Compare' */
};

/* Block states (default storage) for system '<Root>/For Each Subsystem' */
struct DW_CoreSubsys_wturbines_T {
  dsp_simulink_MovingAverage_wt_T obj; /* '<S12>/Moving Average' */
  real_T Delay_DSTATE;                 /* '<S29>/Delay' */
  real_T PrevY;                        /* '<S2>/Rate Limiter' */
  real_T PrevY_e;                      /* '<S2>/Rate Limiter1' */
  real_T PrevY_n;                      /* '<S280>/Rate Limiter' */
  real_T RateTransition13_Buf[2];      /* '<S13>/Rate Transition13' */
  real_T RateTransition2_Buf[2];       /* '<S13>/Rate Transition2' */
  real_T RateTransition3_Buf[2];       /* '<S13>/Rate Transition3' */
  real_T PrevY_d;                      /* '<S278>/Rate Limiter' */
  real_T LastMajorTime;                /* '<S278>/Rate Limiter' */
  real_T m_bpLambda[2];                /* '<S15>/Ct(&#x3BB;, &#x3B2;)' */
  real_T m_yyA[20];                    /* '<S15>/Ct(&#x3BB;, &#x3B2;)' */
  real_T m_yyB[20];                    /* '<S15>/Ct(&#x3BB;, &#x3B2;)' */
  real_T m_yy2[20];                    /* '<S15>/Ct(&#x3BB;, &#x3B2;)' */
  real_T m_up[20];                     /* '<S15>/Ct(&#x3BB;, &#x3B2;)' */
  real_T m_y2[400];                    /* '<S15>/Ct(&#x3BB;, &#x3B2;)' */
  real_T prevBp0AndTableData[420];     /* '<S15>/Ct(&#x3BB;, &#x3B2;)' */
  real_T RateTransition_Buf[2];        /* '<S13>/Rate Transition' */
  real_T RateTransition5_Buf[2];       /* '<S13>/Rate Transition5' */
  real_T RateTransition1_Buf[2];       /* '<S13>/Rate Transition1' */
  real_T RateTransition4_Buf[2];       /* '<S13>/Rate Transition4' */
  real_T RateTransition1_Buf_c[2];     /* '<S8>/Rate Transition1' */
  real_T RateTransition7_Buf[16];      /* '<S2>/Rate Transition7' */
  real_T RateTransition6_Buf[2];       /* '<S13>/Rate Transition6' */
  real_T RateTransition7_Buf_h[2];     /* '<S13>/Rate Transition7' */
  real_T RateTransition9_Buf[2];       /* '<S13>/Rate Transition9' */
  real_T RateTransition8_Buf[2];       /* '<S13>/Rate Transition8' */
  real_T RateTransition10_Buf[2];      /* '<S13>/Rate Transition10' */
  real_T RateTransition11_Buf[2];      /* '<S13>/Rate Transition11' */
  real_T RateTransition12_Buf[2];      /* '<S13>/Rate Transition12' */
  real_T RateTransition2_Buf_n[2];     /* '<S8>/Rate Transition2' */
  real_T NextOutput;                   /* '<S11>/White Noise' */
  real_T NextOutput_b;                 /* '<S271>/White Noise' */
  real_T NextOutput_p;                 /* '<S269>/White Noise' */
  real_T NextOutput_i;                 /* '<S272>/White Noise' */
  real_T NextOutput_a;                 /* '<S270>/White Noise' */
  real_T NextOutput_f;                 /* '<S273>/White Noise' */
  real_T NextOutput_m;                 /* '<S274>/White Noise' */
  real_T NextOutput_n;                 /* '<S275>/White Noise' */
  real_T last_val;                     /* '<S12>/MATLAB Function' */
  void* m_bpDataSet[2];                /* '<S15>/Ct(&#x3BB;, &#x3B2;)' */
  void* TWork[6];                      /* '<S15>/Ct(&#x3BB;, &#x3B2;)' */
  void* SWork[9];                      /* '<S15>/Ct(&#x3BB;, &#x3B2;)' */
  struct {
    void *LoggedData;
  } Operationalmode_PWORK;             /* '<S12>/Operational mode' */

  struct {
    void *LoggedData[2];
  } Setpoints_PWORK;                   /* '<S31>/Setpoints' */

  int32_T sfEvent;                     /* '<S12>/MATLAB Function' */
  int32_T sfEvent_g;                   /* '<S12>/Wind Turbine State Machine' */
  int32_T sfEvent_e;                   /* '<S15>/True Yaw Offset' */
  uint32_T m_bpIndex[2];               /* '<S15>/Ct(&#x3BB;, &#x3B2;)' */
  uint32_T RandSeed;                   /* '<S11>/White Noise' */
  uint32_T RandSeed_b;                 /* '<S271>/White Noise' */
  uint32_T RandSeed_p;                 /* '<S269>/White Noise' */
  uint32_T RandSeed_m;                 /* '<S272>/White Noise' */
  uint32_T RandSeed_j;                 /* '<S270>/White Noise' */
  uint32_T RandSeed_l;                 /* '<S273>/White Noise' */
  uint32_T RandSeed_a;                 /* '<S274>/White Noise' */
  uint32_T RandSeed_g;                 /* '<S275>/White Noise' */
  int8_T RateTransition13_RdBufIdx;    /* '<S13>/Rate Transition13' */
  int8_T RateTransition13_WrBufIdx;    /* '<S13>/Rate Transition13' */
  int8_T RateTransition2_RdBufIdx;     /* '<S13>/Rate Transition2' */
  int8_T RateTransition2_WrBufIdx;     /* '<S13>/Rate Transition2' */
  int8_T RateTransition3_RdBufIdx;     /* '<S13>/Rate Transition3' */
  int8_T RateTransition3_WrBufIdx;     /* '<S13>/Rate Transition3' */
  int8_T RateTransition_RdBufIdx;      /* '<S13>/Rate Transition' */
  int8_T RateTransition_WrBufIdx;      /* '<S13>/Rate Transition' */
  int8_T RateTransition5_RdBufIdx;     /* '<S13>/Rate Transition5' */
  int8_T RateTransition5_WrBufIdx;     /* '<S13>/Rate Transition5' */
  int8_T RateTransition1_RdBufIdx;     /* '<S13>/Rate Transition1' */
  int8_T RateTransition1_WrBufIdx;     /* '<S13>/Rate Transition1' */
  int8_T RateTransition4_RdBufIdx;     /* '<S13>/Rate Transition4' */
  int8_T RateTransition4_WrBufIdx;     /* '<S13>/Rate Transition4' */
  int8_T RateTransition1_RdBufIdx_f;   /* '<S8>/Rate Transition1' */
  int8_T RateTransition1_WrBufIdx_f;   /* '<S8>/Rate Transition1' */
  int8_T RateTransition7_RdBufIdx;     /* '<S2>/Rate Transition7' */
  int8_T RateTransition7_WrBufIdx;     /* '<S2>/Rate Transition7' */
  int8_T RateTransition6_RdBufIdx;     /* '<S13>/Rate Transition6' */
  int8_T RateTransition6_WrBufIdx;     /* '<S13>/Rate Transition6' */
  int8_T RateTransition7_RdBufIdx_g;   /* '<S13>/Rate Transition7' */
  int8_T RateTransition7_WrBufIdx_e;   /* '<S13>/Rate Transition7' */
  int8_T RateTransition9_RdBufIdx;     /* '<S13>/Rate Transition9' */
  int8_T RateTransition9_WrBufIdx;     /* '<S13>/Rate Transition9' */
  int8_T RateTransition8_RdBufIdx;     /* '<S13>/Rate Transition8' */
  int8_T RateTransition8_WrBufIdx;     /* '<S13>/Rate Transition8' */
  int8_T RateTransition10_RdBufIdx;    /* '<S13>/Rate Transition10' */
  int8_T RateTransition10_WrBufIdx;    /* '<S13>/Rate Transition10' */
  int8_T RateTransition11_RdBufIdx;    /* '<S13>/Rate Transition11' */
  int8_T RateTransition11_WrBufIdx;    /* '<S13>/Rate Transition11' */
  int8_T RateTransition12_RdBufIdx;    /* '<S13>/Rate Transition12' */
  int8_T RateTransition12_WrBufIdx;    /* '<S13>/Rate Transition12' */
  int8_T RateTransition2_RdBufIdx_i;   /* '<S8>/Rate Transition2' */
  int8_T RateTransition2_WrBufIdx_m;   /* '<S8>/Rate Transition2' */
  uint8_T reCalcSecDerivFirstDimCoeffs;/* '<S15>/Ct(&#x3BB;, &#x3B2;)' */
  uint8_T is_active_c9_wturbines;      /* '<S12>/Wind Turbine State Machine' */
  boolean_T IC_FirstOutputTime;        /* '<S2>/IC' */
  boolean_T IC1_FirstOutputTime;       /* '<S2>/IC1' */
  boolean_T IC2_FirstOutputTime;       /* '<S2>/IC2' */
  boolean_T IC3_FirstOutputTime;       /* '<S2>/IC3' */
  boolean_T IC4_FirstOutputTime;       /* '<S2>/IC4' */
  boolean_T IC5_FirstOutputTime;       /* '<S2>/IC5' */
  boolean_T IC6_FirstOutputTime;       /* '<S2>/IC6' */
  boolean_T IC_FirstOutputTime_l;      /* '<S12>/IC' */
  boolean_T IC_FirstOutputTime_lt;     /* '<S280>/IC' */
  boolean_T PrevLimited;               /* '<S278>/Rate Limiter' */
  boolean_T Relay_Mode;                /* '<S153>/Relay' */
  boolean_T objisempty;                /* '<S12>/Moving Average' */
  boolean_T doneDoubleBufferReInit;    /* '<S12>/MATLAB Function' */
  boolean_T last_val_not_empty;        /* '<S12>/MATLAB Function' */
  boolean_T doneDoubleBufferReInit_b;  /* '<S15>/True Yaw Offset' */
};

/* Continuous states for system '<Root>/For Each Subsystem' */
struct X_CoreSubsys_wturbines_T {
  real_T Integrator_CSTATE;            /* '<S15>/Integrator' */
  real_T Integrator_CSTATE_o;          /* '<S249>/Integrator' */
  real_T Integrator_CSTATE_l;          /* '<S196>/Integrator' */
  real_T Integrator_CSTATE_e;          /* '<S134>/Integrator' */
  real_T Integrator_CSTATE_oj;         /* '<S80>/Integrator' */
  real_T Hcontroller_CSTATE;           /* '<S36>/H&#x221E; controller ' */
};

/* State derivatives for system '<Root>/For Each Subsystem' */
struct XDot_CoreSubsys_wturbines_T {
  real_T Integrator_CSTATE;            /* '<S15>/Integrator' */
  real_T Integrator_CSTATE_o;          /* '<S249>/Integrator' */
  real_T Integrator_CSTATE_l;          /* '<S196>/Integrator' */
  real_T Integrator_CSTATE_e;          /* '<S134>/Integrator' */
  real_T Integrator_CSTATE_oj;         /* '<S80>/Integrator' */
  real_T Hcontroller_CSTATE;           /* '<S36>/H&#x221E; controller ' */
};

/* State Disabled for system '<Root>/For Each Subsystem' */
struct XDis_CoreSubsys_wturbines_T {
  boolean_T Integrator_CSTATE;         /* '<S15>/Integrator' */
  boolean_T Integrator_CSTATE_o;       /* '<S249>/Integrator' */
  boolean_T Integrator_CSTATE_l;       /* '<S196>/Integrator' */
  boolean_T Integrator_CSTATE_e;       /* '<S134>/Integrator' */
  boolean_T Integrator_CSTATE_oj;      /* '<S80>/Integrator' */
  boolean_T Hcontroller_CSTATE;        /* '<S36>/H&#x221E; controller ' */
};

/* Block signals (default storage) */
struct B_wturbines_T {
  loggingDataVectors y;                /* '<Root>/MATLAB Function' */
  loggingData ImpAsg_InsertedFor_log_at_inpor[9];/* '<S2>/Logging' */
  real_T Cp[9];
              /* '<Root>/SigConversion_InsertedFor_Bus Selector_at_outport_0' */
  real_T Ct[9];
              /* '<Root>/SigConversion_InsertedFor_Bus Selector_at_outport_1' */
  real_T TGen[9];
             /* '<Root>/SigConversion_InsertedFor_Bus Selector_at_outport_10' */
  real_T Ta[9];
             /* '<Root>/SigConversion_InsertedFor_Bus Selector_at_outport_11' */
  real_T WsEff[9];
             /* '<Root>/SigConversion_InsertedFor_Bus Selector_at_outport_12' */
  real_T YawTrue[9];
             /* '<Root>/SigConversion_InsertedFor_Bus Selector_at_outport_13' */
  real_T HorWdSpd[9];
             /* '<Root>/SigConversion_InsertedFor_Bus Selector_at_outport_14' */
  real_T HorWdDir[9];
             /* '<Root>/SigConversion_InsertedFor_Bus Selector_at_outport_15' */
  real_T WSpt[9];
             /* '<Root>/SigConversion_InsertedFor_Bus Selector_at_outport_18' */
  real_T GenSpd[9];
              /* '<Root>/SigConversion_InsertedFor_Bus Selector_at_outport_2' */
  real_T OrientationSpt[9];
              /* '<Root>/SigConversion_InsertedFor_Bus Selector_at_outport_4' */
  real_T Pitch[9];
              /* '<Root>/SigConversion_InsertedFor_Bus Selector_at_outport_5' */
  real_T PitchSpt[9];
              /* '<Root>/SigConversion_InsertedFor_Bus Selector_at_outport_6' */
  real_T RotSpd[9];
              /* '<Root>/SigConversion_InsertedFor_Bus Selector_at_outport_7' */
  real_T TBrake[9];
              /* '<Root>/SigConversion_InsertedFor_Bus Selector_at_outport_9' */
  real_T UDPReceive_o2;                /* '<S4>/UDP Receive' */
  real_T UDPReceive_o2_m;              /* '<S5>/UDP Receive' */
  real_T RateTransition[72];           /* '<S6>/Rate Transition' */
  real_T RateTransition_k[18];         /* '<S1>/Rate Transition' */
  real_T ImpAsg_InsertedFor_YawTrue_at_i[9];/* '<S2>/Rate Transition9' */
  real_T ImpAsg_InsertedFor_Ct_at_inport[9];/* '<S2>/Rate Transition8' */
  real_T ImpAsg_InsertedFor_x_at_inport_[72];/* '<S2>/Rate Transition7' */
  real32_T RateTransition1[9];         /* '<S5>/Rate Transition1' */
  real32_T RateTransition2[9];         /* '<S5>/Rate Transition2' */
  real32_T RateTransition1_c[9];       /* '<S4>/Rate Transition1' */
  real32_T RateTransition2_p[9];       /* '<S4>/Rate Transition2' */
  real32_T DataTypeConversion[72];     /* '<S6>/Data Type Conversion' */
  real32_T DataTypeConversion_e[18];   /* '<S1>/Data Type Conversion' */
  real32_T ByteUnpack_o4[9];           /* '<S294>/Byte Unpack' */
  real32_T ByteUnpack_o5[9];           /* '<S294>/Byte Unpack' */
  real32_T ZeroOrderHold3[9];          /* '<S294>/Zero-Order Hold3' */
  real32_T ZeroOrderHold4[9];          /* '<S294>/Zero-Order Hold4' */
  real32_T ByteUnpack_o1[9];           /* '<S290>/Byte Unpack' */
  real32_T ByteUnpack_o2[9];           /* '<S290>/Byte Unpack' */
  real32_T UnitDelay[9];               /* '<S290>/Unit Delay' */
  real32_T UnitDelay1[9];              /* '<S290>/Unit Delay1' */
  real32_T w_filtered[9];              /* '<S290>/ZoH nan filter2' */
  real32_T w_filtered_k[9];            /* '<S290>/ZoH nan filter1' */
  op_mode OpMode[9];
              /* '<Root>/SigConversion_InsertedFor_Bus Selector_at_outport_3' */
  op_mode ImpAsg_InsertedFor_ctrlState_at[9];
  int32_T eCtrlMode[9];
              /* '<Root>/SigConversion_InsertedFor_Bus Selector_at_outport_8' */
  int32_T ForEach;                     /* '<S2>/For Each' */
  uint8_T RateTransition4[9];          /* '<S5>/Rate Transition4' */
  uint8_T UDPReceive_o1[72];           /* '<S4>/UDP Receive' */
  uint8_T UDPReceive_o1_d[99];         /* '<S5>/UDP Receive' */
  uint8_T BytePack1[288];              /* '<S6>/Byte Pack1' */
  uint8_T BytePack1_d[72];             /* '<S1>/Byte Pack1' */
  uint8_T ByteUnpack_o3[9];            /* '<S294>/Byte Unpack' */
  uint8_T ZeroOrderHold2[9];           /* '<S294>/Zero-Order Hold2' */
  boolean_T RateTransition_l[9];       /* '<S5>/Rate Transition' */
  boolean_T RateTransition3[9];        /* '<S5>/Rate Transition3' */
  boolean_T bEnable[9];
             /* '<Root>/SigConversion_InsertedFor_Bus Selector_at_outport_16' */
  boolean_T bStop[9];
             /* '<Root>/SigConversion_InsertedFor_Bus Selector_at_outport_17' */
  boolean_T Compare;                   /* '<S289>/Compare' */
  boolean_T Compare_h;                 /* '<S293>/Compare' */
  boolean_T ByteUnpack_o1_f[9];        /* '<S294>/Byte Unpack' */
  boolean_T ByteUnpack_o2_k[9];        /* '<S294>/Byte Unpack' */
  boolean_T ZeroOrderHold[9];          /* '<S294>/Zero-Order Hold' */
  boolean_T ZeroOrderHold1[9];         /* '<S294>/Zero-Order Hold1' */
  B_CoreSubsys_wturbines_T CoreSubsys[9];/* '<Root>/For Each Subsystem' */
};

/* Block states (default storage) for system '<Root>' */
struct DW_wturbines_T {
  real_T RateTransition_Buf[36];       /* '<S1>/Rate Transition' */
  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_BusSe;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Bus_j;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Bus_d;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Bus_h;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Bus_m;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Bus_e;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Bu_mk;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Bu_e4;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Bus_n;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Bus_b;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Bus_k;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Bu_hw;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Bu_ki;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Bus_a;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Bu_at;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Bu_h2;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Bu_ne;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Bu_nd;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Bu_dd;   /* synthesized block */

  void* UDPReceive_DWORK1;             /* '<S4>/UDP Receive' */
  void *UDPReceive_PWORK[2];           /* '<S4>/UDP Receive' */
  void* UDPReceive_DWORK1_a;           /* '<S5>/UDP Receive' */
  void *UDPReceive_PWORK_k[2];         /* '<S5>/UDP Receive' */
  void* UDPSend1_DWORK1;               /* '<S6>/UDP Send1' */
  void *UDPSend1_PWORK;                /* '<S6>/UDP Send1' */
  void* UDPSend1_DWORK1_b;             /* '<S1>/UDP Send1' */
  void *UDPSend1_PWORK_g;              /* '<S1>/UDP Send1' */
  real32_T UnitDelay_DSTATE[9];        /* '<S290>/Unit Delay' */
  real32_T UnitDelay1_DSTATE[9];       /* '<S290>/Unit Delay1' */
  real32_T RateTransition1_Buf[18];    /* '<S5>/Rate Transition1' */
  real32_T RateTransition2_Buf[18];    /* '<S5>/Rate Transition2' */
  real32_T RateTransition1_Buf_f[18];  /* '<S4>/Rate Transition1' */
  real32_T RateTransition2_Buf_k[18];  /* '<S4>/Rate Transition2' */
  int32_T sfEvent;                     /* '<S290>/ZoH nan filter2' */
  int32_T sfEvent_n;                   /* '<S290>/ZoH nan filter1' */
  int32_T sfEvent_j;                   /* '<Root>/MATLAB Function' */
  int_T UDPReceive_IWORK[3];           /* '<S4>/UDP Receive' */
  int_T UDPReceive_IWORK_d[3];         /* '<S5>/UDP Receive' */
  int_T UDPSend1_IWORK[2];             /* '<S6>/UDP Send1' */
  int_T UDPSend1_IWORK_g[2];           /* '<S1>/UDP Send1' */
  uint16_T UDPSend1_DWORK2;            /* '<S6>/UDP Send1' */
  uint16_T UDPSend1_DWORK2_d;          /* '<S1>/UDP Send1' */
  int8_T RateTransition_RdBufIdx;      /* '<S5>/Rate Transition' */
  int8_T RateTransition_WrBufIdx;      /* '<S5>/Rate Transition' */
  int8_T RateTransition3_RdBufIdx;     /* '<S5>/Rate Transition3' */
  int8_T RateTransition3_WrBufIdx;     /* '<S5>/Rate Transition3' */
  int8_T RateTransition4_RdBufIdx;     /* '<S5>/Rate Transition4' */
  int8_T RateTransition4_WrBufIdx;     /* '<S5>/Rate Transition4' */
  int8_T RateTransition1_RdBufIdx;     /* '<S5>/Rate Transition1' */
  int8_T RateTransition1_WrBufIdx;     /* '<S5>/Rate Transition1' */
  int8_T RateTransition2_RdBufIdx;     /* '<S5>/Rate Transition2' */
  int8_T RateTransition2_WrBufIdx;     /* '<S5>/Rate Transition2' */
  int8_T RateTransition1_RdBufIdx_k;   /* '<S4>/Rate Transition1' */
  int8_T RateTransition1_WrBufIdx_g;   /* '<S4>/Rate Transition1' */
  int8_T RateTransition2_RdBufIdx_c;   /* '<S4>/Rate Transition2' */
  int8_T RateTransition2_WrBufIdx_g;   /* '<S4>/Rate Transition2' */
  int8_T RateTransition_RdBufIdx_e;    /* '<S1>/Rate Transition' */
  int8_T RateTransition_WrBufIdx_j;    /* '<S1>/Rate Transition' */
  int8_T EnabledSubsystem_SubsysRanBC; /* '<S5>/Enabled Subsystem' */
  int8_T EnabledSubsystem_SubsysRanBC_i;/* '<S4>/Enabled Subsystem' */
  uint8_T RateTransition4_Buf[18];     /* '<S5>/Rate Transition4' */
  boolean_T RateTransition_Buf_n[18];  /* '<S5>/Rate Transition' */
  boolean_T RateTransition3_Buf[18];   /* '<S5>/Rate Transition3' */
  boolean_T doneDoubleBufferReInit;    /* '<S290>/ZoH nan filter2' */
  boolean_T doneDoubleBufferReInit_e;  /* '<S290>/ZoH nan filter1' */
  boolean_T doneDoubleBufferReInit_o;  /* '<Root>/MATLAB Function' */
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
 * '<S3>'   : 'wturbines/MATLAB Function'
 * '<S4>'   : 'wturbines/RX FlowField Conditions'
 * '<S5>'   : 'wturbines/Receive Turbine CMD'
 * '<S6>'   : 'wturbines/Send Turbine Data to PLC'
 * '<S7>'   : 'wturbines/For Each Subsystem/Logging'
 * '<S8>'   : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1'
 * '<S9>'   : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/  '
 * '<S10>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/  1'
 * '<S11>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Band-Limited White Noise4'
 * '<S12>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic'
 * '<S13>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Measurements'
 * '<S14>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Subsystem'
 * '<S15>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Turbine Dynamics'
 * '<S16>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/  /Radians to Degrees'
 * '<S17>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/     '
 * '<S18>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Compare To Constant'
 * '<S19>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Compare To Constant10'
 * '<S20>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Compare To Constant3'
 * '<S21>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Compare To Constant4'
 * '<S22>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Compare To Constant5'
 * '<S23>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Compare To Constant6'
 * '<S24>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Compare To Constant9'
 * '<S25>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/MATLAB Function'
 * '<S26>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller'
 * '<S27>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Wind Turbine State Machine'
 * '<S28>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/     /Degrees to Radians'
 * '<S29>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control '
 * '<S30>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/K&#x3C9;2 controller'
 * '<S31>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation'
 * '<S32>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/ROSCO'
 * '<S33>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control / '
 * '<S34>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /  '
 * '<S35>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller'
 * '<S36>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller'
 * '<S37>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/Gain scheduler'
 * '<S38>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller'
 * '<S39>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/rad2deg'
 * '<S40>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/Gain scheduler/DGain Lookup'
 * '<S41>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/Gain scheduler/IGain Lookup'
 * '<S42>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/Gain scheduler/NGain Lookup'
 * '<S43>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/Gain scheduler/PGain Lookup'
 * '<S44>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/Gain scheduler/IGain Lookup/Enabled'
 * '<S45>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/Gain scheduler/PGain Lookup/Enabled'
 * '<S46>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Anti-windup'
 * '<S47>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/D Gain'
 * '<S48>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/External Derivative'
 * '<S49>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Filter'
 * '<S50>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Filter ICs'
 * '<S51>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/I Gain'
 * '<S52>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Ideal P Gain'
 * '<S53>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Ideal P Gain Fdbk'
 * '<S54>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Integrator'
 * '<S55>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Integrator ICs'
 * '<S56>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/N Copy'
 * '<S57>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/N Gain'
 * '<S58>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/P Copy'
 * '<S59>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Parallel P Gain'
 * '<S60>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Reset Signal'
 * '<S61>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Saturation'
 * '<S62>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Saturation Fdbk'
 * '<S63>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Sum'
 * '<S64>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Sum Fdbk'
 * '<S65>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Tracking Mode'
 * '<S66>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Tracking Mode Sum'
 * '<S67>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Tsamp - Integral'
 * '<S68>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Tsamp - Ngain'
 * '<S69>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/postSat Signal'
 * '<S70>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/preInt Signal'
 * '<S71>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/preSat Signal'
 * '<S72>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Anti-windup/Passthrough'
 * '<S73>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/D Gain/Disabled'
 * '<S74>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/External Derivative/Disabled'
 * '<S75>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Filter/Disabled'
 * '<S76>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Filter ICs/Disabled'
 * '<S77>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/I Gain/External Parameters'
 * '<S78>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Ideal P Gain/Passthrough'
 * '<S79>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Ideal P Gain Fdbk/Disabled'
 * '<S80>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Integrator/Continuous'
 * '<S81>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Integrator ICs/Internal IC'
 * '<S82>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/N Copy/Disabled wSignal Specification'
 * '<S83>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/N Gain/Disabled'
 * '<S84>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/P Copy/Disabled'
 * '<S85>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Parallel P Gain/External Parameters'
 * '<S86>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Reset Signal/Disabled'
 * '<S87>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Saturation/Passthrough'
 * '<S88>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Saturation Fdbk/Disabled'
 * '<S89>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Sum/Sum_PI'
 * '<S90>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Sum Fdbk/Disabled'
 * '<S91>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Tracking Mode/Disabled'
 * '<S92>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Tracking Mode Sum/Passthrough'
 * '<S93>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S94>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/Tsamp - Ngain/Passthrough'
 * '<S95>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/postSat Signal/Forward_Path'
 * '<S96>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/preInt Signal/Internal PreInt'
 * '<S97>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/PI Controller/preSat Signal/Forward_Path'
 * '<S98>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Pitch controller/rad2deg/Radians to Degrees'
 * '<S99>'  : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller'
 * '<S100>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Anti-windup'
 * '<S101>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/D Gain'
 * '<S102>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/External Derivative'
 * '<S103>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Filter'
 * '<S104>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Filter ICs'
 * '<S105>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/I Gain'
 * '<S106>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Ideal P Gain'
 * '<S107>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Ideal P Gain Fdbk'
 * '<S108>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Integrator'
 * '<S109>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Integrator ICs'
 * '<S110>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/N Copy'
 * '<S111>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/N Gain'
 * '<S112>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/P Copy'
 * '<S113>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Parallel P Gain'
 * '<S114>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Reset Signal'
 * '<S115>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Saturation'
 * '<S116>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Saturation Fdbk'
 * '<S117>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Sum'
 * '<S118>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Sum Fdbk'
 * '<S119>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Tracking Mode'
 * '<S120>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Tracking Mode Sum'
 * '<S121>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Tsamp - Integral'
 * '<S122>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Tsamp - Ngain'
 * '<S123>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/postSat Signal'
 * '<S124>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/preInt Signal'
 * '<S125>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/preSat Signal'
 * '<S126>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Anti-windup/Passthrough'
 * '<S127>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/D Gain/Disabled'
 * '<S128>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/External Derivative/Disabled'
 * '<S129>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Filter/Disabled'
 * '<S130>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Filter ICs/Disabled'
 * '<S131>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/I Gain/Internal Parameters'
 * '<S132>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Ideal P Gain/Passthrough'
 * '<S133>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Ideal P Gain Fdbk/Disabled'
 * '<S134>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Integrator/Continuous'
 * '<S135>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Integrator ICs/Internal IC'
 * '<S136>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/N Copy/Disabled wSignal Specification'
 * '<S137>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/N Gain/Disabled'
 * '<S138>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/P Copy/Disabled'
 * '<S139>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Parallel P Gain/Internal Parameters'
 * '<S140>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Reset Signal/Disabled'
 * '<S141>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Saturation/Passthrough'
 * '<S142>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Saturation Fdbk/Disabled'
 * '<S143>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Sum/Sum_PI'
 * '<S144>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Sum Fdbk/Disabled'
 * '<S145>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Tracking Mode/Disabled'
 * '<S146>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Tracking Mode Sum/Passthrough'
 * '<S147>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Tsamp - Integral/TsSignalSpecification'
 * '<S148>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/Tsamp - Ngain/Passthrough'
 * '<S149>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/postSat Signal/Forward_Path'
 * '<S150>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/preInt Signal/Internal PreInt'
 * '<S151>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Gain-scheduled H&#x221E; control /Torque controller/PI controller/preSat Signal/Forward_Path'
 * '<S152>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/K&#x3C9;2 controller/Pitch controller'
 * '<S153>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/K&#x3C9;2 controller/Torque controller'
 * '<S154>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/K&#x3C9;2 controller/Pitch controller/  '
 * '<S155>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/K&#x3C9;2 controller/Pitch controller/rad2deg'
 * '<S156>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/K&#x3C9;2 controller/Pitch controller/rad2deg/Degrees to Radians'
 * '<S157>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/  '
 * '<S158>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller'
 * '<S159>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller'
 * '<S160>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/rads2rpm'
 * '<S161>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller'
 * '<S162>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Anti-windup'
 * '<S163>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/D Gain'
 * '<S164>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/External Derivative'
 * '<S165>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Filter'
 * '<S166>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Filter ICs'
 * '<S167>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/I Gain'
 * '<S168>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Ideal P Gain'
 * '<S169>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Ideal P Gain Fdbk'
 * '<S170>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Integrator'
 * '<S171>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Integrator ICs'
 * '<S172>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/N Copy'
 * '<S173>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/N Gain'
 * '<S174>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/P Copy'
 * '<S175>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Parallel P Gain'
 * '<S176>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Reset Signal'
 * '<S177>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Saturation'
 * '<S178>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Saturation Fdbk'
 * '<S179>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Sum'
 * '<S180>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Sum Fdbk'
 * '<S181>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Tracking Mode'
 * '<S182>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Tracking Mode Sum'
 * '<S183>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Tsamp - Integral'
 * '<S184>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Tsamp - Ngain'
 * '<S185>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/postSat Signal'
 * '<S186>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/preInt Signal'
 * '<S187>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/preSat Signal'
 * '<S188>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Anti-windup/Passthrough'
 * '<S189>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/D Gain/Disabled'
 * '<S190>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/External Derivative/Disabled'
 * '<S191>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Filter/Disabled'
 * '<S192>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Filter ICs/Disabled'
 * '<S193>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/I Gain/Internal Parameters'
 * '<S194>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Ideal P Gain/Passthrough'
 * '<S195>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Ideal P Gain Fdbk/Disabled'
 * '<S196>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Integrator/Continuous'
 * '<S197>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Integrator ICs/Internal IC'
 * '<S198>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/N Copy/Disabled wSignal Specification'
 * '<S199>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/N Gain/Disabled'
 * '<S200>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/P Copy/Disabled'
 * '<S201>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Parallel P Gain/Internal Parameters'
 * '<S202>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Reset Signal/Disabled'
 * '<S203>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Saturation/Passthrough'
 * '<S204>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Saturation Fdbk/Disabled'
 * '<S205>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Sum/Sum_PI'
 * '<S206>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Sum Fdbk/Disabled'
 * '<S207>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Tracking Mode/Disabled'
 * '<S208>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Tracking Mode Sum/Passthrough'
 * '<S209>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Tsamp - Integral/TsSignalSpecification'
 * '<S210>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/Tsamp - Ngain/Passthrough'
 * '<S211>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/postSat Signal/Forward_Path'
 * '<S212>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/preInt Signal/Internal PreInt'
 * '<S213>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Pitch controller/PI controller/preSat Signal/Forward_Path'
 * '<S214>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller'
 * '<S215>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Anti-windup'
 * '<S216>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/D Gain'
 * '<S217>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/External Derivative'
 * '<S218>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Filter'
 * '<S219>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Filter ICs'
 * '<S220>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/I Gain'
 * '<S221>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Ideal P Gain'
 * '<S222>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Ideal P Gain Fdbk'
 * '<S223>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Integrator'
 * '<S224>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Integrator ICs'
 * '<S225>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/N Copy'
 * '<S226>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/N Gain'
 * '<S227>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/P Copy'
 * '<S228>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Parallel P Gain'
 * '<S229>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Reset Signal'
 * '<S230>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Saturation'
 * '<S231>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Saturation Fdbk'
 * '<S232>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Sum'
 * '<S233>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Sum Fdbk'
 * '<S234>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Tracking Mode'
 * '<S235>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Tracking Mode Sum'
 * '<S236>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Tsamp - Integral'
 * '<S237>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Tsamp - Ngain'
 * '<S238>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/postSat Signal'
 * '<S239>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/preInt Signal'
 * '<S240>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/preSat Signal'
 * '<S241>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Anti-windup/Passthrough'
 * '<S242>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/D Gain/Disabled'
 * '<S243>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/External Derivative/Disabled'
 * '<S244>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Filter/Disabled'
 * '<S245>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Filter ICs/Disabled'
 * '<S246>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/I Gain/Internal Parameters'
 * '<S247>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Ideal P Gain/Passthrough'
 * '<S248>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Ideal P Gain Fdbk/Disabled'
 * '<S249>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Integrator/Continuous'
 * '<S250>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Integrator ICs/Internal IC'
 * '<S251>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/N Copy/Disabled wSignal Specification'
 * '<S252>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/N Gain/Disabled'
 * '<S253>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/P Copy/Disabled'
 * '<S254>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Parallel P Gain/Internal Parameters'
 * '<S255>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Reset Signal/Disabled'
 * '<S256>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Saturation/Passthrough'
 * '<S257>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Saturation Fdbk/Disabled'
 * '<S258>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Sum/Sum_PI'
 * '<S259>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Sum Fdbk/Disabled'
 * '<S260>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Tracking Mode/Disabled'
 * '<S261>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Tracking Mode Sum/Passthrough'
 * '<S262>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Tsamp - Integral/TsSignalSpecification'
 * '<S263>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/Tsamp - Ngain/Passthrough'
 * '<S264>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/postSat Signal/Forward_Path'
 * '<S265>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/preInt Signal/Internal PreInt'
 * '<S266>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/Lio downregulation/Torque controller/PI controller/preSat Signal/Forward_Path'
 * '<S267>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/ROSCO/Pitch controller'
 * '<S268>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Control logic/Power controller/ROSCO/Torque controller'
 * '<S269>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Measurements/Band-Limited White Noise'
 * '<S270>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Measurements/Band-Limited White Noise1'
 * '<S271>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Measurements/Band-Limited White Noise2'
 * '<S272>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Measurements/Band-Limited White Noise3'
 * '<S273>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Measurements/Band-Limited White Noise4'
 * '<S274>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Measurements/Band-Limited White Noise5'
 * '<S275>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Measurements/Band-Limited White Noise6'
 * '<S276>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Turbine Dynamics/  '
 * '<S277>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Turbine Dynamics/     '
 * '<S278>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Turbine Dynamics/Collective Pitch Dynamics'
 * '<S279>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Turbine Dynamics/Cp(&#x3BB;, &#x3B2;)'
 * '<S280>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Turbine Dynamics/Orientation Dynamics'
 * '<S281>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Turbine Dynamics/P(t)'
 * '<S282>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Turbine Dynamics/T_a(t)'
 * '<S283>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Turbine Dynamics/True Yaw Offset'
 * '<S284>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Turbine Dynamics/&#x3BB;(t)'
 * '<S285>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Turbine Dynamics/  /Radians to Degrees'
 * '<S286>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Turbine Dynamics/     /Degrees to Radians'
 * '<S287>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Turbine Dynamics/Cp(&#x3BB;, &#x3B2;)/Compare To Constant2'
 * '<S288>' : 'wturbines/For Each Subsystem/Turbine Dynamics + Controller1/Turbine Dynamics/Cp(&#x3BB;, &#x3B2;)/Compare To Constant3'
 * '<S289>' : 'wturbines/RX FlowField Conditions/Compare To Constant'
 * '<S290>' : 'wturbines/RX FlowField Conditions/Enabled Subsystem'
 * '<S291>' : 'wturbines/RX FlowField Conditions/Enabled Subsystem/ZoH nan filter1'
 * '<S292>' : 'wturbines/RX FlowField Conditions/Enabled Subsystem/ZoH nan filter2'
 * '<S293>' : 'wturbines/Receive Turbine CMD/Compare To Constant'
 * '<S294>' : 'wturbines/Receive Turbine CMD/Enabled Subsystem'
 */
#endif                                 /* wturbines_h_ */
