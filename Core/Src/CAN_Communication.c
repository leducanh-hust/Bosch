#include "CAN_Communication.h"

uint8_t MessageCounter = 0;

void CAN_Transmit(CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *pHeader, uint32_t *pTxMailbox, uint8_t *data_rx, uint8_t *data_tx, uint16_t id, uint8_t x)
{
    pHeader->StdId = id;
    pHeader->DLC = 8;
    pHeader->IDE = CAN_ID_STD;
    pHeader->RTR = CAN_RTR_DATA;
    if (data_rx[7] == calc_crc(data_rx, 7))
    {
        data_tx[0] = 0x0A;
        data_tx[1] = 0x02;
        if (data_rx == CAN1_DATA_RX)
        {
            data_tx[2] = 0x0C;
        }
    }
    else
    {
        data_tx[0] = 0x00;
        data_tx[1] = 0x00;
    }
    data_tx[6] = MessageCounter;
    data_tx[7] = calc_crc(data_tx, 7) & x; // make crc wrong or not 
    char buffer[8];
    sprintf(buffer, "CAN%uTX\n", (hcan == &hcan1) ? 1 : 2);
    USART3_SendString((unsigned char *)buffer);
    PrintCANLog(id, data_tx);
    HAL_CAN_AddTxMessage(hcan, pHeader, data_tx, pTxMailbox);
    MessageCounter = (MessageCounter + 1) & 0xF;
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    if (hcan == &hcan1)
    {
        HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &CAN1_pHeaderRx, CAN1_DATA_RX);

        char buffer3[9] = "CAN1 RX\n";
        USART3_SendString((unsigned char *)buffer3);
        PrintCANLog(0x0A2, CAN1_DATA_RX);
    }
    else if (hcan == &hcan2)
    {
        HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &CAN2_pHeaderRx, CAN2_DATA_RX);

        char buffer4[9] = "CAN2 RX\n";
        USART3_SendString((unsigned char *)buffer4);
        PrintCANLog(0x012, CAN2_DATA_RX);
    }
}

void UserButton_Callback(void)
{
    USART3_SendString((uint8_t *)"IG OFF\n");
    while (!BtnU)
        ;
    while (BtnU)
    {
        CAN_Transmit(&hcan2, &CAN2_pHeader, &CAN2_pTxMailbox, CAN2_DATA_RX, CAN2_DATA_TX, 0xA2, 0xFF);
        HAL_Delay(2000);
        CAN_Transmit(&hcan1, &CAN1_pHeader, &CAN1_pTxMailbox, CAN1_DATA_RX, CAN1_DATA_TX, 0x12, 0);
        HAL_Delay(1990);
    }
    // MX_CAN1_Setup();
    // MX_CAN2_Setup();
    USART3_SendString((uint8_t *)"-> IG ON\n");
    while (!BtnU)
        ;
    HAL_Delay(20);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_1)
    {
        HAL_Delay(20);
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
            UserButton_Callback();
    }
}