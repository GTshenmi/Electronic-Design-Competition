#include  "include.h"
#include "wluart.h"
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数  使用串口4作为printf的打印口
int fputc(int ch, FILE *f)
{ 	
//    while(!(UART_S1_REG(UARTN[0]) & UART_S1_TDRE_MASK));
//    //发送数据
//    UART_D_REG(UARTN[0]) = (uint8)ch;
//	return ch;

	//static int y=-1;
	if(ch == '\n')    //换行
        {
            OLED.Cursor.x = 0;
            OLED.Cursor.y+= OLED.Font.Hight;
            return ch;
	}
        if(OLED.Cursor.x > (OLED.Width - OLED.Font.Width) )
	{
            OLED.Cursor.x = 0; 	//x置零
            OLED.Cursor.y+= OLED.Font.Hight;
           // LCD.Font.Backcolor=YELLOW;
        }
        if(OLED.Cursor.y > OLED.Hight - OLED.Font.Hight) 
	{
		OLED.Cursor.x=0;OLED.Cursor.y=0;
		//OLED_CLS();
		return ch;  //直接退出
	}

        
	//OLED_P6x8Str(OLED.Cursor.x,OLED.Cursor.y/OLED.Font.Hight,(unsigned char *)&ch); 	//打印字符ch
        OLED_P6x8Str(OLED.Cursor.x,OLED.Cursor.y,(unsigned char *)&ch); 
	OLED.Cursor.x += OLED.Font.Width; 											//跳转到下一个位置, 是否越界有上面函数判断			

	return ch;
}

//int fgetc(FILE *f)
//{
 // /* 等待串口输入数据 */
 // while (!(WLUART->S1 & UART_S1_RDRF_MASK));
 // return (int)UART_GetChar(WLUART);
//}

void WLUART_Init()
{
    GPIO_PinInit(WLUART_RTS_GPIO_PIN,GPI,0);
    UART_Init(WLUART,115200);
    NVIC_EnableIRQ(WLUART_IRQn);
   // if(!GPIO_PinRead(WLUART_RTS_GPIO_PIN))  
     //printf("\r\nInit Success!\r\n");
}
void WLUART_SendData(char *str)
{

        
        //使用上面的方式 并不是说任何情况下发送的长度都不能超过30个字节
        //限制为30个字节是为了保证在连续发送数据的时候不会出现模块BUFF溢出，限制为30这样是最有保障的。
        //假设发送数据比较慢，那么长度是可以超过30个字节的，由于涉及到的参数比较多，所以这里不变给出一个标准的答案
        //大家在使用的时候可以自行进行测试下。
        //这里给一个参考的数据 空速2Mbps 波特率460800 无电磁干扰 通信良好
        //如果40ms发一次数据 则每次发送1000字节也是可行的
        

        //使用此方法，缺点在于每次发送数据前都会对RTS进行检测
        //但是这样可以不用去控制每次发送的长度
        //如果不想使用while等待的其实可以将RTS引脚接到中断引脚，通过中断来告知单片机当前模块是否可以接受数据。
        //你可以尝试 将test里面的数据增加一些数据
        //while(GPIO_PinRead(WLUART_RTS_GPIO_PIN));   //等待模块可以接受数据
         UART_PutStr(WLUART,str);
}



