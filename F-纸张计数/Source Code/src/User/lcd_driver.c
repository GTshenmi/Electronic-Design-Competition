#if 0
#include "lcd_driver.h"
/*							LCD Control	Structure											*/
lcd_ctrl_t LCD=
{
/*						LCD Basic Info												*/
		158,																				//Hight
		128,																				//Width
		1,																					//display_Type
		{0,0},																			//Cursor(x,y)
		WHITE,																			//background color
		{ORANGE,1,8+4+2},														//XLine(color,Width,interval)
		{1,8,6,BLACK,WHITE,usingNone},							//Font(Type,Hight,Width)
/*						Function												*/
#if USING_FUNCTION_ENCAPSULATION
/*						下面这个结构体仅为上述函数的整理，用法在LCD_Test函数中，不用可注释掉，同时将所有static void 改为 void	*/
		LCD_Init,LCD_DeInit,
		{LCD_ShowChar,LCD_ShowNum,LCD_ShowChinese,LCD_ShowStr},
		{LCD_DrawPoint,LCD_DrawHLine,LCD_DrawVLine,LCD_DrawLine,LCD_DrawSqr,LCD_DrawCircle,LCD_DrawPic},
		{LCD_WriteHalfLine,LCD_WriteLine,LCD_WriteXLine},
		{printf},
#if USING_HARDWARE_CONTROLER
		{LCD_HardWareWriteByte,LCD_HardWareWriteWord,LCD_HardWareWriteCmd,\
		LCD_Test,LCD_AddrReset,LCD_SetPos,LCD_Clear,LCD_Fill,LCD_SetCursor,LCD_SetBackGroundColor,\
		LCD_SetFontSize,LCD_SetFontColor,LCD_SetFontBackColor,LCD_SetXLineColor,LCD_SetXLineWidth,LCD_SetXLineInterval,LCD_SetXLineVal},	
#else 
		{LCD_SoftWareWriteByte,LCD_SoftWareWriteWord,LCD_SoftWareWriteCmd,\
		 LCD_Test,LCD_AddrReset,LCD_SetPos,LCD_Clear,LCD_Fill,LCD_SetCursor,LCD_SetBackGroundColor,\
		 LCD_SetFontSize,LCD_SetFontColor,LCD_SetFontBackColor,LCD_SetXLineColor,LCD_SetXLineWidth,LCD_SetXLineInterval,LCD_SetXLineVal},	
#endif
#endif
};

/**
	*
  * @brief 	LCD 初始化
	* @param	无
  * @retval 无	
  */
void LCD_Init()
{
#if !USING_HARDWARE_CONTROLER
/*								MUXIO									*/		
		CLOCK_EnableClock(kCLOCK_Iomuxc); 
		IOMUXC_SetPinMux(DC_MUXIO, 0U);  //E11                                                      
    IOMUXC_SetPinMux(RST_MUXIO, 0U);  //B13
    IOMUXC_SetPinMux(SDA_MUXIO, 0U);  //E12
    IOMUXC_SetPinMux(SCL_MUXIO, 0U);  //D12
		IOMUXC_SetPinMux(CS_MUXIO, 0U);  //D11
    
    IOMUXC_SetPinConfig(DC_MUXIO,0x10B0u);                                                   
    IOMUXC_SetPinConfig(RST_MUXIO,0x10B0u);
    IOMUXC_SetPinConfig(SDA_MUXIO,0x10B0u);
    IOMUXC_SetPinConfig(SCL_MUXIO,0x10B0u);  
		IOMUXC_SetPinConfig(CS_MUXIO,0x10B0u);
	
	
/*								GPIO									*/			
    gpio_pin_config_t GPIO_Output_Config = {kGPIO_DigitalOutput, //GPIO为输出方向
    0,                   //低电平
    kGPIO_NoIntmode      //非中断模式
    }; 
		GPIO_PinInit(DC_GPIO, DC_GPIO_PIN, &GPIO_Output_Config);      
    GPIO_PinInit(RST_GPIO, RST_GPIO_PIN, &GPIO_Output_Config);      
    GPIO_PinInit(SDA_GPIO, SDA_GPIO_PIN, &GPIO_Output_Config);      
    GPIO_PinInit(SCL_GPIO, SCL_GPIO_PIN, &GPIO_Output_Config); 
  	GPIO_PinInit(CS_GPIO, CS_GPIO_PIN, &GPIO_Output_Config);

#else
		LCD_HardWareSPIInit(96);
#endif		
		LCD_RST=0;
		LCD_delayms(50);                   
		LCD_RST=1;
		LCD_delayms(50);   
		LCD_WriteCmd(0x11);       		  	//关闭睡眠，振荡器工作
		LCD_delayms(10);  
		LCD_WriteCmd(0x3a);       		  	//每次传送16位数据(VIPF3-0=0101)，每个像素16位(IFPF2-0=101)
		LCD_WriteByte(0x55);	
		LCD_WriteCmd(0x26);       		  	
		LCD_WriteByte(0x04);  
		LCD_WriteCmd(0xf2);              		//Driver Output Control(1)
		LCD_WriteByte(0x01);  
		LCD_WriteCmd(0xe0);              		//Driver Output Control(1)
		LCD_WriteByte(0x3f);
		LCD_WriteByte(0x25);
		LCD_WriteByte(0x1c);
		LCD_WriteByte(0x1e);
		LCD_WriteByte(0x20);
		LCD_WriteByte(0x12);
		LCD_WriteByte(0x2a);
		LCD_WriteByte(0x90);
		LCD_WriteByte(0x24);
		LCD_WriteByte(0x11);
		LCD_WriteByte(0x00);
		LCD_WriteByte(0x00);
		LCD_WriteByte(0x00);
		LCD_WriteByte(0x00);
		LCD_WriteByte(0x00);  
		LCD_WriteCmd(0xe1);              //Driver Output Control(1)
		LCD_WriteByte(0x20);
		LCD_WriteByte(0x20);
		LCD_WriteByte(0x20);
		LCD_WriteByte(0x20);
		LCD_WriteByte(0x05);
		LCD_WriteByte(0x00);
		LCD_WriteByte(0x15);
		LCD_WriteByte(0xa7);
		LCD_WriteByte(0x3d);
		LCD_WriteByte(0x18);
		LCD_WriteByte(0x25);
		LCD_WriteByte(0x2a);
		LCD_WriteByte(0x2b);
		LCD_WriteByte(0x2b);  
		LCD_WriteByte(0x3a);    
		LCD_WriteCmd(0xb1);      
		LCD_WriteByte(0x00);    
		LCD_WriteByte(0x00);	    
		LCD_WriteCmd(0xb4);              
		LCD_WriteByte(0x07);		
		LCD_WriteCmd(0xc0);         
		LCD_WriteByte(0x0a);    
		LCD_WriteByte(0x02);  
		LCD_WriteCmd(0xc1);             
		LCD_WriteByte(0x02);  
		LCD_WriteCmd(0xc5);             
		LCD_WriteByte(0x4f);
		LCD_WriteByte(0x5a);  
		LCD_WriteCmd(0xc7);            
		LCD_WriteByte(0x40);  
		LCD_WriteCmd(0x2a);           
		LCD_WriteByte(0x00);		
		LCD_WriteByte(0x00);				
		LCD_WriteByte(0x00);		
		LCD_WriteByte(0xa8);           
		LCD_WriteCmd(0x2b);              
		LCD_WriteByte(0x00);	
		LCD_WriteByte(0x00);
		LCD_WriteByte(0x00);	 
		LCD_WriteByte(0xb3);               
		LCD_WriteCmd(0x36);              
		if(LCD.Type) 
		LCD_WriteByte(0xC0);                //竖屏显示          
		else
		LCD_WriteByte(0xA0);            	  //横屏显示
		
		LCD_WriteCmd(0xb7);        //LCD Driveing control
		LCD_WriteByte(0x00);		
		LCD_WriteCmd(0x29);   		//开启屏幕显示
		LCD_WriteCmd(0x2c);   		//设置为LCD接收数据/命令模式  
		LCD_Clear(WHITE);
		LCD.XLine.Interval=LCD.Font.Hight+LCD.Font.Hight/2;
}
static void LCD_DeInit()
{
		LCD_CS=1;
}


