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
			showAnswer();
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
*	@brief sets the number of button pressed of calls checkAnswer
*/
void userInput () {
	
			keyState(); //checks state of button
				
			uint8_t key = getKey(); //gets the actual button that was pressed
				
			if(key != 0x0 && buttonState != KEY_STILL_PRESSED) { //if the key is being pressed and key is not zero then 
				
<<<<<<< HEAD
				if(key == 'A' || key == 'B' || key == 'C' || key == 'D' || key == '*' || key == '#')  {//if key is non-alphanumeric, then compare with answer
=======
			if(key != 0x0) {
				//key is non-alphanumeric
				if(key == 'A' || key == 'B' || key == '*' || key == '#')  {
>>>>>>> origin/master
					checkAnswer();
						
					if(gameState == 1) {//since game is not over, reset and start again
						first = '0';
						second = '0';
						third = '0';
						numKeyPressed = 0;
					}
						
<<<<<<< HEAD
				} 
				
//				else if(key == '#'){											//this is the delete key if we want to put it in there
//					if(numKeyPressed >0){
//					numKeyPressed--;
//					}
//				}
				else {//this is where it sets the numbers into the variables for them
=======
				} else if(key == 'C') {
						first = '0';
						second = '0';
						third = '0';
						numKeyPressed =0;

				} else if ( key == 'D' ) {
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
					
				} else {
>>>>>>> origin/master
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
void showAnswer () {
	
		if(answer >= 100){													//if answer has three digits, set each digit to its corresponding character and set them 
				first = answer / 100 + '0';
				answer = (uint16_t) answer % 100;
				second = answer / 10 + '0';
				answer = (uint16_t) answer % 10;
				third = answer + '0';
				decimal = 0;
		} else if( answer <100 && answer >= 10) {		//if answer has two digits, set each digit to its corresponding character and set them with 1 decimal
				answer *= 10;
				first = answer / 100 + '0';
				answer = (uint16_t) answer % 100;
				second = answer / 10 + '0';
				answer = (uint16_t) answer % 10;
				third = answer + '0';
				decimal = 2;	
		} else {																		//if answer has 1 digits, set each digit to its corresponding character and set them with 2 decimal accuracy
				answer *= 100;
				first = answer / 100 + '0';
				answer = (uint16_t) answer % 100;
				second = answer / 10 + '0';
				answer = (uint16_t) answer % 10;
				third = answer + '0';
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
	
	//printf("answer: %f \n", answer);
	
}




