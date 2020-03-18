#include "ihm.h"



int IHM_BEGIN(int IHM_USER_STATUS, int *nb_photos){
int sortie = 1;
int select = 0;
 uint8_t Data_out[256];
    uint8_t Data_int[1];

if(IHM_USER_STATUS == 1)
{
   

    HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "****************** IHM PC PROJET PHOTO 360 *************** \n"), 500);
    HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "*********** TAPER SUR 1 POUR CONTINUER  ********* \n"), 500);

while(Data_int[0] != '1'){
Data_int[0]= 0;
 HAL_UART_Receive(&huart1, (uint8_t *)Data_int, 1, 1000);
HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "****************** IHM PC PROJET PHOTO 360 *************** \n\n"), 500);
HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "*********** TAPER SUR 1 POUR CONTINUER  ********* \n"), 500);
}
    
    HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sizeof(Data_int)+1, 500);
    HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "PLUS LE NOMBRE DE PHOTOS EST IMPORTANT, PLUS LE RENDU SERA PRECIS \n"), 500);
    HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "1) 25 Photos .. \n"), 500);
    HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "2) 50 Photos .. \n"), 500);
    HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "3) 75 Photos .. \n"), 500);
    HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "4) 100 Photos .. \n"), 500);
Data_int[0]= 0;

 while((Data_int[0] != '1' )&&(Data_int[0] != '2' )&&(Data_int[0] != '3' )&&(Data_int[0] != '4' ) ){
Data_int[0]= 0;
 HAL_UART_Receive(&huart1, (uint8_t *)Data_int, 1, 1000);
 select = Data_int[0];

}
 HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "*********** OK  ********* \n"), 500);

switch(select){
case '1':
    HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "MODE 25 Photos ACTIF \n"), 500);
    *nb_photos = 25;
      break;

    case '2':
    HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "MODE 50 Photos ACTIF\n"), 500);
        *nb_photos = 50;

      break;

    case '3':
    HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "MODE 75 Photos ACTIF\n"), 500);
    *nb_photos = 75;

      break;

    case '4':
    HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "4) 100 Photos .. \n"), 500);
        *nb_photos = 100;

      break;

    default:
    HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "********************ERROR *******************\n"), 500);
    sortie = 0;
}
}
else
{
sortie = 0;
HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "******** IHM NON ACTIVE, VOIR ECRAN LCD *********\n"), 500);
}

    return sortie;
}

int IHM_MAIN(int IHM_USER_STATUS, int *nb_photos){


int sortie = 1;
int select = 0;
uint8_t Data_out[256];
uint8_t Data_int[1];
if(IHM_USER_STATUS == 1)
{

HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "\n******** IHM  *********\n"), 500);
    HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "PLUS LE NOMBRE DE PHOTOS EST IMPORTANT, PLUS LE RENDU SERA PRECIS \n"), 500);
    HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "1) 25 Photos .. \n"), 500);
    HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "2) 45 Photos .. \n"), 500);
    HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "3) 75 Photos .. \n"), 500);
    HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "4) 100 Photos .. \n"), 500);
        HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "Others) QUIT .. \n"), 500);


while((Data_int[0] != '1' )&&(Data_int[0] != '2' )&&(Data_int[0] != '3' )&&(Data_int[0] != '4' ) ){
Data_int[0]= 0;
 HAL_UART_Receive(&huart1, (uint8_t *)Data_int, 1, 1000);
 select = Data_int[0];

}

switch(select){
case '1':
    HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "MODE 50 Photos ACTIF \n"), 500);
    *nb_photos = 25;
      break;

    case '2':
    HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "MODE 100 Photos ACTIF\n"), 500);
        *nb_photos = 50;

      break;

    case '3':
    HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "MODE 150 Photos ACTIF\n"), 500);
    *nb_photos = 75;

      break;

    case '4':
    HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "4) 200 Photos .. \n"), 500);
        *nb_photos = 100;

      break;

    default:
    HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "********************QUIT *******************\n"), 500);
    sortie = 0;
    return 0;
}

}
else {

    sortie = 0;
}

return sortie;
}

