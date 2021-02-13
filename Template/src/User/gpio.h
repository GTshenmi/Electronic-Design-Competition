#ifndef  _GPIO_H_
#define  _GPIO_H_

#define IO_Scan_Interval 20

typedef enum
{
    Low = 0,
    High = 1,
    Reverse = 2,
    //NotSetState = 3,
    IOTaskInitState = 3,
}io_state_t;

typedef struct
{
    PTXn_e     Ptx_n;
    GPIO_CFG   IOConfig;
    uint16_t   IOState;
    bool       UsingDefaultConfig;

}io_handle_t;

typedef struct
{
    io_handle_t Handle;
    
    uint32_t ReverseTime;
    uint32_t ReverseCount;
    
    bool IO_SHIELD;
    
}GPIO_TypeDef;

#define IOA1    IO[0]
#define IOA2    IO[1]
#define IOA3    IO[2]
#define IOA4    IO[3]
#define IOA5    IO[4]
#define IOA6    IO[5]

#define IOB1    IO[6]
#define IOB2    IO[7]
#define IOB3    IO[8]
#define IOB4    IO[9]
#define IOB5    IO[10]
#define IOB6    IO[11]

extern GPIO_TypeDef IO[12];

void GPIO_Init(GPIO_TypeDef *IO,io_handle_t *handle);
void GPIO_DeInit(GPIO_TypeDef *IO);

void GPIO_SetReverseTime(GPIO_TypeDef *IO,uint32_t ms);

void Task_IOScan();

#endif