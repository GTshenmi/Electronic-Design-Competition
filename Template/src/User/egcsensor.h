#ifndef __EGCSENSOR_H_
#define __EGCSENSOR_H_	 

typedef struct
{
    void (*Init)();
    uint32_t (*Read)(uint8_t ch);
    void (*Test)(u8);
    ads1292_t  *Local;
}egcsensor_t;

extern egcsensor_t EGCSensor;

#endif