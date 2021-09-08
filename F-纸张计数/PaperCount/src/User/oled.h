#ifndef _LQOLED_H
#define _LQOLED_H

typedef enum
{
	UsingOLED,
	UsingUART,
}_printstate;
typedef struct
{
		unsigned char Hight;
		unsigned char Width;
}oled_font_t;
typedef struct
{
		unsigned char x;
		unsigned char y;
}oled_cursor_t;

typedef struct
{
    unsigned char Hight;
    unsigned char Width;
    oled_cursor_t Cursor;
    oled_font_t Font;
    void (*WriteXLine)(int linex,char *format,...);
}oled_ctrl_t;

extern oled_ctrl_t OLED;

extern _printstate printstate;

void OLED_WriteXLine(int linex,char *format,...);

void OLED_PrintU16(unsigned char x,unsigned char y,unsigned int num);
void OLED_PrintFloat(unsigned char x,unsigned char y,float num);


void OLED_Init(void);
void OLED_CLS(void);
void OLED_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[]);
void OLED_P8x16Str(unsigned char x,unsigned char y,unsigned char ch[]);
void OLED_P14x16Str(unsigned char x,unsigned char y,unsigned char ch[]);
void OLED_Print(unsigned char x, unsigned char y, unsigned char ch[]);
void OLED_PutPixel(unsigned char x,unsigned char y);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_WrDat(unsigned char data);
void OLED_WrCmd(unsigned char cmd);
void OLED_Rectangle(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned char gif);
void OLED_Show_LibLogo(void);
void OLED_Show_BMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char * bmp); 
void OLED_Show_Road(void);
void OLED_Show_Frame80(void);
void OLED_Show_Frame94(void);
void OLED_WrDat(unsigned char data);
void OLED_WrCmd(unsigned char cmd);
void OLED_Fill(unsigned char bmp_data);
void OLED_DLY_ms(unsigned int ms);

#endif

