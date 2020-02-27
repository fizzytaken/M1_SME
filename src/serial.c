#include "serial.h"


void menu(){

    
    uint8_t Data[256];

    HAL_UART_Transmit(&huart1, (uint8_t *)Data, sprintf((char *)Data, "*********** MENU ********* \n"), 500);
    HAL_UART_Transmit(&huart1, (uint8_t *)Data, sprintf((char *)Data, "1) 50 Photos .. \n"), 500);
    HAL_UART_Transmit(&huart1, (uint8_t *)Data, sprintf((char *)Data, "2) 100 Photos .. \n"), 500);
    HAL_UART_Transmit(&huart1, (uint8_t *)Data, sprintf((char *)Data, "3) 150 Photos .. \n"), 500);
    HAL_UART_Transmit(&huart1, (uint8_t *)Data, sprintf((char *)Data, "4) 200 Photos .. \n"), 500);


}