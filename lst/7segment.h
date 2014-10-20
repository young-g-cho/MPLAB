#include <stdint.h>



void initDisplay () ;
void displayNum ();
void intiTIMAndNVIC ();
void TIM3_IRQHandler ();
void numDisplay (uint8_t mode, uint8_t digit, uint8_t updateLocation, uint8_t degree_on);