#if !USING_HARDWARE_CONTROLER
/**
	*
	* @brief 	向LCD发送一个字节
	* @param 	data：要发送的字节
  * @retval 无
	*	@attention: 软件模拟
	*
  */
static void LCD_SoftWareWriteByte(unsigned char data)
{  
		uint8_t i;
		LCD_DC=1;		
		for(i=0;i<8;i++)
		{
			LCD_SCL=0;
			//LCD_delayus(1); 	    
			if(data&0x80)
				LCD_SDA=1;
			else
				LCD_SDA=0;           
			LCD_SCL=1;
			//LCD_delayus(1);	
			data = (data<<1);    
		}
}
/**
	*
	* @brief 	向LCD发送一个字
	* @param 	data：要发送的字
  * @retval 无	
	*	@attention: 软件模拟
	*
  */
static void LCD_SoftWareWriteWord(uint16_t data)
{  		 
		uint8_t i;
		
		LCD_DC=1;
		
		for(i=0;i<16;i++)
		{
			LCD_SCL=0;
			//LCD_delayus(1);
			if(data&0x8000){ LCD_SDA=1;}
			else{LCD_SDA=0;}
			LCD_SCL=1;
			//LCD_delayus(1);
			data<<=1;    
		}  
}
/**
	*
	* @brief 	向LCD发送命令
	* @param 	cmd：要发送的命令
  * @retval 无	
	*	@attention: 软件模拟
	*
  */
static void LCD_SoftWareWriteCmd(uint8_t cmd)
{
		uint8_t i;
		
		LCD_DC=0;
		for(i=0;i<8;i++)
		{
			LCD_SCL=0;
			//LCD_delayus(1);	
			if(cmd&0x80){LCD_SDA=1;}
			else{LCD_SDA=0;}
			LCD_SCL=1;
			//LCD_delayus(1);
			cmd = (cmd<<1);
		}
}
#else
/**
	*
	* @brief 	硬件SPI初始化
	* @param 	无
  * @retval 无
	*
  */
static void LCD_HardWareSPIInit(uint8_t baudrate)
{
		lpspi_master_config_t lpspix_config; 
    u32 lpspiclk=0;
    u32 spi_baudrate=baudrate*1000000;
		CLOCK_EnableClock(kCLOCK_Iomuxc); 
/*											MUX IO													*/			   
    CLOCK_SetMux(kCLOCK_LpspiMux,1);    //USB1 PLL PFD0(576MHz)作为LPSPI时钟源
    CLOCK_SetDiv(kCLOCK_LpspiDiv,5);    //分频设置，分频值为5+1，所以LPSPI CLK=576/(1+5)=96Mhz                         
 
		IOMUXC_SetPinMux(IOMUXC_GPIO_B0_15_GPIO2_IO15, 0U);  //E11                                                      
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_10_GPIO2_IO26, 0U);  //B13
    IOMUXC_SetPinMux(LCD_SDA, 0U); 										 	 //E12
    IOMUXC_SetPinMux(LCD_SCL, 0U);  										 //D12
		IOMUXC_SetPinMux(IOMUXC_GPIO_B1_03_GPIO2_IO19, 0U);  //D11
    
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_15_GPIO2_IO15,0x10B0u);                                                   
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_10_GPIO2_IO26,0x10B0u);
    IOMUXC_SetPinConfig(LCD_SDA,0x10B0u);
    IOMUXC_SetPinConfig(LCD_SCL,0x10B0u);  
		IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_03_GPIO2_IO19,0x10B0u);
	
	
/*											GPIO													*/			
    gpio_pin_config_t GPIO_Output_Config = {kGPIO_DigitalOutput, //GPIO为输出方向
    0,                   //低电平
    kGPIO_NoIntmode      //非中断模式
    }; 
		GPIO_PinInit(GPIO2, 15, &GPIO_Output_Config);      
    GPIO_PinInit(GPIO2, 26, &GPIO_Output_Config);      

  	GPIO_PinInit(GPIO2, 19, &GPIO_Output_Config);

		
