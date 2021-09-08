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

#include "MK60_ADC.h"              /* ����ADCģ�� */
#include "MK60_GPIO.h"             /* ����GPIOģ�� */
#include "MK60_GPIO_Cfg.h"         /* ����GPIOģ�� ��51��IO���� */
#include "MK60_PLL.h"              /* ����ʱ��Ƶ������ */
#include "MK60_UART.h"             /* ���ڴ���ģ�� */
#include "MK60_PIT.h"              /* ����PIT��ʱ��ģ�� */
#include "MK60_FTM.h"              /* ����FTM��ʱ��ģ�� */
#include "MK60_CMT.h"              /* ����CMT��ʱ��ĳ�� */
#include "MK60_IIC.h"              /* ����IICģ�� */
#include "MK60_DMA.h"              /* ����DMAģ�� */
#include "MK60_LPTMR.h"            /* ����LPTMR��ʱ��ģ�� */
#include "MK60_WDOG.h"             /* ���ڿ��Ź� */
#include "MK60_SYSTICK.h"          /* systick �ں˶�ʱ�� */
#include "MK60_FLASH.h"            /* Flash ��д */

#include "LQ_LED.h"                /* LED         ���� */
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