#include "include.h"
#include "ads1292_driver.h"

u8 ADS1292_REG[12];		//ads1292寄存器数组
ADS1292_CONFIG1 	Ads1292_Config1		={DATA_RATE};																				//CONFIG1
ADS1292_CONFIG2 	Ads1292_Config2		={PDB_LOFF_COMP,PDB_REFBUF,ADS1292_VREF,CLK_EN,INT_TEST};		//CONFIG2
ADS1292_CHSET 		Ads1292_Ch1set		={CNNNLE1_POWER,CNNNLE1_GAIN,CNNNLE1_MUX};					//CH1SET
ADS1292_CHSET 		Ads1292_Ch2set		={CNNNLE2_POWER,CNNNLE2_GAIN,CNNNLE2_MUX};					//CH2SET
ADS1292_RLD_SENS	Ads1292_Rld_Sens	={PDB_RLD,RLD_LOFF_SENSE,RLD2N,RLD2P,RLD1N,RLD1P};	//RLD_SENS
ADS1292_LOFF_SENS	Ads1292_Loff_Sens	={FLIP2,FLIP1,LOFF2N,LOFF2P,LOFF1N,LOFF1P};					//LOFF_SENS
ADS1292_RESP1			Ads1292_Resp1			={RESP_DEMOD_EN1,RESP_MOD_EN,RESP_PH,RESP_CTRL};		//RSP1
ADS1292_RESP2			Ads1292_Resp2			={CALIB,FREQ,RLDREF_INT};														//RSP2	


