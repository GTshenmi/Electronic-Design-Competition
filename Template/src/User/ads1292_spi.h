#ifndef _ADS1292_SPI_H_
#define _ADS1292_SPI_H_

#define ADS1292_SPIx      SPI0
#define ADS1292_SPI_PCS   SPI_PCS0
#define ADS1292_SPI_MODE  3
#define ADS1292_SPI_BAUD  4//4

//#define ADS1292_SPIx      SPI1
//#define ADS1292_SPI_PCS   SPI_PCS1
//#define ADS1292_SPI_MODE  3
//#define ADS1292_SPI_BAUD  6

#define ADS1292_SPI_CS_PIN   PTA14//PTB20
#define ADS1292_SPI_SDI_PIN  PTA17
#define ADS1292_SPI_SDO_PIN  PTA16
#define ADS1292_SPI_SCK_PIN  PTA15

#define ADS1292_SPI_CS       PTA14_OUT//PTB20_OUT
#define ADS1292_SPI_SDI      PTA17_OUT
#define ADS1292_SPI_SDO      PTA16_OUT
#define ADS1292_SPI_SCK      PTA15_OUT

uint8_t ADS1292_SPI(uint8_t com);
uint8_t SPI_ReadWriteByte(uint8_t com);

void ADS1292_Send_CMD(uint8_t data);//发送命令

void ADS1292_WR_REGS(uint8_t reg,uint8_t len,uint8_t *data);//读写多个寄存器

//uint8_t ADS1292_Read_Data(uint8_t *data);//读9字节数据

#endif