/*
 * wturbines.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "wturbines".
 *
 * Model version              : 1.307
 * Simulink Coder version : 24.2 (R2024b) 21-Jun-2024
 * C++ source code generated on : Mon Jun 15 21:25:00 2026
 *
 * Target selection: speedgoat.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "wturbines.h"
#include "wturbines_types.h"
#include "rtwtypes.h"
#include "rte_wturbines_parameters.h"
#include "wturbines_cal.h"
#include <cstring>
#include <cmath>

extern "C"
{

#include "rt_nonfinite.h"

}

#include "wturbines_private.h"

/* Named constants for MATLAB Function: '<S14>/True Yaw Offset' */
const int32_T wturbines_CALL_EVENT = -1;
const real_T wturbines_period = 0.01;

/* Block signals (default storage) */
B_wturbines_T wturbines_B;

/* Continuous states */
X_wturbines_T wturbines_X;

/* Disabled State Vector */
XDis_wturbines_T wturbines_XDis;

/* Block states (default storage) */
DW_wturbines_T wturbines_DW;

/* Real-time model */
RT_MODEL_wturbines_T wturbines_M_ = RT_MODEL_wturbines_T();
RT_MODEL_wturbines_T *const wturbines_M = &wturbines_M_;

/* Forward declaration for local functions */
static void wturbines_SystemCore_setup(dsp_simulink_MovingAverage_wt_T *obj);

/* Lookup Binary Search Utility BINARYSEARCH_real_T */
void BINARYSEARCH_real_T(uint32_T *piLeft, uint32_T *piRght, real_T u, const
  real_T *pData, uint32_T iHi)
{
  /* Find the location of current input value in the data table. */
  *piLeft = 0U;
  *piRght = iHi;
  if (u <= pData[0] ) {
    /* Less than or equal to the smallest point in the table. */
    *piRght = 0U;
  } else if (u >= pData[iHi] ) {
    /* Greater than or equal to the largest point in the table. */
    *piLeft = iHi;
  } else {
    uint32_T i;

    /* Do a binary search. */
    while (( *piRght - *piLeft ) > 1U ) {
      /* Get the average of the left and right indices using to Floor rounding. */
      i = (*piLeft + *piRght) >> 1;

      /* Move either the right index or the left index so that */
      /*  LeftDataPoint <= CurrentValue < RightDataPoint */
      if (u < pData[i] ) {
        *piRght = i;
      } else {
        *piLeft = i;
      }
    }
  }
}

/* Lookup Utility LookUp_real_T_real_T */
void LookUp_real_T_real_T(real_T *pY, const real_T *pYData, real_T u, const
  real_T *pUData, uint32_T iHi)
{
  uint32_T iLeft;
  uint32_T iRght;
  BINARYSEARCH_real_T( &(iLeft), &(iRght), u, pUData, iHi);

  {
    real_T lambda;
    if (pUData[iRght] > pUData[iLeft] ) {
      real_T num;
      real_T den;
      den = pUData[iRght];
      den -= pUData[iLeft];
      num = u;
      num -= pUData[iLeft];
      lambda = num / den;
    } else {
      lambda = 0.0;
    }

    {
      real_T yLeftCast;
      real_T yRghtCast;
      yLeftCast = pYData[iLeft];
      yRghtCast = pYData[iRght];
      yLeftCast += lambda * ( yRghtCast - yLeftCast );
      (*pY) = yLeftCast;
    }
  }
}

/* n-D Spline interpolation function */
real_T look_SplNBinCZcd(uint32_T numDims, const real_T* u, const
  rt_LUTSplineWork * const SWork)
{
  /*
   *   n-D column-major table lookup operating on real_T with:
   *       - Spline interpolation
   *       - Clipping
   *       - Binary breakpoint search
   *       - Index search starts at the same place each time
   */
  rt_LUTnWork * const TWork_look = SWork->m_TWork;
  real_T* const fraction = static_cast<real_T*>(TWork_look->m_bpLambda);
  uint32_T* const bpIdx = TWork_look->m_bpIndex;
  const uint32_T* const maxIndex = TWork_look->m_maxIndex;
  uint32_T k;
  for (k = 0U; k < numDims; k++) {
    const real_T* const bpData = ((const real_T * const *)
      TWork_look->m_bpDataSet)[k];
    bpIdx[k] = plook_binc(u[k], bpData, maxIndex[k], &fraction[k]);
  }

  return(intrp_NSplcd(numDims, SWork, 1U));
}

/*
 * Second derivative initialization function for spline
 * for last dimension.
 */
void rt_Spline2Derivd(const real_T *x, const real_T *y, uint32_T n, real_T *u,
                      real_T *y2)
{
  real_T p, qn, sig, un;
  uint32_T n1, i, k;
  n1 = n - 1U;
  y2[0U] = 0.0;
  u[0U] = 0.0;
  for (i = 1U; i < n1; i++) {
    real_T dxm1 = x[i] - x[i - 1U];
    real_T dxp1 = x[i + 1U] - x[i];
    real_T dxpm = dxp1 + dxm1;
    sig = dxm1 / dxpm;
    p = (sig * y2[i - 1U]) + 2.0;
    y2[i] = (sig - 1.0) / p;
    u[i] = ((y[i + 1U] - y[i]) / dxp1) - ((y[i] - y[i - 1U]) / dxm1);
    u[i] = (((6.0 * u[i]) / dxpm) - (sig * u[i - 1U])) / p;
  }

  qn = 0.0;
  un = 0.0;
  y2[n1] = (un - (qn * u[n1 - 1U])) / ((qn * y2[n1 - 1U]) + 1.0);
  for (k = n1; k > 0U; k--) {
    y2[k-1U] = (y2[k-1U] * y2[k]) + u[k-1U];
  }

  return;
}

/* n-D natural spline calculation function */
real_T intrp_NSplcd(uint32_T numDims, const rt_LUTSplineWork * const splWork,
                    uint32_T extrapMethod)
{
  uint32_T il;
  uint32_T iu, k, i;
  real_T h, s, p, smsq, pmsq;

  /* intermediate results work areas "this" and "next" */
  const rt_LUTnWork *TWork_interp = static_cast<const rt_LUTnWork *>
    (splWork->m_TWork);
  const real_T *fraction = static_cast<real_T *>(TWork_interp->m_bpLambda);
  const real_T *yp = static_cast<real_T *>(TWork_interp->m_tableData);
  real_T *yyA = static_cast<real_T *>(splWork->m_yyA);
  real_T *yyB = static_cast<real_T *>(splWork->m_yyB);
  real_T *yy2 = static_cast<real_T *>(splWork->m_yy2);
  real_T *up = static_cast<real_T *>(splWork->m_up);
  real_T *y2 = static_cast<real_T *>(splWork->m_y2);
  uint8_T* reCalc = splWork->m_reCalc;
  real_T *dp = static_cast<real_T *>(splWork->m_preBp0AndTable);
  const real_T **bpDataSet = (const real_T **) TWork_interp->m_bpDataSet;
  const real_T *xp = bpDataSet[0U];
  real_T *yy = yyA;
  uint32_T bufBank = 0U;
  uint32_T len = TWork_interp->m_maxIndex[0U] + 1U;

  /* compare bp0 and table to see whether they get changed */
  {
    /* compare the bp0 data */
    if (std::memcmp(dp, xp,
                    len * sizeof(real_T)) != 0) {
      *reCalc = 1;
      (void) std::memcpy(dp, xp,
                         len * sizeof(real_T));
    }

    /* compare the table data */
    dp = &(dp[len]);
    if (std::memcmp(dp, yp,
                    len * splWork->m_numYWorkElts[0U] * sizeof(real_T)) != 0) {
      *reCalc = 1;
      (void) std::memcpy(dp, yp,
                         len * splWork->m_numYWorkElts[0U] * sizeof(real_T));
    }
  }

  if (*reCalc == 1) {
    /* If table and bps are tunable calculate 1st dim 2nd deriv */
    /* Generate first dimension's second derivatives */
    for (i = 0U; i < splWork->m_numYWorkElts[0U]; i++) {
      rt_Spline2Derivd(xp, yp, len, up, y2);
      yp = &yp[len];
      y2 = &y2[len];
    }

    /* Set pointers back to beginning */
    yp = (const real_T *) TWork_interp->m_tableData;
    y2 = (real_T *) splWork->m_y2;
  }

  *reCalc = 0;

  /* Generate at-point splines in each dimension */
  for (k = 0U; k < numDims; k++ ) {
    /* this dimension's input setup */
    xp = bpDataSet[k];
    len = TWork_interp->m_maxIndex[k] + 1U;
    il = TWork_interp->m_bpIndex[k];
    iu = il + 1U;
    h = xp[iu] - xp[il];
    p = fraction[k];
    s = 1.0 - p;
    pmsq = p * ((p*p) - 1.0);
    smsq = s * ((s*s) - 1.0);

    /*
     * Calculate spline curves for input in this
     * dimension at each value of the higher
     * other dimensions\' points in the table.
     */
    if ((p > 1.0) && (extrapMethod == 2U) ) {
      real_T slope;
      for (i = 0U; i < splWork->m_numYWorkElts[k]; i++) {
        slope = (yp[iu] - yp[il]) + ((y2[il]*h*h)*(1.0/6.0));
        yy[i] = yp[iu] + (slope * (p-1.0));
        yp = &yp[len];
        y2 = &y2[len];
      }
    } else if ((p < 0.0) && (extrapMethod == 2U) ) {
      real_T slope;
      for (i = 0U; i < splWork->m_numYWorkElts[k]; i++) {
        slope = (yp[iu] - yp[il]) - ((y2[iu]*h*h)*(1.0/6.0));
        yy[i] = yp[il] + (slope * p);
        yp = &yp[len];
        y2 = &y2[len];
      }
    } else {
      for (i = 0U; i < splWork->m_numYWorkElts[k]; i++) {
        yy[i] = yp[il] + p * (yp[iu] - yp[il]) +
          ((smsq * y2[il] + pmsq * y2[iu])*h*h)*(1.0/6.0);
        yp = &yp[len];
        y2 = &y2[len];
      }
    }

    /* set pointers to new result and calculate second derivatives */
    yp = yy;
    y2 = yy2;
    if (splWork->m_numYWorkElts[k+1U] > 0U ) {
      uint32_T nextLen = TWork_interp->m_maxIndex[k+1U] + 1U;
      const real_T *nextXp = bpDataSet[k+1U];
      for (i = 0U; i < splWork->m_numYWorkElts[k+1U]; i++) {
        rt_Spline2Derivd(nextXp, yp, nextLen, up, y2);
        yp = &yp[nextLen];
        y2 = &y2[nextLen];
      }
    }

    /*
     * Set work vectors yp, y2 and yy for next iteration;
     * the yy just calculated becomes the yp in the
     * next iteration, y2 was just calculated for these
     * new points and the yy buffer is swapped to the space
     * for storing the next iteration\'s results.
     */
    yp = yy;
    y2 = yy2;

    /*
     * Swap buffers for next dimension and
     * toggle bufBank for next iteration.
     */
    if (bufBank == 0U) {
      yy = yyA;
      bufBank = 1U;
    } else {
      yy = yyB;
      bufBank = 0U;
    }
  }

  return( yp[0U] );
}

real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
                     uint32_T maxIndex)
{
  real_T frac;
  real_T yL_0d0;
  uint32_T iLeft;

  /* Column-major Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex]) {
    uint32_T bpIdx;
    uint32_T iRght;

    /* Binary Search */
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1U;
    frac = (u0 - bp0[maxIndex - 1U]) / (bp0[maxIndex] - bp0[maxIndex - 1U]);
  }

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  yL_0d0 = table[iLeft];
  return (table[iLeft + 1U] - yL_0d0) * frac + yL_0d0;
}

real_T look1_binlcapw(real_T u0, const real_T bp0[], const real_T table[],
                      uint32_T maxIndex)
{
  real_T frac;
  real_T y;
  uint32_T iLeft;

  /* Column-major Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'on'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'on'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = 0.0;
  } else if (u0 < bp0[maxIndex]) {
    uint32_T bpIdx;
    uint32_T iRght;

    /* Binary Search */
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex;
    frac = 0.0;
  }

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'on'
     Overflow mode: 'portable wrapping'
   */
  if (iLeft == maxIndex) {
    y = table[iLeft];
  } else {
    real_T yL_0d0;
    yL_0d0 = table[iLeft];
    y = (table[iLeft + 1U] - yL_0d0) * frac + yL_0d0;
  }

  return y;
}

real_T look2_binlcpw(real_T u0, real_T u1, const real_T bp0[], const real_T bp1[],
                     const real_T table[], const uint32_T maxIndex[], uint32_T
                     stride)
{
  real_T fractions[2];
  real_T frac;
  real_T yL_0d0;
  real_T yL_0d1;
  uint32_T bpIndices[2];
  uint32_T bpIdx;
  uint32_T iLeft;
  uint32_T iRght;

  /* Column-major Lookup 2-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = 0.0;
  } else if (u0 < bp0[maxIndex[0U]]) {
    /* Binary Search */
    bpIdx = maxIndex[0U] >> 1U;
    iLeft = 0U;
    iRght = maxIndex[0U];
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex[0U] - 1U;
    frac = 1.0;
  }

  fractions[0U] = frac;
  bpIndices[0U] = iLeft;

  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u1 <= bp1[0U]) {
    iLeft = 0U;
    frac = 0.0;
  } else if (u1 < bp1[maxIndex[1U]]) {
    /* Binary Search */
    bpIdx = maxIndex[1U] >> 1U;
    iLeft = 0U;
    iRght = maxIndex[1U];
    while (iRght - iLeft > 1U) {
      if (u1 < bp1[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u1 - bp1[iLeft]) / (bp1[iLeft + 1U] - bp1[iLeft]);
  } else {
    iLeft = maxIndex[1U] - 1U;
    frac = 1.0;
  }

  /* Column-major Interpolation 2-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  bpIdx = iLeft * stride + bpIndices[0U];
  yL_0d0 = table[bpIdx];
  yL_0d0 += (table[bpIdx + 1U] - yL_0d0) * fractions[0U];
  bpIdx += stride;
  yL_0d1 = table[bpIdx];
  return (((table[bpIdx + 1U] - yL_0d1) * fractions[0U] + yL_0d1) - yL_0d0) *
    frac + yL_0d0;
}

uint32_T plook_binc(real_T u, const real_T bp[], uint32_T maxIndex, real_T
                    *fraction)
{
  uint32_T bpIndex;

  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u <= bp[0U]) {
    bpIndex = 0U;
    *fraction = 0.0;
  } else if (u < bp[maxIndex]) {
    bpIndex = binsearch_u32d(u, bp, maxIndex >> 1U, maxIndex);
    *fraction = (u - bp[bpIndex]) / (bp[bpIndex + 1U] - bp[bpIndex]);
  } else {
    bpIndex = maxIndex - 1U;
    *fraction = 1.0;
  }

  return bpIndex;
}

uint32_T binsearch_u32d(real_T u, const real_T bp[], uint32_T startIndex,
  uint32_T maxIndex)
{
  uint32_T bpIdx;
  uint32_T bpIndex;
  uint32_T iRght;

  /* Binary Search */
  bpIdx = startIndex;
  bpIndex = 0U;
  iRght = maxIndex;
  while (iRght - bpIndex > 1U) {
    if (u < bp[bpIdx]) {
      iRght = bpIdx;
    } else {
      bpIndex = bpIdx;
    }

    bpIdx = (iRght + bpIndex) >> 1U;
  }

  return bpIndex;
}

/*
 * This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE4_IntgData *id = static_cast<ODE4_IntgData *>(rtsiGetSolverData(si));
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T temp;
  int_T i;
  int_T nXc = 54;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) std::memcpy(y, x,
                     static_cast<uint_T>(nXc)*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  wturbines_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  wturbines_step0();
  wturbines_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  wturbines_step0();
  wturbines_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  wturbines_step0();
  wturbines_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

real_T rt_urand_Upu32_Yd_f_pw_snf(uint32_T *u)
{
  uint32_T hi;
  uint32_T lo;

  /* Uniform random number generator (random number between 0 and 1)

     #define IA      16807                      magic multiplier = 7^5
     #define IM      2147483647                 modulus = 2^31-1
     #define IQ      127773                     IM div IA
     #define IR      2836                       IM modulo IA
     #define S       4.656612875245797e-10      reciprocal of 2^31-1
     test = IA * (seed % IQ) - IR * (seed/IQ)
     seed = test < 0 ? (test + IM) : test
     return (seed*S)
   */
  lo = *u % 127773U * 16807U;
  hi = *u / 127773U * 2836U;
  if (lo < hi) {
    *u = 2147483647U - (hi - lo);
  } else {
    *u = lo - hi;
  }

  return static_cast<real_T>(*u) * 4.6566128752457969E-10;
}

real_T rt_nrand_Upu32_Yd_f_pw_snf(uint32_T *u)
{
  real_T si;
  real_T sr;
  real_T y;

  /* Normal (Gaussian) random number generator */
  do {
    sr = 2.0 * rt_urand_Upu32_Yd_f_pw_snf(u) - 1.0;
    si = 2.0 * rt_urand_Upu32_Yd_f_pw_snf(u) - 1.0;
    si = sr * sr + si * si;
  } while (si > 1.0);

  y = std::sqrt(-2.0 * std::log(si) / si) * sr;
  return y;
}

static void wturbines_SystemCore_setup(dsp_simulink_MovingAverage_wt_T *obj)
{
  obj->isInitialized = 1;

  /* Start for MATLABSystem: '<S11>/Moving Average' */
  obj->NumChannels = 1;
  obj->FrameLength = 1;
  obj->pwN = 0.0;
  obj->pmN = 0.0;
  obj->plambda = obj->ForgettingFactor;
  obj->isSetupComplete = true;
  obj->TunablePropsChanged = false;
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    real_T tmp;
    real_T tmp_0;
    tmp = std::abs(u0);
    tmp_0 = std::abs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = std::sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > std::floor(u1))) {
      y = (rtNaN);
    } else {
      y = std::pow(u0, u1);
    }
  }

  return y;
}

