#include "pwm.h"

#define PWM_OUT      GPIO_Pin_7

void PWM_Init()
{
    // Bật clock cho GPIOA
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    // Cấu hình chân A7 là đầu ra chế độ AF (Alternate Function)
    GPIOA->CRL &= ~(GPIO_CRL_MODE7 | GPIO_CRL_CNF7);
    GPIOA->CRL |= GPIO_CRL_MODE7_1 | GPIO_CRL_CNF7_1;

    // Bật clock cho TIM3
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    // Cấu hình TIM3
    TIM3->PSC = 0; // Prescaler
    TIM3->ARR = 999; // Auto-Reload Register (chu kỳ xung)
    TIM3->CCR2 = 0; // Capture/Compare Register (duty cycle)

    // Cấu hình chế độ PWM
    TIM3->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2; // Chọn chế độ PWM mode 1
    TIM3->CCER |= TIM_CCER_CC2E; // Bật kênh 2 (chân A7) của TIM3

    // Bật TIM3
    TIM3->CR1 |= TIM_CR1_CEN;
}
void PWM_ChangeBandWidth(uint32_t band_width)
{
    if (band_width > 999) TIM3 -> CCR2 = 999;
    else TIM3 -> CCR2 = band_width;
}