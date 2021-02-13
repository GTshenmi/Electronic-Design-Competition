#include "include.h"
#include "infrared_sensor.h"

uint8_t InfraredSensorDataProcess(uint8_t Temp)
{
   return Temp;
}

infrared_sensor_t InfraredSensor = 
{
   .Init = amg88xxSensorInit,
   .Read = amg88xx_getTemp,
   .Test = amg88xxTest,
   .Local = &AMG8833,
};