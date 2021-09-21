#ifndef _WLUART_H_
#define _WLUART_H_

#define WLUART                  UART0
#define WLUART_RTS_GPIO_PIN     PTD9
#define WLUART_IRQn UART0_RX_TX_IRQn

void WLUART_Init();
void WLUART_SendData(char *str);

#endif