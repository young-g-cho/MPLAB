#include <stdint.h>

#define X_OFFSET 34
#define Y_OFFSET -16
#define Z_OFFSET -108
#define PI 3.14159265359

typedef struct {
	
	int32_t x;
	int32_t y;
	int32_t z;
	float roll;
	float pitch;
} memsReading;



void initForGpio ();
void initAccelerometer ();
void intiEXTI0AndNVIC () ;
void EXTI0_IRQHandler ();
memsReading getReading ();
void toAngles(memsReading *data, int32_t x, int32_t y, int32_t z);
