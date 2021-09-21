#ifndef INCLUDE_H_
#define INCLUDE_H_

#include <stdio.h>                       
#include <string.h>                     
#include <stdlib.h>                     
#include "stdbool.h"
#include <stdarg.h>
#include "matrix.h"
#include "math.h"
#include "common.h" 
#include "MK66F18.h"           
#include "core_cm4.h"       

#include "MK60_ADC.h"              /* 用于ADC模块 */
#include "MK60_GPIO.h"             /* 用于GPIO模块 */
#include "MK60_GPIO_Cfg.h"         /* 用于GPIO模块 类51的IO操作 */
#include "MK60_PLL.h"              /* 用于时钟频率设置 */
#include "MK60_UART.h"             /* 用于串口模块 */
#include "MK60_PIT.h"              /* 用于PIT定时器模块 */
#include "MK60_FTM.h"              /* 用于FTM定时器模块 */
#include "MK60_CMT.h"              /* 用于CMT定时器某块 */
#include "MK60_IIC.h"              /* 用于IIC模块 */
#include "MK60_DMA.h"              /* 用于DMA模块 */
#include "MK60_LPTMR.h"            /* 用于LPTMR定时器模块 */
#include "MK60_WDOG.h"             /* 用于看门狗 */
#include "MK60_SYSTICK.h"          /* systick 内核定时器 */
#include "MK60_FLASH.h"            /* Flash 读写 */

#include "LQ_LED.h"                /* LED         例子 */
#include "ANO_DT.h"


#include "oled.h"
#include "key.h"
#include "beep.h"
#include "adc.h"       
#include "wluart.h"
#include "oled.h"
#include "oled_font.h"  
#include "ui.h"
#include "FDC2214.h"
#include "papercount.h"

#include "median_filter.h"
//#include "FDC_IIC.h"

//#include "fuzzy_ctrl.h"
//#include "LQ_MPU6050.h"
//#include "motor.h" 
//#include "steer.h"
//#include "rng.h"
//#include "element.h"
//#include "ccd.h"
//#include "gyro_filter.h"

#define and &&
#define or ||

void _SystemInit_();
void PITx_Init();
void PITx_Close();


void PIT0_Init();
void PIT1_Init();
void PIT2_Init();
void PIT3_Init();

#endif