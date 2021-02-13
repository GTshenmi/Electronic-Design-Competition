#ifndef _INFRARED_SENSOR_H_
#define _INFRARED_SENSOR_H_

#define inftemp_limit_t float_limit_t

typedef struct
{
   float Temperature;
   
   inftemp_limit_t TempLimit;
  
   void (*Init)();
   
   float (*Read)();
   
   void (*Test)();
   
   amg8833_t *Local;
  
}infrared_sensor_t;

extern infrared_sensor_t InfraredSensor;

#endif