/* Model step function for TID0 */
void wturbines_step0(void)             /* Sample time: [0.0s, 0.0s] */
{
  /* local scratch DWork variables */
  int32_T ForEach_itr;
  real_T tmp_1[400];
  real_T tmp_2[20];
  real_T tmp_3[20];
  real_T tmp_4;
  real_T tmp_5;
  real_T tmp_6;
  real_T tmp_7;
  real_T tmp_8;
  real_T tmp_9;
  real_T tmp_a;
  real_T tmp_b;
  real_T tmp_c;
  real_T tmp_d;
  real_T tmp_e;
  real_T tmp_f;
  real_T tmp_g;
  real_T tmp_h;
  real_T tmp_i;
  real_T tmp_j;
  real_T tmp_k;
  real_T u0;
  real_T u2;
  real_T y_Cp;
  real_T *tmp_l;
  real_T *tmp_m;
  int32_T i;
  int32_T i_0;
  boolean_T d_out;
  boolean_T limitedCache;
  boolean_T tmp;
  boolean_T tmp_0;
  if (rtmIsMajorTimeStep(wturbines_M)) {
    /* set solver stop time */
    if (!(wturbines_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&wturbines_M->solverInfo,
                            ((wturbines_M->Timing.clockTickH0 + 1) *
        wturbines_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&wturbines_M->solverInfo,
                            ((wturbines_M->Timing.clockTick0 + 1) *
        wturbines_M->Timing.stepSize0 + wturbines_M->Timing.clockTickH0 *
        wturbines_M->Timing.stepSize0 * 4294967296.0));
    }

    /* Update the flag to indicate when data transfers from
     *  Sample time: [0.01s, 0.0s] to Sample time: [0.1s, 0.0s]  */
    (wturbines_M->Timing.RateInteraction.TID1_2)++;
    if ((wturbines_M->Timing.RateInteraction.TID1_2) > 9) {
      wturbines_M->Timing.RateInteraction.TID1_2 = 0;
    }

    /* Update the flag to indicate when data transfers from
     *  Sample time: [0.01s, 0.0s] to Sample time: [0.25s, 0.0s]  */
    (wturbines_M->Timing.RateInteraction.TID1_3)++;
    if ((wturbines_M->Timing.RateInteraction.TID1_3) > 24) {
      wturbines_M->Timing.RateInteraction.TID1_3 = 0;
    }

    /* Update the flag to indicate when data transfers from
     *  Sample time: [0.01s, 0.0s] to Sample time: [0.5s, 0.0s]  */
    (wturbines_M->Timing.RateInteraction.TID1_4)++;
    if ((wturbines_M->Timing.RateInteraction.TID1_4) > 49) {
      wturbines_M->Timing.RateInteraction.TID1_4 = 0;
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(wturbines_M)) {
    wturbines_M->Timing.t[0] = rtsiGetT(&wturbines_M->solverInfo);
  }

  /* Outputs for Iterator SubSystem: '<Root>/For Each Subsystem' incorporates:
   *  ForEach: '<S2>/For Each'
   */
  /* Lookup_n-D: '<S277>/Cp(&#x3BB;, &#x3B2;) ' incorporates:
   *  Switch: '<S277>/Switch'
   */
  tmp_m = get_pitch_vec();
  tmp_l = get_tsr_vec();

  /* RateLimiter: '<S276>/Rate Limiter' */
  tmp_k = *get_pitch_rate_deg();

  /* Relay: '<S151>/Relay' */
  tmp_j = *get_rated_wind_speed();

  /* Switch: '<S11>/Switch' incorporates:
   *  Constant: '<S11>/Constant1'
   *  Switch: '<S11>/Switch3'
   */
  tmp_i = *get_brake_torque();

  /* Chart: '<S11>/Wind Turbine State Machine' */
  tmp_h = *get_ROT_SPEED_MIN_TRANS();
  tmp_g = *get_cut_in_wind_speed();
  tmp_f = *get_MIN_ROT_SPEED();

  /* Product: '<S27>/Divide4' incorporates:
   *  Constant: '<S27>/Constant12'
   *  MultiPortSwitch: '<S27>/Multiport Switch'
   */
  tmp_e = *get_tsr_opt();

  /* RateLimiter: '<S278>/Rate Limiter' */
  tmp_d = *get_yawing_rate();

  /* Gain: '<S265>/Gain' incorporates:
   *  Constant: '<S265>/Constant'
   */
  tmp_c = *get_rated_rotor_speed();

  /* Gain: '<S14>/Multiply2' */
  tmp_b = *get_gearbox_ratio();

  /* RelationalOperator: '<S150>/IsNaN1' incorporates:
   *  Constant: '<S150>/Constant1'
   */
  tmp_a = *get_alpha_pitch_exp();

  /* Product: '<S29>/Product1' incorporates:
   *  Constant: '<S29>/Constant5'
   *  Constant: '<S29>/Constant8'
   *  Constant: '<S29>/Constant9'
   */
  tmp_9 = *get_generator_eff();
  tmp_8 = *get_Cp_opt();
  tmp_7 = *get_air_density();

  /* Saturate: '<S8>/Saturation' */
  tmp_6 = *get_rated_power();

  /* Product: '<S282>/Product' incorporates:
   *  Constant: '<S282>/Constant'
   */
  tmp_5 = *get_rotor_radius();

  /* Saturate: '<S14>/Saturation' */
  tmp_4 = *get_rated_rotor_speed_rads();

  /* End of Outputs for SubSystem: '<Root>/For Each Subsystem' */

  /* RateTransition: '<S5>/Rate Transition' incorporates:
   *  RateTransition: '<S1>/Rate Transition'
   */
  tmp_0 = rtmIsMajorTimeStep(wturbines_M);
  if (tmp_0) {
    /* RateTransition: '<S5>/Rate Transition3' incorporates:
     *  RateTransition: '<S4>/Rate Transition1'
     *  RateTransition: '<S4>/Rate Transition2'
     *  RateTransition: '<S5>/Rate Transition1'
     *  RateTransition: '<S5>/Rate Transition2'
     *  RateTransition: '<S5>/Rate Transition4'
     */
    tmp = (wturbines_M->Timing.RateInteraction.TID1_2 == 1);
    if (tmp) {
      wturbines_DW.RateTransition_RdBufIdx = static_cast<int8_T>
        (wturbines_DW.RateTransition_RdBufIdx == 0);
    }

    i = wturbines_DW.RateTransition_RdBufIdx * 9;

    /* RateTransition: '<S5>/Rate Transition' */
    for (i_0 = 0; i_0 < 9; i_0++) {
      wturbines_B.RateTransition_l[i_0] = wturbines_DW.RateTransition_Buf_n[i_0
        + i];
    }

    /* End of RateTransition: '<S5>/Rate Transition' */

    /* RateTransition: '<S5>/Rate Transition3' */
    if (tmp) {
      wturbines_DW.RateTransition3_RdBufIdx = static_cast<int8_T>
        (wturbines_DW.RateTransition3_RdBufIdx == 0);
    }

    i = wturbines_DW.RateTransition3_RdBufIdx * 9;
    for (i_0 = 0; i_0 < 9; i_0++) {
      /* RateTransition: '<S5>/Rate Transition3' */
      wturbines_B.RateTransition3[i_0] = wturbines_DW.RateTransition3_Buf[i_0 +
        i];
    }

    /* RateTransition: '<S5>/Rate Transition4' */
    if (tmp) {
      wturbines_DW.RateTransition4_RdBufIdx = static_cast<int8_T>
        (wturbines_DW.RateTransition4_RdBufIdx == 0);
    }

    i = wturbines_DW.RateTransition4_RdBufIdx * 9;
    for (i_0 = 0; i_0 < 9; i_0++) {
      /* RateTransition: '<S5>/Rate Transition4' */
      wturbines_B.RateTransition4[i_0] = wturbines_DW.RateTransition4_Buf[i_0 +
        i];
    }

    /* RateTransition: '<S5>/Rate Transition1' */
    if (tmp) {
      wturbines_DW.RateTransition1_RdBufIdx = static_cast<int8_T>
        (wturbines_DW.RateTransition1_RdBufIdx == 0);
    }

    i = wturbines_DW.RateTransition1_RdBufIdx * 9;
    for (i_0 = 0; i_0 < 9; i_0++) {
      /* RateTransition: '<S5>/Rate Transition1' */
      wturbines_B.RateTransition1[i_0] = wturbines_DW.RateTransition1_Buf[i_0 +
        i];
    }

    /* RateTransition: '<S5>/Rate Transition2' */
    if (tmp) {
      wturbines_DW.RateTransition2_RdBufIdx = static_cast<int8_T>
        (wturbines_DW.RateTransition2_RdBufIdx == 0);
    }

    i = wturbines_DW.RateTransition2_RdBufIdx * 9;
    for (i_0 = 0; i_0 < 9; i_0++) {
      /* RateTransition: '<S5>/Rate Transition2' */
      wturbines_B.RateTransition2[i_0] = wturbines_DW.RateTransition2_Buf[i_0 +
        i];
    }

    /* RateTransition: '<S4>/Rate Transition1' */
    if (tmp) {
      wturbines_DW.RateTransition1_RdBufIdx_k = static_cast<int8_T>
        (wturbines_DW.RateTransition1_RdBufIdx_k == 0);
    }

    i = wturbines_DW.RateTransition1_RdBufIdx_k * 9;
    for (i_0 = 0; i_0 < 9; i_0++) {
      /* RateTransition: '<S4>/Rate Transition1' */
      wturbines_B.RateTransition1_c[i_0] =
        wturbines_DW.RateTransition1_Buf_f[i_0 + i];
    }

    /* RateTransition: '<S4>/Rate Transition2' */
    if (tmp) {
      wturbines_DW.RateTransition2_RdBufIdx_c = static_cast<int8_T>
        (wturbines_DW.RateTransition2_RdBufIdx_c == 0);
    }

    i = wturbines_DW.RateTransition2_RdBufIdx_c * 9;
    for (i_0 = 0; i_0 < 9; i_0++) {
      /* RateTransition: '<S4>/Rate Transition2' */
      wturbines_B.RateTransition2_p[i_0] =
        wturbines_DW.RateTransition2_Buf_k[i_0 + i];
    }
  }

  /* End of RateTransition: '<S5>/Rate Transition' */

  /* Outputs for Iterator SubSystem: '<Root>/For Each Subsystem' incorporates:
   *  ForEach: '<S2>/For Each'
   */
  ForEach_itr = 0;

  /* End of Outputs for SubSystem: '<Root>/For Each Subsystem' */
  for (i_0 = 0; i_0 < 400; i_0++) {
    tmp_1[i_0] = (get_Ct_mat())[i_0];
  }

  for (i_0 = 0; i_0 < 20; i_0++) {
    tmp_2[i_0] = tmp_l[i_0];
  }

  for (i_0 = 0; i_0 < 20; i_0++) {
    tmp_3[i_0] = tmp_m[i_0];
  }

  /* Outputs for Iterator SubSystem: '<Root>/For Each Subsystem' incorporates:
   *  ForEach: '<S2>/For Each'
   */
  while (ForEach_itr < 9) {
    /* Outputs for Iterator SubSystem: '<Root>/For Each Subsystem' incorporates:
     *  ForEach: '<S2>/For Each'
     */
    wturbines_B.ForEach = ForEach_itr;

    /* RateTransition: '<S2>/Rate Transition1' incorporates:
     *  RateTransition: '<S12>/Rate Transition1'
     *  RateTransition: '<S2>/Rate Transition2'
     *  RateTransition: '<S2>/Rate Transition4'
     *  RateTransition: '<S2>/Rate Transition6'
     *  RateTransition: '<S2>/Rate Transition7'
     */
    tmp = rtmIsMajorTimeStep(wturbines_M);
    if (tmp) {
      /* DataTypeConversion: '<S2>/Data Type Conversion' incorporates:
       *  ForEachSliceSelector generated from: '<S2>/OrientationSetpoint'
       */
      wturbines_B.CoreSubsys[ForEach_itr].DataTypeConversion =
        wturbines_B.RateTransition2[ForEach_itr];

      /* DataTypeConversion: '<S2>/Data Type Conversion1' incorporates:
       *  ForEachSliceSelector generated from: '<S2>/PowerSetpoint'
       */
      wturbines_B.CoreSubsys[ForEach_itr].DataTypeConversion1 =
        wturbines_B.RateTransition1[ForEach_itr];

      /* DataTypeConversion: '<S2>/Data Type Conversion2' incorporates:
       *  ForEachSliceSelector generated from: '<S2>/WindDirection'
       */
      wturbines_B.CoreSubsys[ForEach_itr].DataTypeConversion2 =
        wturbines_B.RateTransition2_p[ForEach_itr];

      /* DataTypeConversion: '<S2>/Data Type Conversion3' incorporates:
       *  ForEachSliceSelector generated from: '<S2>/WindSpeed'
       */
      wturbines_B.CoreSubsys[ForEach_itr].DataTypeConversion3 =
        wturbines_B.RateTransition1_c[ForEach_itr];

      /* InitialCondition: '<S2>/IC' */
      if (wturbines_DW.CoreSubsys[ForEach_itr].IC_FirstOutputTime) {
        wturbines_DW.CoreSubsys[ForEach_itr].IC_FirstOutputTime = false;

        /* InitialCondition: '<S2>/IC' */
        wturbines_B.CoreSubsys[ForEach_itr].IC =
          wturbines_cal->wturbines_CoreSubsys_cal.IC_Value;
      } else {
        /* InitialCondition: '<S2>/IC' */
        wturbines_B.CoreSubsys[ForEach_itr].IC =
          wturbines_B.CoreSubsys[ForEach_itr].DataTypeConversion;
      }

      /* End of InitialCondition: '<S2>/IC' */

      /* InitialCondition: '<S2>/IC1' */
      if (wturbines_DW.CoreSubsys[ForEach_itr].IC1_FirstOutputTime) {
        wturbines_DW.CoreSubsys[ForEach_itr].IC1_FirstOutputTime = false;

        /* InitialCondition: '<S2>/IC1' */
        wturbines_B.CoreSubsys[ForEach_itr].IC1 =
          wturbines_cal->wturbines_CoreSubsys_cal.IC1_Value;
      } else {
        /* InitialCondition: '<S2>/IC1' */
        wturbines_B.CoreSubsys[ForEach_itr].IC1 =
          wturbines_B.CoreSubsys[ForEach_itr].DataTypeConversion1;
      }

      /* End of InitialCondition: '<S2>/IC1' */

      /* InitialCondition: '<S2>/IC2' */
      if (wturbines_DW.CoreSubsys[ForEach_itr].IC2_FirstOutputTime) {
        wturbines_DW.CoreSubsys[ForEach_itr].IC2_FirstOutputTime = false;

        /* InitialCondition: '<S2>/IC2' */
        wturbines_B.CoreSubsys[ForEach_itr].IC2 =
          wturbines_cal->wturbines_CoreSubsys_cal.IC2_Value;
      } else {
        /* InitialCondition: '<S2>/IC2' incorporates:
         *  ForEachSliceSelector generated from: '<S2>/bEnable'
         */
        wturbines_B.CoreSubsys[ForEach_itr].IC2 =
          wturbines_B.RateTransition_l[ForEach_itr];
      }

      /* End of InitialCondition: '<S2>/IC2' */

      /* InitialCondition: '<S2>/IC3' */
      if (wturbines_DW.CoreSubsys[ForEach_itr].IC3_FirstOutputTime) {
        wturbines_DW.CoreSubsys[ForEach_itr].IC3_FirstOutputTime = false;

        /* InitialCondition: '<S2>/IC3' */
        wturbines_B.CoreSubsys[ForEach_itr].IC3 =
          wturbines_cal->wturbines_CoreSubsys_cal.IC3_Value;
      } else {
        /* InitialCondition: '<S2>/IC3' incorporates:
         *  ForEachSliceSelector generated from: '<S2>/bStop'
         */
        wturbines_B.CoreSubsys[ForEach_itr].IC3 =
          wturbines_B.RateTransition3[ForEach_itr];
      }

      /* End of InitialCondition: '<S2>/IC3' */

      /* InitialCondition: '<S2>/IC4' */
      if (wturbines_DW.CoreSubsys[ForEach_itr].IC4_FirstOutputTime) {
        wturbines_DW.CoreSubsys[ForEach_itr].IC4_FirstOutputTime = false;

        /* InitialCondition: '<S2>/IC4' */
        wturbines_B.CoreSubsys[ForEach_itr].IC4 =
          wturbines_cal->wturbines_CoreSubsys_cal.IC4_Value;
      } else {
        /* InitialCondition: '<S2>/IC4' incorporates:
         *  ForEachSliceSelector generated from: '<S2>/eCtrlMode'
         */
        wturbines_B.CoreSubsys[ForEach_itr].IC4 =
          wturbines_B.RateTransition4[ForEach_itr];
      }

      /* End of InitialCondition: '<S2>/IC4' */

      /* InitialCondition: '<S2>/IC5' */
      if (wturbines_DW.CoreSubsys[ForEach_itr].IC5_FirstOutputTime) {
        wturbines_DW.CoreSubsys[ForEach_itr].IC5_FirstOutputTime = false;

        /* InitialCondition: '<S2>/IC5' */
        wturbines_B.CoreSubsys[ForEach_itr].IC5 =
          wturbines_cal->wturbines_CoreSubsys_cal.IC5_Value;
      } else {
        /* InitialCondition: '<S2>/IC5' */
        wturbines_B.CoreSubsys[ForEach_itr].IC5 =
          wturbines_B.CoreSubsys[ForEach_itr].DataTypeConversion3;
      }

      /* End of InitialCondition: '<S2>/IC5' */

      /* InitialCondition: '<S2>/IC6' */
      if (wturbines_DW.CoreSubsys[ForEach_itr].IC6_FirstOutputTime) {
        wturbines_DW.CoreSubsys[ForEach_itr].IC6_FirstOutputTime = false;

        /* InitialCondition: '<S2>/IC6' */
        wturbines_B.CoreSubsys[ForEach_itr].IC6 =
          wturbines_cal->wturbines_CoreSubsys_cal.IC6_Value;
      } else {
        /* InitialCondition: '<S2>/IC6' */
        wturbines_B.CoreSubsys[ForEach_itr].IC6 =
          wturbines_B.CoreSubsys[ForEach_itr].DataTypeConversion2;
      }

      /* End of InitialCondition: '<S2>/IC6' */
    }

    /* Integrator: '<S14>/Integrator' */
    wturbines_B.CoreSubsys[ForEach_itr].t = wturbines_X.CoreSubsys[ForEach_itr].
      Integrator_CSTATE;

    /* Saturate: '<S14>/Saturation' */
    u0 = wturbines_B.CoreSubsys[ForEach_itr].t;
    y_Cp = wturbines_cal->wturbines_CoreSubsys_cal.Saturation_LowerSat_e;
    u2 = tmp_4;
    if (u0 > u2) {
      /* Saturate: '<S14>/Saturation' */
      wturbines_B.CoreSubsys[ForEach_itr].RotSpd = u2;
    } else if (u0 < y_Cp) {
      /* Saturate: '<S14>/Saturation' */
      wturbines_B.CoreSubsys[ForEach_itr].RotSpd = y_Cp;
    } else {
      /* Saturate: '<S14>/Saturation' */
      wturbines_B.CoreSubsys[ForEach_itr].RotSpd = u0;
    }

    /* Product: '<S282>/Product' incorporates:
     *  Constant: '<S282>/Constant'
     */
    wturbines_B.CoreSubsys[ForEach_itr].Product =
      wturbines_B.CoreSubsys[ForEach_itr].RotSpd * tmp_5;

    /* RateTransition: '<S2>/Rate Transition' */
    if (tmp) {
      /* RateTransition: '<S2>/Rate Transition' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition =
        wturbines_B.CoreSubsys[ForEach_itr].IC5;

      /* RateLimiter: '<S2>/Rate Limiter' */
      y_Cp = wturbines_B.CoreSubsys[ForEach_itr].RateTransition -
        wturbines_DW.CoreSubsys[ForEach_itr].PrevY;
      if (y_Cp > wturbines_cal->wturbines_CoreSubsys_cal.RateLimiter_RisingLim *
          wturbines_period) {
        /* RateLimiter: '<S2>/Rate Limiter' */
        wturbines_B.CoreSubsys[ForEach_itr].RateLimiter =
          wturbines_cal->wturbines_CoreSubsys_cal.RateLimiter_RisingLim *
          wturbines_period + wturbines_DW.CoreSubsys[ForEach_itr].PrevY;
      } else if (y_Cp <
                 wturbines_cal->wturbines_CoreSubsys_cal.RateLimiter_FallingLim *
                 wturbines_period) {
        /* RateLimiter: '<S2>/Rate Limiter' */
        wturbines_B.CoreSubsys[ForEach_itr].RateLimiter =
          wturbines_cal->wturbines_CoreSubsys_cal.RateLimiter_FallingLim *
          wturbines_period + wturbines_DW.CoreSubsys[ForEach_itr].PrevY;
      } else {
        /* RateLimiter: '<S2>/Rate Limiter' */
        wturbines_B.CoreSubsys[ForEach_itr].RateLimiter =
          wturbines_B.CoreSubsys[ForEach_itr].RateTransition;
      }

      wturbines_DW.CoreSubsys[ForEach_itr].PrevY =
        wturbines_B.CoreSubsys[ForEach_itr].RateLimiter;

      /* End of RateLimiter: '<S2>/Rate Limiter' */

      /* RateTransition: '<S2>/Rate Transition1' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition1 =
        wturbines_B.CoreSubsys[ForEach_itr].IC6;

      /* RateLimiter: '<S2>/Rate Limiter1' */
      y_Cp = wturbines_B.CoreSubsys[ForEach_itr].RateTransition1 -
        wturbines_DW.CoreSubsys[ForEach_itr].PrevY_e;
      if (y_Cp > wturbines_cal->wturbines_CoreSubsys_cal.RateLimiter1_RisingLim *
          wturbines_period) {
        /* RateLimiter: '<S2>/Rate Limiter1' */
        wturbines_B.CoreSubsys[ForEach_itr].RateLimiter1 =
          wturbines_cal->wturbines_CoreSubsys_cal.RateLimiter1_RisingLim *
          wturbines_period + wturbines_DW.CoreSubsys[ForEach_itr].PrevY_e;
      } else if (y_Cp <
                 wturbines_cal->wturbines_CoreSubsys_cal.RateLimiter1_FallingLim
                 * wturbines_period) {
        /* RateLimiter: '<S2>/Rate Limiter1' */
        wturbines_B.CoreSubsys[ForEach_itr].RateLimiter1 =
          wturbines_cal->wturbines_CoreSubsys_cal.RateLimiter1_FallingLim *
          wturbines_period + wturbines_DW.CoreSubsys[ForEach_itr].PrevY_e;
      } else {
        /* RateLimiter: '<S2>/Rate Limiter1' */
        wturbines_B.CoreSubsys[ForEach_itr].RateLimiter1 =
          wturbines_B.CoreSubsys[ForEach_itr].RateTransition1;
      }

      wturbines_DW.CoreSubsys[ForEach_itr].PrevY_e =
        wturbines_B.CoreSubsys[ForEach_itr].RateLimiter1;

      /* End of RateLimiter: '<S2>/Rate Limiter1' */

      /* RateTransition: '<S2>/Rate Transition6' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition6 =
        wturbines_B.CoreSubsys[ForEach_itr].IC;

      /* MATLAB Function: '<S11>/MATLAB Function' */
      wturbines_DW.CoreSubsys[ForEach_itr].sfEvent = wturbines_CALL_EVENT;
      if (!wturbines_DW.CoreSubsys[ForEach_itr].last_val_not_empty) {
        wturbines_DW.CoreSubsys[ForEach_itr].last_val =
          wturbines_B.CoreSubsys[ForEach_itr].RateTransition6;
        wturbines_DW.CoreSubsys[ForEach_itr].last_val_not_empty = true;
      }

      if (std::abs(wturbines_B.CoreSubsys[ForEach_itr].RateTransition6 -
                   wturbines_DW.CoreSubsys[ForEach_itr].last_val) >= 5.0) {
        wturbines_DW.CoreSubsys[ForEach_itr].last_val =
          wturbines_B.CoreSubsys[ForEach_itr].RateTransition6;
      }

      wturbines_B.CoreSubsys[ForEach_itr].y =
        wturbines_DW.CoreSubsys[ForEach_itr].last_val;

      /* End of MATLAB Function: '<S11>/MATLAB Function' */

      /* RateLimiter: '<S278>/Rate Limiter' */
      y_Cp = wturbines_B.CoreSubsys[ForEach_itr].y -
        wturbines_DW.CoreSubsys[ForEach_itr].PrevY_n;
      if (y_Cp > tmp_d * wturbines_period) {
        /* RateLimiter: '<S278>/Rate Limiter' */
        wturbines_B.CoreSubsys[ForEach_itr].RateLimiter_p = tmp_d *
          wturbines_period + wturbines_DW.CoreSubsys[ForEach_itr].PrevY_n;
      } else {
        u0 = -tmp_d;
        if (y_Cp < u0 * wturbines_period) {
          /* RateLimiter: '<S278>/Rate Limiter' */
          wturbines_B.CoreSubsys[ForEach_itr].RateLimiter_p = u0 *
            wturbines_period + wturbines_DW.CoreSubsys[ForEach_itr].PrevY_n;
        } else {
          /* RateLimiter: '<S278>/Rate Limiter' */
          wturbines_B.CoreSubsys[ForEach_itr].RateLimiter_p =
            wturbines_B.CoreSubsys[ForEach_itr].y;
        }
      }

      wturbines_DW.CoreSubsys[ForEach_itr].PrevY_n =
        wturbines_B.CoreSubsys[ForEach_itr].RateLimiter_p;

      /* MATLAB Function: '<S14>/True Yaw Offset' */
      wturbines_DW.CoreSubsys[ForEach_itr].sfEvent_e = wturbines_CALL_EVENT;
      wturbines_B.CoreSubsys[ForEach_itr].yaw =
        wturbines_B.CoreSubsys[ForEach_itr].RateLimiter1 -
        wturbines_B.CoreSubsys[ForEach_itr].RateLimiter_p;
      if (wturbines_B.CoreSubsys[ForEach_itr].yaw > 180.0) {
        wturbines_B.CoreSubsys[ForEach_itr].yaw -= 360.0;
      } else if (wturbines_B.CoreSubsys[ForEach_itr].yaw < -180.0) {
        wturbines_B.CoreSubsys[ForEach_itr].yaw += 360.0;
      }

      /* End of MATLAB Function: '<S14>/True Yaw Offset' */

      /* Gain: '<S284>/Gain1' */
      wturbines_B.CoreSubsys[ForEach_itr].Gain1 =
        wturbines_cal->wturbines_CoreSubsys_cal.Gain1_Gain_e *
        wturbines_B.CoreSubsys[ForEach_itr].yaw;

      /* Trigonometry: '<S14>/Trigonometric Function' */
      wturbines_B.CoreSubsys[ForEach_itr].TrigonometricFunction = std::cos
        (wturbines_B.CoreSubsys[ForEach_itr].Gain1);

      /* Product: '<S14>/Product' */
      wturbines_B.CoreSubsys[ForEach_itr].Product_l =
        wturbines_B.CoreSubsys[ForEach_itr].RateLimiter *
        wturbines_B.CoreSubsys[ForEach_itr].TrigonometricFunction;

      /* Saturate: '<S14>/Saturation2' */
      u0 = wturbines_B.CoreSubsys[ForEach_itr].Product_l;
      y_Cp = wturbines_cal->wturbines_CoreSubsys_cal.Saturation2_LowerSat;
      u2 = wturbines_cal->wturbines_CoreSubsys_cal.Saturation2_UpperSat;
      if (u0 > u2) {
        /* Saturate: '<S14>/Saturation2' */
        wturbines_B.CoreSubsys[ForEach_itr].WsEff = u2;
      } else if (u0 < y_Cp) {
        /* Saturate: '<S14>/Saturation2' */
        wturbines_B.CoreSubsys[ForEach_itr].WsEff = y_Cp;
      } else {
        /* Saturate: '<S14>/Saturation2' */
        wturbines_B.CoreSubsys[ForEach_itr].WsEff = u0;
      }

      /* End of Saturate: '<S14>/Saturation2' */
    }

    /* End of RateTransition: '<S2>/Rate Transition' */

    /* Product: '<S282>/Divide' */
    wturbines_B.CoreSubsys[ForEach_itr].t_c = wturbines_B.CoreSubsys[ForEach_itr]
      .Product / wturbines_B.CoreSubsys[ForEach_itr].WsEff;
    if (tmp) {
      /* Gain: '<S26>/Gain1' incorporates:
       *  Constant: '<S11>/Constant4'
       */
      wturbines_B.CoreSubsys[ForEach_itr].Gain1_f =
        wturbines_cal->wturbines_CoreSubsys_cal.Gain1_Gain_j *
        wturbines_cal->wturbines_CoreSubsys_cal.Constant4_Value_a;

      /* RateTransition: '<S12>/Rate Transition13' incorporates:
       *  RateTransition: '<S12>/Rate Transition2'
       *  RateTransition: '<S12>/Rate Transition3'
       */
      limitedCache = (wturbines_M->Timing.RateInteraction.TID1_2 == 1);
      if (limitedCache) {
        wturbines_DW.CoreSubsys[ForEach_itr].RateTransition13_RdBufIdx =
          static_cast<int8_T>(wturbines_DW.CoreSubsys[ForEach_itr].
                              RateTransition13_RdBufIdx == 0);
      }

      /* RateTransition: '<S12>/Rate Transition13' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition13 =
        wturbines_DW.CoreSubsys[ForEach_itr]
        .RateTransition13_Buf[wturbines_DW.CoreSubsys[ForEach_itr].
        RateTransition13_RdBufIdx];

      /* MATLABSystem: '<S11>/Moving Average' */
      if (wturbines_DW.CoreSubsys[ForEach_itr].obj.ForgettingFactor !=
          wturbines_cal->wturbines_CoreSubsys_cal.MovingAverage_ForgettingFactor)
      {
        if (wturbines_DW.CoreSubsys[ForEach_itr].obj.isInitialized == 1) {
          wturbines_DW.CoreSubsys[ForEach_itr].obj.TunablePropsChanged = true;
        }

        wturbines_DW.CoreSubsys[ForEach_itr].obj.ForgettingFactor =
          wturbines_cal->wturbines_CoreSubsys_cal.MovingAverage_ForgettingFactor;
      }

      if (wturbines_DW.CoreSubsys[ForEach_itr].obj.TunablePropsChanged) {
        wturbines_DW.CoreSubsys[ForEach_itr].obj.TunablePropsChanged = false;
        wturbines_DW.CoreSubsys[ForEach_itr].obj.plambda =
          wturbines_DW.CoreSubsys[ForEach_itr].obj.ForgettingFactor;
      }

      y_Cp = wturbines_DW.CoreSubsys[ForEach_itr].obj.plambda *
        wturbines_DW.CoreSubsys[ForEach_itr].obj.pwN + 1.0;
      u2 = (1.0 - 1.0 / y_Cp) * wturbines_DW.CoreSubsys[ForEach_itr].obj.pmN +
        1.0 / y_Cp * wturbines_B.CoreSubsys[ForEach_itr].RateTransition13;
      wturbines_DW.CoreSubsys[ForEach_itr].obj.pwN = y_Cp;
      wturbines_DW.CoreSubsys[ForEach_itr].obj.pmN = u2;

      /* MATLABSystem: '<S11>/Moving Average' */
      wturbines_B.CoreSubsys[ForEach_itr].MovingAverage = u2;

      /* RateTransition: '<S12>/Rate Transition2' */
      if (limitedCache) {
        wturbines_DW.CoreSubsys[ForEach_itr].RateTransition2_RdBufIdx =
          static_cast<int8_T>(wturbines_DW.CoreSubsys[ForEach_itr].
                              RateTransition2_RdBufIdx == 0);
      }

      /* RateTransition: '<S12>/Rate Transition2' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition2 =
        wturbines_DW.CoreSubsys[ForEach_itr]
        .RateTransition2_Buf[wturbines_DW.CoreSubsys[ForEach_itr].
        RateTransition2_RdBufIdx];

      /* RateTransition: '<S2>/Rate Transition2' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition2_b =
        wturbines_B.CoreSubsys[ForEach_itr].IC2;

      /* RateTransition: '<S2>/Rate Transition3' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition3_j =
        wturbines_B.CoreSubsys[ForEach_itr].IC3;

      /* RateTransition: '<S2>/Rate Transition5' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition5 =
        wturbines_B.CoreSubsys[ForEach_itr].IC1;

      /* Saturate: '<S8>/Saturation' */
      u0 = wturbines_B.CoreSubsys[ForEach_itr].RateTransition5;
      y_Cp = wturbines_cal->wturbines_CoreSubsys_cal.Saturation_LowerSat_h;
      u2 = tmp_6;
      if (u0 > u2) {
        /* Saturate: '<S8>/Saturation' */
        wturbines_B.CoreSubsys[ForEach_itr].Saturation = u2;
      } else if (u0 < y_Cp) {
        /* Saturate: '<S8>/Saturation' */
        wturbines_B.CoreSubsys[ForEach_itr].Saturation = y_Cp;
      } else {
        /* Saturate: '<S8>/Saturation' */
        wturbines_B.CoreSubsys[ForEach_itr].Saturation = u0;
      }

      /* Switch: '<S8>/Switch' */
      if (wturbines_B.CoreSubsys[ForEach_itr].Saturation >
          wturbines_cal->wturbines_CoreSubsys_cal.Switch_Threshold) {
        /* Switch: '<S8>/Switch' */
        wturbines_B.CoreSubsys[ForEach_itr].Pref =
          wturbines_B.CoreSubsys[ForEach_itr].Saturation;
      } else {
        /* Math: '<S13>/Power' incorporates:
         *  Constant: '<S13>/Constant3'
         */
        wturbines_B.CoreSubsys[ForEach_itr].ws_drt_h = rt_powd_snf
          (wturbines_B.CoreSubsys[ForEach_itr].RateTransition13,
           wturbines_cal->wturbines_CoreSubsys_cal.Constant3_Value);

        /* Math: '<S13>/Square' incorporates:
         *  Constant: '<S13>/Constant7'
         */
        wturbines_B.CoreSubsys[ForEach_itr].Square_oq = tmp_5 * tmp_5;

        /* Product: '<S13>/Product1' incorporates:
         *  Constant: '<S13>/Constant4'
         *  Constant: '<S13>/Constant5'
         *  Constant: '<S13>/Constant6'
         *  Constant: '<S13>/Constant8'
         *  Constant: '<S13>/Constant9'
         */
        wturbines_B.CoreSubsys[ForEach_itr].Product1_a =
          wturbines_cal->wturbines_CoreSubsys_cal.Constant4_Value * tmp_7 *
          wturbines_cal->wturbines_CoreSubsys_cal.Constant6_Value *
          wturbines_B.CoreSubsys[ForEach_itr].Square_oq * tmp_8 * tmp_9 *
          wturbines_B.CoreSubsys[ForEach_itr].ws_drt_h;

        /* MinMax: '<S13>/Min' incorporates:
         *  Constant: '<S13>/Constant'
         */
        u0 = wturbines_B.CoreSubsys[ForEach_itr].Product1_a;
        y_Cp = tmp_6;
        if ((u0 <= y_Cp) || rtIsNaN(y_Cp)) {
          y_Cp = u0;
        }

        /* MinMax: '<S13>/Min' */
        wturbines_B.CoreSubsys[ForEach_itr].Min = y_Cp;

        /* Switch: '<S8>/Switch' */
        wturbines_B.CoreSubsys[ForEach_itr].Pref =
          wturbines_B.CoreSubsys[ForEach_itr].Min;
      }

      /* End of Switch: '<S8>/Switch' */

      /* Math: '<S29>/Square' incorporates:
       *  Constant: '<S29>/Constant7'
       */
      wturbines_B.CoreSubsys[ForEach_itr].Square = tmp_5 * tmp_5;

      /* Product: '<S29>/Product1' incorporates:
       *  Constant: '<S29>/Constant4'
       *  Constant: '<S29>/Constant5'
       *  Constant: '<S29>/Constant6'
       *  Constant: '<S29>/Constant8'
       *  Constant: '<S29>/Constant9'
       */
      wturbines_B.CoreSubsys[ForEach_itr].Product1 =
        wturbines_cal->wturbines_CoreSubsys_cal.Constant4_Value_g * tmp_7 *
        wturbines_cal->wturbines_CoreSubsys_cal.Constant6_Value_o *
        wturbines_B.CoreSubsys[ForEach_itr].Square * tmp_8 * tmp_9;

      /* Product: '<S29>/Divide1' */
      wturbines_B.CoreSubsys[ForEach_itr].Divide1 =
        wturbines_B.CoreSubsys[ForEach_itr].Pref /
        wturbines_B.CoreSubsys[ForEach_itr].Product1;

      /* Math: '<S29>/Power' incorporates:
       *  Constant: '<S29>/Constant3'
       */
      wturbines_B.CoreSubsys[ForEach_itr].ws_drt = rt_powd_snf
        (wturbines_B.CoreSubsys[ForEach_itr].Divide1,
         wturbines_cal->wturbines_CoreSubsys_cal.Constant3_Value_c);

      /* Sum: '<S29>/Sum1' */
      wturbines_B.CoreSubsys[ForEach_itr].ws_drwst =
        wturbines_B.CoreSubsys[ForEach_itr].ws_drt -
        wturbines_B.CoreSubsys[ForEach_itr].RateTransition13;

      /* Switch: '<S29>/Derating' */
      if (wturbines_B.CoreSubsys[ForEach_itr].ws_drwst >
          wturbines_cal->wturbines_CoreSubsys_cal.Derating_Threshold_l) {
        /* Product: '<S29>/Divide3' incorporates:
         *  Constant: '<S29>/Constant'
         *  Constant: '<S29>/Constant1'
         */
        wturbines_B.CoreSubsys[ForEach_itr].Divide3 = tmp_e *
          wturbines_B.CoreSubsys[ForEach_itr].RateTransition13 / tmp_5;

        /* Switch: '<S29>/Derating' */
        wturbines_B.CoreSubsys[ForEach_itr]._sett =
          wturbines_B.CoreSubsys[ForEach_itr].Divide3;
      } else {
        /* MultiPortSwitch: '<S29>/Multiport Switch' incorporates:
         *  Constant: '<S29>/Mode'
         */
        switch (static_cast<int32_T>(*get_dr_mode())) {
         case 1:
          /* Gain: '<S155>/Multiply' incorporates:
           *  Constant: '<S29>/&#x3C9;_set'
           */
          wturbines_B.CoreSubsys[ForEach_itr].Multiply_d =
            wturbines_cal->wturbines_CoreSubsys_cal.Multiply_Gain * tmp_c;

          /* Gain: '<S155>/Multiply1' */
          wturbines_B.CoreSubsys[ForEach_itr].Multiply1_g =
            wturbines_cal->wturbines_CoreSubsys_cal.Multiply1_Gain *
            wturbines_B.CoreSubsys[ForEach_itr].Multiply_d;

          /* MultiPortSwitch: '<S29>/Multiport Switch' */
          wturbines_B.CoreSubsys[ForEach_itr]._drt =
            wturbines_B.CoreSubsys[ForEach_itr].Multiply1_g;
          break;

         case 2:
          /* Product: '<S29>/Divide2' incorporates:
           *  Constant: '<S29>/Constant10'
           *  Constant: '<S29>/Constant2'
           */
          wturbines_B.CoreSubsys[ForEach_itr]._drt_n = tmp_e *
            wturbines_B.CoreSubsys[ForEach_itr].ws_drt / tmp_5;

          /* MultiPortSwitch: '<S29>/Multiport Switch' */
          wturbines_B.CoreSubsys[ForEach_itr]._drt =
            wturbines_B.CoreSubsys[ForEach_itr]._drt_n;
          break;

         case 3:
          /* Product: '<S29>/Divide4' incorporates:
           *  Constant: '<S29>/Constant11'
           *  Constant: '<S29>/Constant12'
           */
          wturbines_B.CoreSubsys[ForEach_itr]._drt_o = tmp_e *
            wturbines_B.CoreSubsys[ForEach_itr].RateTransition13 / tmp_5;

          /* MultiPortSwitch: '<S29>/Multiport Switch' */
          wturbines_B.CoreSubsys[ForEach_itr]._drt =
            wturbines_B.CoreSubsys[ForEach_itr]._drt_o;
          break;

         case 4:
          /* MultiPortSwitch: '<S29>/Multiport Switch' */
          wturbines_B.CoreSubsys[ForEach_itr]._drt = 0.0;
          break;

         default:
          /* MultiPortSwitch: '<S29>/Multiport Switch' incorporates:
           *  Constant: '<S29>/Constant13'
           */
          wturbines_B.CoreSubsys[ForEach_itr]._drt =
            wturbines_cal->wturbines_CoreSubsys_cal.Constant13_Value;
          break;
        }

        /* End of MultiPortSwitch: '<S29>/Multiport Switch' */

        /* Switch: '<S29>/Derating' */
        wturbines_B.CoreSubsys[ForEach_itr]._sett =
          wturbines_B.CoreSubsys[ForEach_itr]._drt;
      }

      /* End of Switch: '<S29>/Derating' */

      /* RateTransition: '<S2>/Rate Transition4' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition4_e =
        wturbines_B.CoreSubsys[ForEach_itr].IC4;

      /* Chart: '<S11>/Wind Turbine State Machine' */
      wturbines_DW.CoreSubsys[ForEach_itr].sfEvent_g = wturbines_CALL_EVENT;
      if (wturbines_DW.CoreSubsys[ForEach_itr].is_active_c9_wturbines == 0) {
        wturbines_DW.CoreSubsys[ForEach_itr].is_active_c9_wturbines = 1U;
        wturbines_B.CoreSubsys[ForEach_itr].op_mode_m = op_mode_parked;
      } else {
        switch (wturbines_B.CoreSubsys[ForEach_itr].op_mode_m) {
         case op_mode_emergency_stop:
          if (wturbines_B.CoreSubsys[ForEach_itr].RateTransition2 <= tmp_f) {
            wturbines_B.CoreSubsys[ForEach_itr].op_mode_m = op_mode_parked;
          }
          break;

         case op_mode_parked:
          d_out = (wturbines_B.CoreSubsys[ForEach_itr].RateTransition2_b &&
                   (!wturbines_B.CoreSubsys[ForEach_itr].RateTransition3_j) &&
                   (wturbines_B.CoreSubsys[ForEach_itr].MovingAverage >= tmp_g));
          if (d_out) {
            wturbines_B.CoreSubsys[ForEach_itr].op_mode_m = op_mode_starting_up;
          }
          break;

         case op_mode_power_production:
          d_out = (((!wturbines_B.CoreSubsys[ForEach_itr].RateTransition2_b) &&
                    (!wturbines_B.CoreSubsys[ForEach_itr].RateTransition3_j)) ||
                   (wturbines_B.CoreSubsys[ForEach_itr].MovingAverage <= 0.5 *
                    tmp_g) || (wturbines_B.CoreSubsys[ForEach_itr].MovingAverage
                               >= *get_cut_out_wind_speed()));
          if (d_out) {
            wturbines_B.CoreSubsys[ForEach_itr].op_mode_m =
              op_mode_shutting_down;
          } else if (wturbines_B.CoreSubsys[ForEach_itr].RateTransition3_j) {
            wturbines_B.CoreSubsys[ForEach_itr].op_mode_m =
              op_mode_emergency_stop;
          } else if (wturbines_B.CoreSubsys[ForEach_itr].RateTransition2 < 0.1 *
                     tmp_h) {
            wturbines_B.CoreSubsys[ForEach_itr].op_mode_m = op_mode_starting_up;
          }
          break;

         case op_mode_shutting_down:
          d_out = (wturbines_B.CoreSubsys[ForEach_itr].RateTransition3_j ||
                   (wturbines_B.CoreSubsys[ForEach_itr].RateTransition2 >=
                    *get_ROT_EMG_MAX_TOL() * tmp_4));
          if (d_out) {
            wturbines_B.CoreSubsys[ForEach_itr].op_mode_m =
              op_mode_emergency_stop;
          } else if (wturbines_B.CoreSubsys[ForEach_itr].RateTransition2 <=
                     tmp_f) {
            wturbines_B.CoreSubsys[ForEach_itr].op_mode_m = op_mode_parked;
          }
          break;

         default:
          /* State starting_up */
          if (((wturbines_B.CoreSubsys[ForEach_itr].RateTransition4_e == 1) &&
               (wturbines_B.CoreSubsys[ForEach_itr].RateTransition2 >= tmp_h)) ||
              ((wturbines_B.CoreSubsys[ForEach_itr].RateTransition4_e == 2) &&
               (std::abs(wturbines_B.CoreSubsys[ForEach_itr]._sett -
                         wturbines_B.CoreSubsys[ForEach_itr].RateTransition2) <=
                *get_ROT_SPEED_SP_DIFF()))) {
            wturbines_B.CoreSubsys[ForEach_itr].op_mode_m =
              op_mode_power_production;
          } else {
            d_out = ((!wturbines_B.CoreSubsys[ForEach_itr].RateTransition2_b) ||
                     wturbines_B.CoreSubsys[ForEach_itr].RateTransition3_j ||
                     (wturbines_B.CoreSubsys[ForEach_itr].MovingAverage <= 0.5 *
                      tmp_g));
            if (d_out) {
              wturbines_B.CoreSubsys[ForEach_itr].op_mode_m =
                op_mode_shutting_down;
            }
          }
          break;
        }
      }

      /* RelationalOperator: '<S18>/Compare' incorporates:
       *  Constant: '<S18>/Constant'
       */
      wturbines_B.CoreSubsys[ForEach_itr].Compare =
        (wturbines_B.CoreSubsys[ForEach_itr].op_mode_m ==
         wturbines_cal->wturbines_CoreSubsys_cal.CompareToConstant3_const_a);

      /* RelationalOperator: '<S20>/Compare' incorporates:
       *  Constant: '<S20>/Constant'
       */
      wturbines_B.CoreSubsys[ForEach_itr].Compare_c =
        (wturbines_B.CoreSubsys[ForEach_itr].op_mode_m ==
         wturbines_cal->wturbines_CoreSubsys_cal.CompareToConstant5_const);

      /* RelationalOperator: '<S19>/Compare' incorporates:
       *  Constant: '<S19>/Constant'
       */
      wturbines_B.CoreSubsys[ForEach_itr].Compare_j =
        (wturbines_B.CoreSubsys[ForEach_itr].op_mode_m ==
         wturbines_cal->wturbines_CoreSubsys_cal.CompareToConstant4_const);

      /* Logic: '<S11>/OR1' */
      wturbines_B.CoreSubsys[ForEach_itr].OR1 =
        (wturbines_B.CoreSubsys[ForEach_itr].Compare ||
         wturbines_B.CoreSubsys[ForEach_itr].Compare_c ||
         wturbines_B.CoreSubsys[ForEach_itr].Compare_j);

      /* Relay: '<S151>/Relay' */
      u0 = wturbines_B.CoreSubsys[ForEach_itr].RateTransition13;
      y_Cp = tmp_j - 1.0;
      wturbines_DW.CoreSubsys[ForEach_itr].Relay_Mode = ((u0 >= tmp_j) || ((!(u0
        <= y_Cp)) && wturbines_DW.CoreSubsys[ForEach_itr].Relay_Mode));
      if (wturbines_DW.CoreSubsys[ForEach_itr].Relay_Mode) {
        /* Relay: '<S151>/Relay' */
        wturbines_B.CoreSubsys[ForEach_itr].Relay =
          wturbines_cal->wturbines_CoreSubsys_cal.Relay_YOn;
      } else {
        /* Relay: '<S151>/Relay' */
        wturbines_B.CoreSubsys[ForEach_itr].Relay =
          wturbines_cal->wturbines_CoreSubsys_cal.Relay_YOff;
      }

      /* RateTransition: '<S12>/Rate Transition3' */
      if (limitedCache) {
        wturbines_DW.CoreSubsys[ForEach_itr].RateTransition3_RdBufIdx =
          static_cast<int8_T>(wturbines_DW.CoreSubsys[ForEach_itr].
                              RateTransition3_RdBufIdx == 0);
      }

      /* RateTransition: '<S12>/Rate Transition3' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition3 =
        wturbines_DW.CoreSubsys[ForEach_itr]
        .RateTransition3_Buf[wturbines_DW.CoreSubsys[ForEach_itr].
        RateTransition3_RdBufIdx];

      /* Switch: '<S151>/Switch' */
      if (wturbines_B.CoreSubsys[ForEach_itr].Relay >
          wturbines_cal->wturbines_CoreSubsys_cal.Switch_Threshold_e) {
        /* Switch: '<S151>/Switch' incorporates:
         *  Constant: '<S151>/Constant1'
         */
        wturbines_B.CoreSubsys[ForEach_itr].Switch = tmp_6 / (tmp_4 * tmp_b);
      } else {
        /* Math: '<S151>/Square' */
        wturbines_B.CoreSubsys[ForEach_itr].Square_b =
          wturbines_B.CoreSubsys[ForEach_itr].RateTransition3 *
          wturbines_B.CoreSubsys[ForEach_itr].RateTransition3;

        /* Product: '<S151>/Product' incorporates:
         *  Constant: '<S151>/Constant'
         */
        wturbines_B.CoreSubsys[ForEach_itr].Product_b =
          wturbines_B.CoreSubsys[ForEach_itr].Square_b * *get_K_omega_sq();

        /* Switch: '<S151>/Switch' */
        wturbines_B.CoreSubsys[ForEach_itr].Switch =
          wturbines_B.CoreSubsys[ForEach_itr].Product_b;
      }

      /* End of Switch: '<S151>/Switch' */

      /* RelationalOperator: '<S150>/IsNaN1' incorporates:
       *  Constant: '<S150>/Constant1'
       */
      wturbines_B.CoreSubsys[ForEach_itr].IsNaN1 = rtIsNaN(tmp_a);

      /* Logic: '<S150>/NOT' */
      wturbines_B.CoreSubsys[ForEach_itr].is_not_nan =
        !wturbines_B.CoreSubsys[ForEach_itr].IsNaN1;

      /* Switch: '<S150>/Switch' */
      if (wturbines_B.CoreSubsys[ForEach_itr].is_not_nan) {
        /* Gain: '<S152>/Multiply' incorporates:
         *  Constant: '<S150>/Constant'
         */
        wturbines_B.CoreSubsys[ForEach_itr].Multiply_p =
          wturbines_cal->wturbines_CoreSubsys_cal.Multiply_Gain_c * tmp_c;

        /* Gain: '<S152>/Multiply1' */
        wturbines_B.CoreSubsys[ForEach_itr].Multiply1_e =
          wturbines_cal->wturbines_CoreSubsys_cal.Multiply1_Gain_f *
          wturbines_B.CoreSubsys[ForEach_itr].Multiply_p;

        /* Sum: '<S150>/Sum' */
        wturbines_B.CoreSubsys[ForEach_itr].Sum_d =
          wturbines_B.CoreSubsys[ForEach_itr].RateTransition3 -
          wturbines_B.CoreSubsys[ForEach_itr].Multiply1_e;

        /* Product: '<S150>/Product1' incorporates:
         *  Constant: '<S150>/Constant1'
         */
        wturbines_B.CoreSubsys[ForEach_itr].Product1_n =
          wturbines_B.CoreSubsys[ForEach_itr].Sum_d * tmp_a;

        /* Math: '<S150>/Exp'
         *
         * About '<S150>/Exp':
         *  Operator: exp
         */
        wturbines_B.CoreSubsys[ForEach_itr].Exp = std::exp
          (wturbines_B.CoreSubsys[ForEach_itr].Product1_n);

        /* Lookup_n-D: '<S150>/&#x3B2;(ws)' incorporates:
         *  RateTransition: '<S12>/Rate Transition13'
         */
        wturbines_B.CoreSubsys[ForEach_itr].ws = look1_binlcapw
          (wturbines_B.CoreSubsys[ForEach_itr].RateTransition13, get_u_all(),
           get_pitch_all(), 14U);

        /* Gain: '<S154>/Gain1' */
        wturbines_B.CoreSubsys[ForEach_itr].Gain1_o =
          wturbines_cal->wturbines_CoreSubsys_cal.Gain1_Gain *
          wturbines_B.CoreSubsys[ForEach_itr].ws;

        /* Product: '<S150>/Product' */
        wturbines_B.CoreSubsys[ForEach_itr].Product_n =
          wturbines_B.CoreSubsys[ForEach_itr].Gain1_o *
          wturbines_B.CoreSubsys[ForEach_itr].Exp;

        /* Switch: '<S150>/Switch' */
        wturbines_B.CoreSubsys[ForEach_itr].Switch_l =
          wturbines_B.CoreSubsys[ForEach_itr].Product_n;
      } else {
        /* Switch: '<S150>/Switch' incorporates:
         *  Constant: '<S150>/Constant2'
         */
        wturbines_B.CoreSubsys[ForEach_itr].Switch_l =
          wturbines_cal->wturbines_CoreSubsys_cal.Constant2_Value;
      }

      /* End of Switch: '<S150>/Switch' */

      /* Sum: '<S29>/Sum' */
      wturbines_B.CoreSubsys[ForEach_itr].e_t =
        wturbines_B.CoreSubsys[ForEach_itr].RateTransition2 -
        wturbines_B.CoreSubsys[ForEach_itr]._sett;

      /* Gain: '<S252>/Proportional Gain' */
      wturbines_B.CoreSubsys[ForEach_itr].ProportionalGain = *get_K_p_gen() *
        wturbines_B.CoreSubsys[ForEach_itr].e_t;

      /* Sum: '<S157>/Sum' incorporates:
       *  Sum: '<S156>/Sum'
       */
      y_Cp = wturbines_B.CoreSubsys[ForEach_itr].ws_drt -
        wturbines_B.CoreSubsys[ForEach_itr].RateTransition13;

      /* Sum: '<S157>/Sum' */
      wturbines_B.CoreSubsys[ForEach_itr].ws_drwst_p = y_Cp;

      /* Product: '<S157>/Divide' */
      wturbines_B.CoreSubsys[ForEach_itr].Divide =
        wturbines_B.CoreSubsys[ForEach_itr].Pref /
        wturbines_B.CoreSubsys[ForEach_itr]._sett;

      /* Gain: '<S157>/Gain' */
      u0 = 1.0 / tmp_b;

      /* Gain: '<S157>/Gain' */
      wturbines_B.CoreSubsys[ForEach_itr].Gain = u0 *
        wturbines_B.CoreSubsys[ForEach_itr].Divide;

      /* Sum: '<S156>/Sum' */
      wturbines_B.CoreSubsys[ForEach_itr].ws_drwst_o = y_Cp;

      /* Gain: '<S199>/Proportional Gain' */
      wturbines_B.CoreSubsys[ForEach_itr].ProportionalGain_d = *get_K_p_pitch() *
        wturbines_B.CoreSubsys[ForEach_itr].e_t;
    }

    /* Integrator: '<S247>/Integrator' */
    wturbines_B.CoreSubsys[ForEach_itr].Integrator =
      wturbines_X.CoreSubsys[ForEach_itr].Integrator_CSTATE_o;

    /* Integrator: '<S194>/Integrator' */
    wturbines_B.CoreSubsys[ForEach_itr].Integrator_i =
      wturbines_X.CoreSubsys[ForEach_itr].Integrator_CSTATE_l;

    /* Integrator: '<S132>/Integrator' */
    wturbines_B.CoreSubsys[ForEach_itr].Integrator_e =
      wturbines_X.CoreSubsys[ForEach_itr].Integrator_CSTATE_e;
    if (tmp) {
      /* MultiPortSwitch: '<S27>/Multiport Switch' incorporates:
       *  Constant: '<S27>/Mode'
       */
      switch (static_cast<int32_T>(*get_rotor_speed_ref_mode())) {
       case 1:
        /* Lookup_n-D: '<S27>/&#x3C9;_ss(u)' incorporates:
         *  RateTransition: '<S12>/Rate Transition13'
         */
        wturbines_B.CoreSubsys[ForEach_itr]._sst = look1_binlxpw
          (wturbines_B.CoreSubsys[ForEach_itr].RateTransition13,
           get_u_rotor_speed_all(), get_rotor_speed_all(), 1U);

        /* Gain: '<S31>/Multiply' */
        wturbines_B.CoreSubsys[ForEach_itr].Multiply_g =
          wturbines_cal->wturbines_CoreSubsys_cal.Multiply_Gain_e *
          wturbines_B.CoreSubsys[ForEach_itr]._sst;

        /* Gain: '<S31>/Multiply1' */
        wturbines_B.CoreSubsys[ForEach_itr].Multiply1_j =
          wturbines_cal->wturbines_CoreSubsys_cal.Multiply1_Gain_d *
          wturbines_B.CoreSubsys[ForEach_itr].Multiply_g;

        /* MultiPortSwitch: '<S27>/Multiport Switch' */
        wturbines_B.CoreSubsys[ForEach_itr]._rreft =
          wturbines_B.CoreSubsys[ForEach_itr].Multiply1_j;
        break;

       case 2:
        /* Gain: '<S32>/Multiply' incorporates:
         *  Constant: '<S27>/&#x3C9;_set'
         */
        wturbines_B.CoreSubsys[ForEach_itr].Multiply_l =
          wturbines_cal->wturbines_CoreSubsys_cal.Multiply_Gain_m * tmp_c;

        /* Gain: '<S32>/Multiply1' */
        wturbines_B.CoreSubsys[ForEach_itr].Multiply1_p =
          wturbines_cal->wturbines_CoreSubsys_cal.Multiply1_Gain_a *
          wturbines_B.CoreSubsys[ForEach_itr].Multiply_l;

        /* MultiPortSwitch: '<S27>/Multiport Switch' */
        wturbines_B.CoreSubsys[ForEach_itr]._rreft =
          wturbines_B.CoreSubsys[ForEach_itr].Multiply1_p;
        break;

       case 3:
        /* Product: '<S27>/Divide4' incorporates:
         *  Constant: '<S27>/Constant11'
         *  Constant: '<S27>/Constant12'
         */
        wturbines_B.CoreSubsys[ForEach_itr]._rreft_l = tmp_e *
          wturbines_B.CoreSubsys[ForEach_itr].RateTransition13 / tmp_5;

        /* MultiPortSwitch: '<S27>/Multiport Switch' */
        wturbines_B.CoreSubsys[ForEach_itr]._rreft =
          wturbines_B.CoreSubsys[ForEach_itr]._rreft_l;
        break;

       default:
        /* MultiPortSwitch: '<S27>/Multiport Switch' incorporates:
         *  Constant: '<S27>/Constant13'
         */
        wturbines_B.CoreSubsys[ForEach_itr]._rreft =
          wturbines_cal->wturbines_CoreSubsys_cal.Constant13_Value_n;
        break;
      }

      /* Sum: '<S27>/Sum' */
      wturbines_B.CoreSubsys[ForEach_itr].e_rt =
        wturbines_B.CoreSubsys[ForEach_itr].RateTransition2 -
        wturbines_B.CoreSubsys[ForEach_itr]._rreft;

      /* Gain: '<S137>/Proportional Gain' */
      wturbines_B.CoreSubsys[ForEach_itr].ProportionalGain_p = *get_A_k() *
        wturbines_B.CoreSubsys[ForEach_itr].e_rt;

      /* Delay: '<S27>/Delay' */
      wturbines_B.CoreSubsys[ForEach_itr].Delay =
        wturbines_DW.CoreSubsys[ForEach_itr].Delay_DSTATE;

      /* Gain: '<S96>/Gain' */
      wturbines_B.CoreSubsys[ForEach_itr].Gain_k =
        wturbines_cal->wturbines_CoreSubsys_cal.Gain_Gain *
        wturbines_B.CoreSubsys[ForEach_itr].Delay;

      /* S-Function (sfix_look1_dyn): '<S43>/Gain Dynamic Lookup' incorporates:
       *  Constant: '<S33>/Gains'
       *  Constant: '<S35>/Internal breakpoints'
       */
      /* Dynamic Look-Up Table Block: '<S43>/Gain Dynamic Lookup'
       * Input0  Data Type:  Floating Point real_T
       * Input1  Data Type:  Floating Point real_T
       * Input2  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       */
      LookUp_real_T_real_T( &(wturbines_B.CoreSubsys[ForEach_itr].
        GainDynamicLookup), &wturbines_cal->
                           wturbines_CoreSubsys_cal.Gains_Value[0],
                           wturbines_B.CoreSubsys[ForEach_itr].Gain_k,
                           &wturbines_cal->wturbines_CoreSubsys_cal.Gainscheduler_GainArrayBreakpoi
                           [0], 1U);

      /* Gain: '<S33>/Gain' */
      wturbines_B.CoreSubsys[ForEach_itr].Gain_h = *get_K_p_pitch_gs() *
        wturbines_B.CoreSubsys[ForEach_itr].GainDynamicLookup;

      /* Product: '<S83>/PProd Out' */
      wturbines_B.CoreSubsys[ForEach_itr].PProdOut =
        wturbines_B.CoreSubsys[ForEach_itr].e_rt *
        wturbines_B.CoreSubsys[ForEach_itr].Gain_h;
    }

    /* Integrator: '<S78>/Integrator' */
    wturbines_B.CoreSubsys[ForEach_itr].Integrator_d =
      wturbines_X.CoreSubsys[ForEach_itr].Integrator_CSTATE_oj;

    /* Sum: '<S87>/Sum' */
    wturbines_B.CoreSubsys[ForEach_itr].Sum = wturbines_B.CoreSubsys[ForEach_itr]
      .PProdOut + wturbines_B.CoreSubsys[ForEach_itr].Integrator_d;

    /* MultiPortSwitch: '<S24>/Multiport Switch' */
    switch (wturbines_B.CoreSubsys[ForEach_itr].RateTransition4_e) {
     case 1:
      /* MultiPortSwitch: '<S24>/Multiport Switch' */
      wturbines_B.CoreSubsys[ForEach_itr].MultiportSwitch[0] =
        wturbines_B.CoreSubsys[ForEach_itr].Switch;
      wturbines_B.CoreSubsys[ForEach_itr].MultiportSwitch[1] =
        wturbines_B.CoreSubsys[ForEach_itr].Switch_l;
      break;

     case 2:
      /* Switch: '<S157>/Derating' */
      if (wturbines_B.CoreSubsys[ForEach_itr].ws_drwst_p >
          wturbines_cal->wturbines_CoreSubsys_cal.Derating_Threshold) {
        /* Sum: '<S256>/Sum' */
        wturbines_B.CoreSubsys[ForEach_itr].Sum_b =
          wturbines_B.CoreSubsys[ForEach_itr].ProportionalGain +
          wturbines_B.CoreSubsys[ForEach_itr].Integrator;

        /* Switch: '<S157>/Derating' */
        wturbines_B.CoreSubsys[ForEach_itr].Derating =
          wturbines_B.CoreSubsys[ForEach_itr].Sum_b;
      } else {
        /* Switch: '<S157>/Derating' */
        wturbines_B.CoreSubsys[ForEach_itr].Derating =
          wturbines_B.CoreSubsys[ForEach_itr].Gain;
      }

      /* End of Switch: '<S157>/Derating' */

      /* Switch: '<S156>/Derating' */
      if (wturbines_B.CoreSubsys[ForEach_itr].ws_drwst_o >
          wturbines_cal->wturbines_CoreSubsys_cal.Derating_Threshold_c) {
        /* Switch: '<S156>/Derating' incorporates:
         *  Constant: '<S156>/Constant'
         */
        wturbines_B.CoreSubsys[ForEach_itr].Derating_e =
          wturbines_cal->wturbines_CoreSubsys_cal.Constant_Value_l;
      } else {
        /* Sum: '<S203>/Sum' */
        wturbines_B.CoreSubsys[ForEach_itr].Sum_n =
          wturbines_B.CoreSubsys[ForEach_itr].ProportionalGain_d +
          wturbines_B.CoreSubsys[ForEach_itr].Integrator_i;

        /* Switch: '<S156>/Derating' */
        wturbines_B.CoreSubsys[ForEach_itr].Derating_e =
          wturbines_B.CoreSubsys[ForEach_itr].Sum_n;
      }

      /* End of Switch: '<S156>/Derating' */

      /* Saturate: '<S29>/Saturation' */
      u0 = wturbines_B.CoreSubsys[ForEach_itr].Derating_e;
      y_Cp = wturbines_cal->wturbines_CoreSubsys_cal.Saturation_LowerSat;
      u2 = wturbines_cal->wturbines_CoreSubsys_cal.Saturation_UpperSat;
      if (u0 > u2) {
        /* Saturate: '<S29>/Saturation' */
        wturbines_B.CoreSubsys[ForEach_itr].Saturation_k = u2;
      } else if (u0 < y_Cp) {
        /* Saturate: '<S29>/Saturation' */
        wturbines_B.CoreSubsys[ForEach_itr].Saturation_k = y_Cp;
      } else {
        /* Saturate: '<S29>/Saturation' */
        wturbines_B.CoreSubsys[ForEach_itr].Saturation_k = u0;
      }

      /* End of Saturate: '<S29>/Saturation' */

      /* MultiPortSwitch: '<S24>/Multiport Switch' */
      wturbines_B.CoreSubsys[ForEach_itr].MultiportSwitch[0] =
        wturbines_B.CoreSubsys[ForEach_itr].Derating;
      wturbines_B.CoreSubsys[ForEach_itr].MultiportSwitch[1] =
        wturbines_B.CoreSubsys[ForEach_itr].Saturation_k;
      break;

     case 3:
      /* MultiPortSwitch: '<S24>/Multiport Switch' */
      wturbines_B.CoreSubsys[ForEach_itr].MultiportSwitch[0] = 0.0;
      wturbines_B.CoreSubsys[ForEach_itr].MultiportSwitch[1] = 0.0;
      break;

     case 4:
      /* Sum: '<S141>/Sum' */
      wturbines_B.CoreSubsys[ForEach_itr].Sum_a =
        wturbines_B.CoreSubsys[ForEach_itr].ProportionalGain_p +
        wturbines_B.CoreSubsys[ForEach_itr].Integrator_e;

      /* MultiPortSwitch: '<S24>/Multiport Switch' */
      wturbines_B.CoreSubsys[ForEach_itr].MultiportSwitch[0] =
        wturbines_B.CoreSubsys[ForEach_itr].Sum_a;
      wturbines_B.CoreSubsys[ForEach_itr].MultiportSwitch[1] =
        wturbines_B.CoreSubsys[ForEach_itr].Sum;
      break;

     default:
      /* MultiPortSwitch: '<S24>/Multiport Switch' */
      wturbines_B.CoreSubsys[ForEach_itr].MultiportSwitch[0] = 0.0;
      wturbines_B.CoreSubsys[ForEach_itr].MultiportSwitch[1] = 0.0;
      break;
    }

    /* End of MultiPortSwitch: '<S24>/Multiport Switch' */

    /* Switch: '<S11>/Switch2' */
    if (wturbines_B.CoreSubsys[ForEach_itr].OR1) {
      /* Switch: '<S11>/Switch2' */
      wturbines_B.CoreSubsys[ForEach_itr].PitchSpt =
        wturbines_B.CoreSubsys[ForEach_itr].Gain1_f;
    } else {
      /* Switch: '<S11>/Switch2' */
      wturbines_B.CoreSubsys[ForEach_itr].PitchSpt =
        wturbines_B.CoreSubsys[ForEach_itr].MultiportSwitch[1];
    }

    /* End of Switch: '<S11>/Switch2' */

    /* RateLimiter: '<S276>/Rate Limiter' */
    if (wturbines_DW.CoreSubsys[ForEach_itr].LastMajorTime == (rtInf)) {
      /* RateLimiter: '<S276>/Rate Limiter' */
      wturbines_B.CoreSubsys[ForEach_itr].RateLimiter_n =
        wturbines_B.CoreSubsys[ForEach_itr].PitchSpt;
    } else {
      y_Cp = wturbines_M->Timing.t[0];
      u2 = y_Cp - wturbines_DW.CoreSubsys[ForEach_itr].LastMajorTime;
      if (wturbines_DW.CoreSubsys[ForEach_itr].LastMajorTime == y_Cp) {
        if (wturbines_DW.CoreSubsys[ForEach_itr].PrevLimited) {
          /* RateLimiter: '<S276>/Rate Limiter' */
          wturbines_B.CoreSubsys[ForEach_itr].RateLimiter_n =
            wturbines_DW.CoreSubsys[ForEach_itr].PrevY_d;
        } else {
          /* RateLimiter: '<S276>/Rate Limiter' */
          wturbines_B.CoreSubsys[ForEach_itr].RateLimiter_n =
            wturbines_B.CoreSubsys[ForEach_itr].PitchSpt;
        }
      } else {
        u0 = tmp_k * 0.017453292519943295;
        u0 *= u2;
        y_Cp = wturbines_B.CoreSubsys[ForEach_itr].PitchSpt -
          wturbines_DW.CoreSubsys[ForEach_itr].PrevY_d;
        if (y_Cp > u0) {
          /* RateLimiter: '<S276>/Rate Limiter' */
          wturbines_B.CoreSubsys[ForEach_itr].RateLimiter_n =
            wturbines_DW.CoreSubsys[ForEach_itr].PrevY_d + u0;
          limitedCache = true;
        } else {
          u0 = -tmp_k * 0.017453292519943295;
          u2 *= u0;
          if (y_Cp < u2) {
            /* RateLimiter: '<S276>/Rate Limiter' */
            wturbines_B.CoreSubsys[ForEach_itr].RateLimiter_n =
              wturbines_DW.CoreSubsys[ForEach_itr].PrevY_d + u2;
            limitedCache = true;
          } else {
            /* RateLimiter: '<S276>/Rate Limiter' */
            wturbines_B.CoreSubsys[ForEach_itr].RateLimiter_n =
              wturbines_B.CoreSubsys[ForEach_itr].PitchSpt;
            limitedCache = false;
          }
        }

        if (rtsiIsModeUpdateTimeStep(&wturbines_M->solverInfo)) {
          wturbines_DW.CoreSubsys[ForEach_itr].PrevLimited = limitedCache;
        }
      }
    }

    /* Gain: '<S283>/Gain' */
    wturbines_B.CoreSubsys[ForEach_itr].Gain_n =
      wturbines_cal->wturbines_CoreSubsys_cal.Gain_Gain_f *
      wturbines_B.CoreSubsys[ForEach_itr].RateLimiter_n;

    /* Lookup_n-D: '<S14>/Ct(&#x3BB;, &#x3B2;)' */
    /*
     * About '<S14>/Ct(&#x3BB;, &#x3B2;)':
     *       Table size:  20 x 20
     *    Interpolation:  Spline
     *    Extrapolation:  None - Clip
     *   Breakpt Search:  Binary
     *    Breakpt Cache:  OFF
     */
    {
      real_T rt_LUTuVect[2];
      rt_LUTuVect[0] = wturbines_B.CoreSubsys[ForEach_itr].t_c;
      rt_LUTuVect[1] = wturbines_B.CoreSubsys[ForEach_itr].Gain_n;
      wturbines_B.CoreSubsys[ForEach_itr].Ct = look_SplNBinCZcd(2U, rt_LUTuVect,
        (rt_LUTSplineWork*)&wturbines_DW.CoreSubsys[ForEach_itr].SWork[0]);
    }

    /* Saturate: '<S14>/Saturation1' */
    u0 = wturbines_B.CoreSubsys[ForEach_itr].Ct;
    y_Cp = wturbines_cal->wturbines_CoreSubsys_cal.Saturation1_LowerSat;
    u2 = wturbines_cal->wturbines_CoreSubsys_cal.Saturation1_UpperSat;
    if (u0 > u2) {
      /* Saturate: '<S14>/Saturation1' */
      wturbines_B.CoreSubsys[ForEach_itr].Ct_n = u2;
    } else if (u0 < y_Cp) {
      /* Saturate: '<S14>/Saturation1' */
      wturbines_B.CoreSubsys[ForEach_itr].Ct_n = y_Cp;
    } else {
      /* Saturate: '<S14>/Saturation1' */
      wturbines_B.CoreSubsys[ForEach_itr].Ct_n = u0;
    }

    /* End of Saturate: '<S14>/Saturation1' */

    /* RateTransition: '<S2>/Rate Transition8' */
    if (tmp) {
      /* RateTransition: '<S2>/Rate Transition8' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition8 =
        wturbines_B.CoreSubsys[ForEach_itr].Ct_n;

      /* RateTransition: '<S2>/Rate Transition9' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition9 =
        wturbines_B.CoreSubsys[ForEach_itr].yaw;

      /* RateTransition: '<S12>/Rate Transition6' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition6_o =
        wturbines_B.CoreSubsys[ForEach_itr].RateLimiter;

      /* RateTransition: '<S12>/Rate Transition' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition_k =
        wturbines_B.CoreSubsys[ForEach_itr].RateTransition6_o;

      /* RateTransition: '<S12>/Rate Transition5' */
      if (wturbines_M->Timing.RateInteraction.TID1_2 == 1) {
        wturbines_DW.CoreSubsys[ForEach_itr].RateTransition5_RdBufIdx =
          static_cast<int8_T>(wturbines_DW.CoreSubsys[ForEach_itr].
                              RateTransition5_RdBufIdx == 0);
      }

      /* RateTransition: '<S12>/Rate Transition5' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition5_i =
        wturbines_DW.CoreSubsys[ForEach_itr]
        .RateTransition5_Buf[wturbines_DW.CoreSubsys[ForEach_itr].
        RateTransition5_RdBufIdx];

      /* RelationalOperator: '<S22>/Compare' incorporates:
       *  Constant: '<S22>/Constant'
       */
      wturbines_B.CoreSubsys[ForEach_itr].Compare_m =
        (wturbines_B.CoreSubsys[ForEach_itr].op_mode_m !=
         wturbines_cal->wturbines_CoreSubsys_cal.CompareToConstant9_const);
    }

    /* End of RateTransition: '<S2>/Rate Transition8' */

    /* Gain: '<S14>/Multiply2' */
    wturbines_B.CoreSubsys[ForEach_itr].GenSpd = tmp_b *
      wturbines_B.CoreSubsys[ForEach_itr].RotSpd;

    /* Switch: '<S11>/Switch5' */
    if (wturbines_B.CoreSubsys[ForEach_itr].Compare_m) {
      /* Switch: '<S11>/Switch5' incorporates:
       *  Constant: '<S11>/Constant6'
       */
      wturbines_B.CoreSubsys[ForEach_itr].Switch5 =
        wturbines_cal->wturbines_CoreSubsys_cal.Constant6_Value_k;
    } else {
      /* Switch: '<S11>/Switch5' */
      wturbines_B.CoreSubsys[ForEach_itr].Switch5 =
        wturbines_B.CoreSubsys[ForEach_itr].MultiportSwitch[0];
    }

    /* End of Switch: '<S11>/Switch5' */

    /* Saturate: '<S11>/Saturation' */
    u0 = wturbines_B.CoreSubsys[ForEach_itr].Switch5;
    y_Cp = wturbines_cal->wturbines_CoreSubsys_cal.Saturation_LowerSat_c;
    u2 = *get_max_gen_torque();
    if (u0 > u2) {
      /* Saturate: '<S11>/Saturation' */
      wturbines_B.CoreSubsys[ForEach_itr].Tgen = u2;
    } else if (u0 < y_Cp) {
      /* Saturate: '<S11>/Saturation' */
      wturbines_B.CoreSubsys[ForEach_itr].Tgen = y_Cp;
    } else {
      /* Saturate: '<S11>/Saturation' */
      wturbines_B.CoreSubsys[ForEach_itr].Tgen = u0;
    }

    /* End of Saturate: '<S11>/Saturation' */

    /* Product: '<S279>/Product' */
    wturbines_B.CoreSubsys[ForEach_itr].Product_m =
      wturbines_B.CoreSubsys[ForEach_itr].GenSpd *
      wturbines_B.CoreSubsys[ForEach_itr].Tgen;

    /* Gain: '<S279>/Multiply' */
    wturbines_B.CoreSubsys[ForEach_itr].Multiply = tmp_9 *
      wturbines_B.CoreSubsys[ForEach_itr].Product_m;

    /* RateTransition: '<S12>/Rate Transition1' */
    if (tmp) {
      /* RateTransition: '<S12>/Rate Transition4' */
      limitedCache = (wturbines_M->Timing.RateInteraction.TID1_2 == 1);
      if (limitedCache) {
        wturbines_DW.CoreSubsys[ForEach_itr].RateTransition1_RdBufIdx =
          static_cast<int8_T>(wturbines_DW.CoreSubsys[ForEach_itr].
                              RateTransition1_RdBufIdx == 0);
      }

      /* RateTransition: '<S12>/Rate Transition1' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition1_h =
        wturbines_DW.CoreSubsys[ForEach_itr]
        .RateTransition1_Buf[wturbines_DW.CoreSubsys[ForEach_itr].
        RateTransition1_RdBufIdx];

      /* Gain: '<S10>/Gain' */
      wturbines_B.CoreSubsys[ForEach_itr].Gain_i =
        wturbines_cal->wturbines_CoreSubsys_cal.Gain_Gain_d *
        wturbines_B.CoreSubsys[ForEach_itr].RateTransition2;

      /* RateTransition: '<S12>/Rate Transition4' */
      if (limitedCache) {
        wturbines_DW.CoreSubsys[ForEach_itr].RateTransition4_RdBufIdx =
          static_cast<int8_T>(wturbines_DW.CoreSubsys[ForEach_itr].
                              RateTransition4_RdBufIdx == 0);
      }

      /* RateTransition: '<S12>/Rate Transition4' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition4 =
        wturbines_DW.CoreSubsys[ForEach_itr]
        .RateTransition4_Buf[wturbines_DW.CoreSubsys[ForEach_itr].
        RateTransition4_RdBufIdx];
    }

    /* Gain: '<S15>/Gain' */
    wturbines_B.CoreSubsys[ForEach_itr].Gain_o =
      wturbines_cal->wturbines_CoreSubsys_cal.Gain_Gain_i *
      wturbines_B.CoreSubsys[ForEach_itr].PitchSpt;

    /* RateTransition: '<S2>/Rate Transition7' */
    if (tmp) {
      if (wturbines_M->Timing.RateInteraction.TID1_3 == 1) {
        wturbines_DW.CoreSubsys[ForEach_itr].RateTransition7_WrBufIdx =
          static_cast<int8_T>(wturbines_DW.CoreSubsys[ForEach_itr].
                              RateTransition7_WrBufIdx == 0);
      }

      i = wturbines_DW.CoreSubsys[ForEach_itr].RateTransition7_WrBufIdx << 3;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition7_Buf[i] =
        wturbines_B.CoreSubsys[ForEach_itr].RateTransition_k;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition7_Buf[i + 1] =
        wturbines_B.CoreSubsys[ForEach_itr].RateTransition5_i;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition7_Buf[i + 2] =
        wturbines_B.CoreSubsys[ForEach_itr].Multiply;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition7_Buf[i + 3] =
        wturbines_B.CoreSubsys[ForEach_itr].RateTransition1_h;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition7_Buf[i + 4] =
        wturbines_B.CoreSubsys[ForEach_itr].Gain_i;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition7_Buf[i + 5] =
        wturbines_B.CoreSubsys[ForEach_itr].RateTransition4;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition7_Buf[i + 6] =
        wturbines_B.CoreSubsys[ForEach_itr].Gain_o;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition7_Buf[i + 7] =
        wturbines_B.CoreSubsys[ForEach_itr].Tgen;

      /* RelationalOperator: '<S21>/Compare' incorporates:
       *  Constant: '<S21>/Constant'
       */
      wturbines_B.CoreSubsys[ForEach_itr].Compare_b =
        (wturbines_B.CoreSubsys[ForEach_itr].op_mode_m ==
         wturbines_cal->wturbines_CoreSubsys_cal.CompareToConstant6_const);

      /* SignalConversion: '<S33>/Signal Copy' incorporates:
       *  Constant: '<S33>/Gains'
       */
      wturbines_B.CoreSubsys[ForEach_itr].I[0] =
        wturbines_cal->wturbines_CoreSubsys_cal.Gains_Value[0];
      wturbines_B.CoreSubsys[ForEach_itr].I[1] =
        wturbines_cal->wturbines_CoreSubsys_cal.Gains_Value[1];

      /* S-Function (sfix_look1_dyn): '<S42>/Gain Dynamic Lookup' incorporates:
       *  Constant: '<S35>/Internal breakpoints'
       */
      /* Dynamic Look-Up Table Block: '<S42>/Gain Dynamic Lookup'
       * Input0  Data Type:  Floating Point real_T
       * Input1  Data Type:  Floating Point real_T
       * Input2  Data Type:  Floating Point real_T
       * Output0 Data Type:  Floating Point real_T
       * Lookup Method: Linear_Endpoint
       *
       */
      LookUp_real_T_real_T( &(wturbines_B.CoreSubsys[ForEach_itr].
        GainDynamicLookup_f), &wturbines_B.CoreSubsys[ForEach_itr].I[0],
                           wturbines_B.CoreSubsys[ForEach_itr].Gain_k,
                           &wturbines_cal->wturbines_CoreSubsys_cal.Gainscheduler_GainArrayBreakpoi
                           [0], 1U);

      /* Gain: '<S33>/Gain1' */
      wturbines_B.CoreSubsys[ForEach_itr].Gain1_g = *get_K_i_pitch_gs() *
        wturbines_B.CoreSubsys[ForEach_itr].GainDynamicLookup_f;

      /* Product: '<S75>/IProd Out' */
      wturbines_B.CoreSubsys[ForEach_itr].IProdOut =
        wturbines_B.CoreSubsys[ForEach_itr].e_rt *
        wturbines_B.CoreSubsys[ForEach_itr].Gain1_g;

      /* Gain: '<S129>/Integral Gain' */
      wturbines_B.CoreSubsys[ForEach_itr].IntegralGain = *get_B_k() *
        wturbines_B.CoreSubsys[ForEach_itr].e_rt;
    }

    /* StateSpace: '<S34>/H&#x221E; controller ' */
    wturbines_B.CoreSubsys[ForEach_itr].Hcontroller = *get_C_k() *
      wturbines_X.CoreSubsys[ForEach_itr].Hcontroller_CSTATE;
    if (tmp) {
      /* Gain: '<S158>/Multiply' */
      wturbines_B.CoreSubsys[ForEach_itr].Multiply_k =
        wturbines_cal->wturbines_CoreSubsys_cal.Multiply_Gain_g *
        wturbines_B.CoreSubsys[ForEach_itr]._sett;

      /* Gain: '<S158>/Multiply1' */
      wturbines_B.CoreSubsys[ForEach_itr].Multiply1 =
        wturbines_cal->wturbines_CoreSubsys_cal.Multiply1_Gain_o *
        wturbines_B.CoreSubsys[ForEach_itr].Multiply_k;

      /* Gain: '<S191>/Integral Gain' */
      wturbines_B.CoreSubsys[ForEach_itr].IntegralGain_g = *get_K_i_pitch() *
        wturbines_B.CoreSubsys[ForEach_itr].e_t;

      /* Gain: '<S244>/Integral Gain' */
      wturbines_B.CoreSubsys[ForEach_itr].IntegralGain_a = *get_K_i_gen() *
        wturbines_B.CoreSubsys[ForEach_itr].e_t;

      /* Gain: '<S265>/Gain' incorporates:
       *  Constant: '<S265>/Constant'
       */
      wturbines_B.CoreSubsys[ForEach_itr]._grated = tmp_b * tmp_c;

      /* Switch: '<S11>/Switch3' */
      if (wturbines_B.CoreSubsys[ForEach_itr].Compare_b) {
        /* Switch: '<S11>/Switch3' incorporates:
         *  Constant: '<S11>/Constant3'
         */
        wturbines_B.CoreSubsys[ForEach_itr].Tbrake = tmp_i / tmp_b;
      } else {
        /* RelationalOperator: '<S17>/Compare' incorporates:
         *  Constant: '<S17>/Constant'
         */
        wturbines_B.CoreSubsys[ForEach_itr].Compare_i =
          (wturbines_B.CoreSubsys[ForEach_itr].op_mode_m ==
           wturbines_cal->wturbines_CoreSubsys_cal.CompareToConstant_const);

        /* Switch: '<S11>/Switch' */
        if (wturbines_B.CoreSubsys[ForEach_itr].Compare_i) {
          /* Switch: '<S11>/Switch' incorporates:
           *  Constant: '<S11>/Constant1'
           */
          wturbines_B.CoreSubsys[ForEach_itr].Switch_a = tmp_i;
        } else {
          /* Switch: '<S11>/Switch' incorporates:
           *  Constant: '<S11>/Constant'
           */
          wturbines_B.CoreSubsys[ForEach_itr].Switch_a =
            wturbines_cal->wturbines_CoreSubsys_cal.Constant_Value;
        }

        /* Switch: '<S11>/Switch3' */
        wturbines_B.CoreSubsys[ForEach_itr].Tbrake =
          wturbines_B.CoreSubsys[ForEach_itr].Switch_a;
      }

      /* RateTransition: '<S12>/Rate Transition7' incorporates:
       *  RateTransition: '<S12>/Rate Transition10'
       *  RateTransition: '<S12>/Rate Transition11'
       *  RateTransition: '<S12>/Rate Transition12'
       *  RateTransition: '<S12>/Rate Transition8'
       *  RateTransition: '<S12>/Rate Transition9'
       */
      limitedCache = (wturbines_M->Timing.RateInteraction.TID1_2 == 1);
      if (limitedCache) {
        wturbines_DW.CoreSubsys[ForEach_itr].RateTransition7_WrBufIdx_e =
          static_cast<int8_T>(wturbines_DW.CoreSubsys[ForEach_itr].
                              RateTransition7_WrBufIdx_e == 0);
      }

      wturbines_DW.CoreSubsys[ForEach_itr]
        .RateTransition7_Buf_h[wturbines_DW.CoreSubsys[ForEach_itr].
        RateTransition7_WrBufIdx_e] = wturbines_B.CoreSubsys[ForEach_itr].
        RateLimiter1;

      /* End of RateTransition: '<S12>/Rate Transition7' */

      /* RateTransition: '<S12>/Rate Transition9' */
      if (limitedCache) {
        wturbines_DW.CoreSubsys[ForEach_itr].RateTransition9_WrBufIdx =
          static_cast<int8_T>(wturbines_DW.CoreSubsys[ForEach_itr].
                              RateTransition9_WrBufIdx == 0);
      }

      wturbines_DW.CoreSubsys[ForEach_itr]
        .RateTransition9_Buf[wturbines_DW.CoreSubsys[ForEach_itr].
        RateTransition9_WrBufIdx] = wturbines_B.CoreSubsys[ForEach_itr].RotSpd;

      /* RateTransition: '<S12>/Rate Transition8' */
      if (limitedCache) {
        wturbines_DW.CoreSubsys[ForEach_itr].RateTransition8_WrBufIdx =
          static_cast<int8_T>(wturbines_DW.CoreSubsys[ForEach_itr].
                              RateTransition8_WrBufIdx == 0);
      }

      wturbines_DW.CoreSubsys[ForEach_itr]
        .RateTransition8_Buf[wturbines_DW.CoreSubsys[ForEach_itr].
        RateTransition8_WrBufIdx] = wturbines_B.CoreSubsys[ForEach_itr].
        RateLimiter_p;

      /* RateTransition: '<S12>/Rate Transition10' */
      if (limitedCache) {
        wturbines_DW.CoreSubsys[ForEach_itr].RateTransition10_WrBufIdx =
          static_cast<int8_T>(wturbines_DW.CoreSubsys[ForEach_itr].
                              RateTransition10_WrBufIdx == 0);
      }

      wturbines_DW.CoreSubsys[ForEach_itr]
        .RateTransition10_Buf[wturbines_DW.CoreSubsys[ForEach_itr].
        RateTransition10_WrBufIdx] = wturbines_B.CoreSubsys[ForEach_itr].GenSpd;

      /* RateTransition: '<S12>/Rate Transition11' */
      if (limitedCache) {
        wturbines_DW.CoreSubsys[ForEach_itr].RateTransition11_WrBufIdx =
          static_cast<int8_T>(wturbines_DW.CoreSubsys[ForEach_itr].
                              RateTransition11_WrBufIdx == 0);
      }

      wturbines_DW.CoreSubsys[ForEach_itr]
        .RateTransition11_Buf[wturbines_DW.CoreSubsys[ForEach_itr].
        RateTransition11_WrBufIdx] = wturbines_B.CoreSubsys[ForEach_itr].Gain_n;

      /* RateTransition: '<S12>/Rate Transition12' */
      if (limitedCache) {
        wturbines_DW.CoreSubsys[ForEach_itr].RateTransition12_WrBufIdx =
          static_cast<int8_T>(wturbines_DW.CoreSubsys[ForEach_itr].
                              RateTransition12_WrBufIdx == 0);
      }

      wturbines_DW.CoreSubsys[ForEach_itr]
        .RateTransition12_Buf[wturbines_DW.CoreSubsys[ForEach_itr].
        RateTransition12_WrBufIdx] = wturbines_B.CoreSubsys[ForEach_itr].WsEff;
    }

    /* RelationalOperator: '<S285>/Compare' incorporates:
     *  Constant: '<S285>/Constant'
     */
    wturbines_B.CoreSubsys[ForEach_itr].Compare_p =
      (wturbines_B.CoreSubsys[ForEach_itr].Gain_n <
       wturbines_cal->wturbines_CoreSubsys_cal.CompareToConstant2_const);

    /* RelationalOperator: '<S286>/Compare' incorporates:
     *  Constant: '<S286>/Constant'
     */
    wturbines_B.CoreSubsys[ForEach_itr].Compare_a =
      (wturbines_B.CoreSubsys[ForEach_itr].Gain_n >
       wturbines_cal->wturbines_CoreSubsys_cal.CompareToConstant3_const);

    /* Logic: '<S277>/OR1' */
    wturbines_B.CoreSubsys[ForEach_itr].OR1_g =
      (wturbines_B.CoreSubsys[ForEach_itr].Compare_p ||
       wturbines_B.CoreSubsys[ForEach_itr].Compare_a);

    /* Switch: '<S277>/Switch' */
    if (wturbines_B.CoreSubsys[ForEach_itr].OR1_g) {
      /* Switch: '<S277>/Switch' incorporates:
       *  Constant: '<S277>/Constant'
       */
      wturbines_B.CoreSubsys[ForEach_itr].Switch_f =
        wturbines_cal->wturbines_CoreSubsys_cal.Constant_Value_h;
    } else {
      /* Lookup_n-D: '<S277>/Cp(&#x3BB;, &#x3B2;) ' incorporates:
       *  Gain: '<S283>/Gain'
       *  Product: '<S282>/Divide'
       */
      wturbines_B.CoreSubsys[ForEach_itr].Cpt = look2_binlcpw
        (wturbines_B.CoreSubsys[ForEach_itr].t_c,
         wturbines_B.CoreSubsys[ForEach_itr].Gain_n, tmp_l, tmp_m, get_Cp_mat(),
         wturbines_cal->wturbines_CoreSubsys_cal.Cp_maxIndex, 20U);

      /* Switch: '<S277>/Switch' */
      wturbines_B.CoreSubsys[ForEach_itr].Switch_f =
        wturbines_B.CoreSubsys[ForEach_itr].Cpt;
    }

    /* Saturate: '<S277>/Saturation' */
    u0 = wturbines_B.CoreSubsys[ForEach_itr].Switch_f;
    y_Cp = wturbines_cal->wturbines_CoreSubsys_cal.Saturation_LowerSat_j;
    u2 = wturbines_cal->wturbines_CoreSubsys_cal.Saturation_UpperSat_g;
    if (u0 > u2) {
      /* Saturate: '<S277>/Saturation' */
      wturbines_B.CoreSubsys[ForEach_itr].Saturation_g = u2;
    } else if (u0 < y_Cp) {
      /* Saturate: '<S277>/Saturation' */
      wturbines_B.CoreSubsys[ForEach_itr].Saturation_g = y_Cp;
    } else {
      /* Saturate: '<S277>/Saturation' */
      wturbines_B.CoreSubsys[ForEach_itr].Saturation_g = u0;
    }

    /* End of Saturate: '<S277>/Saturation' */

    /* Gain: '<S14>/Friction' */
    wturbines_B.CoreSubsys[ForEach_itr].Friction =
      wturbines_cal->wturbines_CoreSubsys_cal.Friction_Gain *
      wturbines_B.CoreSubsys[ForEach_itr].RotSpd;

    /* Gain: '<S14>/Gain' */
    wturbines_B.CoreSubsys[ForEach_itr].Gain_m = tmp_b *
      wturbines_B.CoreSubsys[ForEach_itr].Tgen;

    /* MinMax: '<S280>/Max' incorporates:
     *  Constant: '<S280>/Constant'
     */
    u0 = wturbines_B.CoreSubsys[ForEach_itr].RotSpd;
    y_Cp = wturbines_cal->wturbines_CoreSubsys_cal.Constant_Value_j;
    if ((u0 >= y_Cp) || rtIsNaN(y_Cp)) {
      y_Cp = u0;
    }

    /* MinMax: '<S280>/Max' */
    wturbines_B.CoreSubsys[ForEach_itr].Max = y_Cp;

    /* Math: '<S280>/  '
     *
     * About '<S280>/  ':
     *  Operator: reciprocal
     */
    u0 = wturbines_B.CoreSubsys[ForEach_itr].Max;

    /* Math: '<S280>/  '
     *
     * About '<S280>/  ':
     *  Operator: reciprocal
     */
    wturbines_B.CoreSubsys[ForEach_itr].ut = 1.0 / u0;
    if (tmp) {
      /* Math: '<S280>/Square' incorporates:
       *  Constant: '<S280>/Constant7'
       */
      wturbines_B.CoreSubsys[ForEach_itr].Square_o = tmp_5 * tmp_5;

      /* Math: '<S280>/Power' incorporates:
       *  Constant: '<S280>/Constant8'
       */
      wturbines_B.CoreSubsys[ForEach_itr].Power = rt_powd_snf
        (wturbines_B.CoreSubsys[ForEach_itr].WsEff,
         wturbines_cal->wturbines_CoreSubsys_cal.Constant8_Value);
    }

    /* Product: '<S280>/Product' incorporates:
     *  Constant: '<S280>/Constant4'
     *  Constant: '<S280>/Constant5'
     *  Constant: '<S280>/Constant6'
     */
    wturbines_B.CoreSubsys[ForEach_itr].T_at =
      wturbines_B.CoreSubsys[ForEach_itr].ut *
      wturbines_cal->wturbines_CoreSubsys_cal.Constant4_Value_d * tmp_7 *
      wturbines_B.CoreSubsys[ForEach_itr].Saturation_g *
      wturbines_B.CoreSubsys[ForEach_itr].Square_o *
      wturbines_cal->wturbines_CoreSubsys_cal.Constant6_Value_l *
      wturbines_B.CoreSubsys[ForEach_itr].Power;

    /* Saturate: '<S280>/Saturation' */
    u0 = wturbines_B.CoreSubsys[ForEach_itr].T_at;
    y_Cp = wturbines_cal->wturbines_CoreSubsys_cal.Saturation_LowerSat_k;
    u2 = *get_rated_torque();
    if (u0 > u2) {
      /* Saturate: '<S280>/Saturation' */
      wturbines_B.CoreSubsys[ForEach_itr].Saturation_f = u2;
    } else if (u0 < y_Cp) {
      /* Saturate: '<S280>/Saturation' */
      wturbines_B.CoreSubsys[ForEach_itr].Saturation_f = y_Cp;
    } else {
      /* Saturate: '<S280>/Saturation' */
      wturbines_B.CoreSubsys[ForEach_itr].Saturation_f = u0;
    }

    /* End of Saturate: '<S280>/Saturation' */

    /* Sum: '<S14>/Sum' */
    wturbines_B.CoreSubsys[ForEach_itr].Sum_g =
      (wturbines_B.CoreSubsys[ForEach_itr].Saturation_f -
       wturbines_B.CoreSubsys[ForEach_itr].Gain_m) -
      wturbines_B.CoreSubsys[ForEach_itr].Tbrake;

    /* Gain: '<S14>/Multiply1' */
    u0 = 1.0 / *get_inertia();

    /* Gain: '<S14>/Multiply1' */
    wturbines_B.CoreSubsys[ForEach_itr]._dott = u0 *
      wturbines_B.CoreSubsys[ForEach_itr].Sum_g;

    /* Sum: '<S14>/Sum1' */
    wturbines_B.CoreSubsys[ForEach_itr].Sum1 =
      wturbines_B.CoreSubsys[ForEach_itr]._dott -
      wturbines_B.CoreSubsys[ForEach_itr].Friction;

    /* BusCreator: '<S7>/Bus Creator' */
    wturbines_B.CoreSubsys[ForEach_itr].BusCreator.Cp =
      wturbines_B.CoreSubsys[ForEach_itr].Saturation_g;
    wturbines_B.CoreSubsys[ForEach_itr].BusCreator.Ct =
      wturbines_B.CoreSubsys[ForEach_itr].Ct_n;
    wturbines_B.CoreSubsys[ForEach_itr].BusCreator.GenSpd =
      wturbines_B.CoreSubsys[ForEach_itr].GenSpd;
    wturbines_B.CoreSubsys[ForEach_itr].BusCreator.OpMode =
      wturbines_B.CoreSubsys[ForEach_itr].op_mode_m;
    wturbines_B.CoreSubsys[ForEach_itr].BusCreator.OrientationSpt =
      wturbines_B.CoreSubsys[ForEach_itr].y;
    wturbines_B.CoreSubsys[ForEach_itr].BusCreator.Pitch =
      wturbines_B.CoreSubsys[ForEach_itr].Gain_n;
    wturbines_B.CoreSubsys[ForEach_itr].BusCreator.PitchSpt =
      wturbines_B.CoreSubsys[ForEach_itr].PitchSpt;
    wturbines_B.CoreSubsys[ForEach_itr].BusCreator.RotSpd =
      wturbines_B.CoreSubsys[ForEach_itr].RotSpd;
    wturbines_B.CoreSubsys[ForEach_itr].BusCreator.eCtrlMode =
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition4_e;
    wturbines_B.CoreSubsys[ForEach_itr].BusCreator.TBrake =
      wturbines_B.CoreSubsys[ForEach_itr].Tbrake;
    wturbines_B.CoreSubsys[ForEach_itr].BusCreator.TGen =
      wturbines_B.CoreSubsys[ForEach_itr].Tgen;
    wturbines_B.CoreSubsys[ForEach_itr].BusCreator.Ta =
      wturbines_B.CoreSubsys[ForEach_itr].Saturation_f;
    wturbines_B.CoreSubsys[ForEach_itr].BusCreator.WsEff =
      wturbines_B.CoreSubsys[ForEach_itr].WsEff;
    wturbines_B.CoreSubsys[ForEach_itr].BusCreator.YawTrue =
      wturbines_B.CoreSubsys[ForEach_itr].yaw;
    wturbines_B.CoreSubsys[ForEach_itr].BusCreator.HorWdSpd =
      wturbines_B.CoreSubsys[ForEach_itr].RateLimiter;
    wturbines_B.CoreSubsys[ForEach_itr].BusCreator.HorWdDir =
      wturbines_B.CoreSubsys[ForEach_itr].RateLimiter1;
    wturbines_B.CoreSubsys[ForEach_itr].BusCreator.bEnable =
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition2_b;
    wturbines_B.CoreSubsys[ForEach_itr].BusCreator.bStop =
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition3_j;
    wturbines_B.CoreSubsys[ForEach_itr].BusCreator.WSpt =
      wturbines_B.CoreSubsys[ForEach_itr].Pref;

    /* ForEachSliceAssignment generated from: '<S2>/log' */
    wturbines_B.ImpAsg_InsertedFor_log_at_inpor[ForEach_itr] =
      wturbines_B.CoreSubsys[ForEach_itr].BusCreator;
    if (rtmIsMajorTimeStep(wturbines_M)) {
      /* ForEachSliceAssignment generated from: '<S2>/ctrlState' */
      wturbines_B.ImpAsg_InsertedFor_ctrlState_at[ForEach_itr] =
        wturbines_B.CoreSubsys[ForEach_itr].op_mode_m;

      /* ForEachSliceAssignment generated from: '<S2>/YawTrue' */
      wturbines_B.ImpAsg_InsertedFor_YawTrue_at_i[ForEach_itr] =
        wturbines_B.CoreSubsys[ForEach_itr].RateTransition9;

      /* ForEachSliceAssignment generated from: '<S2>/Ct' */
      wturbines_B.ImpAsg_InsertedFor_Ct_at_inport[ForEach_itr] =
        wturbines_B.CoreSubsys[ForEach_itr].RateTransition8;
    }

    ForEach_itr++;
  }

  /* End of Outputs for SubSystem: '<Root>/For Each Subsystem' */

  /* RateTransition: '<S1>/Rate Transition' */
  if (tmp_0) {
    if (wturbines_M->Timing.RateInteraction.TID1_4 == 1) {
      wturbines_DW.RateTransition_WrBufIdx_j = static_cast<int8_T>
        (wturbines_DW.RateTransition_WrBufIdx_j == 0);
    }

    for (i = 0; i < 9; i++) {
      wturbines_DW.RateTransition_Buf[i + wturbines_DW.RateTransition_WrBufIdx_j
        * 18] = wturbines_B.ImpAsg_InsertedFor_Ct_at_inport[i];
    }

    for (i = 0; i < 9; i++) {
      wturbines_DW.RateTransition_Buf[(i +
        wturbines_DW.RateTransition_WrBufIdx_j * 18) + 9] =
        wturbines_B.ImpAsg_InsertedFor_YawTrue_at_i[i];
    }
  }

  /* MATLAB Function: '<Root>/MATLAB Function' */
  wturbines_DW.sfEvent_j = wturbines_CALL_EVENT;
  for (i = 0; i < 9; i++) {
    y_Cp = wturbines_B.ImpAsg_InsertedFor_log_at_inpor[i].Cp;
    wturbines_B.y.Cp[i] = y_Cp;
    wturbines_B.y.Ct[i] = wturbines_B.ImpAsg_InsertedFor_log_at_inpor[i].Ct;
    wturbines_B.y.GenSpd[i] = wturbines_B.ImpAsg_InsertedFor_log_at_inpor[i].
      GenSpd;
    wturbines_B.y.OpMode[i] = wturbines_B.ImpAsg_InsertedFor_log_at_inpor[i].
      OpMode;
    wturbines_B.y.OrientationSpt[i] =
      wturbines_B.ImpAsg_InsertedFor_log_at_inpor[i].OrientationSpt;
    wturbines_B.y.Pitch[i] = wturbines_B.ImpAsg_InsertedFor_log_at_inpor[i].
      Pitch;
    wturbines_B.y.PitchSpt[i] = wturbines_B.ImpAsg_InsertedFor_log_at_inpor[i].
      PitchSpt;
    wturbines_B.y.RotSpd[i] = wturbines_B.ImpAsg_InsertedFor_log_at_inpor[i].
      RotSpd;
    wturbines_B.y.eCtrlMode[i] = wturbines_B.ImpAsg_InsertedFor_log_at_inpor[i].
      eCtrlMode;
    wturbines_B.y.TBrake[i] = wturbines_B.ImpAsg_InsertedFor_log_at_inpor[i].
      TBrake;
    wturbines_B.y.TGen[i] = wturbines_B.ImpAsg_InsertedFor_log_at_inpor[i].TGen;
    wturbines_B.y.Ta[i] = wturbines_B.ImpAsg_InsertedFor_log_at_inpor[i].Ta;
    wturbines_B.y.WsEff[i] = wturbines_B.ImpAsg_InsertedFor_log_at_inpor[i].
      WsEff;
    wturbines_B.y.YawTrue[i] = wturbines_B.ImpAsg_InsertedFor_log_at_inpor[i].
      YawTrue;
    wturbines_B.y.HorWdSpd[i] = wturbines_B.ImpAsg_InsertedFor_log_at_inpor[i].
      HorWdSpd;
    wturbines_B.y.HorWdDir[i] = wturbines_B.ImpAsg_InsertedFor_log_at_inpor[i].
      HorWdDir;
    wturbines_B.y.bEnable[i] = wturbines_B.ImpAsg_InsertedFor_log_at_inpor[i].
      bEnable;
    wturbines_B.y.bStop[i] = wturbines_B.ImpAsg_InsertedFor_log_at_inpor[i].
      bStop;
    wturbines_B.y.WSpt[i] = wturbines_B.ImpAsg_InsertedFor_log_at_inpor[i].WSpt;

    /* SignalConversion generated from: '<Root>/Bus Selector' */
    wturbines_B.Cp[i] = y_Cp;
  }

  /* End of MATLAB Function: '<Root>/MATLAB Function' */
  if (tmp_0) {
  }

  /* SignalConversion generated from: '<Root>/Bus Selector' */
  std::memcpy(&wturbines_B.Ct[0], &wturbines_B.y.Ct[0], 9U * sizeof(real_T));
  if (tmp_0) {
  }

  /* SignalConversion generated from: '<Root>/Bus Selector' */
  std::memcpy(&wturbines_B.TGen[0], &wturbines_B.y.TGen[0], 9U * sizeof(real_T));
  if (tmp_0) {
  }

  /* SignalConversion generated from: '<Root>/Bus Selector' */
  std::memcpy(&wturbines_B.Ta[0], &wturbines_B.y.Ta[0], 9U * sizeof(real_T));
  if (tmp_0) {
  }

  /* SignalConversion generated from: '<Root>/Bus Selector' */
  std::memcpy(&wturbines_B.WsEff[0], &wturbines_B.y.WsEff[0], 9U * sizeof(real_T));
  if (tmp_0) {
  }

  /* SignalConversion generated from: '<Root>/Bus Selector' */
  std::memcpy(&wturbines_B.YawTrue[0], &wturbines_B.y.YawTrue[0], 9U * sizeof
              (real_T));
  if (tmp_0) {
  }

  /* SignalConversion generated from: '<Root>/Bus Selector' */
  std::memcpy(&wturbines_B.HorWdSpd[0], &wturbines_B.y.HorWdSpd[0], 9U * sizeof
              (real_T));
  if (tmp_0) {
  }

  /* SignalConversion generated from: '<Root>/Bus Selector' */
  std::memcpy(&wturbines_B.HorWdDir[0], &wturbines_B.y.HorWdDir[0], 9U * sizeof
              (real_T));
  if (tmp_0) {
  }

  for (i = 0; i < 9; i++) {
    /* SignalConversion generated from: '<Root>/Bus Selector' */
    wturbines_B.bEnable[i] = wturbines_B.y.bEnable[i];
  }

  if (tmp_0) {
  }

  for (i = 0; i < 9; i++) {
    /* SignalConversion generated from: '<Root>/Bus Selector' */
    wturbines_B.bStop[i] = wturbines_B.y.bStop[i];
  }

  if (tmp_0) {
  }

  /* SignalConversion generated from: '<Root>/Bus Selector' */
  std::memcpy(&wturbines_B.WSpt[0], &wturbines_B.y.WSpt[0], 9U * sizeof(real_T));
  if (tmp_0) {
  }

  /* SignalConversion generated from: '<Root>/Bus Selector' */
  std::memcpy(&wturbines_B.GenSpd[0], &wturbines_B.y.GenSpd[0], 9U * sizeof
              (real_T));
  if (tmp_0) {
  }

  for (i = 0; i < 9; i++) {
    /* SignalConversion generated from: '<Root>/Bus Selector' */
    wturbines_B.OpMode[i] = wturbines_B.y.OpMode[i];
  }

  if (tmp_0) {
  }

  /* SignalConversion generated from: '<Root>/Bus Selector' */
  std::memcpy(&wturbines_B.OrientationSpt[0], &wturbines_B.y.OrientationSpt[0],
              9U * sizeof(real_T));
  if (tmp_0) {
  }

  /* SignalConversion generated from: '<Root>/Bus Selector' */
  std::memcpy(&wturbines_B.Pitch[0], &wturbines_B.y.Pitch[0], 9U * sizeof(real_T));
  if (tmp_0) {
  }

  /* SignalConversion generated from: '<Root>/Bus Selector' */
  std::memcpy(&wturbines_B.PitchSpt[0], &wturbines_B.y.PitchSpt[0], 9U * sizeof
              (real_T));
  if (tmp_0) {
  }

  /* SignalConversion generated from: '<Root>/Bus Selector' */
  std::memcpy(&wturbines_B.RotSpd[0], &wturbines_B.y.RotSpd[0], 9U * sizeof
              (real_T));
  if (tmp_0) {
  }

  for (i = 0; i < 9; i++) {
    /* SignalConversion generated from: '<Root>/Bus Selector' */
    wturbines_B.eCtrlMode[i] = wturbines_B.y.eCtrlMode[i];
  }

  if (tmp_0) {
  }

  /* SignalConversion generated from: '<Root>/Bus Selector' */
  std::memcpy(&wturbines_B.TBrake[0], &wturbines_B.y.TBrake[0], 9U * sizeof
              (real_T));
  if (tmp_0) {
  }

  if (rtmIsMajorTimeStep(wturbines_M)) {
    /* Update for Iterator SubSystem: '<Root>/For Each Subsystem' */
    for (ForEach_itr = 0; ForEach_itr < 9; ForEach_itr++) {
      if (rtmIsMajorTimeStep(wturbines_M)) {
        /* Update for Delay: '<S27>/Delay' */
        wturbines_DW.CoreSubsys[ForEach_itr].Delay_DSTATE =
          wturbines_B.CoreSubsys[ForEach_itr].Sum;
      }

      /* Update for RateLimiter: '<S276>/Rate Limiter' */
      wturbines_DW.CoreSubsys[ForEach_itr].PrevY_d =
        wturbines_B.CoreSubsys[ForEach_itr].RateLimiter_n;
      wturbines_DW.CoreSubsys[ForEach_itr].LastMajorTime = wturbines_M->
        Timing.t[0];
    }

    /* End of Update for SubSystem: '<Root>/For Each Subsystem' */
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(wturbines_M)) {
    rt_ertODEUpdateContinuousStates(&wturbines_M->solverInfo);

    /* Update absolute time */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++wturbines_M->Timing.clockTick0)) {
      ++wturbines_M->Timing.clockTickH0;
    }

    wturbines_M->Timing.t[0] = rtsiGetSolverStopTime(&wturbines_M->solverInfo);

    /* Update absolute time */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.01, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    wturbines_M->Timing.clockTick1++;
    if (!wturbines_M->Timing.clockTick1) {
      wturbines_M->Timing.clockTickH1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void wturbines_derivatives(void)
{
  /* local scratch DWork variables */
  int32_T ForEach_itr;
  XDot_wturbines_T *_rtXdot;
  _rtXdot = ((XDot_wturbines_T *) wturbines_M->derivs);

  /* Derivatives for Iterator SubSystem: '<Root>/For Each Subsystem' */
  for (ForEach_itr = 0; ForEach_itr < 9; ForEach_itr++) {
    /* Derivatives for Integrator: '<S14>/Integrator' */
    _rtXdot->CoreSubsys[ForEach_itr].Integrator_CSTATE =
      wturbines_B.CoreSubsys[ForEach_itr].Sum1;

    /* Derivatives for Integrator: '<S247>/Integrator' */
    _rtXdot->CoreSubsys[ForEach_itr].Integrator_CSTATE_o =
      wturbines_B.CoreSubsys[ForEach_itr].IntegralGain_a;

    /* Derivatives for Integrator: '<S194>/Integrator' */
    _rtXdot->CoreSubsys[ForEach_itr].Integrator_CSTATE_l =
      wturbines_B.CoreSubsys[ForEach_itr].IntegralGain_g;

    /* Derivatives for Integrator: '<S132>/Integrator' */
    _rtXdot->CoreSubsys[ForEach_itr].Integrator_CSTATE_e =
      wturbines_B.CoreSubsys[ForEach_itr].IntegralGain;

    /* Derivatives for Integrator: '<S78>/Integrator' */
    _rtXdot->CoreSubsys[ForEach_itr].Integrator_CSTATE_oj =
      wturbines_B.CoreSubsys[ForEach_itr].IProdOut;

    /* Derivatives for StateSpace: '<S34>/H&#x221E; controller ' */
    _rtXdot->CoreSubsys[ForEach_itr].Hcontroller_CSTATE = *get_A_k() *
      wturbines_X.CoreSubsys[ForEach_itr].Hcontroller_CSTATE;
    _rtXdot->CoreSubsys[ForEach_itr].Hcontroller_CSTATE += *get_B_k() * 0.0;
  }

  /* End of Derivatives for SubSystem: '<Root>/For Each Subsystem' */
}

/* Model step function for TID2 */
void wturbines_step2(void)             /* Sample time: [0.1s, 0.0s] */
{
  /* local scratch DWork variables */
  int32_T ForEach_itr;
  real_T tmp;
  real_T x;
  int32_T i;
  int32_T k;
  real32_T ByteUnpack_o1;
  boolean_T nan_idx[9];
  boolean_T exitg1;
  boolean_T y;

  /* Outputs for Enabled SubSystem: '<S4>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S288>/Enable'
   */
  /* MATLAB Function: '<S288>/ZoH nan filter1' */
  tmp = *get_Nt();

  /* End of Outputs for SubSystem: '<S4>/Enabled Subsystem' */
  /* Reset subsysRan breadcrumbs */
  srClearBC(wturbines_DW.EnabledSubsystem_SubsysRanBC_i);

  /* Reset subsysRan breadcrumbs */
  srClearBC(wturbines_DW.EnabledSubsystem_SubsysRanBC);

  /* Outputs for Iterator SubSystem: '<Root>/For Each Subsystem' incorporates:
   *  ForEach: '<S2>/For Each'
   */
  for (ForEach_itr = 0; ForEach_itr < 9; ForEach_itr++) {
    /* Outputs for Iterator SubSystem: '<Root>/For Each Subsystem' incorporates:
     *  ForEach: '<S2>/For Each'
     */
    wturbines_B.ForEach = ForEach_itr;

    /* RandomNumber: '<S267>/White Noise' */
    wturbines_B.CoreSubsys[ForEach_itr].WhiteNoise =
      wturbines_DW.CoreSubsys[ForEach_itr].NextOutput;

    /* Gain: '<S267>/Output' */
    x = wturbines_cal->wturbines_CoreSubsys_cal.BandLimitedWhiteNoise_Cov;
    x = std::sqrt(x);
    x /= 0.31622776601683794;

    /* Gain: '<S267>/Output' */
    wturbines_B.CoreSubsys[ForEach_itr].Output = x *
      wturbines_B.CoreSubsys[ForEach_itr].WhiteNoise;

    /* RateTransition: '<S12>/Rate Transition7' */
    wturbines_DW.CoreSubsys[ForEach_itr].RateTransition7_RdBufIdx_g =
      static_cast<int8_T>(wturbines_DW.CoreSubsys[ForEach_itr].
                          RateTransition7_RdBufIdx_g == 0);

    /* RateTransition: '<S12>/Rate Transition7' */
    wturbines_B.CoreSubsys[ForEach_itr].RateTransition7 =
      wturbines_DW.CoreSubsys[ForEach_itr]
      .RateTransition7_Buf_h[wturbines_DW.CoreSubsys[ForEach_itr].
      RateTransition7_RdBufIdx_g];

    /* Sum: '<S12>/Sum1' */
    wturbines_B.CoreSubsys[ForEach_itr].Sum1_j =
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition7 +
      wturbines_B.CoreSubsys[ForEach_itr].Output;

    /* RateTransition: '<S12>/Rate Transition5' */
    wturbines_DW.CoreSubsys[ForEach_itr].RateTransition5_WrBufIdx =
      static_cast<int8_T>(wturbines_DW.CoreSubsys[ForEach_itr].
                          RateTransition5_WrBufIdx == 0);
    wturbines_DW.CoreSubsys[ForEach_itr]
      .RateTransition5_Buf[wturbines_DW.CoreSubsys[ForEach_itr].
      RateTransition5_WrBufIdx] = wturbines_B.CoreSubsys[ForEach_itr].Sum1_j;

    /* RandomNumber: '<S270>/White Noise' */
    wturbines_B.CoreSubsys[ForEach_itr].WhiteNoise_a =
      wturbines_DW.CoreSubsys[ForEach_itr].NextOutput_i;

    /* Gain: '<S270>/Output' */
    x = wturbines_cal->wturbines_CoreSubsys_cal.BandLimitedWhiteNoise3_Cov;
    x = std::sqrt(x);
    x /= 0.31622776601683794;

    /* Gain: '<S270>/Output' */
    wturbines_B.CoreSubsys[ForEach_itr].Output_g = x *
      wturbines_B.CoreSubsys[ForEach_itr].WhiteNoise_a;

    /* RateTransition: '<S12>/Rate Transition9' */
    wturbines_DW.CoreSubsys[ForEach_itr].RateTransition9_RdBufIdx =
      static_cast<int8_T>(wturbines_DW.CoreSubsys[ForEach_itr].
                          RateTransition9_RdBufIdx == 0);

    /* RateTransition: '<S12>/Rate Transition9' */
    wturbines_B.CoreSubsys[ForEach_itr].RateTransition9_o =
      wturbines_DW.CoreSubsys[ForEach_itr]
      .RateTransition9_Buf[wturbines_DW.CoreSubsys[ForEach_itr].
      RateTransition9_RdBufIdx];

    /* Sum: '<S12>/Sum3' */
    wturbines_B.CoreSubsys[ForEach_itr].Sum3 =
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition9_o +
      wturbines_B.CoreSubsys[ForEach_itr].Output_g;

    /* RateTransition: '<S12>/Rate Transition2' */
    wturbines_DW.CoreSubsys[ForEach_itr].RateTransition2_WrBufIdx =
      static_cast<int8_T>(wturbines_DW.CoreSubsys[ForEach_itr].
                          RateTransition2_WrBufIdx == 0);
    wturbines_DW.CoreSubsys[ForEach_itr]
      .RateTransition2_Buf[wturbines_DW.CoreSubsys[ForEach_itr].
      RateTransition2_WrBufIdx] = wturbines_B.CoreSubsys[ForEach_itr].Sum3;

    /* RandomNumber: '<S268>/White Noise' */
    wturbines_B.CoreSubsys[ForEach_itr].WhiteNoise_p =
      wturbines_DW.CoreSubsys[ForEach_itr].NextOutput_a;

    /* Gain: '<S268>/Output' */
    x = wturbines_cal->wturbines_CoreSubsys_cal.BandLimitedWhiteNoise1_Cov;
    x = std::sqrt(x);
    x /= 0.31622776601683794;

    /* Gain: '<S268>/Output' */
    wturbines_B.CoreSubsys[ForEach_itr].Output_p = x *
      wturbines_B.CoreSubsys[ForEach_itr].WhiteNoise_p;

    /* RateTransition: '<S12>/Rate Transition8' */
    wturbines_DW.CoreSubsys[ForEach_itr].RateTransition8_RdBufIdx =
      static_cast<int8_T>(wturbines_DW.CoreSubsys[ForEach_itr].
                          RateTransition8_RdBufIdx == 0);

    /* RateTransition: '<S12>/Rate Transition8' */
    wturbines_B.CoreSubsys[ForEach_itr].RateTransition8_e =
      wturbines_DW.CoreSubsys[ForEach_itr]
      .RateTransition8_Buf[wturbines_DW.CoreSubsys[ForEach_itr].
      RateTransition8_RdBufIdx];

    /* Sum: '<S12>/Sum' */
    wturbines_B.CoreSubsys[ForEach_itr].Sum_i =
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition8_e +
      wturbines_B.CoreSubsys[ForEach_itr].Output_p;

    /* RateTransition: '<S12>/Rate Transition1' */
    wturbines_DW.CoreSubsys[ForEach_itr].RateTransition1_WrBufIdx =
      static_cast<int8_T>(wturbines_DW.CoreSubsys[ForEach_itr].
                          RateTransition1_WrBufIdx == 0);
    wturbines_DW.CoreSubsys[ForEach_itr]
      .RateTransition1_Buf[wturbines_DW.CoreSubsys[ForEach_itr].
      RateTransition1_WrBufIdx] = wturbines_B.CoreSubsys[ForEach_itr].Sum_i;

    /* RandomNumber: '<S271>/White Noise' */
    wturbines_B.CoreSubsys[ForEach_itr].WhiteNoise_e =
      wturbines_DW.CoreSubsys[ForEach_itr].NextOutput_f;

    /* Gain: '<S271>/Output' */
    x = wturbines_cal->wturbines_CoreSubsys_cal.BandLimitedWhiteNoise4_Cov;
    x = std::sqrt(x);
    x /= 0.31622776601683794;

    /* Gain: '<S271>/Output' */
    wturbines_B.CoreSubsys[ForEach_itr].Output_h = x *
      wturbines_B.CoreSubsys[ForEach_itr].WhiteNoise_e;

    /* RateTransition: '<S12>/Rate Transition10' */
    wturbines_DW.CoreSubsys[ForEach_itr].RateTransition10_RdBufIdx =
      static_cast<int8_T>(wturbines_DW.CoreSubsys[ForEach_itr].
                          RateTransition10_RdBufIdx == 0);

    /* RateTransition: '<S12>/Rate Transition10' */
    wturbines_B.CoreSubsys[ForEach_itr].RateTransition10 =
      wturbines_DW.CoreSubsys[ForEach_itr]
      .RateTransition10_Buf[wturbines_DW.CoreSubsys[ForEach_itr].
      RateTransition10_RdBufIdx];

    /* Sum: '<S12>/Sum4' */
    wturbines_B.CoreSubsys[ForEach_itr].Sum4 =
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition10 +
      wturbines_B.CoreSubsys[ForEach_itr].Output_h;

    /* RateTransition: '<S12>/Rate Transition3' */
    wturbines_DW.CoreSubsys[ForEach_itr].RateTransition3_WrBufIdx =
      static_cast<int8_T>(wturbines_DW.CoreSubsys[ForEach_itr].
                          RateTransition3_WrBufIdx == 0);
    wturbines_DW.CoreSubsys[ForEach_itr]
      .RateTransition3_Buf[wturbines_DW.CoreSubsys[ForEach_itr].
      RateTransition3_WrBufIdx] = wturbines_B.CoreSubsys[ForEach_itr].Sum4;

    /* RandomNumber: '<S272>/White Noise' */
    wturbines_B.CoreSubsys[ForEach_itr].WhiteNoise_f =
      wturbines_DW.CoreSubsys[ForEach_itr].NextOutput_m;

    /* Gain: '<S272>/Output' */
    x = wturbines_cal->wturbines_CoreSubsys_cal.BandLimitedWhiteNoise5_Cov;
    x = std::sqrt(x);
    x /= 0.31622776601683794;

    /* Gain: '<S272>/Output' */
    wturbines_B.CoreSubsys[ForEach_itr].Output_m = x *
      wturbines_B.CoreSubsys[ForEach_itr].WhiteNoise_f;

    /* RateTransition: '<S12>/Rate Transition11' */
    wturbines_DW.CoreSubsys[ForEach_itr].RateTransition11_RdBufIdx =
      static_cast<int8_T>(wturbines_DW.CoreSubsys[ForEach_itr].
                          RateTransition11_RdBufIdx == 0);

    /* RateTransition: '<S12>/Rate Transition11' */
    wturbines_B.CoreSubsys[ForEach_itr].RateTransition11 =
      wturbines_DW.CoreSubsys[ForEach_itr]
      .RateTransition11_Buf[wturbines_DW.CoreSubsys[ForEach_itr].
      RateTransition11_RdBufIdx];

    /* Sum: '<S12>/Sum5' */
    wturbines_B.CoreSubsys[ForEach_itr].Sum5 =
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition11 +
      wturbines_B.CoreSubsys[ForEach_itr].Output_m;

    /* RateTransition: '<S12>/Rate Transition4' */
    wturbines_DW.CoreSubsys[ForEach_itr].RateTransition4_WrBufIdx =
      static_cast<int8_T>(wturbines_DW.CoreSubsys[ForEach_itr].
                          RateTransition4_WrBufIdx == 0);
    wturbines_DW.CoreSubsys[ForEach_itr]
      .RateTransition4_Buf[wturbines_DW.CoreSubsys[ForEach_itr].
      RateTransition4_WrBufIdx] = wturbines_B.CoreSubsys[ForEach_itr].Sum5;

    /* RandomNumber: '<S273>/White Noise' */
    wturbines_B.CoreSubsys[ForEach_itr].WhiteNoise_i =
      wturbines_DW.CoreSubsys[ForEach_itr].NextOutput_n;

    /* Gain: '<S273>/Output' */
    x = wturbines_cal->wturbines_CoreSubsys_cal.BandLimitedWhiteNoise6_Cov;
    x = std::sqrt(x);
    x /= 0.31622776601683794;

    /* Gain: '<S273>/Output' */
    wturbines_B.CoreSubsys[ForEach_itr].Output_k = x *
      wturbines_B.CoreSubsys[ForEach_itr].WhiteNoise_i;

    /* RateTransition: '<S12>/Rate Transition12' */
    wturbines_DW.CoreSubsys[ForEach_itr].RateTransition12_RdBufIdx =
      static_cast<int8_T>(wturbines_DW.CoreSubsys[ForEach_itr].
                          RateTransition12_RdBufIdx == 0);

    /* RateTransition: '<S12>/Rate Transition12' */
    wturbines_B.CoreSubsys[ForEach_itr].RateTransition12 =
      wturbines_DW.CoreSubsys[ForEach_itr]
      .RateTransition12_Buf[wturbines_DW.CoreSubsys[ForEach_itr].
      RateTransition12_RdBufIdx];

    /* Sum: '<S12>/Sum6' */
    wturbines_B.CoreSubsys[ForEach_itr].Sum6 =
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition12 +
      wturbines_B.CoreSubsys[ForEach_itr].Output_k;

    /* RateTransition: '<S12>/Rate Transition13' */
    wturbines_DW.CoreSubsys[ForEach_itr].RateTransition13_WrBufIdx =
      static_cast<int8_T>(wturbines_DW.CoreSubsys[ForEach_itr].
                          RateTransition13_WrBufIdx == 0);
    wturbines_DW.CoreSubsys[ForEach_itr]
      .RateTransition13_Buf[wturbines_DW.CoreSubsys[ForEach_itr].
      RateTransition13_WrBufIdx] = wturbines_B.CoreSubsys[ForEach_itr].Sum6;

    /* RandomNumber: '<S269>/White Noise' */
    wturbines_B.CoreSubsys[ForEach_itr].WhiteNoise_g =
      wturbines_DW.CoreSubsys[ForEach_itr].NextOutput_b;

    /* Gain: '<S269>/Output' */
    x = wturbines_cal->wturbines_CoreSubsys_cal.BandLimitedWhiteNoise2_Cov;
    x = std::sqrt(x);
    x /= 0.31622776601683794;

    /* Gain: '<S269>/Output' */
    wturbines_B.CoreSubsys[ForEach_itr].Output_l = x *
      wturbines_B.CoreSubsys[ForEach_itr].WhiteNoise_g;

    /* Sum: '<S12>/Sum2' */
    wturbines_B.CoreSubsys[ForEach_itr].Sum2 =
      wturbines_B.CoreSubsys[ForEach_itr].Output_l;
  }

  /* End of Outputs for SubSystem: '<Root>/For Each Subsystem' */

  /* S-Function (slrealtimeUDPReceive): '<S4>/UDP Receive' */
  {
    try {
      slrealtime::ip::udp::Socket *udpSock = reinterpret_cast<slrealtime::ip::
        udp::Socket*>(wturbines_DW.UDPReceive_PWORK[0]);
      char *buffer = (char *)wturbines_DW.UDPReceive_PWORK[1];
      memset(buffer,0,72);
      void *dataPort = &wturbines_B.UDPReceive_o1[0];
      int_T numBytesAvail = (int_T)(udpSock->bytesToRead());
      if (numBytesAvail > 0) {
        uint8_t* fmAddArg = (uint8_t *)wturbines_cal->UDPReceive_fmAddress;
        size_t num_bytesRcvd = (size_t)(udpSock->receive(buffer,( numBytesAvail<
          65507 )? numBytesAvail:65507, !0,fmAddArg));
        if (num_bytesRcvd == 0) {
          wturbines_B.UDPReceive_o2 = 0;
        } else {
          wturbines_B.UDPReceive_o2 = (double)num_bytesRcvd;
          memcpy(dataPort,(void*)buffer,72);
        }
      } else {
        wturbines_B.UDPReceive_o2 = 0;
      }
    } catch (std::exception& e) {
      std::string tmp = std::string(e.what());
      static std::string eMsg = tmp;
      rtmSetErrorStatus(wturbines_M, eMsg.c_str());
      rtmSetStopRequested(wturbines_M, 1);
      ;
    }
  }

  /* RelationalOperator: '<S287>/Compare' incorporates:
   *  Constant: '<S287>/Constant'
   */
  wturbines_B.Compare = (wturbines_B.UDPReceive_o2 >
    wturbines_cal->CompareToConstant_const);

  /* Outputs for Enabled SubSystem: '<S4>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S288>/Enable'
   */
  if (wturbines_B.Compare) {
    /* S-Function (byte2any): '<S288>/Byte Unpack' */

    /* Unpack: <S288>/Byte Unpack */
    (void) std::memcpy(&wturbines_B.ByteUnpack_o1[0],
                       &wturbines_B.UDPReceive_o1[0],
                       36);
    (void) std::memcpy(&wturbines_B.ByteUnpack_o2[0],
                       &wturbines_B.UDPReceive_o1[36],
                       36);

    /* MATLAB Function: '<S288>/ZoH nan filter1' */
    wturbines_DW.sfEvent_n = wturbines_CALL_EVENT;
    for (i = 0; i < 9; i++) {
      /* UnitDelay: '<S288>/Unit Delay' */
      wturbines_B.UnitDelay[i] = wturbines_DW.UnitDelay_DSTATE[i];

      /* UnitDelay: '<S288>/Unit Delay1' */
      wturbines_B.UnitDelay1[i] = wturbines_DW.UnitDelay1_DSTATE[i];

      /* MATLAB Function: '<S288>/ZoH nan filter1' */
      ByteUnpack_o1 = wturbines_B.ByteUnpack_o1[i];
      wturbines_B.w_filtered_k[i] = ByteUnpack_o1;
      nan_idx[i] = (ByteUnpack_o1 == 0.0F);
    }

    /* MATLAB Function: '<S288>/ZoH nan filter1' */
    y = true;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k < 9)) {
      if (!nan_idx[k]) {
        y = false;
        exitg1 = true;
      } else {
        k++;
      }
    }

    if (y) {
      k = static_cast<int32_T>(tmp);
      for (i = 0; i < k; i++) {
        wturbines_B.w_filtered_k[i] = 10.0F;
      }
    }

    /* MATLAB Function: '<S288>/ZoH nan filter2' */
    wturbines_DW.sfEvent = wturbines_CALL_EVENT;
    for (i = 0; i < 9; i++) {
      /* MATLAB Function: '<S288>/ZoH nan filter1' */
      y = rtIsNaNF(wturbines_B.w_filtered_k[i]);
      if (y) {
        wturbines_B.w_filtered_k[i] = wturbines_B.UnitDelay[i];
      }

      /* MATLAB Function: '<S288>/ZoH nan filter2' */
      ByteUnpack_o1 = wturbines_B.ByteUnpack_o2[i];
      wturbines_B.w_filtered[i] = ByteUnpack_o1;
      y = (ByteUnpack_o1 == 0.0F);
      nan_idx[i] = y;
    }

    /* MATLAB Function: '<S288>/ZoH nan filter2' */
    y = true;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k < 9)) {
      if (!nan_idx[k]) {
        y = false;
        exitg1 = true;
      } else {
        k++;
      }
    }

    if (y) {
      k = static_cast<int32_T>(tmp);
      if (k - 1 >= 0) {
        std::memset(&wturbines_B.w_filtered[0], 0, static_cast<uint32_T>(k) *
                    sizeof(real32_T));
      }
    }

    for (i = 0; i < 9; i++) {
      y = rtIsNaNF(wturbines_B.w_filtered[i]);
      if (y) {
        wturbines_B.w_filtered[i] = wturbines_B.UnitDelay1[i];
      }

      /* Update for UnitDelay: '<S288>/Unit Delay' */
      wturbines_DW.UnitDelay_DSTATE[i] = wturbines_B.w_filtered_k[i];

      /* Update for UnitDelay: '<S288>/Unit Delay1' */
      wturbines_DW.UnitDelay1_DSTATE[i] = wturbines_B.w_filtered[i];
    }

    if (rtsiIsModeUpdateTimeStep(&wturbines_M->solverInfo)) {
      srUpdateBC(wturbines_DW.EnabledSubsystem_SubsysRanBC_i);
    }
  }

  /* End of Outputs for SubSystem: '<S4>/Enabled Subsystem' */

  /* RateTransition: '<S4>/Rate Transition1' */
  wturbines_DW.RateTransition1_WrBufIdx_g = static_cast<int8_T>
    (wturbines_DW.RateTransition1_WrBufIdx_g == 0);
  for (i = 0; i < 9; i++) {
    wturbines_DW.RateTransition1_Buf_f[i +
      wturbines_DW.RateTransition1_WrBufIdx_g * 9] = wturbines_B.w_filtered_k[i];
  }

  /* End of RateTransition: '<S4>/Rate Transition1' */

  /* RateTransition: '<S4>/Rate Transition2' */
  wturbines_DW.RateTransition2_WrBufIdx_g = static_cast<int8_T>
    (wturbines_DW.RateTransition2_WrBufIdx_g == 0);
  for (i = 0; i < 9; i++) {
    wturbines_DW.RateTransition2_Buf_k[i +
      wturbines_DW.RateTransition2_WrBufIdx_g * 9] = wturbines_B.w_filtered[i];
  }

  /* End of RateTransition: '<S4>/Rate Transition2' */

  /* S-Function (slrealtimeUDPReceive): '<S5>/UDP Receive' */
  {
    try {
      slrealtime::ip::udp::Socket *udpSock = reinterpret_cast<slrealtime::ip::
        udp::Socket*>(wturbines_DW.UDPReceive_PWORK_k[0]);
      char *buffer = (char *)wturbines_DW.UDPReceive_PWORK_k[1];
      memset(buffer,0,99);
      void *dataPort = &wturbines_B.UDPReceive_o1_d[0];
      int_T numBytesAvail = (int_T)(udpSock->bytesToRead());
      if (numBytesAvail > 0) {
        uint8_t* fmAddArg = (uint8_t *)wturbines_cal->UDPReceive_fmAddress_f;
        size_t num_bytesRcvd = (size_t)(udpSock->receive(buffer,( numBytesAvail<
          65507 )? numBytesAvail:65507, !0,fmAddArg));
        if (num_bytesRcvd == 0) {
          wturbines_B.UDPReceive_o2_m = 0;
        } else {
          wturbines_B.UDPReceive_o2_m = (double)num_bytesRcvd;
          memcpy(dataPort,(void*)buffer,99);
        }
      } else {
        wturbines_B.UDPReceive_o2_m = 0;
      }
    } catch (std::exception& e) {
      std::string tmp = std::string(e.what());
      static std::string eMsg = tmp;
      rtmSetErrorStatus(wturbines_M, eMsg.c_str());
      rtmSetStopRequested(wturbines_M, 1);
      ;
    }
  }

  /* RelationalOperator: '<S291>/Compare' incorporates:
   *  Constant: '<S291>/Constant'
   */
  wturbines_B.Compare_h = (wturbines_B.UDPReceive_o2_m >
    wturbines_cal->CompareToConstant_const_m);

  /* Outputs for Enabled SubSystem: '<S5>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S292>/Enable'
   */
  if (wturbines_B.Compare_h) {
    /* S-Function (byte2any): '<S292>/Byte Unpack' */

    /* Unpack: <S292>/Byte Unpack */
    (void) std::memcpy(&wturbines_B.ByteUnpack_o1_f[0],
                       &wturbines_B.UDPReceive_o1_d[0],
                       9);
    (void) std::memcpy(&wturbines_B.ByteUnpack_o2_k[0],
                       &wturbines_B.UDPReceive_o1_d[9],
                       9);
    (void) std::memcpy(&wturbines_B.ByteUnpack_o3[0],
                       &wturbines_B.UDPReceive_o1_d[18],
                       9);
    (void) std::memcpy(&wturbines_B.ByteUnpack_o4[0],
                       &wturbines_B.UDPReceive_o1_d[27],
                       36);
    (void) std::memcpy(&wturbines_B.ByteUnpack_o5[0],
                       &wturbines_B.UDPReceive_o1_d[63],
                       36);
    for (i = 0; i < 9; i++) {
      /* ZeroOrderHold: '<S292>/Zero-Order Hold' */
      wturbines_B.ZeroOrderHold[i] = wturbines_B.ByteUnpack_o1_f[i];

      /* ZeroOrderHold: '<S292>/Zero-Order Hold1' */
      wturbines_B.ZeroOrderHold1[i] = wturbines_B.ByteUnpack_o2_k[i];

      /* ZeroOrderHold: '<S292>/Zero-Order Hold2' */
      wturbines_B.ZeroOrderHold2[i] = wturbines_B.ByteUnpack_o3[i];

      /* ZeroOrderHold: '<S292>/Zero-Order Hold3' */
      wturbines_B.ZeroOrderHold3[i] = wturbines_B.ByteUnpack_o4[i];

      /* ZeroOrderHold: '<S292>/Zero-Order Hold4' */
      wturbines_B.ZeroOrderHold4[i] = wturbines_B.ByteUnpack_o5[i];
    }

    if (rtsiIsModeUpdateTimeStep(&wturbines_M->solverInfo)) {
      srUpdateBC(wturbines_DW.EnabledSubsystem_SubsysRanBC);
    }
  }

  /* End of Outputs for SubSystem: '<S5>/Enabled Subsystem' */

  /* RateTransition: '<S5>/Rate Transition' */
  wturbines_DW.RateTransition_WrBufIdx = static_cast<int8_T>
    (wturbines_DW.RateTransition_WrBufIdx == 0);
  for (i = 0; i < 9; i++) {
    wturbines_DW.RateTransition_Buf_n[i + wturbines_DW.RateTransition_WrBufIdx *
      9] = wturbines_B.ZeroOrderHold[i];
  }

  /* End of RateTransition: '<S5>/Rate Transition' */

  /* RateTransition: '<S5>/Rate Transition1' */
  wturbines_DW.RateTransition1_WrBufIdx = static_cast<int8_T>
    (wturbines_DW.RateTransition1_WrBufIdx == 0);
  for (i = 0; i < 9; i++) {
    wturbines_DW.RateTransition1_Buf[i + wturbines_DW.RateTransition1_WrBufIdx *
      9] = wturbines_B.ZeroOrderHold3[i];
  }

  /* End of RateTransition: '<S5>/Rate Transition1' */

  /* RateTransition: '<S5>/Rate Transition2' */
  wturbines_DW.RateTransition2_WrBufIdx = static_cast<int8_T>
    (wturbines_DW.RateTransition2_WrBufIdx == 0);
  for (i = 0; i < 9; i++) {
    wturbines_DW.RateTransition2_Buf[i + wturbines_DW.RateTransition2_WrBufIdx *
      9] = wturbines_B.ZeroOrderHold4[i];
  }

  /* End of RateTransition: '<S5>/Rate Transition2' */

  /* RateTransition: '<S5>/Rate Transition3' */
  wturbines_DW.RateTransition3_WrBufIdx = static_cast<int8_T>
    (wturbines_DW.RateTransition3_WrBufIdx == 0);
  for (i = 0; i < 9; i++) {
    wturbines_DW.RateTransition3_Buf[i + wturbines_DW.RateTransition3_WrBufIdx *
      9] = wturbines_B.ZeroOrderHold1[i];
  }

  /* End of RateTransition: '<S5>/Rate Transition3' */

  /* RateTransition: '<S5>/Rate Transition4' */
  wturbines_DW.RateTransition4_WrBufIdx = static_cast<int8_T>
    (wturbines_DW.RateTransition4_WrBufIdx == 0);
  for (i = 0; i < 9; i++) {
    wturbines_DW.RateTransition4_Buf[i + wturbines_DW.RateTransition4_WrBufIdx *
      9] = wturbines_B.ZeroOrderHold2[i];
  }

  /* End of RateTransition: '<S5>/Rate Transition4' */

  /* Update for Iterator SubSystem: '<Root>/For Each Subsystem' */
  for (ForEach_itr = 0; ForEach_itr < 9; ForEach_itr++) {
    /* Update for RandomNumber: '<S267>/White Noise' */
    wturbines_DW.CoreSubsys[ForEach_itr].NextOutput = rt_nrand_Upu32_Yd_f_pw_snf
      (&wturbines_DW.CoreSubsys[ForEach_itr].RandSeed) *
      wturbines_cal->wturbines_CoreSubsys_cal.WhiteNoise_StdDev +
      wturbines_cal->wturbines_CoreSubsys_cal.WhiteNoise_Mean;

    /* Update for RandomNumber: '<S270>/White Noise' */
    wturbines_DW.CoreSubsys[ForEach_itr].NextOutput_i =
      rt_nrand_Upu32_Yd_f_pw_snf(&wturbines_DW.CoreSubsys[ForEach_itr].
      RandSeed_m) * wturbines_cal->wturbines_CoreSubsys_cal.WhiteNoise_StdDev_k
      + wturbines_cal->wturbines_CoreSubsys_cal.WhiteNoise_Mean_p;

    /* Update for RandomNumber: '<S268>/White Noise' */
    wturbines_DW.CoreSubsys[ForEach_itr].NextOutput_a =
      rt_nrand_Upu32_Yd_f_pw_snf(&wturbines_DW.CoreSubsys[ForEach_itr].
      RandSeed_j) * wturbines_cal->wturbines_CoreSubsys_cal.WhiteNoise_StdDev_a
      + wturbines_cal->wturbines_CoreSubsys_cal.WhiteNoise_Mean_h;

    /* Update for RandomNumber: '<S271>/White Noise' */
    wturbines_DW.CoreSubsys[ForEach_itr].NextOutput_f =
      rt_nrand_Upu32_Yd_f_pw_snf(&wturbines_DW.CoreSubsys[ForEach_itr].
      RandSeed_l) * wturbines_cal->wturbines_CoreSubsys_cal.WhiteNoise_StdDev_d
      + wturbines_cal->wturbines_CoreSubsys_cal.WhiteNoise_Mean_hm;

    /* Update for RandomNumber: '<S272>/White Noise' */
    wturbines_DW.CoreSubsys[ForEach_itr].NextOutput_m =
      rt_nrand_Upu32_Yd_f_pw_snf(&wturbines_DW.CoreSubsys[ForEach_itr].
      RandSeed_a) * wturbines_cal->wturbines_CoreSubsys_cal.WhiteNoise_StdDev_n
      + wturbines_cal->wturbines_CoreSubsys_cal.WhiteNoise_Mean_pi;

    /* Update for RandomNumber: '<S273>/White Noise' */
    wturbines_DW.CoreSubsys[ForEach_itr].NextOutput_n =
      rt_nrand_Upu32_Yd_f_pw_snf(&wturbines_DW.CoreSubsys[ForEach_itr].
      RandSeed_g) * wturbines_cal->wturbines_CoreSubsys_cal.WhiteNoise_StdDev_e
      + wturbines_cal->wturbines_CoreSubsys_cal.WhiteNoise_Mean_d;

    /* Update for RandomNumber: '<S269>/White Noise' */
    wturbines_DW.CoreSubsys[ForEach_itr].NextOutput_b =
      rt_nrand_Upu32_Yd_f_pw_snf(&wturbines_DW.CoreSubsys[ForEach_itr].
      RandSeed_b) * wturbines_cal->wturbines_CoreSubsys_cal.WhiteNoise_StdDev_f
      + wturbines_cal->wturbines_CoreSubsys_cal.WhiteNoise_Mean_g;
  }

  /* End of Update for SubSystem: '<Root>/For Each Subsystem' */

  /* Update absolute time */
  /* The "clockTick2" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.1, which is the step size
   * of the task. Size of "clockTick2" ensures timer will not overflow during the
   * application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick2 and the high bits
   * Timing.clockTickH2. When the low bit overflows to 0, the high bits increment.
   */
  wturbines_M->Timing.clockTick2++;
  if (!wturbines_M->Timing.clockTick2) {
    wturbines_M->Timing.clockTickH2++;
  }
}

