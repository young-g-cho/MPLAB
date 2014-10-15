#include "stm32f4xx.h"                  //Device header
#include "stm32f4xx_conf.h"

void ext1Init() {
	
	EXTI_InitTypeDef init;

	init.EXTI_Line = ENABLE;
	init.EXTI_Mode = EXTI_Mode_Interrupt;
	init.EXTI_Trigger = EXTI_Trigger_Rising;
	init.EXTI_LineCmd = ENABLE;
	
	EXTI_Init(&init);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource1);
	
}

//typedef enum
//{
//  EXTI_Mode_Interrupt = 0x00,
//  EXTI_Mode_Event = 0x04
//}EXTIMode_TypeDef;
//typedef enum
//{
//  EXTI_Trigger_Rising = 0x08,
//  EXTI_Trigger_Falling = 0x0C,  
//  EXTI_Trigger_Rising_Falling = 0x10
//}EXTITrigger_TypeDef;

//void SYSCFG_EXTILineConfig(uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex)
//{
//  uint32_t tmp = 0x00;

//  /* Check the parameters */
//  assert_param(IS_EXTI_PORT_SOURCE(EXTI_PortSourceGPIOx));
//  assert_param(IS_EXTI_PIN_SOURCE(EXTI_PinSourcex));

//  tmp = ((uint32_t)0x0F) << (0x04 * (EXTI_PinSourcex & (uint8_t)0x03));
//  SYSCFG->EXTICR[EXTI_PinSourcex >> 0x02] &= ~tmp;
//  SYSCFG->EXTICR[EXTI_PinSourcex >> 0x02] |= (((uint32_t)EXTI_PortSourceGPIOx) << (0x04 * (EXTI_PinSourcex & (uint8_t)0x03)));
//}

//                ##### How to use this driver #####
// ===================================================================  
// 
// [..] In order to use an I/O pin as an external interrupt source, follow steps 
//      below:
//   (#) Configure the I/O in input mode using GPIO_Init()
//   (#) Select the input source pin for the EXTI line using SYSCFG_EXTILineConfig()
//   (#) Select the mode(interrupt, event) and configure the trigger 
//       selection (Rising, falling or both) using EXTI_Init()
//   (#) Configure NVIC IRQ channel mapped to the EXTI line using NVIC_Init()

// [..]     
//   (@) SYSCFG APB clock must be enabled to get write access to SYSCFG_EXTICRx
//       registers using RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);


//typedef struct
//{
//  uint32_t EXTI_Line;               /*!< Specifies the EXTI lines to be enabled or disabled.
//                                         This parameter can be any combination value of @ref EXTI_Lines */
//   
//  EXTIMode_TypeDef EXTI_Mode;       /*!< Specifies the mode for the EXTI lines.
//                                         This parameter can be a value of @ref EXTIMode_TypeDef */

//  EXTITrigger_TypeDef EXTI_Trigger; /*!< Specifies the trigger signal active edge for the EXTI lines.
//                                         This parameter can be a value of @ref EXTITrigger_TypeDef */

//  FunctionalState EXTI_LineCmd;     /*!< Specifies the new state of the selected EXTI lines.
//                                         This parameter can be set either to ENABLE or DISABLE */ 
//}EXTI_InitTypeDef;


//#define EXTI_Line0       ((uint32_t)0x00001)     /*!< External interrupt line 0 */
//#define EXTI_Line1       ((uint32_t)0x00002)     /*!< External interrupt line 1 */
//#define EXTI_Line2       ((uint32_t)0x00004)     /*!< External interrupt line 2 */
//#define EXTI_Line3       ((uint32_t)0x00008)     /*!< External interrupt line 3 */
//#define EXTI_Line4       ((uint32_t)0x00010)     /*!< External interrupt line 4 */
//#define EXTI_Line5       ((uint32_t)0x00020)     /*!< External interrupt line 5 */
//#define EXTI_Line6       ((uint32_t)0x00040)     /*!< External interrupt line 6 */
//#define EXTI_Line7       ((uint32_t)0x00080)     /*!< External interrupt line 7 */
//#define EXTI_Line8       ((uint32_t)0x00100)     /*!< External interrupt line 8 */
//#define EXTI_Line9       ((uint32_t)0x00200)     /*!< External interrupt line 9 */
//#define EXTI_Line10      ((uint32_t)0x00400)     /*!< External interrupt line 10 */
//#define EXTI_Line11      ((uint32_t)0x00800)     /*!< External interrupt line 11 */
//#define EXTI_Line12      ((uint32_t)0x01000)     /*!< External interrupt line 12 */
//#define EXTI_Line13      ((uint32_t)0x02000)     /*!< External interrupt line 13 */
//#define EXTI_Line14      ((uint32_t)0x04000)     /*!< External interrupt line 14 */
//#define EXTI_Line15      ((uint32_t)0x08000)     /*!< External interrupt line 15 */
//#define EXTI_Line16      ((uint32_t)0x10000)     /*!< External interrupt line 16 Connected to the PVD Output */
//#define EXTI_Line17      ((uint32_t)0x20000)     /*!< External interrupt line 17 Connected to the RTC Alarm event */
//#define EXTI_Line18      ((uint32_t)0x40000)     /*!< External interrupt line 18 Connected to the USB OTG FS Wakeup from suspend event */                                    
//#define EXTI_Line19      ((uint32_t)0x80000)     /*!< External interrupt line 19 Connected to the Ethernet Wakeup event */
//#define EXTI_Line20      ((uint32_t)0x00100000)  /*!< External interrupt line 20 Connected to the USB OTG HS (configured in FS) Wakeup event  */
//#define EXTI_Line21      ((uint32_t)0x00200000)  /*!< External interrupt line 21 Connected to the RTC Tamper and Time Stamp events */                                               
//#define EXTI_Line22      ((uint32_t)0x00400000)  /*!< External interrupt line 22 Connected to the RTC Wakeup event */                 


///*  Function used to set the EXTI configuration to the default reset state *****/
//void EXTI_DeInit(void);

///* Initialization and Configuration functions *********************************/
//void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct);
//void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct);
//void EXTI_GenerateSWInterrupt(uint32_t EXTI_Line);

///* Interrupts and flags management functions **********************************/
//FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_Line);
//void EXTI_ClearFlag(uint32_t EXTI_Line);
//ITStatus EXTI_GetITStatus(uint32_t EXTI_Line);
//void EXTI_ClearITPendingBit(uint32_t EXTI_Line);
