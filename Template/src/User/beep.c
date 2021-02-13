#include "include.h"
#include "beep.h"

void BEEP_Init()
{
    GPIO_PinInit(BEEP_GPIO_PIN, GPO, 1);
}

void BEEP_Reverse()
{
   static int times = 0;
   times++;
   if(times%2)
     BEEP_ON;
   else
     BEEP_OFF;
}

void Task_BeepScan()
{
   static uint16_t state = TaskInitState;

   if(!BEEP.IO_SHIELD)
   {
      if(BEEP.State != state)
      {
         state = BEEP.State;
         if(BEEP.State == ON)
           BEEP_ON;
         if(BEEP.State == OFF)
           BEEP_OFF;
         if(BEEP.State == Toggle)
         {
           BEEP_Reverse();
           BEEP.ToggleCount =  BEEP.ToggleTime/IO_Scan_Interval;
         }
              
            
      }
      if(BEEP.State == Toggle)
      {
             BEEP.ToggleCount--;
             if(BEEP.ToggleCount == 0)
             {
                BEEP.ToggleCount =  BEEP.ToggleTime/IO_Scan_Interval;
                BEEP_Reverse();
             }
             
      }
  }
}

void BEEP_Test()
{
    BEEP_Init();
    uint16_t count = 0;
    uint32_t now_time = 0;
    uint16_t t = 0;
    uint16_t time = 0;

    BEEP.IO_SHIELD = false;
    BEEP.State = Toggle;
    BEEP.ToggleTime = 1000;
    BEEP.ToggleCount = 0;
    uint32_t used_time_ms = 0;
    uint32_t used_time_us = 0;

    while(1)
    {
       if(systime.get_time_ms() - now_time >= 50)
       {
        used_time_ms = systime.get_time_ms();
        used_time_us = systime.get_time_ms();
         t++;
         now_time = systime.get_time_ms();
         if(BEEP.ToggleCount == 0) 
         {
             count = t;
             time = 1000 - 10*(t);
         } 
         
         if(t>=10)
           t = 0;
         
    
         BEEP.ToggleTime = time;
         BEEP.ToggleCount = count;
          if(used_time_ms)
          {
             LCD.Write.XLine(4,"used time:%d ms",used_time_ms);
          }
          else
          {
             LCD.Write.XLine(4,"used time:%d us",used_time_us);
          }
       }
      
    }
    
}

beep_t BEEP = 
{
     .IO_SHIELD = true,
     .ToggleTime = 0,
     .ToggleCount = 0,
     .State = OFF,
};

