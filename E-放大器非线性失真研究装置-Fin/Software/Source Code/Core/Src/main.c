/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "XMF_OLED_STM32Cube.h"
#include "stdio.h"
#include "delay.h"

#include "stdlib.h"

#include "string.h"


#include "stm32_dsp.h"
#include "arm_math.h"
#include "arm_const_structs.h"
#include "table_fft.h"
#include "math.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define NPT 4096
#define PI2 6.28318530717959
#define Fs  (32768)
#define R   Fs/(NPT*1.0)
#define ifftFlag 0
#define doBitReverse 1

typedef struct{
    uint16_t num;
    float value;
    float hz;
}disBuf;

float fft_hz[5];
float fft_Value[5];

disBuf disFFT[(NPT>>1)];   //频谱线数据
			
uint16_t adc_buff[NPT]={0};
float fadc_buf[NPT] = {0.0};
float FFT_InputBuf[NPT*2];
float FFT_OutputBuf[NPT];



/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */


int state;//按键的标志位，未使用上
int i = 0;

int sig =5;

int tat = 0;

float THD = 0.0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//6 - A - KEY1 --- B5 -- D3
//8 - B - KEY4 --- B4 -- D2
//7 - C - KEY2 --- B6 -- D4
//5 - D - KEY3 --- B7 -- D5
#define SW1_GPIO 			GPIOD//GPIOB
#define SW1_GPIO_PIN 	GPIO_PIN_3//GPIO_PIN_5
#define SW2_GPIO 			GPIOD//GPIOB
#define SW2_GPIO_PIN 	GPIO_PIN_2//GPIO_PIN_6//GPIO_PIN_3
#define SW3_GPIO 			GPIOD//GPIOB
#define SW3_GPIO_PIN 	GPIO_PIN_4//GPIO_PIN_7//GPIO_PIN_4
#define SW4_GPIO 			GPIOD//GPIOB
#define SW4_GPIO_PIN 	GPIO_PIN_5//GPIO_PIN_4//GPIO_PIN_6

#define ON 1
#define OFF 0
#define Switch1(state) ((state) == ON?HAL_GPIO_WritePin(SW1_GPIO,SW1_GPIO_PIN,GPIO_PIN_SET):HAL_GPIO_WritePin(SW1_GPIO,SW1_GPIO_PIN,GPIO_PIN_RESET))
#define Switch2(state) ((state) == ON?HAL_GPIO_WritePin(SW2_GPIO,SW2_GPIO_PIN,GPIO_PIN_SET):HAL_GPIO_WritePin(SW2_GPIO,SW2_GPIO_PIN,GPIO_PIN_RESET))
#define Switch3(state) ((state) == ON?HAL_GPIO_WritePin(SW3_GPIO,SW3_GPIO_PIN,GPIO_PIN_SET):HAL_GPIO_WritePin(SW3_GPIO,SW3_GPIO_PIN,GPIO_PIN_RESET))
#define Switch4(state) ((state) == ON?HAL_GPIO_WritePin(SW4_GPIO,SW4_GPIO_PIN,GPIO_PIN_SET):HAL_GPIO_WritePin(SW4_GPIO,SW4_GPIO_PIN,GPIO_PIN_RESET))


#define printf1(...)  HAL_UART_Transmit(&huart1,\
																				(uint8_t *)u_buf,\
																				sprintf((char *)u_buf,__VA_ARGS__),\
																			  100)
																				
//#define OLED_WriteXLine(row,...) OLED_ShowStr(0,(row%5) * 20,\
//																								(uint8_t *)o_buf,sprintf((char *)o_buf,__VA_ARGS__))
																				
uint32_t u_buf[128];
uint32_t o_buf[2];										

#define LED1_ON()   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_SET)
#define LED1_OFF()  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_RESET)

#define LED2_ON()   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_SET)
#define LED2_OFF()  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_RESET)

#define BEEP_ON()   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_12,GPIO_PIN_RESET)
#define BEEP_OFF()  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_12,GPIO_PIN_SET)

																								
																								
