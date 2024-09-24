#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>
#include "uart.h"
#include <stdio.h>
#include <Wire>

#include "BME68x_SensorAPI/bme68x.h"
#include "BME68x_SensorAPI/bme68x_defs.h"


#include "lcd.h"

#define LED_BUILTIN 13

/**
 * D12 (PB4) is RS (register select)
 *  (R/W pin) is ground (always writing?)
 * D11 (PB3) is ENABLE
 * D2 - D5 (PD2-PD5) are DB4-7
 * 
 */

// T = (MOD + 1)/(Fclk / ps)
// MOD = T * (Fclk / ps) - 1
void delay_ms(uint16_t period){
	PRR &= ~(1<<3); // make sure Timer 1 is enabled

	TCNT1 = 0x00; // start at 0
	//          * 9            * .5         *.125 (approximate .1)
	OCR1A = (period * 9) + (period >> 1) + (period >> 3) - 1; // set compare A
	char out[10];
	sprintf(out, "%u\n", OCR1A);
	uart_send_s(out); 

	TIFR1 |= (1 << OCF1A); // clear compare A flag
	TCCR1B |= (1 << CS12) | (1 << CS10); // turn on timer w/ prescaler 1024

	while((TIFR1 & (1 << OCF1A)) == false); // wait for compare A flag to be set
	TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));  // turn off timer
}

void delay_us(uint32_t period, void *intf_ptr){
    TCCR1B = (TCCR1B & ~(0b111)) | 0b001; 
}

int main(){
    _delay_ms(100); 

    
    lcd_begin();

	char o[15];
	sprintf(o, "%lu", F_CPU);
	lcd_write(o);

    // struct bme68x_dev bme_interface;

    // bme_interface.chip_id = BME68X_CHIP_ID;
    // bme_interface.read = &i2c_read;
    // bme_interface.write = &i2c_write;
    // bme_interface.delay_us = &delay_us_mask; 

    uart_begin(); // begin uart and set baud to 9600

    // DDRB |= 0b00100000;

    // PORTB |= 0b00100000; 

    DDRB |= (1<<DDB5); 
    
    while(1){
		uart_send_c('\n');
		delay_ms(1000); 
		

		// uart_receive_s(buf, 10);
		// uart_send_s(buf);

        // PORTB |= (1<<PORTB5);

        // _delay_ms(500);

        // PORTB &= ~(1<<PORTB5);

        // _delay_ms(500); 

    }



    return 0; 
}