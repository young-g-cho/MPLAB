#include "stm32f4xx.h"                  // Device header
#include "7segment.h"

extern uint_fast16_t refresh;
extern uint8_t decimal;

void initDisplay () {
	
		GPIO_InitTypeDef gpio_init_s;
	
		// for segement A-G + DP + L1-L3
		gpio_init_s.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | //8 segments of the display 
		GPIO_Pin_11| GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14; // dots, and degree sign
		gpio_init_s.GPIO_Mode = GPIO_Mode_OUT; // Set as OUTPUT
		gpio_init_s.GPIO_Speed = GPIO_Speed_100MHz; // Don't limit slew rate
		gpio_init_s.GPIO_OType = GPIO_OType_PP; // Push-pull
		gpio_init_s.GPIO_PuPd = GPIO_PuPd_NOPULL; // Not input, don't pull
		GPIO_Init(GPIOE,&gpio_init_s); 
	
		//for segement Digi 1 - 4
		gpio_init_s.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
		GPIO_Init(GPIOB,&gpio_init_s); 
	
		
	
}

/*!
*		@brief initializes the timer and the NVIC for the timer
*/

void intiTIMAndNVIC () { 
	
		NVIC_InitTypeDef initNVIC;
		TIM_TimeBaseInitTypeDef initTIM;
			
		// enable GPIO clocks
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//for GPIO TIM3
	
		initNVIC.NVIC_IRQChannel =  TIM3_IRQn ; //set NVIC to the correct timer as we will use timer 3
		initNVIC.NVIC_IRQChannelPreemptionPriority = 0; // highest type of priority
		initNVIC.NVIC_IRQChannelSubPriority = 1;  // if it needs to wait, set as next highest priority
		initNVIC.NVIC_IRQChannelCmd = ENABLE; //enable the channel
		
		NVIC_Init(&initNVIC); //initialize
	
		/* Time base configuration */
	
		initTIM.TIM_Period = 3000; // since we use three of the displays and we want 100Hz for each, we set it to 3000
		initTIM.TIM_Prescaler = 42; // 
		initTIM.TIM_ClockDivision = 0; //not need for this
		initTIM.TIM_CounterMode = TIM_CounterMode_Up; //set the mode to count upwards
		TIM_TimeBaseInit(TIM3, &initTIM);
		
		/* TIM3 enable counter */
		TIM_Cmd(TIM3, ENABLE);
		/*TIM IT enable */
		TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

}
/**
*		@brief handles the interrupt for timer 3
*/
void TIM3_IRQHandler() {
	
		if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) { //when the status of the timer isnt RESET then check the refresh param
			
				if(refresh > 3) {
						refresh = 0; //if greater than 3, reset it
				} else { 				//else increment it
						refresh ++;																																							//max 4 
				}
					TIM_ClearITPendingBit(TIM3, TIM_IT_Update); // clears the pending bit of the interrupt update source
		}
}


