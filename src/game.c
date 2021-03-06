#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "stm32f4xx.h"                  // Device header
#include "game.h"
#include "keypad.h"
#include "7segment.h"

extern uint8_t first;
extern uint8_t second;
extern uint8_t third;
extern uint8_t decimal;
extern uint8_t gameState;
extern uint8_t chances;

uint8_t numKeyPressed;

float answer;

extern uint_fast16_t refresh;


/**
*	@brief initializes the game
*/
void startGame (float angle) {
	
		answer = angle;
		first = '0';
		second = '0';
		third = '0';
		numKeyPressed = 0;
		chances = NUMBER_OF_CHANCES;
		gameState = 1;

}

/**
*	@brief compare user's input to correct angle
*/
void checkAnswer () {
		
		uint32_t guess = ((first -'0')*100 + (second-'0')*10 + (third -'0')); //convert each digit to integer (-'0') and add together to get the actual guessed number
	
		if((guess < (answer + 4))  && (guess > (answer - 4))) {//if guess in with 4 of answer, then 
			//show correct answer(Game end state for player win)
			gameState = 3;
			showAnswer(answer);
		} else if (guess < (answer - 4)) {//if guess is less by more than 4, then set blue LED and check if game is over
			// blue LED
			GPIO_ResetBits(GPIOD, GPIO_Pin_14);
			GPIO_SetBits(GPIOD, GPIO_Pin_15);
			isGameOver();
		} else {													//if guess is higher by more than 4, then set red LED and check if game is over
			// red LED
			GPIO_ResetBits(GPIOD, GPIO_Pin_15);
			GPIO_SetBits(GPIOD, GPIO_Pin_14);
			isGameOver();
		}
}
/**
*	@brief checks the useinput and calls checkAnswer
*/
void userInput () {
	
			keyState(); //checks state of button
				
			uint8_t key = getKey(); //gets the actual button that was pressed

			if(key != 0x0) {// key is being pressed
				//key is non-alphanumeric
				if(key == 'A' || key == 'B' || key == '*' || key == '#')  {

					checkAnswer();
						
					if(gameState == 1) {//since game is not over, reset and start again
						first = '0';
						second = '0';
						third = '0';
						numKeyPressed = 0;
					}

				} else if(key == 'C') { //clear the all the button that has been pressed for current chance
						first = '0';
						second = '0';
						third = '0';
						numKeyPressed =0;

				} else if ( key == 'D' ) { //deletes the previouse button pressed
					if(third != '0' && second == '0' && first == '0') {
							third = '0';
					} else if(second != '0' && first == '0') {
							third = second;
							second = '0';
					} else if(first != '0') {
							third = second;
							second = first;
							first = '0';
					}
					
					numKeyPressed--;
					
				} else {	//updates the number that has been pressed by the user
						if(numKeyPressed == 0) {
								third = key;
								numKeyPressed++;
						} else if (numKeyPressed == 1) {
								second = third;
								third = key;
								numKeyPressed++;
						} else if  (numKeyPressed == 2) {
							first  = second;
							second = third;
							third = key;
							numKeyPressed++;
					}
				}
			}
}
/**
*	@brief displays the correct angle
*/
void showAnswer (float angle) {
	
		if(angle >= 100){													//if answer has three digits, set each digit to its corresponding character and set them 
				first = angle / 100 + '0';
				angle = (uint16_t) angle % 100;
				second = angle / 10 + '0';
				angle = (uint16_t) angle % 10;
				third = angle + '0';
				decimal = 0;
		} else if( angle <100 && angle >= 10) {		//if answer has two digits, set each digit to its corresponding character and set them with 1 decimal
				angle *= 10;
				first = angle / 100 + '0';
				angle = (uint16_t) angle % 100;
				second = angle / 10 + '0';
				angle = (uint16_t) angle % 10;
				third = angle + '0';
				decimal = 2;	
		} else {																		//if answer has 1 digits, set each digit to its corresponding character and set them with 2 decimal accuracy
				angle *= 100;
				first = angle / 100 + '0';
				angle = (uint16_t) angle % 100;
				second = angle / 10 + '0';
				angle = (uint16_t) angle % 10;
				third = angle + '0';
				decimal = 1;
		}
		
}
/**
*	@brief checks if game is over
*/
void isGameOver () {
	
	chances--; // decrement how many chances player has
	
	if(chances == 0) { //if no more chances, game is over and turn over LEDs
			gameState = 2;
			GPIO_ResetBits(GPIOD, GPIO_Pin_14);
			GPIO_ResetBits(GPIOD, GPIO_Pin_15);
	}

}

void printAnswer(){
	
	//print out answer values to display
	if (refresh == 1)
		numDisplay(decimal,first,1,1);
	else if (refresh == 2)
		numDisplay(decimal, second, 2,1);
	else if (refresh == 3)
		numDisplay(decimal, third, 3, 1);
	
}