/* Model step function for TID3 */
void wturbines_step3(void)             /* Sample time: [0.25s, 0.0s] */
{
  /* local scratch DWork variables */
  int32_T ForEach_itr;
  real_T RateTransition;
  int32_T i;
  int32_T tmp;

  /* Outputs for Iterator SubSystem: '<Root>/For Each Subsystem' incorporates:
   *  ForEach: '<S2>/For Each'
   */
  for (ForEach_itr = 0; ForEach_itr < 9; ForEach_itr++) {
    /* Outputs for Iterator SubSystem: '<Root>/For Each Subsystem' incorporates:
     *  ForEach: '<S2>/For Each'
     */
    wturbines_B.ForEach = ForEach_itr;

    /* RateTransition: '<S2>/Rate Transition7' */
    wturbines_DW.CoreSubsys[ForEach_itr].RateTransition7_RdBufIdx =
      static_cast<int8_T>(wturbines_DW.CoreSubsys[ForEach_itr].
                          RateTransition7_RdBufIdx == 0);
    tmp = wturbines_DW.CoreSubsys[ForEach_itr].RateTransition7_RdBufIdx << 3;
    for (i = 0; i < 8; i++) {
      /* RateTransition: '<S2>/Rate Transition7' */
      RateTransition = wturbines_DW.CoreSubsys[ForEach_itr]
        .RateTransition7_Buf[i + tmp];
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition7_p[i] = RateTransition;

      /* ForEachSliceAssignment generated from: '<S2>/x' */
      wturbines_B.ImpAsg_InsertedFor_x_at_inport_[i + (ForEach_itr << 3)] =
        RateTransition;
    }
  }

  /* End of Outputs for SubSystem: '<Root>/For Each Subsystem' */
  for (i = 0; i < 72; i++) {
    /* RateTransition: '<S6>/Rate Transition' */
    RateTransition = wturbines_B.ImpAsg_InsertedFor_x_at_inport_[i];
    wturbines_B.RateTransition[i] = RateTransition;

    /* DataTypeConversion: '<S6>/Data Type Conversion' */
    wturbines_B.DataTypeConversion[i] = static_cast<real32_T>(RateTransition);
  }

  /* S-Function (any2byte_svd): '<S6>/Byte Pack1' */

  /* Pack: <S6>/Byte Pack1 */
  {
    uint32_T MW_outputPortOffset = 0U;
    uint16_T MW_inputPortWidth = 0U;

    /* Packed output data type - uint8_T */
    void* packData = &wturbines_B.BytePack1[0];

    /* Packing the values of Input 1 */
    /* Input data type - real32_T, size - 72 */
    {
      MW_inputPortWidth = (uint16_T)72 * sizeof(real32_T);
      memcpy((void *)&(((uint8_T *)packData)[MW_outputPortOffset]), (void*)
             &wturbines_B.DataTypeConversion[0], MW_inputPortWidth);
    }
  }

  /* S-Function (slrealtimeUDPSend): '<S6>/UDP Send1' incorporates:
   *  Constant: '<S6>/Constant1'
   */
  RateTransition = *get_Nt() * *get_turbineDataBytes();

  {
    try {
      slrealtime::ip::udp::Socket *udpSock = reinterpret_cast<slrealtime::ip::
        udp::Socket*>(wturbines_DW.UDPSend1_PWORK);
      uint8_t *remoteAddress = (uint8_t *)wturbines_cal->UDPSend1_toAddress;
      uint16_t *remotePort = (uint16_t *)&wturbines_cal->UDPSend1_toPort;
      udpSock->resetRemoteEndpoint(remoteAddress, remotePort);
      int dataLen = RateTransition;
      dataLen = (dataLen <= wturbines_DW.UDPSend1_IWORK[0]) ? dataLen :
        wturbines_DW.UDPSend1_IWORK[0];
      dataLen = (dataLen <= -1) ? 0 : dataLen;
      void *dataPort = &wturbines_B.BytePack1[0];
      size_t numBytesSend = udpSock->send((const char*)dataPort,dataLen);
    } catch (std::exception& e) {
      std::string tmp = std::string(e.what());
      static std::string eMsg = tmp;
      rtmSetErrorStatus(wturbines_M, eMsg.c_str());
      rtmSetStopRequested(wturbines_M, 1);
      ;
    }
  }

  /* Update absolute time */
  /* The "clockTick3" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.25, which is the step size
   * of the task. Size of "clockTick3" ensures timer will not overflow during the
   * application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick3 and the high bits
   * Timing.clockTickH3. When the low bit overflows to 0, the high bits increment.
   */
  wturbines_M->Timing.clockTick3++;
  if (!wturbines_M->Timing.clockTick3) {
    wturbines_M->Timing.clockTickH3++;
  }
}

