#pragma once
#ifndef CAN_COMMUNICATION_H
#define CAN_COMMUNICATION_H

#include "stm32f4xx_hal.h"

#define BtnU HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)

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

extern uint8_t CAN1_DATA_TX[8];
extern uint8_t CAN1_DATA_RX[8];
extern uint8_t CAN2_DATA_TX[8];
extern uint8_t CAN2_DATA_RX[8];

extern uint8_t MessageCounter;

extern void USART3_SendString(char* ch);
extern void PrintCANLog(uint16_t CANID, uint8_t *CAN_Frame);

extern void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);
extern void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);




//Functional
extern uint8_t calc_crc(uint8_t *data, uint8_t crc_len);
extern void CAN1_Transmit(void);
extern void CAN2_Transmit(void);
extern void UserButton_Callback(void);



#endif // CAN_COMMUNICATION_H