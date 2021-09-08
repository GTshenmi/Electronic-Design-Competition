//#ifndef _KEY_H_
//#define _KEY_H_
//
//#define KEY_LONG_DOWN_DELAY 10
//
//#define __ROW0_GPIO_PIN PTA19
//#define __ROW1_GPIO_PIN PTA19
//#define __ROW2_GPIO_PIN PTA19
//#define __COL0_GPIO_PIN PTA19
//#define __COL1_GPIO_PIN PTA19
//#define __COL2_GPIO_PIN PTA19
//
//
//#define __ROW0 GPIO_PinRead(__ROW0_GPIO_PIN)
//#define __ROW1 GPIO_PinRead(__ROW1_GPIO_PIN)
//#define __ROW2 GPIO_PinRead(__ROW2_GPIO_PIN)
//#define __COL0 GPIO_PinRead(__COL0_GPIO_PIN)
//#define __COL1 GPIO_PinRead(__COL1_GPIO_PIN)
//#define __COL2 GPIO_PinRead(__COL2_GPIO_PIN)
//
//
//typedef enum _KEY_STATUS_LIST
//{
//	KEY_NULL = 0x00,
//	KEY_SURE = 0x01,
//	KEY_UP   = 0x02,
//	KEY_DOWN = 0x04,
//	KEY_LONG = 0x08,
//}KEY_STATUS_LIST;
//typedef enum _KEY_LIST
//{
//	KEY0,
//	KEY1,
//	KEY2,
//	KEY_NUM,
//}KEY_LIST;
//typedef struct _KEY_COMPONENTS
//{
//    uint8_t KEY_SHIELD;       //��������0:���Σ�1:������
//    uint8_t KEY_COUNT;        //������������
//    uint8_t KEY_LEVEL;        //���⵱ǰIO��ƽ������1��̧��0
//    uint8_t KEY_DOWN_LEVEL;   //����ʱIOʵ�ʵĵ�ƽ
//    uint8_t KEY_STATUS;       //����״̬
//    uint8_t KEY_EVENT;        //�����¼�
//    uint8_t (*READ_PIN)(void);//��IO��ƽ����
//}KEY_COMPONENTS;
//
//typedef struct
//{
//   void (*ReadPin)(void);
//}read_t;
//
//extern read_t Col[3];
//extern read_t Row[3];
//
//
//
//
//extern KEY_COMPONENTS Key_Buf[KEY_NUM];
//
//void KEY_Init();
//void Key_Effect();
//
//#endif