/* Model step function for TID4 */
void wturbines_step4(void)             /* Sample time: [0.5s, 0.0s] */
{
  real_T RateTransition_k;
  int32_T i;
  int32_T tmp;

  /* RateTransition: '<S1>/Rate Transition' */
  wturbines_DW.RateTransition_RdBufIdx_e = static_cast<int8_T>
    (wturbines_DW.RateTransition_RdBufIdx_e == 0);
  tmp = wturbines_DW.RateTransition_RdBufIdx_e * 18;
  for (i = 0; i < 18; i++) {
    /* RateTransition: '<S1>/Rate Transition' */
    RateTransition_k = wturbines_DW.RateTransition_Buf[i + tmp];
    wturbines_B.RateTransition_k[i] = RateTransition_k;

    /* DataTypeConversion: '<S1>/Data Type Conversion' */
    wturbines_B.DataTypeConversion_e[i] = static_cast<real32_T>(RateTransition_k);
  }

  /* S-Function (any2byte_svd): '<S1>/Byte Pack1' */

  /* Pack: <S1>/Byte Pack1 */
  {
    uint32_T MW_outputPortOffset = 0U;
    uint16_T MW_inputPortWidth = 0U;

    /* Packed output data type - uint8_T */
    void* packData = &wturbines_B.BytePack1_d[0];

    /* Packing the values of Input 1 */
    /* Input data type - real32_T, size - 18 */
    {
      MW_inputPortWidth = (uint16_T)18 * sizeof(real32_T);
      memcpy((void *)&(((uint8_T *)packData)[MW_outputPortOffset]), (void*)
             &wturbines_B.DataTypeConversion_e[0], MW_inputPortWidth);
    }
  }

  /* S-Function (slrealtimeUDPSend): '<S1>/UDP Send1' incorporates:
   *  Constant: '<S1>/Constant1'
   */
  RateTransition_k = *get_Nt() * 2.0 * 4.0;

  {
    try {
      slrealtime::ip::udp::Socket *udpSock = reinterpret_cast<slrealtime::ip::
        udp::Socket*>(wturbines_DW.UDPSend1_PWORK_g);
      uint8_t *remoteAddress = (uint8_t *)wturbines_cal->UDPSend1_toAddress_b;
      uint16_t *remotePort = (uint16_t *)&wturbines_cal->UDPSend1_toPort_i;
      udpSock->resetRemoteEndpoint(remoteAddress, remotePort);
      int dataLen = RateTransition_k;
      dataLen = (dataLen <= wturbines_DW.UDPSend1_IWORK_g[0]) ? dataLen :
        wturbines_DW.UDPSend1_IWORK_g[0];
      dataLen = (dataLen <= -1) ? 0 : dataLen;
      void *dataPort = &wturbines_B.BytePack1_d[0];
      size_t numBytesSend = udpSock->send((const char*)dataPort,dataLen);
    } catch (std::exception& e) {
      std::string tmp = std::string(e.what());
      static std::string eMsg = tmp;
      rtmSetErrorStatus(wturbines_M, eMsg.c_str());
      rtmSetStopRequested(wturbines_M, 1);
      ;
    }
  }

  /* Update absolute time */
  /* The "clockTick4" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.5, which is the step size
   * of the task. Size of "clockTick4" ensures timer will not overflow during the
   * application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick4 and the high bits
   * Timing.clockTickH4. When the low bit overflows to 0, the high bits increment.
   */
  wturbines_M->Timing.clockTick4++;
  if (!wturbines_M->Timing.clockTick4) {
    wturbines_M->Timing.clockTickH4++;
  }
}

