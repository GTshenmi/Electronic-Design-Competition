
/*
②稳定方案
*/

/*
    for (int i=0;i<128;i++)
      CCD.Buf[i]=0;
    
    CCD.Is_Garage = false;
    for(int i=0;i<5;i++)
    {
        AD[i].SamplingValue=0;
        AD[i].MaxValue=4095;
        AD[i].MinValue=0;
        AD[i].ProcessedValue=0;
        AD[i].LastProcessedValue = 0;
        for(int j=0;j<ADC_ErrorBuf_Len;j++)
          AD[i].Error[j]=0;
    }
    
    LeftMotor.Kp=70;
    LeftMotor.Ki=0;
    LeftMotor.Kd=60;
    
    LeftMotor.MaxSpeed=320;
    LeftMotor.MinSpeed=0;
    LeftMotor.Inc_Speed = 0;
		
    RightMotor.Kp=70;
    RightMotor.Ki=0;
    RightMotor.Kd=60;
    
    RightMotor.MaxSpeed=320;
    RightMotor.MinSpeed=0;
    RightMotor.Inc_Speed = 0;
    
    Steer.Kp=0.05; 
    Steer.Ki=0.0;
    
    Steer.Kd=12.0;
    //14
    //Steer.Kd = 0.9;
    
    Steer.MaxAngle=70;
    Steer.MinAngle=-70;
    
    Steer.Jp=0.000332;   
    Steer.Kp_Inc=0;
    Steer.Kp_MaxValue=1.2;
    
    Steer.Jd = 0.460;//0.436
    Steer.Kd_Inc=0.0;
    Steer.Kd_MaxValue=16;//16
    
    Steer.Differnce_P=0.15;
    
    Steer.Angle=0;
    LeftMotor.Speed=4000;
    RightMotor.Speed=4000;   
    
   
    Steer.using_steerprotect = false;
    using_outwayprotect=true;        
    Start_Car = false;
    
    Steer.PID_Lock = false;
    LeftMotor.PID_Lock = false;
    LeftMotor.Is_Run = false;
    RightMotor.PID_Lock = false;
    RightMotor.Is_Run = false;
    Steer.Is_Run = false;
*/

/*
③完赛方案
*/
/*稳定值    1
 Steer.Kp=0.1; 
    Steer.Ki=0.0;
    Steer.Kd=0.25;
    
    Steer.MaxAngle=70;
    Steer.MinAngle=-70;
    
    Steer.J=0.0005;   
    Steer.Kp_Inc=0;
    Steer.Kp_MaxValue=0.6;
    
    Steer.Differnce_P=0.28;
    
    
    
    Steer.Angle=0;
    LeftMotor.Speed=4000;
    RightMotor.Speed=4000;   
void CircleGet()
{
  if((short)ADM.NormalizedValue>=50 && ((short)ADLS.NormalizedValue>=85 || (short)ADRS.NormalizedValue>=85) && Circle_flag==false)
  {
    if(abs((short)ADLC.NormalizedValue-(short)ADRC.NormalizedValue)>=10)
    {
      LCIN_count++;
    }
  }
  if((short)ADM.NormalizedValue<=80 && ((short)ADLS.NormalizedValue>=80 || (short)ADRS.NormalizedValue<=80) && LCIN_count>=2)
  {
     Circle_flag=true;
      CircleIn_flag=true;
      LCIN_count=0;
  }
  if(Circle_flag==true)
  {
    CircleIn_count++;
    if(CircleIn_count>=1000)
    {
      CircleIn_count=0;
      Circle_flag=false;
      CircleIn_flag = false;
    }
    
  }
  if(CircleIn_count>=250)
  {
      CircleIn_flag=false;
  }
*/



/*
 *@PID1
    Speed=3600
    Kp=1.5
    Kd=2.0
    Ki=0.0
    Dp=0.8
 *@PID2
    Speed=3600
    Kp=1.6
    Kd=4.0
    Ki=0.0
    Dp=0.5
 *@PID3
    Speed=3600
    Kp=1.36
    Kd=0.25
    Ki=0.0
    Dp=0.52
 *@PID3   动态PID
    Speed=4500
    Steer.Kp=0.2;
    Steer.Kd=0.25;
    Steer.J=0.001;
    Steer.Kp_MaxValue=0.75;
*/
    /*
    speed:4000
    Steer.Kp=0.2; 
    Steer.Ki=0.0;
    Steer.Kd=0.12;
    Steer.MaxAngle=70;
    Steer.MinAngle=-70;
    Steer.J=0.001;
    Steer.Kp_Inc=0;
    Steer.Kp_MaxValue=1;
    
    Steer.Differnce_P=0.3;
*/