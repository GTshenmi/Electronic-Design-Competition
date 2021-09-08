#include "include.h"
#include "motor.h"

void MotorInit(motor_ctrl_t *Motor)
{
    FTM_PwmInit(Motor->Handle.PwmFTM[0],Motor->Handle.PwmChannel[0],Motor->Handle.PwmFreq,0);
    FTM_PwmInit(Motor->Handle.PwmFTM[1],Motor->Handle.PwmChannel[1],Motor->Handle.PwmFreq,0);
    
    FTM_ABInit(Motor->Handle.ENCFTM);
    
    Motor->CtrlFinishCallBack = NULL;
    Motor->CtrlStrategy = NULL;
    Motor->CurrentValue = 0;
    Motor->DataProcess = NULL;
    Motor->GetActualValue = NULL;
    Motor->Is_Run = true;
    Motor->PwmValue = 0;
    Motor->TargetValue = 0;
    Motor->TargetValue_Inc = 0;
    
    motor_handle_t handle;
    
    handle.CtrlType = SpeedCtrl;
    handle.ENCFTM = NULL;
    handle.ParameterLimit.Max = NotSetLimit;
    handle.ParameterLimit.Min = NotSetLimit;
    handle.PwmFTM[0] = NULL;
    handle.PwmFTM[1] = NULL;
    
    handle.PwmLimit.Max = NotSetLimit;
    MotorCreateHandle(Motor,&handle);
}

void MotorCreateHandle(motor_ctrl_t *Motor,motor_handle_t *handle)
{
    motor_handle_t _handle = Motor->Handle;
    
    Motor->Handle = *handle;
    
    if(handle->ENCFTM == NULL)
    {
        Motor->Handle.ENCFTM = _handle.ENCFTM;
    }
    if(handle->ParameterLimit.Max == NotSetLimit || handle->ParameterLimit.Min == NotSetLimit)
    {
        Motor->Handle.ParameterLimit = _handle.ParameterLimit;
    }      
    if(handle->PwmLimit.Max == NotSetLimit || handle->PwmLimit.Min == NotSetLimit)
    {
        Motor->Handle.PwmLimit = _handle.PwmLimit;
    }      
    if(handle->PwmFTM[0] == NULL || handle->PwmFTM == NULL)
    {
       for(int i = 0; i < 2; i++)
       {
          Motor->Handle.PwmFTM[i] = _handle.PwmFTM[i];
          Motor->Handle.PwmChannel[i] = _handle.PwmChannel[i];
       }
    }      
    if(handle->PwmFreq == NULL)
    {
        Motor->Handle.PwmFreq = _handle.PwmFreq;
    }    
}

void SetMotorParameter(motor_ctrl_t *Motor,short value)
{
  if(Motor->Is_Run)
  {
     if(value<Motor->Handle.ParameterLimit.Min)
       value=Motor->Handle.ParameterLimit.Min;
     if(value>Motor->Handle.ParameterLimit.Max)
       value=Motor->Handle.ParameterLimit.Max;
     
#if MOTOR_CTRLSTRATEGY_EN  
     Motor->PwmValue=Motor->CtrlStrategy(Motor->TargetValue+Motor->TargetValue_Inc);
#else
     Motor->PwmValue=value;
#endif
     
     SetMotorPwmDuty(Motor,Motor->PwmValue);                               //angel=-duty+685;
  }
  else
  {
     SetMotorPwmDuty(Motor,0); 
  }  
  
#if MOTOR_CTRL_FIN_CALLBACK_EN
  Motor->CtrlFinishCallBack();
#endif
}


void SetMotorPwmDuty(motor_ctrl_t *Motor,short duty)
{
    if(Motor->Is_Run)
    {
      
      if(duty > Motor->Handle.PwmLimit.Max)     //·ÀÖ¹Õ¼¿Õ±È¸ø´í
      {
          duty = Motor->Handle.PwmLimit.Max;
      }
      if(duty < Motor->Handle.PwmLimit.Min)
      {
          duty = Motor->Handle.PwmLimit.Min;
      }
      
      /*Duty Ctrl*/
      if(duty >= 0)        
      {
          FTM_PwmDuty(Motor->Handle.PwmFTM[0], Motor->Handle.PwmChannel[0], (u16)duty);
          FTM_PwmDuty(Motor->Handle.PwmFTM[1], Motor->Handle.PwmChannel[1],  (u16)0);
      }
      else
      {
          FTM_PwmDuty(Motor->Handle.PwmFTM[0], Motor->Handle.PwmChannel[0], (u16)0);
          FTM_PwmDuty(Motor->Handle.PwmFTM[1], Motor->Handle.PwmChannel[1],  (u16)( -duty));
      }
      /*Duty Ctrl*/
      
    }
    else
    {
          FTM_PwmDuty(Motor->Handle.PwmFTM[0], Motor->Handle.PwmChannel[0],  (u16)0);
          FTM_PwmDuty(Motor->Handle.PwmFTM[1], Motor->Handle.PwmChannel[1], (u16)0);
    }
  
}

motor_ctrl_t Motor[4] = 
{
  [0]=
  {
    .Handle.PwmFTM = MOTOR0_PWMFTM,
    .Handle.PwmChannel = MOTOR0_PWMFTM_CH,
    .Handle.ENCFTM = MOTOR0_ENCFTM,
    .Handle.PwmFreq = MOTOR0_PWMFTM_FREQ,
    .Handle.PwmLimit.Max = 10000,
    .Handle.PwmLimit.Min = -10000,
  },
  [1]=
  {
    .Handle.PwmFTM = MOTOR1_PWMFTM,
    .Handle.PwmChannel = MOTOR1_PWMFTM_CH,
    .Handle.ENCFTM = MOTOR1_ENCFTM,
    .Handle.PwmFreq = MOTOR1_PWMFTM_FREQ,
    .Handle.PwmLimit.Max = 10000,
    .Handle.PwmLimit.Min = -10000,
  },
  [2]=
  {
    .Handle.PwmFTM = MOTOR2_PWMFTM,
    .Handle.PwmChannel = MOTOR2_PWMFTM_CH,
    .Handle.ENCFTM = MOTOR2_ENCFTM,
    .Handle.PwmFreq = MOTOR2_PWMFTM_FREQ,
    .Handle.PwmLimit.Max = 10000,
    .Handle.PwmLimit.Min = -10000,
  },
  [3]=
  {
    .Handle.PwmFTM = MOTOR3_PWMFTM,
    .Handle.PwmChannel = MOTOR0_PWMFTM_CH,
    .Handle.ENCFTM = MOTOR3_ENCFTM,
    .Handle.PwmFreq = MOTOR3_PWMFTM_FREQ,
    .Handle.PwmLimit.Max = 10000,
    .Handle.PwmLimit.Min = -10000,
  },
};

