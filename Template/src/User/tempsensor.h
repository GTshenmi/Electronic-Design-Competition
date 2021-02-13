#ifndef _TEMP_SENSOR_H_
#define _TEMP_SENSOR_H_

#include "include.h"
#include "lmt70.h"

#define temp_limit_t float_limit_t

typedef struct
{
   float Temperature;
   
   temp_limit_t TempLimit;
   
   void (*Init)();
   
   float (*Read)();
   
   void (*Test)();
   
   lmt70_t *Local;
   
}temp_sensor_t;


extern temp_sensor_t TempSensor;

#endif