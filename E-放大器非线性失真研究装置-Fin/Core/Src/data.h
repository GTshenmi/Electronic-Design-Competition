#ifndef _DATA_H
#define _DATA_H
#include "arm_math.h"
#include  <stm32f4xx_hal.h>
#define SAMPLE_N    64
#define SAMPLE_FS   3200
#define FFT_DPI     (SAMPLE_FS / SAMPLE_N);

extern float32_t data2handle[SAMPLE_N * 2];
extern float32_t FFT_Output[SAMPLE_N];

extern float32_t xiebo[SAMPLE_N];
extern float32_t phaseA[SAMPLE_N];
extern float32_t phaseB[SAMPLE_N];
extern float32_t phaseC[SAMPLE_N];

#endif