/* Model initialize function */
void wturbines_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  wturbines_cal->wturbines_CoreSubsys_cal.RateLimiter_RisingLim = rtInf;
  wturbines_cal->wturbines_CoreSubsys_cal.RateLimiter_FallingLim = rtMinusInf;
  wturbines_cal->wturbines_CoreSubsys_cal.RateLimiter1_RisingLim = rtInf;
  wturbines_cal->wturbines_CoreSubsys_cal.RateLimiter1_FallingLim = rtMinusInf;
  wturbines_cal->wturbines_CoreSubsys_cal.Saturation2_UpperSat = rtInf;
  wturbines_cal->wturbines_CoreSubsys_cal.Saturation1_UpperSat = rtInf;

  /* Set task counter limit used by the static main program */
  (wturbines_M)->Timing.TaskCounters.cLimit[0] = 1;
  (wturbines_M)->Timing.TaskCounters.cLimit[1] = 1;
  (wturbines_M)->Timing.TaskCounters.cLimit[2] = 10;
  (wturbines_M)->Timing.TaskCounters.cLimit[3] = 25;
  (wturbines_M)->Timing.TaskCounters.cLimit[4] = 50;

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&wturbines_M->solverInfo,
                          &wturbines_M->Timing.simTimeStep);
    rtsiSetTPtr(&wturbines_M->solverInfo, &rtmGetTPtr(wturbines_M));
    rtsiSetStepSizePtr(&wturbines_M->solverInfo, &wturbines_M->Timing.stepSize0);
    rtsiSetdXPtr(&wturbines_M->solverInfo, &wturbines_M->derivs);
    rtsiSetContStatesPtr(&wturbines_M->solverInfo, (real_T **)
                         &wturbines_M->contStates);
    rtsiSetNumContStatesPtr(&wturbines_M->solverInfo,
      &wturbines_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&wturbines_M->solverInfo,
      &wturbines_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&wturbines_M->solverInfo,
      &wturbines_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&wturbines_M->solverInfo,
      &wturbines_M->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&wturbines_M->solverInfo, (boolean_T**)
      &wturbines_M->contStateDisabled);
    rtsiSetErrorStatusPtr(&wturbines_M->solverInfo, (&rtmGetErrorStatus
      (wturbines_M)));
    rtsiSetRTModelPtr(&wturbines_M->solverInfo, wturbines_M);
  }

  rtsiSetSimTimeStep(&wturbines_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&wturbines_M->solverInfo, false);
  rtsiSetIsContModeFrozen(&wturbines_M->solverInfo, false);
  wturbines_M->intgData.y = wturbines_M->odeY;
  wturbines_M->intgData.f[0] = wturbines_M->odeF[0];
  wturbines_M->intgData.f[1] = wturbines_M->odeF[1];
  wturbines_M->intgData.f[2] = wturbines_M->odeF[2];
  wturbines_M->intgData.f[3] = wturbines_M->odeF[3];
  wturbines_M->contStates = ((X_wturbines_T *) &wturbines_X);
  wturbines_M->contStateDisabled = ((XDis_wturbines_T *) &wturbines_XDis);
  wturbines_M->Timing.tStart = (0.0);
  rtsiSetSolverData(&wturbines_M->solverInfo, static_cast<void *>
                    (&wturbines_M->intgData));
  rtsiSetSolverName(&wturbines_M->solverInfo,"ode4");
  rtmSetTPtr(wturbines_M, &wturbines_M->Timing.tArray[0]);
  wturbines_M->Timing.stepSize0 = 0.01;

  /* block I/O */
  (void) std::memset((static_cast<void *>(&wturbines_B)), 0,
                     sizeof(B_wturbines_T));

  {
    int32_T i;
    for (i = 0; i < 9; i++) {
      wturbines_B.OpMode[i] = op_mode_None;
    }

    for (i = 0; i < 9; i++) {
      wturbines_B.ImpAsg_InsertedFor_ctrlState_at[i] = op_mode_None;
    }
  }

  /* states (continuous) */
  {
    (void) std::memset(static_cast<void *>(&wturbines_X), 0,
                       sizeof(X_wturbines_T));
  }

  /* disabled states */
  {
    (void) std::memset(static_cast<void *>(&wturbines_XDis), 0,
                       sizeof(XDis_wturbines_T));
  }

  /* states (dwork) */
  (void) std::memset(static_cast<void *>(&wturbines_DW), 0,
                     sizeof(DW_wturbines_T));

  {
    real_T tmp;
    real_T tmp_0;
    int32_T i;

    /* Start for S-Function (slrealtimeUDPSend): '<S6>/UDP Send1' incorporates:
     *  Constant: '<S6>/Constant1'
     */
    tmp_0 = *get_Nt();
    for (i = 0; i < 9; i++) {
      /* Start for RateTransition: '<S5>/Rate Transition' */
      wturbines_B.RateTransition_l[i] =
        wturbines_cal->RateTransition_InitialConditi_l;

      /* Start for RateTransition: '<S5>/Rate Transition3' */
      wturbines_B.RateTransition3[i] =
        wturbines_cal->RateTransition3_InitialConditio;

      /* Start for RateTransition: '<S5>/Rate Transition4' */
      wturbines_B.RateTransition4[i] =
        wturbines_cal->RateTransition4_InitialConditio;

      /* Start for RateTransition: '<S5>/Rate Transition1' */
      wturbines_B.RateTransition1[i] =
        wturbines_cal->RateTransition1_InitialConditio;

      /* Start for RateTransition: '<S5>/Rate Transition2' */
      wturbines_B.RateTransition2[i] =
        wturbines_cal->RateTransition2_InitialConditio;

      /* Start for RateTransition: '<S4>/Rate Transition1' */
      wturbines_B.RateTransition1_c[i] =
        wturbines_cal->RateTransition1_InitialCondit_k;

      /* Start for RateTransition: '<S4>/Rate Transition2' */
      wturbines_B.RateTransition2_p[i] =
        wturbines_cal->RateTransition2_InitialCondit_d;
    }

    /* Start for S-Function (slrealtimeUDPReceive): '<S4>/UDP Receive' */
    {
      try {
        uint8_t *tempAddr = nullptr;
        uint8_t *tempInterface = nullptr;
        slrealtime::ip::udp::Socket *udpSock = (slrealtime::ip::udp::Socket *)
          slrealtime::ip::SocketFactory::createSocket(slrealtime::ip::SocketType::
          UDP, "172.19.3.43",49152U);
        if (tempAddr)
          delete tempAddr;
        if (tempInterface)
          delete tempInterface;
        wturbines_DW.UDPReceive_IWORK[0] = 72;
        wturbines_DW.UDPReceive_PWORK[0] = reinterpret_cast<void*>(udpSock);
        char *buffer = (char *)calloc(65507,sizeof(char));
        wturbines_DW.UDPReceive_PWORK[1] = (void*)buffer;
      } catch (std::exception& e) {
        std::string tmp = std::string(e.what());
        static std::string eMsg = tmp;
        rtmSetErrorStatus(wturbines_M, eMsg.c_str());
        rtmSetStopRequested(wturbines_M, 1);
        ;
      }
    }

    /* Start for S-Function (slrealtimeUDPReceive): '<S5>/UDP Receive' */
    {
      try {
        uint8_t *tempAddr = nullptr;
        uint8_t *tempInterface = nullptr;
        slrealtime::ip::udp::Socket *udpSock = (slrealtime::ip::udp::Socket *)
          slrealtime::ip::SocketFactory::createSocket(slrealtime::ip::SocketType::
          UDP, "172.19.3.43",10000U);
        if (tempAddr)
          delete tempAddr;
        if (tempInterface)
          delete tempInterface;
        wturbines_DW.UDPReceive_IWORK_d[0] = 99;
        wturbines_DW.UDPReceive_PWORK_k[0] = reinterpret_cast<void*>(udpSock);
        char *buffer = (char *)calloc(65507,sizeof(char));
        wturbines_DW.UDPReceive_PWORK_k[1] = (void*)buffer;
      } catch (std::exception& e) {
        std::string tmp = std::string(e.what());
        static std::string eMsg = tmp;
        rtmSetErrorStatus(wturbines_M, eMsg.c_str());
        rtmSetStopRequested(wturbines_M, 1);
        ;
      }
    }

    /* Start for S-Function (slrealtimeUDPSend): '<S6>/UDP Send1' incorporates:
     *  Constant: '<S6>/Constant1'
     */
    tmp = tmp_0 * *get_turbineDataBytes();

    {
      try {
        slrealtime::ip::udp::Socket *udpSock = (slrealtime::ip::udp::Socket *)
          slrealtime::ip::SocketFactory::createSocket(slrealtime::ip::SocketType::
          UDP,"172.19.3.43",11000U);
        uint8_t *remoteAddress = (uint8_t *)wturbines_cal->UDPSend1_toAddress;
        uint16_t *remotePort = (uint16_t *)&wturbines_cal->UDPSend1_toPort;
        udpSock->setRemoteEndpoint(remoteAddress, remotePort[0]);
        wturbines_DW.UDPSend1_IWORK[0] = 288;
        wturbines_DW.UDPSend1_IWORK[1] = 11000U;
        wturbines_DW.UDPSend1_PWORK = reinterpret_cast<void*>(udpSock);
      } catch (std::exception& e) {
        std::string tmp = std::string(e.what());
        static std::string eMsg = tmp;
        rtmSetErrorStatus(wturbines_M, eMsg.c_str());
        rtmSetStopRequested(wturbines_M, 1);
        ;
      }
    }

    /* Start for S-Function (slrealtimeUDPSend): '<S1>/UDP Send1' incorporates:
     *  Constant: '<S1>/Constant1'
     */
    tmp = tmp_0 * 2.0 * 4.0;

    {
      try {
        slrealtime::ip::udp::Socket *udpSock = (slrealtime::ip::udp::Socket *)
          slrealtime::ip::SocketFactory::createSocket(slrealtime::ip::SocketType::
          UDP,"172.19.3.43",49160U);
        uint8_t *remoteAddress = (uint8_t *)wturbines_cal->UDPSend1_toAddress_b;
        uint16_t *remotePort = (uint16_t *)&wturbines_cal->UDPSend1_toPort_i;
        udpSock->setRemoteEndpoint(remoteAddress, remotePort[0]);
        wturbines_DW.UDPSend1_IWORK_g[0] = 72;
        wturbines_DW.UDPSend1_IWORK_g[1] = 49160U;
        wturbines_DW.UDPSend1_PWORK_g = reinterpret_cast<void*>(udpSock);
      } catch (std::exception& e) {
        std::string tmp = std::string(e.what());
        static std::string eMsg = tmp;
        rtmSetErrorStatus(wturbines_M, eMsg.c_str());
        rtmSetStopRequested(wturbines_M, 1);
        ;
      }
    }
  }

  {
    /* local scratch DWork variables */
    int32_T ForEach_itr;
    real_T tmp;
    int32_T i;
    int32_T t;
    uint32_T tseed;
    boolean_T flag;
    static const loggingData tmp_0 = { 0.0,/* Cp */
      0.0,                             /* Ct */
      0.0,                             /* GenSpd */
      op_mode_None,                    /* OpMode */
      0.0,                             /* OrientationSpt */
      0.0,                             /* Pitch */
      0.0,                             /* PitchSpt */
      0.0,                             /* RotSpd */
      0U,                              /* eCtrlMode */
      0.0,                             /* TBrake */
      0.0,                             /* TGen */
      0.0,                             /* Ta */
      0.0,                             /* WsEff */
      0.0,                             /* YawTrue */
      0.0,                             /* HorWdSpd */
      0.0,                             /* HorWdDir */
      false,                           /* bEnable */
      false,                           /* bStop */
      0.0                              /* WSpt */
    };

    real_T tmp_1[400];
    real_T tmp_2[20];
    real_T tmp_3[20];

    /* InitializeConditions for RateTransition: '<S5>/Rate Transition' */
    for (i = 0; i < 9; i++) {
      wturbines_DW.RateTransition_Buf_n[i] =
        wturbines_cal->RateTransition_InitialConditi_l;
    }

    wturbines_DW.RateTransition_WrBufIdx = 0;
    wturbines_DW.RateTransition_RdBufIdx = 1;

    /* End of InitializeConditions for RateTransition: '<S5>/Rate Transition' */

    /* InitializeConditions for RateTransition: '<S5>/Rate Transition3' */
    for (i = 0; i < 9; i++) {
      wturbines_DW.RateTransition3_Buf[i] =
        wturbines_cal->RateTransition3_InitialConditio;
    }

    wturbines_DW.RateTransition3_WrBufIdx = 0;
    wturbines_DW.RateTransition3_RdBufIdx = 1;

    /* End of InitializeConditions for RateTransition: '<S5>/Rate Transition3' */

    /* InitializeConditions for RateTransition: '<S5>/Rate Transition4' */
    for (i = 0; i < 9; i++) {
      wturbines_DW.RateTransition4_Buf[i] =
        wturbines_cal->RateTransition4_InitialConditio;
    }

    wturbines_DW.RateTransition4_WrBufIdx = 0;
    wturbines_DW.RateTransition4_RdBufIdx = 1;

    /* End of InitializeConditions for RateTransition: '<S5>/Rate Transition4' */

    /* InitializeConditions for RateTransition: '<S5>/Rate Transition1' */
    for (i = 0; i < 9; i++) {
      wturbines_DW.RateTransition1_Buf[i] =
        wturbines_cal->RateTransition1_InitialConditio;
    }

    wturbines_DW.RateTransition1_WrBufIdx = 0;
    wturbines_DW.RateTransition1_RdBufIdx = 1;

    /* End of InitializeConditions for RateTransition: '<S5>/Rate Transition1' */

    /* InitializeConditions for RateTransition: '<S5>/Rate Transition2' */
    for (i = 0; i < 9; i++) {
      wturbines_DW.RateTransition2_Buf[i] =
        wturbines_cal->RateTransition2_InitialConditio;
    }

    wturbines_DW.RateTransition2_WrBufIdx = 0;
    wturbines_DW.RateTransition2_RdBufIdx = 1;

    /* End of InitializeConditions for RateTransition: '<S5>/Rate Transition2' */

    /* InitializeConditions for RateTransition: '<S4>/Rate Transition1' */
    for (i = 0; i < 9; i++) {
      wturbines_DW.RateTransition1_Buf_f[i] =
        wturbines_cal->RateTransition1_InitialCondit_k;
    }

    wturbines_DW.RateTransition1_WrBufIdx_g = 0;
    wturbines_DW.RateTransition1_RdBufIdx_k = 1;

    /* End of InitializeConditions for RateTransition: '<S4>/Rate Transition1' */

    /* InitializeConditions for RateTransition: '<S4>/Rate Transition2' */
    for (i = 0; i < 9; i++) {
      wturbines_DW.RateTransition2_Buf_k[i] =
        wturbines_cal->RateTransition2_InitialCondit_d;
    }

    wturbines_DW.RateTransition2_WrBufIdx_g = 0;
    wturbines_DW.RateTransition2_RdBufIdx_c = 1;

    /* End of InitializeConditions for RateTransition: '<S4>/Rate Transition2' */

    /* InitializeConditions for RateTransition: '<S1>/Rate Transition' */
    for (i = 0; i < 18; i++) {
      wturbines_DW.RateTransition_Buf[i] =
        wturbines_cal->RateTransition_InitialCondition;
    }

    wturbines_DW.RateTransition_WrBufIdx_j = 0;
    wturbines_DW.RateTransition_RdBufIdx_e = 1;

    /* End of InitializeConditions for RateTransition: '<S1>/Rate Transition' */

    /* SystemInitialize for Iterator SubSystem: '<Root>/For Each Subsystem' */
    ForEach_itr = 0;

    /* End of SystemInitialize for SubSystem: '<Root>/For Each Subsystem' */
    for (i = 0; i < 400; i++) {
      tmp_1[i] = (get_Ct_mat())[i];
    }

    for (i = 0; i < 20; i++) {
      tmp_2[i] = (get_tsr_vec())[i];
    }

    for (i = 0; i < 20; i++) {
      tmp_3[i] = (get_pitch_vec())[i];
    }

    /* SystemInitialize for Iterator SubSystem: '<Root>/For Each Subsystem' */
    while (ForEach_itr < 9) {
      /* SystemInitialize for DataTypeConversion: '<S2>/Data Type Conversion' */
      wturbines_B.CoreSubsys[ForEach_itr].DataTypeConversion = 0.0;

      /* SystemInitialize for DataTypeConversion: '<S2>/Data Type Conversion1' */
      wturbines_B.CoreSubsys[ForEach_itr].DataTypeConversion1 = 0.0;

      /* SystemInitialize for DataTypeConversion: '<S2>/Data Type Conversion2' */
      wturbines_B.CoreSubsys[ForEach_itr].DataTypeConversion2 = 0.0;

      /* SystemInitialize for DataTypeConversion: '<S2>/Data Type Conversion3' */
      wturbines_B.CoreSubsys[ForEach_itr].DataTypeConversion3 = 0.0;

      /* SystemInitialize for InitialCondition: '<S2>/IC' */
      wturbines_B.CoreSubsys[ForEach_itr].IC = 0.0;

      /* SystemInitialize for InitialCondition: '<S2>/IC1' */
      wturbines_B.CoreSubsys[ForEach_itr].IC1 = 0.0;

      /* SystemInitialize for InitialCondition: '<S2>/IC2' */
      wturbines_B.CoreSubsys[ForEach_itr].IC2 = false;

      /* SystemInitialize for InitialCondition: '<S2>/IC3' */
      wturbines_B.CoreSubsys[ForEach_itr].IC3 = false;

      /* SystemInitialize for InitialCondition: '<S2>/IC4' */
      wturbines_B.CoreSubsys[ForEach_itr].IC4 = 0U;

      /* SystemInitialize for InitialCondition: '<S2>/IC5' */
      wturbines_B.CoreSubsys[ForEach_itr].IC5 = 0.0;

      /* SystemInitialize for InitialCondition: '<S2>/IC6' */
      wturbines_B.CoreSubsys[ForEach_itr].IC6 = 0.0;

      /* SystemInitialize for Integrator: '<S14>/Integrator' */
      wturbines_B.CoreSubsys[ForEach_itr].t = 0.0;

      /* SystemInitialize for Saturate: '<S14>/Saturation' */
      wturbines_B.CoreSubsys[ForEach_itr].RotSpd = 0.0;

      /* SystemInitialize for Product: '<S282>/Product' */
      wturbines_B.CoreSubsys[ForEach_itr].Product = 0.0;

      /* SystemInitialize for RateTransition: '<S2>/Rate Transition' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition = 0.0;

      /* SystemInitialize for RateLimiter: '<S2>/Rate Limiter' */
      wturbines_B.CoreSubsys[ForEach_itr].RateLimiter = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].PrevY = 0.0;

      /* SystemInitialize for RateTransition: '<S2>/Rate Transition1' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition1 = 0.0;

      /* SystemInitialize for RateLimiter: '<S2>/Rate Limiter1' */
      wturbines_B.CoreSubsys[ForEach_itr].RateLimiter1 = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].PrevY_e = 0.0;

      /* SystemInitialize for RateTransition: '<S2>/Rate Transition6' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition6 = 0.0;

      /* SystemInitialize for RateLimiter: '<S278>/Rate Limiter' */
      wturbines_B.CoreSubsys[ForEach_itr].RateLimiter_p = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].PrevY_n = 0.0;

      /* SystemInitialize for Gain: '<S284>/Gain1' */
      wturbines_B.CoreSubsys[ForEach_itr].Gain1 = 0.0;

      /* SystemInitialize for Trigonometry: '<S14>/Trigonometric Function' */
      wturbines_B.CoreSubsys[ForEach_itr].TrigonometricFunction = 0.0;

      /* SystemInitialize for Product: '<S14>/Product' */
      wturbines_B.CoreSubsys[ForEach_itr].Product_l = 0.0;

      /* SystemInitialize for Saturate: '<S14>/Saturation2' */
      wturbines_B.CoreSubsys[ForEach_itr].WsEff = 0.0;

      /* SystemInitialize for Product: '<S282>/Divide' */
      wturbines_B.CoreSubsys[ForEach_itr].t_c = 0.0;

      /* SystemInitialize for Gain: '<S26>/Gain1' */
      wturbines_B.CoreSubsys[ForEach_itr].Gain1_f = 0.0;

      /* SystemInitialize for RateTransition: '<S12>/Rate Transition13' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition13 = 0.0;

      /* SystemInitialize for RateTransition: '<S12>/Rate Transition2' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition2 = 0.0;

      /* SystemInitialize for RateTransition: '<S2>/Rate Transition2' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition2_b = false;

      /* SystemInitialize for RateTransition: '<S2>/Rate Transition3' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition3_j = false;

      /* SystemInitialize for RateTransition: '<S2>/Rate Transition5' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition5 = 0.0;

      /* SystemInitialize for Saturate: '<S8>/Saturation' */
      wturbines_B.CoreSubsys[ForEach_itr].Saturation = 0.0;

      /* SystemInitialize for Switch: '<S8>/Switch' */
      wturbines_B.CoreSubsys[ForEach_itr].Pref = 0.0;

      /* SystemInitialize for Math: '<S29>/Square' */
      wturbines_B.CoreSubsys[ForEach_itr].Square = 0.0;

      /* SystemInitialize for Product: '<S29>/Product1' */
      wturbines_B.CoreSubsys[ForEach_itr].Product1 = 0.0;

      /* SystemInitialize for Product: '<S29>/Divide1' */
      wturbines_B.CoreSubsys[ForEach_itr].Divide1 = 0.0;

      /* SystemInitialize for Math: '<S29>/Power' */
      wturbines_B.CoreSubsys[ForEach_itr].ws_drt = 0.0;

      /* SystemInitialize for Sum: '<S29>/Sum1' */
      wturbines_B.CoreSubsys[ForEach_itr].ws_drwst = 0.0;

      /* SystemInitialize for Switch: '<S29>/Derating' */
      wturbines_B.CoreSubsys[ForEach_itr]._sett = 0.0;

      /* SystemInitialize for RateTransition: '<S2>/Rate Transition4' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition4_e = 0U;

      /* SystemInitialize for RelationalOperator: '<S18>/Compare' */
      wturbines_B.CoreSubsys[ForEach_itr].Compare = false;

      /* SystemInitialize for RelationalOperator: '<S20>/Compare' */
      wturbines_B.CoreSubsys[ForEach_itr].Compare_c = false;

      /* SystemInitialize for RelationalOperator: '<S19>/Compare' */
      wturbines_B.CoreSubsys[ForEach_itr].Compare_j = false;

      /* SystemInitialize for Logic: '<S11>/OR1' */
      wturbines_B.CoreSubsys[ForEach_itr].OR1 = false;

      /* SystemInitialize for Relay: '<S151>/Relay' */
      wturbines_B.CoreSubsys[ForEach_itr].Relay = 0.0;

      /* SystemInitialize for RateTransition: '<S12>/Rate Transition3' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition3 = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition13_Buf[0] = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition2_Buf[0] = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition3_Buf[0] = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition13_Buf[1] = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition2_Buf[1] = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition3_Buf[1] = 0.0;

      /* SystemInitialize for Switch: '<S151>/Switch' */
      wturbines_B.CoreSubsys[ForEach_itr].Switch = 0.0;

      /* SystemInitialize for RelationalOperator: '<S150>/IsNaN1' */
      wturbines_B.CoreSubsys[ForEach_itr].IsNaN1 = false;

      /* SystemInitialize for Logic: '<S150>/NOT' */
      wturbines_B.CoreSubsys[ForEach_itr].is_not_nan = false;

      /* SystemInitialize for Switch: '<S150>/Switch' */
      wturbines_B.CoreSubsys[ForEach_itr].Switch_l = 0.0;

      /* SystemInitialize for Sum: '<S29>/Sum' */
      wturbines_B.CoreSubsys[ForEach_itr].e_t = 0.0;

      /* SystemInitialize for Gain: '<S252>/Proportional Gain' */
      wturbines_B.CoreSubsys[ForEach_itr].ProportionalGain = 0.0;

      /* SystemInitialize for Integrator: '<S247>/Integrator' */
      wturbines_B.CoreSubsys[ForEach_itr].Integrator = 0.0;

      /* SystemInitialize for Sum: '<S157>/Sum' */
      wturbines_B.CoreSubsys[ForEach_itr].ws_drwst_p = 0.0;

      /* SystemInitialize for Product: '<S157>/Divide' */
      wturbines_B.CoreSubsys[ForEach_itr].Divide = 0.0;

      /* SystemInitialize for Gain: '<S157>/Gain' */
      wturbines_B.CoreSubsys[ForEach_itr].Gain = 0.0;

      /* SystemInitialize for Sum: '<S156>/Sum' */
      wturbines_B.CoreSubsys[ForEach_itr].ws_drwst_o = 0.0;

      /* SystemInitialize for Gain: '<S199>/Proportional Gain' */
      wturbines_B.CoreSubsys[ForEach_itr].ProportionalGain_d = 0.0;

      /* SystemInitialize for Integrator: '<S194>/Integrator' */
      wturbines_B.CoreSubsys[ForEach_itr].Integrator_i = 0.0;

      /* SystemInitialize for MultiPortSwitch: '<S27>/Multiport Switch' */
      wturbines_B.CoreSubsys[ForEach_itr]._rreft = 0.0;

      /* SystemInitialize for Sum: '<S27>/Sum' */
      wturbines_B.CoreSubsys[ForEach_itr].e_rt = 0.0;

      /* SystemInitialize for Gain: '<S137>/Proportional Gain' */
      wturbines_B.CoreSubsys[ForEach_itr].ProportionalGain_p = 0.0;

      /* SystemInitialize for Integrator: '<S132>/Integrator' */
      wturbines_B.CoreSubsys[ForEach_itr].Integrator_e = 0.0;

      /* SystemInitialize for Delay: '<S27>/Delay' */
      wturbines_B.CoreSubsys[ForEach_itr].Delay = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].Delay_DSTATE = 0.0;

      /* SystemInitialize for Gain: '<S96>/Gain' */
      wturbines_B.CoreSubsys[ForEach_itr].Gain_k = 0.0;

      /* SystemInitialize for Gain: '<S33>/Gain' */
      wturbines_B.CoreSubsys[ForEach_itr].Gain_h = 0.0;

      /* SystemInitialize for Product: '<S83>/PProd Out' */
      wturbines_B.CoreSubsys[ForEach_itr].PProdOut = 0.0;

      /* SystemInitialize for Integrator: '<S78>/Integrator' */
      wturbines_B.CoreSubsys[ForEach_itr].Integrator_d = 0.0;

      /* SystemInitialize for Sum: '<S87>/Sum' */
      wturbines_B.CoreSubsys[ForEach_itr].Sum = 0.0;

      /* SystemInitialize for MultiPortSwitch: '<S24>/Multiport Switch' */
      wturbines_B.CoreSubsys[ForEach_itr].MultiportSwitch[0] = 0.0;
      wturbines_B.CoreSubsys[ForEach_itr].MultiportSwitch[1] = 0.0;

      /* SystemInitialize for Switch: '<S11>/Switch2' */
      wturbines_B.CoreSubsys[ForEach_itr].PitchSpt = 0.0;

      /* SystemInitialize for RateLimiter: '<S276>/Rate Limiter' */
      wturbines_B.CoreSubsys[ForEach_itr].RateLimiter_n = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].PrevY_d = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].LastMajorTime = 0.0;

      /* SystemInitialize for Gain: '<S283>/Gain' */
      wturbines_B.CoreSubsys[ForEach_itr].Gain_n = 0.0;

      /* SystemInitialize for Saturate: '<S14>/Saturation1' */
      wturbines_B.CoreSubsys[ForEach_itr].Ct_n = 0.0;

      /* SystemInitialize for RateTransition: '<S2>/Rate Transition8' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition8 = 0.0;

      /* SystemInitialize for RateTransition: '<S2>/Rate Transition9' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition9 = 0.0;

      /* SystemInitialize for RateTransition: '<S12>/Rate Transition6' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition6_o = 0.0;

      /* SystemInitialize for RateTransition: '<S12>/Rate Transition' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition_k = 0.0;

      /* SystemInitialize for RateTransition: '<S12>/Rate Transition5' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition5_i = 0.0;

      /* SystemInitialize for Gain: '<S14>/Multiply2' */
      wturbines_B.CoreSubsys[ForEach_itr].GenSpd = 0.0;

      /* SystemInitialize for RelationalOperator: '<S22>/Compare' */
      wturbines_B.CoreSubsys[ForEach_itr].Compare_m = false;

      /* SystemInitialize for Switch: '<S11>/Switch5' */
      wturbines_B.CoreSubsys[ForEach_itr].Switch5 = 0.0;

      /* SystemInitialize for Saturate: '<S11>/Saturation' */
      wturbines_B.CoreSubsys[ForEach_itr].Tgen = 0.0;

      /* SystemInitialize for Product: '<S279>/Product' */
      wturbines_B.CoreSubsys[ForEach_itr].Product_m = 0.0;

      /* SystemInitialize for Gain: '<S279>/Multiply' */
      wturbines_B.CoreSubsys[ForEach_itr].Multiply = 0.0;

      /* SystemInitialize for RateTransition: '<S12>/Rate Transition1' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition1_h = 0.0;

      /* SystemInitialize for Gain: '<S10>/Gain' */
      wturbines_B.CoreSubsys[ForEach_itr].Gain_i = 0.0;

      /* SystemInitialize for RateTransition: '<S12>/Rate Transition4' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition4 = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition5_Buf[0] = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition1_Buf[0] = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition4_Buf[0] = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition5_Buf[1] = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition1_Buf[1] = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition4_Buf[1] = 0.0;

      /* SystemInitialize for Gain: '<S15>/Gain' */
      wturbines_B.CoreSubsys[ForEach_itr].Gain_o = 0.0;

      /* SystemInitialize for RateTransition: '<S2>/Rate Transition7' */
      std::memset(&wturbines_B.CoreSubsys[ForEach_itr].RateTransition7_p[0], 0,
                  sizeof(real_T) << 3U);
      std::memset(&wturbines_DW.CoreSubsys[ForEach_itr].RateTransition7_Buf[0],
                  0, sizeof(real_T) << 4U);

      /* SystemInitialize for RelationalOperator: '<S21>/Compare' */
      wturbines_B.CoreSubsys[ForEach_itr].Compare_b = false;

      /* SystemInitialize for SignalConversion: '<S33>/Signal Copy' */
      wturbines_B.CoreSubsys[ForEach_itr].I[0] = 0.0;
      wturbines_B.CoreSubsys[ForEach_itr].I[1] = 0.0;

      /* SystemInitialize for Gain: '<S33>/Gain1' */
      wturbines_B.CoreSubsys[ForEach_itr].Gain1_g = 0.0;

      /* SystemInitialize for Product: '<S75>/IProd Out' */
      wturbines_B.CoreSubsys[ForEach_itr].IProdOut = 0.0;

      /* SystemInitialize for Gain: '<S129>/Integral Gain' */
      wturbines_B.CoreSubsys[ForEach_itr].IntegralGain = 0.0;

      /* SystemInitialize for StateSpace: '<S34>/H&#x221E; controller ' */
      wturbines_B.CoreSubsys[ForEach_itr].Hcontroller = 0.0;

      /* SystemInitialize for Gain: '<S158>/Multiply' */
      wturbines_B.CoreSubsys[ForEach_itr].Multiply_k = 0.0;

      /* SystemInitialize for Gain: '<S158>/Multiply1' */
      wturbines_B.CoreSubsys[ForEach_itr].Multiply1 = 0.0;

      /* SystemInitialize for Gain: '<S191>/Integral Gain' */
      wturbines_B.CoreSubsys[ForEach_itr].IntegralGain_g = 0.0;

      /* SystemInitialize for Gain: '<S244>/Integral Gain' */
      wturbines_B.CoreSubsys[ForEach_itr].IntegralGain_a = 0.0;

      /* SystemInitialize for Gain: '<S265>/Gain' */
      wturbines_B.CoreSubsys[ForEach_itr]._grated = 0.0;

      /* SystemInitialize for Switch: '<S11>/Switch3' */
      wturbines_B.CoreSubsys[ForEach_itr].Tbrake = 0.0;

      /* SystemInitialize for RateTransition: '<S12>/Rate Transition7' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition7 = 0.0;

      /* SystemInitialize for RateTransition: '<S12>/Rate Transition9' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition9_o = 0.0;

      /* SystemInitialize for RateTransition: '<S12>/Rate Transition8' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition8_e = 0.0;

      /* SystemInitialize for RateTransition: '<S12>/Rate Transition10' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition10 = 0.0;

      /* SystemInitialize for RateTransition: '<S12>/Rate Transition11' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition11 = 0.0;

      /* SystemInitialize for RateTransition: '<S12>/Rate Transition12' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition12 = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition7_Buf_h[0] = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition9_Buf[0] = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition8_Buf[0] = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition10_Buf[0] = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition11_Buf[0] = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition12_Buf[0] = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition7_Buf_h[1] = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition9_Buf[1] = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition8_Buf[1] = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition10_Buf[1] = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition11_Buf[1] = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition12_Buf[1] = 0.0;

      /* SystemInitialize for RelationalOperator: '<S285>/Compare' */
      wturbines_B.CoreSubsys[ForEach_itr].Compare_p = false;

      /* SystemInitialize for RelationalOperator: '<S286>/Compare' */
      wturbines_B.CoreSubsys[ForEach_itr].Compare_a = false;

      /* SystemInitialize for Logic: '<S277>/OR1' */
      wturbines_B.CoreSubsys[ForEach_itr].OR1_g = false;

      /* SystemInitialize for Switch: '<S277>/Switch' */
      wturbines_B.CoreSubsys[ForEach_itr].Switch_f = 0.0;

      /* SystemInitialize for Saturate: '<S277>/Saturation' */
      wturbines_B.CoreSubsys[ForEach_itr].Saturation_g = 0.0;

      /* SystemInitialize for Gain: '<S14>/Friction' */
      wturbines_B.CoreSubsys[ForEach_itr].Friction = 0.0;

      /* SystemInitialize for Gain: '<S14>/Gain' */
      wturbines_B.CoreSubsys[ForEach_itr].Gain_m = 0.0;

      /* SystemInitialize for MinMax: '<S280>/Max' */
      wturbines_B.CoreSubsys[ForEach_itr].Max = 0.0;

      /* SystemInitialize for Math: '<S280>/  '
       *
       * About '<S280>/  ':
       *  Operator: reciprocal
       */
      wturbines_B.CoreSubsys[ForEach_itr].ut = 0.0;

      /* SystemInitialize for Math: '<S280>/Square' */
      wturbines_B.CoreSubsys[ForEach_itr].Square_o = 0.0;

      /* SystemInitialize for Math: '<S280>/Power' */
      wturbines_B.CoreSubsys[ForEach_itr].Power = 0.0;

      /* SystemInitialize for Product: '<S280>/Product' */
      wturbines_B.CoreSubsys[ForEach_itr].T_at = 0.0;

      /* SystemInitialize for Saturate: '<S280>/Saturation' */
      wturbines_B.CoreSubsys[ForEach_itr].Saturation_f = 0.0;

      /* SystemInitialize for Sum: '<S14>/Sum' */
      wturbines_B.CoreSubsys[ForEach_itr].Sum_g = 0.0;

      /* SystemInitialize for Gain: '<S14>/Multiply1' */
      wturbines_B.CoreSubsys[ForEach_itr]._dott = 0.0;

      /* SystemInitialize for Sum: '<S14>/Sum1' */
      wturbines_B.CoreSubsys[ForEach_itr].Sum1 = 0.0;

      /* SystemInitialize for BusCreator: '<S7>/Bus Creator' */
      wturbines_B.CoreSubsys[ForEach_itr].BusCreator = tmp_0;

      /* SystemInitialize for RandomNumber: '<S267>/White Noise' */
      wturbines_B.CoreSubsys[ForEach_itr].WhiteNoise = 0.0;

      /* SystemInitialize for Gain: '<S267>/Output' */
      wturbines_B.CoreSubsys[ForEach_itr].Output = 0.0;

      /* SystemInitialize for Sum: '<S12>/Sum1' */
      wturbines_B.CoreSubsys[ForEach_itr].Sum1_j = 0.0;

      /* SystemInitialize for RandomNumber: '<S270>/White Noise' */
      wturbines_B.CoreSubsys[ForEach_itr].WhiteNoise_a = 0.0;

      /* SystemInitialize for Gain: '<S270>/Output' */
      wturbines_B.CoreSubsys[ForEach_itr].Output_g = 0.0;

      /* SystemInitialize for Sum: '<S12>/Sum3' */
      wturbines_B.CoreSubsys[ForEach_itr].Sum3 = 0.0;

      /* SystemInitialize for RandomNumber: '<S268>/White Noise' */
      wturbines_B.CoreSubsys[ForEach_itr].WhiteNoise_p = 0.0;

      /* SystemInitialize for Gain: '<S268>/Output' */
      wturbines_B.CoreSubsys[ForEach_itr].Output_p = 0.0;

      /* SystemInitialize for Sum: '<S12>/Sum' */
      wturbines_B.CoreSubsys[ForEach_itr].Sum_i = 0.0;

      /* SystemInitialize for RandomNumber: '<S271>/White Noise' */
      wturbines_B.CoreSubsys[ForEach_itr].WhiteNoise_e = 0.0;

      /* SystemInitialize for Gain: '<S271>/Output' */
      wturbines_B.CoreSubsys[ForEach_itr].Output_h = 0.0;

      /* SystemInitialize for Sum: '<S12>/Sum4' */
      wturbines_B.CoreSubsys[ForEach_itr].Sum4 = 0.0;

      /* SystemInitialize for RandomNumber: '<S272>/White Noise' */
      wturbines_B.CoreSubsys[ForEach_itr].WhiteNoise_f = 0.0;

      /* SystemInitialize for Gain: '<S272>/Output' */
      wturbines_B.CoreSubsys[ForEach_itr].Output_m = 0.0;

      /* SystemInitialize for Sum: '<S12>/Sum5' */
      wturbines_B.CoreSubsys[ForEach_itr].Sum5 = 0.0;

      /* SystemInitialize for RandomNumber: '<S273>/White Noise' */
      wturbines_B.CoreSubsys[ForEach_itr].WhiteNoise_i = 0.0;

      /* SystemInitialize for Gain: '<S273>/Output' */
      wturbines_B.CoreSubsys[ForEach_itr].Output_k = 0.0;

      /* SystemInitialize for Sum: '<S12>/Sum6' */
      wturbines_B.CoreSubsys[ForEach_itr].Sum6 = 0.0;

      /* SystemInitialize for RandomNumber: '<S269>/White Noise' */
      wturbines_B.CoreSubsys[ForEach_itr].WhiteNoise_g = 0.0;

      /* SystemInitialize for Gain: '<S269>/Output' */
      wturbines_B.CoreSubsys[ForEach_itr].Output_l = 0.0;

      /* SystemInitialize for Sum: '<S12>/Sum2' */
      wturbines_B.CoreSubsys[ForEach_itr].Sum2 = 0.0;

      /* Start for InitialCondition: '<S2>/IC' */
      wturbines_DW.CoreSubsys[ForEach_itr].IC_FirstOutputTime = true;

      /* Start for InitialCondition: '<S2>/IC1' */
      wturbines_DW.CoreSubsys[ForEach_itr].IC1_FirstOutputTime = true;

      /* Start for InitialCondition: '<S2>/IC2' */
      wturbines_DW.CoreSubsys[ForEach_itr].IC2_FirstOutputTime = true;

      /* Start for InitialCondition: '<S2>/IC3' */
      wturbines_DW.CoreSubsys[ForEach_itr].IC3_FirstOutputTime = true;

      /* Start for InitialCondition: '<S2>/IC4' */
      wturbines_DW.CoreSubsys[ForEach_itr].IC4_FirstOutputTime = true;

      /* Start for InitialCondition: '<S2>/IC5' */
      wturbines_DW.CoreSubsys[ForEach_itr].IC5_FirstOutputTime = true;

      /* Start for InitialCondition: '<S2>/IC6' */
      wturbines_DW.CoreSubsys[ForEach_itr].IC6_FirstOutputTime = true;

      /* Start for RateTransition: '<S12>/Rate Transition13' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition13 =
        wturbines_cal->wturbines_CoreSubsys_cal.RateTransition13_InitialConditi;

      /* Start for RateTransition: '<S12>/Rate Transition2' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition2 =
        wturbines_cal->wturbines_CoreSubsys_cal.RateTransition2_InitialConditio;

      /* Start for RateTransition: '<S12>/Rate Transition3' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition3 =
        wturbines_cal->wturbines_CoreSubsys_cal.RateTransition3_InitialConditio;

      /* Start for Lookup_n-D: '<S14>/Ct(&#x3BB;, &#x3B2;)' */
      {
        rt_LUTnWork *TWork_start = (rt_LUTnWork *)
          &wturbines_DW.CoreSubsys[ForEach_itr].TWork[0];
        void **bpDataSet = static_cast<void **>
          (&wturbines_DW.CoreSubsys[ForEach_itr].m_bpDataSet[0]);
        TWork_start->m_dimSizes = static_cast<const uint32_T *>
          (wturbines_cal->wturbines_CoreSubsys_cal.Ct_dimSizes);
        TWork_start->m_tableData = (void *) get_Ct_mat();
        TWork_start->m_bpDataSet = bpDataSet;
        TWork_start->m_bpIndex = &wturbines_DW.CoreSubsys[ForEach_itr]
          .m_bpIndex[0];
        TWork_start->m_bpLambda = &wturbines_DW.CoreSubsys[ForEach_itr].
          m_bpLambda[0];
        TWork_start->m_maxIndex = static_cast<const uint32_T *>
          (wturbines_cal->wturbines_CoreSubsys_cal.Ct_maxIndex);
        bpDataSet[0] = (void *) get_tsr_vec();
        bpDataSet[1] = (void *) get_pitch_vec();
      }

      {
        const real_T **bpDataSet;
        const real_T *xp, *yp;
        real_T *dp;
        uint32_T len;
        const rt_LUTnWork *TWork_interp;
        rt_LUTSplineWork *rt_SplWk = (rt_LUTSplineWork*)
          &wturbines_DW.CoreSubsys[ForEach_itr].SWork[0];
        rt_SplWk->m_TWork = (rt_LUTnWork*)&wturbines_DW.CoreSubsys[ForEach_itr].
          TWork[0];
        rt_SplWk->m_yyA = &wturbines_DW.CoreSubsys[ForEach_itr].m_yyA[0];
        rt_SplWk->m_yyB = &wturbines_DW.CoreSubsys[ForEach_itr].m_yyB[0];
        rt_SplWk->m_yy2 = &wturbines_DW.CoreSubsys[ForEach_itr].m_yy2[0];
        rt_SplWk->m_up = &wturbines_DW.CoreSubsys[ForEach_itr].m_up[0];
        rt_SplWk->m_y2 = &wturbines_DW.CoreSubsys[ForEach_itr].m_y2[0];
        rt_SplWk->m_numYWorkElts =
          wturbines_cal->wturbines_CoreSubsys_cal.Ct_numYWorkElts;
        rt_SplWk->m_reCalc = &wturbines_DW.CoreSubsys[ForEach_itr].
          reCalcSecDerivFirstDimCoeffs;
        rt_SplWk->m_preBp0AndTable = &wturbines_DW.CoreSubsys[ForEach_itr].
          prevBp0AndTableData[0];
        *rt_SplWk->m_reCalc = 1;

        /* cache table data and first breakpoint data */
        TWork_interp = static_cast<const rt_LUTnWork *>(rt_SplWk->m_TWork);
        bpDataSet = (const real_T **) TWork_interp->m_bpDataSet;
        xp = bpDataSet[0U];
        len = TWork_interp->m_maxIndex[0U] + 1U;
        dp = (real_T *) rt_SplWk->m_preBp0AndTable;
        yp = (real_T *) TWork_interp->m_tableData;
        (void) std::memcpy(dp, xp,
                           len * sizeof(real_T));
        dp = &(dp[len]);

        /* save the table data */
        (void) std::memcpy(dp, yp,
                           len * rt_SplWk->m_numYWorkElts[0U] * sizeof(real_T));
      }

      /* Start for RateTransition: '<S12>/Rate Transition4' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition4 =
        wturbines_cal->wturbines_CoreSubsys_cal.RateTransition4_InitialConditio;

      /* Start for RateTransition: '<S12>/Rate Transition9' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition9_o =
        wturbines_cal->wturbines_CoreSubsys_cal.RateTransition9_InitialConditio;

      /* Start for RateTransition: '<S12>/Rate Transition10' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition10 =
        wturbines_cal->wturbines_CoreSubsys_cal.RateTransition10_InitialConditi;

      /* Start for RateTransition: '<S12>/Rate Transition11' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition11 =
        wturbines_cal->wturbines_CoreSubsys_cal.RateTransition11_InitialConditi;

      /* Start for RateTransition: '<S12>/Rate Transition12' */
      wturbines_B.CoreSubsys[ForEach_itr].RateTransition12 =
        wturbines_cal->wturbines_CoreSubsys_cal.RateTransition12_InitialConditi;

      /* InitializeConditions for Integrator: '<S14>/Integrator' */
      wturbines_X.CoreSubsys[ForEach_itr].Integrator_CSTATE =
        wturbines_cal->wturbines_CoreSubsys_cal.Integrator_IC;

      /* InitializeConditions for RateLimiter: '<S2>/Rate Limiter' */
      wturbines_DW.CoreSubsys[ForEach_itr].PrevY =
        wturbines_cal->wturbines_CoreSubsys_cal.RateLimiter_IC;

      /* InitializeConditions for RateLimiter: '<S2>/Rate Limiter1' */
      wturbines_DW.CoreSubsys[ForEach_itr].PrevY_e =
        wturbines_cal->wturbines_CoreSubsys_cal.RateLimiter1_IC;

      /* InitializeConditions for RateLimiter: '<S278>/Rate Limiter' */
      wturbines_DW.CoreSubsys[ForEach_itr].PrevY_n =
        wturbines_cal->wturbines_CoreSubsys_cal.RateLimiter_IC_e;

      /* InitializeConditions for RateTransition: '<S12>/Rate Transition13' */
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition13_Buf[0] =
        wturbines_cal->wturbines_CoreSubsys_cal.RateTransition13_InitialConditi;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition13_WrBufIdx = 0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition13_RdBufIdx = 1;

      /* InitializeConditions for RateTransition: '<S12>/Rate Transition2' */
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition2_Buf[0] =
        wturbines_cal->wturbines_CoreSubsys_cal.RateTransition2_InitialConditio;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition2_WrBufIdx = 0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition2_RdBufIdx = 1;

      /* InitializeConditions for RateTransition: '<S12>/Rate Transition3' */
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition3_Buf[0] =
        wturbines_cal->wturbines_CoreSubsys_cal.RateTransition3_InitialConditio;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition3_WrBufIdx = 0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition3_RdBufIdx = 1;

      /* InitializeConditions for Integrator: '<S247>/Integrator' */
      wturbines_X.CoreSubsys[ForEach_itr].Integrator_CSTATE_o =
        wturbines_cal->wturbines_CoreSubsys_cal.PIcontroller_InitialConditionFo;

      /* InitializeConditions for Integrator: '<S194>/Integrator' */
      wturbines_X.CoreSubsys[ForEach_itr].Integrator_CSTATE_l =
        wturbines_cal->wturbines_CoreSubsys_cal.PIcontroller_InitialCondition_i;

      /* InitializeConditions for Integrator: '<S132>/Integrator' */
      wturbines_X.CoreSubsys[ForEach_itr].Integrator_CSTATE_e =
        wturbines_cal->wturbines_CoreSubsys_cal.PIcontroller_InitialCondition_g;

      /* InitializeConditions for Delay: '<S27>/Delay' */
      wturbines_DW.CoreSubsys[ForEach_itr].Delay_DSTATE =
        wturbines_cal->wturbines_CoreSubsys_cal.Delay_InitialCondition;

      /* InitializeConditions for Integrator: '<S78>/Integrator' */
      wturbines_X.CoreSubsys[ForEach_itr].Integrator_CSTATE_oj =
        wturbines_cal->wturbines_CoreSubsys_cal.PIController_InitialConditionFo;

      /* InitializeConditions for RateLimiter: '<S276>/Rate Limiter' */
      wturbines_DW.CoreSubsys[ForEach_itr].LastMajorTime = (rtInf);

      /* InitializeConditions for RateTransition: '<S12>/Rate Transition5' */
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition5_Buf[0] =
        wturbines_cal->wturbines_CoreSubsys_cal.RateTransition5_InitialConditio;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition5_WrBufIdx = 0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition5_RdBufIdx = 1;

      /* InitializeConditions for RateTransition: '<S12>/Rate Transition1' */
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition1_Buf[0] =
        wturbines_cal->wturbines_CoreSubsys_cal.RateTransition1_InitialConditio;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition1_WrBufIdx = 0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition1_RdBufIdx = 1;

      /* InitializeConditions for RateTransition: '<S12>/Rate Transition4' */
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition4_Buf[0] =
        wturbines_cal->wturbines_CoreSubsys_cal.RateTransition4_InitialConditio;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition4_WrBufIdx = 0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition4_RdBufIdx = 1;

      /* InitializeConditions for RateTransition: '<S2>/Rate Transition7' */
      for (i = 0; i < 8; i++) {
        wturbines_DW.CoreSubsys[ForEach_itr].RateTransition7_Buf[i] =
          wturbines_cal->wturbines_CoreSubsys_cal.RateTransition7_InitialConditio;
      }

      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition7_WrBufIdx = 0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition7_RdBufIdx = 1;

      /* End of InitializeConditions for RateTransition: '<S2>/Rate Transition7' */

      /* InitializeConditions for StateSpace: '<S34>/H&#x221E; controller ' */
      wturbines_X.CoreSubsys[ForEach_itr].Hcontroller_CSTATE =
        wturbines_cal->wturbines_CoreSubsys_cal.Hcontroller_InitialCondition;

      /* InitializeConditions for RateTransition: '<S12>/Rate Transition7' */
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition7_Buf_h[0] =
        wturbines_cal->wturbines_CoreSubsys_cal.RateTransition7_InitialCondit_j;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition7_WrBufIdx_e = 0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition7_RdBufIdx_g = 1;

      /* InitializeConditions for RateTransition: '<S12>/Rate Transition9' */
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition9_Buf[0] =
        wturbines_cal->wturbines_CoreSubsys_cal.RateTransition9_InitialConditio;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition9_WrBufIdx = 0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition9_RdBufIdx = 1;

      /* InitializeConditions for RateTransition: '<S12>/Rate Transition8' */
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition8_Buf[0] =
        wturbines_cal->wturbines_CoreSubsys_cal.RateTransition8_InitialConditio;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition8_WrBufIdx = 0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition8_RdBufIdx = 1;

      /* InitializeConditions for RateTransition: '<S12>/Rate Transition10' */
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition10_Buf[0] =
        wturbines_cal->wturbines_CoreSubsys_cal.RateTransition10_InitialConditi;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition10_WrBufIdx = 0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition10_RdBufIdx = 1;

      /* InitializeConditions for RateTransition: '<S12>/Rate Transition11' */
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition11_Buf[0] =
        wturbines_cal->wturbines_CoreSubsys_cal.RateTransition11_InitialConditi;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition11_WrBufIdx = 0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition11_RdBufIdx = 1;

      /* InitializeConditions for RateTransition: '<S12>/Rate Transition12' */
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition12_Buf[0] =
        wturbines_cal->wturbines_CoreSubsys_cal.RateTransition12_InitialConditi;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition12_WrBufIdx = 0;
      wturbines_DW.CoreSubsys[ForEach_itr].RateTransition12_RdBufIdx = 1;

      /* InitializeConditions for RandomNumber: '<S267>/White Noise' */
      tmp = std::floor
        (wturbines_cal->wturbines_CoreSubsys_cal.BandLimitedWhiteNoise_seed);
      if (rtIsNaN(tmp) || rtIsInf(tmp)) {
        tmp = 0.0;
      } else {
        tmp = std::fmod(tmp, 4.294967296E+9);
      }

      tseed = tmp < 0.0 ? static_cast<uint32_T>(-static_cast<int32_T>(
        static_cast<uint32_T>(-tmp))) : static_cast<uint32_T>(tmp);
      i = static_cast<int32_T>(tseed >> 16U);
      t = static_cast<int32_T>(tseed & 32768U);
      tseed = ((((tseed - (static_cast<uint32_T>(i) << 16U)) +
                 static_cast<uint32_T>(t)) << 16U) + static_cast<uint32_T>(t)) +
        static_cast<uint32_T>(i);
      if (tseed < 1U) {
        tseed = 1144108930U;
      } else if (tseed > 2147483646U) {
        tseed = 2147483646U;
      }

      wturbines_DW.CoreSubsys[ForEach_itr].RandSeed = tseed;
      wturbines_DW.CoreSubsys[ForEach_itr].NextOutput =
        rt_nrand_Upu32_Yd_f_pw_snf(&wturbines_DW.CoreSubsys[ForEach_itr].
        RandSeed) * wturbines_cal->wturbines_CoreSubsys_cal.WhiteNoise_StdDev +
        wturbines_cal->wturbines_CoreSubsys_cal.WhiteNoise_Mean;

      /* End of InitializeConditions for RandomNumber: '<S267>/White Noise' */

      /* InitializeConditions for RandomNumber: '<S270>/White Noise' */
      tmp = std::floor
        (wturbines_cal->wturbines_CoreSubsys_cal.BandLimitedWhiteNoise3_seed);
      if (rtIsNaN(tmp) || rtIsInf(tmp)) {
        tmp = 0.0;
      } else {
        tmp = std::fmod(tmp, 4.294967296E+9);
      }

      tseed = tmp < 0.0 ? static_cast<uint32_T>(-static_cast<int32_T>(
        static_cast<uint32_T>(-tmp))) : static_cast<uint32_T>(tmp);
      i = static_cast<int32_T>(tseed >> 16U);
      t = static_cast<int32_T>(tseed & 32768U);
      tseed = ((((tseed - (static_cast<uint32_T>(i) << 16U)) +
                 static_cast<uint32_T>(t)) << 16U) + static_cast<uint32_T>(t)) +
        static_cast<uint32_T>(i);
      if (tseed < 1U) {
        tseed = 1144108930U;
      } else if (tseed > 2147483646U) {
        tseed = 2147483646U;
      }

      wturbines_DW.CoreSubsys[ForEach_itr].RandSeed_m = tseed;
      wturbines_DW.CoreSubsys[ForEach_itr].NextOutput_i =
        rt_nrand_Upu32_Yd_f_pw_snf(&wturbines_DW.CoreSubsys[ForEach_itr].
        RandSeed_m) *
        wturbines_cal->wturbines_CoreSubsys_cal.WhiteNoise_StdDev_k +
        wturbines_cal->wturbines_CoreSubsys_cal.WhiteNoise_Mean_p;

      /* End of InitializeConditions for RandomNumber: '<S270>/White Noise' */

      /* InitializeConditions for RandomNumber: '<S268>/White Noise' */
      tmp = std::floor
        (wturbines_cal->wturbines_CoreSubsys_cal.BandLimitedWhiteNoise1_seed);
      if (rtIsNaN(tmp) || rtIsInf(tmp)) {
        tmp = 0.0;
      } else {
        tmp = std::fmod(tmp, 4.294967296E+9);
      }

      tseed = tmp < 0.0 ? static_cast<uint32_T>(-static_cast<int32_T>(
        static_cast<uint32_T>(-tmp))) : static_cast<uint32_T>(tmp);
      i = static_cast<int32_T>(tseed >> 16U);
      t = static_cast<int32_T>(tseed & 32768U);
      tseed = ((((tseed - (static_cast<uint32_T>(i) << 16U)) +
                 static_cast<uint32_T>(t)) << 16U) + static_cast<uint32_T>(t)) +
        static_cast<uint32_T>(i);
      if (tseed < 1U) {
        tseed = 1144108930U;
      } else if (tseed > 2147483646U) {
        tseed = 2147483646U;
      }

      wturbines_DW.CoreSubsys[ForEach_itr].RandSeed_j = tseed;
      wturbines_DW.CoreSubsys[ForEach_itr].NextOutput_a =
        rt_nrand_Upu32_Yd_f_pw_snf(&wturbines_DW.CoreSubsys[ForEach_itr].
        RandSeed_j) *
        wturbines_cal->wturbines_CoreSubsys_cal.WhiteNoise_StdDev_a +
        wturbines_cal->wturbines_CoreSubsys_cal.WhiteNoise_Mean_h;

      /* End of InitializeConditions for RandomNumber: '<S268>/White Noise' */

      /* InitializeConditions for RandomNumber: '<S271>/White Noise' */
      tmp = std::floor
        (wturbines_cal->wturbines_CoreSubsys_cal.BandLimitedWhiteNoise4_seed);
      if (rtIsNaN(tmp) || rtIsInf(tmp)) {
        tmp = 0.0;
      } else {
        tmp = std::fmod(tmp, 4.294967296E+9);
      }

      tseed = tmp < 0.0 ? static_cast<uint32_T>(-static_cast<int32_T>(
        static_cast<uint32_T>(-tmp))) : static_cast<uint32_T>(tmp);
      i = static_cast<int32_T>(tseed >> 16U);
      t = static_cast<int32_T>(tseed & 32768U);
      tseed = ((((tseed - (static_cast<uint32_T>(i) << 16U)) +
                 static_cast<uint32_T>(t)) << 16U) + static_cast<uint32_T>(t)) +
        static_cast<uint32_T>(i);
      if (tseed < 1U) {
        tseed = 1144108930U;
      } else if (tseed > 2147483646U) {
        tseed = 2147483646U;
      }

      wturbines_DW.CoreSubsys[ForEach_itr].RandSeed_l = tseed;
      wturbines_DW.CoreSubsys[ForEach_itr].NextOutput_f =
        rt_nrand_Upu32_Yd_f_pw_snf(&wturbines_DW.CoreSubsys[ForEach_itr].
        RandSeed_l) *
        wturbines_cal->wturbines_CoreSubsys_cal.WhiteNoise_StdDev_d +
        wturbines_cal->wturbines_CoreSubsys_cal.WhiteNoise_Mean_hm;

      /* End of InitializeConditions for RandomNumber: '<S271>/White Noise' */

      /* InitializeConditions for RandomNumber: '<S272>/White Noise' */
      tmp = std::floor
        (wturbines_cal->wturbines_CoreSubsys_cal.BandLimitedWhiteNoise5_seed);
      if (rtIsNaN(tmp) || rtIsInf(tmp)) {
        tmp = 0.0;
      } else {
        tmp = std::fmod(tmp, 4.294967296E+9);
      }

      tseed = tmp < 0.0 ? static_cast<uint32_T>(-static_cast<int32_T>(
        static_cast<uint32_T>(-tmp))) : static_cast<uint32_T>(tmp);
      i = static_cast<int32_T>(tseed >> 16U);
      t = static_cast<int32_T>(tseed & 32768U);
      tseed = ((((tseed - (static_cast<uint32_T>(i) << 16U)) +
                 static_cast<uint32_T>(t)) << 16U) + static_cast<uint32_T>(t)) +
        static_cast<uint32_T>(i);
      if (tseed < 1U) {
        tseed = 1144108930U;
      } else if (tseed > 2147483646U) {
        tseed = 2147483646U;
      }

      wturbines_DW.CoreSubsys[ForEach_itr].RandSeed_a = tseed;
      wturbines_DW.CoreSubsys[ForEach_itr].NextOutput_m =
        rt_nrand_Upu32_Yd_f_pw_snf(&wturbines_DW.CoreSubsys[ForEach_itr].
        RandSeed_a) *
        wturbines_cal->wturbines_CoreSubsys_cal.WhiteNoise_StdDev_n +
        wturbines_cal->wturbines_CoreSubsys_cal.WhiteNoise_Mean_pi;

      /* End of InitializeConditions for RandomNumber: '<S272>/White Noise' */

      /* InitializeConditions for RandomNumber: '<S273>/White Noise' */
      tmp = std::floor
        (wturbines_cal->wturbines_CoreSubsys_cal.BandLimitedWhiteNoise6_seed);
      if (rtIsNaN(tmp) || rtIsInf(tmp)) {
        tmp = 0.0;
      } else {
        tmp = std::fmod(tmp, 4.294967296E+9);
      }

      tseed = tmp < 0.0 ? static_cast<uint32_T>(-static_cast<int32_T>(
        static_cast<uint32_T>(-tmp))) : static_cast<uint32_T>(tmp);
      i = static_cast<int32_T>(tseed >> 16U);
      t = static_cast<int32_T>(tseed & 32768U);
      tseed = ((((tseed - (static_cast<uint32_T>(i) << 16U)) +
                 static_cast<uint32_T>(t)) << 16U) + static_cast<uint32_T>(t)) +
        static_cast<uint32_T>(i);
      if (tseed < 1U) {
        tseed = 1144108930U;
      } else if (tseed > 2147483646U) {
        tseed = 2147483646U;
      }

      wturbines_DW.CoreSubsys[ForEach_itr].RandSeed_g = tseed;
      wturbines_DW.CoreSubsys[ForEach_itr].NextOutput_n =
        rt_nrand_Upu32_Yd_f_pw_snf(&wturbines_DW.CoreSubsys[ForEach_itr].
        RandSeed_g) *
        wturbines_cal->wturbines_CoreSubsys_cal.WhiteNoise_StdDev_e +
        wturbines_cal->wturbines_CoreSubsys_cal.WhiteNoise_Mean_d;

      /* End of InitializeConditions for RandomNumber: '<S273>/White Noise' */

      /* InitializeConditions for RandomNumber: '<S269>/White Noise' */
      tmp = std::floor
        (wturbines_cal->wturbines_CoreSubsys_cal.BandLimitedWhiteNoise2_seed);
      if (rtIsNaN(tmp) || rtIsInf(tmp)) {
        tmp = 0.0;
      } else {
        tmp = std::fmod(tmp, 4.294967296E+9);
      }

      tseed = tmp < 0.0 ? static_cast<uint32_T>(-static_cast<int32_T>(
        static_cast<uint32_T>(-tmp))) : static_cast<uint32_T>(tmp);
      i = static_cast<int32_T>(tseed >> 16U);
      t = static_cast<int32_T>(tseed & 32768U);
      tseed = ((((tseed - (static_cast<uint32_T>(i) << 16U)) +
                 static_cast<uint32_T>(t)) << 16U) + static_cast<uint32_T>(t)) +
        static_cast<uint32_T>(i);
      if (tseed < 1U) {
        tseed = 1144108930U;
      } else if (tseed > 2147483646U) {
        tseed = 2147483646U;
      }

      wturbines_DW.CoreSubsys[ForEach_itr].RandSeed_b = tseed;
      wturbines_DW.CoreSubsys[ForEach_itr].NextOutput_b =
        rt_nrand_Upu32_Yd_f_pw_snf(&wturbines_DW.CoreSubsys[ForEach_itr].
        RandSeed_b) *
        wturbines_cal->wturbines_CoreSubsys_cal.WhiteNoise_StdDev_f +
        wturbines_cal->wturbines_CoreSubsys_cal.WhiteNoise_Mean_g;

      /* End of InitializeConditions for RandomNumber: '<S269>/White Noise' */

      /* SystemInitialize for Chart: '<S11>/Wind Turbine State Machine' */
      wturbines_DW.CoreSubsys[ForEach_itr].sfEvent_g = wturbines_CALL_EVENT;
      wturbines_DW.CoreSubsys[ForEach_itr].is_active_c9_wturbines = 0U;
      wturbines_B.CoreSubsys[ForEach_itr].op_mode_m = op_mode_None;

      /* SystemInitialize for MATLAB Function: '<S11>/MATLAB Function' */
      wturbines_B.CoreSubsys[ForEach_itr].y = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].last_val_not_empty = false;
      wturbines_DW.CoreSubsys[ForEach_itr].doneDoubleBufferReInit = false;
      wturbines_DW.CoreSubsys[ForEach_itr].sfEvent = wturbines_CALL_EVENT;

      /* SystemInitialize for MATLAB Function: '<S14>/True Yaw Offset' */
      wturbines_B.CoreSubsys[ForEach_itr].yaw = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].doneDoubleBufferReInit_b = false;
      wturbines_DW.CoreSubsys[ForEach_itr].sfEvent_e = wturbines_CALL_EVENT;

      /* SystemInitialize for Lookup_n-D: '<S27>/&#x3C9;_ss(u)' */
      wturbines_B.CoreSubsys[ForEach_itr]._sst = 0.0;

      /* SystemInitialize for Gain: '<S31>/Multiply' */
      wturbines_B.CoreSubsys[ForEach_itr].Multiply_g = 0.0;

      /* SystemInitialize for Gain: '<S31>/Multiply1' */
      wturbines_B.CoreSubsys[ForEach_itr].Multiply1_j = 0.0;

      /* SystemInitialize for Gain: '<S32>/Multiply' */
      wturbines_B.CoreSubsys[ForEach_itr].Multiply_l = 0.0;

      /* SystemInitialize for Gain: '<S32>/Multiply1' */
      wturbines_B.CoreSubsys[ForEach_itr].Multiply1_p = 0.0;

      /* SystemInitialize for Product: '<S27>/Divide4' */
      wturbines_B.CoreSubsys[ForEach_itr]._rreft_l = 0.0;

      /* SystemInitialize for Gain: '<S152>/Multiply' */
      wturbines_B.CoreSubsys[ForEach_itr].Multiply_p = 0.0;

      /* SystemInitialize for Gain: '<S152>/Multiply1' */
      wturbines_B.CoreSubsys[ForEach_itr].Multiply1_e = 0.0;

      /* SystemInitialize for Sum: '<S150>/Sum' */
      wturbines_B.CoreSubsys[ForEach_itr].Sum_d = 0.0;

      /* SystemInitialize for Product: '<S150>/Product1' */
      wturbines_B.CoreSubsys[ForEach_itr].Product1_n = 0.0;

      /* SystemInitialize for Math: '<S150>/Exp'
       *
       * About '<S150>/Exp':
       *  Operator: exp
       */
      wturbines_B.CoreSubsys[ForEach_itr].Exp = 0.0;

      /* SystemInitialize for Lookup_n-D: '<S150>/&#x3B2;(ws)' */
      wturbines_B.CoreSubsys[ForEach_itr].ws = 0.0;

      /* SystemInitialize for Gain: '<S154>/Gain1' */
      wturbines_B.CoreSubsys[ForEach_itr].Gain1_o = 0.0;

      /* SystemInitialize for Product: '<S150>/Product' */
      wturbines_B.CoreSubsys[ForEach_itr].Product_n = 0.0;

      /* SystemInitialize for Math: '<S151>/Square' */
      wturbines_B.CoreSubsys[ForEach_itr].Square_b = 0.0;

      /* SystemInitialize for Product: '<S151>/Product' */
      wturbines_B.CoreSubsys[ForEach_itr].Product_b = 0.0;

      /* SystemInitialize for Product: '<S29>/Divide3' */
      wturbines_B.CoreSubsys[ForEach_itr].Divide3 = 0.0;

      /* SystemInitialize for MultiPortSwitch: '<S29>/Multiport Switch' */
      wturbines_B.CoreSubsys[ForEach_itr]._drt = 0.0;

      /* SystemInitialize for Gain: '<S155>/Multiply' */
      wturbines_B.CoreSubsys[ForEach_itr].Multiply_d = 0.0;

      /* SystemInitialize for Gain: '<S155>/Multiply1' */
      wturbines_B.CoreSubsys[ForEach_itr].Multiply1_g = 0.0;

      /* SystemInitialize for Product: '<S29>/Divide2' */
      wturbines_B.CoreSubsys[ForEach_itr]._drt_n = 0.0;

      /* SystemInitialize for Product: '<S29>/Divide4' */
      wturbines_B.CoreSubsys[ForEach_itr]._drt_o = 0.0;

      /* SystemInitialize for Switch: '<S157>/Derating' */
      wturbines_B.CoreSubsys[ForEach_itr].Derating = 0.0;

      /* SystemInitialize for Switch: '<S156>/Derating' */
      wturbines_B.CoreSubsys[ForEach_itr].Derating_e = 0.0;

      /* SystemInitialize for Saturate: '<S29>/Saturation' */
      wturbines_B.CoreSubsys[ForEach_itr].Saturation_k = 0.0;

      /* SystemInitialize for Sum: '<S256>/Sum' */
      wturbines_B.CoreSubsys[ForEach_itr].Sum_b = 0.0;

      /* SystemInitialize for Sum: '<S203>/Sum' */
      wturbines_B.CoreSubsys[ForEach_itr].Sum_n = 0.0;

      /* SystemInitialize for Sum: '<S141>/Sum' */
      wturbines_B.CoreSubsys[ForEach_itr].Sum_a = 0.0;

      /* SystemInitialize for RelationalOperator: '<S17>/Compare' */
      wturbines_B.CoreSubsys[ForEach_itr].Compare_i = false;

      /* SystemInitialize for Switch: '<S11>/Switch' */
      wturbines_B.CoreSubsys[ForEach_itr].Switch_a = 0.0;

      /* SystemInitialize for Math: '<S13>/Power' */
      wturbines_B.CoreSubsys[ForEach_itr].ws_drt_h = 0.0;

      /* SystemInitialize for Math: '<S13>/Square' */
      wturbines_B.CoreSubsys[ForEach_itr].Square_oq = 0.0;

      /* SystemInitialize for Product: '<S13>/Product1' */
      wturbines_B.CoreSubsys[ForEach_itr].Product1_a = 0.0;

      /* SystemInitialize for MinMax: '<S13>/Min' */
      wturbines_B.CoreSubsys[ForEach_itr].Min = 0.0;

      /* SystemInitialize for Lookup_n-D: '<S277>/Cp(&#x3BB;, &#x3B2;) ' */
      wturbines_B.CoreSubsys[ForEach_itr].Cpt = 0.0;

      /* SystemInitialize for MATLABSystem: '<S11>/Moving Average' */
      wturbines_B.CoreSubsys[ForEach_itr].MovingAverage = 0.0;

      /* Start for MATLABSystem: '<S11>/Moving Average' */
      wturbines_DW.CoreSubsys[ForEach_itr].obj.isInitialized = 0;
      wturbines_DW.CoreSubsys[ForEach_itr].obj.NumChannels = -1;
      wturbines_DW.CoreSubsys[ForEach_itr].obj.FrameLength = -1;
      wturbines_DW.CoreSubsys[ForEach_itr].obj.matlabCodegenIsDeleted = false;
      wturbines_DW.CoreSubsys[ForEach_itr].objisempty = true;
      flag = (wturbines_DW.CoreSubsys[ForEach_itr].obj.isInitialized == 1);
      if (flag) {
        wturbines_DW.CoreSubsys[ForEach_itr].obj.TunablePropsChanged = true;
      }

      wturbines_DW.CoreSubsys[ForEach_itr].obj.ForgettingFactor =
        wturbines_cal->wturbines_CoreSubsys_cal.MovingAverage_ForgettingFactor;
      wturbines_SystemCore_setup(&wturbines_DW.CoreSubsys[ForEach_itr].obj);

      /* InitializeConditions for MATLABSystem: '<S11>/Moving Average' */
      wturbines_DW.CoreSubsys[ForEach_itr].obj.pwN = 0.0;
      wturbines_DW.CoreSubsys[ForEach_itr].obj.pmN = 0.0;
      ForEach_itr++;
    }

    /* End of SystemInitialize for SubSystem: '<Root>/For Each Subsystem' */

    /* SystemInitialize for MATLAB Function: '<Root>/MATLAB Function' */
    wturbines_DW.doneDoubleBufferReInit_o = false;
    wturbines_DW.sfEvent_j = wturbines_CALL_EVENT;

    /* SystemInitialize for Enabled SubSystem: '<S4>/Enabled Subsystem' */
    /* SystemInitialize for MATLAB Function: '<S288>/ZoH nan filter1' */
    wturbines_DW.doneDoubleBufferReInit_e = false;
    wturbines_DW.sfEvent_n = wturbines_CALL_EVENT;

    /* SystemInitialize for MATLAB Function: '<S288>/ZoH nan filter2' */
    wturbines_DW.doneDoubleBufferReInit = false;
    wturbines_DW.sfEvent = wturbines_CALL_EVENT;

    /* SystemInitialize for Enabled SubSystem: '<S5>/Enabled Subsystem' */
    for (i = 0; i < 9; i++) {
      /* InitializeConditions for UnitDelay: '<S288>/Unit Delay' */
      wturbines_DW.UnitDelay_DSTATE[i] =
        wturbines_cal->UnitDelay_InitialCondition[i];

      /* InitializeConditions for UnitDelay: '<S288>/Unit Delay1' */
      wturbines_DW.UnitDelay1_DSTATE[i] =
        wturbines_cal->UnitDelay1_InitialCondition[i];

      /* SystemInitialize for Outport: '<S288>/WindSpeed' */
      wturbines_B.w_filtered_k[i] = wturbines_cal->WindSpeed_Y0;

      /* SystemInitialize for Outport: '<S288>/Wind Direction' */
      wturbines_B.w_filtered[i] = wturbines_cal->WindDirection_Y0;

      /* SystemInitialize for ZeroOrderHold: '<S292>/Zero-Order Hold' incorporates:
       *  Outport: '<S292>/bEnable'
       */
      wturbines_B.ZeroOrderHold[i] = wturbines_cal->bEnable_Y0;

      /* SystemInitialize for ZeroOrderHold: '<S292>/Zero-Order Hold1' incorporates:
       *  Outport: '<S292>/bStop'
       */
      wturbines_B.ZeroOrderHold1[i] = wturbines_cal->bStop_Y0;

      /* SystemInitialize for ZeroOrderHold: '<S292>/Zero-Order Hold2' incorporates:
       *  Outport: '<S292>/eCTRL_MODE'
       */
      wturbines_B.ZeroOrderHold2[i] = wturbines_cal->eCTRL_MODE_Y0;

      /* SystemInitialize for ZeroOrderHold: '<S292>/Zero-Order Hold3' incorporates:
       *  Outport: '<S292>/fPowerSpt'
       */
      wturbines_B.ZeroOrderHold3[i] = wturbines_cal->fPowerSpt_Y0;

      /* SystemInitialize for ZeroOrderHold: '<S292>/Zero-Order Hold4' incorporates:
       *  Outport: '<S292>/fYawSpt'
       */
      wturbines_B.ZeroOrderHold4[i] = wturbines_cal->fYawSpt_Y0;
    }

    /* End of SystemInitialize for SubSystem: '<S5>/Enabled Subsystem' */
    /* End of SystemInitialize for SubSystem: '<S4>/Enabled Subsystem' */
  }
}

