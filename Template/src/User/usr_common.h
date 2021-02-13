#ifndef _USR_COMMON_H_
#define _USR_COMMON_H_
#include "stdint.h"

#define NotSetLimit (short)32767

typedef enum
{
   ON,OFF,Toggle,TaskInitState,
}state_t;

typedef struct
{
    int16_t Max;
    int16_t Min;
}int16_limit_t;

typedef struct
{
    uint16_t Max;
    uint16_t Min;
}uint16_limit_t;

typedef struct
{
   float Max;
   float Min;
}float_limit_t;

#endif