//设置寄存器数组
void ADS1292_SET_REGBUFF(void)
{
	ADS1292_REG[ADS1292R_ID] =	ADS1292_DEVICE;//ID只读
	 
	ADS1292_REG[CONFIG1] =	0x00;		//0000 0aaa	[7] 0连续转换模式  [6:3] 必须为0 
	ADS1292_REG[CONFIG1] |=	Ads1292_Config1.Data_Rate;//[2:0] aaa 采样率设置采样率

	ADS1292_REG[CONFIG2] =	0x00;		//1abc d0e1	[7] 必须为1  [2] 必须为0  [0] 设置测试信号为1HZ、±1mV方波 
	ADS1292_REG[CONFIG2] |=	Ads1292_Config2.Pdb_Loff_Comp<<6;	//[6]a 导联脱落比较器是否掉电
	ADS1292_REG[CONFIG2] |=	Ads1292_Config2.Pdb_Refbuf<<5;		//[5]b 内部参考缓冲器是否掉电
	ADS1292_REG[CONFIG2] |=	Ads1292_Config2.Vref<<4;					//[4]c 内部参考电压设置，默认2.42V
	ADS1292_REG[CONFIG2] |=	Ads1292_Config2.Clk_EN<<3;				//[3]d CLK引脚输出时钟脉冲？
	ADS1292_REG[CONFIG2] |=	Ads1292_Config2.Int_Test<<1;			//[1]e 是否打开内部测试信号,
	ADS1292_REG[CONFIG2] |=	0x81;//设置默认位
	
	ADS1292_REG[LOFF] =	0x10;//[7:5]	设置导联脱落比较器阈值 [4]	必须为1 		[3:2] 导联脱落电流幅值		[1]	必须为0	[0]	导联脱落检测方式 0 DC 1 AC 

	ADS1292_REG[CH1SET] =	0x00;	 //abbb cccc
	ADS1292_REG[CH1SET] |=Ads1292_Ch1set.PD<<7;		//[7]  a 		通道1断电？
	ADS1292_REG[CH1SET] |=Ads1292_Ch1set.GAIN<<4;	//[6:4]bbb	设置PGA增益
	ADS1292_REG[CH1SET] |=Ads1292_Ch1set.MUX;			//[3:0]cccc	设置通道1输入方式

	ADS1292_REG[CH2SET] =	0x00;	//abbb cccc
	ADS1292_REG[CH2SET] |=Ads1292_Ch2set.PD<<7;		//[7]  a 		通道2断电？
	ADS1292_REG[CH2SET] |=Ads1292_Ch2set.GAIN<<4;	//[6:4]bbb	设置PGA增益
	ADS1292_REG[CH2SET] |=Ads1292_Ch2set.MUX;			//[3:0]cccc	设置通道2输入方式
	
	ADS1292_REG[RLD_SENS] = 0X00; //11ab cdef	[7:6] 11 PGA斩波频率	fMOD/4 
	ADS1292_REG[RLD_SENS] |=Ads1292_Rld_Sens.Pdb_Rld<<5;					//[5]a	该位决定RLD缓冲电源状态
	ADS1292_REG[RLD_SENS] |=Ads1292_Rld_Sens.Rld_Loff_Sense<<4;	//[4]b	该位使能RLD导联脱落检测功能
	ADS1292_REG[RLD_SENS] |=Ads1292_Rld_Sens.Rld2N<<3;						//[3]c	这个位控制通道2负输入	用于右腿驱动的输出
	ADS1292_REG[RLD_SENS] |=Ads1292_Rld_Sens.Rld2P<<2;						//[2]d	该位控制通道2正输入		用于右腿驱动的输出
	ADS1292_REG[RLD_SENS] |=Ads1292_Rld_Sens.Rld1N<<1;						//[1]e	这个位控制通道1负输入	用于右腿驱动的输出
	ADS1292_REG[RLD_SENS] |=Ads1292_Rld_Sens.Rld1P;							//[0]f	该位控制通道1正输入		用于右腿驱动的输出	
	ADS1292_REG[RLD_SENS] |=	0xc0;//设置默认位

	ADS1292_REG[LOFF_SENS] = 0X00;  //00ab cdef	[7:6] 必须为0
	ADS1292_REG[LOFF_SENS] |=Ads1292_Loff_Sens.Flip2<<5;		//[5]a	这个位用于控制导联脱落检测通道2的电流的方向
	ADS1292_REG[LOFF_SENS] |=Ads1292_Loff_Sens.Flip1<<4;		//[4]b	这个位控制用于导联脱落检测通道1的电流的方向
	ADS1292_REG[LOFF_SENS] |=Ads1292_Loff_Sens.Loff2N<<3;	//[3]c	该位控制通道2负输入端的导联脱落检测
	ADS1292_REG[LOFF_SENS] |=Ads1292_Loff_Sens.Loff2P<<2;	//[2]d	该位控制通道2正输入端的导联脱落检测
	ADS1292_REG[LOFF_SENS] |=Ads1292_Loff_Sens.Loff1N<<1;	//[1]e	该位控制通道1负输入端的导联脱落检测
	ADS1292_REG[LOFF_SENS] |=Ads1292_Loff_Sens.Loff1P;			//[0]f	该位控制通道1正输入端的导联脱落检测
	
	ADS1292_REG[LOFF_STAT] =	0x00;		//[6]0 设置fCLK和fMOD之间的模分频比 fCLK=fMOD/4  [4:0]只读，导联脱落和电极连接状态
	
	ADS1292_REG[RESP1] = 0X00;//abcc cc1d
	ADS1292_REG[RESP1] |=Ads1292_Resp1.RESP_DemodEN<<7;//[7]a		这个位启用和禁用通道1上的解调电路		
	ADS1292_REG[RESP1] |=Ads1292_Resp1.RESP_modEN<<6;	//[6]b		这个位启用和禁用通道1上的调制电路	
	ADS1292_REG[RESP1] |=Ads1292_Resp1.RESP_ph<<2;			//[5:2]c	这些位控制呼吸解调控制信号的相位	
	ADS1292_REG[RESP1] |=Ads1292_Resp1.RESP_Ctrl;			//[0]d		这个位设置呼吸回路的模式
	ADS1292_REG[RESP1] |=	0x02;//设置默认位	
	
	ADS1292_REG[RESP2] = 0x00; //a000 0bc1	[6:3]必须为0 [0]必须为1
	ADS1292_REG[RESP2] |=	Ads1292_Resp2.Calib<<7;				//[7]a 启动通道偏移校正？
	ADS1292_REG[RESP2] |=	Ads1292_Resp2.freq<<2;				//[2]b 呼吸频率设置
	ADS1292_REG[RESP2] |=	Ads1292_Resp2.Rldref_Int<<1;	//[1]c RLDREF信号源外部馈电？
	ADS1292_REG[RESP2] |= 0X01;//设置默认位	
 
	ADS1292_REG[GPIO] =	0x0C;			//GPIO设为输入		[7:4]必须为0	 [3:2]11 GPIO为输入 [1:0] 设置输入时，指示引脚电平，设置输出时控制引脚电平
}

