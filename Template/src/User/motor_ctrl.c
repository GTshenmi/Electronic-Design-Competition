#include "include.h"
#include "motor_ctrl.h"


PID_TypeDef PID_CtrlStr; 

short Motor0CtrlStrategy(motor_handle_t *handle,short value)
{
    short PwmValue = 0 ;
    
    Motor0.CurrentValue = - GetMotorParameter(&Motor[0]);
    
    if(PID_CtrlStr.PID_Error[2] <= 25.0)
    {
       PID_Ctrl(&PID_CtrlStr,(float)value,(float)Motor0.CurrentValue);
       
       PwmValue = (short)PID_CtrlStr.Result;
    }
    else
    {
       PwmValue = 5000 * (value>0?1:-1);
    }
    
    return PwmValue;
}

