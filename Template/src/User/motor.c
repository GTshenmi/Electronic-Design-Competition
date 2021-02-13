#include "include.h"
#include "motor.h"

void MotorInit(motor_ctrl_t *Motor,motor_handle_t *handle)
{
    Motor->Is_Run = false;
    
    MotorCreateHandle(Motor,handle);
        
    Motor->Handle.PwmValue = 0;
    Motor->TargetValue = 0;
    Motor->TargetValue_Inc = 0;
    Motor->CurrentValue = 0;
    
#if MOTOR_CTRL_FIN_CALLBACK_EN
    Motor->CtrlFinishCallBack = Motor_DefaultCtrlFinishCallBack;
#endif
#if MOTOR_DATAPROCESS_FIN_CALLBACK_EN
    Motor->DataProcessFinishCallBack = Motor_DefaultDataProcessFinishCallBack;
#endif
    
#if MOTOR_CTRLSTRATEGY_EN    
    Motor->CtrlStrategy = Motor_DefaultCtrl;
#endif
    
#if MOTOR_DATAPROCESS_EN
    Motor->DataProcess = Motor_DefaultDataProcess;
#endif
    
    Motor->GetActualValue = Motor_DefaultGetValue;
    
    FTM_PwmInit(Motor->Handle.PwmFTM[0],Motor->Handle.PwmChannel[0],Motor->Handle.PwmFreq,0);
    FTM_PwmInit(Motor->Handle.PwmFTM[1],Motor->Handle.PwmChannel[1],Motor->Handle.PwmFreq,0);
    
    if(!handle->UsingDefaultConfig && handle->UsingFeedBack)
      FTM_ABInit(Motor->Handle.ENCFTM);
    
    Motor->Is_Run = true;
}
void MotorCreateDefaultHandle(motor_handle_t *handle)
{
    handle->CtrlType = SpeedCtrl;
    handle->ENCFTM = NULL;
    handle->PwmFTM[0] = NULL;
    handle->PwmFTM[1] = NULL;
    handle->PwmFreq = NULL;
    handle->PwmLimit.Max = NotSetLimit;
    handle->PwmLimit.Min = NotSetLimit;
    handle->ParameterLimit.Max = NotSetLimit;
    handle->ParameterLimit.Min = NotSetLimit;
    handle->PwmValue = 0;
    handle->UsingDefaultConfig = true;
    handle->UsingFeedBack = false;
}
void MotorCreateHandle(motor_ctrl_t *Motor,motor_handle_t *handle)
{
    if(!handle->UsingDefaultConfig)
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
      if(handle->PwmFTM[0] == NULL || handle->PwmFTM[1] == NULL)
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
}

short GetMotorParameter(motor_ctrl_t *Motor)
{ 
   if (Motor->Handle.UsingFeedBack)
    return Motor->DataProcess(&Motor->Handle,FTM_ABGet(Motor->Handle.ENCFTM));
   else
    return NULL;
}

