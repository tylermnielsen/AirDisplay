#ifndef I2C_H
#define I2C_H

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>

int8_t i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t length, void *intf_ptr);
int8_t i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t length, void *intf_ptr);

#endif