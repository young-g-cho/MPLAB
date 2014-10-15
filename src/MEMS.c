#include <lis302dl.h>


void memsInit() {
	LIS302DL_InitTypeDef   init;
	
	init.Power_Mode = LIS302DL_LOWPOWERMODE_ACTIVE;										/* Power-down/Active Mode */
	init.Output_DataRate = LIS302DL_DATARATE_100 ;																/* OUT data rate 100 Hz / 400 Hz */
	init.Axes_Enable = LIS302DL_XYZ_ENABLE;																					/* Axes enable */
	init.Full_Scale = LIS302DL_FULLSCALE_9_2;																					/* Full scale */
	
	LIS302DL_Init(&init);
	
}

	
//void LIS302DL_InterruptConfig(LIS302DL_InterruptConfigTypeDef *LIS302DL_IntConfigStruct)
//{
//  uint8_t ctrl = 0x00;
//  
//  /* Read CLICK_CFG register */
//  LIS302DL_Read(&ctrl, LIS302DL_CLICK_CFG_REG_ADDR, 1);
//  
//  /* Configure latch Interrupt request, click interrupts and double click interrupts */                   
//  ctrl = (uint8_t)(LIS302DL_IntConfigStruct->Latch_Request| \
//                   LIS302DL_IntConfigStruct->SingleClick_Axes | \
//                   LIS302DL_IntConfigStruct->DoubleClick_Axes);
//  
//  /* Write value to MEMS CLICK_CFG register */
//  LIS302DL_Write(&ctrl, LIS302DL_CLICK_CFG_REG_ADDR, 1);
//}



///* LIS302DL struct */
//typedef struct
//{
//  uint8_t Power_Mode;                         /* Power-down/Active Mode */
//  uint8_t Output_DataRate;                    /* OUT data rate 100 Hz / 400 Hz */
//  uint8_t Axes_Enable;                        /* Axes enable */
//  uint8_t Full_Scale;                         /* Full scale */
//  uint8_t Self_Test;                          /* Self test */
//}LIS302DL_InitTypeDef;


///* LIS302DL Interrupt struct */
///*typedef struct
//{
//  uint8_t Latch_Request;                      /* Latch interrupt request into CLICK_SRC register*/
//  uint8_t SingleClick_Axes;                   /* Single Click Axes Interrupts */
//  uint8_t DoubleClick_Axes;                   /* Double Click Axes Interrupts */ 
//}LIS302DL_InterruptConfigTypeDef;  


//#define LIS302DL_SPI_INT1_PIN              GPIO_Pin_0                  /* PE.00 */
//#define LIS302DL_SPI_INT1_GPIO_PORT        GPIOE                       /* GPIOE */
//#define LIS302DL_SPI_INT1_GPIO_CLK         RCC_AHB1Periph_GPIOE
//#define LIS302DL_SPI_INT1_EXTI_LINE        EXTI_Line0
//#define LIS302DL_SPI_INT1_EXTI_PORT_SOURCE EXTI_PortSourceGPIOE
//#define LIS302DL_SPI_INT1_EXTI_PIN_SOURCE  EXTI_PinSource0
//#define LIS302DL_SPI_INT1_EXTI_IRQn        EXTI0_IRQn 


//#define LIS302DL_LOWPOWERMODE_ACTIVE                      ((uint8_t)0x40)
//#define LIS302DL_DATARATE_100                             ((uint8_t)0x00)
//#define LIS302DL_XYZ_ENABLE                               ((uint8_t)0x07)
//#define LIS302DL_FULLSCALE_2_3                            ((uint8_t)0x00)
//#define LIS302DL_FULLSCALE_9_2                            ((uint8_t)0x20)