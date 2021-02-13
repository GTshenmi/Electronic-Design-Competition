#ifndef _UART_H_
#define _UART_H_

typedef struct
{
    UART_Type *uartn;
    uint32 baud;
    bool UsingDefaultConfig;
    bool IsSendingData;
}uart_handle_t;


typedef struct
{
    uart_handle_t Handle; 
    uint8_t Cache[50];
    uint16_t Pointer;
    uint16_t ReceiveLen;
    
    bool CacheIsFull;
    bool StartReceive;
    
    bool Is_Run;
}uart_t;

//#define UART3_Printf(format,ap) UARTx_Printf(&Uart[0],format,ap)
//#define UART4_Printf(format,ap) UARTx_Printf(&Uart[1],format,ap)

extern uart_t uart[2];


void UARTx_Init(uart_t *uart,uart_handle_t *handle);
void UARTxCreateHandle(uart_t *uart,uart_handle_t *handle);
void UARTxCreateDefaultHandle(uart_handle_t *handle);
void UART3_Printf(const char *format,...);
void UART4_Printf(const char *format,...);
void UARTx_Printf(uart_t *uart,const char *format,...);
void UARTx_SendStr(uart_t *uart,unsigned char *str);


#endif
