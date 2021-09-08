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
//    uint8_t KEY_SHIELD;       //按键屏蔽0:屏蔽，1:不屏蔽
//    uint8_t KEY_COUNT;        //按键长按计数
//    uint8_t KEY_LEVEL;        //虚拟当前IO电平，按下1，抬起0
//    uint8_t KEY_DOWN_LEVEL;   //按下时IO实际的电平
//    uint8_t KEY_STATUS;       //按键状态
//    uint8_t KEY_EVENT;        //按键事件
//    uint8_t (*READ_PIN)(void);//读IO电平函数
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