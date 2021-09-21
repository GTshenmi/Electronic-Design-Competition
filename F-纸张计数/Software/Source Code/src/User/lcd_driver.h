#if 0
#ifndef _LCD_DRIVER_H_
#define _LCD_DRIVER_H_

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "fsl_gpio.h"
#include "stdio.h"
#include <stdarg.h>

#define USING_HARDWARE_CONTROLER 0
#define USING_FUNCTION_ENCAPSULATION 1

/*						!important!							*/
#include "delay.h"
#define LCD_delayus(us)	delay_us(us);			//Delay function interface->delay x us
#define LCD_delayms(ms) delay_ms(ms);			//Delay function interface->delay x ms
/*						!important!							*/

/*						!SPI Control!							*/
#if !USING_HARDWARE_CONTROLER

#define LCD_WriteByte	LCD_SoftWareWriteByte //send byte function interface->LCD_SoftWareWriteByte
#define LCD_WriteWord	LCD_SoftWareWriteWord //send word function interface->LCD_SoftWareWriteWord
#define LCD_WriteCmd  LCD_SoftWareWriteCmd	//send command function interface->LCD_SoftWareWriteCmd

#define LCD_DC	(GPIO2)->DRs.DR22	 
#define LCD_RST	(GPIO2)->DRs.DR20	
#define LCD_SDA	(GPIO2)->DRs.DR25  
#define LCD_SCL	(GPIO2)->DRs.DR24  
#define LCD_CS  (GPIO2)->DRs.DR16	 

#define DC_MUXIO  IOMUXC_GPIO_B1_06_GPIO2_IO22
#define RST_MUXIO	IOMUXC_GPIO_B1_04_GPIO2_IO20
#define	SDA_MUXIO	IOMUXC_GPIO_B1_09_GPIO2_IO25
#define SCL_MUXIO	IOMUXC_GPIO_B1_08_GPIO2_IO24
#define CS_MUXIO	IOMUXC_GPIO_B1_00_GPIO2_IO16

#define DC_GPIO		GPIO2
#define RST_GPIO	GPIO2
#define	SDA_GPIO	GPIO2
#define SCL_GPIO	GPIO2
#define CS_GPIO		GPIO2

#define DC_GPIO_PIN		22
#define RST_GPIO_PIN	20
#define	SDA_GPIO_PIN	25
#define SCL_GPIO_PIN	24
#define CS_GPIO_PIN		16

#else

#define LCD_WriteByte	LCD_HardWareWriteByte //send byte function interface->LCD_SoftWareWriteByte
#define LCD_WriteWord	LCD_HardWareWriteWord //send word function interface->LCD_SoftWareWriteWord
#define LCD_WriteCmd  LCD_HardWareWriteCmd	//send command function interface->LCD_SoftWareWriteCmd

#include "fsl_lpspi.h"
#define LPSPI LPSPI3
#define LCD_DC	(GPIO2)->DRs.DR15	 //E11->GPIO_B0_15
#define LCD_RST	(GPIO2)->DRs.DR26	 //B13->GPIO_B1_10
#define LCD_SDA	IOMUXC_GPIO_AD_B0_01_LPSPI3_SDO
#define LCD_SCL	IOMUXC_GPIO_AD_B0_00_LPSPI3_SCK   
#define LCD_CS  (GPIO2)->DRs.DR19	 

#endif
/*						!SPI Control!							*/

typedef enum
{
		RED		=0xf800,
		GREEN	=0x07e0,
		LIGHTBLUE=0x87ff,
		BLUE		=0x001f,
		PURPLE	=0xf81f,
		YELLOW	=0xffe0,
		CYAN		=0x07ff, 		//蓝绿色
		ORANGE	=0xfc08,
		BLACK	=0x0000,
		WHITE	=0xffff,
	
}lcd_color_t;
typedef enum
{
		usingWriteXLine,
		usingNone,
}_printstate;
typedef struct
{
		unsigned char Type;	//字体，还未写代码
		unsigned char Hight;
		unsigned char Width;
		lcd_color_t Color;
		lcd_color_t Backcolor;
		_printstate PrintState;
}lcd_font_t;
typedef struct
{
		unsigned int x;
		unsigned int y;
}cursor_t;
typedef struct
{
		lcd_color_t Color;
		uint8_t Width;
		uint8_t Interval;
}XLine_t;
#if USING_FUNCTION_ENCAPSULATION
/*						下面这个结构体仅为上述函数的整理，用法在LCD_Test函数中，不用可注释掉，同时将所有static void 改为 void	*/
typedef struct 
{
		void (*HalfLine)(const char *format,...);
		void (*Line)(const char *format,...);
		void (*XLine)(uint8_t linex,const char *format,...);
}write_t;

typedef struct
{
		void (*Char)(uint8_t row,uint8_t col,uint8_t ch,lcd_color_t color);
		void (*Num)(uint8_t row,uint8_t col,long num,lcd_color_t color);
		void (*Chinese)(void);
		void (*Str)(uint8_t row,uint8_t col,uint8_t *str,lcd_color_t color);
}show_t;

typedef struct
{
		void (*Point)(uint8_t xs,uint8_t ys,lcd_color_t color);
		void (*Hline)(uint8_t xs,uint8_t ys,uint8_t len,uint8_t width,lcd_color_t color);
		void (*Vline)(uint8_t xs,uint8_t ys,uint8_t len,uint8_t width,lcd_color_t color);
		void (*Line)(uint8_t xs,uint8_t ys,uint8_t xe,uint8_t ye,lcd_color_t color);
		void (*Sqr)(uint8_t xs,uint8_t ys,uint8_t xe,uint8_t ye,lcd_color_t color);
		void (*Circle)(uint8_t x,uint8_t y,uint8_t r,lcd_color_t color);
		void (*Pic)(uint8_t x,uint8_t y,uint8_t w,uint8_t h,uint8_t *ppic);	
}draw_t;

typedef struct 
{
		void (*SendByte)(uint8_t data);
		void (*SendWord)(uint16_t data);
		void (*SendCmd)(uint8_t cmd);
		void (*Test)(void);
		void (*AddrReset)(void);
		void (*SetPos)(uint8_t xs,uint8_t ys,uint8_t xe,uint8_t ye);
		void (*Clear)(lcd_color_t color);
		void (*Fill)(uint8_t xs,uint8_t ys,uint8_t xe,uint8_t ye,lcd_color_t color);
		void (*SetCursor)(uint16_t x,uint16_t y);
		void (*SetBackGroundColor)(lcd_color_t color);
		void (*SetFontSize)(uint16_t width,uint16_t hight);
		void (*SetFontColor)(lcd_color_t color);
		void (*SetFontBackColor)(lcd_color_t color);
		void (*SetXLineColor)(lcd_color_t color);
		void (*SetXLineWidth)(uint8_t width);
		void (*SetXLineInterval)(uint8_t interval);
		void (*SetXLineVal)(lcd_color_t color,uint8_t width,uint8_t interval);
}debug_t;
typedef struct
{
		void (*Init)(void);
		show_t Show;
		draw_t Draw;
		write_t	Write;
		int (*Printf)(const char *, ...);
		debug_t Debug;
}lcd_t;

/*																																																	*/
#endif
typedef struct
{
		unsigned int Hight;
		unsigned int Width;
		bool Type;					//横竖屏 只支持竖屏，横屏代码没写
		cursor_t Cursor;
		lcd_color_t Backgroundcolor;
		XLine_t XLine;
		lcd_font_t Font;
#if USING_FUNCTION_ENCAPSULATION
		void (*Init)(void);
		void (*DeInit)(void);
		show_t Show;
		draw_t Draw;
		write_t	Write;
		int (*Printf)(const char *, ...);
		debug_t Debug;	
#endif
}lcd_ctrl_t;


extern lcd_ctrl_t LCD;

void LCD_Init(void);
static void LCD_DeInit(void);

#if !USING_HARDWARE_CONTROLER
static void LCD_SoftWareWriteByte(uint8_t data);
static void LCD_SoftWareWriteWord(uint16_t data);
static void LCD_SoftWareWriteCmd(uint8_t cmd);
#else
static void LCD_HardWareSPIInit(uint8_t baudrate);
static void LCD_HardWareWriteByte(uint8_t data);
static void LCD_HardWareWriteWord(uint16_t data);
static void LCD_HardWareWriteCmd(uint8_t cmd);
#endif
static void LCD_AddrReset(void);
static void LCD_SetPos(uint8_t xs,uint8_t ys,uint8_t xe,uint8_t ye);
static void LCD_SetBackGroundColor(lcd_color_t color);
static void LCD_SetFontSize(uint16_t width,uint16_t hight); //仅供printf 以及write函数使用
static void LCD_SetFontColor(lcd_color_t color);						//仅供printf 以及write函数使用
static void LCD_SetFontBackColor(lcd_color_t color);								//仅供printf 以及write函数使用
static void LCD_SetCursor(uint16_t x,uint16_t y);						//仅供printf 以及write函数使用
static void LCD_SetXLineColor(lcd_color_t color);						// 仅用于WriteXLine函数
static void LCD_SetXLineWidth(uint8_t width);								// 仅用于WriteXLine函数
static void LCD_SetXLineInterval(uint8_t interval);					// 仅用于WriteXLine函数
static void LCD_SetXLineVal(lcd_color_t color,uint8_t width,uint8_t interval);		// 仅用于WriteXLine函数
static void LCD_Clear(lcd_color_t color);
static void LCD_Fill(uint8_t xs,uint8_t ys,uint8_t xe,uint8_t ye,lcd_color_t color);

static void LCD_DrawPoint(uint8_t xs,uint8_t ys,lcd_color_t color);
static void LCD_DrawHLine(uint8_t xs,uint8_t ys,uint8_t len,uint8_t width,lcd_color_t color);
static void LCD_DrawVLine(uint8_t xs,uint8_t ys,uint8_t len,uint8_t width,lcd_color_t color);
static void LCD_DrawLine(uint8_t xs,uint8_t ys,uint8_t xe,uint8_t ye,lcd_color_t color);
static void LCD_DrawSqr(uint8_t xs,uint8_t ys,uint8_t xe,uint8_t ye,lcd_color_t color);
static void LCD_DrawCircle(uint8_t x,uint8_t y,uint8_t r,lcd_color_t color);
static void LCD_DrawPic(uint8_t x,uint8_t y,uint8_t w,uint8_t h,uint8_t *ppic);

static void LCD_ShowChar(uint8_t row,uint8_t col,uint8_t ch,lcd_color_t color);
static void LCD_ShowNum(uint8_t row,uint8_t col,long num,lcd_color_t color);
static void LCD_ShowChinese(void);
static void LCD_ShowStr(uint8_t row,uint8_t col,uint8_t *str,lcd_color_t color);

static void LCD_WriteHalfLine(const char *format,...);
static void LCD_WriteLine(const char *format,...);
static void LCD_WriteXLine(uint8_t linex,const char *format,...);

void LCD_Test(void);
/*																								字体库																									*/
extern unsigned char Font_code8[][6];
/*																								字体库																									*/
#endif
#endif
