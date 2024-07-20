#ifndef UART_H
#define UART_H

#include <stdint.h>

#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

void uart_begin(uint32_t ubrr);
void uart_send_c(unsigned char c);
unsigned char uart_receive_c();
uint8_t uart_send_s(char* buf);
uint8_t uart_receive_s(char * buf, int max_len); 


#endif