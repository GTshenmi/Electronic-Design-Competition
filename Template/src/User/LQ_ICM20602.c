/*-----------------------------------------------------------------------------------------------------
��ƽ    ̨������K60���İ�-���ܳ���
����    д��LQ-005
��E-mail  ��chiusir@163.com
������汾��V1.0������Դ���룬�����ο�������Ը�
�������¡�2019��04��02��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
������ƽ̨��IAR 8.2
����    �ܡ�
��ע�����ICM20602���Կ���MPU6050�������棬���ܸ����ȶ����Ҽ���6050
-------------------------------------------------------------*/
#include "include.h"
#include "LQ_ICM20602.h"

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�LQ-005
������˵������ȡ MPU6050 ��ԭʼ����
������汾��V1.0
�������¡�2019��03��13�� 
����������
������ֵ���� 0����ʼ���ɹ�   1��ʧ��
������ֵ���� 
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#ifdef LQ_TFT1_8
void Test_ICM20602(void)
{
    TFTSPI_Init(1);                //TFT1.8��ʼ��  
    TFTSPI_CLS(u16BLUE);           //����
    UART_Init(UART4, 115200);
    char  txt[30];
	short aacx,aacy,aacz;	        //���ٶȴ�����ԭʼ����
	short gyrox,gyroy,gyroz;        //������ԭʼ���� 
    TFTSPI_P8X16Str(2,0,"LQ ICM20602 Test",u16RED,u16BLUE);
    printf("\r\nLQ ICM20602 Test");
    if(ICM20602_Init())
    {
        TFTSPI_P8X16Str(2,0,"ICM20602 Test Fail",u16RED,u16BLUE);
        while(1);   
    }
        
    while(1)
    {
        MPU_Get_Raw_data(&aacx,&aacy,&aacz,&gyrox,&gyroy,&gyroz);	//�õ����ٶȴ���������  
        sprintf((char*)txt,"ax:%06d",aacx);
        TFTSPI_P8X16Str(0,1,txt,u16RED,u16BLUE);
        sprintf((char*)txt,"ay:%06d",aacy);
        TFTSPI_P8X16Str(0,2,txt,u16RED,u16BLUE);
        sprintf((char*)txt,"az:%06d",aacz);
        TFTSPI_P8X16Str(0,3,txt,u16RED,u16BLUE);
        sprintf((char*)txt,"gx:%06d",gyrox);
        TFTSPI_P8X16Str(0,4,txt,u16RED,u16BLUE);
        sprintf((char*)txt,"gy:%06d",gyroy);
        TFTSPI_P8X16Str(0,5,txt,u16RED,u16BLUE);
        sprintf((char*)txt,"gz:%06d",gyroz);
        TFTSPI_P8X16Str(0,6,txt,u16RED,u16BLUE);

        printf("\r\nAX: %d  ",aacx); 
        printf("\r\nAY: %d  ",aacy);
        printf("\r\nAZ: %d  ",aacz); 
        printf("\r\nGX: %d  ",gyrox);
        printf("\r\nGY: %d  ",gyroy); 
        printf("\r\nGZ: %d  ",gyroz);
        delayms(100);
        printf("*********************");
    }
    
}
#endif
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�LQ-005
������˵������ȡ MPU6050 ��ԭʼ����
������汾��V1.0
�������¡�2019��03��13�� 
����������
������ֵ���� 0����ʼ���ɹ�   1��ʧ��
������ֵ���� 
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#ifdef LQ_OLED
void Test_ICM20602(void)
{
    char  txt[30];
	short aacx,aacy,aacz;	        //���ٶȴ�����ԭʼ����
	short gyrox,gyroy,gyroz;        //������ԭʼ����
    UART_Init(UART4, 115200);
    OLED_Init();                  //LCD��ʼ��
    OLED_CLS();                   //LCD����
    OLED_P8x16Str(15,0,"ICM20602 Test"); 
    printf("\r\nLQ ICM20602 Test");
    
    if(ICM20602_Init())
    {
    
        OLED_P8x16Str(15,2,"ICM20602 Test Fail");
        while(1);
    }
        
    while(1)
    {
        ICM_Get_Raw_data(&aacx,&aacy,&aacz,&gyrox,&gyroy,&gyroz);	//�õ����ٶȴ���������  
        sprintf((char*)txt,"ax:%06d",aacx);
        OLED_P6x8Str(0,2,txt);
        sprintf((char*)txt,"ay:%06d",aacy);
        OLED_P6x8Str(0,3,txt);
        sprintf((char*)txt,"az:%06d",aacz);
        OLED_P6x8Str(0,4,txt);
        sprintf((char*)txt,"gx:%06d",gyrox);
        OLED_P6x8Str(0,5,txt);
        sprintf((char*)txt,"gy:%06d",gyroy);
        OLED_P6x8Str(0,6,txt);
        sprintf((char*)txt,"gz:%06d",gyroz);
        OLED_P6x8Str(0,7,txt);

        printf("\r\nAX: %d  ",aacx); 
        printf("\r\nAY: %d  ",aacy);
        printf("\r\nAZ: %d  ",aacz); 
        printf("\r\nGX: %d  ",gyrox);
        printf("\r\nGY: %d  ",gyroy); 
        printf("\r\nGZ: %d  ",gyroz);
        delayms(100);
        printf("*********************");
    }
    
}
#endif

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�LQ-005
������˵������ʼ�� ICM20602
������汾��V1.0
�������¡�2019��03��13�� 
����������
������ֵ���� 0����ʼ���ɹ�   1��ʧ��
������ֵ���� 
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
uint8_t ICM20602_Init(void)
{
    uint8_t res;
    SPI_Init(SPI1, SPI_PCS1, MASTER, 1, 10);            //ICM20602 ֧��10M SPI
    delayms(100);
    res=ICM_Read_Byte(WHO_AM_I);                        //��ȡICM20602��ID
    if(res!=ICM20602_ID)                                 //����ID��ȷ
    {
        printf("ID=%#X\r\n",res);
        printf("ICM20602 is fail!\n");
    }
    else  printf("ICM20602 is OK!\n");
    res = 0;
    ICM_Write_Byte(ICM_PWR_MGMT1_REG,0X80);//��λ
    delayms(100);  //��ʱ100ms
    ICM_Write_Byte(ICM_PWR_MGMT1_REG,0X00);//����
    delayms(100);  //��ʱ100ms

    ICM_Set_Gyro_Fsr(3);			       //�����Ǵ�����,��2000dps   
    ICM_Set_Accel_Fsr(1);				   //���ٶȴ�����,��4g
    ICM_Set_Rate(1000);					   //���ò�����1000Hz
    ICM_Write_Byte(ICM_CFG_REG,0x02);      //�������ֵ�ͨ�˲���   98hz
    ICM_Write_Byte(ICM_INT_EN_REG,0X00);   //�ر������ж�
    ICM_Write_Byte(ICM_USER_CTRL_REG,0X00);//I2C��ģʽ�ر�
    ICM_Write_Byte(ICM_PWR_MGMT1_REG,0X01);//����CLKSEL,PLL X��Ϊ�ο�
    ICM_Write_Byte(ICM_PWR_MGMT2_REG,0X00);//���ٶ��������Ƕ�����

    
    return 0;
}

