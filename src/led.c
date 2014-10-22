#include "stm32f4xx.h"                  // Device header

/**
*	@brief initialize the LEDs
*/
void initLED() {

		// declare GPIO initializatio structure
		GPIO_InitTypeDef init;

	
		// LED output pins initialization
		init.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; // select pins 12,13,14,15(Green, Orange, Red, Blue) from GPIOD (for LED output)
		init.GPIO_Mode = GPIO_Mode_OUT; // Set as output
		init.GPIO_Speed = GPIO_Speed_100MHz; // Don't limit slew rate
		init.GPIO_OType = GPIO_OType_PP; // Push-pull
		init.GPIO_PuPd = GPIO_PuPd_NOPULL; // Not input, don't pull
		GPIO_Init(GPIOD,&init); //initialize GPIOD with the above parameters
}

/**
*	@brief flash through the LEDs where one LED is turned on and previous is turned off.
*	@param numLED: cycle number to be activated
*				@args 1,2,3: possible cycle numbers
*	@retval returns incremented cycle number
*/
uint8_t flashLED(uint8_t numLED) {
			//Cycle through indefinitely, for each run
	
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
/**
*	@brief flash the red LED
*	@param numLED: cycle number to be activated
*				@args 1,2,3: possible cycle numbers
*	@retval returns incremented cycle number
*/

uint8_t redLEDFlash (uint8_t numLED) {
	
		if(numLED == 1) {//if cycle 1 then set the red LED
					GPIO_SetBits(GPIOD, GPIO_Pin_14);
					numLED++;
		} else {  // else turn off the red LED
					GPIO_ResetBits(GPIOD, GPIO_Pin_14);
					numLED = 1;
		}
		return numLED;
}
