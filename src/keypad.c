#include "stm32f4xx.h"                  //Device header
#include "keypad.h"

extern uint_fast16_t refresh;
extern uint8_t numKeyPressed;

uint8_t buttonState = KEY_RELEASED;
uint8_t currentButtonPressed = 0x0;
uint8_t previousButtonPressed;
/**
*	@brief initiate peripheral clock for keypad
*/
void initKeypad () {
	
		// enable GPIO clocks
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);					//for key pad 

}

/**
*	@brief initialize the rows as inputs with 1s and columns as outputs with 0, 
*/

void rowAsInput () {
	
		GPIO_InitTypeDef gpio_init_s;

		// ROWS
		gpio_init_s.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 ; //1-row 1, 2=row 2, 3 = row 3 and 6 = row 4
		gpio_init_s.GPIO_Mode = GPIO_Mode_IN; // Set as input
		gpio_init_s.GPIO_Speed = GPIO_Speed_100MHz; // Don't limit slew rate
		gpio_init_s.GPIO_OType = GPIO_OType_PP; // Push-pull
		gpio_init_s.GPIO_PuPd = GPIO_PuPd_UP; //set pins as 1
		GPIO_Init(GPIOD,&gpio_init_s); //
	
		//COLUMNS
		gpio_init_s.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;//7=column 1, 8=column 2, 9=column 3 and 10=column 4
		gpio_init_s.GPIO_Mode = GPIO_Mode_OUT; // set as output
		gpio_init_s.GPIO_PuPd = GPIO_PuPd_DOWN; //set to 0
		GPIO_Init(GPIOD,&gpio_init_s); //
	
}
/**
*	@brief initialize the columns as inputs with 1s and rows as outputs with 0, 
*/
void columnAsInput () {
	
		GPIO_InitTypeDef gpio_init_s;

		// ROWS
		gpio_init_s.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 ; //1-row 1, 2=row 2, 3 = row 3 and 6 = row 4
		gpio_init_s.GPIO_Mode = GPIO_Mode_OUT; // Set as output
		gpio_init_s.GPIO_Speed = GPIO_Speed_100MHz; // Don't limit slew rate
		gpio_init_s.GPIO_OType = GPIO_OType_PP; // Push-pull
		gpio_init_s.GPIO_PuPd = GPIO_PuPd_DOWN; // set to 0
		GPIO_Init(GPIOD,&gpio_init_s); //
	
		//COLUMNS
		gpio_init_s.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;//7=column 1, 8=column 2, 9=column 3 and 10=column 4
		gpio_init_s.GPIO_Mode = GPIO_Mode_IN; // Set as input
		gpio_init_s.GPIO_PuPd = GPIO_PuPd_UP; // set to 1
		GPIO_Init(GPIOD,&gpio_init_s); //
	
	
}
/**
*	@brief Determine the state of the key being pressed
*/
void keyState () {
			
		searchColumn(); //check columns

		if(buttonState == KEY_RELEASED){// if it is not being pressed any longer then set param to 0
				currentButtonPressed = 0x0;
				return;
		}
		
		searchRow(); //if not columns, then check the rows
		
		if(currentButtonPressed == previousButtonPressed){// if button being pressed is still the same button, then set state to STILL PRESSED
				buttonState = KEY_STILL_PRESSED;	
		}	
}
/**
*	@brief search the column for the columns in which the button is being pressed
*/
void searchColumn () {
		uint8_t key = 0x0, key2 = 0x0;
	
		columnAsInput(); //set columns as input as they will be the ones going from 1 to 0
			
		if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7) == 0x0) { //if check column 1 is 0 then its the one being pressed
				key = 0x1;	
					
		} else if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_8) == 0x0) {//if check column 2 is 0 then its the one being pressed
				key = 0x2;	
					
		} else if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_9) == 0x0) {//if check column 3 is 0 then its the one being pressed
				key = 0x4;
					
		} else if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_10) == 0x0) {//if check column 4 is 0 then its the one being pressed
				key = 0x8;
		} 
	
		debounce();  //use the debouncing method to check for debouncing then repeat previous part for key 2

				if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7) == 0x0) {
				key2 = 0x1;	
					
		} else if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_8) == 0x0) {
				key2 = 0x2;	
					
		} else if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_9) == 0x0) {
				key2 = 0x4;
					
		} else if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_10) == 0x0) {
				key2 = 0x8;
		} 
		
		if(key == key2) { // if first check is the same as second time, then 
				if(key == 0x0) {
						buttonState = KEY_RELEASED; //if key is 0 then the state of the button is released and there was no button being pressed
				} else {
						buttonState = KEY_PRESSED; // else there is a button being pressed
						previousButtonPressed = currentButtonPressed;
						currentButtonPressed = key; // set the column found in current Button Pressed
				}
		}	
}
/**
*	@brief search the rows for the row in which the button is being pressed
*/
void searchRow () {
		uint8_t key = 0x0;
	
		rowAsInput(); //set rows as input as they will be the ones going from 1 to 0
		
		if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_1) == 0x0) {//if check row 1 is 0 then its the one being pressed
			key = 0x10;	
			
		} else if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2) == 0x0) {//if check row 2 is 0 then its the one being pressed
			key = 0x20;	
			
		} else if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3) == 0x0) {//if check row 3 is 0 then its the one being pressed
				key = 0x40;
			
		}else	if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_6) == 0x0) {//if check row 4 is 0 then its the one being pressed
				key = 0x80;
		}

			currentButtonPressed ^= key; // add the row found bit to the column found bit by XORing to get the button
}
/**
*	@brief finds the key being pressed
*	@retval  returns the character of the button being pressed
*/
uint8_t getKey () {
	
		if(buttonState ==	KEY_PRESSED) {//if a button is being pressed then find the case using the 2 hexbits
			
			switch(currentButtonPressed) {// all values set using DEFINE
				
				case ZERO : return '0';
				case ONE : return '1';
				case TWO : return '2';
				case THREE : return '3';
				case FOUR : return '4';
				case FIVE : return '5';
				case SIX : return '6';
				case SEVEN : return '7';
				case EIGHT : return '8';
				case NINE : return '9';
				case LETTER_A : return 'A';
				case LETTER_B : return 'B';
				case LETTER_C: return 'C';
				case LETTER_D: return 'D';
				case STAR: return '*';
				case SHARP: return '#';

			}
		}
	return 0x0;
}
/**
*	@brief debounces by delaying
*/
void debounce() {

		uint8_t debounce = 0;
		uint8_t temp = refresh;
	
		while(debounce < 3) {//using the refresh param, increment the debounce 
				
				if(temp + 1 == refresh || temp - 3 == refresh) {
					debounce++;
					temp = refresh;
				}
		}
			
}
