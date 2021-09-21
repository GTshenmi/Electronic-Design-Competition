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
            dat |= 0x01;//���λ��1
        }
        else
        {
            dat &=  0xfe;	//1111 1110���λ��0
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
//���� FDC_Address_W =0x54
void FDC_write_reg(unsigned char addr,unsigned short value)   //addr Ϊ�Ĵ�����ַ��valueΪ��Ҫд��ļĴ������� 
{ 
	   I2C_start();                    //����START�ź�
	   I2C_send_byte(FDC_Address_W);   //���ʹӻ���ַ��д�ź�
	   I2C_wait_ack();                 //�ȴ�ACK
	   I2C_send_byte(addr);            //������Ҫд��ļĴ�����ַ
	   I2C_wait_ack();                 //�ȴ�ACK
	   I2C_send_byte(value>>8);        //���͸�8λ����
	   I2C_wait_ack();                 //�ȴ�ACK
	   I2C_send_byte(value&0xFF);      //���͵�8λ����
	   I2C_wait_ack();                 //�ȴ�ACK
           I2C_stop();                      //����STOP�ź�
	   FDC2214_Delayms(1);
}

//FDC_Address_W =0x54
//FDC_Address_R =0x55
//Receive_Data[] Ϊ�������ݵ�����
//C_Data Ϊһ��16λ�޷��ŵ�����
unsigned short FDC_read_reg(unsigned char addr)
{
      unsigned char Receive_Data[2];
      I2C_start();                    //����START�ź�
	    I2C_send_byte(FDC_Address_W);   //����д����
	    I2C_wait_ack();		
	    I2C_send_byte(addr);            //������Ҫ���ļĴ����ĵ�ַ
			I2C_wait_ack();
	
	     I2C_start();
	     I2C_send_byte(FDC_Address_R);  //���Ͷ�����
	     I2C_wait_ack();
	     
	   // Receive_Data[0]=I2C_read_byte(0);  //����8λ����ack

			
             Receive_Data[0]=I2C_read_byte(0);;
             Receive_Data[1]= I2C_read_byte(0); //����8λ nack
	     I2C_stop();	                    //����STOP�ź�

	    
		 return  (Receive_Data[0]<<8)+ Receive_Data[1];
}


void FDC_Start(void)  
{    
        uint16_t ID = 0,MID = 0;
        
        IIC_Init();
        
        FDC2214_Delayms(500);
        
        FDC_write_reg(0x08,0x8329);   //(CHx_RCOUNT*16)/55M ==9.76ms��,ÿ10ms���ҿ��Զ�һ��ֵ
	FDC_write_reg(0x09,0x8329);
        FDC_write_reg(0x0A,0x8329);	
	FDC_write_reg(0x0B,0x8329);
	
	FDC_write_reg(0x10,0x000A);  //����4��ͨ����С�ȶ�ʱ��
	FDC_write_reg(0x11,0x000A);
	FDC_write_reg(0x12,0x000A);
	FDC_write_reg(0x13,0x000A);
	
        FDC_write_reg(0x14,0x1001); //ʱ�ӳ���1�����ô�����Ƶ����0.01M��8.5M֮��
	FDC_write_reg(0x15,0x1001);
	FDC_write_reg(0x16,0x1001);
	FDC_write_reg(0x17,0x1001);
	
	FDC_write_reg(0x19,0x0000); //�������жϱ�־λ
	FDC_write_reg(0x1B,0xC20D);//ʹ��0,1,2,3ͨ�����Ҵ�������Ϊ10M
 
	FDC_write_reg(0x1E,0x8000); //����4��ͨ������������
        FDC_write_reg(0x1F,0x8000);
	FDC_write_reg(0x20,0x8000);
	FDC_write_reg(0x21,0x8000);
 
 	
	FDC_write_reg(0x1A,0x1401);	//ʹ��FDC2214,��ȡ�ڲ�ʱ��Ϊ�ο�ʱ��
        
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
	u8 reg_addr1 = 0;			 //MSB��ַ
	u8 reg_addr = 0;			 //LSB��ַ
	//u16 data = 0;//���յ�������
        
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
		default: return 0;	//�������
		
	}
	
	//printf("%d \r\n",LCD_read_16bit(reg_addr1));
	//printf("%d \r\n",LCD_read_16bit(reg_addr));		//��֪��LSB�Ĵ�����ʲô�ã��ֲ�Ҳû����
        
        
        data0 = FDC_read_reg(reg_addr1);
        data1 = FDC_read_reg(reg_addr);
        
        
        data0 = data0 &0x0FFF;
        
        result = data0<<16;
        
        result += data1;
        
        RawC = result;
        
        result /= 1000;
        
	return result;
}