//寄存器数组写入寄存器
u8 ADS1292_WRITE_REGBUFF(void)
{
		u8 i,res=0;
		u8 REG_Cache[12] = {0,0,0,0,0,0,0,0,0,0,0,0};	//存储寄存器数据
		ADS1292_SET_REGBUFF();//设置寄存器数组		
		ADS1292_WR_REGS(WREG|CONFIG1,11,ADS1292_REG+1);//数组变量写入寄存器
		systime.delay_ms(10);		
		ADS1292_WR_REGS(RREG|ADS1292R_ID,12,REG_Cache);//读寄存器
		systime.delay_ms(10);	
		
//	#ifdef DEBUG_ADS1292	
//		LCD.Write.XLine(0,"WRITE REG:\r\n");
//		for(i=0;i<12;i++	)//要写的数据								
//		LCD.Write.XLine(0,"%d %d\r\n",i,ADS1292_REG[i]);	
//		LCD.Write.XLine(0,"READ REG:\r\n");
//	#endif	
	
	
		for(i=0;i<12;i++	)	//检查寄存器	
		{						
				if(ADS1292_REG[i] != REG_Cache[i])
				{
						if(i!= 0 && i!=8 && i != 11)	//0 8 和11是ID 导联脱落和GPIO相关
								res=1;
						else
								continue;
				}					
//			#ifdef DEBUG_ADS1292
//				LCD.Write.XLine(0,"%d %x\r\n",i,REG_Cache[i]); //读到的数据			
//			#endif
		}	

//		#ifdef DEBUG_ADS1292	
//			if(res == 0)
//					LCD.Write.XLine(0,"REG write success\r\n");
//			else		
//					LCD.Write.XLine(0,"REG write err\r\n");
//		#endif
                
		return res;				
}

void ADS1292_PowerOnInit(void)
{	
		u8 i;
		u8 REG_Cache[12] = {0,0,0,0,0,0,0,0,0,0,0,0};	
	
//		ADS_CLKSEL=1;//启用内部时钟
		ADS1292_START=0; //停止数据输出	
		ADS1292_RESET=0; //复位
		systime.delay_ms(1000);
		ADS1292_RESET=1;//芯片上电，可以使用	
		systime.delay_ms(100);	//等待稳定
	
		ADS1292_Send_CMD(SDATAC);//发送停止连续读取数据命令
		systime.delay_ms(100);	
		ADS1292_Send_CMD(RESET);//复位
		systime.delay_ms(1000);		
		ADS1292_Send_CMD(SDATAC);//发送停止连续读取数据命令
		systime.delay_ms(100);		
	
//#ifdef DEBUG_ADS1292	
                
		ADS1292_WR_REGS(RREG|ADS1292R_ID,12,REG_Cache);
		LCD.Write.XLine(0,"read default REG:");
                
		for(i=0;i<12;i++)	//读默认寄存器
                  LCD.Write.XLine(i+1,"REG[%d]:0x%x",i,REG_Cache[i]);
		
//#endif
		//ADS1292_Send_CMD(STANDBY);//进入待机模式	
}

//设置通道1内部1mV测试信号
u8 ADS1292_Single_Test(void) //注意1292R开了呼吸解调，会对通道一的内部测试信号波形造成影响，这里只参考通道2即可，1292不受影响
{
		u8 res=0;
		Ads1292_Config2.Int_Test = INT_TEST_ON;//打开内部测试信号
		Ads1292_Ch1set.MUX=MUX_Test_signal;//测试信号输入	
		Ads1292_Ch2set.MUX=MUX_Test_signal;//测试信号输入	
		
		if(ADS1292_WRITE_REGBUFF())//写入寄存器
				res=1;	
		systime.delay_ms(10);			
		return res;		
}
//设置内部噪声测试
u8 ADS1292_Noise_Test(void)
{
		u8 res=0;
		Ads1292_Config2.Int_Test = INT_TEST_OFF;//关内部测试信号
		Ads1292_Ch1set.MUX = MUX_input_shorted;//输入短路	
		Ads1292_Ch2set.MUX = MUX_input_shorted;//输入短路	

		if(ADS1292_WRITE_REGBUFF())//写入寄存器
				res=1;	
		systime.delay_ms(10);			
		return res;			
}

//正常信号采集模式
u8 ADS1292_Single_Read(void)
{
		u8 res=0;
		Ads1292_Config2.Int_Test = INT_TEST_OFF;//关内部测试信号
		Ads1292_Ch1set.MUX = MUX_Normal_input;//普通电极输入
		Ads1292_Ch2set.MUX = MUX_Normal_input;//普通电极输入
	
		if(ADS1292_WRITE_REGBUFF())//写入寄存器
				res=1;
		systime.delay_ms(10);		
		return res;		
}

