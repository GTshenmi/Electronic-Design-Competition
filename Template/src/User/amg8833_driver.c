#include "include.h"
#include "amg8833_driver.h"

#define DEVICE_NUM 1

#define Amg88xxIIC_SCL_1()	GPIO_PinWrite(Amg88xxIIC_SCL_GPIO_Pin, 1)
#define Amg88xxIIC_SCL_0()	GPIO_PinWrite(Amg88xxIIC_SCL_GPIO_Pin, 0)

#define Amg88xxIIC_SDA_1()	GPIO_PinWrite(Amg88xxIIC_SDA_GPIO_Pin,1)
#define Amg88xxIIC_SDA_0()	GPIO_PinWrite(Amg88xxIIC_SDA_GPIO_Pin,0)

#define Amg88xxIIC_SCL_READ()	GPIO_PinRead(Amg88xxIIC_SCL_GPIO_Pin)
#define Amg88xxIIC_SDA_READ()	GPIO_PinRead(Amg88xxIIC_SDA_GPIO_Pin)

#define Amg88xxIIC_WR	0		/* д����bit */
#define Amg88xxIIC_RD	1		/* ������bit */

#define Amg88xxIICSDA_IN()  GPIO_PinSetDir(Amg88xxIIC_SDA_GPIO_Pin,GPI)
#define Amg88xxIICSDA_OUT() GPIO_PinSetDir(Amg88xxIIC_SDA_GPIO_Pin,GPO)

//static void i2c_Delay(void)
//{
//	uint8_t i;
//
//	/*��
//		CPU��Ƶ168MHzʱ�����ڲ�Flash����, MDK���̲��Ż�����̨ʽʾ�����۲Ⲩ�Ρ�
//		ѭ������Ϊ5ʱ��SCLƵ�� = 1.78MHz (����ʱ: 92ms, ��д������������ʾ����̽ͷ���ϾͶ�дʧ�ܡ�ʱ��ӽ��ٽ�)
//		ѭ������Ϊ10ʱ��SCLƵ�� = 1.1MHz (����ʱ: 138ms, ���ٶ�: 118724B/s)
//		ѭ������Ϊ30ʱ��SCLƵ�� = 440KHz�� SCL�ߵ�ƽʱ��1.0us��SCL�͵�ƽʱ��1.2us
//
//		��������ѡ��2.2Kŷʱ��SCL������ʱ��Լ0.5us�����ѡ4.7Kŷ����������Լ1us
//
//		ʵ��Ӧ��ѡ��400KHz���ҵ����ʼ���
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
	/* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C����ֹͣ�ź� */
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
	/* �ȷ����ֽڵĸ�λbit7 */
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
			 Amg88xxIIC_SDA_1(); // �ͷ�����
		}
		Byte <<= 1;	/* ����һ��bit */
		//i2c_Delay();
		systime.delay_us(2);
	}
}

static bool Amg88xxIIC_WaitAck()
{
	bool re;
	Amg88xxIICSDA_IN();
	Amg88xxIIC_SDA_1();	/* CPU�ͷ�SDA���� */
	//i2c_Delay();
	systime.delay_us(1);
	Amg88xxIIC_SCL_1();	/* CPU����SCL = 1, ��ʱ�����᷵��ACKӦ�� */
	//i2c_Delay();
	systime.delay_us(1);
	if (Amg88xxIIC_SDA_READ())	/* CPU��ȡSDA����״̬ */
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

	/* ������1��bitΪ���ݵ�bit7 */
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
//	Amg88xxIIC_SDA_1();	/* CPU����SDA = 1 */
//	//i2c_Delay();
//	systime.delay_ms(10);
//	Amg88xxIIC_SCL_1();	/* CPU����1��ʱ�� */
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
//	Amg88xxIIC_SDA_0();	/* CPU����SDA = 0 */
//	//i2c_Delay();
//
//	Amg88xxIIC_SCL_1();	/* CPU����1��ʱ�� */
//	//i2c_Delay();
//	systime.delay_ms(10);
//	Amg88xxIIC_SCL_0();
//	//i2c_Delay();
//	systime.delay_ms(10);
//	Amg88xxIIC_SDA_1();	/* CPU�ͷ�SDA���� */
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
    Amg88xxIIC_SendByte((device_addr<<1)|0); //����������ַ+д����
    if(Amg88xxIIC_WaitAck())          //�ȴ�Ӧ��
    {
        Amg88xxIIC_Stop();
        return 1;
    }
    Amg88xxIIC_SendByte(reg);         //д�Ĵ�����ַ
    Amg88xxIIC_WaitAck();             //�ȴ�Ӧ��
    Amg88xxIIC_SendByte(data);        //��������
    if(Amg88xxIIC_WaitAck())          //�ȴ�ACK
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
    Amg88xxIIC_SendByte((device_addr<<1)|0); //����������ַ+д����
    if(Amg88xxIIC_WaitAck())          //�ȴ�Ӧ��
    {
        Amg88xxIIC_Stop();
        return 1;
    }
    Amg88xxIIC_SendByte(reg);         //д�Ĵ�����ַ
    Amg88xxIIC_WaitAck();             //�ȴ�Ӧ��
    Amg88xxIIC_Start();                
    Amg88xxIIC_SendByte((device_addr<<1)|1); //����������ַ+������
    Amg88xxIIC_WaitAck();             //�ȴ�Ӧ��
    while(len)
    {
        if(len==1)
		{
			*buf=Amg88xxIIC_ReadByte();//������,����nACK 
			Amg88xxIIC_NAck();
		}
		else 
		{
			*buf=Amg88xxIIC_ReadByte();		//������,����ACK  
			Amg88xxIIC_Ack();
		}
		len--;
		buf++;  
    }
    Amg88xxIIC_Stop();                 //����һ��ֹͣ����
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