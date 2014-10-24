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

uint8_t first;  //variable for first digit
uint8_t second; //variable for second digit
uint8_t third;  //variable for third digit
uint8_t decimal = 0;
uint8_t gameState;    //1 for playing, 2 for gameOver(player loss) 3 for gameOver(player Win)
uint8_t numLED = 0;				//LED tracker
uint8_t chances;
uint8_t gameInit = 0;
uint8_t delay =0;
uint8_t clickDetection = 1;


MovingAverageFilter x;
MovingAverageFilter y;
MovingAverageFilter z;


void gameSet();
void gameReset();

/**
*	@brief initialize everything and play the game!!
*	@retval returns 0
*/

int main(){
	
	
		//initializes
		initForGpio ();
		initMems ();
		initAccelerometerDataReady ();
		//initAccelerometerDoubleClick ();
		intiEXTI0AndNVIC () ;
		initDisplay () ;
		initKeypad ();
		intiTIMAndNVIC ();
		initLED ();

		
		initFilter(&x);
		initFilter(&y);
		initFilter(&z);
		

		while(1){
			
				if(tick) {//when ticked get the data, add to filter, convert to angles
					
					//detecting click interrupt
					if(clickDetection == 0)
						clickDetection = 1;
					
					delay++;
					tick = 0;
					data = getReading();
					
					filterAdd(&x,data.x);
					filterAdd(&y,data.y);
					filterAdd(&z,data.z);
					toAngles(&data, x.average, y.average, z.average);
					
					//printf("x = %d\n",x.average);
					//printf("y = %d\n",y.average);
					//printf("z = %d\n",z.average);
					//printf("roll = %f\n",data.roll);
					//printf("pitch = %f\n",data.pitch);
					
					//if game is OVER then change to click interrupt. Once interrupt detected reinitialize the game
					if(gameState > 1) {
							
							if(gameInit == 1){
									initAccelerometerDoubleClick ();
									clickDetection = 0;
									gameInit = 0;
							}
							gameReset();
					}
				
				}	
			//shows the angle in 7segment display(angles need to be hard coded
		//		showAnswer(data.roll);
		//		printAnswer();
			

				if (gameState == 1) { //game is currently being played
							
						if(refresh  >0){
							userInput(); //wait for user input
						}		
						//update screen if game is not over set the desired numbers to the display
							if(refresh == 1) {
										numDisplay (decimal, first, 1,1);
							} else if(refresh == 2) {
										numDisplay (decimal, second,2,1);
							} else if(refresh == 3) {
										numDisplay (decimal, third, 3,1);
							} else if(refresh == 4) {
										numDisplay (decimal, chances + '0', 4,1);
							}
							
				} else {
						//resets the LED
						resetLED();
					
						if (gameState == 3)	{// if player won the game
								printAnswer();
								greenLEDFlash(refresh);
						}else if (gameState == 2)	{//if player lose, display LOSE
									redLEDFlash(refresh);
									if (refresh == 1)
											numDisplay(0,'L',1,0);
									else if (refresh == 2)
											numDisplay(0,'0',2,0);
									else if (refresh == 3)
											numDisplay(0,'5',3,0);
									else 
											numDisplay(0,'E',4,0);		
											
						} else {
									gameSet();
						}
				}
			//
			}
			return 0;
}

/**
*	@brief Starts the game by initializing game valuables
*/
void gameSet() {
		//game initialization
		if(gameInit == 0) {
				if(delay ==100) {
						startGame(data.roll);
						gameInit = 1;
						delay = 0;
				} 
		}
}

/**
*	@brief Restarts the game by chainging interrupt to data ready
*/
void gameReset() {
									
	//game Reset
	if(gameInit == 0) {
			
			if(clickDetection) {
					initAccelerometerDataReady();
					gameState = 0;
					decimal = 0;
			}		
			
	}
}