/*											LPSPI													*/	
    lpspiclk=(CLOCK_GetFreq(kCLOCK_Usb1PllPfd0Clk)/(5+1));//LPSPI时钟
    lpspix_config.baudRate=spi_baudrate;               //SPI速度
    lpspix_config.whichPcs=kLPSPI_Pcs1;                 //片选信号，PCS1
    lpspix_config.pcsActiveHighOrLow=kLPSPI_PcsActiveLow;//片选信号低电平有效
    lpspix_config.bitsPerFrame=8;                       //设置SPI的数据大小:SPI发送接收8位帧结构
    lpspix_config.cpol=kLPSPI_ClockPolarityActiveLow;   //串行同步时钟低电平有效
    lpspix_config.cpha=kLPSPI_ClockPhaseSecondEdge;      //串行同步时钟的第二个跳变沿（上升或下降）数据被采样
    lpspix_config.direction=kLPSPI_MsbFirst;            //指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
    lpspix_config.pinCfg=kLPSPI_SdiInSdoOut;            //SDI输入引脚，SDO输出引脚
    lpspix_config.dataOutConfig=kLpspiDataOutRetained;  //输出数据保留
    lpspix_config.pcsToSckDelayInNanoSec=10;            //片选拉低到时钟有效之间的延时时间,单位ns
    lpspix_config.lastSckToPcsDelayInNanoSec=10;        //最后一个时钟到片选拉高之间的延时，单位ns
    lpspix_config.betweenTransferDelayInNanoSec=10;     //两次传输之间的延时，单位ns
    LPSPI_MasterInit(LPSPI,&lpspix_config,lpspiclk);
    LPSPI_Enable(LPSPI,true);                          //使能LPSPI		
}

/**
	*
	* @brief 	向LCD发送一个字节
	* @param 	data：要发送的字节
  * @retval 无
	*	@attention: 硬件控制
	*
  */
static void LCD_HardWareWriteByte(uint8_t data)
{  
		LCD_DC=1;
    uint8_t spitxdata=data;
    lpspi_transfer_t spi_tranxfer;
    
    spi_tranxfer.configFlags=kLPSPI_MasterPcs1|kLPSPI_MasterPcsContinuous;     //PCS1
    spi_tranxfer.txData=&spitxdata;                 //要发送的数据
    spi_tranxfer.dataSize=1;                        //数据长度
    LPSPI_MasterTransferBlocking(LPSPI,&spi_tranxfer);	    //SPI阻塞发送   					    		
}
/**
	*
	* @brief 	向LCD发送一个字
	* @param 	data：要发送的字
  * @retval 无	
	*	@attention: 硬件控制
	*
  */
static void LCD_HardWareWriteWord(uint16_t data)
{  
//			LCD_DC=1;
//			uint8_t spitxdata[2];
//			spitxdata[0]=(uint8_t)((data&0xFF00)>>8);
//			spitxdata[1]=(uint8_t)(data&0x00FF);
//			lpspi_transfer_t spi_tranxfer;
//			
//			spi_tranxfer.configFlags=kLPSPI_MasterPcs1|kLPSPI_MasterPcsContinuous;     //PCS1
//			spi_tranxfer.txData=&spitxdata;                 //要发送的数据
//			spi_tranxfer.dataSize=2;                        //数据长度
//			LPSPI_MasterTransferBlocking(LPSPI3,&spi_tranxfer);	    //SPI阻塞发送   					
			LCD_HardWareWriteByte((uint8_t)((data&0xFF00)>>8));	
			LCD_HardWareWriteByte((uint8_t)(data&0x00FF));
}
/**
	*
	* @brief 	向LCD发送命令
	* @param 	cmd：要发送的命令
  * @retval 无	
	*	@attention: 硬件控制
	*
  */
static void LCD_HardWareWriteCmd(uint8_t cmd)
{
		LCD_DC=0;
    uint8_t spitxdata=cmd;
    lpspi_transfer_t spi_tranxfer;
    
    spi_tranxfer.configFlags=kLPSPI_MasterPcs1|kLPSPI_MasterPcsContinuous;     //PCS1
    spi_tranxfer.txData=&spitxdata;                 //要发送的数据
    spi_tranxfer.dataSize=1;                        //数据长度
    LPSPI_MasterTransferBlocking(LPSPI,&spi_tranxfer);	    //SPI阻塞发送   	
}
#endif
/**
	*
	* @brief 	LCD地址复位
	* @param 	无
  * @retval 无	
	*
  */
static void LCD_AddrReset(void)
{
		LCD_WriteCmd(0x2a);     //配置MCU可操作的LCD内部RAM横坐标起始、结束参数
		LCD_WriteByte(0x00);       //横坐标起始地址0x0000
		LCD_WriteByte(0x00);					
		LCD_WriteByte(0x00);       //横坐标结束地址0x007f(127)
		LCD_WriteByte(0xa8);       //7f  
		LCD_WriteCmd(0x2b);     //配置MCU可操作的LCD内部RAM纵坐标起始结束参数
		LCD_WriteByte(0x00);       //纵坐标起始地址0x0000
		LCD_WriteByte(0x00);
		LCD_WriteByte(0x00);       //纵坐标结束地址0x009f(159)
		LCD_WriteByte(0xb3);       //9f  
		LCD_WriteCmd(0x2C);     //GRAM接收MCU数据或命令
}
/**
	*
	* @brief 	设置LCD画点范围
	* @param 	xs：起始x坐标
	* @param 	ys：起始y坐标
	* @param 	xe：结束x坐标
	* @param 	ye：结束y坐标
  * @retval 无	
	*
  */
static void LCD_SetPos(uint8_t xs,uint8_t ys,uint8_t xe,uint8_t ye)
{
		LCD_WriteCmd(0x2A);      	//Colulm addRSTs set
		LCD_WriteByte(0x00);		//行起始坐标高8位，始终为零
		LCD_WriteByte(xs);			//行起始坐标低8位
		LCD_WriteByte(0x00);		//行终止坐标高8位，始终为零
		LCD_WriteByte(xe);			//行终止坐标低8位  
		LCD_WriteCmd(0x2B);      	//Colulm addRSTs set
		LCD_WriteByte(0x00);		//列起始坐标高8位，始终为零
		LCD_WriteByte(ys);			//列起始坐标低8位
		LCD_WriteByte(0x00);		//列终止坐标高8位，始终为零
		LCD_WriteByte(ye);			//列终止坐标低8位  
		LCD_WriteCmd(0x2C);      	//GRAM接收MCU数据或命令
}
/**
	*
	* @brief 	设置LCD光标
	* @param 	x：光标x坐标
	* @param 	y：光标y坐标
  * @retval 无	
	*	@attention： 仅用于Printf 函数及 write函数
	*
  */
