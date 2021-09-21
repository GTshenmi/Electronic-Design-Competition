#ifndef _FDC2214_H_
#define _FDC2214_H_

#define 	DATA_CH0        			0X00         //数据寄存器0 MSB转换结果和状态
#define 	DATA_LSB_CH0    			0X01         //通道0 LSB转换结果，必须在寄存器地址0x00之后
#define 	DATA_CH1        			0X02         //数据寄存器1 MSB转换结果和状态
#define 	DATA_LSB_CH1    			0X03         //通道1 LSB转换结果，必须在寄存器地址0x02后读取
#define 	DATA_CH2       	  		        0X04         //数据寄存器2 MSB转换结果和状态
#define 	DATA_LSB_CH2    			0X05         //通道2 LSB转换结果，必须在寄存器地址0x04后读取
#define 	DATA_CH3        			0X06         //数据寄存器3 MSB转换结果和状态
#define 	DATA_LSB_CH3    			0X07         //通道3 LSB转化结果，必须在寄存器地址0x06之后读取

#define 	RCOUNT_CH0      			0X08         //转换时间配置寄存器 0 
#define 	RCOUNT_CH1      			0X09         //转换时间配置寄存器 1 
#define 	RCOUNT_CH2      			0X0A         //转换时间配置寄存器 2 
#define 	RCOUNT_CH3      			0X0B         //转换时间配置寄存器 3 

#define 	OFFSET_CH0      			0X0C         //频率偏移寄存器 0
#define 	OFFSET_CH1      			0X0D         //频率偏移寄存器 1
#define 	OFFSET_CH2      			0X0E         //频率偏移寄存器 2
#define 	OFFSET_CH3      			0X0F         //频率偏移寄存器 3

#define 	SETTLECOUNT_CH0 			0X10         //所选传感器建立最短时间 0 
#define 	SETTLECOUNT_CH1 			0X11         //所选传感器建立最短时间 1
#define 	SETTLECOUNT_CH2 			0X12         //所选传感器建立最短时间 2
#define 	SETTLECOUNT_CH3 			0X13         //所选传感器建立最短时间 3

#define 	CLOCK_DIVIDERS_CH0 		0X14      	 //通道0的参考分频器设置
#define 	CLOCK_DIVIDERS_CH1 		0X15      	 //通道1的参考分频器设置
#define 	CLOCK_DIVIDERS_CH2 		0X16      	 //通道2的参考分频器设置
#define 	CLOCK_DIVIDERS_CH3 		0X17      	 //通道3的参考分频器设置

#define 	STATUS          			0X18         //设备状态报告地址

#define 	ERROR_CONFIG   				0X19         //误差配置寄存器
#define 	CONFIG          			0X1A         //转化配置(电流驱动控制寄存器)
#define 	MUX_CONFIG      			0X1B         //通道复用配置(通道转化)

#define 	RESET_DEV       			0X1C         //复位装置

#define 	DRIVE_CURRENT_CH0 		0X1E         //通道0 传感器电流驱动配置
#define 	DRIVE_CURRENT_CH1 		0X1F         //通道1 传感器电流驱动配置
#define 	DRIVE_CURRENT_CH2 		0X20         //通道2 传感器电流驱动配置
#define 	DRIVE_CURRENT_CH3 		0X21         //通道3 传感器电流驱动配置

#define 	MANUFACTURER_ID  			0X7E         //制造商ID
#define 	DEVICE_ID        			0X7F         //设备ID

void FDC_Start(void);
unsigned char FDC_read_reg_low(unsigned char addr);
unsigned char FDC_read_reg_high(unsigned char addr);
unsigned short FDC_read_reg(unsigned char addr);
void FDC_write_reg(unsigned char addr,unsigned short value);
uint32_t FDC_Read_CH3();
uint32_t FDC_read_CHx(u8 CHx);
u16 FDC_read_16bit(u8 regaddr); //读寄存器regaddr的值，regaddr为寄存器的地址
void FDC_write_16bit(u8 regaddr,u16 data);	//写data到寄存器，regaddr为寄存器的地址

// C --- 1/d
// Data --- fs
// fs --- 1/sqrt(C)

#endif