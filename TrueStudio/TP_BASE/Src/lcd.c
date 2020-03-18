#include "lcd.h"
#include "main.h"
#include "string.h"
#include "i2c.h"

//I2C_HandleTypeDef hi2c1;

/* Fonction qui permet d'initialiser l'écran LCD */
void lcd_init(I2C_HandleTypeDef* I2Cx, rgb_lcd* DataStruct)
{
	I2C_HandleTypeDef* Handle = I2Cx;
	DataStruct->_displayfunction |= LCD_2LINE | LCD_5x10DOTS; // MODE 2 LIGNES et 5x10points
	uint8_t data[2];
	data[0] = 0x80;
	data[1] = LCD_FUNCTIONSET | DataStruct->_displayfunction;

	HAL_I2C_IsDeviceReady(Handle,LCD_ADDRESS,5,100);
	HAL_Delay(50);

    HAL_I2C_Master_Transmit(Handle, LCD_ADDRESS, data,2,5000);
	HAL_Delay(50);

	HAL_I2C_Master_Transmit(Handle,LCD_ADDRESS,data,2,5000);
	HAL_Delay(5);

	HAL_I2C_Master_Transmit(Handle,LCD_ADDRESS,data,2,5000);

	// CONTROL -> Affichage ON, Curseur OFF & Blink OFF
	DataStruct->_displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    // On applique le masque de displaycontrol
	data[1] = LCD_DISPLAYCONTROL | DataStruct->_displaycontrol;
	// On envoie au lcd les registres de configuration a modifier 
	HAL_I2C_Master_Transmit(Handle,LCD_ADDRESS, data,2,1000);

	data[1] = LCD_CLEARDISPLAY; // On efface ce qui est affiché sur l'écran
	HAL_I2C_Master_Transmit(Handle, (uint16_t)LCD_ADDRESS, (uint8_t *)data,2,1000);
	HAL_Delay(2);

	// MODE
	DataStruct->_displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	data[1] = LCD_ENTRYMODESET | DataStruct->_displaymode;
	HAL_I2C_Master_Transmit(Handle, (uint16_t)LCD_ADDRESS, (uint8_t *)data,2,1000);

	// BACKLIGHT INIT
	uint8_t data_backlight[2];
	data_backlight[0] = REG_MODE1;
	data_backlight[1] = 0;
	HAL_I2C_Master_Transmit(Handle, (uint16_t)RGB_ADDRESS, (uint8_t *)data_backlight,2,1000);

	data_backlight[0] = REG_OUTPUT;
	data_backlight[1] = 0xFF;
	HAL_I2C_Master_Transmit(Handle, (uint16_t)RGB_ADDRESS, (uint8_t *)data_backlight,2,1000);

	data_backlight[0] = REG_MODE2;
	data_backlight[1] = 0x20;
	HAL_I2C_Master_Transmit(Handle, (uint16_t)RGB_ADDRESS, (uint8_t *)data_backlight,2,1000);

	// RGB WHITE
	// On utilise l'adresse RGB_ADDRESS pour configurer le rétroéclairage
	uint8_t data_rgb[2];
	data_rgb[0] = REG_RED;
	data_rgb[1] = 255;
	HAL_I2C_Master_Transmit(Handle, (uint16_t)RGB_ADDRESS, (uint8_t *)data_rgb,2,1000);

	data_rgb[0] = REG_GREEN;
	data_rgb[1] = 255;
	HAL_I2C_Master_Transmit(Handle, (uint16_t)RGB_ADDRESS, (uint8_t *)data_rgb,2,1000);

	data_rgb[0] = REG_BLUE;
	data_rgb[1] = 255;
	HAL_I2C_Master_Transmit(Handle, (uint16_t)RGB_ADDRESS, (uint8_t *)data_rgb,2,1000);

}
/* Fonction qui permet d'afficher une valeur sur l'écran LCD */
void lcd_write(I2C_HandleTypeDef* I2Cx, uint8_t value)
{
	I2C_HandleTypeDef* Handle = I2Cx;
    unsigned char data[2] = {0x40, value};
    HAL_I2C_Master_Transmit(Handle,LCD_ADDRESS, data,2,1000);
}
/* Fonction qui permet d'afficher une chaîne de caractères sur l'écran LCD */
void lcd_print(char *str)
{
	//I2C_HandleTypeDef* Handle = I2Cx;
    char data[2];
    data[0] = 0x40;
    int i=0;
    while(str[i] != '\0')
    {
            data[1] = str[i];
            HAL_I2C_Master_Transmit(&hi2c1,LCD_ADDRESS,(uint8_t *) data, 2,1000);
            i++;
   }
}
/* Fonction qui permet de positionner le curseur */
void lcd_locate(I2C_HandleTypeDef* I2Cx,char col, char row)
{
	I2C_HandleTypeDef* Handle = I2Cx;
    if(row == 0)
    {
        col = col | 0x80;
    }
    else
    {
        col = col | 0xc0;
    }

    char data[2];
    data[0] = 0x80;
    data[1] = col;
    HAL_I2C_Master_Transmit(Handle,LCD_ADDRESS,(uint8_t *) data, 2,1000);
}

void lcd_clear()
{
	uint8_t data[2];
	data[0] = 0x80;
	data[1] = LCD_CLEARDISPLAY; // On efface ce qui est affiché sur l'écran
    HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)LCD_ADDRESS, (uint8_t *)data,2,1000);
	HAL_Delay(2);
}
