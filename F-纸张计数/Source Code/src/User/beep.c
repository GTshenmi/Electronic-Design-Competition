#include "include.h"
#include "beep.h"
void BEEP_Init()
{
    GPIO_PinInit(BEEP_GPIO_PIN, GPO, 1);
}

