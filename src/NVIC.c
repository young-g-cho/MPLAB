#include "stm32f4xx.h"                  //Device header
#include "stm32f4xx_conf.h"

void nvicInit() {
	NVIC_InitTypeDef init;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	init.NVIC_IRQChannel = EXTI0_IRQn ;
	init.NVIC_IRQChannelPreemptionPriority = 0;
	init.NVIC_IRQChannelSubPriority = 0;
	init.NVIC_IRQChannelCmd = ENABLE;
	
	
	//SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource);
}



//void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup);


//typedef struct
//{
//  uint8_t NVIC_IRQChannel;                    /*!< Specifies the IRQ channel to be enabled or disabled.
//                                                   This parameter can be an enumerator of @ref IRQn_Type 
//                                                   enumeration (For the complete STM32 Devices IRQ Channels
//                                                   list, please refer to stm32f4xx.h file) */

//  uint8_t NVIC_IRQChannelPreemptionPriority;  /*!< Specifies the pre-emption priority for the IRQ channel
//                                                   specified in NVIC_IRQChannel. This parameter can be a value
//                                                   between 0 and 15 as described in the table @ref MISC_NVIC_Priority_Table
//                                                   A lower priority value indicates a higher priority */

//  uint8_t NVIC_IRQChannelSubPriority;         /*!< Specifies the subpriority level for the IRQ channel specified
//                                                   in NVIC_IRQChannel. This parameter can be a value
//                                                   between 0 and 15 as described in the table @ref MISC_NVIC_Priority_Table
//                                                   A lower priority value indicates a higher priority */

//  FunctionalState NVIC_IRQChannelCmd;         /*!< Specifies whether the IRQ channel defined in NVIC_IRQChannel
//                                                   will be enabled or disabled. 
//                                                   This parameter can be set either to ENABLE or DISABLE */   
//} NVIC_InitTypeDef;



//#define NVIC_PriorityGroup_0         ((uint32_t)0x700) /*!< 0 bits for pre-emption priority
//                                                            4 bits for subpriority */
//#define NVIC_PriorityGroup_1         ((uint32_t)0x600) /*!< 1 bits for pre-emption priority
//                                                            3 bits for subpriority */
//#define NVIC_PriorityGroup_2         ((uint32_t)0x500) /*!< 2 bits for pre-emption priority
//                                                            2 bits for subpriority */
//#define NVIC_PriorityGroup_3         ((uint32_t)0x400) /*!< 3 bits for pre-emption priority
//                                                            1 bits for subpriority */
//#define NVIC_PriorityGroup_4         ((uint32_t)0x300) /*!< 4 bits for pre-emption priority
//                                                            0 bits for subpriority */

//#define IS_NVIC_PRIORITY_GROUP(GROUP) (((GROUP) == NVIC_PriorityGroup_0) || \
//                                       ((GROUP) == NVIC_PriorityGroup_1) || \
//                                       ((GROUP) == NVIC_PriorityGroup_2) || \
//                                       ((GROUP) == NVIC_PriorityGroup_3) || \
//                                       ((GROUP) == NVIC_PriorityGroup_4))

//#define IS_NVIC_PREEMPTION_PRIORITY(PRIORITY)  ((PRIORITY) < 0x10)

//#define IS_NVIC_SUB_PRIORITY(PRIORITY)  ((PRIORITY) < 0x10)

//#define IS_NVIC_OFFSET(OFFSET)  ((OFFSET) < 0x000FFFFF)



//void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup);
//void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct);
//void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset);
//void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState NewState);
//void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource);