/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
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
#define USER_BUTTON_Pin GPIO_PIN_13
#define USER_BUTTON_GPIO_Port GPIOC
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define LED6_Pin GPIO_PIN_10
#define LED6_GPIO_Port GPIOB
#define LED7_Pin GPIO_PIN_11
#define LED7_GPIO_Port GPIOB
#define LED8_Pin GPIO_PIN_12
#define LED8_GPIO_Port GPIOB
#define LED9_Pin GPIO_PIN_13
#define LED9_GPIO_Port GPIOB
#define LED10_Pin GPIO_PIN_14
#define LED10_GPIO_Port GPIOB
#define BUTTON_MODE_Pin GPIO_PIN_7
#define BUTTON_MODE_GPIO_Port GPIOC
#define BUTTON_BACKWARD_Pin GPIO_PIN_8
#define BUTTON_BACKWARD_GPIO_Port GPIOC
#define BUTTON_FORWARD_Pin GPIO_PIN_9
#define BUTTON_FORWARD_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_5
#define LED1_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_6
#define LED2_GPIO_Port GPIOB
#define LED3_Pin GPIO_PIN_7
#define LED3_GPIO_Port GPIOB
#define LED4_Pin GPIO_PIN_8
#define LED4_GPIO_Port GPIOB
#define LED5_Pin GPIO_PIN_9
#define LED5_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
