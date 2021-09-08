#include "include.h"
#include "steer.h"

short GetInductanceDifference()//电感差值
{
    short Ind_Value;
    
    if(Circle_State==Circle_State_4)
    {
//        if((ADLC.ProcessedValue+ADRC.ProcessedValue)>40)
        {
          if (ADLC.ProcessedValue==0 && ADRC.ProcessedValue==0)
            Ind_Value =0;
          else
            Ind_Value = (short)((((short)ADLC.ProcessedValue-(short)ADRC.ProcessedValue)*100)/((short)ADLC.ProcessedValue+(short)ADRC.ProcessedValue));
        }
//        else
//        {
//          ADLC.ProcessedValue = ADLC.LastProcessedValue;
//          ADRC.ProcessedValue = ADRC.LastProcessedValue;
//          if (ADLC.LastProcessedValue==0 && ADRC.LastProcessedValue==0)
//            Ind_Value =0;
//          else
//            Ind_Value = (short)((((short)ADLC.LastProcessedValue-(short)ADRC.LastProcessedValue)*100)/((short)ADLC.LastProcessedValue+(short)ADRC.LastProcessedValue)); 
//        }
    }
    else
    {
//       if((ADLS.ProcessedValue+ADRS.ProcessedValue)>40)
       {
          if (ADLS.ProcessedValue==0 && ADRS.ProcessedValue==0)
            Ind_Value =0;
          else
            Ind_Value =(short)((((short)ADLS.ProcessedValue-(short)ADRS.ProcessedValue)*100)/((short)ADLS.ProcessedValue+(short)ADRS.ProcessedValue));
       }
//       if(abs(Ind_Value)>=80)
//       {
//         if(Ind_Value>=0)
//         {
//           Ind_Value=80;
//         }
//         else
//         {
//           Ind_Value=-80;
//         }
//       }
//       else
//       {
//          ADLS.ProcessedValue = ADLS.LastProcessedValue;
//          ADRS.ProcessedValue = ADRS.LastProcessedValue;
//          if (ADLS.LastProcessedValue==0 && ADRS.LastProcessedValue==0)
//            Ind_Value =0;
//          else
//            Ind_Value =(short)((((short)ADLS.LastProcessedValue-(short)ADRS.LastProcessedValue)*100)/((short)ADLS.LastProcessedValue+(short)ADRS.LastProcessedValue));   
//       }
    }
//    else 
//    {
//        Ind_Value = (short)((((short)ADLC.NormalizedValue-(short)ADRC.NormalizedValue)*100)/((short)ADLC.NormalizedValue+(short)ADRC.NormalizedValue));
//    }    
    
    Steer.dA = 0;
    
    Steer.dA = Ind_Value;
    
    //Steer.dA = 1;
    
    if (Steer.dA>10)
      Steer.A += Steer.dA;
      
    return Ind_Value;  
  
}


void SteerInit()
{
    FTM_PwmInit(STEER_PWM, STEER_PWM_CHANNEL, STEER_PWM_FREQ, STEER_PWM_CENT_VALUE);
}

/*
  @SteerCtrl                              
                   ____________________                     __________________        ___________________                  
                  |                    |                   |                  |      |                   |
                  |   Other Function   |               .-->|   Dynamic PID    |      |   Other Function  |         
                  |____________________|               |   |__________________|      |___________________|
                           |                           |       |    |    |                  |
                           |                           |       | Kp | Ki |Kd                |
                         + |  Steer.Position_Inc       |       |    |    |                + |  Steer.Angle_Inc
                           |                           |     _ ↓ ___↓____↓__                |    ___________________                     ___________________          @Output               __________________
                    +      ↓        Steer.PID_Error[3] |    |               | Steer.Angle   |   |                   |  Steer.PwmValue   |                   |  Generate Midline Deviation  |                  |
     Steer.Position--->---(+)--(+)------------>-------------|  PID Control  |--------->----(+)--|  Steer.SetAngle() |------->-----------|   Steer.SetPwm()  |-------------->---------------|      @ADC        |
                         @Input ↑                           |_______________|          (-70,70) |___________________|                   |___________________|                              |__________________|
                                |                                                                                                                                                                   |
                                |                                                      ___________________________                                                                                  |                                
                                | -             Steer.CurrentPosition                 |                           |                              AD[5]                                              |
                                *-----------------------<-----------------------------| Steer.GetActualPosition() |--------------------------------<------------------------------------------------|
                                                                                      |___________________________|


*/    

