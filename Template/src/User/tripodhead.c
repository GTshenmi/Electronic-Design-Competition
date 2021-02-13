#include "include.h"
#include "tripodhead.h"

void TriHeadController(tripodhead_t *TripodHead,short AngleH,short AngleV)
{   
    TripodHead->CtrlStrategy(&AngleH,&AngleV); 
    SetTriHeadAngle(TripodHead,AngleH,AngleV);
}

void TriHeadInit(tripodhead_t *TripodHead,steer_ctrl_t *SteerH,steer_ctrl_t *SteerV)
{
   
    TripodHead->SteerH = SteerH;
    TripodHead->SteerV = SteerV;
   
    steer_handle_t handle;
//    handle.AngleLimit.Max = NotSetLimit;   
//    
//    handle.PwmCentValue = NULL;
//    
//    handle.PwmFTM = NULL;
//    
//    handle.PwmFreq = NULL;
//    
//    handle.PwmLimit.Max = NotSetLimit;
    
    SteerCreateDefaultHandle(&handle);
    
//    handle.UsingDefaultConfig = false;
    
    
    SteerInit(TripodHead->SteerH,&handle);
    
    SteerInit(TripodHead->SteerV,&handle);
    
    TripodHead->Is_Run = true;
    
#if TRIHEAD_DATA_PROCESS_EN    
    TripodHead->DataProcess = NULL;
#endif
    
#if TRIHEAD_CTRL_STRATEGY_EN    
    TripodHead->CtrlStrategy = NULL;
#endif    

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

tripodhead_t TripodHead ;

void TriHeadTest()
{

   TriHeadxInit();
   
   int t = 0;
   uint32_t now_time = systime.get_time_ms();
   int angle = 0;
   uint32_t used_time_ms = 0;
   uint32_t used_time_us = 0;
   uint32_t time_ms = 0;
   uint32_t time_us = 0;
   
   while(1)
   {
       if(systime.get_time_ms() - now_time >= 200)
       {  
           LCD.Debug.Clear(WHITE);
           now_time = systime.get_time_ms();
           time_ms = systime.get_time_ms();
           time_us = systime.get_time_us();
           t += 20;
           if(t >= (2 * TripodHead.SteerH->Handle.AngleLimit.Max - TripodHead.SteerH->Handle.AngleLimit.Min))
             t = TripodHead.SteerH->Handle.AngleLimit.Min;
           else if(t >= (TripodHead.SteerH->Handle.AngleLimit.Max))
           {
              angle = (TripodHead.SteerH->Handle.AngleLimit.Max - TripodHead.SteerH->Handle.AngleLimit.Min)-t;
           }
           else
           {
              angle = t;
           }
           
           SetTriHeadAngle(&TripodHead,angle,angle);
           
           used_time_ms = systime.get_time_ms() - time_ms;
           used_time_us = systime.get_time_us() - time_us;
           
           LCD.Write.XLine(1,"Angle:%d",angle);
           
           if(used_time_ms)
           {
               LCD.Write.XLine(2,"used time:%ld ms",used_time_ms);
           }
           else
           {
               LCD.Write.XLine(2,"used time:%ld us",used_time_us);
           }
      
       }
     
   }
  
}
