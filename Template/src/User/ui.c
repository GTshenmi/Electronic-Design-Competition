#include "include.h"
#include "ui.h"

void OLED_ShowInitUI()
{
   OLED_P8x16Str(36,3,"Welcome.");
   systime.delay_ms(1000);
}

void OLED_Display(void)
{
    OLED_CLS();
//    for(int i = 0;i<5;i++)
//      OLED_WriteXLine(i,"ADC%d:%d",i,AD[i].SamplingValue); 
}
