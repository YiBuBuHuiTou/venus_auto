/*
 * BMP180.h
 *
 *  Created on: 2022年3月8日
 *      Author: YiBuBuHuiTou
 */

#ifndef SRC_DRIVER_SENSOR_INF_BMP180_H_
#define SRC_DRIVER_SENSOR_INF_BMP180_H_

#include "main.h"
#include "cmsis_os.h"
#include "io_cfg.h"
#include "i2c.h"
#include "math.h"

enum BMP180_OSS{
	BMP180_LOW,
	BMP180_STANDARD,
	BMP180_HIGH,
	BMP180_ULTRA
};

extern void initBMP180( unsigned char oss );
extern void BMP180_readData( float* temperate, long* pressure, float* altitude );
#endif /* SRC_DRIVER_SENSOR_INF_BMP180_H_ */
