#include "include.h"

void LED_Init(void)
{
  
   GPIO_PinInit(PTD15, GPO, 1);
   //GPIO_PinInit(PTA17, GPO, 1);  
   //GPIO_PinInit(PTD15, GPO, 1);
   //GPIO_PinInit(PTE26, GPO, 1);
      
   //GPIO_PinInit(PTC0 , GPO, 1);
//   GPIO_PinInit(PTD15, GPO, 1);
//   GPIO_PinInit(PTE26, GPO, 1);
//   
//   GPIO_PinInit(PTC18, GPO, 1);
//   GPIO_PinInit(PTC19, GPO, 1);
   
   for(int i=0;i<4;i++)
   {
     LED[i].IO_SHIELD = false;
     LED[i].State = OFF;
   }
   LED[1].IO_SHIELD = true;
   LED[2].IO_SHIELD = true;
   LED[3].IO_SHIELD = true;
}
void Task_LEDScan()
{
   static uint16_t state[4] = {TaskInitState,TaskInitState,TaskInitState,TaskInitState};
   static uint16_t toggle_times[4] = {-1,-1,-1,-1};
   
   for(int i=0;i<4;i++)
   {
      if(!LED[i].IO_SHIELD)
      {
         if(LED[i].State != state[i])
         {
            state[i] = LED[i].State;
            if(LED[i].State == ON)
              LED_ON(LED[i].LED_NUM);
            if(LED[i].State == OFF)
              LED_OFF(LED[i].LED_NUM);
            if(LED[i].State == Toggle)
            {
              //LED_Reverse(LED[i].LED_NUM);
              if(LED[i].ToggleTimes != 0)
                LED_OFF(LED[i].LED_NUM);
              //LED[i].ToggleCount =  LED[i].ToggleTime/IO_Scan_Interval;
//              toggle_times[i] = 0;
            }
              
            
         }
         if(LED[i].State == Toggle)
         {
             if(LED[i].ToggleTimes == LED_COUNT_INFINITY)
             {
          
               if(LED[i].ToggleCount == 0)
               {
                  LED[i].ToggleCount =  LED[i].ToggleTime/IO_Scan_Interval;
                  LED_Reverse(LED[i].LED_NUM);
               }
               LED[i].ToggleCount--;
             }
             else if(LED[i].ToggleTimes>0)
             {
               if(LED[i].ToggleTimes)
               {
                 if(LED[i].ToggleCount == 0)
                 {
                    LED[i].ToggleCount =  LED[i].ToggleTime/IO_Scan_Interval;
                    LED_Reverse(LED[i].LED_NUM);
                    toggle_times[i]++;
                    if(toggle_times[i]>=2)
                    {
                      toggle_times[i] = 0;
                      LED[i].ToggleTimes--;
                    }
                 }
                 LED[i].ToggleCount--;

               }
               else
               {
                    LED_OFF(LED[i].LED_NUM);
                    toggle_times[i] = -1;
                    LED[i].ToggleTimes = 0;
                    LED[i].State = OFF;
                    LED[i].ToggleCount = 0;
                    LED[i].ToggleTime = 0;
                    
               }
             }
             if(LED[i].ToggleCount <= 0)
              LED[i].ToggleCount = 0;
         }
      }
   }
}

void LED_ON(uint8_t led)
{
    switch(led)
    {
      case 0:
        GPIO_PinInit(PTA17, GPO, 0);
        break;
        
      case 1:
        GPIO_PinInit(PTC0 , GPO, 0);
        break;
        
      case 2:
        GPIO_PinInit(PTD15, GPO, 0);
        break;
        
      case 3:
        GPIO_PinInit(PTE26, GPO, 0);
        break;
        
      case 4:
        GPIO_PinInit(PTC18, GPO, 0);
        break;
        
      case 5:
        GPIO_PinInit(PTC19, GPO, 0);
        break;
        
      default:
        break;
    }
}

void LED_OFF(uint8_t led)
{

    switch(led)
    {
      case 0:
        GPIO_PinInit(PTA17, GPO, 1);
        break;
        
      case 1:
        GPIO_PinInit(PTC0 , GPO, 1);
        break;
        
      case 2:
        GPIO_PinInit(PTD15, GPO, 1);
        break;
        
      case 3:
        GPIO_PinInit(PTE26, GPO, 1);
        break;
        
      case 4:
        GPIO_PinInit(PTC18, GPO, 1);
        break;
        
      case 5:
        GPIO_PinInit(PTC19, GPO, 1);
        break;
        
      default:
        break;
    }
}

void LED_Reverse(uint8_t led)
{
    /* ¼ÇÂ¼LED×´Ì¬ */
    static uint8_t led_state[6];
    led_state[led]++;
    
    if(0 == led_state[led]%2)
    {
        LED_ON(led);
    }
    else
    {
        LED_OFF(led);
    }
}
void LED_Test()
{
    LED_Init();
    uint16_t count = 0;
    uint32_t now_time = 0;
    uint16_t t = 0;
    uint16_t time = 0;
    for(int i=0;i<4;i++)
    {
       //LED[i].IO_SHIELD = false;
       LED[i].State = Toggle;
       LED[i].ToggleTime = 1000;
       LED[i].ToggleTimes = 0;
    }
    uint32_t used_time_ms = 0;
    uint32_t used_time_us = 0;   
    while(1)
    {
       if(systime.get_time_ms() - now_time >= 50)
       {
         LCD.Debug.Clear(WHITE);
         used_time_ms = systime.get_time_ms();
         used_time_us = systime.get_time_us();

         now_time = systime.get_time_ms();
         if(LED[1].ToggleCount == 0) 
         {
             t++;
             count = t;
             time = 1000 - 10*(t);
             
             if(t>=10)
               t = 0;
             
             for(int i = 0;i<4;i++)
             {
               LED[i].ToggleTime = time;
               LED[i].ToggleTimes = count;
             }
         } 
         used_time_ms = systime.get_time_ms() - used_time_ms;
         used_time_us = systime.get_time_us() - used_time_us;
         LCD.Write.XLine(0,"toggle_times:%d",count);
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
void Test_LED(void)
{
    LED_Init();
    while(1)
    {
        LED_ON(0);
        LED_OFF(1);
        LED_OFF(2);
        LED_OFF(3);
        delayms(100);
        
        LED_OFF(0);
        LED_ON(1);
        LED_OFF(2);
        LED_OFF(3);
        delayms(100);
        
        LED_OFF(0);
        LED_OFF(1);
        LED_ON(2);
        LED_OFF(3);
        delayms(100);
        
        LED_OFF(0);
        LED_OFF(1);
        LED_OFF(2);
        LED_ON(3);
        delayms(100);
        
        LED_Reverse(4);
        LED_Reverse(5);
    }
}

led_t LED[4] = 
{
  [0] = 
  {
     .IO_SHIELD = true,
     .LED_NUM = 1,
     .ToggleTime = 0,
     .ToggleCount = 0,
  },
  [1] = 
  {
     .IO_SHIELD = true, 
     .LED_NUM = 0,
     .ToggleTime = 0,
     .ToggleCount = 0,
  },
  [2] = 
  {
     .IO_SHIELD = true,   
     .LED_NUM = 3,
     .ToggleTime = 0,
     .ToggleCount = 0,
  },  
  [3] = 
  {
     .IO_SHIELD = true,    
     .LED_NUM = 2,
     .ToggleTime = 0,
     .ToggleCount = 0,
  },
};
