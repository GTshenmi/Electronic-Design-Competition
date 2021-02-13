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
            //状态0：没有按键按下
            case KEY_NULL:
                if(KEY[i].Level == 1)//有按键按下
                {
                    KEY[i].State = KEY_SURE;//转入状态1
					KEY[i].Event = KEY_NULL;//空事件
                }
                else
                {
                    KEY[i].Event = KEY_NULL;//空事件
                }
                break;
            //状态1：按键按下确认
            case KEY_SURE:
                if(KEY[i].Level == 1)//确认和上次相同
                {
                    KEY[i].State = KEY_DOWN;//转入状态2
		    KEY[i].Event = KEY_DOWN;//按下事件
                    KEY[i].Count = 0;//计数器清零
                }
                else
                {
                    KEY[i].State = KEY_NULL;//转入状态0
                    KEY[i].Event = KEY_NULL;//空事件
                }
                break;
            //状态2：按键按下
            case KEY_DOWN:
                if(KEY[i].Level != 1)//按键释放，端口高电平
                {
                    KEY[i].State = KEY_NULL;//转入状态0
                    KEY[i].Event = KEY_UP;//松开事件
                }
                else if((KEY[i].Level == 1) && (++KEY[i].Count >= KEY_LONG_DOWN_DELAY)) //超过KEY_LONG_DOWN_DELAY没有释放
                {
                    KEY[i].State = KEY_LONG;//转入状态3
                    KEY[i].Event = KEY_LONG;//长按事件
                    KEY[i].Count = 0;//计数器清零
                }
                else
                {
                    KEY[i].Event = KEY_NULL;//空事件
                }
                break;
            //状态3：按键连续按下
            case KEY_LONG:
                if(KEY[i].Level != 1)//按键释放，端口高电平
                {
                    KEY[i].State = KEY_NULL;//转入状态0
                    KEY[i].Event = KEY_UP;//松开事件
					KEY[i].Event = KEY_NULL;
                }
                else if((KEY[i].Level == 1) 
                && (++KEY[i].Count >= KEY_LONG_DOWN_DELAY)) //超过KEY_LONG_DOWN_DELAY没有释放
                {
                    KEY[i].Event = KEY_LONG;//长按事件
                    KEY[i].Count = 0;//计数器清零
                }
                else
                {
                    KEY[i].Event = KEY_NULL;//空事件
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