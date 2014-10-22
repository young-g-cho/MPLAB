#include "stm32f4xx.h"                  // Device header
#include "7segment.h"

extern uint_fast16_t refresh;
extern uint8_t decimal;

void initDisplay () {
	
		GPIO_InitTypeDef gpio_init_s;
	
		// for segement A-G + DP + L1-L3
		gpio_init_s.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | 
		GPIO_Pin_11| GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14; // 
		gpio_init_s.GPIO_Mode = GPIO_Mode_OUT; // Set as OUTPUT
		gpio_init_s.GPIO_Speed = GPIO_Speed_100MHz; // Don't limit slew rate
		gpio_init_s.GPIO_OType = GPIO_OType_PP; // Push-pull
		gpio_init_s.GPIO_PuPd = GPIO_PuPd_NOPULL; // Not input, don't pull
		GPIO_Init(GPIOE,&gpio_init_s); //
	
		//for segement Digi 1 - 4
		gpio_init_s.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
		GPIO_Init(GPIOB,&gpio_init_s); //
	
		
	
}

void intiTIMAndNVIC () {
	
		NVIC_InitTypeDef initNVIC;
		TIM_TimeBaseInitTypeDef initTIM;
			
		// enable GPIO clocks
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);												//for GPIO TIM3
	
		initNVIC.NVIC_IRQChannel =  TIM3_IRQn ;
		initNVIC.NVIC_IRQChannelPreemptionPriority = 0;
		initNVIC.NVIC_IRQChannelSubPriority = 1;
		initNVIC.NVIC_IRQChannelCmd = ENABLE;
		
		NVIC_Init(&initNVIC);
	
		/* Time base configuration */
	
		initTIM.TIM_Period = 3000; // 
		initTIM.TIM_Prescaler = 42; // 
		initTIM.TIM_ClockDivision = 0;
		initTIM.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM3, &initTIM);
		
		/* TIM3 enable counter */
		TIM_Cmd(TIM3, ENABLE);
		/*TIM IT enable */
		TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

}

void TIM3_IRQHandler() {
	
		if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
			
				if(refresh > 3) {
						refresh = 0;
				} else {
						refresh ++;																																							//max 4 
				}
					TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		}
}

// mode = 0 => normal mode , mode = 1 => display game correct answer
void numDisplay (uint8_t mode, uint8_t digit, uint8_t updateLocation, uint8_t degree_on) {
		
		GPIO_ResetBits(GPIOE, GPIO_Pin_15 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10| GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
		GPIO_SetBits(GPIOB, GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
	
	
		if(updateLocation == 1) {
				GPIO_ResetBits(GPIOB, GPIO_Pin_11);
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
		
		
		switch (digit) {
			
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
			case 'E':
					GPIO_SetBits(GPIOE, GPIO_Pin_15);
					GPIO_SetBits(GPIOE, GPIO_Pin_6);
					GPIO_SetBits(GPIOE, GPIO_Pin_7);
					GPIO_SetBits(GPIOE, GPIO_Pin_8);
					GPIO_SetBits(GPIOE, GPIO_Pin_9);				
			break;
			case 'L':
					GPIO_SetBits(GPIOE, GPIO_Pin_6);
					GPIO_SetBits(GPIOE, GPIO_Pin_7);
					GPIO_SetBits(GPIOE, GPIO_Pin_8);	
			break;
		}
	
}