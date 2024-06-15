#include <avr/io.h>
#include <util/delay.h>

#define LED_BUILTIN 13

int main(){

    // set pin 13 to output
    PORTB |= 0b00100000;
    
    while(1){
        
        DDRB |= 0b00100000;

        _delay_ms(100);

        DDRB &= 0b11011111;

        _delay_ms(100); 

    }



    return 0; 
}