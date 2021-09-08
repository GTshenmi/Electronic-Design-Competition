#include "tripodhead.h"
#include "include.h"

tripodhead_t TripodHead;

void TriHeadController(tripodhead_t *TripodHead)
{
    short AngleH = 0;
    short AngleV = 0;
    TripodHead->CtrlStrategy(&AngleH,&AngleV);
    //TriHeadCtrl(TripodHead,AngleH,AngleV);
}

void TriHeadInit(tripodhead_t *TripodHead)
{
   steer_handle_t handle;
   
   TripodHead->SteerH = &Steer[0];
   TripodHead->SteerH = &Steer[1];
   
   handle.PwmFTM = NULL;

   handle.PwmFreq = NULL;
   handle.PwmCentValue = 700;
      
   handle.AngleLimit.Max = 360;
   handle.AngleLimit.Min = 0;
   
   handle.PwmLimit.Max = NotSetLimit;
   handle.PwmLimit.Min = NotSetLimit;
   
   SteerCreateHandle(TripodHead->SteerH,&handle);
   
   handle.PwmFTM = NULL;

   handle.PwmFreq = NULL;
   handle.PwmCentValue = 700;
      
   handle.AngleLimit.Max = 360;
   handle.AngleLimit.Min = 0;
   
   handle.PwmLimit.Max = NotSetLimit;
   handle.PwmLimit.Min = NotSetLimit;
   
   SteerCreateHandle(TripodHead->SteerV,&handle);
   
   SteerInit(TripodHead->SteerH);
   SteerInit(TripodHead->SteerV);
}

void SetTriHeadAngle(tripodhead_t *TripodHead,short AngleH,short AngleV)
{
    if(TripodHead->Is_Run)
    {
       SetSteerAngle(TripodHead->SteerH,AngleH); 
       SetSteerAngle(TripodHead->SteerV,AngleV);
    }
    else
    {
       SetSteerAngle(TripodHead->SteerH,0); 
       SetSteerAngle(TripodHead->SteerV,0);
    }
}