void DynamicKbCtrl()
{
    float Kb_Inc_9 = 0.0;
    float kb_inc_0_8 = 0.0;
    
    static short LastPos = 0;
    
    float _div_ = 0.0;
    
    if (Steer.LastBias != 0)
      _div_ = Steer.Bias/Steer.LastBias;
    else
      _div_ = 100.0;
    
    if ((BoundaryProtect_State != BoundProtect_state_2)&& Circle_State == Circle_State_1)
    {
      
        //0.042
        Kb_Inc_9 = 0.036 * 0.42*fabs(((LeftMotor.CurrentSpeed * RightMotor.CurrentSpeed)/10000.0)*((Steer.CurrentPosition* Steer.CurrentPosition * Steer.CurrentPosition)/(LastPos * 100.0)) * (_div_));
        if (Kb_Inc_9 > 0.42)
          Kb_Inc_9 = 0.42;
        kb_inc_0_8 = -   Kb_Inc_9/9.0;
        Steer.Kb_Inc[9] = Kb_Inc_9;
        for (int i = 0 ;i < 9 ;i++)
          Steer.Kb_Inc[i] = kb_inc_0_8;
    }
    else
    {
        Kb_Inc_9 = 0;
        kb_inc_0_8 = 0;
        Steer.Kb_Inc[9] = Kb_Inc_9;
        for (int i = 0 ;i < 9 ;i++)
          Steer.Kb_Inc[i] = kb_inc_0_8;
    }
    
    
    if ((ADLS.ProcessedValue + ADRS.ProcessedValue) <= 40 && (ADLC.ProcessedValue - ADRC.ProcessedValue)<=40)
    {
        Kb_Inc_9 = - Steer.Kb_Inc[9];
        kb_inc_0_8 = - Kb_Inc_9/9.0;
        Steer.Kb_Inc[9] = Kb_Inc_9;
        for (int i = 0 ;i < 9 ;i++)
          Steer.Kb_Inc[i] = kb_inc_0_8;  
    }
    LastPos = Steer.CurrentPosition;
}

void SetSteerDynamicPID()
{
  if (!Steer.PID_Lock)
  {
     Steer.LastPosition=Steer.CurrentPosition;
     Steer.CurrentPosition=Steer.GetActualPosition();
     
    
#if Using_Dynamic_PID_1
     for(int i=0;i<9;i++)
     {
        Steer._Bias[i]=Steer._Bias[i+1];
     }
     Steer._Bias[9]=Steer.CurrentPosition;
     Steer.LastBias = Steer.Bias;

      float _bias = 0.0;
      
  #if UsingDynamicKbCtrl    
      DynamicKbCtrl();
  #endif      
      
      for (int i = 0; i < 10; i++)
      {
  #if UsingDynamicKbCtrl
          _bias += ((Steer.Kb[i]+Steer.Kb_Inc[i])*Steer._Bias[i]);
  #else
          _bias += ((Steer.Kb[i])*Steer._Bias[i]);
  #endif    
      }
      
      
      Steer.Bias = (short)_bias;
      
      Steer.Kp_Inc = Steer.Bias*Steer.Bias*Steer.Jp;
      //Steer.Kd_Inc = Steer.Bias*Steer.Bias*Steer.Jd;  
      
      /*PID限幅*/ 
      if((int)(Steer.Kp+Steer.Kp_Inc)>(int)(Steer.Kp_MaxValue)) //*float 
       Steer.Kp_Inc = Steer.Kp_MaxValue-Steer.Kp;
      
      if((int)(Steer.Kd+Steer.Kd_Inc)>(int)(Steer.Kd_MaxValue)) //*float
      {
          Steer.Kd_Inc = Steer.Kd_MaxValue -  Steer.Kd;
      }
      
      for(int j=0;j<9;j++)
      {
        Steer._Angle[j]=Steer._Angle[j+1];
      }
      Steer._Angle[9] = (short)((Steer.Kp+Steer.Kp_Inc)*(Steer.Bias)\
                        +(Steer.Kd+Steer.Kd_Inc)*(Steer.Bias-Steer.LastBias));
#endif      
  }
  else
  {
     Steer.LastPosition=Steer.CurrentPosition;
     Steer.CurrentPosition=Steer.GetActualPosition(); 
  }
    
}