/* Model terminate function */
void wturbines_terminate(void)
{
  /* local scratch DWork variables */
  int32_T ForEach_itr;
  real_T tmp;
  real_T tmp_0;

  /* Terminate for S-Function (slrealtimeUDPSend): '<S6>/UDP Send1' incorporates:
   *  Constant: '<S6>/Constant1'
   */
  tmp_0 = *get_Nt();

  /* Terminate for Iterator SubSystem: '<Root>/For Each Subsystem' */
  for (ForEach_itr = 0; ForEach_itr < 9; ForEach_itr++) {
    /* Terminate for MATLABSystem: '<S11>/Moving Average' */
    if (!wturbines_DW.CoreSubsys[ForEach_itr].obj.matlabCodegenIsDeleted) {
      wturbines_DW.CoreSubsys[ForEach_itr].obj.matlabCodegenIsDeleted = true;
      if ((wturbines_DW.CoreSubsys[ForEach_itr].obj.isInitialized == 1) &&
          wturbines_DW.CoreSubsys[ForEach_itr].obj.isSetupComplete) {
        wturbines_DW.CoreSubsys[ForEach_itr].obj.NumChannels = -1;
        wturbines_DW.CoreSubsys[ForEach_itr].obj.FrameLength = -1;
      }
    }

    /* End of Terminate for MATLABSystem: '<S11>/Moving Average' */
  }

  /* End of Terminate for SubSystem: '<Root>/For Each Subsystem' */
  /* Terminate for S-Function (slrealtimeUDPReceive): '<S4>/UDP Receive' */
  {
    slrealtime::ip::SocketFactory::releaseSocket("172.19.3.43",49152U);
    char *buffer = (char *)wturbines_DW.UDPReceive_PWORK[1];
    if (buffer)
      free(buffer);
  }

  /* Terminate for S-Function (slrealtimeUDPReceive): '<S5>/UDP Receive' */
  {
    slrealtime::ip::SocketFactory::releaseSocket("172.19.3.43",10000U);
    char *buffer = (char *)wturbines_DW.UDPReceive_PWORK_k[1];
    if (buffer)
      free(buffer);
  }

  /* Terminate for S-Function (slrealtimeUDPSend): '<S6>/UDP Send1' incorporates:
   *  Constant: '<S6>/Constant1'
   */
  tmp = tmp_0 * *get_turbineDataBytes();

  {
    slrealtime::ip::SocketFactory::releaseSocket("172.19.3.43",11000U);
  }

  /* Terminate for S-Function (slrealtimeUDPSend): '<S1>/UDP Send1' incorporates:
   *  Constant: '<S1>/Constant1'
   */
  tmp = tmp_0 * 2.0 * 4.0;

  {
    slrealtime::ip::SocketFactory::releaseSocket("172.19.3.43",49160U);
  }
}
