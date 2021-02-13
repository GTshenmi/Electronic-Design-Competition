#include "include.h"
#include "uart.h"

void UART3_RX_TX_IRQHandler()
{
   if(uart[0].Is_Run)
   {
      if(UART3_S1 & UART_S1_RDRF_MASK)
      {
          if(uart[0].StartReceive)
          {
              for(int i = 0;i<uart[0].Pointer;i++)
                uart[0].Cache[i] = ' ';
              uart[0].CacheIsFull = false;
              uart[0].Pointer = 0;
              uart[0].StartReceive = false;
          }
          if(uart[0].Pointer>=50)
          {
            uart[0].Pointer = 0;
            uart[0].CacheIsFull = true;
          }
          if(!uart[0].CacheIsFull)
          {
              uart[0].Pointer = 0;
              for(int i = 0;i < uart[0].ReceiveLen;i++)
              {
                //while(!(UART_S1_REG(uart[1].Handle.uartn) & UART_S1_TDRE_MASK));
                uart[0].Cache[uart[0].Pointer] = UART_GetChar(uart[0].Handle.uartn);
                uart[0].Pointer++;
              }
              if(uart[0].Pointer >= (uart[0].ReceiveLen - 1))
              {
                  uart[0].CacheIsFull = true;
                  for(int i = uart[0].Pointer;i<50;i++)
                  {
                      uart[0].Cache[i] = ' ';
                  }
              }
              
          }
      }
   }
}
void UART4_RX_TX_IRQHandler()
{
   if(uart[1].Is_Run)
   {
      if(UART4_S1 & UART_S1_RDRF_MASK)
      {
          
          if(uart[1].StartReceive)
          {
              for(int i = 0;i<uart[1].Pointer;i++)
                uart[1].Cache[i] = ' ';
              uart[1].CacheIsFull = false;
              uart[1].Pointer = 0;
              uart[1].StartReceive = false;
          }
          if(uart[1].Pointer>=50)
          {
            uart[1].Pointer = 0;
            uart[1].CacheIsFull = true;
          }
          if(!uart[1].CacheIsFull)
          {
              uart[1].Pointer = 0;
              for(int i = 0;i < uart[1].ReceiveLen;i++)
              {
                //while(!(UART_S1_REG(uart[1].Handle.uartn) & UART_S1_TDRE_MASK));
                uart[1].Cache[uart[1].Pointer] = UART_GetChar(uart[1].Handle.uartn);
                uart[1].Pointer++;
              }
              if(uart[1].Pointer >= (uart[1].ReceiveLen - 1))
              {
                  uart[1].CacheIsFull = true;
                  for(int i = uart[1].Pointer;i<50;i++)
                  {
                      uart[1].Cache[i] = ' ';
                  }
              }
              
          }
          //UART4_S1 = UART4_S1 & (~UART_S1_RDRF_MASK);
      }
   }
}

void UARTx_Init(uart_t *uart,uart_handle_t *handle)
{
    UARTxCreateHandle(uart,handle);
    
    UART_Init(uart->Handle.uartn,uart->Handle.baud);
    
    uart->Is_Run = true; 
}

void UARTxCreateHandle(uart_t *uart,uart_handle_t *handle)
{
    if(!handle->UsingDefaultConfig)
    {
        if(handle->baud != NULL)
          uart->Handle.baud = handle->baud;
        if(handle->uartn != NULL)
          uart->Handle.uartn = handle->uartn;
    }
}

void UARTxCreateDefaultHandle(uart_handle_t *handle)
{
    handle->UsingDefaultConfig = true;
    handle->baud = NULL;
    handle->uartn = NULL;
}

void UARTx_SendStr(uart_t *uart,unsigned char *str)
{
    while(*str)
    {
        UART_PutChar(uart->Handle.uartn,*str);
        str++;
    }
}

void UART3_Printf(const char *format,...)
{
   va_list ap;
   va_start(ap,format);
   
   UARTx_Printf(&uart[0],format,ap);
   
   va_end(ap);
}
void UART4_Printf(const char *format,...)
{
   va_list ap;
   va_start(ap,format);
   
   UARTx_Printf(&uart[1],format,ap);
   
   
   va_end(ap);
}

void UARTx_Printf(uart_t *uart,const char *format,...)
{
   uart->Handle.IsSendingData = true;
   
   va_list(ap);
   va_start(ap,format);

   vprintf(format, ap);
   
   va_end(ap);
   
   uart->Handle.IsSendingData = false;
}

uart_t uart[2] = 
{
  [0] = 
  {
     .Handle.uartn = UART3,
     .Handle.baud = 9600,
     .Is_Run = false,
     .CacheIsFull = false,
     .StartReceive = false,
     .ReceiveLen = 0,
     .Pointer = 0,
  },
  
  [1] = 
  {
     .Handle.uartn = UART4, 
     .Handle.baud = 9600,
     .ReceiveLen = 0,
     .Is_Run = false,
     .CacheIsFull = false,
     .StartReceive = false,
     .Pointer = 0,
  }
  
};

