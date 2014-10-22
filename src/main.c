#include <stdio.h>
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"
#include "accelerometer.h"
#include "led.h"
#include "filter.h"
#include "7segment.h"
#include "keypad.h"
#include "game.h"
//#include "servoControl.c"


memsReading data;

volatile uint_fast16_t tick = 0;
volatile uint_fast16_t refresh = 0;

uint8_t first;  //variable for first digit
uint8_t second; //variable for second digit
uint8_t third;  //variable for third digit
uint8_t decimal = 0;
uint8_t gameState;    //1 for playing, 2 for gameOver(player loss) 3 for gameOver(player Win)
uint8_t numLED = 0;				//LED tracker


MovingAverageFilter x;
MovingAverageFilter y;
MovingAverageFilter z;


/**
*	@brief initialize everything and play the game!!
*	@retval returns 0
*/

int main(){
	
	
	//initialize everything needed
	initForGpio ();
	initAccelerometer ();
	intiEXTI0AndNVIC () ;
	initDisplay () ;
	initKeypad ();
	intiTIMAndNVIC ();
	initLED ();
	//initPanel();
	
	initFilter(&x);
	initFilter(&y);
	initFilter(&z);
	
	uint8_t gameInit = 0;
	uint8_t delay =0;
	

	
	while(1){ // infinite loop
		
			if(tick) { //when ticked get the data, add to filter, convert to angles
				
				tick = 0;
				data = getReading();
				
				filterAdd(&x,data.x);
				filterAdd(&y,data.y);
				filterAdd(&z,data.z);
				toAngles(&data, x.average, y.average, z.average);
				
				//printf("x = %d\n",x.average);
				//printf("y = %d\n",y.average);
				//printf("z = %d\n",z.average);
				//printf("roll = %d\n",data.roll);
				//printf("pitch = %d\n",data.pitch);
				
			} else { 	
					
				if (gameState == 1){ //user is playing the game
					
					userInput(); //wait for user input
					
					//update screen if game is not over set the desired numbers to the display
						if(refresh == 1) {
								numDisplay (decimal, first, 1,1); 
					} 	else if(refresh == 2) {
								numDisplay (decimal, second,2,1);
					} 	else if(refresh == 3) {
								numDisplay (decimal, third, 3,1);
					}
				}
				
				else {
						
						if (gameState == 3) // if player won the game, display YES
						{
							numDisplay(0,'Y',1,0);
							numDisplay(0,'E',2,0);
							numDisplay(0,'S',3,0);
						
						}
						
						else //if player losed, display LOSE
						{
							numDisplay(0,'L',1,0);
							numDisplay(0,'0',2,0);
							numDisplay(0,'S',3,0);
							numDisplay(0,'E',4,0);							
						}	
						
					}


							//LED blinking for player win or loss
								if(gameState == 2) {
									numLED = redLEDFlash(numLED);
								} else if(gameState == 3) {
									numLED = flashLED(numLED);
								}	
					printf("%c%c%c\n",first,second,third);
			}
			
			//game initialization
			if(gameInit == 0) {
					if(delay == 30) {
							startGame(data.roll);
							gameInit = 1;
					} else {
							delay++;
					}				
			}


	
} //end while
	
	return 0;
}
