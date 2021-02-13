#ifndef _BEEP_H_
#define _BEEP_H_

#define BEEP_GPIO_PIN PTD14

#define BEEP_ON  GPIO_PinWrite(BEEP_GPIO_PIN, 0)
#define BEEP_OFF GPIO_PinWrite(BEEP_GPIO_PIN, 1)

typedef struct
{
   state_t State;
   uint32_t ToggleTime;
   uint32_t ToggleCount;
   bool IO_SHIELD;
   
}beep_t;


extern beep_t BEEP;


void BEEP_Init();
void BEEP_Reverse();
void Task_BeepScan();
void BEEP_Test();

#endif