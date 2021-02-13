#include "include.h"
#include "egcsensor.h"





egcsensor_t EGCSensor = 
{
    .Init = ADS1292_Init,
    .Read = ADS1292_ReadEGCData,
    .Test = ADS1292_Test,
    .Local = &ADS1292,
};