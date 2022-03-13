/*
 * DAQ.c
 *
 *  Created on: 2022年3月8日
 *      Author: YiBuBuHuiTou
 */
#include "BMP180.h"

#include "io_cfg.h"
#include "i2c.h"
void DAQ_Init( void ) {
	//设置BMP功率，并且从EEPROM中读取相关标定
	initBMP180(BMP180_ULTRA);
}

void DAQ( void ) {
	float temperature, altitude;
	long pressure;
	BMP180_readData( &temperature, &pressure, &altitude);

}
