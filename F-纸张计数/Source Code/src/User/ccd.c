#include "include.h"
#include "ccd.h"

#define CentVal 1500

void CCD_Binary(uint16_t *buf,bool *BinaryBuf,uint16_t len)
{
    for(int i=0;i<len;i++)
    {
        if(CCD.Buf[i]>=CentVal)
        {
           CCD.Buf[i]= 4095;
           CCD.BinaryBuf[i] = true;
        }
        else
        {
          CCD.Buf[i] = 0;
          CCD.BinaryBuf[i] = false;
        }
    }
}

void CCD_Delayus(uint8_t us)
{
  while(us--)
  {
    for(uint16_t i=0;i<50;i++)
	{
		 asm("nop");  
	}  
  }
}


void CCD_Init(void) 
{
  GPIO_PinInit(CCD_CLK,GPO,1);  
  GPIO_PinInit(CCD_SI, GPO,1);
  ADC_Init(ADC0);

}

/*------------------------------------------------------------------------------------------------------
【函    数】CCD_Collect
【功    能】CCD采集函数
【参    数】p  ：  存放采集数据的首地址
【返 回 值】无
【实    例】uint16_t ccd_buf[128];
【实    例】CCD_Collect(ccd_buf); 
【注意事项】
--------------------------------------------------------------------------------------------------------*/

void CCD_Collect(uint16_t *p) 
{
	unsigned char i;
	unsigned int  temp = 0;

	TSL_SI=1;;             //SI  = 1 
	CCD_Delayus(1);
	TSL_CLK = 1;           // CLK = 1 
	CCD_Delayus(1);
	TSL_SI=0;              // SI  = 0 
	CCD_Delayus(1);

	for(i=0; i<128; i++) 
	{
		CCD_Delayus(1);
		TSL_CLK = 1;       // CLK = 1 
		CCD_Delayus(1);
		temp= ADC_Ave(ADC0, CCD_A0, ADC_12bit, 5);       
		*p++ = temp;     
		TSL_CLK = 0;       // CLK = 0 
	}
	CCD_Delayus(1);
	TSL_CLK = 1;           // CLK = 1 
	CCD_Delayus(1);
	TSL_CLK = 0;           // CLK = 0 
}

void CCD_ShowInOLED(void)
{	
	uint32_t now_time = systime.get_time_ms();
	
	static uint8_t count = 0;
	while(1)
	{
		if(systime.get_time_ms() - now_time >= 50)                  //20帧
		{
			now_time = systime.get_time_ms();
			
			/* 采集ccd图像 */
			CCD_Collect(CCD.Buf);
			
			/* OLED 显示 */
			if(count % 3 == 0)
			{
				for(uint8_t i=0; i<128; i++)
				{
					OLED_Set_Pos(i , 7); 
					if(CCD.Buf[i] > 1500)	      			
						OLED_WrDat(0xFF);
					else
						OLED_WrDat(0x00);	
				}
			
			}	
			
		}
	}
}

_ccd_t_ CCD =
{
    .Init=CCD_Init,
    .Delayus=CCD_Delayus,
    .Collect=CCD_Collect,
    .Binary=CCD_Binary,
    .ShowInOLED = CCD_ShowInOLED,
    .SendToUart = CCD_ShowInUart,
    .Is_Garage=false,
};

void CCD_ShowInUart()
{
  static uint8_t count = 0;
		
  if (DetectGarage())
  {
    BEEP_ON;
  }
			/* 发送到上位机 */
  if(count++%5 == 0)
  {
      UART_PutChar(UART0,'T');
      for(uint8_t i=0; i<128; i++) 
      {
         UART_PutChar(UART0,(unsigned char)(CCD.Buf[i]>>8)); //发送高8位
         UART_PutChar(UART0,(unsigned char)CCD.Buf[i]);      //发送高低8位 
      }
  }
}


