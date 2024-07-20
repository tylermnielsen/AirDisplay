// #include <avr/io.h>
// #include <util/delay.h>
// #include <stdbool.h>
// #include <stdint.h>
// #include "i2c.h"
// #include "uart.h"

// #include "BME68x_SensorAPI/bme68x.h"
// #include "BME68x_SensorAPI/bme68x_defs.h"


// #include "lcd.h"

// #define LED_BUILTIN 13

// /**
//  * D12 (PB4) is RS (register select)
//  *  (R/W pin) is ground (always writing?)
//  * D11 (PB3) is ENABLE
//  * D2 - D5 (PD2-PD5) are DB4-7
//  * 
//  */

// volatile bool overflowed = 0; 
// void timer_overflow(){ 
//     overflowed = 1;
// }

// void delay_us_mask(uint32_t period, void *intf_ptr){
//     for(uint32_t i = 0; i < period; i++){
//         _delay_us(1); 
//     }
// }

// int main(){
//     _delay_ms(100); 

    
//     // lcd_begin();

//     // lcd_write("Hello Dude!");

//     // struct bme68x_dev bme_interface;

//     // bme_interface.chip_id = 
//     // bme_interface.read = &i2c_read;
//     // bme_interface.write = &i2c_write;
//     // bme_interface.delay_us = &delay_us_mask; 


//     //uart_begin(MYUBRR); // begin uart and set baud to 9600

//     // DDRB |= 0b00100000;

//     // PORTB |= 0b00100000; 

//     DDRB |= (1<<DDB5); 
    
//     while(1){
//         uart_send_c('h');

//         PORTB |= (1<<PORTB5);

//         _delay_ms(500);

//         PORTB &= ~(1<<PORTB5);

//         _delay_ms(500); 

//     }



//     return 0; 
// }

/*
* usart.c
*
* Created : 15-08-2020 07:24:45 PM
* Author  : Arnab Kumar Das
* Website : www.ArnabKumarDas.com
*/

// #define F_CPU 16000000UL // Defining the CPU Frequency

#include <avr/io.h>      // Contains all the I/O Register Macros
#include <util/delay.h>  // Generates a Blocking Delay

#define USART_BAUDRATE 9600 // Desired Baud Rate
#define BAUD_PRESCALER (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#define ASYNCHRONOUS (0<<UMSEL00) // USART Mode Selection

#define DISABLED    (0<<UPM00)
#define EVEN_PARITY (2<<UPM00)
#define ODD_PARITY  (3<<UPM00)
#define PARITY_MODE  DISABLED // USART Parity Bit Selection

#define ONE_BIT (0<<USBS0)
#define TWO_BIT (1<<USBS0)
#define STOP_BIT ONE_BIT      // USART Stop Bit Selection

#define FIVE_BIT  (0<<UCSZ00)
#define SIX_BIT   (1<<UCSZ00)
#define SEVEN_BIT (2<<UCSZ00)
#define EIGHT_BIT (3<<UCSZ00)
#define DATA_BIT   EIGHT_BIT  // USART Data Bit Selection

void USART_Init()
{
	// Set Baud Rate
	UBRR0H = BAUD_PRESCALER >> 8;
	UBRR0L = BAUD_PRESCALER;
	
	// Set Frame Format
	UCSR0C = ASYNCHRONOUS | PARITY_MODE | STOP_BIT | DATA_BIT;
	
	// Enable Receiver and Transmitter
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
}

void USART_TransmitPolling(uint8_t DataByte)
{
	while (( UCSR0A & (1<<UDRE0)) == 0) {}; // Do nothing until UDR is ready
	UDR0 = DataByte;
}

int main()
{
	USART_Init();
	while (1)
	{
		USART_TransmitPolling('A');
		USART_TransmitPolling('R');
		USART_TransmitPolling('N');
		USART_TransmitPolling('A');
		USART_TransmitPolling('B');
		USART_TransmitPolling('\n');
		_delay_ms(1000);
	}
	return 0;
}