void LED_Check()//在中断回调函数里不用HAL_DELAY
{
    LED1_ON();
    HAL_Delay(500);
    LED2_ON();
    HAL_Delay(500);
	
    LED1_OFF();
    HAL_Delay(500);
    LED2_OFF();
    HAL_Delay(500);
	
}

unsigned char str_buff[12];

void ADC_DMAStart()
{
    HAL_Delay(500);
	
    HAL_ADC_Start_DMA(&hadc1,(uint32_t *)adc_buff,NPT);
	
    HAL_Delay(500);
    HAL_ADC_Stop_DMA(&hadc1);
	
	
	
	
    for(int i=0;i<NPT;i++)
    {	
        fadc_buf[i] = (adc_buff[i] & 0x0fff) * 1.0;
    }
}
void FFT_Shift(float *SampleValueBuf,float *OutPutBuf,uint32_t len)
{
    for(int i = 0;i<len;i++) 
    {
        FFT_InputBuf[2*i] = (float)SampleValueBuf[i];//* 3.3/4096.0;
        FFT_InputBuf[2*i + 1] = 0.0;
    }
  
    arm_cfft_f32(&arm_cfft_sR_f32_len4096,FFT_InputBuf,ifftFlag,doBitReverse);

    arm_cmplx_mag_f32(FFT_InputBuf, OutPutBuf,len); 	
}

void CalculateTHD(float *fft_outputbuf,float *THD,float len)
{
    int FFT = 0;
    float a = 0.0;

    for(int i = 0;i<5;i++)
    {
        fft_hz[i] = 0.0;
        fft_Value[i] = 0.0;		
    }
    for(i=1;i<len-1;i++)
    {
        if((fft_outputbuf[i]>fft_outputbuf[i-1]&&fft_outputbuf[i]>fft_outputbuf[i+1]))
        {
            if(fft_outputbuf[i]>(float)62060.6)
            {
                disFFT[FFT].num =i;
                disFFT[FFT++].value =fft_outputbuf[i];
            }
        }
    }
    for(i=0;i<FFT/2;i++)
    {
        if((disFFT[i].num)*(Fs*1.0)/(len*1.0)>=5200.0)
        {
            break;
        }
        else
        {
            fft_hz[i]=(float)((disFFT[i].num)*Fs/len);
            fft_Value[i]=(disFFT[i].value + disFFT[FFT-1-i].value)/(len*2);
        }				

    }
		
    arm_sqrt_f32(fft_Value[1]*fft_Value[1]+fft_Value[2]*fft_Value[2]+fft_Value[3]*fft_Value[3]+fft_Value[4]*fft_Value[4],&a);
    if(fabs(fft_Value[0])<1e-6)
        *THD = 0.0;
    else
        *THD=a/fft_Value[0];
		
    if(*THD >= 0.483f)
        *THD = 0.483f;
		
    printf1("\r\n%.3f\r\n",*THD);
}

float CalculateTHDAve(float *THD,float len)
{
    float _THD[5] = {0.0,0.0,0.0,0.0,0.0};
    *THD = 0;
    for(int i = 0;i<5;i++)
    {
        ADC_DMAStart();

        FFT_Shift(fadc_buf,FFT_OutputBuf,NPT);
        CalculateTHD(FFT_OutputBuf,&_THD[i],NPT);	
        *THD += _THD[i];
    }
    *THD /= (5.0f);
	
    return *THD;
}

void DisplayNormalWave()
{
    Switch1(ON);
    Switch2(OFF);
    Switch3(OFF);
    Switch4(OFF);
}

void DisplayTopDistortionWave()
{
    Switch1(ON);
    Switch2(OFF);
    Switch3(ON);
    Switch4(OFF);
	
//    Switch1(ON);
//    Switch2(ON);
//    Switch3(OFF);
//    Switch4(OFF);
}
void DisplayButtonDistortionWave()
{
    Switch1(OFF);
    Switch2(OFF);
    Switch3(OFF);
    Switch4(OFF);
}
void DisplayTwoWayDistortionWave()
{	
    Switch1(ON);
    Switch2(OFF);
    Switch3(OFF);
    Switch4(ON);
	
//    Switch1(ON);
//    Switch2(OFF);
//    Switch3(ON);
//    Switch4(OFF);
}
void DisplayCrossoverDistortionWave()
{
    Switch1(ON);
    Switch2(ON);
    Switch3(OFF);
    Switch4(OFF);
	
//    Switch1(ON);
//    Switch2(OFF);
//    Switch3(OFF);
//    Switch4(ON);
}

