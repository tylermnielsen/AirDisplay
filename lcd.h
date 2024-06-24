/**
 * D12 (PB4) is RS (register select)
 *  (R/W pin) is ground (always writing?)
 * D11 (PB3) is ENABLE
 * D2 - D5 (PD2-PD5) are DB4-7
 * 
 */
#ifndef LCD_H
#define LCD_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>

void lcd_send4Prep(uint8_t data); 
void lcd_send4(uint8_t data);
void lcd_begin(); 
void lcd_command(uint8_t rs, uint8_t instruction);
void lcd_write(char * str);

#endif 