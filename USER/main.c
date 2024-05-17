#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "lcd16x2.h"
#include "dht11.h"
#include "delay.h"
#include <stdio.h>

DHT11_TypeDef dht11_data;

int main(void)
{
    // Delay initialization
    DelayInit();
    // LCD initialization
    LCD_Init();
	
		DHT11_Init();
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
					sprintf(data,"Temp: %.1f",temperature);
					LCD_Gotoxy(0,0);
					LCD_Puts(data);
					float humidity = dht11_data.humidityI + 0.1 * dht11_data.humidityR;
					sprintf(data,"Humd: %.1f",humidity);
					LCD_Gotoxy(0,1);
					LCD_Puts(data);
				}
			DelayMs(100);
		}

    		

}

