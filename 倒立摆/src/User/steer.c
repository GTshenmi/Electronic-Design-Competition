#include "include.h"
#include "steer.h"


void SteerInit(steer_ctrl_t *Steer)
{
    FTM_PwmInit(Steer->Handle.PwmFTM, Steer->Handle.PwmChannel, Steer->Handle.PwmFreq, Steer->Handle.PwmCentValue);
    
    steer_handle_t handle;
    
    handle.AngleLimit.Max = NULL;
    
    handle.PwmCentValue = NULL;
    
    handle.PwmFTM = NULL;
    
    handle.PwmFreq = NULL;
    
    handle.PwmLimit.Max = NULL;
    
    SteerCreateHandle(Steer,&handle);
    
    
    Steer->CtrlFinishCallBack = NULL;
    Steer->CtrlStrategy = NULL;
    Steer->CurrentAngle = 0;
    Steer->DataProcess = NULL;
    Steer->GetActualAngle = NULL;
    Steer->Is_Run = true;
    Steer->PwmValue = 0;
    Steer->TargetAngle = 0;
    Steer->TargetAngle_Inc = 0;
}

void SteerCreateHandle(steer_ctrl_t *Steer,steer_handle_t *handle)
{
   Steer->TargetAngle = 0;
   Steer->TargetAngle_Inc = 0;
   Steer->PwmValue = 0;
   Steer->CurrentAngle = 0;
   Steer->Is_Run = false;
   
   Steer->Handle.AngleLimit.Max = handle->AngleLimit.Max;
   Steer->Handle.AngleLimit.Min=  handle->AngleLimit.Min;
   
   if(handle->PwmLimit.Max != NotSetLimit && handle->PwmLimit.Min != NotSetLimit)
   {
     Steer->Handle.PwmLimit.Max = handle->PwmLimit.Max;
     Steer->Handle.PwmLimit.Min = handle->PwmLimit.Min;
   }
   
   if(handle->PwmFTM != NULL)
   {
     Steer->Handle.PwmFTM = handle->PwmFTM;
     Steer->Handle.PwmChannel = handle->PwmChannel;
   }
   
   if(handle->PwmCentValue != NULL)
     Steer->Handle.PwmCentValue = handle->PwmCentValue;
     
   if(handle->PwmFreq != NULL)
     Steer->Handle.PwmFreq = handle->PwmFreq;
   
   
   
   //Steer->Handle = handle;
  
   Steer->GetActualAngle = NULL;
      
#if STEER_CTRLSTRATEGY_EN  
   Steer->CtrlStrategy = NULL;
#endif
   
#if STEER_CTRL_FIN_CALLBACK_EN
   Steer->CtrlFinishCallBack = NULL;
#endif
   
#if STEER_DATAPROCESS_FIN_CALLBACK_EN
   Steer->DataProcessFinishCallBack = NULL;
#endif   
   
#if STEER_DATAPROCESS_FIN_CALLBACK_EN
   Steer->DataProcess = NULL;
#endif
   
}

void SteerController(steer_ctrl_t *Steer,short angle)
{
   SetSteerAngle(Steer,angle);
}

#if STEER_DATAPROCESS_FIN_CALLBACK_EN


#endif

void SetSteerAngle(steer_ctrl_t *Steer,short angle)//angel range from -70 to 70
{
  if(Steer->Is_Run)
  {
     if(angle<Steer->Handle.AngleLimit.Min)
       angle=Steer->Handle.AngleLimit.Min;
     if(angle>Steer->Handle.AngleLimit.Max)
       angle=Steer->Handle.AngleLimit.Max;
#if STEER_CTRLSTRATEGY_EN  
     Steer->PwmValue=Steer->CtrlStrategy(Steer->TargetAngle+Steer->TargetAngle_Inc);
#else
     Steer->PwmValue=angle;
#endif
     
     SetSteerPwmDuty(Steer,Steer->PwmValue);                               //angel=-duty+685;
  }
  else
  {
     SetSteerPwmDuty(Steer,Steer->Handle.PwmCentValue); 
  }  
  
#if STEER_CTRL_FIN_CALLBACK_EN
  Steer->CtrlFinishCallBack();
#endif
  
}

void SetSteerPwmDuty(steer_ctrl_t *Steer,short duty)
{
    if(abs(duty) > FTM_PRECISON)                //防止占空比给错
    {
        duty = STEER_PWM_CENT_VALUE;
    }
    if(abs(duty) > Steer->Handle.PwmLimit.Max)        //舵机打角进行限制，防止卡死
    {
        duty = Steer->Handle.PwmLimit.Max;
    }
    if(abs(duty) < Steer->Handle.PwmLimit.Min)
    {
        duty = Steer->Handle.PwmLimit.Min;      
    }

    FTM_PwmDuty(Steer->Handle.PwmFTM, Steer->Handle.PwmChannel, (u16)duty);
    
}
steer_ctrl_t Steer[4] = 
{
  [0]=
  {
    .Handle.PwmFTM = FTM3,
    .Handle.PwmChannel = FTM_CH0,
    .Handle.PwmCentValue = STEER0_PWM_CENT_VALUE,
    .Handle.PwmFreq = 300,
    .Handle.PwmLimit.Max = 10000,
    .Handle.PwmLimit.Min = -10000,
  },
  [1]=
  {
    .Handle.PwmFTM = FTM3,
    .Handle.PwmChannel = FTM_CH1,
    .Handle.PwmCentValue = STEER1_PWM_CENT_VALUE,
    .Handle.PwmFreq = 300,
    .Handle.PwmLimit.Max = 10000,
    .Handle.PwmLimit.Min = -10000,
  },
  [2]=
  {
    .Handle.PwmFTM = FTM3,
    .Handle.PwmChannel = FTM_CH2,
    .Handle.PwmCentValue = STEER2_PWM_CENT_VALUE,
    .Handle.PwmFreq = 300,
    .Handle.PwmLimit.Max = 10000,
    .Handle.PwmLimit.Min = -10000,
  },
  [3]=
  {
    .Handle.PwmFTM = FTM3,
    .Handle.PwmChannel = FTM_CH3,
    .Handle.PwmCentValue = STEER3_PWM_CENT_VALUE,
    .Handle.PwmFreq = 300,
    .Handle.PwmLimit.Max = 10000,
    .Handle.PwmLimit.Min = -10000,
  },
};
