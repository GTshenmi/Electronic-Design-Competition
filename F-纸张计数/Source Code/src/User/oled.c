#include "include.h"
#include "oled_font.h"  
#include "oled.h"

#define OLED_DC 	PTC19_OUT  
#define OLED_RST	PTC18_OUT 
#define OLED_SDA	PTC17_OUT  
#define OLED_SCL	PTC16_OUT  

#define OLED_DC_GPIO PTC19
#define OLED_RST_GPIO PTC18
#define OLED_SDA_GPIO PTC17
#define OLED_SCL_GPIO PTC16



#define  u8 unsigned char
#define  u32 unsigned int

oled_ctrl_t OLED=
{
    .Hight=64,
    .Width=132,
    .Font.Width=6,
    .Font.Hight=8,
    .Cursor.x=0,
    .Cursor.y=0,
    .WriteXLine=OLED_WriteXLine,
};

void OLED_WriteXLine(int linex,char *format,...)
{	
	va_list(ap);
	va_start(ap,format);
	
	//OLED.Cursor.y=linex*(OLED.Font.Hight);

        OLED.Cursor.y = linex;

	vprintf(format,ap);
		
	//OLED.Cursor.y+=OLED.Font.Hight;
	OLED.Cursor.x=0;

	va_end(ap);
}
//#define X_WIDTH 132
//#define Y_WIDTH 64

