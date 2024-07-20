#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>
#include "i2c.h"

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

volatile bool overflowed = 0; 
void timer_overflow(){ 
    overflowed = 1;
}

void delay_us_mask(uint32_t period, void *intf_ptr){
    for(uint32_t i = 0; i < period; i++){
        _delay_us(1); 
    }
}

int main(){
    _delay_ms(100); 

    // set pin 13 to output
    
    lcd_begin();

    lcd_write("Hello Dude!");

    struct bme68x_dev bme_interface;

    bme_interface.chip_id = 
    bme_interface.read = &i2c_read;
    bme_interface.write = &i2c_write;
    bme_interface.delay_us = &delay_us_mask; 

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