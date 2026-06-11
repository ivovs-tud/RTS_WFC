#ifndef wturbines_cal_h_
#define wturbines_cal_h_
#include "rtwtypes.h"
#include "wturbines_types.h"

/* Storage class 'PageSwitching', for system '<Root>/For Each Subsystem' */
struct wturbines_CoreSubsys_cal_type {
  real_T Gainscheduler_GainArrayBreakpoi[2];
                              /* Mask Parameter: Gainscheduler_GainArrayBreakpoi
                               * Referenced by: '<S35>/Internal breakpoints'
                               */
  real_T Gains_Value[2];               /* Expression: [1 3]
                                        * Referenced by: '<S33>/Gains'
                                        */
  real_T BandLimitedWhiteNoise_Cov; /* Mask Parameter: BandLimitedWhiteNoise_Cov
                                     * Referenced by: '<S267>/Output'
                                     */
  real_T BandLimitedWhiteNoise1_Cov;
                                   /* Mask Parameter: BandLimitedWhiteNoise1_Cov
                                    * Referenced by: '<S268>/Output'
                                    */
  real_T PIcontroller_InitialConditionFo;
                              /* Mask Parameter: PIcontroller_InitialConditionFo
                               * Referenced by: '<S247>/Integrator'
                               */
  real_T PIcontroller_InitialCondition_i;
                              /* Mask Parameter: PIcontroller_InitialCondition_i
                               * Referenced by: '<S194>/Integrator'
                               */
  real_T PIcontroller_InitialCondition_g;
                              /* Mask Parameter: PIcontroller_InitialCondition_g
                               * Referenced by: '<S132>/Integrator'
                               */
  real_T PIController_InitialConditionFo;
                              /* Mask Parameter: PIController_InitialConditionFo
                               * Referenced by: '<S78>/Integrator'
                               */
  real_T CompareToConstant2_const;   /* Mask Parameter: CompareToConstant2_const
                                      * Referenced by: '<S280>/Constant'
                                      */
  real_T CompareToConstant3_const;   /* Mask Parameter: CompareToConstant3_const
                                      * Referenced by: '<S281>/Constant'
                                      */
  real_T BandLimitedWhiteNoise_seed;
                                   /* Mask Parameter: BandLimitedWhiteNoise_seed
                                    * Referenced by: '<S267>/White Noise'
                                    */
  real_T BandLimitedWhiteNoise1_seed;
                                  /* Mask Parameter: BandLimitedWhiteNoise1_seed
                                   * Referenced by: '<S268>/White Noise'
                                   */
  real_T Multiply_Gain;                /* Expression: 2 * pi
                                        * Referenced by: '<S155>/Multiply'
                                        */
  real_T Multiply1_Gain;               /* Expression: 1 / 60
                                        * Referenced by: '<S155>/Multiply1'
                                        */
  real_T Constant13_Value;             /* Expression: 0
                                        * Referenced by: '<S29>/Constant13'
                                        */
  real_T Multiply_Gain_c;              /* Expression: 2 * pi
                                        * Referenced by: '<S152>/Multiply'
                                        */
  real_T Multiply1_Gain_f;             /* Expression: 1 / 60
                                        * Referenced by: '<S152>/Multiply1'
                                        */
  real_T Gain1_Gain;                   /* Expression: pi/180
                                        * Referenced by: '<S154>/Gain1'
                                        */
  real_T Constant2_Value;              /* Expression: 0
                                        * Referenced by: '<S150>/Constant2'
                                        */
  real_T Multiply_Gain_e;              /* Expression: 2 * pi
                                        * Referenced by: '<S31>/Multiply'
                                        */
  real_T Multiply1_Gain_d;             /* Expression: 1 / 60
                                        * Referenced by: '<S31>/Multiply1'
                                        */
  real_T Multiply_Gain_m;              /* Expression: 2 * pi
                                        * Referenced by: '<S32>/Multiply'
                                        */
  real_T Multiply1_Gain_a;             /* Expression: 1 / 60
                                        * Referenced by: '<S32>/Multiply1'
                                        */
  real_T Constant13_Value_n;           /* Expression: 0
                                        * Referenced by: '<S27>/Constant13'
                                        */
  real_T Derating_Threshold;           /* Expression: 0
                                        * Referenced by: '<S157>/Derating'
                                        */
  real_T Derating_Threshold_c;         /* Expression: 0
                                        * Referenced by: '<S156>/Derating'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 15 * (2 * pi / 360)
                                        * Referenced by: '<S29>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -2 * (2 * pi / 360)
                                        * Referenced by: '<S29>/Saturation'
                                        */
  real_T Constant_Value;               /* Expression: 0
                                        * Referenced by: '<S9>/Constant'
                                        */
  real_T IC_Value;                     /* Expression: 0
                                        * Referenced by: '<S2>/IC'
                                        */
  real_T IC1_Value;                    /* Expression: -1
                                        * Referenced by: '<S2>/IC1'
                                        */
  real_T IC5_Value;                    /* Expression: 0
                                        * Referenced by: '<S2>/IC5'
                                        */
  real_T IC6_Value;                    /* Expression: 0
                                        * Referenced by: '<S2>/IC6'
                                        */
  real_T Integrator_IC;                /* Expression: 0
                                        * Referenced by: '<S11>/Integrator'
                                        */
  real_T Saturation_UpperSat_e;        /* Expression: inf
                                        * Referenced by: '<S11>/Saturation'
                                        */
  real_T Saturation_LowerSat_e;        /* Expression: 0
                                        * Referenced by: '<S11>/Saturation'
                                        */
  real_T RateLimiter_RisingLim;        /* Expression: inf
                                        * Referenced by: '<S2>/Rate Limiter'
                                        */
  real_T RateLimiter_FallingLim;       /* Expression: -inf
                                        * Referenced by: '<S2>/Rate Limiter'
                                        */
  real_T RateLimiter_IC;               /* Expression: 0
                                        * Referenced by: '<S2>/Rate Limiter'
                                        */
  real_T RateLimiter1_RisingLim;       /* Expression: inf
                                        * Referenced by: '<S2>/Rate Limiter1'
                                        */
  real_T RateLimiter1_FallingLim;      /* Expression: -inf
                                        * Referenced by: '<S2>/Rate Limiter1'
                                        */
  real_T RateLimiter1_IC;              /* Expression: 0
                                        * Referenced by: '<S2>/Rate Limiter1'
                                        */
  real_T RateLimiter_IC_e;             /* Expression: 0
                                        * Referenced by: '<S273>/Rate Limiter'
                                        */
  real_T Gain1_Gain_e;                 /* Expression: pi/180
                                        * Referenced by: '<S279>/Gain1'
                                        */
  real_T Saturation2_UpperSat;         /* Expression: inf
                                        * Referenced by: '<S11>/Saturation2'
                                        */
  real_T Saturation2_LowerSat;         /* Expression: 0
                                        * Referenced by: '<S11>/Saturation2'
                                        */
  real_T Constant4_Value;              /* Expression: 90
                                        * Referenced by: '<S9>/Constant4'
                                        */
  real_T Gain1_Gain_j;                 /* Expression: pi/180
                                        * Referenced by: '<S26>/Gain1'
                                        */
  real_T Saturation_LowerSat_h;        /* Expression: 0
                                        * Referenced by: '<S6>/Saturation'
                                        */
  real_T Switch_Threshold;             /* Expression: 0
                                        * Referenced by: '<S6>/Switch'
                                        */
  real_T Constant4_Value_g;            /* Expression: 1/2
                                        * Referenced by: '<S29>/Constant4'
                                        */
  real_T Constant6_Value;              /* Expression: pi
                                        * Referenced by: '<S29>/Constant6'
                                        */
  real_T Constant3_Value;              /* Expression: 1/3
                                        * Referenced by: '<S29>/Constant3'
                                        */
  real_T Derating_Threshold_l;         /* Expression: 0
                                        * Referenced by: '<S29>/Derating'
                                        */
  real_T Constant_Value_l;             /* Expression: 0
                                        * Referenced by: '<S156>/Constant'
                                        */
  real_T Delay_InitialCondition;       /* Expression: 0.0
                                        * Referenced by: '<S27>/Delay'
                                        */
  real_T Gain_Gain;                    /* Expression: 180/pi
                                        * Referenced by: '<S96>/Gain'
                                        */
  real_T RateLimiter_RisingLim_m;      /* Expression: 1
                                        * Referenced by: '<S271>/Rate Limiter'
                                        */
  real_T RateLimiter_FallingLim_e;     /* Expression: -1
                                        * Referenced by: '<S271>/Rate Limiter'
                                        */
  real_T Gain_Gain_f;                  /* Expression: 180/pi
                                        * Referenced by: '<S278>/Gain'
                                        */
  real_T Saturation1_UpperSat;         /* Expression: inf
                                        * Referenced by: '<S11>/Saturation1'
                                        */
  real_T Saturation1_LowerSat;         /* Expression: 0
                                        * Referenced by: '<S11>/Saturation1'
                                        */
  real_T RateTransition5_InitialConditio;/* Expression: 0
                                          * Referenced by: '<S10>/Rate Transition5'
                                          */
  real_T Constant5_Value;              /* Expression: 0
                                        * Referenced by: '<S9>/Constant5'
                                        */
  real_T Constant2_Value_d;            /* Expression: 0
                                        * Referenced by: '<S9>/Constant2'
                                        */
  real_T Saturation_LowerSat_c;        /* Expression: 0
                                        * Referenced by: '<S9>/Saturation'
                                        */
  real_T RateTransition1_InitialConditio;/* Expression: 0
                                          * Referenced by: '<S10>/Rate Transition1'
                                          */
  real_T Gain_Gain_d;                  /* Expression: 60/(2*pi)
                                        * Referenced by: '<S8>/Gain'
                                        */
  real_T Gain_Gain_i;                  /* Expression: 180/pi
                                        * Referenced by: '<S12>/Gain'
                                        */
  real_T RateTransition7_InitialConditio;/* Expression: 0
                                          * Referenced by: '<S2>/Rate Transition7'
                                          */
  real_T Hcontroller_InitialCondition; /* Expression: 0
                                        * Referenced by: '<S34>/H&#x221E; controller '
                                        */
  real_T Multiply_Gain_g;              /* Expression: 1 / (2 * pi)
                                        * Referenced by: '<S158>/Multiply'
                                        */
  real_T Multiply1_Gain_o;             /* Expression: 60
                                        * Referenced by: '<S158>/Multiply1'
                                        */
  real_T RateTransition7_InitialCondit_j;/* Expression: 0
                                          * Referenced by: '<S10>/Rate Transition7'
                                          */
  real_T RateTransition8_InitialConditio;/* Expression: 0
                                          * Referenced by: '<S10>/Rate Transition8'
                                          */
  real_T Constant_Value_j;             /* Expression: 0.001
                                        * Referenced by: '<S275>/Constant'
                                        */
  real_T Constant4_Value_d;            /* Expression: 1/2
                                        * Referenced by: '<S275>/Constant4'
                                        */
  real_T Constant_Value_h;             /* Expression: 0
                                        * Referenced by: '<S272>/Constant'
                                        */
  real_T Saturation_UpperSat_g;        /* Expression: 1
                                        * Referenced by: '<S272>/Saturation'
                                        */
  real_T Saturation_LowerSat_j;        /* Expression: 0
                                        * Referenced by: '<S272>/Saturation'
                                        */
  real_T Constant6_Value_l;            /* Expression: pi
                                        * Referenced by: '<S275>/Constant6'
                                        */
  real_T Constant8_Value;              /* Expression: 3
                                        * Referenced by: '<S275>/Constant8'
                                        */
  real_T Saturation_LowerSat_k;        /* Expression: 0
                                        * Referenced by: '<S275>/Saturation'
                                        */
  real_T Friction_Gain;                /* Expression: 0
                                        * Referenced by: '<S11>/Friction'
                                        */
  real_T WhiteNoise_Mean;              /* Expression: 0
                                        * Referenced by: '<S267>/White Noise'
                                        */
  real_T WhiteNoise_StdDev;            /* Computed Parameter: WhiteNoise_StdDev
                                        * Referenced by: '<S267>/White Noise'
                                        */
  real_T WhiteNoise_Mean_h;            /* Expression: 0
                                        * Referenced by: '<S268>/White Noise'
                                        */
  real_T WhiteNoise_StdDev_a;         /* Computed Parameter: WhiteNoise_StdDev_a
                                       * Referenced by: '<S268>/White Noise'
                                       */
  uint32_T Cp_maxIndex[2];             /* Computed Parameter: Cp_maxIndex
                                        * Referenced by: '<S272>/Cp(&#x3BB;, &#x3B2;) '
                                        */
  uint32_T Ct_maxIndex[2];             /* Computed Parameter: Ct_maxIndex
                                        * Referenced by: '<S11>/Ct(&#x3BB;, &#x3B2;)'
                                        */
  uint32_T Ct_dimSizes[2];             /* Computed Parameter: Ct_dimSizes
                                        * Referenced by: '<S11>/Ct(&#x3BB;, &#x3B2;)'
                                        */
  uint32_T Ct_numYWorkElts[3];         /* Computed Parameter: Ct_numYWorkElts
                                        * Referenced by: '<S11>/Ct(&#x3BB;, &#x3B2;)'
                                        */
  op_mode CompareToConstant3_const_a;
                                   /* Mask Parameter: CompareToConstant3_const_a
                                    * Referenced by: '<S17>/Constant'
                                    */
  op_mode CompareToConstant5_const;  /* Mask Parameter: CompareToConstant5_const
                                      * Referenced by: '<S19>/Constant'
                                      */
  op_mode CompareToConstant4_const;  /* Mask Parameter: CompareToConstant4_const
                                      * Referenced by: '<S18>/Constant'
                                      */
  op_mode CompareToConstant7_const;  /* Mask Parameter: CompareToConstant7_const
                                      * Referenced by: '<S21>/Constant'
                                      */
  op_mode CompareToConstant1_const;  /* Mask Parameter: CompareToConstant1_const
                                      * Referenced by: '<S15>/Constant'
                                      */
  op_mode CompareToConstant2_const_l;
                                   /* Mask Parameter: CompareToConstant2_const_l
                                    * Referenced by: '<S16>/Constant'
                                    */
  op_mode CompareToConstant_const;    /* Mask Parameter: CompareToConstant_const
                                       * Referenced by: '<S14>/Constant'
                                       */
  op_mode CompareToConstant6_const;  /* Mask Parameter: CompareToConstant6_const
                                      * Referenced by: '<S20>/Constant'
                                      */
  uint8_T CompareToConstant8_const;  /* Mask Parameter: CompareToConstant8_const
                                      * Referenced by: '<S22>/Constant'
                                      */
  uint8_T IC4_Value;                   /* Computed Parameter: IC4_Value
                                        * Referenced by: '<S2>/IC4'
                                        */
  boolean_T IC2_Value;                 /* Expression: false
                                        * Referenced by: '<S2>/IC2'
                                        */
  boolean_T IC3_Value;                 /* Expression: false
                                        * Referenced by: '<S2>/IC3'
                                        */
};

