#ifndef _CCD_H_
#define _CCD_H_

#define CCD_A0   ADC0_SE15
#define CCD_CLK  PTB23
#define CCD_SI   PTB21

#define TSL_CLK  PTB23_OUT    
#define TSL_SI   PTB21_OUT   

typedef struct
{
    uint16_t Buf[128];
    
    bool BinaryBuf[128]; // 0:White 1:Black
    
    void (*Init)();
    void (*Delayus)(uint8_t us);
    void (*Collect)(uint16_t *p);
    void (*Binary)(uint16_t *buf,bool *BinaryBuf,uint16_t len);    
    void (*ShowInOLED)();
    void (*SendToUart)();
    
    bool Is_Garage;
  
}_ccd_t_;


void CCD_Init(void);

void CCD_Collect(uint16_t *p);
void CCD_Binary(uint16_t *buf,bool *BinaryBuf,uint16_t len);

void CCD_ShowInOLED(void);
void CCD_ShowInUart();

extern _ccd_t_ CCD;


#endif