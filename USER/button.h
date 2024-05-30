#ifndef __EXTI_H
#define __EXTI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "delay.h"

#define EXTI_PR_INCREASE      EXTI_PR_PR0
#define EXTI_PR_DECREASE      EXTI_PR_PR1

void BUTTON_Init();

#ifdef __cplusplus

}
#endif

#endif /* __MISC_H */