void SetMidlineDeviation(int dx) /*PID Control*/ 
{
#if !TEST_CAR_STEER

  if(!Steer.PID_Lock)
  {
    /*获取中线偏差*/
    Steer.LastAngle = Steer.Angle;
	
    Steer.TargetPosition=dx;    
    
    /*计算误差*/
    Steer.PID_PreError=Steer.PID_Error;
    Steer.PID_LastError=Steer.PID_PreError;  
    Steer.PID_Error=(Steer.TargetPosition-Steer.CurrentPosition)*1.0;
   
  #if !Using_Dynamic_PID_1 
    /*动态Kp*/

        Steer.Kp_Inc=Steer.PID_Error*Steer.PID_Error*Steer.Jp;

    
    
    /*动态Kd*/
//    if(abs((short)Steer.PID_Error)>=10)
//    {
//        Steer.Kd_Inc =Steer.Jd*(Steer.Kp_Inc+Steer.Kp)*((Steer.PID_Error*Steer.PID_Error)/fabs((Steer.PID_PreError*Steer.PID_LastError)));
//    }
//    else
//    {
//        Steer.Kd_Inc = 0;
//    }
        
    /*PID限幅*/ 
    if((int)(Steer.Kp+Steer.Kp_Inc)>(int)(Steer.Kp_MaxValue)) //*float 
     Steer.Kp_Inc = Steer.Kp_MaxValue-Steer.Kp;
    
    if((int)(Steer.Kd+Steer.Kd_Inc)>(int)(Steer.Kd_MaxValue)) //*float
    {
        Steer.Kd_Inc = Steer.Kd_MaxValue -  Steer.Kd;
    }

  #endif
    
    /* 误差控制舵机打角 */
  #if USING_INC	
    /* 增量式PID */
    Steer.PID_Inc=((Steer.Kp*(Steer.PID_Error-Steer.PID_PreError)\
                  +Steer.Ki*Steer.PID_Error+Steer.Kd*(Steer.PID_Error\
                  -2*Steer.PID_PreError+Steer.PID_LastError)));
    
    Steer.Angle+=(short)(Steer.PID_Inc);
		
  #else
    
    #if Using_Dynamic_PID_1  
    
      float _angle = 0.0;
        
      for (int i = 0 ; i < 10 ; i++)
      {
          _angle += Steer.Kb[i]*Steer._Angle[i];
      }
      
      Steer.Angle =-(short)_angle;
      
    #else
    /* 位置式PID */
      Steer.Angle=(short)((Steer.Kp+Steer.Kp_Inc)*(Steer.PID_Error)\
                  +(Steer.Kd+Steer.Kd_Inc)*(Steer.PID_Error-Steer.PID_PreError));
    #endif
    
  #endif   
  }
  else
  {
      Steer.LastPosition=Steer.CurrentPosition;
      Steer.CurrentPosition=Steer.GetActualPosition();
  }
  
  
  if (Steer.using_steerprotect)
    Steer.Protect();   

  Steer.SetAngle(Steer.Angle+Steer.Angle_Inc);

    
#else
  
    Steer.LastPosition=Steer.CurrentPosition;
  
    Steer.CurrentPosition=Steer.GetActualAngle(); 
    
    Steer.SetPwm(dx);
    
#endif
}

