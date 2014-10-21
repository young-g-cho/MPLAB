#include "stm32f4xx.h"                  //Device header
#include "stm32f4xx_conf.h"
#include "accelerometer.h"
#include <lis302dl.h>
#include <Math.h>
#include <stdio.h>

extern uint_fast16_t tick;

void initForGpio () {

	GPIO_InitTypeDef gpio_init_s;
	
	
	// enable GPIO clocks
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);												//for GPIO PE0
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);												//for EXTI line input
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);											//to get write access to SYSCFG_EXTICRx registers

	// MEMS interrupt pins initialization
	gpio_init_s.GPIO_Pin = GPIO_Pin_0; // Select pin 0 from GPIOE (for interrupt signal)
	gpio_init_s.GPIO_Mode = GPIO_Mode_IN; // Set as input
	gpio_init_s.GPIO_Speed = GPIO_Speed_100MHz; // Don't limit slew rate
	gpio_init_s.GPIO_OType = GPIO_OType_OD; // Open Drain
	gpio_init_s.GPIO_PuPd = GPIO_PuPd_NOPULL; // Not input, don't pull
	GPIO_Init(GPIOE,&gpio_init_s); //initialize GPIOE with the above parameters
	
}

void initAccelerometer () {
	
	uint8_t ctrl;
	LIS302DL_InitTypeDef init;

	
	init.Power_Mode = LIS302DL_LOWPOWERMODE_ACTIVE;										/*Mode */
	init.Output_DataRate = LIS302DL_DATARATE_100 ;																/* OUT data rate 100 Hz*/
	init.Axes_Enable = LIS302DL_XYZ_ENABLE;																					/* Axes enable */
	init.Full_Scale = LIS302DL_FULLSCALE_2_3;																					/* Full scale */
	init.Self_Test = LIS302DL_SELFTEST_NORMAL;																			/* self test */
	LIS302DL_Init(&init);
	
	//enable data-ready interrupt
	ctrl = 0x04;
	LIS302DL_Write(&ctrl, LIS302DL_CTRL_REG3_ADDR, 1);

}

void intiEXTI0AndNVIC () {
	
	EXTI_InitTypeDef initEXTI0;
	NVIC_InitTypeDef initNVIC;
	
	
	initEXTI0.EXTI_Line = EXTI_Line0;
	initEXTI0.EXTI_Mode = EXTI_Mode_Interrupt;
	initEXTI0.EXTI_Trigger = EXTI_Trigger_Rising;
	initEXTI0.EXTI_LineCmd = ENABLE;
	
	EXTI_Init(&initEXTI0);
	
	//sets GPIO for EXTI0 line 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource0);
	
	initNVIC.NVIC_IRQChannel = EXTI0_IRQn ;
	initNVIC.NVIC_IRQChannelPreemptionPriority = 0;
	initNVIC.NVIC_IRQChannelSubPriority = 0;
	initNVIC.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&initNVIC);
	
}

void EXTI0_IRQHandler () {
	
	tick  = 1;
	EXTI_ClearFlag(LIS302DL_SPI_INT1_EXTI_LINE);
}

memsReading getReading() {
	
	int32_t buffer[3];
	memsReading data;

	LIS302DL_ReadACC(buffer);
	
	int32_t x_r = buffer[1];
	int32_t y_r = buffer[0];
	int32_t z_r = buffer[2];	
	
	
	
	data.x = 0.9719*x_r + 0.0034*y_r - 0.0034*z_r + 33.9648;
	data.y = 0.0041*x_r + 1.0221*y_r + 0.0125*z_r - 37.6956;
	data.z = 0.0102*x_r + 0.0219*y_r + 0.9619*z_r + 115.2684;

	
	return data;
	
}

void toAngles(memsReading *data, int32_t x, int32_t y, int32_t z) {
	
	data->pitch = 90 + atan(x / (sqrt(y*y+z*z)))*(180/PI);
	data->roll = 90 + atan(y / (sqrt(x*x+z*z)))*(180/PI);
	
	//printf("pitch : %f, roll: %f \n", data->pitch, data->roll);
	
}
