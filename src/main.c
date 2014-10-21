#include <stdio.h>
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"
#include "accelerometer.h"
#include "led.h"
#include "filter.h"
#include "7segment.h"
#include "keypad.h"
#include "game.h"



memsReading data;

volatile uint_fast16_t tick = 0;
volatile uint_fast16_t refresh = 0;

uint8_t first;
uint8_t second;
uint8_t third;
uint8_t decimal = 0;
uint8_t gameState;    //1 for playing, 2 for gameOver(player loss) 3 for gameOver(player Win)
uint8_t numLED = 0;				//LED tracker


MovingAverageFilter x;
MovingAverageFilter y;
MovingAverageFilter z;

int main(){
	
	initForGpio ();
	initAccelerometer ();
	intiEXTI0AndNVIC () ;
	initDisplay () ;
	initKeypad ();
	intiTIMAndNVIC ();
	initLED ();

	
	initFilter(&x);
	initFilter(&y);
	initFilter(&z);
	
	uint8_t gameInit = 0;
	uint8_t delay =0;
	

	
	while(1){
		
			if(tick) {
				
				tick = 0;
				data = getReading();
				
				filterAdd(&x,data.x);
				filterAdd(&y,data.y);
				filterAdd(&z,data.z);
				toAngles(&data, x.average, y.average, z.average);
				
				
			} 	
		 
		 
			
		 if (gameState == 1){
					
					userInput();
					
					//update screen if game is not over
						if(refresh == 1) {
								numDisplay (decimal, first, 1,1);
					} 	else if(refresh == 2) {
								numDisplay (decimal, second,2,1);
					} 	else if(refresh == 3) {
								numDisplay (decimal, third, 3,1);
					}
					
				}
				
				else {
						
						if (gameState == 3)
						{
							printAnswer();
							numLED = flashLED(numLED);
																
						}
						
						else if (gameState == 2)
						{
							if (refresh == 1)
							numDisplay(0,'L',1,0);
							else if (refresh == 2)
							numDisplay(0,'0',2,0);
							else if (refresh == 3)
							numDisplay(0,'5',3,0);
							else 
							numDisplay(0,'E',4,0);		

							numLED = redLEDFlash(numLED);
							
						}	
						
						else
						{
						
							//game initialization
							if(gameInit == 0) {
									if(delay == 30) {
										startGame(data.roll);
										gameInit = 1;
										}
				
									else 
									delay++;
											
						}
							
						}
						
					}

		

 
	
} //end while
	
	return 0;
}
