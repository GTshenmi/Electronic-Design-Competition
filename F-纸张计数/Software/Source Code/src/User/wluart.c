#include  "include.h"
#include "wluart.h"
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc����  ʹ�ô���4��Ϊprintf�Ĵ�ӡ��
int fputc(int ch, FILE *f)
{ 	
//    while(!(UART_S1_REG(UARTN[0]) & UART_S1_TDRE_MASK));
//    //��������
//    UART_D_REG(UARTN[0]) = (uint8)ch;
//	return ch;

	//static int y=-1;
	if(ch == '\n')    //����
        {
            OLED.Cursor.x = 0;
            OLED.Cursor.y+= OLED.Font.Hight;
            return ch;
	}
        if(OLED.Cursor.x > (OLED.Width - OLED.Font.Width) )
	{
            OLED.Cursor.x = 0; 	//x����
            OLED.Cursor.y+= OLED.Font.Hight;
           // LCD.Font.Backcolor=YELLOW;
        }
        if(OLED.Cursor.y > OLED.Hight - OLED.Font.Hight) 
	{
		OLED.Cursor.x=0;OLED.Cursor.y=0;
		//OLED_CLS();
		return ch;  //ֱ���˳�
	}

        
	//OLED_P6x8Str(OLED.Cursor.x,OLED.Cursor.y/OLED.Font.Hight,(unsigned char *)&ch); 	//��ӡ�ַ�ch
        OLED_P6x8Str(OLED.Cursor.x,OLED.Cursor.y,(unsigned char *)&ch); 
	OLED.Cursor.x += OLED.Font.Width; 											//��ת����һ��λ��, �Ƿ�Խ�������溯���ж�			

	return ch;
}

//int fgetc(FILE *f)
//{
 // /* �ȴ������������� */
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

        
        //ʹ������ķ�ʽ ������˵�κ�����·��͵ĳ��ȶ����ܳ���30���ֽ�
        //����Ϊ30���ֽ���Ϊ�˱�֤�������������ݵ�ʱ�򲻻����ģ��BUFF���������Ϊ30���������б��ϵġ�
        //���跢�����ݱȽ�������ô�����ǿ��Գ���30���ֽڵģ������漰���Ĳ����Ƚ϶࣬�������ﲻ�����һ����׼�Ĵ�
        //�����ʹ�õ�ʱ��������н��в����¡�
        //�����һ���ο������� ����2Mbps ������460800 �޵�Ÿ��� ͨ������
        //���40ms��һ������ ��ÿ�η���1000�ֽ�Ҳ�ǿ��е�
        

        //ʹ�ô˷�����ȱ������ÿ�η�������ǰ�����RTS���м��
        //�����������Բ���ȥ����ÿ�η��͵ĳ���
        //�������ʹ��while�ȴ�����ʵ���Խ�RTS���Žӵ��ж����ţ�ͨ���ж�����֪��Ƭ����ǰģ���Ƿ���Խ������ݡ�
        //����Գ��� ��test�������������һЩ����
        //while(GPIO_PinRead(WLUART_RTS_GPIO_PIN));   //�ȴ�ģ����Խ�������
         UART_PutStr(WLUART,str);
}



