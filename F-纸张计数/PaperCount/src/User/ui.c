#include "include.h"
#include "oled.h"
#include "ui.h"

uint8_t OLED_display_flag=0;

void OLED_Display_Page_1(void)
{
  OLED_CLS();

}

void OLED_Display_Page_2(void)
{
    
}

void OLED_ShowInitUI()
{
   OLED_P8x16Str(36,3,"Welcome.");
   systime.delay_ms(1000);
}

void OLED_Display(void)
{
    OLED_CLS();

    OLED_WriteXLine(0,"RawC:%lu",RawC);
    OLED_WriteXLine(2,"C:%lu",C); 
      
    OLED_WriteXLine(4,"Num:%u",num);
    OLED_WriteXLine(6,"Time:%lums",totaltime);
   
}
