#include "gpio.h"
#include "timer.h"
#include "main.h"

void photo_canon(int nb){
// https://publiclab.org/notes/cfastie/02-28-2016/auto-eos-m

    for(int i=0; i<nb; i++) {

        for(int i=0; i<16; i++) { 
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
            delay_us(40); // 40 => 15 us
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
            delay_us(40);
        } 
        HAL_Delay(7); // en ms

        for(int i=0; i<16; i++) { 
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
            delay_us(40);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
            delay_us(40);
        }
        HAL_Delay(200);// Time entre les salves (quand multiples photos)
    }       
}

void photo_nikon(int nb){
//https://www.christidis.info/index.php/personal-projects/arduino-nikon-infrared-command-code

    for(int i=0; i<nb; i++) {

        for (int i = 0; i < 16; i++) {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
            delay_us(5); // 5 -> 7us 
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
            delay_us(5);
        }
        HAL_Delay(27);

        for (int i = 0; i < 16; i++) {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
            delay_us(5);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
            delay_us(5);
        }
        HAL_Delay(1);

        for (int i = 0; i < 16; i++) {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
            delay_us(5);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
            delay_us(5);
        }
        HAL_Delay(3);

        for (int i = 0; i < 16; i++) {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
            delay_us(5);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
            delay_us(5);
        }
        
        HAL_Delay(200); // Time entre les salves (quand multiples photos)
    }
}