static void LCD_SetCursor(uint16_t x,uint16_t y)
{
		LCD.Cursor.x=x;
		LCD.Cursor.y=y;
}
/**
	*
	* @brief 	设置LCD的背景色
	* @param 	color:背景颜色
  * @retval 无	
	*	@attention： 仅用于Printf 函数及 write函数
	*
  */
static void LCD_SetBackGroundColor(lcd_color_t color)
{
		LCD.Backgroundcolor=color;
}
/**
	*
	* @brief 	设置显示的字体大小
	* @param 	width：字体的宽度
	* @param 	hight：字体的高度
  * @retval 无	
	*
  */
static void LCD_SetFontSize(uint16_t width,uint16_t hight)
{
		LCD.Font.Hight=hight;
		LCD.Font.Width=width;
}
/**
	*
	* @brief 	设置显示的字体颜色
	* @param 	color:字体颜色
  * @retval 无	
	*	@attention： 仅用于Printf 函数及 write函数
	*
  */
static void LCD_SetFontColor(lcd_color_t color)
{
		LCD.Font.Color=color;
}
/**
	*
	* @brief 	设置显示的字体的背景颜色
	* @param 	color:字体背景颜色
  * @retval 无	
	*	@attention： 仅用于Printf 函数及 write函数
	*
  */
void LCD_SetFontBackColor(lcd_color_t color)
{
		LCD.Font.Backcolor=color;
}
/**
	*
	* @brief 	设置分割线的颜色
	* @param 	color:颜色
  * @retval 无	
	*	@attention 仅用于WriteXLine函数
	*
  */
static void LCD_SetXLineColor(lcd_color_t color)
{
		LCD.XLine.Color=color;
}
/**
	*
	* @brief 	设置分割线的宽度
	* @param 	width:宽度
  * @retval 无	
	*	@attention 仅用于WriteXLine函数
	*
  */
static void LCD_SetXLineWidth(uint8_t width)
{
		LCD.XLine.Width=width;
}
/**
	*
	* @brief 	设置分割线的间隔
	* @param 	interval:间隔
  * @retval 无	
	*	@attention 仅用于WriteXLine函数
	*
  */
static void LCD_SetXLineInterval(uint8_t interval)
{
		if(interval>LCD.Font.Hight)
		LCD.XLine.Interval=interval;
		else
		LCD.XLine.Interval=LCD.Font.Hight+LCD.Font.Hight/2;
}
/**
	*
	* @brief 	分割线配置
	* @param 	color:颜色
	* @param 	width:宽度
	* @param 	interval:间隔
  * @retval 无	
	*	@attention 仅用于WriteXLine函数
	*
  */
static void LCD_SetXLineVal(lcd_color_t color,uint8_t width,uint8_t interval)
{
		LCD.XLine.Color=color;
		LCD.XLine.Width=width;
		if(interval>LCD.Font.Hight)
		LCD.XLine.Interval=interval;
		else
		LCD.XLine.Interval=LCD.Font.Hight+LCD.Font.Hight/2;
}
/**
	*
	* @brief 	清屏
	* @param 	color:背景颜色
  * @retval 无	
	*
  */
static void LCD_Clear(lcd_color_t color)
{
		unsigned int i,j;
		
		LCD_AddrReset();
		LCD.Backgroundcolor=color;
		for(i=0;i<LCD.Hight;i++)      //160
		{
			for(j=0;j<LCD.Width;j++)
			{
				LCD_WriteWord(color);
			}
		}
}
/**
	*
	* @brief 	范围填充
	* @param 	xs：起始x坐标
	* @param 	ys：起始y坐标
	* @param 	xe：结束x坐标
	* @param 	ye：结束y坐标	
	* @param 	color:填充颜色
  * @retval 无	
	*
  */
static void LCD_Fill(uint8_t xs,uint8_t ys,uint8_t xe,uint8_t ye,lcd_color_t color)
{
		int i,j;
		for(i=xs;i<xe;i++)
			for(j=ys;j<=ye;j++)
				LCD_DrawPoint(i,j,color);
}


/**
	*
	* @brief 	画点
	* @param 	xs：x坐标
	* @param 	ys：y坐标
	* @param 	color:填充颜色
  * @retval 无	
	*
  */
static void LCD_DrawPoint(uint8_t xs,uint8_t ys,lcd_color_t color)
{
		LCD_WriteCmd(0x2A);      	//Colulm addRSTs set
		LCD_WriteByte(0x00);		//行起始坐标高8位，始终为零
		LCD_WriteByte(xs);			//行起始坐标低8位
		LCD_WriteByte(0x00);		//行终止坐标高8位，始终为零
		LCD_WriteByte(xs+1);			//行终止坐标低8位  
		LCD_WriteCmd(0x2B);      	//Colulm addRSTs set
		LCD_WriteByte(0x00);		//列起始坐标高8位，始终为零
		LCD_WriteByte(ys);			//列起始坐标低8位
		LCD_WriteByte(0x00);		//列终止坐标高8位，始终为零
		LCD_WriteByte(ys);			//列终止坐标低8位  
		LCD_WriteCmd(0x2C);      	//GRAM接收MCU数据或命令		
		LCD_WriteWord(color);
}
/**
	*
	* @brief  画水平线
	* @param 	xs：起始x坐标
	* @param 	ys：起始y坐标
	* @param 	len：线的长度
	* @param 	width：线的宽度	
	* @param 	color:线条颜色
  * @retval 无	
	*
  */
static void LCD_DrawHLine(uint8_t xs,uint8_t ys,uint8_t len,uint8_t width,lcd_color_t color)//水平线
{
  unsigned int i,j;
  
  //TFTSPI_Addr_Rst();
	
  LCD_SetPos(xs,ys,xs+len,width+ys-1);
  for(i=0;i<=len;i++)      //160
  {
    for(j=0;j<width;j++)
    {
      LCD_WriteWord(color);
    }
  }
	LCD.Cursor.x=xs+len;
	LCD.Cursor.y=ys+width;
}
/**
	*
	* @brief  画垂线
	* @param 	xs：起始x坐标
	* @param 	ys：起始y坐标
	* @param 	len：线的长度
	* @param 	width：线的宽度	
	* @param 	color:线条颜色
  * @retval 无	
	*
  */
