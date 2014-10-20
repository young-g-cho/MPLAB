#include "stm32f4xx.h"
#include <stdint.h>



void initPanel() {
	
		GPIO_InitTypeDef gpio_init_s;
		
		// initialize GPIO pin for servo output
		gpio_init_s.GPIO_Pin = GPIO_Pin_1;
		gpio_init_s.GPIO_Mode = GPIO_Mode_OUT; // Set as output
		gpio_init_s.GPIO_Speed = GPIO_Speed_100MHz; // Don't limit slew rate
		gpio_init_s.GPIO_OType = GPIO_OType_PP; // Push-pull
		gpio_init_s.GPIO_PuPd = GPIO_PuPd_NOPULL; 
		GPIO_Init(GPIOB,&gpio_init_s); 
	
		// initialize hardware timer (or sysTick)
		
		
}

