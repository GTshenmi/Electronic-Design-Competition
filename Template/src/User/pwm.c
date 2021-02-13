#include "include.h"
#include "pwm.h"

void Pwm_Init(pwm_t *Pwm,pwm_handle_t *handle)
{
   if(!handle->UsingDefaultConfig)
   {
     if (handle->duty != NULL)
       Pwm->Handle.duty = handle->duty;
     else
       Pwm->Handle.duty = 0;
     
     if(handle->PwmFreq != NULL)
       Pwm->Handle.PwmFreq = handle->PwmFreq;
     
     if(handle->PwmLimit.Max != NotSetLimit && handle->PwmLimit.Min != NotSetLimit)
       Pwm->Handle.PwmLimit = handle->PwmLimit;
     
     if(handle->PwmFTM != NULL)
     {
        Pwm->Handle.PwmFTM = handle->PwmFTM;
        Pwm->Handle.PwmChannel = handle->PwmChannel;
     }
   }
   
   FTM_PwmInit(Pwm->Handle.PwmFTM,Pwm->Handle.PwmChannel,Pwm->Handle.PwmFreq,Pwm->Handle.duty);
  
}

void SetPwmDuty(pwm_t *Pwm,uint16_t duty)
{
    Pwm->Handle.duty = duty;
    FTM_PwmDuty(Pwm->Handle.PwmFTM,Pwm->Handle.PwmChannel,Pwm->Handle.duty);
}

pwm_t Pwm1[4] = 
{
[0]=
  {
    .Handle.PwmFTM = FTM0,
    .Handle.PwmChannel = FTM_CH0,
    .Handle.PwmFreq = 10000,
    .Handle.PwmLimit.Max = 10000,
    .Handle.PwmLimit.Min =0,
  },
  [1]=
  {
    .Handle.PwmFTM = FTM0,
    .Handle.PwmChannel = FTM_CH1,
    .Handle.PwmFreq = 10000,
    .Handle.PwmLimit.Max = 10000,
    .Handle.PwmLimit.Min =0,
  },
  [2]=
  {
    .Handle.PwmFTM = FTM0,
    .Handle.PwmChannel = FTM_CH2,
    .Handle.PwmFreq = 10000,
    .Handle.PwmLimit.Max = 10000,
    .Handle.PwmLimit.Min =0,
  },
  [3]=
  {
    .Handle.PwmFTM = FTM0,
    .Handle.PwmChannel = FTM_CH3,
    .Handle.PwmFreq = 10000,
    .Handle.PwmLimit.Max = 10000,
    .Handle.PwmLimit.Min =0,
  },
};
pwm_t Pwm2[4] = 
{
  [0]=
  {
    .Handle.PwmFTM = FTM0,
    .Handle.PwmChannel = FTM_CH6,
    .Handle.PwmFreq = 10000,
    .Handle.PwmLimit.Max = 10000,
    .Handle.PwmLimit.Min =0,
  },
  [1]=
  {
    .Handle.PwmFTM = FTM0,
    .Handle.PwmChannel = FTM_CH4,
    .Handle.PwmFreq = 10000,
    .Handle.PwmLimit.Max = 10000,
    .Handle.PwmLimit.Min =0,
  },
  [2]=
  {
    .Handle.PwmFTM = FTM0,
    .Handle.PwmChannel = FTM_CH5,
    .Handle.PwmFreq = 10000,
    .Handle.PwmLimit.Max = 10000,
    .Handle.PwmLimit.Min =0,
  },
  [3]=
  {
    .Handle.PwmFTM = FTM0,
    .Handle.PwmChannel = FTM_CH7,
    .Handle.PwmFreq = 10000,
    .Handle.PwmLimit.Max = 10000,
    .Handle.PwmLimit.Min =0,
  },
};
