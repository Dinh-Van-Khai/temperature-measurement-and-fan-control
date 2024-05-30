#include "button.h"

void BUTTON_Init(void) {
    // Bật clock cho GPIOA
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    // Cấu hình PA0 và PA1 là ngõ vào floating (mặc định)
    GPIOA->CRL &= ~GPIO_CRL_MODE0; // PA0 là input
    GPIOA->CRL &= ~GPIO_CRL_CNF0;
    GPIOA->CRL |= GPIO_CRL_CNF0_0; // PA0 floating input

    GPIOA->CRL &= ~GPIO_CRL_MODE1; // PA1 là input
    GPIOA->CRL &= ~GPIO_CRL_CNF1;
    GPIOA->CRL |= GPIO_CRL_CNF1_0; // PA1 floating input

    // Bật clock cho AFIO (Alternate Function I/O)
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    // Cấu hình PA0 và PA1 cho ngắt ngoài (EXTI)
    AFIO->EXTICR[0] &= ~AFIO_EXTICR1_EXTI0;
    AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PA; // EXTI0 từ PA0

    AFIO->EXTICR[0] &= ~AFIO_EXTICR1_EXTI1;
    AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI1_PA; // EXTI1 từ PA1

    // Cấu hình EXTI0 và EXTI1 là rising edge trigger
    EXTI->IMR |= EXTI_IMR_MR0;
    EXTI->IMR |= EXTI_IMR_MR1;
    EXTI->RTSR |= EXTI_RTSR_TR0;
    EXTI->RTSR |= EXTI_RTSR_TR1;

    // Bật ngắt trong NVIC
    NVIC_EnableIRQ(EXTI0_IRQn);
    NVIC_SetPriority(EXTI0_IRQn, 0);

    NVIC_EnableIRQ(EXTI1_IRQn);
    NVIC_SetPriority(EXTI1_IRQn, 0);
}