//配置ads1292采集方式
u8 Set_ADS1292_Collect(u8 mode)
{
		u8 res;
		
		systime.delay_ms(10);	
		switch(mode)//设置采集方式
		{
				case 0:
					res =ADS1292_Single_Read();												
				break;
				case 1:
					res =ADS1292_Single_Test();											
				break;
				case 2:
					res =ADS1292_Noise_Test();											
				break;
		}		
		if(res)return 1;//寄存器设置失败		
		ADS1292_Send_CMD(RDATAC); //启动连续模式
		systime.delay_ms(10);		
		ADS1292_Send_CMD(START);	//发送开始数据转换（等效于拉高START引脚）	
		systime.delay_ms(10);		
		return 0;
}
u8 ADS1292_Read_Data(u8 *data)//72M时钟下函数耗时大约10us  8M时钟下 函数耗时大约 100us
{		
		u8 i;	
		
		//ADS_CS=0;//读9个字节的数据
		//delay_us(10);
		for(i=0;i<9;i++)
		{	
				*data=ADS1292_SPI(0X00);	
				data++;
		}
		//delay_us(10);
		//ADS_CS=1;		
		return 0;
}
int32_t ADS1292_Get_Volt(uint32_t num)
{		
	int32_t temp;			
	temp = num;
	temp <<= 8;
	temp >>= 8;
	return temp;
}

void ADS1292_Init(void) 
{		
          GPIO_PinInit(ADS1292_START_PIN,GPO,1);
          GPIO_PinInit(ADS1292_RESET_PIN,GPO,1);
          GPIO_PinInit(ADS1292_DRDY_PIN,GPI,1);
          GPIO_PinInit(ADS1292_SPI_CS_PIN,GPO,0);
  
          SPI_Init(ADS1292_SPIx,ADS1292_SPI_PCS,MASTER,ADS1292_SPI_MODE,ADS1292_SPI_BAUD);		
		
          ADS1292_PowerOnInit();//上电复位，进入待机模式	

          while(Set_ADS1292_Collect(0))//0 正常采集  //1 1mV1Hz内部侧试信号 //2 内部短接噪声测试
          {	
              //LCD.Debug.Clear(WHITE);
              LCD.Write.XLine(13,"Set Reg Failed.");
              systime.delay_ms(50);	
          }
          LCD.Write.XLine(13,"Set Reg Success.");
          
          //systime.delay_ms(5000);
}
uint32_t ADS1292_ReadEGCData(uint8_t ch)
{
   uint32_t cannle[2] = {0,0};
   int32_t p_Temp[2] = {0,0};
   
   ADS1292_Read_Data(ADS1292.Cache);
   
   cannle[0]=ADS1292.Cache[3]<<16 | ADS1292.Cache[4]<<8 | ADS1292.Cache[5];//获取原始数据		
   cannle[1]=ADS1292.Cache[6]<<16 | ADS1292.Cache[7]<<8 | ADS1292.Cache[8];
						
   p_Temp[0] = ADS1292_Get_Volt(cannle[0]);	//把采到的3个字节转成有符号32位数
   p_Temp[1] = ADS1292_Get_Volt(cannle[1]);	//把采到的3个字节转成有符号32位数
					
						//有符号数为再转为无符号，无符号数为逻辑右移
   ADS1292.Channle[0] = p_Temp[0];
   ADS1292.Channle[1] = p_Temp[1];
   
   ADS1292.Data = ADS1292.Channle[0] << 32 + ADS1292.Channle[1];
   
   for(int i = 0;i<2;i++)
      LCD.Write.XLine(i+3,"Data[%d]:%lu",i,ADS1292.Channle[i]);
   
   LCD.Write.XLine(7,"Data[3]:%lu",ADS1292.Data);
   
   return ((ch == 2)?(ADS1292.Channle[1]):(ADS1292.Channle[0]));
}
  
void ADS1292_Test(u8 mode)
{
    ADS1292_Init();
    while(Set_ADS1292_Collect(mode))//0 正常采集  //1 1mV1Hz内部侧试信号 //2 内部短接噪声测试
    {	
        //LCD.Debug.Clear(WHITE);
        LCD.Write.XLine(13,"Set Reg Failed.");
	systime.delay_ms(50);	
    }
    LCD.Write.XLine(13,"Set Reg Success.");
    systime.delay_ms(5000);
}

ads1292_t ADS1292;
