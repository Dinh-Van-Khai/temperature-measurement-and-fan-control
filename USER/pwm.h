#ifndef __PWM_H
#define __PWM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "delay.h"

void PWM_Init();
void PWM_ChangeBandWidth(uint8_t band-width);

#ifdef __cplusplus

}
#endif

#endif /* __MISC_H */
