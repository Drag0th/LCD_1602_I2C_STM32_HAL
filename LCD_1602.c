#include "LCD_1602.h"

void lcd_send_data(uint8_t data)
{
    HAL_I2C_Master_Transmit(&LCD1602_HI2C, LCD1602_ADRESS, (data & 0xf0) | BACKLIGHT | EN | RS, sizeof(data), 2);
    HAL_I2C_Master_Transmit(&LCD1602_HI2C, LCD1602_ADRESS, (data & 0xf0) | BACKLIGHT | RS, sizeof(data), 2);
    HAL_I2C_Master_Transmit(&LCD1602_HI2C, LCD1602_ADRESS, ((data << 4) & 0xf0) | BACKLIGHT | EN | RS, sizeof(data), 2);
    HAL_I2C_Master_Transmit(&LCD1602_HI2C, LCD1602_ADRESS, ((data << 4) & 0xf0) | BACKLIGHT | RS, sizeof(data), 2);
}

void lcd_send_command(uint8_t data)
{
    HAL_I2C_Master_Transmit(&LCD1602_HI2C, LCD1602_ADRESS, (data & 0xf0) | BACKLIGHT | EN, sizeof(data), 2);
    HAL_I2C_Master_Transmit(&LCD1602_HI2C, LCD1602_ADRESS, (data & 0xf0) | BACKLIGHT, sizeof(data), 2);
    HAL_I2C_Master_Transmit(&LCD1602_HI2C, LCD1602_ADRESS, ((data << 4) & 0xf0) | BACKLIGHT | EN, sizeof(data), 2);
    HAL_I2C_Master_Transmit(&LCD1602_HI2C, LCD1602_ADRESS, ((data << 4) & 0xf0) | BACKLIGHT, sizeof(data), 2);
}

void lcd_display_string(uint8_t row, uint8_t col, char *data)
{
    switch (row)
    {
    case 0:
        lcd_send_command((0x00 + col) | DDRAM_AD_SET);
        break;
    case 1:
        lcd_send_command((0x40 + col) | DDRAM_AD_SET);
        break;
    default:
        break;
    }
    while (*data)
        lcd_send_data(*data++);
}

void lcd_init(void)
{
    HAL_Delay(50);
    lcd_send_command(0x30);
    HAL_Delay(5);
    lcd_send_command(0x30);
    HAL_Delay(1);
    lcd_send_command(0x30);
    HAL_Delay(10);
    lcd_send_command(0x20); // 4-Bit mode
    HAL_Delay(10);
    lcd_send_command(0x28); // Function set: DL=0 , N = 1, F = 0
    HAL_Delay(1);
    lcd_send_command(0x08); // Display switch: D=0, C=0, B=0
    HAL_Delay(1);
    lcd_send_command(SCREEN_CLEAR); // Screen clear
    HAL_Delay(1);
    lcd_send_command(0x06); // Input set: I/D = 1, S = 0
    HAL_Delay(1);
    lcd_send_command(0x0C); // Display switch: D=1, C=0, B=0
}

void lcd_clear(void)
{
    lcd_send_command(SCREEN_CLEAR);
}