void OLED_Init(void)        
{ 
    GPIO_PinInit(OLED_DC_GPIO,GPO,0);
    GPIO_PinInit(OLED_RST_GPIO,GPO,0);
    GPIO_PinInit(OLED_SDA_GPIO,GPO,0);
    GPIO_PinInit(OLED_SCL_GPIO,GPO,0);  

  
    OLED_SCL=1;
    //OLED_CS=1;	//预制SLK和SS为高电平               
    OLED_RST=0;
    OLED_DLY_ms(50);
    OLED_RST=1;

    OLED_WrCmd(0xae);//--turn off oled panel
    OLED_WrCmd(0x00);//---set low column address
    OLED_WrCmd(0x10);//---set high column address
    OLED_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    OLED_WrCmd(0x81);//--set contrast control register
    OLED_WrCmd(0xcf); // Set SEG Output Current Brightness
    OLED_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
    OLED_WrCmd(0xc8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
    OLED_WrCmd(0xa6);//--set normal display
    OLED_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
    OLED_WrCmd(0x3f);//--1/64 duty
    OLED_WrCmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
    OLED_WrCmd(0x00);//-not offset
    OLED_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
    OLED_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
    OLED_WrCmd(0xd9);//--set pre-charge period
    OLED_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    OLED_WrCmd(0xda);//--set com pins hardware configuration
    OLED_WrCmd(0x12);
    OLED_WrCmd(0xdb);//--set vcomh
    OLED_WrCmd(0x40);//Set VCOM Deselect Level
    OLED_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
    OLED_WrCmd(0x02);//
    OLED_WrCmd(0x8d);//--set Charge Pump enable/disable
    OLED_WrCmd(0x14);//--set(0x10) disable
    OLED_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
    OLED_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7) 
    OLED_WrCmd(0xaf);//--turn on oled panel
    OLED_Fill(0x00);  //初始清屏
    OLED_Set_Pos(0,0);  
    OLED_CLS();
//    OLED_P14x16Str(0,0,"Content");
//    OLED_P8x16Str(0,20,"ADC_Value");
//    OLED_P8x16Str(0,36,"Steer_PID");
//    OLED_P8x16Str(0,52,"Motor_PID");
	
}
void OLED_WrDat(unsigned char data)
{
	unsigned char i=8;
	//OLED_CS=0;;
	OLED_DC=1;;
  OLED_SCL=0;;
  //asm("nop");    
  while(i--)
  {
    if(data&0x80){OLED_SDA=1;}
    else{OLED_SDA=0;}
    OLED_SCL=1; 
    asm("nop");;
		//asm("nop");            
    OLED_SCL=0;;    
    data<<=1;    
  }
	//OLED_CS=1;
}
void OLED_WrCmd(unsigned char cmd)
{
	unsigned char i=8;
	
	//OLED_CS=0;;
	OLED_DC=0;;
  OLED_SCL=0;;
  //asm("nop");   
  while(i--)
  {
    if(cmd&0x80){OLED_SDA=1;}
    else{OLED_SDA=0;;}
    OLED_SCL=1;;
    asm("nop");;
		//asm("nop");             
    OLED_SCL=0;;    
    cmd<<=1;;   
  } 	
	//OLED_CS=1;
}
void OLED_Set_Pos(unsigned char x, unsigned char y)
{ 
  OLED_WrCmd(0xb0+y);
  OLED_WrCmd(((x&0xf0)>>4)|0x10);
  OLED_WrCmd((x&0x0f)); 
} 
void OLED_Fill(unsigned char bmp_data)
{
	unsigned char y,x;
	
	for(y=0;y<8;y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for(x=0;x<OLED.Width;x++)
			OLED_WrDat(bmp_data);
	}
}
void OLED_CLS(void)
{
	unsigned char y,x;	
	for(y=0;y<8;y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10); 
		for(x=0;x<OLED.Width;x++)
			OLED_WrDat(0);
	}
}
void OLED_DLY_ms(unsigned int ms)
{                         
  unsigned int a;
  while(ms)
  {
    a=1335;
    while(a--);
    ms--;
  }
  //delayms(ms);
  return;
}

 
//==============================================================
//函数名： void OLED_PutPixel(unsigned char x,unsigned char y)
//功能描述：绘制一个点（x,y）
//参数：真实坐标值(x,y),x的范围0～127，y的范围0～64
//返回：无
//==============================================================
void OLED_PutPixel(unsigned char x,unsigned char y)
{
	unsigned char data1;  //data1当前点的数据 

	OLED_Set_Pos(x,(unsigned char)(y>>3)); 
	data1 =(unsigned char)(0x01<<(y%8)); 	
	OLED_WrCmd((unsigned char)(0xb0+(y>>3)));
	OLED_WrCmd((unsigned char)(((x&0xf0)>>4)|0x10));
	OLED_WrCmd((unsigned char)((x&0x0f)|0x00));
	OLED_WrDat(data1); 	 	
}
//==============================================================
//函数名： void OLED_Rectangle(unsigned char x1,unsigned char y1,
//                   unsigned char x2,unsigned char y2,unsigned char color,unsigned char gif)
//功能描述：绘制一个实心矩形
//参数：左上角坐标（x1,y1）,右下角坐标（x2，y2）
//      其中x1、x2的范围0～127，y1，y2的范围0～63，即真实坐标值
//返回：无
//==============================================================
void OLED_Rectangle(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned char gif)
{
	unsigned char n; 
		
	OLED_Set_Pos(x1,y1>>3);
	for(n=x1;n<=x2;n++)
	{
		OLED_WrDat(0x01<<(y1%8)); 			
		if(gif == 1) 	OLED_DLY_ms(50);
	}  
	OLED_Set_Pos(x1,y2>>3);
  for(n=x1;n<=x2;n++)
	{
		OLED_WrDat(0x01<<(y2%8)); 			
		if(gif == 1) 	OLED_DLY_ms(5);
	}
	
}  
//==============================================================
//函数名：OLED_P6x8Str(unsigned char x,unsigned char y,unsigned char *p)
//功能描述：写入一组标准ASCII字符串
//参数：显示的位置（x,y），y为页范围0～7，要显示的字符串
//返回：无
//==============================================================  
void OLED_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[])
{
  unsigned char c=0,i=0,j=0;      
  while (ch[j]!='\0')
  {    
    c =ch[j]-32;
    if(x>126){x=0;y++;}
    OLED_Set_Pos(x,y);    
  	for(i=0;i<6;i++)     
  	  OLED_WrDat(F6x8[c][i]);  
  	x+=6;
  	j++;
  }
}
//==============================================================
//函数名：OLED_P8x16Str(unsigned char x,unsigned char y,unsigned char *p)
//功能描述：写入一组标准ASCII字符串
//参数：显示的位置（x,y），y为页范围0～7，要显示的字符串
//返回：无
//==============================================================  
void OLED_P8x16Str(unsigned char x,unsigned char y,unsigned char ch[])
{
  unsigned char c=0,i=0,j=0;
        
  while (ch[j]!='\0')
  {    
    c =ch[j]-32;
    if(x>120){x=0;y++;}
    OLED_Set_Pos(x,y);    
  	for(i=0;i<8;i++)     
  	  OLED_WrDat(F8X16[c*16+i]);
  	OLED_Set_Pos(x,y+1);    
  	for(i=0;i<8;i++)     
  	  OLED_WrDat(F8X16[c*16+i+8]);  
  	x+=8;
  	j++;
  }
}
//输出汉字字符串
void OLED_P14x16Str(unsigned char x,unsigned char y,unsigned char ch[])
{
	unsigned char wm=0,ii = 0;
	unsigned int adder=1; 
	
	while(ch[ii] != '\0')
	{
  	wm = 0;
  	adder = 1;
  	while(F14x16_Idx[wm] > 127)
  	{
  		if(F14x16_Idx[wm] == ch[ii])
  		{
  			if(F14x16_Idx[wm + 1] == ch[ii + 1])
  			{
  				adder = wm * 14;
  				break;
  			}
  		}
  		wm += 2;			
  	}
  	if(x>118){x=0;y++;}
  	OLED_Set_Pos(x , y); 
  	if(adder != 1)// 显示汉字					
  	{
  		OLED_Set_Pos(x , y);
  		for(wm = 0;wm < 14;wm++)               
  		{
  			OLED_WrDat(F14x16[adder]);	
  			adder += 1;
  		}      
  		OLED_Set_Pos(x,y + 1); 
  		for(wm = 0;wm < 14;wm++)          
  		{
  			OLED_WrDat(F14x16[adder]);
  			adder += 1;
  		}   		
  	}
  	else			  //显示空白字符			
  	{
  		ii += 1;
      OLED_Set_Pos(x,y);
  		for(wm = 0;wm < 16;wm++)
  		{
  				OLED_WrDat(0);
  		}
  		OLED_Set_Pos(x,y + 1);
  		for(wm = 0;wm < 16;wm++)
  		{   		
  				OLED_WrDat(0);	
  		}
  	}
  	x += 14;
  	ii += 2;
	}
}
//输出汉字和字符混合字符串
void OLED_Print(unsigned char x, unsigned char y, unsigned char ch[])
{
	unsigned char ch2[3];
	unsigned char ii=0;        
	while(ch[ii] != '\0')
	{
		if(ch[ii] > 127)
		{
			ch2[0] = ch[ii];
	 		ch2[1] = ch[ii + 1];
			ch2[2] = '\0';			//汉字为两个字节
			OLED_P14x16Str(x , y, ch2);	//显示汉字
			x += 14;
			ii += 2;
		}
		else
		{
			ch2[0] = ch[ii];	
			ch2[1] = '\0';			//字母占一个字节
			OLED_P8x16Str(x , y , ch2);	//显示字母
			x += 8;
			ii+= 1;
		}
	}
} 

