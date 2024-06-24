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

void send4Prep(uint8_t data){
    PORTD &= 0b11000011;
    for (int i = 0; i < 4; i++) {
        PORTD |= (((data >> i) & 0x01) << i) << 4; 
    }

    _delay_us(100); 

    // enable
    PORTB &= ~(1<<PB3);
    _delay_us(1); 
    PORTB |= (1<<PB3);
    _delay_us(1);
    // disable
    PORTB &= ~(1<<PB3);
    _delay_us(100); 
}

void send4(uint8_t data){

    PORTD &= 0b11000011; 

    for(int i = 0; i < 4; i++){
        PORTD |= (((data >> i) & 0x1) << (3-i)) << 2; 
    }


    _delay_us(100); 

    // enable
    PORTB &= ~(1<<PB3);
    _delay_us(1); 
    PORTB |= (1<<PB3);
    _delay_us(1);
    // disable
    PORTB &= ~(1<<PB3);
    _delay_us(100); 
}

void begin(){
     // set pins 12, 11 to output
    DDRB |= (1<<DDB4) | (1<<DDB3);
    // set pins 5-2 to output
    DDRD |= (1<<DDD2) | (1<<DDD3) | (1<<DDD4) | (1<<DDD5);

    _delay_us(50000);

    // set 12, 11 to low
    PORTB &= ~((1<<PB4) | (1<<PB3)); 
    
    // try to set 4 bit mode x3
    send4Prep(0b0011); 
    _delay_us(4500);

    send4Prep(0b0011); 
    _delay_us(4500); 

    send4Prep(0b0011); 
    _delay_us(150); 

    send4Prep(0b0010); // set interface to be 4 bits long
    
    send4Prep(0b0010); // function set (display lines and char font)
    send4Prep(0b1000);  // 0000? NF**

    send4Prep(0b0000); // display off
    send4Prep(0b1100);  // 1000

    send4Prep(0b0000); // display clear
    send4Prep(0b0001); 
    _delay_us(2000); 

    send4Prep(0b0000); // entry mode set
    send4Prep(0b0110); // I/D S

    _delay_ms(100); 

}

void command(uint8_t rs, uint8_t instruction){
    // wipe previous
    PORTB &= ~(1<<PB4); 
    // write new
    PORTB |= ((rs && 1)<<PB4);

    send4(instruction >> 4);
    send4(instruction); 
    _delay_ms(10); 
}

void write(char * str, uint8_t len){
    for(int i = 0; i < len; i++){
        command(1, str[i]);
    }
}


// void write_c(char c){

//     switch (c) {
//         case 'H':
//             command(1, 0b01001000);
//             break;
//         case 'I':
//             command(1, 0b01001001);
//             break;
//         case 't':
//             command(1, 0b01000000); 
//     }
// }

int main(){
    _delay_ms(100); 

    // set pin 13 to output
    
    begin();

    write("Hello wo", 11);

    command(0, 0b10000000 | 0x40); //0x40

    write("rld!", 4); 

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