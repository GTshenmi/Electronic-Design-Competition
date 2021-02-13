#include "include.h"
#include "ads1292_spi.h"

uint8_t SPI_ReadWriteByte(uint8_t com)
{
    uint8_t ReceiveData = 0;
    
    SPI_ReadWrite(ADS1292_SPIx, ADS1292_SPI_PCS,&com,&ReceiveData,1);
    
    return ReceiveData;
}

//通过SPI总线与ADS1292通信
u8 ADS1292_SPI(u8 com)
{	
	return SPI_ReadWriteByte(com);
}
//写命令
void ADS1292_Send_CMD(u8 data)
{
		//ADS1292_SPI_CS=0;
		systime.delay_us(100);
		ADS1292_SPI(data);		
		systime.delay_us(100);	
		//ADS1292_SPI_CS=1;
}


/*ADS1291、ADS1292和ADS1292R串行接口以字节形式解码命令，需要4个tCLK周期来解码和执行.
因此，在发送多字节命令时，4 tCLK周期必须将一个字节(或操作码)的结束与下一个字节(或操作码)分开。
假设CLK（时钟）为512 kHz，则tSDECODE (4 tCLK)为7.8125 us。
当SCLK（数据速率）为16mhz时，一个字节可以在500ns中传输，此字节传输时间不符合tSDECODE规范;
因此，必须插入一个延迟，以便第二个字节的末尾晚于7.3125us到达。
如果SCLK为1 MHz，则在8u秒内传输一个字节。由于此传输时间超过tSDECODE规范，处理器可以不延迟地发送后续字节。
在后面的场景中，可以对串行端口进行编程，使其从每个循环的单字节传输转移到多个字节*/

//读写多个寄存器
void ADS1292_WR_REGS(u8 reg,u8 len,u8 *data)
{
		u8 i;
		//ADS1292_SPI_CS=0;	
		systime.delay_us(100);
		ADS1292_SPI(reg);
		systime.delay_us(100);
		ADS1292_SPI(len-1);
		if(reg&0x40) //写
		{
				for(i=0;i<len;i++)
				{
						systime.delay_us(100);		
						ADS1292_SPI(*data);
						data++;				
				}			
		}
		else //读		
		{
				for(i=0;i<len;i++)
				{
						systime.delay_us(100);		
						*data = ADS1292_SPI(0);
						data++;
				}
		}			
		systime.delay_us(100);	
		//ADS1292_SPI_CS=1;
}

////读取72位的数据1100+LOFF_STAT[4:0]+GPIO[1:0]+13个0+2CHx24位，共9字节
////	1100	LOFF_STAT[4			3			2			1			0	]	//导联脱落相关的信息在LOFF_STAT寄存器里
////									RLD		1N2N	1N2P	1N1N	1N1P	
////	例	C0 00 00 FF E1 1A FF E1 52	
//
//u8 ADS1292_Read_Data(u8 *data)//72M时钟下函数耗时大约10us  8M时钟下 函数耗时大约 100us
//{		
//		u8 i;	
//		
//		//ADS1292_SPI_CS=0;//读9个字节的数据
//		systime.delay_us(10);
//		for(i=0;i<9;i++)
//		{	
//				*data=ADS1292_SPI(0X00);	
//				data++;
//		}
//		systime.delay_us(10);
//		//ADS1292_SPI_CS=1;		
//		return 0;
//}