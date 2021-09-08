#include "include.h"
#include "fdc2214.h"
#define FDC_Address_W 0x54
#define FDC_Address_R 0x55

//#define FDC_Address_W 0x56
//#define FDC_Address_R 0x57

//sbit    IIC_SDA         =   P0^7;
//sbit    IIC_SCL         =   P0^6;

//#define IIC_SDA PTA19_OUT
//#define IIC_SCL PTB19_OUT

//#define IIC_SDA_IN PTA19_IN
//#define IIC_SDA_OUT PTA19_OUT

void FDC2214_Delayms(uint16_t ms)
{       
    systime.delay_ms(ms);
}
void FDC2214_Delayus(uint16_t us)
{
    systime.delay_us(us);
}


void I2C_start()
{
    IIC_SCL = 1;
    FDC2214_Delayus(10);
    IIC_SDA = 1;
    FDC2214_Delayus(10);
    IIC_SDA = 0;
    FDC2214_Delayus(10);
}

void I2C_stop()
{
    IIC_SDA = 0;
    FDC2214_Delayus(10);
    IIC_SCL = 1;
    FDC2214_Delayus(10);
    IIC_SDA = 1;
    FDC2214_Delayus(10);
}

/*ZHU send ACK*/
void Master_ACK(bool i)	
{
    IIC_SCL = 0; // allow IIC_SDA change
    FDC2214_Delayus(2);//  relax
		IIC_SDA=i;//i=1 ack, i=0 nack
    FDC2214_Delayus(2);// relax
    IIC_SCL = 1;// raise IIC_SCL, allow slave read ACK
    FDC2214_Delayus(2);
    IIC_SCL = 0;// pull down IIC_SCL and occupy bus
//    FDC2214_Delayus(5);
//    IIC_SDA = 1;//release IIC_SDA
//    FDC2214_Delayus(5);
}


void I2C_send_byte(unsigned char byte)
{
    unsigned char i;
    for(i = 0 ; i < 8 ; i++)
    {
        IIC_SCL = 0;			//allow communicate
        FDC2214_Delayus(5);
        if (byte & 0x80)		//From high to low
        {
            IIC_SDA = 1;
            FDC2214_Delayus(5);
        }
        else
        {
            IIC_SDA = 0;
            FDC2214_Delayus(5);
        }
        IIC_SCL = 1;
        FDC2214_Delayus(5);
        byte <<= 1;
    }
    IIC_SCL = 0;		//pull down IIC_SCL ,ready for next transfer

    FDC2214_Delayus(1);
    IIC_SDA = 1;		//release IIC_SDA,CONG control bus
    FDC2214_Delayus(1);
}

unsigned char I2C_wait_ack(void)
{
	unsigned char ucErrTime=0;   
	IIC_SDA=1;FDC2214_Delayus(1);	   
	IIC_SCL=1;FDC2214_Delayus(1);	 
        
        SDA_IN();
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			I2C_stop();
			return 1;
		}
	}
        SDA_OUT();
        
	IIC_SCL=0;	   
	return 0;  
}

unsigned char I2C_read_byte(bool mAck)
{
    unsigned char dat,i;
    
    IIC_SCL = 0;
    FDC2214_Delayus(5);
    IIC_SDA = 1;
    FDC2214_Delayus(5);
    
    SDA_IN();
    for(i = 0 ; i < 8 ; i++)
    {
        IIC_SCL = 1;		//while IIC_SCL is high,data is stable enough to receive
        FDC2214_Delayus(5);
        
        if (READ_SDA)
        {
            dat |= 0x01;//最低位置1
        }
        else
        {
            dat &=  0xfe;	//1111 1110最低位置0
        }
        FDC2214_Delayus(5);
        IIC_SCL = 0 ;
        FDC2214_Delayus(5);
        if(i < 7)
        {
            dat = dat << 1;
        }
    }
    SDA_OUT();
    Master_ACK(mAck);
    return(dat);
}






