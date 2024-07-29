/*
 * i2c-lcd.c
 *
 *  Created on: Jun 25, 2024
 *      Author: ESG
 */
#include "i2c-lcd.h"
#include "main.h"

extern I2C_HandleTypeDef hi2c2;

void lcd_send_cmd(char cmd) {
    char data_u, data_l;
    uint8_t data_t[4];
    data_u = (cmd & 0xf0);
    data_l = ((cmd << 4) & 0xf0);
    data_t[0] = data_u | 0x0C; // En=1, Rs=0
    data_t[1] = data_u | 0x08; // En=0, Rs=0
    data_t[2] = data_l | 0x0C; // En=1, Rs=0
    data_t[3] = data_l | 0x08; // En=0, Rs=0
    HAL_I2C_Master_Transmit(&hi2c2, LCD_ADDR, (uint8_t *)data_t, 4, 100);
}

void lcd_send_data(char data) {
    char data_u, data_l;
    uint8_t data_t[4];
    data_u = (data & 0xf0);
    data_l = ((data << 4) & 0xf0);
    data_t[0] = data_u | 0x0D; // En=1, Rs=1
    data_t[1] = data_u | 0x09; // En=0, Rs=1
    data_t[2] = data_l | 0x0D; // En=1, Rs=1
    data_t[3] = data_l | 0x09; // En=0, Rs=1
    HAL_I2C_Master_Transmit(&hi2c2, LCD_ADDR, (uint8_t *)data_t, 4, 100);
}

void lcd_clear(void) {
    lcd_send_cmd(0x80);
    for (int i = 0; i < 70; i++) {
        lcd_send_data(' ');
    }
}

void lcd_put_cursor(int row, int col) {
    uint8_t pos = (row == 0) ? (0x80 + col) : (0xC0 + col);
    lcd_send_cmd(pos);
}

void lcd_send_string(char *str) {
    while (*str) lcd_send_data(*str++);
}

void lcd_init(void) {
    HAL_Delay(50);
    lcd_send_cmd(0x30);
    HAL_Delay(5);
    lcd_send_cmd(0x30);
    HAL_Delay(1);
    lcd_send_cmd(0x30);
    HAL_Delay(10);
    lcd_send_cmd(0x20);
    HAL_Delay(10);

    lcd_send_cmd(0x28);
    HAL_Delay(1);
    lcd_send_cmd(0x08);
    HAL_Delay(1);
    lcd_send_cmd(0x01);
    HAL_Delay(1);
    HAL_Delay(1);
    lcd_send_cmd(0x06);
    HAL_Delay(1);
    lcd_send_cmd(0x0C);
}


