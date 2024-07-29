/*
 * i2c-lcd.h
 *
 *  Created on: Jun 25, 2024
 *      Author: ESG
 */
//#ifndef I2C_LCD_H
//#define I2C_LCD_H


#ifndef INC_I2C_LCD_H_
#define INC_I2C_LCD_H_


#include "stm32g4xx_hal.h"

// LCD address
#define LCD_ADDR 0x27 << 1 // Adjust if needed
#define LCD_COLS 16
#define LCD_ROWS 2

void lcd_init(void);
void lcd_send_string(char *str);
void lcd_put_cursor(int row, int col);
void lcd_clear(void);



#endif /* INC_I2C_LCD_H_ */
