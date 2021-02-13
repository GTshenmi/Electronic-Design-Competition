#ifndef _LED_H
#define _LED_H

#define LED_COUNT_INFINITY -1

#define LED0 LED[0]
#define LED1 LED[1]
#define LED2 LED[2]
#define LED3 LED[3]

typedef struct
{
    uint8_t LED_NUM;
    uint32_t ToggleTime;
    uint32_t ToggleCount;
    int16_t ToggleTimes;
    state_t State;
    bool IO_SHIELD; 
}led_t;

extern led_t LED[4];

void LED_Init(void);

void LED_ON(uint8_t led);

void LED_OFF(uint8_t led);

void LED_Reverse(uint8_t led);

void Task_LEDScan();

void LED_Test();
void Test_LED(void);

#endif