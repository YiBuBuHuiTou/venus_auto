/*
 * PWM.h
 *
 *  Created on: Apr 23, 2022
 *      Author: YiBuBuHuiTou
 */

#ifndef INC_DRIVER_PWM_PWM_H_
#define INC_DRIVER_PWM_PWM_H_

#include "main.h"
#include "cmsis_os.h"
#include "tim.h"

extern void initPWM(TIM_HandleTypeDef* htim);
extern void changeChannelConfig(TIM_HandleTypeDef* htim, unsigned char channel, TIM_OC_InitTypeDef* sConfigOC);
extern void changeGlobalConfig(TIM_HandleTypeDef* htim, TIM_HandleTypeDef* config);
extern void changeDuty(TIM_HandleTypeDef* htim, unsigned char channel, unsigned int duty);
extern void testPWM(TIM_HandleTypeDef* htim, unsigned char channel);


#endif /* INC_DRIVER_PWM_PWM_H_ */
