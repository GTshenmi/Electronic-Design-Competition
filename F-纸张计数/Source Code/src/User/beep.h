#ifndef _BEEP_H_
#define _BEEP_H_

#define BEEP_GPIO_PIN PTA17

#define BEEP_ON GPIO_PinWrite(BEEP_GPIO_PIN, 0)
#define BEEP_OFF GPIO_PinWrite(BEEP_GPIO_PIN, 1)

void BEEP_Init();

#endif