/*
 *  rtmodel.cpp:
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "wturbines".
 *
 * Model version              : 1.241
 * Simulink Coder version : 24.2 (R2024b) 21-Jun-2024
 * C++ source code generated on : Thu Jun 11 13:02:08 2026
 *
 * Target selection: speedgoat.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "rtmodel.h"

/* Use this function only if you need to maintain compatibility with an existing static main program. */
void wturbines_step(int_T tid)
{
  switch (tid) {
   case 0 :
    wturbines_step0();
    break;

   case 1 :
    wturbines_step2();
    break;

   case 2 :
    wturbines_step3();
    break;

   case 3 :
    wturbines_step4();
    break;

   default :
    /* do nothing */
    break;
  }
}