//==============================================================
//函数名： void OLED_Show_BMP(unsigned char x,unsigned char y)
//功能描述：显示BMP图片128×64
//参数：起始点坐标(x,y),x的范围0～127，y为页的范围0～7
//返回：无
//==============================================================
void OLED_Show_BMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char * bmp)
{ 	
  unsigned int ii=0;
  unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<=y1;y++)
	{
		OLED_Set_Pos(x0,y);				
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WrDat(bmp[ii++]);	    	
	    }
	}
}


void OLED_PrintU16(unsigned char x,unsigned char y,unsigned int num)
{
	unsigned char tmp[6],i;
	tmp[5]=0;
	tmp[4]=(unsigned char)(num%10+0x30);
	tmp[3]=(unsigned char)(num/10%10+0x30);
	tmp[2]=(unsigned char)(num/100%10+0x30);
	tmp[1]=(unsigned char)(num/1000%10+0x30);
	tmp[0]=(unsigned char)(num/10000%10+0x30);
	
	for(i=0;i<4;i++)
	{
		if(tmp[i]=='0')
			tmp[i]=' ';
		else
			break;
	}
	OLED_P6x8Str(x,y,tmp);
	
}
void OLED_PrintFloat(unsigned char x,unsigned char y,float num)
{
	unsigned char tmp[6],i;
	tmp[5]=0;
	num *= 10;
	if(num>0)
	{
		tmp[0]='+';
		tmp[4]=(unsigned char)((int)num%10+0x30);
		tmp[3]=(unsigned char)((int)num/10%10+0x30);
		tmp[2]=(unsigned char)((int)num/100%10+0x30);
		tmp[1]=(unsigned char)((int)num/1000%10+0x30);
	}
	else
	{
		tmp[0]='-';
		num=-num;
		tmp[4]=(unsigned char)((int)num%10+0x30);
		tmp[3]=(unsigned char)((int)num/10%10+0x30);
		tmp[2]=(unsigned char)((int)num/100%10+0x30);
		tmp[1]=(unsigned char)((int)num/1000%10+0x30);
	}
	for(i=0;i<4;i++)
	{
		if(tmp[i]=='0')
			tmp[i]=' ';
		else
			break;
	}
	OLED_P6x8Str(x,y,tmp);
}

