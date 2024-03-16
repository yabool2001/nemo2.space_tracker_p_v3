/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "my_global.h"
#include "my_astronode.h"
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
#define DBG_TX_Pin GPIO_PIN_2
#define DBG_TX_GPIO_Port GPIOA
#define DBG_RX_Pin GPIO_PIN_3
#define DBG_RX_GPIO_Port GPIOA
#define ASTRO_WKUP_Pin GPIO_PIN_0
#define ASTRO_WKUP_GPIO_Port GPIOB
#define ASTRO_RST_Pin GPIO_PIN_1
#define ASTRO_RST_GPIO_Port GPIOB
#define ASTRO_EVT_Pin GPIO_PIN_2
#define ASTRO_EVT_GPIO_Port GPIOB
#define RF_SW_CTL1_Pin GPIO_PIN_10
#define RF_SW_CTL1_GPIO_Port GPIOB
#define RF_SW_CTL2_Pin GPIO_PIN_11
#define RF_SW_CTL2_GPIO_Port GPIOB
#define GNSS_RST_Pin GPIO_PIN_13
#define GNSS_RST_GPIO_Port GPIOB
#define GNSS_PWR_SW_Pin GPIO_PIN_15
#define GNSS_PWR_SW_GPIO_Port GPIOB
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define GNSS_TX_Pin GPIO_PIN_3
#define GNSS_TX_GPIO_Port GPIOB
#define GNSS_RX_Pin GPIO_PIN_4
#define GNSS_RX_GPIO_Port GPIOB
#define ASTRO_TX_Pin GPIO_PIN_8
#define ASTRO_TX_GPIO_Port GPIOB
#define ASTRO_RX_Pin GPIO_PIN_9
#define ASTRO_RX_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define HUART_DBG	huart2
#define HUART_ASTRO	huart3
#define HUART_GNSS	huart5
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
