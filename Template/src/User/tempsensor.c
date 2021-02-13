#include "include.h"
#include "tempsensor.h"


temp_sensor_t TempSensor = 
{
   .Temperature = 0.0,
   .TempLimit.Max = 150.0,
   .TempLimit.Min = -55.0,
   .Init = LMT70DefaultInit,
   .Read = LMT70GetTemperature,
   .Test = LMT70Test,
   .Local = &LMT70,
};