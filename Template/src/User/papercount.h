#ifndef _PAPERCOUNT_H_
#define _PAPERCOUNT_H_

extern uint32_t num;
extern uint32_t PaperIndex[];
extern uint32_t totaltime;
extern bool StartCount;

void PaperCount();
void PaperCount_OLED_Display(void);
uint16_t CountPaperNum(uint32_t C);

void PaperCount_KEY_Init(void);
uint8_t PaperCount_KEY_Read(uint8_t mode);
void PaperCount_Key_Effect(void);

uint32_t ResultFilter(uint32_t *Result,uint16_t len);
uint32_t FDC_SlidingMedianFilter(unsigned int delay_time);

#endif

