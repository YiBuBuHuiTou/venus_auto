/*
 * OSConfig.c
 *
 *  Created on: Apr 23, 2022
 *      Author: YiBuBuHuiTou
 */


#include "OSConfig.h"
#include "stdio.h"
void OS_Config_Init( void ){
	initPWM(&htim3);
}

void OS_Config( void ) {
	testPWM(&htim3, TIM_CHANNEL_1);
	printf("duty = %d", htim3.Instance->CCR1);
}



