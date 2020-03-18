/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "ihm.h"
#include "i2c.h"
#include "gpio.h"
#include "timer.h"
#include "photo.h"
#include "motor.h"
#include "lcd.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define DEBUG 0
#define IHM 1  // activation ou non de l'IHM au démarrage 
int IHM_USER_STATUS  = 1;  // activation ou non de l'IHM au démarrage 
int NB_Photo =  50;


uint8_t Data_out[256];

/* USER CODE END Includes */
/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  
  MX_TIM3_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "******  INITIALISATION TIM3  ******  \n"), 500);
  HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "******  INITIALISATION I2C  ******   \n"), 500);
  HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "******  INITIALISATION GPIO  ******  \n"), 500);

  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim3);
  __HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
  HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(USART1_IRQn);

  init_screen();
  lcd_clear();
  lcd_locate(&hi2c1,0,0);
  HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "******  INITIALISATION LCD  ******  \n"), 500);

  lcd_print("...Photo 360... ");
  HAL_Delay(5000);

  //print_avancement(1);

  int photo;  //Initialisation du nombre de photos prises
  int angle_calcule;

   IHM_BEGIN(IHM_USER_STATUS, &NB_Photo);

 
  angle_calcule = (360 / NB_Photo); //Angle de déplacement entre chaque photo, calculé a partir du nombre de photos à prendre
  while(DEBUG == 1)
  {
      HAL_UART_Transmit(&huart1, (uint8_t *)Data_out, sprintf((char *)Data_out, "******  MODE DEBUG  ****** -->>  37,5 pour 100 \n"), 500);

    tourne(1);
  }

  for(photo=0; photo <= NB_Photo; photo++)
  {

    lcd_ihm(photo,NB_Photo);
    photo_canon(2);
    photo_nikon(2);
    
    tourne(angle_calcule);

    HAL_Delay(10000);
  } 

  lcd_clear();
  lcd_locate(&hi2c1,4,0);
	lcd_print("! DONE !");

  
  
  /* USER CODE END 2 */


  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
      IHM_MAIN(IHM_USER_STATUS, &NB_Photo);

    
    angle_calcule = (360 / NB_Photo); //Angle de déplacement entre chaque photo, calculé a partir du nombre de photos à prendre
    while(DEBUG == 1)
    {
      tourne(1);
    }

   for(photo=0; photo <= NB_Photo; photo++)
   {

    lcd_ihm(photo,NB_Photo);
    photo_canon(2);
    photo_nikon(2);
    
    tourne(angle_calcule);

    HAL_Delay(10000);
  } 

  lcd_clear();
  lcd_locate(&hi2c1,4,0);
	lcd_print("! DONE !");


  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
