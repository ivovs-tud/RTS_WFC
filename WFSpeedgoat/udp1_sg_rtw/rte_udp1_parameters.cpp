#include "rte_udp1_parameters.h"
#include "udp1.h"
#include "udp1_cal.h"

extern udp1_cal_type udp1_cal_impl;
namespace slrealtime
{
  /* Description of SEGMENTS */
  SegmentVector segmentInfo {
    { (void*)&udp1_cal_impl, (void**)&udp1_cal, sizeof(udp1_cal_type), 2 }
  };

  SegmentVector &getSegmentVector(void)
  {
    return segmentInfo;
  }
}                                      // slrealtime
