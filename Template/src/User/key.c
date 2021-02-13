#include "include.h"
#include "key.h"

void KEY_Init()
{
    GPIO_PinInit(KEY0_GPIO_PIN,GPI,0);
    GPIO_PinInit(KEY1_GPIO_PIN,GPI,0);
    GPIO_PinInit(KEY2_GPIO_PIN,GPI,0);
    GPIO_PinInit(KEY3_GPIO_PIN,GPI,0);
    GPIO_PinInit(KEY4_GPIO_PIN,GPI,0);
    GPIO_PinInit(KEY5_GPIO_PIN,GPI,0);
}

static void Get_Key_Level(void)
{
    uint8_t i;
    
    for(i = 0;i < KEY_NUM;i++)
    {
        if(KEY[i].KeyShield == 0)
            continue;
        if(KEY[i].ReadPin() == KEY[i].DownLevel)
            KEY[i].Level = 1;
        else
            KEY[i].Level = 0;
    }
}

void ReadKeyStatus(void)
{
    uint8_t i;
	
    Get_Key_Level();
	
    for(i = 0;i < KEY_NUM;i++)
    {
        switch(KEY[i].State)
        {
            //״̬0��û�а�������
            case KEY_NULL:
                if(KEY[i].Level == 1)//�а�������
                {
                    KEY[i].State = KEY_SURE;//ת��״̬1
					KEY[i].Event = KEY_NULL;//���¼�
                }
                else
                {
                    KEY[i].Event = KEY_NULL;//���¼�
                }
                break;
            //״̬1����������ȷ��
            case KEY_SURE:
                if(KEY[i].Level == 1)//ȷ�Ϻ��ϴ���ͬ
                {
                    KEY[i].State = KEY_DOWN;//ת��״̬2
		    KEY[i].Event = KEY_DOWN;//�����¼�
                    KEY[i].Count = 0;//����������
                }
                else
                {
                    KEY[i].State = KEY_NULL;//ת��״̬0
                    KEY[i].Event = KEY_NULL;//���¼�
                }
                break;
            //״̬2����������
            case KEY_DOWN:
                if(KEY[i].Level != 1)//�����ͷţ��˿ڸߵ�ƽ
                {
                    KEY[i].State = KEY_NULL;//ת��״̬0
                    KEY[i].Event = KEY_UP;//�ɿ��¼�
                }
                else if((KEY[i].Level == 1) && (++KEY[i].Count >= KEY_LONG_DOWN_DELAY)) //����KEY_LONG_DOWN_DELAYû���ͷ�
                {
                    KEY[i].State = KEY_LONG;//ת��״̬3
                    KEY[i].Event = KEY_LONG;//�����¼�
                    KEY[i].Count = 0;//����������
                }
                else
                {
                    KEY[i].Event = KEY_NULL;//���¼�
                }
                break;
            //״̬3��������������
            case KEY_LONG:
                if(KEY[i].Level != 1)//�����ͷţ��˿ڸߵ�ƽ
                {
                    KEY[i].State = KEY_NULL;//ת��״̬0
                    KEY[i].Event = KEY_UP;//�ɿ��¼�
					KEY[i].Event = KEY_NULL;
                }
                else if((KEY[i].Level == 1) 
                && (++KEY[i].Count >= KEY_LONG_DOWN_DELAY)) //����KEY_LONG_DOWN_DELAYû���ͷ�
                {
                    KEY[i].Event = KEY_LONG;//�����¼�
                    KEY[i].Count = 0;//����������
                }
                else
                {
                    KEY[i].Event = KEY_NULL;//���¼�
                }
                break;
        }
	}
}

__weak void Task_KEY_Scan(void)
{
	ReadKeyStatus();
	
	
	if(KeyUp.Event == KEY_UP)
	{
            
            LCD.Write.XLine(18,"KeyUp Pressed\n");
            KeyUp.PressedCallBack();
	}
	else if(KeyUp.Event == KEY_LONG)
	{
            LCD.Write.XLine(18,"KeyUp Long Pressed\n");
            KeyUp.LongPressedCallBack();
	}

	
	if(KeyDown.Event == KEY_UP)
	{
            KeyDown.PressedCallBack();
            LCD.Write.XLine(18,"KeyDown Pressed\n");
	}
	else if(KeyDown.Event == KEY_LONG)
	{
            KeyDown.PressedCallBack();
	    LCD.Write.XLine(18,"KeyDown Long Pressed\n");
	} 

        
	if(KeyLeft.Event == KEY_UP)
	{
            KeyLeft.PressedCallBack();
	    LCD.Write.XLine(18,"KeyLeft Pressed\n");
	}
	else if(KeyLeft.Event == KEY_LONG)
	{
            KeyLeft.LongPressedCallBack();
            LCD.Write.XLine(18,"KeyLeft Long Pressed\n");
	} 

        
	if(KeyRight.Event == KEY_UP)
	{
            KeyRight.PressedCallBack();
            LCD.Write.XLine(18,"KeyRight Pressed\n");
	}
	else if(KeyRight.Event == KEY_LONG)
	{
            KeyRight.LongPressedCallBack();
            LCD.Write.XLine(18,"KeyRight Long Pressed\n");
	} 

        
        if(KeyCenter.Event == KEY_UP)
	{
            KeyCenter.PressedCallBack();
            LCD.Write.XLine(18,"KeyCenter Pressed\n");
	}
	else if(KeyCenter.Event == KEY_LONG)
	{
            KeyCenter.LongPressedCallBack();
            LCD.Write.XLine(18,"KeyCenter Long Pressed\n");
	} 
        
}

static void KeyPressedDefaultCallBack()
{
    
}
static void KeyLongPressedDefaultCallBack()
{
  
}

static uint8_t KEY0_ReadPin(void)
{
    return _KEY0;
}

static uint8_t KEY1_ReadPin(void)
{
    return _KEY1;
}

static uint8_t KEY2_ReadPin(void)
{
    return _KEY2;
}
static uint8_t KEY3_ReadPin(void)
{
    return _KEY3;
}

static uint8_t KEY4_ReadPin(void)
{
    return _KEY4;
}

static uint8_t KEY5_ReadPin(void)
{
    return _KEY5;
}

KEY_COMPONENTS KEY[KEY_NUM] = {
{1,0,0,0,KEY_NULL,KEY_NULL,KEY0_ReadPin,KeyPressedDefaultCallBack,KeyLongPressedDefaultCallBack},
{1,0,0,0,KEY_NULL,KEY_NULL,KEY1_ReadPin,KeyPressedDefaultCallBack,KeyLongPressedDefaultCallBack},
{1,0,0,0,KEY_NULL,KEY_NULL,KEY2_ReadPin,KeyPressedDefaultCallBack,KeyLongPressedDefaultCallBack},
{1,0,0,0,KEY_NULL,KEY_NULL,KEY3_ReadPin,KeyPressedDefaultCallBack,KeyLongPressedDefaultCallBack},
{1,0,0,0,KEY_NULL,KEY_NULL,KEY4_ReadPin,KeyPressedDefaultCallBack,KeyLongPressedDefaultCallBack},
{1,0,0,0,KEY_NULL,KEY_NULL,KEY5_ReadPin,KeyPressedDefaultCallBack,KeyLongPressedDefaultCallBack},
};