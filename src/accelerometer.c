#include "stm32f4xx.h"                  //Device header
#include "stm32f4xx_conf.h"
#include "accelerometer.h"
#include <lis302dl.h>
#include <Math.h>

extern uint_fast16_t tick;
/**
*	@brief initialize the GPIOE with periph clocks
*/
void initForGpio () {

	GPIO_InitTypeDef gpio_init_s;
	
	// enable GPIO clocks
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);			//for GPIO PE0
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);			//for EXTI line input
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);		//to get write access to SYSCFG_EXTICRx registers

	// MEMS interrupt pins initialization
	gpio_init_s.GPIO_Pin = GPIO_Pin_0; 												// Select pin 0 from GPIOE (for interrupt signal)
	gpio_init_s.GPIO_Mode = GPIO_Mode_IN; 										// Set as input
	gpio_init_s.GPIO_Speed = GPIO_Speed_100MHz;								// Don't limit slew rate
	gpio_init_s.GPIO_OType = GPIO_OType_OD; 									// Open Drain
	gpio_init_s.GPIO_PuPd = GPIO_PuPd_NOPULL; 								// Not input, don't pull
	GPIO_Init(GPIOE,&gpio_init_s); 														//initialize GPIOE with the above parameters
	
}
/**
*	@brief initialize the Accelerometer
*/

void initAccelerometer () {
	
	uint8_t ctrl;
	LIS302DL_InitTypeDef init;

	
	init.Power_Mode = LIS302DL_LOWPOWERMODE_ACTIVE;							/*Mode */
	init.Output_DataRate = LIS302DL_DATARATE_100 ;							/* OUT data rate 100 Hz*/
	init.Axes_Enable = LIS302DL_XYZ_ENABLE;											/* Axes enable */
	init.Full_Scale = LIS302DL_FULLSCALE_2_3;										/* Full scale */
	init.Self_Test = LIS302DL_SELFTEST_NORMAL;									/* self test */
	LIS302DL_Init(&init);
	
	//enable data-ready interrupt
	ctrl = 0x04;
	LIS302DL_Write(&ctrl, LIS302DL_CTRL_REG3_ADDR, 1); //send 4 to the SPI ??????????????????????

}
/**
*	@brief initialize the EXTI0 and the the NVIC for it
*/
void intiEXTI0AndNVIC () {
	
	//create variables
	EXTI_InitTypeDef initEXTI0;
	NVIC_InitTypeDef initNVIC;
	
	
	initEXTI0.EXTI_Line = EXTI_Line0; 								//set external interrupt line to 0
	initEXTI0.EXTI_Mode = EXTI_Mode_Interrupt;				//set it to ba an interrupt
	initEXTI0.EXTI_Trigger = EXTI_Trigger_Rising;			//set to rising as when rising because we care when trigger goes to 1 ??????????????????????????????
	initEXTI0.EXTI_LineCmd = ENABLE;									//enable line
	
	EXTI_Init(&initEXTI0); 														//initialize EXTI0
	
	//sets GPIO for EXTI0 line 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource0);
	
	initNVIC.NVIC_IRQChannel = EXTI0_IRQn ; 				//set channel to the exti0 that we initialized
	initNVIC.NVIC_IRQChannelPreemptionPriority = 0;	//set to highest priority
	initNVIC.NVIC_IRQChannelSubPriority = 0;				//when needs to wait, set still as highest priority
	initNVIC.NVIC_IRQChannelCmd = ENABLE;						//enable channel
	
	NVIC_Init(&initNVIC); 													//initialize NVIC
	
}
/**
*	@brief handles when external interrupt happens
*/
void EXTI0_IRQHandler () {
	
	tick  = 1;
	EXTI_ClearFlag(LIS302DL_SPI_INT1_EXTI_LINE);//reset the interrupt flag ???????????????
}
/**
*	@brief  initialize the EXTI0 and the the NVIC for it
*	@retval returns the data structure with values for x, y and z
*/
memsReading getReading() {
	uint8_t Buffer[6];
	memsReading data;

	LIS302DL_Read(Buffer, 0x29, 6); //read 6 bytes of data from LIS302DL and put in buffer
	
	//set x,y,z values for data using equation with predetermined offsets
	data.x = (int8_t)(Buffer[0]) * 18 - X_OFFSET; 
	data.y = (int8_t)(Buffer[2]) * 18 - Y_OFFSET;
	data.z = (int8_t)(Buffer[4]) * 18 - Z_OFFSET;
	
	return data;
	
}
/**
*	@brief	determines the pitch and roll of data
*	@param	data: address of a data structure
*	@param	x: value on the x plane
*	@param	y: value on the y plane
*	@param	z: value on the z plane
*/
void toAngles(memsReading *data, int32_t x, int32_t y, int32_t z) {
	
	data->pitch = 90 + atan(x / (sqrt(y*y+z*z)))*(180/PI);
	data->roll = 90 + atan(y / (sqrt(x*x+z*z)))*(180/PI);
	
}
