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
#include "io_cfg.h"

enum BMP180_OSS{
	BMP180_LOW,
	BMP180_STANDARD,
	BMP180_HIGH,
	BMP180_ULTRA
};

#define EEPROM_START_ADDR   ( 0xAA )
#define EEPROM_END_ADDR     ( 0xBF )
#define BMP180_UT_REG_MSB   ( 0xF6 )
#define BMP180_UT_REG_LSB   ( 0xF7 )
#define BMP180_UP_REG_MSB   ( 0xF6 )
#define BMP180_UP_REG_LSB   ( 0xF7 )
#define BMP180_UP_REG_XLSB  ( 0xF8 )

extern void initBMP180(I2C_HandleTypeDef* i2c, unsigned char oss );
extern void BMP180_readData( float* temperate, long* pressure, float* altitude );
#endif /* SRC_DRIVER_SENSOR_INF_BMP180_H_ */
