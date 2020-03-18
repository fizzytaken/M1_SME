
#include "main.h"
#include "motor.h"


void tourne (int angle){
    
    int state = 0;
    int i;
    angle = angle * 593 / 360; //593 => 360 degrés
    for (i=0; i<7*angle; i++){
        HAL_Delay(1);
        switch (state){

            case 0: 
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
                state ++;
                break;
            
            case 1: 
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
                state ++;
                break;
            
            case 2: 
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
                state ++;
                break;
            
            case 3: 
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
                state ++ ;
                break;
            
            case 4: 
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
                state ++;
                break;
            
            case 5: 
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
                state ++;
                break;
            
            case 6: 
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
                state ++;
                break;

            case 7: 
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
                state = 0;
                break;

            default:
                state = 0; 
                break;
            }
    }
    return 0;
}    