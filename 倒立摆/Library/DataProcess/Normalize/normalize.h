#ifndef _NORMALIZE_H_
#define _NORMALIZE_H_

#define NORMALIZE_EPS 1e-6 /*¾«¶È*/

typedef struct
{
	 float MaxValue;
	 float MinValue;
}normalize_range_t;

float Normalize(normalize_range_t Range,float Value);

void NormalizeArray(normalize_range_t Range,float *Value,int len);

normalize_range_t Range(float MinValue,float MaxValue);

#endif

