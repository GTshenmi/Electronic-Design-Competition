#ifndef _MEDIAN_FILTER_H_
#define _MEDIAN_FILTER_H_

#include "include.h" /*Delay函数所在的.h文件*/

#define MedianFilterDelay(ms) systime.delay_ms(ms)

#define CollectFunc() HAL_GetTick()

#define CollectFuncTypeDef unsigned int

float MedianFilter(float i,float j,float k);
float SlidingMedianFilter(float i[],float j[],float k[]);

float F_SlidingMedianFilter(CollectFuncTypeDef (*CollectFunc)(),unsigned int delay_time);
float F_MedianFilter(CollectFuncTypeDef (*CollectFunc)(),unsigned int delay_time);

#endif