static void LCD_DrawVLine(uint8_t xs,uint8_t ys,uint8_t len,uint8_t width,lcd_color_t color)//垂线
{
		unsigned int i,j;
		
		//TFTSPI_Addr_Rst();
		
		LCD_SetPos(xs,ys,xs+width-1,len+ys);
		for(i=0;i<=len;i++)      //160
		{
			for(j=0;j<width;j++)
			{
				LCD_WriteWord(color);
			}
		}	
		LCD.Cursor.x=xs+width;
		LCD.Cursor.y=ys+len;
}
/**
	*
	* @brief  画线
	* @param 	xs：起始x坐标
	* @param 	ys：起始y坐标
	* @param 	xe：结束x坐标
	* @param 	ye：结束y坐标
	* @param 	color:线条颜色
  * @retval 无	
	*
  */
static void LCD_DrawLine(uint8_t xs,uint8_t ys,uint8_t xe,uint8_t ye,lcd_color_t color)
{
		unsigned int x;
		unsigned int k;
		if(xs!=xe)
		{
				k=(ye-ys)/(xe-xs);
				for(x=xs;x<=xe;x++)
				{
						LCD_DrawPoint(x,k*(x-xs)+ys,color);
				}
		}
		else
		{
				for(x=ys;x<=ye;x++)
				{
						LCD_DrawPoint(xs,x,color);
				}
		}
}
/**
	*
	* @brief  画矩形
	* @param 	xs：起始x坐标
	* @param 	ys：起始y坐标
	* @param 	xe：结束x坐标
	* @param 	ye：结束y坐标
	* @param 	color:线条颜色
  * @retval 无	
	*
  */
static void LCD_DrawSqr(uint8_t xs,uint8_t ys,uint8_t xe,uint8_t ye,lcd_color_t color)
{
		LCD_DrawLine(xs,ys,xe,ys,color);
		LCD_DrawLine(xs,ys,xs,ye,color);
		LCD_DrawLine(xs,ye,xe,ye,color);
		LCD_DrawLine(xe,ys,xe,ye,color);
}
/**
	*
	* @brief  画圆
	* @param 	x：圆心x坐标
	* @param 	y：圆心y坐标
	* @param 	r：圆半径
	* @param 	color:线条颜色
  * @retval 无	
	*
  */
static void LCD_DrawCircle(uint8_t x,uint8_t y,uint8_t r,lcd_color_t color)
{
  unsigned char dx, dy = r; 
  
  if((x>=r) &&((LCD.Hight-x)>=r) && (y>=r) && ((LCD.Width-y)>=r))		//确定所画圆在屏幕范围内，没有超出最外边，(暂不支持与屏幕边相交)
  {
    for(dx = 0; dx <= r; dx++)
    {
      while((r * r + 1 - dx * dx) < (dy * dy)) dy--;
      LCD_DrawPoint(x + dx, y - dy, color);
      LCD_DrawPoint(x - dx, y - dy, color);
      LCD_DrawPoint(x - dx, y + dy, color);
      LCD_DrawPoint(x + dx, y + dy, color);
      
      LCD_DrawPoint(x + dy, y - dx, color);
      LCD_DrawPoint(x - dy, y - dx, color);
      LCD_DrawPoint(x - dy, y + dx, color);
      LCD_DrawPoint(x + dy, y + dx, color);
    }
  }
}
/**
	*
	* @brief  画图
	* @param 	x：		起始x坐标
	* @param 	y：		起始y坐标
	* @param 	w：		图片宽度
	* @param 	h：		图片高度
	* @param 	*ppic:存储图片的首地址
  * @retval 无	
	*
  */
static void LCD_DrawPic(uint8_t x,uint8_t y,uint8_t w,uint8_t h,uint8_t *ppic) 
{
    unsigned int i;	
    LCD_SetPos(x,y,x+w-1,y+h);
    for(i=0;i<w*h;i++)
    { 			
        LCD_WriteWord((ppic[2*i]<<8)+(ppic[2*i+1])); //高位在前，且两个数据组合成一个16位数据表示像素值  
    }
}
/**
	*
	* @brief  显示字符
	* @param 	x：		x坐标
	* @param 	y：		y坐标
	* @param 	ch：			要显示的字符
	* @param 	color：	字符颜色
  * @retval 无	
	*	@attention 实际坐标x=row*字体宽度,实际坐标y=col*字体高度
	*
  */
static void LCD_ShowChar(uint8_t x,uint8_t y,uint8_t ch,lcd_color_t color)
{
  uint8_t i,j;
	if(x>LCD.Width)
		y+=LCD.Font.Hight,x=0;
	
	LCD.Cursor.x=x;
	LCD.Cursor.y=y;
	
  LCD_SetPos(x,y,x+LCD.Font.Width-1,y+LCD.Font.Hight-1);			//定位字符显示区域
  
  for(j=0; j<8; j++)
  {
    for(i=0; i<6; i++)
    {
      if((Font_code8[ch-32][i]) & (0x01<<j))
				LCD_WriteWord(color);
      else
        LCD_WriteWord(LCD.Font.Backcolor);
    }
  }		
}	
/**
	*
	* @brief  显示字符
	* @param 	row：		行
	* @param 	col：		列
	* @param 	num：			要显示的数字
	* @param 	color：	字符颜色
  * @retval 无	
	*	@attention 实际坐标x=row*字体宽度,实际坐标y=col*字体高度
	*
  */
static void LCD_ShowNum(uint8_t row,uint8_t col,long num,lcd_color_t color)
{
			unsigned int len=0;
			long temp=num;
			unsigned int i=0;
			if(num<0)
			{
					LCD_ShowChar(row*LCD.Font.Width,col*LCD.Font.Hight,'-',color);
					num=-num;
					row++;
			}
			if(num==0)
			LCD_ShowChar(row*LCD.Font.Width,col*LCD.Font.Hight,'0',color);
			else
			{
					while(temp)
					{
							len++;
							temp/=10;
					}
					for(i=0;i<len;i++)
					{
						LCD_ShowChar((row+len-i-1)*LCD.Font.Width,col*LCD.Font.Hight,(num%10+'0'),color);
						num/=10;
					}
			}
}
/**
	*
	* @brief  显示汉字
	* @param 	无
  * @retval 无	
	*
  */
