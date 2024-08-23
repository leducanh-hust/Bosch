#pragma once
#ifndef UDS_H
#define UDS_H

#include "stm32f4xx_hal.h"
#include <stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define BtnU HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)

extern UART_HandleTypeDef huart3;
extern uint8_t uart3_receive;

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

extern uint16_t NumBytesReq;
extern uint8_t REQ_BUFFER[4096];
extern uint8_t  REQ_1BYTE_DATA;

//Functional
extern uint8_t getSID(uint8_t data[]);
extern uint16_t getDID(uint8_t data[]);
extern void FormatCANFrame(uint8_t data[]);

extern bool checkFormat(uint8_t data[]);
//extern void checkDID();


extern void CAN1_SendRequest();
extern void SID_22_Practice();
// extern void SID_27_Practice();
// extern void SID_2E_Practice();
#endif // UDS_H