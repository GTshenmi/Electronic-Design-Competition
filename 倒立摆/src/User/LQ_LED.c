#include "include.h"

void LED_Init(void)
{
   GPIO_PinInit(PTC0 , GPO, 1);
   GPIO_PinInit(PTD15, GPO, 1);
   GPIO_PinInit(PTE26, GPO, 1);
   
   GPIO_PinInit(PTC18, GPO, 1);
   GPIO_PinInit(PTC19, GPO, 1);
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