#include "stm32f4xx.h"                  //Device header
#include "keypad.h"

extern uint_fast16_t refresh;
extern uint8_t numKeyPressed;

uint8_t buttonState = KEY_RELEASED;
uint8_t currentButtonPressed = 0x0;
uint8_t previousButtonPressed;

void initKeypad () {
	
		// enable GPIO clocks
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);												//for key pad 

}

void rowAsInput () {
	
		GPIO_InitTypeDef gpio_init_s;

		// ROWS
		gpio_init_s.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 ;
		gpio_init_s.GPIO_Mode = GPIO_Mode_IN; // Set as input
		gpio_init_s.GPIO_Speed = GPIO_Speed_100MHz; // Don't limit slew rate
		gpio_init_s.GPIO_OType = GPIO_OType_PP; // Push-pull
		gpio_init_s.GPIO_PuPd = GPIO_PuPd_UP; //
		GPIO_Init(GPIOD,&gpio_init_s); //
	
		//COLUMNS
		gpio_init_s.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
		gpio_init_s.GPIO_Mode = GPIO_Mode_OUT; // 
		gpio_init_s.GPIO_PuPd = GPIO_PuPd_DOWN; //
		GPIO_Init(GPIOD,&gpio_init_s); //
	
}

void columnAsInput () {
	
		GPIO_InitTypeDef gpio_init_s;

		// ROWS
		gpio_init_s.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 ;
		gpio_init_s.GPIO_Mode = GPIO_Mode_OUT; // Set as output
		gpio_init_s.GPIO_Speed = GPIO_Speed_100MHz; // Don't limit slew rate
		gpio_init_s.GPIO_OType = GPIO_OType_PP; // Push-pull
		gpio_init_s.GPIO_PuPd = GPIO_PuPd_DOWN; // 
		GPIO_Init(GPIOD,&gpio_init_s); //
	
		//COLUMNS
		gpio_init_s.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
		gpio_init_s.GPIO_Mode = GPIO_Mode_IN; // Set as input
		gpio_init_s.GPIO_PuPd = GPIO_PuPd_UP; //
		GPIO_Init(GPIOD,&gpio_init_s); //
	
	
}

void keyState () {
			
		searchColumn();

		if(buttonState == KEY_RELEASED){
				currentButtonPressed = 0x0;
				return;
		}
		
		searchRow();
		
		if(currentButtonPressed == previousButtonPressed){
				buttonState = KEY_STILL_PRESSED;	
		}	
}

void searchColumn () {
		uint8_t key = 0x0, key2 = 0x0;
	
		columnAsInput();
			
		if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7) == 0x0) {
				key = 0x1;	
					
		} else if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_8) == 0x0) {
				key = 0x2;	
					
		} else if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_9) == 0x0) {
				key = 0x4;
					
		} else if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_10) == 0x0) {
				key = 0x8;
		} 
	
		debounce();

				if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7) == 0x0) {
				key2 = 0x1;	
					
		} else if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_8) == 0x0) {
				key2 = 0x2;	
					
		} else if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_9) == 0x0) {
				key2 = 0x4;
					
		} else if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_10) == 0x0) {
				key2 = 0x8;
		} 
		
		if(key == key2) {
				if(key == 0x0) {
						buttonState = KEY_RELEASED;
				} else {
						buttonState = KEY_PRESSED;
						previousButtonPressed = currentButtonPressed;
						currentButtonPressed = key;
				}
		}	
}

void searchRow () {
		uint8_t key = 0x0;
	
		rowAsInput();
		
		if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_1) == 0x0) {
			key = 0x10;	
			
		} else if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2) == 0x0) {
			key = 0x20;	
			
		} else if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3) == 0x0) {
				key = 0x40;
			
		}else	if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_6) == 0x0) {
				key = 0x80;
		}

			currentButtonPressed ^= key;
}

uint8_t getKey () {
	
		if(buttonState ==	KEY_PRESSED) {
			
			switch(currentButtonPressed) {
				
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

void debounce() {

		uint8_t debounce = 0;
		uint8_t temp = refresh;
	
		while(debounce < 3) {
				
				if(temp + 1 == refresh || temp - 3 == refresh) {
					debounce++;
					temp = refresh;
				}
		}
			
}
