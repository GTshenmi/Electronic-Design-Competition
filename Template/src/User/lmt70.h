#ifndef _LMT70_H_
#define _LMT70_H_
#include "usr_common.h"

#define lmt70_limit_t float_limit_t

typedef struct
{
   adc_t *ADC;
   lmt70_limit_t TempLimit;
   uint32_t (*GetADCValue)();
   float (*BinarySearch)(float * ,unsigned int,float);
   int (*SearchTest)();
}lmt70_t;

extern lmt70_t LMT70;

void LMT70DefaultInit();

float LMT70GetTemperature();

void LMT70Test();

#endif