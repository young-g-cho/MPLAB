#include "stm32f4xx.h"                  // Device header


void initLED() {

		// declare GPIO initializatio structure
		GPIO_InitTypeDef init;

	
		// LED output pins initialization
		init.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; // select pins 1213,14,15(Green, Orange, Red, Blue) from GPIOD (for LED output)
		init.GPIO_Mode = GPIO_Mode_OUT; // Set as output
		init.GPIO_Speed = GPIO_Speed_100MHz; // Don't limit slew rate
		init.GPIO_OType = GPIO_OType_PP; // Push-pull
		init.GPIO_PuPd = GPIO_PuPd_NOPULL; // Not input, don't pull
		GPIO_Init(GPIOD,&init); //initialize GPIOD with the above parameters
}


uint8_t flashLED(uint8_t numLED) {
			//Cycle through indefinitely, for each run
			//one LED is turned on and previous is turned off.
	
			if(numLED == 1) {
					GPIO_SetBits(GPIOD, GPIO_Pin_15);
					GPIO_ResetBits(GPIOD, GPIO_Pin_12);
					numLED++;
			} else if(numLED == 2) {
					GPIO_SetBits(GPIOD, GPIO_Pin_12);
					GPIO_ResetBits(GPIOD, GPIO_Pin_13);
					numLED++;
				
			} else if(numLED == 3) {
					GPIO_SetBits(GPIOD, GPIO_Pin_13);
					GPIO_ResetBits(GPIOD, GPIO_Pin_14);
					numLED++;
			} else {
					GPIO_SetBits(GPIOD, GPIO_Pin_14);
					GPIO_ResetBits(GPIOD, GPIO_Pin_15);
					numLED = 1;
			}
			
			return numLED;
}

uint8_t redLEDFlash (uint8_t numLED) {
	
		if(numLED == 1) {
					GPIO_SetBits(GPIOD, GPIO_Pin_14);
					numLED++;
		} else {
					GPIO_ResetBits(GPIOD, GPIO_Pin_14);
					numLED = 1;
		}
		return numLED;
}
