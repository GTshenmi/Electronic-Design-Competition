#include "include.h"

void PIT0_IRQHandler()
{
    PIT_Flag_Clear(PIT0);
  
    

    //ANO_DT_send_int16((short)(RightMotor.CurrentSpeed));
    //ANO_DT_send_int16((short)(LeftMotor.CurrentSpeed));
    
    
    //printf("%d\n",LeftMotor.RawSpeed);
}

void PIT1_IRQHandler()
{   
    PIT_Flag_Clear(PIT1);
    
}
//long t[4] = { -50,-50,-50,-50};

void PIT2_IRQHandler()
{
    PIT_Flag_Clear(PIT2);
    Task.KeyScan();
    Task.IOScan();
    Task.LEDScan();
    Task.BeepScan();
    
}

void PIT3_IRQHandler()
{
    PIT_Flag_Clear(PIT3);
}
