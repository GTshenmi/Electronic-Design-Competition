#ifndef _PWM_H_
#define _PWM_H_

#define pwm_limit_t uint16_limit_t

typedef struct
{
    FTM_Type *PwmFTM; 
    FTM_CHn_e PwmChannel;           
    
    pwm_limit_t PwmLimit; 
    
    uint16_t duty;
    
    short PwmFreq;
    
    bool UsingDefaultConfig;    
    
}pwm_handle_t;

typedef struct
{
   pwm_handle_t Handle;     
    
   short PwmValue;			
                
   bool Is_Run;  
}pwm_t;

extern pwm_t Pwm1[4];
extern pwm_t Pwm2[4];

void Pwm_Init(pwm_t *Pwm,pwm_handle_t *handle);
void SetPwmDuty(pwm_t *Pwm,uint16_t duty);


#endif