static void LCD_ShowChinese()
{
	;
}
/**
	*
	* @brief  显示字符串
	* @param 	row：		行
	* @param 	col：		列
	* @param 	*str：		要显示的字符串首地址
	* @param 	color：	字符颜色
  * @retval 无	
	*	@attention 实际坐标x=row*字体宽度,实际坐标y=col*字体高度
	*
  */
static void LCD_ShowStr(uint8_t row,uint8_t col,uint8_t *str,lcd_color_t color)
{
		int len=0,i;
		uint8_t *p=str;
		while(*p!='\0')
		{
				p++;
				len++;
		}
		for(i=0;i<len;i++)
		{
				LCD_ShowChar((row+i)*LCD.Font.Width,col*LCD.Font.Hight,str[i],color);
		}
}
#if 0
/**
	*
	* @brief  fputc
	* @param 	ch：			字符
	* @param 	*f：			文件流
  * @retval 字符	
	*	@attention 该函数用于printf的重定向到LCD屏幕
	*
  */
int fputc(int ch, FILE *f)
{
			if(LCD.Font.PrintState==usingWriteXLine)
			{
					static int y=-1;
					if(ch == '\n')    //换行
					{
							LCD.Cursor.x = 0;
							LCD.Cursor.y+= LCD.XLine.Interval;
							LCD.Font.Backcolor=YELLOW;
							y=LCD.Cursor.y;
							return ch;
					}
					if(LCD.Cursor.x > (LCD.Width - LCD.Font.Width) )
					{
							LCD.Cursor.x = 0; 	//x置零
							LCD.Cursor.y+= LCD.XLine.Interval;
							y=LCD.Cursor.y;
							LCD.Font.Backcolor=YELLOW;
					}
				 if(LCD.Cursor.y > LCD.Hight - LCD.Font.Hight) 
				 {
							LCD.Cursor.x=0;LCD.Cursor.y=0;
		//				LCD_Clear(WHITE);
							return ch;  //直接退出
				 }
				 LCD_ShowChar(LCD.Cursor.x,LCD.Cursor.y,ch,LCD.Font.Color); 	//打印字符ch
				 if(LCD.Cursor.y==y)
				 {
						LCD.Font.Backcolor=YELLOW;
				 }
				 else
				 {
						LCD.Font.Backcolor=LCD.Backgroundcolor;
				 }
				 LCD.Cursor.x += LCD.Font.Width; 											//跳转到下一个位置, 是否越界有上面函数判断			
			}
			else
			{
					if(ch == '\n')    //换行
					{
							LCD.Cursor.x = 0;
							LCD.Cursor.y+= LCD.Font.Hight;
							return ch;
					}
					if(LCD.Cursor.x > (LCD.Width - LCD.Font.Width) )
					{
							LCD.Cursor.x = 0; 	//x置零
							LCD.Cursor.y += LCD.Font.Hight;  //y移至下一行
					}
				 if(LCD.Cursor.y > LCD.Hight - LCD.Font.Hight) 
				 {
							LCD.Cursor.x=0;LCD.Cursor.y=0;
		//					LCD_Clear(WHITE);
							return ch;  //直接退出
				 }
				 LCD_ShowChar(LCD.Cursor.x,LCD.Cursor.y,ch,LCD.Font.Color); 	//打印字符ch
				 LCD.Cursor.x += LCD.Font.Width; 											//跳转到下一个位置, 是否越界有上面函数判断
		 }

		 return ch;
}
#else
int fputc(int ch, FILE *f)
{         
			if(ch == '\n')    //换行
			{
					LCD.Cursor.x = 0;
					LCD.Cursor.y  += LCD.Font.Hight;
					return ch;
			}
			if(LCD.Cursor.x > LCD.Width -LCD.Font.Width) 
			{
					LCD.Cursor.x = 0; 	//x置零
					LCD.Cursor.y += LCD.Font.Hight;  //y移至下一行
			}
			 if(LCD.Cursor.y > LCD.Hight - LCD.Font.Hight) 
			 {
						LCD.Cursor.x=0;
						LCD.Cursor.y=0;
						LCD_Clear(WHITE);
						return ch;  //直接退出
			 }
			LCD_ShowChar(LCD.Cursor.x,LCD.Cursor.y,ch,LCD.Font.Color);; 	//打印字符ch
			LCD.Cursor.x += LCD.Font.Width; 				//跳转到下一个位置, 是否越界有上面函数判断

		 return ch;
}
#endif
/**
	*
	* @brief  写半行
	* @param 	format：	格式
	* @param 	...：		可变参数
  * @retval 无	
	*	@attention 用法同printf
	*
  */
static void LCD_WriteHalfLine(const char *format,...)
{
		va_list ap;
		va_start(ap,format);
	
		if(LCD.Cursor.x<(LCD.Width/2))
		{
				vprintf(format,ap);
				LCD.Cursor.x=LCD.Width/2;
		}
		else
		{
				LCD.Cursor.x=(LCD.Width/2);
				vprintf(format,ap);
				LCD.Cursor.x=LCD.Font.Width;
				LCD.Cursor.y+=LCD.Font.Hight;
		}
		va_end(ap);
}
/**
	*
	* @brief  写一行
	* @param 	format：	格式
	* @param 	...：		可变参数
  * @retval 无	
	*	@attention 用法同printf，会自动换行
	*
  */
static void LCD_WriteLine(const char *format,...)
{
		va_list(ap);
		va_start(ap,format);
	
		vprintf(format, ap);
	
		LCD.Cursor.x=0;
		LCD.Cursor.y+=LCD.Font.Hight;

		va_end(ap);
}
#if 0
/**
	*
	* @brief  写第X行
	* @param 	format：	格式
	* @param 	...：		可变参数
  * @retval 无	
	*	@attention 固定写第X行,不支持自动换行，字符越界会高亮闪烁提示。
	*
  */
