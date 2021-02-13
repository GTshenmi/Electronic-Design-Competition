#include "include.h"
#include "ads1292_spi.h"

uint8_t SPI_ReadWriteByte(uint8_t com)
{
    uint8_t ReceiveData = 0;
    
    SPI_ReadWrite(ADS1292_SPIx, ADS1292_SPI_PCS,&com,&ReceiveData,1);
    
    return ReceiveData;
}

//ͨ��SPI������ADS1292ͨ��
u8 ADS1292_SPI(u8 com)
{	
	return SPI_ReadWriteByte(com);
}
//д����
void ADS1292_Send_CMD(u8 data)
{
		//ADS1292_SPI_CS=0;
		systime.delay_us(100);
		ADS1292_SPI(data);		
		systime.delay_us(100);	
		//ADS1292_SPI_CS=1;
}


/*ADS1291��ADS1292��ADS1292R���нӿ����ֽ���ʽ���������Ҫ4��tCLK�����������ִ��.
��ˣ��ڷ��Ͷ��ֽ�����ʱ��4 tCLK���ڱ��뽫һ���ֽ�(�������)�Ľ�������һ���ֽ�(�������)�ֿ���
����CLK��ʱ�ӣ�Ϊ512 kHz����tSDECODE (4 tCLK)Ϊ7.8125 us��
��SCLK���������ʣ�Ϊ16mhzʱ��һ���ֽڿ�����500ns�д��䣬���ֽڴ���ʱ�䲻����tSDECODE�淶;
��ˣ��������һ���ӳ٣��Ա�ڶ����ֽڵ�ĩβ����7.3125us���
���SCLKΪ1 MHz������8u���ڴ���һ���ֽڡ����ڴ˴���ʱ�䳬��tSDECODE�淶�����������Բ��ӳٵط��ͺ����ֽڡ�
�ں���ĳ����У����ԶԴ��ж˿ڽ��б�̣�ʹ���ÿ��ѭ���ĵ��ֽڴ���ת�Ƶ�����ֽ�*/

//��д����Ĵ���
void ADS1292_WR_REGS(u8 reg,u8 len,u8 *data)
{
		u8 i;
		//ADS1292_SPI_CS=0;	
		systime.delay_us(100);
		ADS1292_SPI(reg);
		systime.delay_us(100);
		ADS1292_SPI(len-1);
		if(reg&0x40) //д
		{
				for(i=0;i<len;i++)
				{
						systime.delay_us(100);		
						ADS1292_SPI(*data);
						data++;				
				}			
		}
		else //��		
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

////��ȡ72λ������1100+LOFF_STAT[4:0]+GPIO[1:0]+13��0+2CHx24λ����9�ֽ�
////	1100	LOFF_STAT[4			3			2			1			0	]	//����������ص���Ϣ��LOFF_STAT�Ĵ�����
////									RLD		1N2N	1N2P	1N1N	1N1P	
////	��	C0 00 00 FF E1 1A FF E1 52	
//
//u8 ADS1292_Read_Data(u8 *data)//72Mʱ���º�����ʱ��Լ10us  8Mʱ���� ������ʱ��Լ 100us
//{		
//		u8 i;	
//		
//		//ADS1292_SPI_CS=0;//��9���ֽڵ�����
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