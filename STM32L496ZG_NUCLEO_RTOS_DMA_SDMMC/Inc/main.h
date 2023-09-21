/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BUTTON_1_Pin GPIO_PIN_13
#define BUTTON_1_GPIO_Port GPIOC
#define BUTTON_1_EXTI_IRQn EXTI15_10_IRQn
#define SDMMC1_DETECT_Pin GPIO_PIN_3
#define SDMMC1_DETECT_GPIO_Port GPIOF
#define LED_NUCLEO_RED_Pin GPIO_PIN_14
#define LED_NUCLEO_RED_GPIO_Port GPIOB
#define USART3_TX_Pin GPIO_PIN_8
#define USART3_TX_GPIO_Port GPIOD
#define USART3_RX_Pin GPIO_PIN_9
#define USART3_RX_GPIO_Port GPIOD
#define TERMINAL_TX_Pin GPIO_PIN_7
#define TERMINAL_TX_GPIO_Port GPIOG
#define TERMINAL_RX_Pin GPIO_PIN_8
#define TERMINAL_RX_GPIO_Port GPIOG
#define LED_NUCLEO_GREEN_Pin GPIO_PIN_7
#define LED_NUCLEO_GREEN_GPIO_Port GPIOC
#define USB_CONNECT_Pin GPIO_PIN_9
#define USB_CONNECT_GPIO_Port GPIOA
#define USB_CONNECT_EXTI_IRQn EXTI9_5_IRQn
#define LED_NUCLEO_BLUE_Pin GPIO_PIN_7
#define LED_NUCLEO_BLUE_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
