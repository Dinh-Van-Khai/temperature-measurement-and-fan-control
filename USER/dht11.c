#include "dht11.h"

#define DHT11_DATA      GPIO_Pin_0

void DHT11_Init()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitTypeDef        GPIO_DHT11_InitStruction;
    
    /*Configure GPIO pin Output Level */
    GPIO_WriteBit(GPIOB, DHT11_DATA, 0);  
    
    GPIO_DHT11_InitStruction.GPIO_Mode    = GPIO_Mode_Out_PP;
    GPIO_DHT11_InitStruction.GPIO_Pin     = DHT11_DATA;      
    GPIO_DHT11_InitStruction.GPIO_Speed   = GPIO_Speed_10MHz;
    GPIO_Init(GPIOB, &GPIO_DHT11_InitStruction);
}

uint8_t DHT11_Read(DHT11_TypeDef *DHT11_Data)
{
    uint8_t buffer[5] = {0};
    uint8_t i, j;

    GPIO_InitTypeDef        GPIO_DHT11_InitStruction;
    GPIO_DHT11_InitStruction.GPIO_Mode    = GPIO_Mode_Out_PP;
    GPIO_DHT11_InitStruction.GPIO_Pin     = DHT11_DATA;      
    GPIO_DHT11_InitStruction.GPIO_Speed   = GPIO_Speed_10MHz;
    GPIO_Init(GPIOB, &GPIO_DHT11_InitStruction);

    GPIO_WriteBit(GPIOB, DHT11_DATA, 0);
    DelayUs(18000);

    GPIO_WriteBit(GPIOB, DHT11_DATA, 1);

    GPIO_DHT11_InitStruction.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_DHT11_InitStruction);

    while (GPIO_ReadInputDataBit(GPIOB, DHT11_DATA)); // Chờ tín hiệu thấp

    while (!GPIO_ReadInputDataBit(GPIOB, DHT11_DATA)); // Chờ tín hiệu cao

    while (GPIO_ReadInputDataBit(GPIOB, DHT11_DATA)); // Chờ tín hiệu thấp

    for (j = 0; j < 5; j++)
    {
        uint8_t result = 0;
        for (i = 0; i < 8; i++)
        {
        while (!GPIO_ReadInputDataBit(GPIOB, DHT11_DATA)); // Chờ tín hiệu cao
        DelayUs(40);
        if (GPIO_ReadInputDataBit(GPIOB, DHT11_DATA) == 0) // Kiểm tra thời gian tín hiệu cao
        {
            result &= ~(1 << (7 - i)); // Ghi dữ liệu vào biến result
        }
        else
        {
            while (GPIO_ReadInputDataBit(GPIOB, DHT11_DATA)); // Chờ tín hiệu thấp
            result |= (1 << (7 - i)); // Ghi dữ liệu vào biến result
        }
        }
        buffer[j] = result;
    }

    if (buffer[0] + buffer[1] + buffer[2] + buffer[3] == buffer[4])
    {
        DHT11_Data->humidityI = buffer[0];
        DHT11_Data->humidityR = buffer[1];
        DHT11_Data->temperatureI = buffer[2];
        DHT11_Data->temperatureR = buffer[3];
        return DHT11_OK;
    }
    else
    {
        return DHT11_ERROR;
    }
}