#ifndef _KEY_H_
#define _KEY_H_


extern uint8_t Key_effect_flag;
extern uint8_t Page;
extern uint8_t Selection;
extern uint8_t Key_pointer;
extern uint32_t Select_Num;
extern uint8_t StartCar_flag;

extern bool StartCount;

void KEY_Init(void);

void Key_Effect(void);

extern bool Start_Car;

#endif