void SetSteerAngle(short angle)//angel range from -70 to 70
{
  if(Steer.Is_Run)
  {
    if(angle<Steer.MinAngle)
      angle=Steer.MinAngle;
    if(angle>Steer.MaxAngle)
      angle=Steer.MaxAngle;
  
    Steer.PwmValue=-angle+STEER_PWM_CENT_VALUE;              //打角和占空比转换     
    SteerCtrl(Steer.PwmValue);                               //angel=-duty+685;
  }
  else
  {
      SteerCtrl(STEER_PWM_CENT_VALUE); 
  }
  
}

void SteerForceTurnLeft()
{
    if(Steer.CurrentPosition>(Steer.Position+Steer.Position_Inc))
    {
       Steer.PID_Lock = true;
       Steer.CurrentPosition = Steer.GetActualPosition();
       Steer.Angle  = 0;
       Steer.Angle_Inc = Steer.MinAngle;
    }
    else
    {
       Steer.A = 0;
       Steer.dA = 0;
       
       Steer.Angle  = 0;
       Steer.Angle_Inc = 0;   
       
       Steer.PID_Lock = false;
    }
}
void SteerForceTurnRight()
{
    if(Steer.CurrentPosition<(Steer.Position+Steer.Position_Inc))
    {
       Steer.PID_Lock = true;
       Steer.CurrentPosition = Steer.GetActualPosition();
       Steer.Angle  = 0;
       Steer.Angle_Inc = Steer.MinAngle;
    }
    else
    {
       Steer.PID_Lock = false;
       Steer.A = 0;
       Steer.dA = 0;
       
       Steer.Angle  = 0;
       Steer.Angle_Inc = 0;  
    }
}
void SteerCtrl(short duty)
{
    if(abs(duty) > FTM_PRECISON)                //防止占空比给错
    {
        duty = STEER_PWM_CENT_VALUE;
    }
    if(abs(duty) > STEER_MAX_PWM_DUTY_L)        //舵机打角进行限制，防止卡死
    {
        duty = STEER_MAX_PWM_DUTY_L;
    }
    if(abs(duty) < STEER_MIN_PWM_DUTY_R)
    {
        duty = STEER_MIN_PWM_DUTY_R;      
    }

    FTM_PwmDuty(STEER_PWM, STEER_PWM_CHANNEL, (u16)duty);
}

void SteerProtect()
{
    static int times=0;
    
    if(LeftMotor.CurrentSpeed==0&&RightMotor.CurrentSpeed==0) //*float
      times++;
    if(times>=5) 
    {
      Steer.PwmValue = STEER_PWM_CENT_VALUE;
      times=0;
    }
    
}
steer_ctrl_t Steer=
{
    .MaxAngle=75,
    .MinAngle=-85,
    .SetAngle=SetSteerAngle,
    .SetPwm=SteerCtrl,
    
    .GetActualPosition=GetInductanceDifference,
    .Protect = SteerProtect,
    .ForceTurnLeft = SteerForceTurnLeft,
    .ForceTurnRight = SteerForceTurnRight,
    
    .Kp=0.0,
    .Kp_Inc=0.0,
    .Jp=0.0,
    .Kp_MaxValue = 0.0,
 
    .Ki=0.0,

    .Kd=0.0,    
    .Kd_Inc=0.0,
    .Jd=0.0,
    .Kd_MaxValue = 0.0,

    .PID_Error=0.0,
    .PID_PreError=0.0,
    .PID_LastError=0.0,
    .PID_Inc=0.0,
    
    .CurrentPosition=0,
    .LastPosition=0,
    .Position = 0,
    .Position_Inc = 0,
    .TargetPosition =0,

    .Angle=0,
    .Angle_Inc=0,
    .TargetAngle=0,	
    .CurrentAngle=0,	      
    .LastAngle=0,	

    .PwmValue=0,  
    
    .PID_Lock = false,
    .using_steerprotect = false,
    .Is_Run = false,
    
    .dA = 0,
    .A = 0,
    .MaxA = 0,
    .MinA = 0,
};