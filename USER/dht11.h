#ifndef __DHT_H
#define __DHT_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "delay.h"

typedef struct {
  uint8_t temperatureI;
  uint8_t temperatureR;
  uint8_t humidityI;
  uint8_t humidityR;
} DHT11_TypeDef;

#define DHT11_OK       0
#define DHT11_ERROR    1

void DHT11_Init();
uint8_t DHT11_Read(DHT11_TypeDef *DHT11_Data);

#ifdef __cplusplus

}
#endif

#endif /* __MISC_H */