static void LCD_WriteXLine(uint8_t linex,const char *format,...)
{	
		va_list(ap);
		va_start(ap,format);
	
		if(linex)
		LCD.Cursor.y=linex*(LCD.XLine.Interval+LCD.XLine.Width);
		else
		LCD.Cursor.y=0;
		
		uint8_t interval=(LCD.XLine.Interval-LCD.Font.Hight)/2;
		uint16_t xs=LCD.Cursor.y+LCD.XLine.Width;
		LCD_Fill(0,xs,LCD.Width,xs+LCD.XLine.Interval,LCD.Backgroundcolor);
		LCD_DrawHLine(0,LCD.Cursor.y,LCD.Width,LCD.XLine.Width,LCD.XLine.Color);
		LCD.Cursor.y+=LCD.XLine.Width;
		LCD.Cursor.y+=interval;
		LCD.Cursor.x=0;

		LCD.Font.PrintState=usingWriteXLine;
		vprintf(format,ap);
		LCD.Font.PrintState=usingNone;
		
		LCD.Cursor.y+=LCD.Font.Hight;
		
		LCD.Cursor.x=0;
		LCD_DrawHLine(0,LCD.Cursor.y+interval,LCD.Width,LCD.XLine.Width,LCD.XLine.Color);
		va_end(ap);	
}
#else
/**
	*
	* @brief  写第X行
	* @param 	format：	格式
	* @param 	...：		可变参数
  * @retval 无	
	*	@attention 固定写第X行,不支持自动换行，字符越界会高亮闪烁提示。
	*
  */
static void LCD_WriteXLine(uint8_t linex,const char *format,...)
{	
		va_list(ap);
		va_start(ap,format);
	
		LCD.Cursor.y=linex*(LCD.Font.Hight);

		vprintf(format,ap);
		
		LCD.Cursor.y+=LCD.Font.Hight;
		LCD.Cursor.x=0;

		va_end(ap);	
}
#endif
#if USING_FUNCTION_ENCAPSULATION
/*																																																				*/
/**
	*
	* @brief  LCD测试
	* @param 	无
  * @retval 无	
	*
  */
