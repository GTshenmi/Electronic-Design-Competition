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
//            //״̬0��û�а�������
//            case KEY_NULL:
//                if(Key_Buf[i].KEY_LEVEL == 1)//�а�������
//                {
//                    Key_Buf[i].KEY_STATUS = KEY_SURE;//ת��״̬1
//                    Key_Buf[i].KEY_EVENT = KEY_NULL;//���¼�
//                }
//                else
//                {
//                    Key_Buf[i].KEY_EVENT = KEY_NULL;//���¼�
//                }
//                break;
//            //״̬1����������ȷ��
//            case KEY_SURE:
//                if(Key_Buf[i].KEY_LEVEL == 1)//ȷ�Ϻ��ϴ���ͬ
//                {
//                    Key_Buf[i].KEY_STATUS = KEY_DOWN;//ת��״̬2
//					Key_Buf[i].KEY_EVENT = KEY_DOWN;//�����¼�
//                    Key_Buf[i].KEY_COUNT = 0;//����������
//                }
//                else
//                {
//                    Key_Buf[i].KEY_STATUS = KEY_NULL;//ת��״̬0
//                    Key_Buf[i].KEY_EVENT = KEY_NULL;//���¼�
//                }
//                break;
//            //״̬2����������
//            case KEY_DOWN:
//                if(Key_Buf[i].KEY_LEVEL != 1)//�����ͷţ��˿ڸߵ�ƽ
//                {
//                    Key_Buf[i].KEY_STATUS = KEY_NULL;//ת��״̬0
//                    Key_Buf[i].KEY_EVENT = KEY_UP;//�ɿ��¼�
//                }
//                else if((Key_Buf[i].KEY_LEVEL == 1) && (++Key_Buf[i].KEY_COUNT >= KEY_LONG_DOWN_DELAY)) //����KEY_LONG_DOWN_DELAYû���ͷ�
//                {
//                    Key_Buf[i].KEY_STATUS = KEY_LONG;//ת��״̬3
//                    Key_Buf[i].KEY_EVENT = KEY_LONG;//�����¼�
//					Key_Buf[i].KEY_COUNT = 0;//����������
//                }
//                else
//                {
//                    Key_Buf[i].KEY_EVENT = KEY_NULL;//���¼�
//                }
//                break;
//            //״̬3��������������
//            case KEY_LONG:
//                if(Key_Buf[i].KEY_LEVEL != 1)//�����ͷţ��˿ڸߵ�ƽ
//                {
//                    Key_Buf[i].KEY_STATUS = KEY_NULL;//ת��״̬0
//                    Key_Buf[i].KEY_EVENT = KEY_UP;//�ɿ��¼�
//					Key_Buf[i].KEY_EVENT = KEY_NULL;
//                }
//                else if((Key_Buf[i].KEY_LEVEL == 1) && (++Key_Buf[i].KEY_COUNT >= KEY_LONG_DOWN_DELAY)) //����KEY_LONG_DOWN_DELAYû���ͷ�
//                {
//                    Key_Buf[i].KEY_EVENT = KEY_LONG;//�����¼�
//                    Key_Buf[i].KEY_COUNT = 0;//����������
//                }
//                else
//                {
//                    Key_Buf[i].KEY_EVENT = KEY_NULL;//���¼�
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