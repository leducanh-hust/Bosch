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
#include "stm32f4xx_hal.h"

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

/* USER CODE BEGIN Private defines */
extern uint8_t uart3_receive;
extern UART_HandleTypeDef huart3;

extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;
extern CAN_TxHeaderTypeDef CAN1_pHeader;
extern CAN_RxHeaderTypeDef CAN1_pHeaderRx;
extern CAN_FilterTypeDef CAN1_sFilterConfig;
extern CAN_TxHeaderTypeDef CAN2_pHeader;
extern CAN_RxHeaderTypeDef CAN2_pHeaderRx;
extern CAN_FilterTypeDef CAN2_sFilterConfig;
extern uint32_t CAN1_pTxMailbox;
extern uint32_t CAN2_pTxMailbox;

extern uint16_t NumBytesReq;
extern uint8_t REQ_BUFFER[4096];
extern uint8_t  REQ_1BYTE_DATA;

extern uint8_t CAN1_DATA_TX[8];
extern uint8_t CAN1_DATA_RX[8];
extern uint8_t CAN2_DATA_TX[8];
extern uint8_t CAN2_DATA_RX[8];

extern unsigned int TimeStamp;

extern void USART3_SendString(char* ch);
extern void PrintCANLog(uint16_t CANID, uint8_t *CAN_Frame);

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
