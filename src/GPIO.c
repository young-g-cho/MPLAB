#include "stm32f4xx.h"                  //Device header
#include "stm32f4xx_conf.h"



void gpioInit() {
		// declare GPIO initializatio structure
		GPIO_InitTypeDef gpio_init_s;
	
		// enable GPIO clocks
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);												//for GPIO PE0
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);												//for EXTI line input
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);												//for LED
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);											//to get write access to SYSCFG_EXTICRx registers

		//  pins initialization
		gpio_init_s.GPIO_Pin = GPIO_Pin_0; // Select pin 0 from GPIOE (for interrupt signal)
		gpio_init_s.GPIO_Mode = GPIO_Mode_OUT; // Set as output
		gpio_init_s.GPIO_Speed = GPIO_Speed_100MHz; // Don't limit slew rate
		gpio_init_s.GPIO_OType = GPIO_OType_PP; // Push-pull
		gpio_init_s.GPIO_PuPd = GPIO_PuPd_NOPULL; // Not input, don't pull
		GPIO_Init(GPIOE,&gpio_init_s); //initialize GPIOE with the above parameters
	
		// LED output pins initialization
		gpio_init_s.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14 | GPIO_Pin_15; // select pins 12,13,14,15 from GPIOD (for LED output)
		GPIO_Init(GPIOD,&gpio_init_s); //initialize GPIOD with the above parameters
	
		//EXTI line
		gpio_init_s.GPIO_Pin = GPIO_Pin_1; // Select pin 1 from GPIOE (for interrupt signal)
		gpio_init_s.GPIO_Mode = GPIO_Mode_IN; // Set as input
		gpio_init_s.GPIO_PuPd = GPIO_PuPd_UP; // Not input, pull UP
		GPIO_Init(GPIOB,&gpio_init_s); //initialize GPIOE with the above parameters
}



//#define LIS302DL_SPI_INT1_PIN              GPIO_Pin_0                  /* PE.00 */
//#define LIS302DL_SPI_INT1_GPIO_PORT        GPIOE                       /* GPIOE */
//#define LIS302DL_SPI_INT1_GPIO_CLK         RCC_AHB1Periph_GPIOE
//#define LIS302DL_SPI_INT1_EXTI_LINE        EXTI_Line0
//#define LIS302DL_SPI_INT1_EXTI_PORT_SOURCE EXTI_PortSourceGPIOE
//#define LIS302DL_SPI_INT1_EXTI_PIN_SOURCE  EXTI_PinSource0
//#define LIS302DL_SPI_INT1_EXTI_IRQn        EXTI0_IRQn 