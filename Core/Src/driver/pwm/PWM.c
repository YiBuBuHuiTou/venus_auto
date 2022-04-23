/*
 * PWM.c
 *
 *  Created on: Apr 23, 2022
 *      Author: YiBuBuHuiTou
 */


#include "PWM.h"


void initPWM(TIM_HandleTypeDef* htim) {

	HAL_TIM_PWM_Start(htim, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(htim, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(htim, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(htim, TIM_CHANNEL_4);
	HAL_TIMEx_PWMN_Start(htim, TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Start(htim, TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Start(htim, TIM_CHANNEL_3);
	HAL_TIMEx_PWMN_Start(htim, TIM_CHANNEL_4);
}


void changeChannelConfig(TIM_HandleTypeDef* htim, unsigned char channel, TIM_OC_InitTypeDef* sConfigOC) {
	HAL_TIM_PWM_ConfigChannel(htim, sConfigOC, channel);
}

void changeGlobalConfig(TIM_HandleTypeDef* htim, TIM_HandleTypeDef* config) {


}

void changeDuty(TIM_HandleTypeDef* htim, unsigned char channel, unsigned int duty) {
	if (htim == NULL || duty == 0) {
		return;
	}

	switch( channel ) {

	case TIM_CHANNEL_1:
		htim->Instance->CCR1 = duty;
		//__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, duty);
		break;
	case TIM_CHANNEL_2:
		break;
	case TIM_CHANNEL_3:
		break;
	case TIM_CHANNEL_4:
		break;
	default:
		break;
	}
}

void testPWM(TIM_HandleTypeDef* htim, unsigned char channel) {
	for (int i = 0; i < 999; i++) {
		changeDuty(htim, channel, i);
		HAL_Delay(1000);
	}

}