/**
* @brief determines what is to be displayed on the 7 segment LED
*
* @param mode: the current mode of the display
*					@arg 0: normal mode where user is inputting values
*					@arg 1: display current game's answer
*	@param digit: desired number to be displayed
*					@args first, second, third: param where number is held
*	@param updateLocation: which 7 segment to affect
*					@args 1,2,3: desired display segments
*	@param degree_on: turn on or off the degree sign
*					@args 0,1: off or on respectively
*/
void numDisplay (uint8_t mode, uint8_t digit, uint8_t updateLocation, uint8_t degree_on) {
		//first reset all pins and set pin for initializing the 7segemnt display
		GPIO_ResetBits(GPIOE, GPIO_Pin_15 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10| GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
		GPIO_SetBits(GPIOB, GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
	
	
		if(updateLocation == 1) { 																			// the location of the 7segment display. The bits will be held low for the display we want to change while others held high
				GPIO_ResetBits(GPIOB, GPIO_Pin_11);						//mode determines the decimal point for displaying the correct angle to user.
				if(mode == 1)  													
						GPIO_SetBits(GPIOE, GPIO_Pin_10);
		} else if (updateLocation == 2) {
				GPIO_ResetBits(GPIOB, GPIO_Pin_12);
				if(mode == 2)
						GPIO_SetBits(GPIOE, GPIO_Pin_10);
		} else if (updateLocation == 3) {
				GPIO_ResetBits(GPIOB, GPIO_Pin_13);
		} 
			else if (updateLocation == 4){
				GPIO_ResetBits(GPIOB, GPIO_Pin_14);
		}

		// degree sign 
		if (degree_on != 0)
			GPIO_SetBits(GPIOE, GPIO_Pin_11);
		
		
		switch (digit) {																											//segments to set to achieve desired numbers
			
			case '0': 
					GPIO_SetBits(GPIOE, GPIO_Pin_15);
					GPIO_SetBits(GPIOE, GPIO_Pin_4);
					GPIO_SetBits(GPIOE, GPIO_Pin_5);
					GPIO_SetBits(GPIOE, GPIO_Pin_6);
					GPIO_SetBits(GPIOE, GPIO_Pin_7);
					GPIO_SetBits(GPIOE, GPIO_Pin_8);
			break;
			case '1':
					GPIO_SetBits(GPIOE, GPIO_Pin_4);
					GPIO_SetBits(GPIOE, GPIO_Pin_5);
			break;
			case '2':
					GPIO_SetBits(GPIOE, GPIO_Pin_15);
					GPIO_SetBits(GPIOE, GPIO_Pin_4);
					GPIO_SetBits(GPIOE, GPIO_Pin_6);
					GPIO_SetBits(GPIOE, GPIO_Pin_7);
					GPIO_SetBits(GPIOE, GPIO_Pin_9);
			break;
			case '3':
					GPIO_SetBits(GPIOE, GPIO_Pin_15);
					GPIO_SetBits(GPIOE, GPIO_Pin_4);
					GPIO_SetBits(GPIOE, GPIO_Pin_5);
					GPIO_SetBits(GPIOE, GPIO_Pin_6);
					GPIO_SetBits(GPIOE, GPIO_Pin_9);
			break;
			case '4':
					GPIO_SetBits(GPIOE, GPIO_Pin_4);
					GPIO_SetBits(GPIOE, GPIO_Pin_5);
					GPIO_SetBits(GPIOE, GPIO_Pin_8);
					GPIO_SetBits(GPIOE, GPIO_Pin_9);
			break;
			case '5':
					GPIO_SetBits(GPIOE, GPIO_Pin_15);
					GPIO_SetBits(GPIOE, GPIO_Pin_5);
					GPIO_SetBits(GPIOE, GPIO_Pin_6);
					GPIO_SetBits(GPIOE, GPIO_Pin_8);
					GPIO_SetBits(GPIOE, GPIO_Pin_9);
			break;
			case '6':
					GPIO_SetBits(GPIOE, GPIO_Pin_15);
					GPIO_SetBits(GPIOE, GPIO_Pin_5);
					GPIO_SetBits(GPIOE, GPIO_Pin_6);
					GPIO_SetBits(GPIOE, GPIO_Pin_7);
					GPIO_SetBits(GPIOE, GPIO_Pin_8);
					GPIO_SetBits(GPIOE, GPIO_Pin_9);
			break;
			case '7':
					GPIO_SetBits(GPIOE, GPIO_Pin_15);
					GPIO_SetBits(GPIOE, GPIO_Pin_4);
					GPIO_SetBits(GPIOE, GPIO_Pin_5);
			break;
			case '8':
					GPIO_SetBits(GPIOE, GPIO_Pin_15);
					GPIO_SetBits(GPIOE, GPIO_Pin_4);
					GPIO_SetBits(GPIOE, GPIO_Pin_5);
					GPIO_SetBits(GPIOE, GPIO_Pin_6);
					GPIO_SetBits(GPIOE, GPIO_Pin_7);
					GPIO_SetBits(GPIOE, GPIO_Pin_8);
					GPIO_SetBits(GPIOE, GPIO_Pin_9);
			break;
			case '9':	
					GPIO_SetBits(GPIOE, GPIO_Pin_15);
					GPIO_SetBits(GPIOE, GPIO_Pin_4);
					GPIO_SetBits(GPIOE, GPIO_Pin_5);
					GPIO_SetBits(GPIOE, GPIO_Pin_6);
					GPIO_SetBits(GPIOE, GPIO_Pin_8);
					GPIO_SetBits(GPIOE, GPIO_Pin_9);
			break;
			case 'Y': //Y in Yes
					GPIO_SetBits(GPIOE, GPIO_Pin_4);
					GPIO_SetBits(GPIOE, GPIO_Pin_5);
					GPIO_SetBits(GPIOE, GPIO_Pin_8);
					GPIO_SetBits(GPIOE, GPIO_Pin_9);
					GPIO_SetBits(GPIOE, GPIO_Pin_6);
			break;
			case 'E': // E in yEs and losE
					GPIO_SetBits(GPIOE, GPIO_Pin_15);
					GPIO_SetBits(GPIOE, GPIO_Pin_6);
					GPIO_SetBits(GPIOE, GPIO_Pin_7);
					GPIO_SetBits(GPIOE, GPIO_Pin_8);
					GPIO_SetBits(GPIOE, GPIO_Pin_9);				
			break;
			case 'S': // S in yeS and loSe
					GPIO_SetBits(GPIOE, GPIO_Pin_15);
					GPIO_SetBits(GPIOE, GPIO_Pin_5);
					GPIO_SetBits(GPIOE, GPIO_Pin_6);
					GPIO_SetBits(GPIOE, GPIO_Pin_8);
					GPIO_SetBits(GPIOE, GPIO_Pin_9);
			break;
			case 'L': // L in Lose
					GPIO_SetBits(GPIOE, GPIO_Pin_6);
					GPIO_SetBits(GPIOE, GPIO_Pin_7);
					GPIO_SetBits(GPIOE, GPIO_Pin_8);	
			break;
		}
}
