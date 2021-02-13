#include "include.h"
#include "amg8833_driver.h"

#define DEVICE_NUM 1

#define Amg88xxIIC_SCL_1()	GPIO_PinWrite(Amg88xxIIC_SCL_GPIO_Pin, 1)
#define Amg88xxIIC_SCL_0()	GPIO_PinWrite(Amg88xxIIC_SCL_GPIO_Pin, 0)

#define Amg88xxIIC_SDA_1()	GPIO_PinWrite(Amg88xxIIC_SDA_GPIO_Pin,1)
#define Amg88xxIIC_SDA_0()	GPIO_PinWrite(Amg88xxIIC_SDA_GPIO_Pin,0)

#define Amg88xxIIC_SCL_READ()	GPIO_PinRead(Amg88xxIIC_SCL_GPIO_Pin)
#define Amg88xxIIC_SDA_READ()	GPIO_PinRead(Amg88xxIIC_SDA_GPIO_Pin)

#define Amg88xxIIC_WR	0		/* 写控制bit */
#define Amg88xxIIC_RD	1		/* 读控制bit */

#define Amg88xxIICSDA_IN()  GPIO_PinSetDir(Amg88xxIIC_SDA_GPIO_Pin,GPI)
#define Amg88xxIICSDA_OUT() GPIO_PinSetDir(Amg88xxIIC_SDA_GPIO_Pin,GPO)

//static void i2c_Delay(void)
//{
//	uint8_t i;
//
//	/*　
//		CPU主频168MHz时，在内部Flash运行, MDK工程不优化。用台式示波器观测波形。
//		循环次数为5时，SCL频率 = 1.78MHz (读耗时: 92ms, 读写正常，但是用示波器探头碰上就读写失败。时序接近临界)
//		循环次数为10时，SCL频率 = 1.1MHz (读耗时: 138ms, 读速度: 118724B/s)
//		循环次数为30时，SCL频率 = 440KHz， SCL高电平时间1.0us，SCL低电平时间1.2us
//
//		上拉电阻选择2.2K欧时，SCL上升沿时间约0.5us，如果选4.7K欧，则上升沿约1us
//
//		实际应用选择400KHz左右的速率即可
//	*/
//	for (i = 0; i < 30; i++);
//}

void amg88xxi2c_init()
{
	Amg88xxIIC_SCL_1();
	Amg88xxIIC_SDA_1();
}

static void Amg88xxIIC_Start()
{
	Amg88xxIICSDA_OUT();
	Amg88xxIIC_SDA_1();
	Amg88xxIIC_SCL_1();
	//i2c_Delay();
	systime.delay_us(4);
	Amg88xxIIC_SDA_0();
	//i2c_Delay();
	systime.delay_us(4);
	Amg88xxIIC_SCL_0();
        
        
}
static void Amg88xxIIC_Stop()
{
	/* 当SCL高电平时，SDA出现一个上跳沿表示I2C总线停止信号 */
	/*
	I2C_SDA_0();
	I2C_SCL_1();
	i2c_Delay();
	I2C_SDA_1();
	*/
	
	Amg88xxIICSDA_OUT();
	Amg88xxIIC_SCL_0();
	Amg88xxIIC_SDA_0();
	systime.delay_us(4);
	Amg88xxIIC_SCL_1();
	Amg88xxIIC_SDA_1();
	systime.delay_us(4);
}
static void Amg88xxIIC_SendByte(uint8_t Byte)
{
	uint8_t i;
	Amg88xxIICSDA_OUT();
	Amg88xxIIC_SCL_0();	
	/* 先发送字节的高位bit7 */
	for (i = 0; i < 8; i++)
	{
		if (Byte & 0x80)
		{
			Amg88xxIIC_SDA_1();
		}
		else
		{
			Amg88xxIIC_SDA_0();
		}
		//i2c_Delay();
		systime.delay_us(2);
		Amg88xxIIC_SCL_1();
		//i2c_Delay();
		systime.delay_us(2);
		Amg88xxIIC_SCL_0();
		if (i == 7)
		{
			 Amg88xxIIC_SDA_1(); // 释放总线
		}
		Byte <<= 1;	/* 左移一个bit */
		//i2c_Delay();
		systime.delay_us(2);
	}
}