//fdc_config
//这里 FDC_Address_W =0x54
void FDC_write_reg(unsigned char addr,unsigned short value)   //addr 为寄存器地址，value为需要写入的寄存器数据 
{ 
	   I2C_start();                    //产生START信号
	   I2C_send_byte(FDC_Address_W);   //发送从机地址和写信号
	   I2C_wait_ack();                 //等待ACK
	   I2C_send_byte(addr);            //发送需要写入的寄存器地址
	   I2C_wait_ack();                 //等待ACK
	   I2C_send_byte(value>>8);        //发送高8位数据
	   I2C_wait_ack();                 //等待ACK
	   I2C_send_byte(value&0xFF);      //发送低8位数据
	   I2C_wait_ack();                 //等待ACK
           I2C_stop();                      //产生STOP信号
	   FDC2214_Delayms(1);
}

//FDC_Address_W =0x54
//FDC_Address_R =0x55
//Receive_Data[] 为接收数据的数组
//C_Data 为一个16位无符号的整型
unsigned short FDC_read_reg(unsigned char addr)
{
      unsigned char Receive_Data[2];
      I2C_start();                    //产生START信号
	    I2C_send_byte(FDC_Address_W);   //发送写命令
	    I2C_wait_ack();		
	    I2C_send_byte(addr);            //发送需要读的寄存器的地址
			I2C_wait_ack();
	
	     I2C_start();
	     I2C_send_byte(FDC_Address_R);  //发送读命令
	     I2C_wait_ack();
	     
	   // Receive_Data[0]=I2C_read_byte(0);  //读高8位并且ack

			
             Receive_Data[0]=I2C_read_byte(0);;
             Receive_Data[1]= I2C_read_byte(0); //读低8位 nack
	     I2C_stop();	                    //产生STOP信号

	    
		 return  (Receive_Data[0]<<8)+ Receive_Data[1];
}


void FDC_Start(void)  
{    
        uint16_t ID = 0,MID = 0;
        
        IIC_Init();
        
        FDC2214_Delayms(500);
        
        FDC_write_reg(0x08,0x8329);   //(CHx_RCOUNT*16)/55M ==9.76ms，,每10ms左右可以读一次值
	FDC_write_reg(0x09,0x8329);
        FDC_write_reg(0x0A,0x8329);	
	FDC_write_reg(0x0B,0x8329);
	
	FDC_write_reg(0x10,0x000A);  //设置4个通道最小稳定时间
	FDC_write_reg(0x11,0x000A);
	FDC_write_reg(0x12,0x000A);
	FDC_write_reg(0x13,0x000A);
	
        FDC_write_reg(0x14,0x1001); //时钟除以1，设置传感器频率在0.01M到8.5M之间
	FDC_write_reg(0x15,0x1001);
	FDC_write_reg(0x16,0x1001);
	FDC_write_reg(0x17,0x1001);
	
	FDC_write_reg(0x19,0x0000); //不设置中断标志位
	FDC_write_reg(0x1B,0xC20D);//使能0,1,2,3通道，且带宽设置为10M
 
	FDC_write_reg(0x1E,0x8000); //设置4个通道的驱动电流
        FDC_write_reg(0x1F,0x8000);
	FDC_write_reg(0x20,0x8000);
	FDC_write_reg(0x21,0x8000);
 
 	
	FDC_write_reg(0x1A,0x1401);	//使能FDC2214,且取内部时钟为参考时钟
        
        ID = FDC_read_reg(DEVICE_ID);
        MID = FDC_read_reg(MANUFACTURER_ID);
        
        if (ID != 0x3055 || MID != 0x5449)
          LED_ON(1);     
}
uint32_t FDC_Read_CH3()
{
    uint32_t data0=0,data1=0;
    uint32_t result = 0;
    
    data0 = FDC_read_reg(DATA_CH0);
    data1 = FDC_read_reg(DATA_LSB_CH0);
    
    data0 = data0 & 0x0FFF;
    
   // data1 = (data1 >> 4) & 0x0FFF ;
    result = data0<<16;
    result += data1;
    //result = data0<<16 + data1;
    
//    OLED_P6x8Str(0,3,"CH:");  
//    
//    OLED_PrintU16(18,3,data0);
//    OLED_PrintU16(18,4,data1);
    
    return result/1000;
}
uint32_t FDC_read_CHx(u8 CHx)	
{
	u8 reg_addr1 = 0;			 //MSB地址
	u8 reg_addr = 0;			 //LSB地址
	//u16 data = 0;//接收到的数据
        
        uint32_t data0=0,data1=0;
        uint32_t result = 0;
        
	switch(CHx)
	{
		case 0:
		{
			reg_addr1 = DATA_CH0;
			reg_addr 	= DATA_LSB_CH0;	
		}break;
		case 1:
		{
			reg_addr1 = DATA_CH1;
			reg_addr 	= DATA_LSB_CH1;
		}break;
		case 2:
		{
			reg_addr1 = DATA_CH2;			
			reg_addr 	= DATA_LSB_CH2;
		}break;
		case 3:
		{
			reg_addr1 = DATA_CH3;
			reg_addr 	= DATA_LSB_CH3;
		}break;
//		data = ;
		default: return 0;	//输入错误
		
	}
	
	//printf("%d \r\n",LCD_read_16bit(reg_addr1));
	//printf("%d \r\n",LCD_read_16bit(reg_addr));		//不知道LSB寄存器有什么用，手册也没见有
        
        
        data0 = FDC_read_reg(reg_addr1);
        data1 = FDC_read_reg(reg_addr);
        
        
        data0 = data0 &0x0FFF;
        
        result = data0<<16;
        
        result += data1;
        
        RawC = result;
        
        result /= 1000;
        
	return result;
}

