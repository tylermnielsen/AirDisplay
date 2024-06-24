#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>

#include "lcd.h"

#define LED_BUILTIN 13

/**
 * D12 (PB4) is RS (register select)
 *  (R/W pin) is ground (always writing?)
 * D11 (PB3) is ENABLE
 * D2 - D5 (PD2-PD5) are DB4-7
 * 
 */


int main(){
    _delay_ms(100); 

    // set pin 13 to output
    
    lcd_begin();

    lcd_write("Hello Dude!");

    _delay_ms(10); 

    // DDRB |= 0b00100000;

    // PORTB |= 0b00100000; 

    // DDRB |= (1<<DDB4); 
    
    while(1){

        // PORTB |= (1<<PORTB4);

        // _delay_ms(100);

        // PORTB &= ~(1<<PORTB4);

        // _delay_ms(100); 

    }



    return 0; 
}