//����MPU6050�����Ǵ����������̷�Χ
//fsr:0,��250dps;1,��500dps;2,��1000dps;3,��2000dps
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
void ICM_Set_Gyro_Fsr(uint8_t fsr)
{
	ICM_Write_Byte(ICM_GYRO_CFG_REG,fsr<<3);//���������������̷�Χ  
}
//����MPU6050���ٶȴ����������̷�Χ
//fsr:0,��2g;1,��4g;2,��8g;3,��16g
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
void ICM_Set_Accel_Fsr(uint8_t fsr)
{
	ICM_Write_Byte(ICM_ACCEL_CFG_REG,fsr<<3);//���ü��ٶȴ����������̷�Χ  
}

//����MPU6050�����ֵ�ͨ�˲���
//lpf:���ֵ�ͨ�˲�Ƶ��(Hz)
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
void ICM_Set_LPF(uint16_t lpf)
{
	uint8_t data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	ICM_Write_Byte(ICM_CFG_REG,data);//�������ֵ�ͨ�˲���  
}

//����MPU6050�Ĳ�����(�ٶ�Fs=1KHz)
//rate:4~1000(Hz)
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
void ICM_Set_Rate(uint16_t rate)
{
	uint8_t data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	ICM_Write_Byte(ICM_SAMPLE_RATE_REG,data);	//�������ֵ�ͨ�˲���
 	ICM_Set_LPF(rate/2);	//�Զ�����LPFΪ�����ʵ�һ��
}

