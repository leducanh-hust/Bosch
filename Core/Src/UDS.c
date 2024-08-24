#include "UDS.h"

#define NRC 0x7F
#define INVALID_LENGTH 0x13
#define INVALID_DID 0x31

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

void CAN1_SendRequest()
{
    if (HAL_CAN_AddTxMessage(&hcan1, &CAN1_pHeader, CAN1_DATA_TX, &CAN1_pTxMailbox) != HAL_OK)
    {
        Error_Handler();
    }
    PrintCANLog(CAN1_pHeader.StdId, CAN1_DATA_TX);
}

void CAN2_SendResponse()
{
    if (HAL_CAN_AddTxMessage(&hcan2, &CAN2_pHeader, CAN2_DATA_TX, &CAN2_pTxMailbox) != HAL_OK)
    {
        Error_Handler();
    }
    PrintCANLog(CAN2_pHeader.StdId, CAN2_DATA_TX);
}


void FormatCANFrame(uint8_t data[])
{
    for (uint8_t loopIndx = data[0] + 1; loopIndx < 8; loopIndx++)
    {
        if (data[loopIndx] == 0x00)
        {
            data[loopIndx] = 0x55;
        }
    }
}


void calculate_key_from_seed(uint8_t *input, uint8_t *output)
{
    output[0] = input[0] ^ input[1];
    output[1] = input[1] + input[2];
    output[2] = input[2] ^ input[3];
    output[3] = input[3] + input[0];
}

bool cmp_key(uint8_t *key1, uint8_t *key2, uint8_t len)
{
    for(uint8_t i = 0; i < len; i++)
    {
        if (key1[i] != key2[i])
        {
            return false;
        }
    }
    return true;
}


bool checkFormat(uint8_t data[])
{
    //data[1] is the Service ID
    //data[0] is the length of the data
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

bool checkDID(uint8_t data[])
{
    if (data[2] == 0x01 && data[2] == 0x23)
        return true;
    return false;
}



void UART_ReadString(uint8_t *buf, uint8_t *data, uint8_t len)
{
    if(buf[0] != 0)
    {
        data[0] = len;
        for(uint8_t i = 1; i <= len; i++)
        {
            data[i] = buf[i - 1];
        }
        for(uint8_t i = len + 1; i < 8; i++)
        {
            data[i] = 0x00;
        }
        FormatCANFrame(data);
        return;
    }
    USART3_SendString((uint8_t *)"Invalid Input\n");
}

void SID22_Practice(uint8_t *data_tx, uint8_t *data_rx)
{
    if(checkFormat(data_rx)) //check length returned true
    {
        if(checkDID(data_rx)) //check DID returned true, CAN2 Receive Correct message
        {
        //Case 1 in excel, $22 normal flow
            data_tx[0] = 0x05;
            data_tx[1] = data_rx[1] + 0x40;
            data_tx[2] = data_rx[2];
            data_tx[3] = data_rx[3];
            data_tx[4] = 0x00;
            data_tx[5] = 0x78;
            data_tx[6] = 0x00;
            data_tx[7] = 0x00;
            FormatCANFrame(data_tx);
            //Expected Res: 05 62 01 23 00 78 55 55
        }
        //Case 3 in excel, Invalid DID
        else
        {
            data_tx[0] = 0x03;
            data_tx[1] = NRC;
            data_tx[2] = 0x22;
            data_tx[3] = INVALID_DID;
            for (int i = 4; i < 8; i++)
            {
                data_tx[i] = 0x00;
            }
            FormatCANFrame(data_tx);
            //Expected Res: 03 7F 22 31 55 55 55 55
        }
    }
    //Case 2 in excel, Invalid Length
    else
    {
        data_tx[0] = 0x03;
        data_tx[1] = NRC;
        data_tx[2] = 0x22;
        data_tx[3] = INVALID_LENGTH;
        for (int i = 4; i < 8; i++)
        {
            data_tx[i] = 0x00;
        }
        FormatCANFrame(data_tx);
        //Expected Res: 03 7F 22 13 55 55 55 55
    }

    if(HAL_CAN_AddTxMessage(&hcan2, &CAN2_pHeader, data_tx, &CAN2_pTxMailbox) != HAL_OK)
    {
        Error_Handler();
    }
}

void SID27_Practice(uint8_t *data_tx, uint8_t *data_rx)
{

}