/* 写  */
void FDC_write_16bit(u8 regaddr,u16 data)	//写data到寄存器，regaddr为寄存器的地址
{
//	u16 data_temp = 0;
//	u16 data_temp1 = 0;
        FDC_write_reg(regaddr,data>>8);
        FDC_write_reg(regaddr+1,data&0xff);
        
        
  
//	u8 Ack1,Ack2,Ack3,Ack4;
//	Ack1=Ack2=Ack3=Ack4=2;
//	
//	IIC_Start();
//	I2C_send_byte(FDC_Address_W);	//发送设备地址，写
//	Ack1 = I2C_wait_ack();
//	
//	I2C_send_byte(regaddr);	//寄存器地址
//	Ack2 = I2C_wait_ack();
//	
//	I2C_send_byte(data>>8);	//发送高八位
//	Ack3 = I2C_wait_ack();
//	
//	I2C_send_byte(data&0xff);	//发送低八位
//	Ack4 = I2C_wait_ack();
//	
//        if (Ack1 && Ack2 && Ack3 && Ack4)
//        {
//            ;
//        }
//	IIC_Stop();//产生一个停止条件

}


/* 读  */
u16 FDC_read_16bit(u8 regaddr) //读寄存器regaddr的值，regaddr为寄存器的地址
{
	u16 data_temp = 0;
	u16 data_temp1 = 0;
        
        data_temp1 = FDC_read_reg(regaddr);
        data_temp = FDC_read_reg(regaddr+1);
        
        
//	u8 Ack1,Ack2,Ack3,Ack4;
//	Ack1=Ack2=Ack3=Ack4=2;
//	
//	IIC_Start();
//	I2C_send_byte(FDC_Address_W);	//发送设备地址，写
//	Ack1 = I2C_wait_ack();					
//	IIC_SendByte(regaddr);	        //寄存器地址
//	Ack2 = I2C_wait_ack();
//	
//	IIC_Start();
//	I2C_send_byte(FDC_Address_R);		//发送设备地址，读
//	Ack3 = I2C_wait_ack();
//	data_temp1 = IIC_ReadByte(0);	//IIC读取高位字节
//	data_temp = IIC_ReadByte(0);		//IIC读取低位字节
//	IIC_Stop();
//	
//	//printf (" Ack1 %d\r\n Ack2 %d\r\n Ack3 %d, \r\n",Ack1,Ack2,Ack3);
//	//printf ("data_temp1 %d,data_temp %d \r\n",data_temp1,data_temp);
//	
//	data_temp = data_temp + (data_temp1<<8) ;	//数据合并
//        
//	if (Ack1 && Ack2 && Ack3 && Ack4)
//        {
//            ;
//        }
//	//printf("%d \r\n",data_temp); //串口发送看结果无误
        
        data_temp = data_temp + (data_temp1<<8) ;	//数据合并
	return data_temp;

}
