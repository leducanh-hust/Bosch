#include "UDS.h"

void CAN1_SendRequest()
{
    // Get Data from UART, prepare CAN Frame
    if (REQ_BUFFER[0] != 0)
    {
        HAL_Delay(50);
        USART3_SendString((uint8_t *)"\n");
        for (int i = 0; i < 8; ++i)
        {
            CAN1_DATA_TX[i] = REQ_BUFFER[i];
            FormatCANFrame(CAN1_DATA_TX);
        }
    }

    HAL_CAN_AddTxMessage(&hcan1, &CAN1_pHeader, CAN1_DATA_TX, &CAN1_pTxMailbox);
    PrintCANLog(0x712, CAN1_DATA_TX);
    memset(REQ_BUFFER, 0x00, 4096);
    NumBytesReq = 0;
}

void SID_22_Practice()
{
    bool eligibleFormat = 0;
    eligibleFormat = checkFormat(CAN1_DATA_TX);
    if (eligibleFormat)
    {
        if (getDID(CAN1_DATA_TX) == 0x0123)
        {
            CAN2_DATA_TX[0] = 0x05;
            CAN2_DATA_TX[1] = 0x22 + 0x40;
            CAN2_DATA_TX[2] = 0x01;
            CAN2_DATA_TX[3] = 0x23;
            CAN2_DATA_TX[4] = 0x00;
            CAN2_DATA_TX[5] = 0x78;
            //FormatCANFrame(CAN2_DATA_TX);
            HAL_CAN_AddTxMessage(&hcan2, &CAN2_pHeader, CAN2_DATA_TX, &CAN2_pTxMailbox);
            PrintCANLog(0x7A2, CAN2_DATA_TX);
        }
    }
}

uint8_t getSID(uint8_t data[])
{
    return data[1];
}

uint16_t getDID(uint8_t data[])
{
    uint16_t tmp = 0x0000;
    tmp = data[2];
    tmp <<= 8;
    tmp += data[3];
    return tmp;
}

void FormatCANFrame(uint8_t data[])
{
    uint8_t loopIndx = 0;
    for (loopIndx = data[0]; loopIndx < 8; loopIndx++)
    {
        if (data[loopIndx] == 0x00)
        {
            data[loopIndx] = 0x55;
        }
    }
}

bool checkFormat(uint8_t data[])
{
    switch (data[1])
    {
    case 0x22:
        if (data[0] == 0x03)
            return true;
        return false;
        break;
    case 0x27:
        if (data[0] == 0x02 || data[0] == 0x06)
            return true;
        return false;
        break;
    case 0x2E:
        if (data[0] == 0x05)
            return true;
        return false;
    default:
        USART3_SendString((uint8_t *)"Invalid Service ID\n");
        return false;
        break;
    }
}