static bool Amg88xxIIC_WaitAck()
{
	bool re;
	Amg88xxIICSDA_IN();
	Amg88xxIIC_SDA_1();	/* CPU释放SDA总线 */
	//i2c_Delay();
	systime.delay_us(1);
	Amg88xxIIC_SCL_1();	/* CPU驱动SCL = 1, 此时器件会返回ACK应答 */
	//i2c_Delay();
	systime.delay_us(1);
	if (Amg88xxIIC_SDA_READ())	/* CPU读取SDA口线状态 */
	{
		re = 1;
	}
	else
	{
		re = 0;
	}
	Amg88xxIIC_SCL_0();
	//i2c_Delay();
	return re;
}
static uint8_t Amg88xxIIC_ReadByte()
{
	uint8_t i;
	uint8_t value;
	Amg88xxIICSDA_IN();

	/* 读到第1个bit为数据的bit7 */
	value = 0;
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		Amg88xxIIC_SCL_1();
		//i2c_Delay();
		systime.delay_us(2);
		
		if (Amg88xxIIC_SDA_READ())
		{
			value++;
		}
		Amg88xxIIC_SCL_0();
		//i2c_Delay();
		systime.delay_us(1);
	}
	return value;
}

void Amg88xxIIC_NAck()
{
//	Amg88xxIIC_SDA_1();	/* CPU驱动SDA = 1 */
//	//i2c_Delay();
//	systime.delay_ms(10);
//	Amg88xxIIC_SCL_1();	/* CPU产生1个时钟 */
//	//i2c_Delay();
//	systime.delay_ms(10);
//	Amg88xxIIC_SCL_0();
//	//i2c_Delay();
//	systime.delay_ms(10);
	
	Amg88xxIIC_SCL_0();
	Amg88xxIICSDA_OUT();
	Amg88xxIIC_SDA_1();
	systime.delay_us(2);
	Amg88xxIIC_SCL_1();
	systime.delay_us(2);
	Amg88xxIIC_SCL_0();
}
void Amg88xxIIC_Ack()
{
//	Amg88xxIIC_SDA_0();	/* CPU驱动SDA = 0 */
//	//i2c_Delay();
//
//	Amg88xxIIC_SCL_1();	/* CPU产生1个时钟 */
//	//i2c_Delay();
//	systime.delay_ms(10);
//	Amg88xxIIC_SCL_0();
//	//i2c_Delay();
//	systime.delay_ms(10);
//	Amg88xxIIC_SDA_1();	/* CPU释放SDA总线 */
	Amg88xxIIC_SCL_0();
	Amg88xxIICSDA_OUT();
	Amg88xxIIC_SDA_0();
	systime.delay_us(2);
	Amg88xxIIC_SCL_1();
	systime.delay_us(2);
	Amg88xxIIC_SCL_0();
}

uint8_t device_selector(int deivce_num)
{
	uint8_t device_addr;
		(deivce_num!=2)?(device_addr = AMG88xx_ADDRESS):(device_addr = AMG88xx_ADDRESS_2);
		return device_addr;
}

uint8_t amg88xx_write(uint8_t reg,uint8_t data,int device_num)
{		
		uint8_t device_addr;
		device_addr = device_selector(device_num);
	
    Amg88xxIIC_Start();
    Amg88xxIIC_SendByte((device_addr<<1)|0); //发送器件地址+写命令
    if(Amg88xxIIC_WaitAck())          //等待应答
    {
        Amg88xxIIC_Stop();
        return 1;
    }
    Amg88xxIIC_SendByte(reg);         //写寄存器地址
    Amg88xxIIC_WaitAck();             //等待应答
    Amg88xxIIC_SendByte(data);        //发送数据
    if(Amg88xxIIC_WaitAck())          //等待ACK
    {
        Amg88xxIIC_Stop();
        return 1;
    }
    Amg88xxIIC_Stop();
    return 0;
}

uint8_t amg88xx_read_len(uint8_t reg,uint8_t len,uint8_t *buf,int device_num)
{ 	
    uint8_t device_addr;
    device_addr = device_selector(device_num);
	
    Amg88xxIIC_Start();
    Amg88xxIIC_SendByte((device_addr<<1)|0); //发送器件地址+写命令
    if(Amg88xxIIC_WaitAck())          //等待应答
    {
        Amg88xxIIC_Stop();
        return 1;
    }
    Amg88xxIIC_SendByte(reg);         //写寄存器地址
    Amg88xxIIC_WaitAck();             //等待应答
    Amg88xxIIC_Start();                
    Amg88xxIIC_SendByte((device_addr<<1)|1); //发送器件地址+读命令
    Amg88xxIIC_WaitAck();             //等待应答
    while(len)
    {
        if(len==1)
		{
			*buf=Amg88xxIIC_ReadByte();//读数据,发送nACK 
			Amg88xxIIC_NAck();
		}
		else 
		{
			*buf=Amg88xxIIC_ReadByte();		//读数据,发送ACK  
			Amg88xxIIC_Ack();
		}
		len--;
		buf++;  
    }
    Amg88xxIIC_Stop();                 //产生一个停止条件
    return 0;       
}

float AMG88XX_signedMag12ToFloat(uint16_t val)
{
	//take first 11 bits as absolute val
	uint16_t absVal = (val & 0x7FF);
        
//	float ActualVal = absVal * 0.0625;
        
	return (val & 0x8000) ? 0 - (float)absVal : (float)absVal ;
}