//�õ��¶�ֵ
//����ֵ:�¶�ֵ(������100��)
short ICM_Get_Temperature(void)
{
    uint8_t buf[3]; 
    short raw;
	float temp;
	ICM_Read_Len(ICM_TEMP_OUTH_REG,2,buf); 
    raw=((uint16_t)buf[0]<<8)|buf[1];  
    temp=21+((double)raw)/333.87;  
    return (short)temp*100;
}
//�õ�������ֵ(ԭʼֵ)
//gx,gy,gz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
void ICM_Get_Gyroscope(short *gx,short *gy,short *gz)
{
    uint8_t buf[7]; 
	ICM_Read_Len(ICM_GYRO_XOUTH_REG,6,buf);
    
    *gx=((uint16_t)buf[1]<<8)|buf[2];  
    *gy=((uint16_t)buf[3]<<8)|buf[4];  
    *gz=((uint16_t)buf[5]<<8)|buf[6];
    
}
//�õ����ٶ�ֵ(ԭʼֵ)
//gx,gy,gz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
void ICM_Get_Accelerometer(short *ax,short *ay,short *az)
{
    uint8_t buf[7];  
	ICM_Read_Len(ICM_ACCEL_XOUTH_REG,6,buf);
    
    *ax=((uint16_t)buf[1]<<8)|buf[2];  
    *ay=((uint16_t)buf[3]<<8)|buf[4];  
    *az=((uint16_t)buf[5]<<8)|buf[6];
    
}

//�õ��Ӽ�ֵ���¶�ֵ�����ٶ�ֵ(ԭʼֵ)
//gx,gy,gz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
void ICM_Get_Raw_data(short *ax,short *ay,short *az,short *gx,short *gy,short *gz)
{
    uint8_t buf[15];  
	ICM_Read_Len(ICM_ACCEL_XOUTH_REG,14,buf);
    
    *ax=((uint16_t)buf[1]<<8)|buf[2];  
    *ay=((uint16_t)buf[3]<<8)|buf[4];  
    *az=((uint16_t)buf[5]<<8)|buf[6];
    *gx=((uint16_t)buf[9]<<8)|buf[10];  
    *gy=((uint16_t)buf[11]<<8)|buf[12];  
    *gz=((uint16_t)buf[13]<<8)|buf[14];
	
}



/**
  * @brief    SPI ������
  *
  * @param    reg   ���ļĴ�����ַ
  * @param    len   ����
  * @param    buf   ��Ŷ������� �ĵ�ַ
  *
  * @return   
  *
  * @note     
  * 
  * @example  
  *
  * @date     2019/5/27 ����һ
  */

void ICM_Read_Len(uint8_t reg,uint8_t len,uint8_t *buf)
{   
    buf[0] = reg | 0x80;
    /* д��Ҫ���ļĴ�����ַ */
    SPI_ReadWrite(SPI1, SPI_PCS1, buf, buf, len + 1);

}


/**
  * @brief    SPI д
  *
  * @param    reg   д�ļĴ�����ַ
  * @param    value Ҫд��ֵ
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/5/27 ����һ
  */
void ICM_Write_Byte(uint8_t reg,uint8_t value)
{
    uint8_t buff[2];

    buff[0] = reg;          //�ȷ��ͼĴ���
    buff[1] = value;        //�ٷ�������

    SPI_ReadWrite(SPI1, SPI_PCS1, buff, buff, 2); //����buff�����ݣ����ɼ��� buff��
}

/**
  * @brief    SPI ��
  *
  * @param    reg   ���ļĴ�����ַ
  *
  * @return   ����������
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/5/27 ����һ
  */
uint8_t ICM_Read_Byte(uint8_t reg)
{
    uint8 buff[2];
    buff[0] = reg | 0x80;          //�ȷ��ͼĴ���

    SPI_ReadWrite(SPI1, SPI_PCS1, buff, buff,  2);
    

    return buff[1];
}
