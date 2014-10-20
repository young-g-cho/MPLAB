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
extern uint8_t buttonState;
char char_answer [4];

uint8_t numKeyPressed;
uint8_t chances;

float answer;

extern uint_fast16_t refresh;

void startGame (float angle) {
	
		answer = angle;
		first = '0';
		second = '0';
		third = '0';
		numKeyPressed = 0;
		chances = 3;
		gameState = 1;

	
}

void checkAnswer () {
		
		uint32_t guess = ((first -'0')*100 + (second-'0')*10 + (third -'0'));
	
		if((guess < (answer + 4))  && (guess > (answer - 4))) {
			//show correct answer(Game end state for player win)
			gameState = 3;
			showAnswer();
		} else if (guess < (answer - 4)) {
			// blue LED
			GPIO_ResetBits(GPIOD, GPIO_Pin_14);
			GPIO_SetBits(GPIOD, GPIO_Pin_15);
			isGameOver();
		} else {
			// red LED
			GPIO_ResetBits(GPIOD, GPIO_Pin_15);
			GPIO_SetBits(GPIOD, GPIO_Pin_14);
			isGameOver();
		}
}

void userInput () {
	
			keyState();
				
			uint8_t key = getKey();
				
			if(key != 0x0 && buttonState != KEY_STILL_PRESSED) {
				//key is non-alphanumeric
				if(key == 'A' || key == 'B' || key == 'C' || key == 'D' || key == '*' || key == '#')  {
					checkAnswer();
						
					if(gameState == 1) {
						first = '0';
						second = '0';
						third = '0';
						numKeyPressed = 0;
					}
						
				} else {
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

void showAnswer () {
	
		if(answer >= 100){
				first = answer / 100 + '0';
				answer = (uint16_t) answer % 100;
				second = answer / 10 + '0';
				answer = (uint16_t) answer % 10;
				third = answer + '0';
				decimal = 0;
		} else if( answer <100 && answer >= 10) {
				answer *= 10;
				first = answer / 100 + '0';
				answer = (uint16_t) answer % 100;
				second = answer / 10 + '0';
				answer = (uint16_t) answer % 10;
				third = answer + '0';
				decimal = 2;
		} else {
				answer *= 100;
				first = answer / 100 + '0';
				answer = (uint16_t) answer % 100;
				second = answer / 10 + '0';
				answer = (uint16_t) answer % 10;
				third = answer + '0';
				decimal = 1;
		}
		
}

void isGameOver () {
	
	chances--;
	
	if(chances == 0) {
			gameState = 2;
			GPIO_ResetBits(GPIOD, GPIO_Pin_14);
			GPIO_ResetBits(GPIOD, GPIO_Pin_15);
	}

}

void printAnswer(){
	
	//decompose float into three digits
	//convert from float to char array
	sprintf(char_answer,"%f",answer);

	
  //case with no decimals
	if (answer >= 100){
	
		if (refresh == 1)
			numDisplay(0,char_answer[0],1,1);
		else if (refresh == 2)
			numDisplay(0,char_answer[1],2,1);			
		else if (refresh == 3)
			numDisplay(0,char_answer[2],3,1);
		
	}
	//case with decimal on display 2
	else if (answer >= 10 && answer < 100){

		if (refresh == 1)
			numDisplay(0,char_answer[0],1,1);
		else if (refresh == 2)
			numDisplay(1,char_answer[1],2,1);			
		else if (refresh == 3)
			numDisplay(0,char_answer[3],3,1);
		
	}
	//case with decimal on display 
	else{
		
		if (refresh == 1)
			numDisplay(1,char_answer[0],1,1);
		else if (refresh == 2)
			numDisplay(0,char_answer[2],2,1);			
		else if (refresh == 3)
			numDisplay(0,char_answer[3],3,1);
		
	}
	
}




