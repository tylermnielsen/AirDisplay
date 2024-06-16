#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>

#define LED_BUILTIN 13

/**
 * D12 (PB4) is RS (register select)
 *  (R/W pin) is ground (always writing?)
 * D11 (PB3) is ENABLE
 * D2 - D5 (PD2-PD5) are DB4-7
 * 
 */

void toggleEnable(){
    // enable
    DDRB &= ~(0b1 << 3);
    _delay_ms(1); 
    DDRB |= (0b1 << 3);
    _delay_ms(1);
    // disable
    DDRB &= ~(0b1 << 3);
    _delay_ms(100); 
}

void send4(uint8_t rs, uint8_t data){
    if(rs == 1){
        PORTB |= (0b1 << 4);
    }

    PORTD |= (data << 2) | 0b11000011; 

    toggleEnable(); 

    PORTB &= ~(0b1 << 4);
    _delay_ms(100);
}

void begin(){
     // set pins 12, 11 to output
    DDRB |= 0b00011000;
    // set pins 5-2 to output
    DDRD |= 0b00111100;

    _delay_ms(500); 
    
    send4(0, 0b0011); 
    _delay_ms(5);
    send4(0, 0b0011); 
    _delay_ms(5); 
    send4(0, 0b0011); 

    send4(0, 0b0010); // set interface to be 4 bits long
    
    send4(0, 0b0010); // function set (display lines and char font)
    send4(0, 0b1000);  // 0000? NF**

    send4(0, 0b0000); // display off
    send4(0, 0b1000); 

    send4(0, 0b0000); // display clear
    send4(0, 0b0001); 

    send4(0, 0b0000); // entry mode set
    send4(0, 0b0110); // I/D S

}

void transfer(bool datareg, uint8_t data){

    send4(datareg, data >> 4);

    send4(datareg, data & 0b00001111);

    _delay_ms(2); 
}

int main(){
    _delay_ms(100); 

    // set pin 13 to output
    DDRB |= 0b00100000;
    
    begin();

   // transfer(1, 0b00000011);
    
    while(1){
        
        PORTB |= 0b00100000;

        _delay_ms(100);

        PORTB &= 0b11011111;

        _delay_ms(100); 

    }



    return 0; 
}