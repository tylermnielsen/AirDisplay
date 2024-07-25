#ifndef UART_H
#define UART_H

#include <stdint.h>

#define CLOCK_RATE 16000000UL
#define BAUD 9600
#define MYUBRR (CLOCK_RATE/16UL/BAUD-1)

void uart_begin();
void uart_send_c(unsigned char c);
unsigned char uart_receive_c();
uint8_t uart_send_s(char* buf);
uint8_t uart_receive_s(char * buf, int max_len); 


#endif