float amg88xx_readThermistor(int device_num)
{
	uint8_t device_addr;
	device_addr = device_selector(device_num);
	
	uint8_t raw[2];
	uint16_t recast;
	
	amg88xx_read_len(AMG88xx_TTHL, 2, raw,device_addr);
	recast = ((uint16_t)raw[1] << 8) | ((uint16_t)raw[0]);
        
        //uint16_t re = recast;
        //LCD.Write.XLine(2,"RawValue:%u",re);
	return AMG88XX_signedMag12ToFloat(recast) * AMG88xx_THERMISTOR_CONVERSION;
}

void amg88xx_readPixels(float *buf, uint8_t size,int device_num)
{	
	uint8_t device_addr;
	device_addr = device_selector(device_num);
	
	uint16_t recast;
	float converted;
	uint8_t rawArray[128];
	
	amg88xx_read_len(AMG88xx_PIXEL_OFFSET, 128, rawArray, device_addr);
	
	for(int i=0; i<size; i++)
	{
		uint8_t pos = i << 1;
		recast = ((uint16_t)rawArray[pos + 1] << 8) | ((uint16_t)rawArray[pos]);	
		converted = AMG88XX_signedMag12ToFloat(recast) * AMG88xx_PIXEL_TEMP_CONVERSION;
		buf[i] = converted;
	}
}
void AMG8833DrawPic()
{
   amg88xx_readPixels(AMG8833.PixelCache,64,DEVICE_NUM);
   //show(AMG8833.Pixel);
}
void amg88xx_init()
{   
	amg88xx_write(AMG88xx_PCTL, AMG88xx_NORMAL_MODE,DEVICE_NUM);
	amg88xx_write(AMG88xx_RST, AMG88xx_INITIAL_RESET,DEVICE_NUM);
	amg88xx_write(AMG88xx_FPSC, AMG88xx_FPS_10,DEVICE_NUM);       
}
void amg88xxSensorInit()
{
   GPIO_PinInit(Amg88xxIIC_SDA_GPIO_Pin,GPO,1);
   GPIO_PinInit(Amg88xxIIC_SCL_GPIO_Pin,GPO,1);
   
   amg88xxi2c_init();
   
   amg88xx_init();
   
}
float amg88xx_getTemp()
{
    float result = 0.0;     
    
    amg88xx_readPixels(AMG8833.PixelCache,64,DEVICE_NUM);

    result = (AMG8833.PixelCache[27] + AMG8833.PixelCache[28] + AMG8833.PixelCache[35] + AMG8833.PixelCache[36])/4.0;
    
    if(result >= AMG8833.ValueLimit.Max)
      result = AMG8833.ValueLimit.Max;
    else if(result <= AMG8833.ValueLimit.Min)
      result = AMG8833.ValueLimit.Min;
    
    return result;
}
void amg88xxTest()
{
    amg88xxSensorInit();
    
    uint32_t used_time_ms = 0;
    uint32_t used_time_us = 0;
    uint32_t now_time = systime.get_time_ms();
    used_time_ms = systime.get_time_ms();
    used_time_us = systime.get_time_ms();
    float Temp = 0.0;
    if(used_time_ms)
    {
       LCD.Write.XLine(4,"used time:%d ms",used_time_ms);
    }
    else
    {
       LCD.Write.XLine(4,"used time:%d us",used_time_us);
    }
    
    while(1)
    {
      
       if(systime.get_time_ms() - now_time >= 1000)
       {
          LCD.Debug.Clear(WHITE);
          now_time = systime.get_time_ms();
          used_time_ms = systime.get_time_ms();
          used_time_us = systime.get_time_us();
        //InfraredSensor.Temperature = InfraredSensor.GetTemperature();
        //LCD.Write.XLine(0,"%.3f",InfraredSensor.Temperature);

//        for(int i = 0;i<15;i++)
//          Temp += amg88xx_getTemp();
//        
//        Temp /= 15.0;
        Temp = amg88xx_getTemp();  
        used_time_ms = systime.get_time_ms() - used_time_ms;
        used_time_us = systime.get_time_us() - used_time_us;
        
        
        LCD.Write.XLine(0,"Temp:%.3f",Temp);
        if(used_time_ms)
        {
           LCD.Write.XLine(4,"used time:%d ms",used_time_ms);
        }
        else
        {
           LCD.Write.XLine(4,"used time:%d us",used_time_us);
        }
       }
    }
}

amg8833_t AMG8833 = 
{
   .ReadPixels = amg88xx_readPixels,
   .ValueLimit.Max = 80.0,
   .ValueLimit.Min = 0.0,
   .DrawPixels = AMG8833DrawPic,
};