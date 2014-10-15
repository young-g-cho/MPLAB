#include <stdio.h>
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"
#include "mems.h"

int main(){
	
	while(1){
		uint8_t ctrl = 0x00;
		LIS302DL_Read(&ctrl, LIS302DL_CTRL_REG3_ADDR, 1);
	}
	
	return 0;
}


