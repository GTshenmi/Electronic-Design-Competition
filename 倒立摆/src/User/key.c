//#include "include.h"
//
//void KEY_Init()
//{
//     
//  
//}
//void Key_Effect()
//{
//  
//}
//
//static uint8_t Row0_ReadPin(void)
//{
//    return __ROW0;
//}
//
//static uint8_t Row1_ReadPin(void)
//{
//    return __ROW1;
//}
//
//static uint8_t Row2_ReadPin(void)
//{
//    return __ROW2;
//}
//static uint8_t Col0_ReadPin(void)
//{
//    return __COL0;
//}
//
//static uint8_t Col1_ReadPin(void)
//{
//    return __COL1;
//}
//
//static uint8_t Col2_ReadPin(void)
//{
//    return __COL2;
//}
//
//
//
//static void Get_Key_Level(void)
//{
//    uint8_t i;
//    
//    for(i = 0;i < KEY_NUM;i++)
//    {
//        
////        if(Key_Buf[i].KEY_SHIELD == 0)
////            continue;
////        if(Key_Buf[i].READ_PIN() == Key_Buf[i].KEY_DOWN_LEVEL)
////            Key_Buf[i].KEY_LEVEL = 1;
////        else
////            Key_Buf[i].KEY_LEVEL = 0;
//    }
//}
//
//void ReadKeyStatus(void)
//{
//    uint8_t i;
//	
//    Get_Key_Level();
//	
//    for(i = 0;i < KEY_NUM;i++)
//    {
//        switch(Key_Buf[i].KEY_STATUS)
//        {
//            //状态0：没有按键按下
//            case KEY_NULL:
//                if(Key_Buf[i].KEY_LEVEL == 1)//有按键按下
//                {
//                    Key_Buf[i].KEY_STATUS = KEY_SURE;//转入状态1
//                    Key_Buf[i].KEY_EVENT = KEY_NULL;//空事件
//                }
//                else
//                {
//                    Key_Buf[i].KEY_EVENT = KEY_NULL;//空事件
//                }
//                break;
//            //状态1：按键按下确认
//            case KEY_SURE:
//                if(Key_Buf[i].KEY_LEVEL == 1)//确认和上次相同
//                {
//                    Key_Buf[i].KEY_STATUS = KEY_DOWN;//转入状态2
//					Key_Buf[i].KEY_EVENT = KEY_DOWN;//按下事件
//                    Key_Buf[i].KEY_COUNT = 0;//计数器清零
//                }
//                else
//                {
//                    Key_Buf[i].KEY_STATUS = KEY_NULL;//转入状态0
//                    Key_Buf[i].KEY_EVENT = KEY_NULL;//空事件
//                }
//                break;
//            //状态2：按键按下
//            case KEY_DOWN:
//                if(Key_Buf[i].KEY_LEVEL != 1)//按键释放，端口高电平
//                {
//                    Key_Buf[i].KEY_STATUS = KEY_NULL;//转入状态0
//                    Key_Buf[i].KEY_EVENT = KEY_UP;//松开事件
//                }
//                else if((Key_Buf[i].KEY_LEVEL == 1) && (++Key_Buf[i].KEY_COUNT >= KEY_LONG_DOWN_DELAY)) //超过KEY_LONG_DOWN_DELAY没有释放
//                {
//                    Key_Buf[i].KEY_STATUS = KEY_LONG;//转入状态3
//                    Key_Buf[i].KEY_EVENT = KEY_LONG;//长按事件
//					Key_Buf[i].KEY_COUNT = 0;//计数器清零
//                }
//                else
//                {
//                    Key_Buf[i].KEY_EVENT = KEY_NULL;//空事件
//                }
//                break;
//            //状态3：按键连续按下
//            case KEY_LONG:
//                if(Key_Buf[i].KEY_LEVEL != 1)//按键释放，端口高电平
//                {
//                    Key_Buf[i].KEY_STATUS = KEY_NULL;//转入状态0
//                    Key_Buf[i].KEY_EVENT = KEY_UP;//松开事件
//					Key_Buf[i].KEY_EVENT = KEY_NULL;
//                }
//                else if((Key_Buf[i].KEY_LEVEL == 1) && (++Key_Buf[i].KEY_COUNT >= KEY_LONG_DOWN_DELAY)) //超过KEY_LONG_DOWN_DELAY没有释放
//                {
//                    Key_Buf[i].KEY_EVENT = KEY_LONG;//长按事件
//                    Key_Buf[i].KEY_COUNT = 0;//计数器清零
//                }
//                else
//                {
//                    Key_Buf[i].KEY_EVENT = KEY_NULL;//空事件
//                }
//                break;
//        }
//	}
//}
//
////KEY_COMPONENTS Key_Buf[KEY_NUM] = {
////{1,0,0,0,KEY_NULL,KEY_NULL,KEY0_ReadPin},
////{1,0,0,0,KEY_NULL,KEY_NULL,KEY1_ReadPin},
////{1,0,0,0,KEY_NULL,KEY_NULL,KEY2_ReadPin},
////};