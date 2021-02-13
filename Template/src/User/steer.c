#include "include.h"
#include "steer.h"

void SteerInit(steer_ctrl_t *Steer,steer_handle_t *handle)
{  
    Steer->Is_Run = false;
    
    SteerCreateHandle(Steer,handle);
    
    Steer->TargetAngle = 0;
    Steer->TargetAngle_Inc = 0;
    Steer->CurrentAngle = 0;
    
#if STEER_CTRL_FIN_CALLBACK_EN    
    Steer->CtrlFinishCallBack = Steer_DefaultCtrlFinishCallBack;
#endif
    
#if STEER_DATAPROCESS_FIN_CALLBACK_EN    
    Steer->DataProcessFinishCallBack = Steer_DefaultDataProcessFinishCallBack;
#endif  
    
#if STEER_CTRLSTRATEGY_EN    
    Steer->CtrlStrategy = Steer_DefaultCtrl;
#endif

#if STEER_DATAPROCESS_EN    
    Steer->DataProcess = Steer_DefaultDataProcess;
#endif
    
    Steer->GetActualAngle = Steer_DefaultGetActualAngle;
   
    FTM_PwmInit(Steer->Handle.PwmFTM, Steer->Handle.PwmChannel, Steer->Handle.PwmFreq, Steer->Handle.PwmCentValue);
    
    Steer->Is_Run = true;
}
void SteerCreateDefaultHandle(steer_handle_t *handle)
{
    handle->AngleLimit.Max = NotSetLimit;
    handle->AngleLimit.Min = NotSetLimit;
    handle->PwmCentValue = NULL;
    handle->PwmFreq = NULL;
    handle->PwmFTM = NULL;
    handle->PwmLimit.Max = NotSetLimit;
    handle->PwmLimit.Min = NotSetLimit;
    handle->PwmValue = 0;
    handle->UsingDefaultConfig = true;
}
void SteerCreateHandle(steer_ctrl_t *Steer,steer_handle_t *handle)
{
   
   Steer->Handle.PwmValue = 0;
   
   if(!handle->UsingDefaultConfig)
   {
     if(handle->PwmLimit.Max != NotSetLimit && handle->PwmLimit.Min != NotSetLimit)
     {
       Steer->Handle.AngleLimit.Max = handle->AngleLimit.Max;
       Steer->Handle.AngleLimit.Min=  handle->AngleLimit.Min;
     }
     
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
   }
   
  
//   Steer->GetActualAngle = NULL;
      
//#if STEER_CTRLSTRATEGY_EN  
//   Steer->CtrlStrategy = NULL;
//#endif
//   
//#if STEER_CTRL_FIN_CALLBACK_EN
//   Steer->CtrlFinishCallBack = NULL;
//#endif
//   
//#if STEER_DATAPROCESS_FIN_CALLBACK_EN
//   Steer->DataProcessFinishCallBack = NULL;
//#endif   
//   
//#if STEER_DATAPROCESS_FIN_CALLBACK_EN
//   Steer->DataProcess = NULL;
//#endif
   
}

void SetSteerAngle(steer_ctrl_t *Steer,int16_t angle)
{
  if(Steer->Is_Run)
  {
     if(angle<(Steer->Handle.AngleLimit.Min))
     {
        angle=Steer->Handle.AngleLimit.Min;
     }
     else if(angle>(Steer->Handle.AngleLimit.Max))
     {
       angle=Steer->Handle.AngleLimit.Max;
     }
#if STEER_CTRLSTRATEGY_EN  
     Steer->Handle.PwmValue=Steer->CtrlStrategy(&Steer->Handle,angle);
#else
     Steer->PwmValue=angle;
#endif    
     SetSteerPwmDuty(Steer,Steer->Handle.PwmValue);                              
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

short Steer_DefaultCtrl(steer_handle_t* handle,short data)
{
    return  (-data+handle->PwmCentValue);
}

short Steer_DefaultDataProcess(steer_handle_t *handle,short value)
{
    return value;
}
void Steer_DefaultDataProcessFinishCallBack(steer_handle_t *handle)
{

}
void Steer_DefaultCtrlFinishCallBack(steer_handle_t* handle)
{

}
short Steer_DefaultGetActualAngle(steer_handle_t* handle)
{
    return PwmToAngle(handle->PwmCentValue,handle->PwmValue);
}

steer_ctrl_t Steer[4] = 
{
  [0]=
  {
    .Handle.PwmFTM = STEER0_FTM,
    .Handle.PwmChannel = STEER0_FTM_CH,
    .Handle.PwmCentValue = STEER0_PWM_CENT_VALUE,
    .Handle.PwmFreq = 50,
    .Handle.PwmLimit.Max = STEER0_MAX_PWM_DUTY_L,
    .Handle.PwmLimit.Min = STEER0_MIN_PWM_DUTY_R,
    .Handle.AngleLimit.Max = STEER0_PWM_CENT_VALUE - STEER0_MIN_PWM_DUTY_R,
    .Handle.AngleLimit.Min = STEER0_PWM_CENT_VALUE - STEER0_MAX_PWM_DUTY_L,
    .Handle.UsingDefaultConfig = true,
  },
  [1]=
  {
    .Handle.PwmFTM = STEER1_FTM,
    .Handle.PwmChannel = STEER1_FTM_CH,
    .Handle.PwmCentValue = STEER1_PWM_CENT_VALUE,
    .Handle.PwmFreq = 50,
    .Handle.PwmLimit.Max = STEER1_MAX_PWM_DUTY_L,
    .Handle.PwmLimit.Min = STEER1_MIN_PWM_DUTY_R,
    .Handle.AngleLimit.Max = STEER1_PWM_CENT_VALUE - STEER1_MIN_PWM_DUTY_R,
    .Handle.AngleLimit.Min = STEER1_PWM_CENT_VALUE - STEER1_MAX_PWM_DUTY_L,
    .Handle.UsingDefaultConfig = true,
  },
  [2]=
  {
    .Handle.PwmFTM = STEER2_FTM,
    .Handle.PwmChannel = STEER2_FTM_CH,
    .Handle.PwmCentValue = STEER2_PWM_CENT_VALUE,
    .Handle.PwmFreq = 50,
    .Handle.PwmLimit.Max = STEER2_MAX_PWM_DUTY_L,
    .Handle.PwmLimit.Min = STEER2_MIN_PWM_DUTY_R,
    .Handle.AngleLimit.Max = STEER2_PWM_CENT_VALUE - STEER2_MIN_PWM_DUTY_R,
    .Handle.AngleLimit.Min = STEER2_PWM_CENT_VALUE - STEER2_MAX_PWM_DUTY_L,
    .Handle.UsingDefaultConfig = true,
  },
  [3]=
  {
    .Handle.PwmFTM = STEER3_FTM,
    .Handle.PwmChannel = STEER3_FTM_CH,
    .Handle.PwmCentValue = STEER3_PWM_CENT_VALUE,
    .Handle.PwmFreq = 50,
    .Handle.PwmLimit.Max = STEER3_MAX_PWM_DUTY_L,
    .Handle.PwmLimit.Min = STEER3_MIN_PWM_DUTY_R,
    .Handle.AngleLimit.Max = STEER3_PWM_CENT_VALUE - STEER3_MIN_PWM_DUTY_R,
    .Handle.AngleLimit.Min = STEER3_PWM_CENT_VALUE - STEER3_MAX_PWM_DUTY_L,
    .Handle.UsingDefaultConfig = true,
  },
};