void OLED_Display(uint8_t *wave_str,float THD)
{
	 
    OLED_ShowString(0,0,(uint8_t *)"www.bilibili.com"); 

    sprintf((char *)str_buff,"%d",(int)THD);//将数据格式化为字符串
    OLED_ShowString(46,2,str_buff);
}

void CD4066Ctrl(uint8_t data)
{
    uint8_t x = data & 0x0f;
	
    Switch1(((data>>3)&0x01));
    Switch2((data>>2)&0x01);
    Switch3((data>>1)&0x01);
    Switch3((data)&0x01);
}
void Search()
{
    for(int i = 0;i<16;i++)
        CD4066Ctrl(i);
}
void ClearStrBuf()
{
    for(int i = 0;i<12;i++)
        str_buff[i] = ' ';
	
}
void DisplayWave()
{
    float THD = 0.0;
		
    DisplayNormalWave();   //正常
    OLED_Clear();
	  
    OLED_ShowString(0,0,(uint8_t *)"Normal Wave"); 
	 
    CalculateTHDAve(&THD,NPT);

    ClearStrBuf();
    sprintf((char *)str_buff,"%7.3f %%",THD*100);//将数据格式化为字符串
	  
    OLED_ShowString(46,4,str_buff);
    HAL_Delay(4500);	
    BEEP_ON();
    HAL_Delay(500);
    BEEP_OFF();
	

    DisplayTopDistortionWave(); //顶部
    OLED_Clear();
    OLED_ShowString(0,0,(uint8_t *)"Top Distortion Wave"); 
		
    CalculateTHDAve(&THD,NPT);
		
    ClearStrBuf();
    sprintf((char *)str_buff,"%.3f %%",THD*100);//将数据格式化为字符串		OLED_ShowString(46,4,str_buff);
    OLED_ShowString(46,4,str_buff);
		
    HAL_Delay(4500);	
    BEEP_ON();
    HAL_Delay(500);
    BEEP_OFF();

    OLED_Clear();
    DisplayButtonDistortionWave(); //底部
    OLED_ShowString(0,0,(uint8_t *)"Button Distortion Wave");
		
    CalculateTHDAve(&THD,NPT);	
    ClearStrBuf();
    sprintf((char *)str_buff,"%.3f %%",THD*100);//将数据格式化为字符串
		
    OLED_ShowString(46,4,str_buff);
    HAL_Delay(4500);	
    BEEP_ON();
    HAL_Delay(500);
    BEEP_OFF();
		
		
    OLED_Clear();
    OLED_ShowString(0,0,(uint8_t *)"Two Way Distortion Wave");
    DisplayTwoWayDistortionWave();
    CalculateTHDAve(&THD,NPT);
		
    ClearStrBuf();
		
    sprintf((char *)str_buff,"%.3f %%",THD*100);//将数据格式化为字符串
    OLED_ShowString(46,4,str_buff);
    HAL_Delay(4500);	
    BEEP_ON();
    HAL_Delay(500);
    BEEP_OFF();
		
    DisplayCrossoverDistortionWave(); //交越	
    OLED_Clear();
    OLED_ShowString(0,0,(uint8_t *)"Crossover Distortion Wave"); 
		
    CalculateTHDAve(&THD,NPT);
	
    ClearStrBuf();
    sprintf((char *)str_buff,"%.3f %%",THD*100);//将数据格式化为字符串
		
    OLED_ShowString(46,4,str_buff);
    HAL_Delay(4500);	
    BEEP_ON();
    HAL_Delay(500);
    BEEP_OFF();
}


extern unsigned char BMP1[]; //开机界面    bilibili干杯！
void OLED_display_pic()
{
    OLED_Clear();
    //OLED_DrawBMP(0,0,128,8,BMP1);
    OLED_ShowString(0,0,(uint8_t *)"Hello world"); 
}