/* д  */
void FDC_write_16bit(u8 regaddr,u16 data)	//дdata���Ĵ�����regaddrΪ�Ĵ����ĵ�ַ
{
//	u16 data_temp = 0;
//	u16 data_temp1 = 0;
        FDC_write_reg(regaddr,data>>8);
        FDC_write_reg(regaddr+1,data&0xff);
        
        
  
//	u8 Ack1,Ack2,Ack3,Ack4;
//	Ack1=Ack2=Ack3=Ack4=2;
//	
//	IIC_Start();
//	I2C_send_byte(FDC_Address_W);	//�����豸��ַ��д
//	Ack1 = I2C_wait_ack();
//	
//	I2C_send_byte(regaddr);	//�Ĵ�����ַ
//	Ack2 = I2C_wait_ack();
//	
//	I2C_send_byte(data>>8);	//���͸߰�λ
//	Ack3 = I2C_wait_ack();
//	
//	I2C_send_byte(data&0xff);	//���͵Ͱ�λ
//	Ack4 = I2C_wait_ack();
//	
//        if (Ack1 && Ack2 && Ack3 && Ack4)
//        {
//            ;
//        }
//	IIC_Stop();//����һ��ֹͣ����

}


/* ��  */
u16 FDC_read_16bit(u8 regaddr) //���Ĵ���regaddr��ֵ��regaddrΪ�Ĵ����ĵ�ַ
{
	u16 data_temp = 0;
	u16 data_temp1 = 0;
        
        data_temp1 = FDC_read_reg(regaddr);
        data_temp = FDC_read_reg(regaddr+1);
        
        
//	u8 Ack1,Ack2,Ack3,Ack4;
//	Ack1=Ack2=Ack3=Ack4=2;
//	
//	IIC_Start();
//	I2C_send_byte(FDC_Address_W);	//�����豸��ַ��д
//	Ack1 = I2C_wait_ack();					
//	IIC_SendByte(regaddr);	        //�Ĵ�����ַ
//	Ack2 = I2C_wait_ack();
//	
//	IIC_Start();
//	I2C_send_byte(FDC_Address_R);		//�����豸��ַ����
//	Ack3 = I2C_wait_ack();
//	data_temp1 = IIC_ReadByte(0);	//IIC��ȡ��λ�ֽ�
//	data_temp = IIC_ReadByte(0);		//IIC��ȡ��λ�ֽ�
//	IIC_Stop();
//	
//	//printf (" Ack1 %d\r\n Ack2 %d\r\n Ack3 %d, \r\n",Ack1,Ack2,Ack3);
//	//printf ("data_temp1 %d,data_temp %d \r\n",data_temp1,data_temp);
//	
//	data_temp = data_temp + (data_temp1<<8) ;	//���ݺϲ�
//        
//	if (Ack1 && Ack2 && Ack3 && Ack4)
//        {
//            ;
//        }
//	//printf("%d \r\n",data_temp); //���ڷ��Ϳ��������
        
        data_temp = data_temp + (data_temp1<<8) ;	//���ݺϲ�
	return data_temp;

}