void LCD_Test(void)
{
		LCD.Init();       
		LCD.Debug.Clear(WHITE);
		
		LCD.Show.Num(0,1,1,BLACK);
		LCD.Show.Str(1,1,"#include",YELLOW);
		LCD.Show.Str(9,1,"<stdio.h>",PURPLE);
		
		LCD.Show.Num(0,2,2,BLACK);
		LCD.Show.Str(1,2,"int",RED);
		LCD.Show.Str(5,2,"main()",BLACK);
		
		LCD.Show.Num(0,3,3,BLACK);
		LCD.Show.Char(1*LCD.Font.Width,LCD.Font.Hight*3,'{',RED);
		
		LCD.Show.Num(0,4,3,BLACK);
		LCD.Show.Str(2,4,"Printf(",BLACK);
		LCD.Show.Char(9*LCD.Font.Width,LCD.Font.Hight*4,'"',PURPLE);
		LCD.Show.Str(10,4,"Hello,World!",PURPLE);
		LCD.Show.Char(21*LCD.Font.Width,LCD.Font.Hight*4,'"',PURPLE);
		LCD.Show.Str(22,4,");",BLACK);
		
		LCD.Write.Line("4 return");
		LCD.Show.Num(9,5,0,BLUE);
		LCD.Show.Char(10*LCD.Font.Width,LCD.Font.Hight*5,';',BLACK);

		LCD.Show.Num(0,6,5,BLACK);
		LCD.Show.Char(1*LCD.Font.Width,LCD.Font.Hight*6,'}',RED);	

		LCD.Draw.Hline(0,0,LCD.Width,2,BLUE);
		LCD.Draw.Hline(0,LCD.Hight/2-10,LCD.Width,2,BLUE);
		LCD.Draw.Vline(LCD.Width/2,LCD.Hight/2,LCD.Hight/2-LCD.Font.Hight,1,PURPLE);

		LCD.Draw.Sqr(1,LCD.Hight/2,LCD.Width-1,LCD.Hight-5,YELLOW);	
		
		LCD.Debug.SetFontColor(GREEN);
		LCD.Debug.SetCursor(10*LCD.Font.Width,11*LCD.Font.Hight);
		LCD.Write.Line("//%d",-1234);

		LCD.Debug.SetCursor(10*LCD.Font.Width,12*LCD.Font.Hight);
		LCD.Printf("%s","//#C");

		LCD.Debug.SetCursor(10*LCD.Font.Width,13*LCD.Font.Hight);
		LCD.Write.HalfLine("//%.3f",1.23);
		
		LCD.Write.Line("\n//Dog Rui");
		LCD.Write.Line("//Dog Rui");
		
		LCD.Write.HalfLine("//Doge");
		LCD.Write.HalfLine("//Doge");
		
		LCD.Draw.Circle(30,95,10,BLUE);
}
#endif
/*					ASCII字符编码						*/
unsigned char Font_code8[][6] = {
  {0x00,0x00,0x00,0x00,0x00,0x00},// (0)
  {0x00,0x00,0x00,0x4F,0x00,0x00},//!(1)
  {0x00,0x00,0x07,0x00,0x07,0x00},//"(2)
  {0x00,0x14,0x7F,0x14,0x7F,0x14},//#(3)
  {0x00,0x24,0x2A,0x7F,0x2A,0x12},//$(4)
  {0x00,0x23,0x13,0x08,0x64,0x62},//%(5)
  {0x00,0x36,0x49,0x55,0x22,0x50},//&(6)
  {0x00,0x00,0x05,0x03,0x00,0x00},//'(7)
  {0x00,0x00,0x1C,0x22,0x41,0x00},//((8)
  {0x00,0x00,0x41,0x22,0x1C,0x00},//)(9)
  {0x00,0x14,0x08,0x3E,0x08,0x14},//*(10)
  {0x00,0x08,0x08,0x3E,0x08,0x08},//+(11)
  {0x00,0x00,0x50,0x30,0x00,0x00},//,(12)
  {0x00,0x08,0x08,0x08,0x08,0x08},//-(13)
  {0x00,0x00,0x60,0x60,0x00,0x00},//.(14)
  {0x00,0x20,0x10,0x08,0x04,0x02},///(15)
  {0x00,0x3E,0x51,0x49,0x45,0x3E},//0(16)
  {0x00,0x00,0x42,0x7F,0x40,0x00},//1(17)
  {0x00,0x42,0x61,0x51,0x49,0x46},//2(18)
  {0x00,0x21,0x41,0x45,0x4B,0x31},//3(19)
  {0x00,0x18,0x14,0x12,0x7F,0x10},//4(20)
  {0x00,0x27,0x45,0x45,0x45,0x39},//5(21)
  {0x00,0x3C,0x4A,0x49,0x49,0x30},//6(22)
  {0x00,0x01,0x71,0x09,0x05,0x03},//7(23)
  {0x00,0x36,0x49,0x49,0x49,0x36},//8(24)
  {0x00,0x06,0x49,0x49,0x29,0x1E},//9(25)
  {0x00,0x00,0x36,0x36,0x00,0x00},//:(26)
  {0x00,0x00,0x56,0x36,0x00,0x00},//;(27)
  {0x00,0x08,0x14,0x22,0x41,0x00},//<(28)
  {0x00,0x14,0x14,0x14,0x14,0x14},//=(29)
  {0x00,0x00,0x41,0x22,0x14,0x08},//>(30)
  {0x00,0x02,0x01,0x51,0x09,0x06},//?(31)
  {0x00,0x32,0x49,0x79,0x41,0x3E},//@(32)
  {0x00,0x7E,0x11,0x11,0x11,0x7E},//A(33)
  {0x00,0x7F,0x49,0x49,0x49,0x3E},//B(34)
  {0x00,0x3E,0x41,0x41,0x41,0x22},//C(35)
  {0x00,0x7F,0x41,0x41,0x22,0x1C},//D(36)
  {0x00,0x7F,0x49,0x49,0x49,0x41},//E(37)
  {0x00,0x7F,0x09,0x09,0x09,0x01},//F(38)
  {0x00,0x3E,0x41,0x49,0x49,0x7A},//G(39)
  {0x00,0x7F,0x08,0x08,0x08,0x7F},//H(40)
  {0x00,0x00,0x41,0x7F,0x41,0x00},//I(41)
  {0x00,0x20,0x40,0x41,0x3F,0x01},//J(42)
  {0x00,0x7F,0x08,0x14,0x22,0x41},//K(43)
  {0x00,0x7F,0x40,0x40,0x40,0x40},//L(44)
  {0x00,0x7F,0x02,0x04,0x02,0x7F},//M(45)
  {0x00,0x7F,0x04,0x08,0x10,0x7F},//N(46)
  {0x00,0x3E,0x41,0x41,0x41,0x3E},//O(47)
  {0x00,0x7F,0x09,0x09,0x09,0x06},//P(48)
  {0x00,0x3E,0x41,0x51,0x21,0x5E},//Q(49)
  {0x00,0x7F,0x09,0x19,0x29,0x46},//R(50)
  {0x00,0x46,0x49,0x49,0x49,0x31},//S(51)
  {0x00,0x01,0x01,0x7F,0x01,0x01},//T(52)
  {0x00,0x3F,0x40,0x40,0x40,0x3F},//U(53)
  {0x00,0x1F,0x20,0x40,0x20,0x1F},//V(54)
  {0x00,0x3F,0x40,0x38,0x40,0x3F},//W(55)
  {0x00,0x63,0x14,0x08,0x14,0x63},//X(56)
  {0x00,0x03,0x04,0x78,0x04,0x03},//Y(57)
  {0x00,0x61,0x51,0x49,0x45,0x43},//Z(58)
  {0x00,0x00,0x7F,0x41,0x41,0x00},//[(59)
  {0x00,0x15,0x16,0x7C,0x16,0x15},//\(60)
  {0x00,0x00,0x41,0x41,0x7F,0x00},//](61)
  {0x00,0x04,0x02,0x01,0x02,0x04},//^(62)
  {0x00,0x40,0x40,0x40,0x40,0x40},//_(63)
  {0x00,0x00,0x01,0x02,0x04,0x00},//`(64)
  {0x00,0x20,0x54,0x54,0x54,0x78},//a(65)
  {0x00,0x7F,0x48,0x44,0x44,0x38},//b(66)
  {0x00,0x38,0x44,0x44,0x44,0x20},//c(67)
  {0x00,0x38,0x44,0x44,0x48,0x7F},//d(68)
  {0x00,0x38,0x54,0x54,0x54,0x18},//e(69)
  {0x00,0x08,0x7E,0x09,0x01,0x02},//f(70)
  {0x00,0x0C,0x52,0x52,0x52,0x3E},//g(71)
  {0x00,0x7F,0x08,0x04,0x04,0x78},//h(72)
  {0x00,0x00,0x44,0x7D,0x40,0x00},//i(73)
  {0x00,0x20,0x40,0x44,0x3D,0x00},//j(74)
  {0x00,0x7F,0x10,0x28,0x44,0x00},//k(75)
  {0x00,0x00,0x41,0x7F,0x40,0x00},//l(76)
  {0x00,0x7E,0x02,0x0C,0x02,0x7C},//m(77)
  {0x00,0x7E,0x04,0x02,0x02,0x7C},//n(78)
  {0x00,0x38,0x44,0x44,0x44,0x38},//o(79)
  {0x00,0x7C,0x14,0x14,0x14,0x08},//p(80)
  {0x00,0x08,0x14,0x14,0x18,0x7C},//q(81)
  {0x00,0x7C,0x08,0x04,0x04,0x08},//r(82)
  {0x00,0x48,0x54,0x54,0x54,0x20},//s(83)
  {0x00,0x04,0x3F,0x44,0x40,0x20},//t(84)
  {0x00,0x3C,0x40,0x40,0x20,0x7C},//u(85)
  {0x00,0x1C,0x20,0x40,0x20,0x1C},//v(86)
  {0x00,0x3C,0x40,0x30,0x40,0x3C},//w(87)
  {0x00,0x44,0x28,0x10,0x28,0x44},//x(88)
  {0x00,0x0C,0x50,0x50,0x50,0x3C},//y(89)
  {0x00,0x44,0x64,0x54,0x4C,0x44},//z(90)
  {0x00,0x00,0x08,0x36,0x41,0x00},//{(91)
  {0x00,0x00,0x00,0x7F,0x00,0x00},//|(92)
  {0x00,0x00,0x41,0x36,0x08,0x00},//}(93)
  {0x00,0x08,0x04,0x08,0x10,0x08},//~(94)
  {0x00,0x08,0x08,0x2A,0x1C,0x08},//→(127)
  {0x00,0x08,0x1C,0x2A,0x08,0x08},//←(128)
  {0x00,0x04,0x02,0x7F,0x02,0x04},//↑(129)
  {0x00,0x10,0x20,0x7F,0x20,0x10},//↓(130)
  {0x00,0x1C,0x2A,0x32,0x2A,0x1C},//笑面(131)
  {0x00,0x1C,0x22,0x44,0x22,0x1C}};//爱心(132)   
#endif