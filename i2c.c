#include "i2c.h"
#include <util/twi.h>

/**
 * SCL - A5 - PC5
 * SDA - A4 - PC4
 */
// https://embedds.com/programming-avr-I2C-interface/
#define TWI_FREQ 100000L

void i2c_init(void){

    DDRC &= ~((1<<5)|(1<<4)); 
    PORTC |= (1<<5)|(1<<4); 

    TWSR &= ~(_BV(TWPS0)|_BV(TWPS1));
    TWBR = ((F_CPU / TWI_FREQ) - 16) / 2 + 1; 

    TWCR = _BV(TWEN)|_BV(TWIE)|_BV(TWEA); 
}

int8_t i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t length, void *intf_ptr){
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); // start
    while(!(TWCR & (1<<TWINT))); // wait for ack

    if((TWSR & 0xF8) != TW_START) return 1; // check if it worked

    TWDR = (reg_addr << 1) | TW_READ; // set address
    TWCR = (1<<TWINT)|(1<<TWEN); // start write
    while(!(TWCR & (1<<TWINT))); // what for write to end 

    if((TWSR & 0xF8) != TW_MR_SLA_ACK) return 1; // check if it worked

    for(uint32_t i = 0; i < length; i++){
        if(i < length-1) {
            TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA); // read with ack 
        }
        else {
            TWCR = (1<<TWINT)|(1<<TWEN); // read with NACK 
        }
        while(!(TWCR & (1<<TWINT))); 

        if((TWSR & 0xF8) != TW_MR_DATA_ACK) return 1; // check if it worked 

        reg_data[i] = TWDR;  

    }


    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);  // send stop 

    return 0; 
    
}

int8_t i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t length, void *intf_ptr){

    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); 

    while(!(TWCR & (1<<TWINT))); 

    if((TWSR & 0xF8) != TW_START) return 1; 

    TWDR = (reg_addr << 1) | TW_WRITE; 
    TWCR = (1<<TWINT)|(1<<TWEN); 

    while(!(TWCR & (1<<TWINT))); 

    if((TWSR & 0xF8) != TW_MT_SLA_ACK) return 1; 

    TWDR = *reg_data; 
    TWCR = (1<<TWINT)|(1<<TWEN); 

    while(!(TWCR & (1<<TWINT)));

    if((TWSR & 0xF8) != TW_MT_DATA_ACK) return 0; 
    
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); 

    return 0; 
}

