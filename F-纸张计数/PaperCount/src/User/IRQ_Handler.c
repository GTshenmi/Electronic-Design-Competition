#include "include.h"

void PIT0_IRQHandler()
{
    PIT_Flag_Clear(PIT0);    
    
    //C = FDC_read_CHx(3);

    
    //ANO_DT_send_int16((short)(RightMotor.CurrentSpeed));
    //ANO_DT_send_int16((short)(LeftMotor.CurrentSpeed));
    
    
    //printf("%d\n",LeftMotor.RawSpeed);
}

void PIT1_IRQHandler()
{   
    PIT_Flag_Clear(PIT1);
    
}
void PIT2_IRQHandler()
{
    PIT_Flag_Clear(PIT2);

}

void PIT3_IRQHandler()
{
    PIT_Flag_Clear(PIT3);
}
