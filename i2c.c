#include "i2c.h"

/**
 * SCL - A5 - PC5
 * SDA - A4 - PC4
 */

#define START           0x08
#define MT_SLA_ACK      0x18
#define MT_DATA_ACK     0x28
#define I2C_WRITE_BIT   0x00
#define I2C_READ_BIT    0x01
#define READ_SLA_ACK    0x40


int8_t i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t length, void *intf_ptr){

    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWSTO)|(1<<TWEN); 

    while(!(TWCR & (1<<TWINT))); 

    if((TWSR & 0xF8) != START) return 1;

    TWDR = (reg_addr << 1) | I2C_READ_BIT; 
    TWCR = (1<<TWINT)|(1<<TWEN); 

    while(!(TWCR & (1<<TWINT))); 

    if(!(TWSR & 0xF8) != READ_SLA_ACK) return 1; 



    return 0; 
}

int8_t i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t length, void *intf_ptr){
    
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);

    while(!(TWCR & (1<<TWINT)));

    if((TWSR & 0xF8) != START) return 1;

    TWDR = (reg_addr << 1) | I2C_READ_BIT;  // SLA_W
    TWCR = (1<<TWINT)|(1<<TWEN);

    while(!(TWCR & (1<<TWINT)));

    if((TWSR & 0xF8) != MT_SLA_ACK) return 1; 

    TWDR = *reg_data;
    TWCR = (1<<TWINT)|(1<<TWEN); 

    while(!(TWCR & (1<<TWINT)));

    if((TWSR & 0xF8) != MT_DATA_ACK) return 1; 

    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); 

    return 0; 
}