void OLED_display_info()
{
    OLED_Clear();
    OLED_ShowString(0,0,(uint8_t *)"YZ0012");
    //OLED_ShowString(0,0,(uint8_t *)"www.bilibili.com");  //第6和像素点，第0页，字符串数组
    //汉字16个像素点，一般为18个
//    OLED_ShowCHinese(0,2,0);//采样：
//    OLED_ShowCHinese(18,2,1);
//    OLED_ShowString(36,2,(uint8_t *)":"); 
//	
//	
//    OLED_ShowCHinese(0,4,3);//电压：
//    OLED_ShowCHinese(18,4,4);
//    //OLED_ShowString(38,3,(uint8_t *)"(V)");
//    OLED_ShowString(36,4,(uint8_t *)":");  
//	
//    OLED_ShowString(0,6,(uint8_t *)"Temp:");
//	
	
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_ADC1_Init();
    MX_USART1_UART_Init();
    MX_TIM3_Init();
    /* USER CODE BEGIN 2 */
    LED_Check();
    OLED_Init();
    BEEP_ON();

    HAL_Delay(500);

    BEEP_OFF();

    delay_init(72); 
	
    OLED_WriteXLine(0,"Hello,World.");
    OLED_display_info();
    HAL_TIM_Base_Start(&htim3);
    HAL_ADC_Start(&hadc1);
	
#if 1

    DisplayWave();
    DisplayNormalWave();
	
#endif
	
	
    /*******F4FFT测试*******/
	
	
    delay_init(72); 
 
    HAL_Delay(500);
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
        uint8_t fft_harmonic[5] = {0,0,0,0,0};
        uint8_t _fft_harmonic[6] = {0,0,0,0,0,0};
//        uint8_t harmonic_buf[12];
//        for(int i = 0;i<12;i++)
//            harmonic_buf[i] = ' ';
    
        /* USER CODE END WHILE */
        OLED_Clear();
        OLED_ShowString(0,0,(uint8_t *)"Test Wave"); 
			
        CalculateTHDAve(&THD,NPT);	
        for(int i = 0;i<5;i++)
        {
            if(fft_Value[i] >= 50.0||((fft_hz[i] >= ((i+1)*1000 - 250))&&(fft_hz[i] <= ((i+1)*1000 + 250))))
            {
                fft_harmonic[i] = 1;
                //if(fft_hz[i] >= ((i*1000)))
            }
            else
                fft_harmonic[i] = 0;
					
            if(fft_harmonic[i])
                _fft_harmonic[i] = i + '1';
            else
                _fft_harmonic[i] = ' ';			
        }
			
        fft_harmonic[0] = 1;
        _fft_harmonic[0] = '1';
        _fft_harmonic[5] = '\0';

        OLED_Clear();
        OLED_ShowString(0, 4,(char *)_fft_harmonic);

        sprintf((char *)str_buff,"%.3f %%",THD*100);//将数据格式化为字符串
			
        OLED_ShowString(46,2,str_buff);
			
        HAL_Delay(4500);	
        BEEP_ON();
        HAL_Delay(500);
        BEEP_OFF();
        /* USER CODE BEGIN 3 */
  }
        /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage*/
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 25;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
    {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */
//GPIO中断,此处为按键中断，记录按下的时间，未使用
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)//中断回调函数 在main中重写
{//双边沿中断
    if(GPIO_Pin == GPIO_PIN_3)  //key1 模式一 红外测温
    {
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET);
        delay_ms(10);
        tat=0;
	
    }
	
	
	
    if(GPIO_Pin == GPIO_PIN_2) 		//key2  模式2LMT70测温
    {
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET);
                          tat=1;
    }
	
	
	
}


int fputc(int ch,FILE *f)
{
    size_t count =1;
    char chTemp = (char)ch;
	
    HAL_UART_Transmit(&huart1,(uint8_t *)&chTemp,count,100);
    return count;
}
//定时器TIM1中断，未使用
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) 
{
    if(htim->Instance == TIM1)
    {
			
    }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
