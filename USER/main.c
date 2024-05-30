#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "lcd16x2.h"
#include "dht11.h"
#include "delay.h"
#include "pwm.h"
#include "button.h"
#include "usbcdc.h"
#include <stdio.h>

DHT11_TypeDef dht11_data;

volatile int target_temp = 25;

void EXTI0_IRQHandler(void) {
    if (EXTI->PR & EXTI_PR_INCREASE) { // Kiểm tra nếu ngắt từ PA0
        target_temp++; // Tăng giá trị biến target_temp
        EXTI->PR |= EXTI_PR_INCREASE; // Xóa cờ ngắt
    }
}

void EXTI1_IRQHandler(void) {
    if (EXTI->PR & EXTI_PR_DECREASE) { // Kiểm tra nếu ngắt từ PA1
        target_temp--; // Giảm giá trị biến target_temp
        EXTI->PR |= EXTI_PR_DECREASE; // Xóa cờ ngắt
    }
}


int main(void)
{
    DelayInit();
    LCD_Init();
	DHT11_Init();
	PWM_Init();
	BUTTON_Init();
	
	LCD_Gotoxy(0,0);
	LCD_Puts("starting");
    while(1)
		{
				
			/*LCD_SendCommand(0x1C);
				LCD_SendCommand(0x18);*/
				
				if (DHT11_Read(&dht11_data) == DHT11_OK)
				{
					DHT11_Read(&dht11_data);
					float temperature = dht11_data.temperatureI + 0.1 * dht11_data.temperatureR;
					char data[16];
					sprintf(data,"Cur Temp: %.1f",temperature);
					LCD_Gotoxy(0,0);
					LCD_Puts(data);
					// float humidity = dht11_data.humidityI + 0.1 * dht11_data.humidityR;
					sprintf(data,"Tar Temp: %.1f",(float)target_temp);
					LCD_Gotoxy(0,1);
					LCD_Puts(data);
					
					PWM_ChangeBandWidth((temperature - target_temp)/10*999);
				}
			DelayMs(100);
		}

    		

}

