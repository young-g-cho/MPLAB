#include <stdint.h>

#define ZERO 0x28
#define ONE 0x11
#define TWO 0x21
#define THREE 0x41
#define FOUR 0x12
#define FIVE 0x22
#define SIX 0x42
#define SEVEN 0x14
#define EIGHT 0x24
#define NINE 0x44
#define LETTER_A 0x81
#define LETTER_B 0x82
#define LETTER_C 0x84
#define LETTER_D 0x88
#define STAR 0x18
#define SHARP 0x48


#define KEY_RELEASED 0
#define KEY_PRESSED 1
#define KEY_STILL_PRESSED 2

void initKeypad ();
void rowAsInput () ;
void keyState();
void searchColumn();
void searchRow();
uint8_t getKey();
void debounce();
