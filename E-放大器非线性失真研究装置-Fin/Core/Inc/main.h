/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdint.h"
#include "arm_math.h"
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
#define SDA_Pin GPIO_PIN_3
#define SDA_GPIO_Port GPIOF
#define RES_Pin GPIO_PIN_5
#define RES_GPIO_Port GPIOF
#define DC_Pin GPIO_PIN_7
#define DC_GPIO_Port GPIOF
#define CS_Pin GPIO_PIN_9
#define CS_GPIO_Port GPIOF
#define KEYEXTI1_Pin GPIO_PIN_0
#define KEYEXTI1_GPIO_Port GPIOC
#define KEYEXTI1_EXTI_IRQn EXTI0_IRQn
#define KEYEXTI2_Pin GPIO_PIN_2
#define KEYEXTI2_GPIO_Port GPIOC
#define KEYEXTI2_EXTI_IRQn EXTI2_IRQn
#define CD4066D_Pin GPIO_PIN_2
#define CD4066D_GPIO_Port GPIOB
#define CD4066C_Pin GPIO_PIN_12
#define CD4066C_GPIO_Port GPIOF
#define CD4066A_Pin GPIO_PIN_15
#define CD4066A_GPIO_Port GPIOA
#define CD4066B_Pin GPIO_PIN_10
#define CD4066B_GPIO_Port GPIOC
#define BEEp_Pin GPIO_PIN_12
#define BEEp_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_7
#define LED1_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_9
#define LED2_GPIO_Port GPIOB
#define SCK_Pin GPIO_PIN_1
#define SCK_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
