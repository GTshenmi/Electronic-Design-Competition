#ifndef _KEY_H_
#define _KEY_H_

#define KEY_LONG_DOWN_DELAY 10

#define KEY0_GPIO_PIN PTE26 //�����ú�KEY1 ��ͬ
#define KEY1_GPIO_PIN PTE26
#define KEY2_GPIO_PIN PTE27
#define KEY3_GPIO_PIN PTE28
#define KEY4_GPIO_PIN PTA4
#define KEY5_GPIO_PIN PTA5

#define _KEY0  GPIO_PinRead(KEY0_GPIO_PIN)
#define _KEY1  GPIO_PinRead(KEY1_GPIO_PIN)
#define _KEY2  GPIO_PinRead(KEY2_GPIO_PIN)
#define _KEY3  GPIO_PinRead(KEY3_GPIO_PIN)
#define _KEY4  GPIO_PinRead(KEY4_GPIO_PIN)
#define _KEY5  GPIO_PinRead(KEY5_GPIO_PIN)

#define KeyUp     KEY[KEY2]
#define KeyDown   KEY[KEY4]
#define KeyLeft   KEY[KEY1]
#define KeyRight  KEY[KEY5]
#define KeyCenter KEY[KEY3]

typedef enum _KEY_STATUS_LIST
{
	KEY_NULL = 0x00,
	KEY_SURE = 0x01,
	KEY_UP   = 0x02,
	KEY_DOWN = 0x04,
	KEY_LONG = 0x08,
}KEY_STATUS_LIST;
typedef enum _KEY_LIST
{
	KEY0,
	KEY1,
	KEY2,
        KEY3,
        KEY4,
        KEY5,
	KEY_NUM,
}KEY_LIST;

typedef struct _KEY_COMPONENTS
{
    
    uint8_t KeyShield;       //��������0:���Σ�1:������
    uint8_t Count;        //������������
    uint8_t Level;        //���⵱ǰIO��ƽ������1��̧��0
    uint8_t DownLevel;   //����ʱIOʵ�ʵĵ�ƽ
    uint8_t State;       //����״̬
    uint8_t Event;        //�����¼�
    uint8_t (*ReadPin)(void);//��IO��ƽ����
    void (*PressedCallBack)();
    void (*LongPressedCallBack)();
    
}KEY_COMPONENTS;

extern KEY_COMPONENTS KEY[KEY_NUM];

void KEY_Init();
__weak void Task_KEY_Scan(void); //call it in interrupt every 20ms 

#endif