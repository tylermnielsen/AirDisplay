#include "uart.h"
#include <avr/io.h>

void uart_begin(){
    // set baud rate
    UBRR0H = (unsigned char)(MYUBRR>>8);
    UBRR0L = (unsigned char)MYUBRR; 
   
    // set format: 8 data 1 stop bit
    UCSR0B = (3<<UCSZ00);

    // enable receiver and transmitter
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
}

void uart_send_c(unsigned char c){
    // while transmit buffer not empty 
    while(!(UCSR0A & (1<<UDRE0)));
    // write to transmit buffer, sends data 
    UDR0 = c; 
}

unsigned char uart_receive_c(){
    // while data not received 
    while(!(UCSR0A & (1<<RXC0)));
    // get and return data
    return UDR0; 
}

uint8_t uart_send_s(char* buf){
    while(*buf != '\0'){
        uart_send_c(*(buf++)); 
    }
    return 0; 
}

uint8_t uart_receive_s(char * buf, int max_len){
    for(int i = 0; i < max_len; i++){
        unsigned char c = uart_receive_c();
        *(buf++) = c; 
        if(c == '\0') return 0; 
    }
    return 1; 
}