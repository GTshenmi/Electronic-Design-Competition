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
#include "usr_common.h"
#include "MK66F18.h"           
#include "core_cm4.h"       
#include "task.h"
#include "pid_ctrl.h"
#include "normalize.h"
#include "filter.h"
#include "LUTThreshold01C.h"
#include "oled_font.h" 

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
#include "MK60_SPI.h"
   
#include "ANO_DT.h"

/*usr driver*/
#include "led.h" 
#include "beep.h"
#include "key.h"
#include "adc.h" 
#include "uart.h"
#include "oled.h"
#include "rng.h" 
#include "wluart.h"
#include "pwm.h"
#include "gpio.h"
#include "motor.h" 
#include "steer.h"
#include "tripodhead.h"
#include "FDC2214.h"
#include "lcd_driver.h"
#include "amg8833_driver.h"
#include "ads1292_spi.h"
#include "ads1292_driver.h"
#include "lmt70.h"
#include "LQ_ICM20602.h"

#include "init.h"
#include "adc_app.h"
#include "motor_ctrl.h"
#include "steer_ctrl.h"
#include "triheadctrl.h"
#include "infrared_sensor.h"
#include "tempsensor.h"
#include "egcsensor.h"
#include "ui.h"

#include "papercount.h"

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