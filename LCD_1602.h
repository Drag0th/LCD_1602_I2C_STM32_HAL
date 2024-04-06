
#include "stm32f1xx_hal.h"
#include "i2c.h"

// Change values below suitable for your setup
// ##########################
#define LCD1602_HI2C hi2c1
#define LCD1602_ADRESS 0x4E
// ##########################

#define RS 0x01
#define EN 0x04
#define BACKLIGHT 0x08
#define DDRAM_AD_SET 0x80
#define SCREEN_CLEAR 0x01

void lcd_send_data(uint8_t data);
void lcd_send_command(uint8_t data);
void lcd_display_string(uint8_t row, uint8_t col, char *data);
void lcd_clear(void);
void lcd_init(void);
