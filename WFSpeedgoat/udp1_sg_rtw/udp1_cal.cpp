#include "udp1_cal.h"
#include "udp1.h"

/* Storage class 'PageSwitching' */
udp1_cal_type udp1_cal_impl = {
  /* Expression: zeros(8*12,1)
   * Referenced by: '<Root>/Unit Delay'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  /* Expression: 8*8*12
   * Referenced by: '<Root>/Constant1'
   */
  768.0,

  /* Computed Parameter: UDPSend1_toPort
   * Referenced by: '<Root>/UDP Send1'
   */
  10001U,

  /* Computed Parameter: UDPReceive_fmAddress
   * Referenced by: '<Root>/UDP Receive'
   */
  { 172U, 19U, 3U, 190U },

  /* Computed Parameter: UDPSend1_toAddress
   * Referenced by: '<Root>/UDP Send1'
   */
  { 172U, 19U, 3U, 190U },

  /* Computed Parameter: TmpRTBAtUDPSend1Inport1_Initial
   * Referenced by:
   */
  0U
};

udp1_cal_type *udp1_cal = &udp1_cal_impl;
