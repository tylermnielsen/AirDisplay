#include "lcd.h"

void lcd_send4Prep(uint8_t data){
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

void lcd_send4(uint8_t data){

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

void lcd_begin(){
     // set pins 12, 11 to output
    DDRB |= (1<<DDB4) | (1<<DDB3);
    // set pins 5-2 to output
    DDRD |= (1<<DDD2) | (1<<DDD3) | (1<<DDD4) | (1<<DDD5);

    _delay_us(50000);

    // set 12, 11 to low
    PORTB &= ~((1<<PB4) | (1<<PB3)); 
    
    // try to set 4 bit mode x3
    lcd_send4Prep(0b0011); 
    _delay_us(4500);

    lcd_send4Prep(0b0011); 
    _delay_us(4500); 

    lcd_send4Prep(0b0011); 
    _delay_us(150); 

    lcd_send4Prep(0b0010); // set interface to be 4 bits long
    
    lcd_send4Prep(0b0010); // function set (display lines and char font)
    lcd_send4Prep(0b1000);  // 0000? NF**

    lcd_send4Prep(0b0000); // display off
    lcd_send4Prep(0b1100);  // 1000

    lcd_send4Prep(0b0000); // display clear
    lcd_send4Prep(0b0001); 
    _delay_us(2000); 

    lcd_send4Prep(0b0000); // entry mode set
    lcd_send4Prep(0b0110); // I/D S

    _delay_ms(100); 

}

void lcd_command(uint8_t rs, uint8_t instruction){
    // wipe previous
    PORTB &= ~(1<<PB4); 
    // write new
    PORTB |= ((rs && 1)<<PB4);

    lcd_send4(instruction >> 4);
    lcd_send4(instruction); 
    _delay_ms(10); 
}

void lcd_write(char * str){
    for(int i = 0; str[i] != '\0'; i++){
        if(i == 8){
            lcd_command(0, 0b10000000 | 0x40); 
        }
        lcd_command(1, str[i]);
    }
}