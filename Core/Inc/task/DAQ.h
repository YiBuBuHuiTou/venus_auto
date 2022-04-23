/*
 * DQA.h
 *
 *  Created on: 2022年3月8日
 *      Author: YiBuBuHuiTou
 */

#ifndef SRC_TASK_INF_DAQ_H_
#define SRC_TASK_INF_DAQ_H_


#include "BMP180.h"
#include "DHT20.h"

#include "io_cfg.h"
#include "i2c.h"


extern void DAQ_Init( void );
extern void DAQ( void );

#endif /* SRC_TASK_INF_DAQ_H_ */
