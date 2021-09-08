#ifndef _FDC2214_H_
#define _FDC2214_H_

#define 	DATA_CH0        			0X00         //���ݼĴ���0 MSBת�������״̬
#define 	DATA_LSB_CH0    			0X01         //ͨ��0 LSBת������������ڼĴ�����ַ0x00֮��
#define 	DATA_CH1        			0X02         //���ݼĴ���1 MSBת�������״̬
#define 	DATA_LSB_CH1    			0X03         //ͨ��1 LSBת������������ڼĴ�����ַ0x02���ȡ
#define 	DATA_CH2       	  		        0X04         //���ݼĴ���2 MSBת�������״̬
#define 	DATA_LSB_CH2    			0X05         //ͨ��2 LSBת������������ڼĴ�����ַ0x04���ȡ
#define 	DATA_CH3        			0X06         //���ݼĴ���3 MSBת�������״̬
#define 	DATA_LSB_CH3    			0X07         //ͨ��3 LSBת������������ڼĴ�����ַ0x06֮���ȡ

#define 	RCOUNT_CH0      			0X08         //ת��ʱ�����üĴ��� 0 
#define 	RCOUNT_CH1      			0X09         //ת��ʱ�����üĴ��� 1 
#define 	RCOUNT_CH2      			0X0A         //ת��ʱ�����üĴ��� 2 
#define 	RCOUNT_CH3      			0X0B         //ת��ʱ�����üĴ��� 3 

#define 	OFFSET_CH0      			0X0C         //Ƶ��ƫ�ƼĴ��� 0
#define 	OFFSET_CH1      			0X0D         //Ƶ��ƫ�ƼĴ��� 1
#define 	OFFSET_CH2      			0X0E         //Ƶ��ƫ�ƼĴ��� 2
#define 	OFFSET_CH3      			0X0F         //Ƶ��ƫ�ƼĴ��� 3

#define 	SETTLECOUNT_CH0 			0X10         //��ѡ�������������ʱ�� 0 
#define 	SETTLECOUNT_CH1 			0X11         //��ѡ�������������ʱ�� 1
#define 	SETTLECOUNT_CH2 			0X12         //��ѡ�������������ʱ�� 2
#define 	SETTLECOUNT_CH3 			0X13         //��ѡ�������������ʱ�� 3

#define 	CLOCK_DIVIDERS_CH0 		0X14      	 //ͨ��0�Ĳο���Ƶ������
#define 	CLOCK_DIVIDERS_CH1 		0X15      	 //ͨ��1�Ĳο���Ƶ������
#define 	CLOCK_DIVIDERS_CH2 		0X16      	 //ͨ��2�Ĳο���Ƶ������
#define 	CLOCK_DIVIDERS_CH3 		0X17      	 //ͨ��3�Ĳο���Ƶ������

#define 	STATUS          			0X18         //�豸״̬�����ַ

#define 	ERROR_CONFIG   				0X19         //������üĴ���
#define 	CONFIG          			0X1A         //ת������(�����������ƼĴ���)
#define 	MUX_CONFIG      			0X1B         //ͨ����������(ͨ��ת��)

#define 	RESET_DEV       			0X1C         //��λװ��

#define 	DRIVE_CURRENT_CH0 		0X1E         //ͨ��0 ������������������
#define 	DRIVE_CURRENT_CH1 		0X1F         //ͨ��1 ������������������
#define 	DRIVE_CURRENT_CH2 		0X20         //ͨ��2 ������������������
#define 	DRIVE_CURRENT_CH3 		0X21         //ͨ��3 ������������������

#define 	MANUFACTURER_ID  			0X7E         //������ID
#define 	DEVICE_ID        			0X7F         //�豸ID

void FDC_Start(void);
unsigned char FDC_read_reg_low(unsigned char addr);
unsigned char FDC_read_reg_high(unsigned char addr);
unsigned short FDC_read_reg(unsigned char addr);
void FDC_write_reg(unsigned char addr,unsigned short value);
uint32_t FDC_Read_CH3();
uint32_t FDC_read_CHx(u8 CHx);
u16 FDC_read_16bit(u8 regaddr); //���Ĵ���regaddr��ֵ��regaddrΪ�Ĵ����ĵ�ַ
void FDC_write_16bit(u8 regaddr,u16 data);	//дdata���Ĵ�����regaddrΪ�Ĵ����ĵ�ַ

// C --- 1/d
// Data --- fs
// fs --- 1/sqrt(C)

#endif