void OLED_ClrDot(unsigned char x)
{
	OLED_Set_Pos(x,6);
	OLED_WrCmd((unsigned char)(0xb0+6));
	OLED_WrCmd((unsigned char)(((x&0xf0)>>4)|0x10));
	OLED_WrCmd((unsigned char)((x&0x0f)|0x00));
	OLED_WrDat(0x00);
	
	OLED_Set_Pos(x,7);
	OLED_WrCmd((unsigned char)(0xb0+7));
	OLED_WrCmd((unsigned char)(((x&0xf0)>>4)|0x10));
	OLED_WrCmd((unsigned char)((x&0x0f)|0x00));
	OLED_WrDat(0x00);
} 
/*
void OLED_Show_Road(void)
{ 	
  int i = 0, j = 0,temp=0;
	for(i=0;i<56;i+=8)
	{
	  	OLED_Set_Pos(13,i/8);
	  	for(j=0;j<100;j++) 
	  	{ 
	  	  temp=0;
	  	  if(Copy_Image[0+i][j]) temp|=0x01;
	  	  if(Copy_Image[1+i][j]) temp|=0x02;
	  	  if(Copy_Image[2+i][j]) temp|=0x04;
	  	  if(Copy_Image[3+i][j]) temp|=0x08;
	  	  if(Copy_Image[4+i][j]) temp|=0x10;
	  	  if(Copy_Image[5+i][j]) temp|=0x20;
	  	  if(Copy_Image[6+i][j]) temp|=0x40;
	  	  if(Copy_Image[7+i][j]) temp|=0x80;
	  	  OLED_WrDat(temp); 	  	  	  	  
	  	}
	}           
}
*/
//void OLED_Show_Frame80(void)
//{ 	
////  OLED_Set_Pos(23,0);
////  OLED_WrDat(0xFF); 
////  OLED_Set_Pos(23,1);
////  OLED_WrDat(0xFF); 
//  OLED_Set_Pos(23,2);
//  OLED_WrDat(0xFF); 
//  OLED_Set_Pos(23,3);
//  OLED_WrDat(0xFF); 
//  OLED_Set_Pos(23,4);
//  OLED_WrDat(0xFF); 
//  OLED_Set_Pos(23,5);
//  OLED_WrDat(0xFF);
//  OLED_Set_Pos(23,6);
//  OLED_WrDat(0xFF);
//  OLED_Set_Pos(23,7);
//  OLED_WrDat(0xFF);
//  
////  OLED_Set_Pos(104,0);
////  OLED_WrDat(0xFF); 
////  OLED_Set_Pos(104,1);
////  OLED_WrDat(0xFF); 
//  OLED_Set_Pos(105,2);
//  OLED_WrDat(0xFF); 
//  OLED_Set_Pos(105,3);
//  OLED_WrDat(0xFF); 
//  OLED_Set_Pos(105,4);
//  OLED_WrDat(0xFF); 
//  OLED_Set_Pos(105,5);
//  OLED_WrDat(0xFF);
//  OLED_Set_Pos(105,6);
//  OLED_WrDat(0xFF);
//  OLED_Set_Pos(105,7);
//  OLED_WrDat(0xFF);
//}
//void OLED_Show_Frame94(void)
//{ 	
//  //OLED_Set_Pos(2,0);//第0行，第13列
//  //OLED_WrDat(0xFF); //画竖线
//  //OLED_Set_Pos(2,1);
//  //OLED_WrDat(0xFF); 
//  OLED_Set_Pos(17,2);
//  OLED_WrDat(0xFF); 
//  OLED_Set_Pos(17,3);
//  OLED_WrDat(0xFF); 
//  OLED_Set_Pos(17,4);
//  OLED_WrDat(0xFF); 
//  OLED_Set_Pos(17,5);
//  OLED_WrDat(0xFF);
//  OLED_Set_Pos(17,6);
//  OLED_WrDat(0xFF);
//  OLED_Set_Pos(17,7);
//  OLED_WrDat(0xFF);
//  
//  //OLED_Set_Pos(112,0);
//  //OLED_WrDat(0xFF); 
//  //OLED_Set_Pos(112,1);
//  //OLED_WrDat(0xFF); 
//  OLED_Set_Pos(112,2);
//  OLED_WrDat(0xFF); 
//  OLED_Set_Pos(112,3);
//  OLED_WrDat(0xFF); 
//  OLED_Set_Pos(112,4);
//  OLED_WrDat(0xFF); 
//  OLED_Set_Pos(112,5);
//  OLED_WrDat(0xFF);
//  OLED_Set_Pos(112,6);
//  OLED_WrDat(0xFF);
//  OLED_Set_Pos(112,7);
//  OLED_WrDat(0xFF);
//}