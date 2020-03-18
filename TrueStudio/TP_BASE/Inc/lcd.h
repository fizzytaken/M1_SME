#ifndef LCD_H_
#define LCD_H_

#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_i2c.h"

// Device I2C Arress
#define LCD_ADDRESS     0x7c
#define RGB_ADDRESS     0xc4

// color define
#define WHITE           0
#define RED             1
#define GREEN           2
#define BLUE            3

#define REG_RED         0x04        
#define REG_GREEN       0x03        
#define REG_BLUE        0x02        

#define REG_MODE1       0x00
#define REG_MODE2       0x01
#define REG_OUTPUT      0x08

// Commandes
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

typedef struct
{
  uint8_t _displayfunction;
  uint8_t _displaycontrol;
  uint8_t _displaymode;
} rgb_lcd;

// Méthodes
void lcd_init(I2C_HandleTypeDef* I2Cx, rgb_lcd* DataStruct);
void lcd_write(I2C_HandleTypeDef* I2Cx, uint8_t value);
void lcd_print(char *str);
void lcd_locate(I2C_HandleTypeDef* I2Cx,char col, char row);
void lcd_clear(void);

#endif /* LCD_H_ */