void SetMotorParameter(motor_ctrl_t *Motor,short value)
{
  if(Motor->Is_Run)
  {
     if(value<Motor->Handle.ParameterLimit.Min)
       value=Motor->Handle.ParameterLimit.Min;
     if(value>Motor->Handle.ParameterLimit.Max)
       value=Motor->Handle.ParameterLimit.Max;
     
     Motor->TargetValue = value;
#if MOTOR_CTRLSTRATEGY_EN  
     Motor->Handle.PwmValue=Motor->CtrlStrategy(&Motor->Handle,value);
#else
     Motor->PwmValue=value;
#endif
     
      if(Motor->Handle.PwmValue > Motor->Handle.PwmLimit.Max)     //防止占空比给错
      {
          Motor->Handle.PwmValue = Motor->Handle.PwmLimit.Max;
      }
      if(Motor->Handle.PwmValue < Motor->Handle.PwmLimit.Min)
      {
          Motor->Handle.PwmValue = Motor->Handle.PwmLimit.Min;
      }
      
     SetMotorPwmDuty(Motor,Motor->Handle.PwmValue);                               //angel=-duty+685;
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
      
      if(duty > Motor->Handle.PwmLimit.Max)     //防止占空比给错
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

void MotorTest()
{
   motor_handle_t handle;
   handle.UsingDefaultConfig = true;
   handle.UsingFeedBack = false;
   
   for(int i = 0 ; i < 4 ; i++)
   {
      MotorInit(&Motor[i],&handle); 
   }
   
   int t = 0;
   uint32_t now_time = systime.get_time_ms();
   int16_t Pwm[4];
   uint32_t used_time_ms = 0;
   uint32_t used_time_us = 0;
   while(1)
   {

       if(systime.get_time_ms() - now_time >= 200)
       {  
           now_time = systime.get_time_ms();
           LCD.Debug.Clear(WHITE);
           
           used_time_ms = systime.get_time_ms();
           used_time_us = systime.get_time_us();
           t += 20;
           
           for(int i = 0;i<4;i++)
           {
              if(t >= 3*(Motor->Handle.PwmLimit.Max - i*1000)) 
                t = -10000;
              else if(t >= (Motor->Handle.PwmLimit.Max - i*1000))
              {
                  Pwm[i] = 2 *(Motor->Handle.PwmLimit.Max - i*1000) - t;
              }
              else 
              {
                  Pwm[i] = t;
              }
              Pwm[i] = -(Pwm[i] + i*1000);
              
           }
           
           for(int i = 0;i<4;i++)
           {
              SetMotorPwmDuty(&Motor[i],Pwm[i]);
           }
           
           used_time_ms = systime.get_time_ms() - used_time_ms;
           used_time_us = systime.get_time_us() - used_time_us;
          
           
           for(int i = 0 ; i<4;i++)
              LCD.Write.XLine(i,"Motor[%d]:%.3f",i,Pwm[i]/100.0);
           
           
           if(used_time_ms)
           {
               LCD.Write.XLine(4,"used time:%ld ms",used_time_ms);
           }
           else
           {
               LCD.Write.XLine(4,"used time:%ld us",used_time_us);
           }
          
       }
     
   }
  
}

short Motor_DefaultDataProcess(motor_handle_t *handle,short value)
{
      return value;
}
short Motor_DefaultCtrl(motor_handle_t* handle,short value)
{
      return value;
}
void Motor_DefaultDataProcessFinishCallBack(motor_handle_t *handle)
{

}
void Motor_DefaultCtrlFinishCallBack(motor_handle_t* handle)
{

}
short Motor_DefaultGetValue(motor_handle_t* handle)
{
    return handle->PwmValue;
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
    .Handle.ParameterLimit.Max = 10000,
    .Handle.ParameterLimit.Min = -10000,
    
    .Handle.UsingFeedBack = false,
    .Handle.UsingDefaultConfig = true,
  },
  [1]=
  {
    .Handle.PwmFTM = MOTOR1_PWMFTM,
    .Handle.PwmChannel = MOTOR1_PWMFTM_CH,
    .Handle.ENCFTM = MOTOR1_ENCFTM,
    .Handle.PwmFreq = MOTOR1_PWMFTM_FREQ,
    .Handle.PwmLimit.Max = 10000,
    .Handle.PwmLimit.Min = -10000,
    .Handle.ParameterLimit.Max = 10000,
    .Handle.ParameterLimit.Min = -10000,
    .Handle.UsingFeedBack = false,
    .Handle.UsingDefaultConfig = true,
  },
  [2]=
  {
    .Handle.PwmFTM = MOTOR2_PWMFTM,
    .Handle.PwmChannel = MOTOR2_PWMFTM_CH,
    .Handle.ENCFTM = MOTOR2_ENCFTM,
    .Handle.PwmFreq = MOTOR2_PWMFTM_FREQ,
    .Handle.ParameterLimit.Max = 10000,
    .Handle.ParameterLimit.Min = -10000,
    .Handle.PwmLimit.Max = 10000,
    .Handle.PwmLimit.Min = -10000,
    .Handle.UsingFeedBack = false,
    .Handle.UsingDefaultConfig = true,
  },
  [3]=
  {
    .Handle.PwmFTM = MOTOR3_PWMFTM,
    .Handle.PwmChannel = MOTOR3_PWMFTM_CH,
    .Handle.ENCFTM = MOTOR3_ENCFTM,
    .Handle.PwmFreq = MOTOR3_PWMFTM_FREQ,
    .Handle.ParameterLimit.Max = 10000,
    .Handle.ParameterLimit.Min = -10000,
    .Handle.PwmLimit.Max = 10000,
    .Handle.PwmLimit.Min = -10000,
    .Handle.UsingFeedBack = false,
    .Handle.UsingDefaultConfig = true,
  },
};