/* Storage class 'PageSwitching', for system '<Root>' */
struct wturbines_cal_type {
  wturbines_CoreSubsys_cal_type wturbines_CoreSubsys_cal;/* '<Root>/For Each Subsystem' */
  real_T CompareToConstant_const;     /* Mask Parameter: CompareToConstant_const
                                       * Referenced by: '<S282>/Constant'
                                       */
  real_T CompareToConstant_const_m; /* Mask Parameter: CompareToConstant_const_m
                                     * Referenced by: '<S286>/Constant'
                                     */
  real_T RateTransition_InitialCondition;/* Expression: 0
                                          * Referenced by: '<S1>/Rate Transition'
                                          */
  real32_T WindSpeed_Y0;               /* Computed Parameter: WindSpeed_Y0
                                        * Referenced by: '<S283>/WindSpeed'
                                        */
  real32_T WindDirection_Y0;           /* Computed Parameter: WindDirection_Y0
                                        * Referenced by: '<S283>/Wind Direction'
                                        */
  real32_T UnitDelay_InitialCondition;
                               /* Computed Parameter: UnitDelay_InitialCondition
                                * Referenced by: '<S283>/Unit Delay'
                                */
  real32_T UnitDelay1_InitialCondition;
                              /* Computed Parameter: UnitDelay1_InitialCondition
                               * Referenced by: '<S283>/Unit Delay1'
                               */
  real32_T fPowerSpt_Y0;               /* Computed Parameter: fPowerSpt_Y0
                                        * Referenced by: '<S287>/fPowerSpt'
                                        */
  real32_T fYawSpt_Y0;                 /* Computed Parameter: fYawSpt_Y0
                                        * Referenced by: '<S287>/fYawSpt'
                                        */
  real32_T RateTransition1_InitialConditio;
                          /* Computed Parameter: RateTransition1_InitialConditio
                           * Referenced by: '<S4>/Rate Transition1'
                           */
  real32_T RateTransition2_InitialConditio;
                          /* Computed Parameter: RateTransition2_InitialConditio
                           * Referenced by: '<S4>/Rate Transition2'
                           */
  real32_T RateTransition1_InitialCondit_k;
                          /* Computed Parameter: RateTransition1_InitialCondit_k
                           * Referenced by: '<S3>/Rate Transition1'
                           */
  real32_T RateTransition2_InitialCondit_d;
                          /* Computed Parameter: RateTransition2_InitialCondit_d
                           * Referenced by: '<S3>/Rate Transition2'
                           */
  uint16_T UDPSend1_toPort;            /* Computed Parameter: UDPSend1_toPort
                                        * Referenced by: '<S5>/UDP Send1'
                                        */
  uint16_T UDPSend1_toPort_i;          /* Computed Parameter: UDPSend1_toPort_i
                                        * Referenced by: '<S1>/UDP Send1'
                                        */
  uint8_T UDPReceive_fmAddress[4];   /* Computed Parameter: UDPReceive_fmAddress
                                      * Referenced by: '<S3>/UDP Receive'
                                      */
  uint8_T UDPReceive_fmAddress_f[4];
                                   /* Computed Parameter: UDPReceive_fmAddress_f
                                    * Referenced by: '<S4>/UDP Receive'
                                    */
  uint8_T UDPSend1_toAddress[4];       /* Computed Parameter: UDPSend1_toAddress
                                        * Referenced by: '<S5>/UDP Send1'
                                        */
  uint8_T UDPSend1_toAddress_b[4];   /* Computed Parameter: UDPSend1_toAddress_b
                                      * Referenced by: '<S1>/UDP Send1'
                                      */
  uint8_T eCTRL_MODE_Y0;               /* Computed Parameter: eCTRL_MODE_Y0
                                        * Referenced by: '<S287>/eCTRL_MODE'
                                        */
  uint8_T RateTransition4_InitialConditio;
                          /* Computed Parameter: RateTransition4_InitialConditio
                           * Referenced by: '<S4>/Rate Transition4'
                           */
  boolean_T bEnable_Y0;                /* Computed Parameter: bEnable_Y0
                                        * Referenced by: '<S287>/bEnable'
                                        */
  boolean_T bStop_Y0;                  /* Computed Parameter: bStop_Y0
                                        * Referenced by: '<S287>/bStop'
                                        */
  boolean_T RateTransition_InitialConditi_l;
                          /* Computed Parameter: RateTransition_InitialConditi_l
                           * Referenced by: '<S4>/Rate Transition'
                           */
  boolean_T RateTransition3_InitialConditio;
                          /* Computed Parameter: RateTransition3_InitialConditio
                           * Referenced by: '<S4>/Rate Transition3'
                           */
};

/* Storage class 'PageSwitching' */
extern wturbines_cal_type wturbines_cal_impl;
extern wturbines_cal_type *wturbines_cal;

#endif                                 /* wturbines_cal_h_ */
