#ifndef _ARM_SUB_H
#define _ARM_SUB_H

#include "arm_math.h"

void arm_sub_q7(
  const q7_t * pSrcA,
  const q7_t * pSrcB,
  q7_t * pDst,
  uint32_t blockSize);
void arm_sub_q15(
  const q15_t * pSrcA,
  const q15_t * pSrcB,
  q15_t * pDst,
  uint32_t blockSize);
void arm_sub_q31(
  const q31_t * pSrcA,
  const q31_t * pSrcB,
  q31_t * pDst,
  uint32_t blockSize);
void arm_sub_f32(
  const float32_t * pSrcA,
  const float32_t * pSrcB,
  float32_t * pDst,
  uint32_t blockSize);

#endif
