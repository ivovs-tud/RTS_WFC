#ifndef udp1_cal_h_
#define udp1_cal_h_
#include "rtwtypes.h"

/* Storage class 'PageSwitching', for system '<Root>' */
struct udp1_cal_type {
  real_T UnitDelay_InitialCondition[96];/* Expression: zeros(8*12,1)
                                         * Referenced by: '<Root>/Unit Delay'
                                         */
  real_T Constant1_Value;              /* Expression: 8*8*12
                                        * Referenced by: '<Root>/Constant1'
                                        */
  uint16_T UDPSend1_toPort;            /* Computed Parameter: UDPSend1_toPort
                                        * Referenced by: '<Root>/UDP Send1'
                                        */
  uint8_T UDPReceive_fmAddress[4];   /* Computed Parameter: UDPReceive_fmAddress
                                      * Referenced by: '<Root>/UDP Receive'
                                      */
  uint8_T UDPSend1_toAddress[4];       /* Computed Parameter: UDPSend1_toAddress
                                        * Referenced by: '<Root>/UDP Send1'
                                        */
  uint8_T TmpRTBAtUDPSend1Inport1_Initial;
                          /* Computed Parameter: TmpRTBAtUDPSend1Inport1_Initial
                           * Referenced by:
                           */
};

/* Storage class 'PageSwitching' */
extern udp1_cal_type udp1_cal_impl;
extern udp1_cal_type *udp1_cal;

#endif                                 /* udp1_cal_h_ */
