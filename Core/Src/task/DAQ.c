/*
 * DAQ.c
 *
 *  Created on: 2022年3月8日
 *      Author: YiBuBuHuiTou
 */

#include "DAQ.h"
void DAQ_Init( void ) {
	//设置BMP功率，并且从EEPROM中读取相关标定
	initBMP180(&hi2c2, BMP180_ULTRA);
//	DHT20_init(&hi2c1);
}

void DAQ( void ) {
	float temperature, altitude;
	long pressure;
	BMP180_readData( &temperature, &pressure, &altitude);

//	float rh, temp;
//	DHT20_read_data(&rh, &temp);
}
