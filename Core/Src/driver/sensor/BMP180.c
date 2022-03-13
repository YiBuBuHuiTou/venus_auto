/*
 * BMP180.c
 *
 *  Created on: Mar 7, 2022
 *      Author: YiBuBuHuiTou
 */

/*
  * 工作电压 ：1.8v~3.6v
 * IIC
 *
 *
 *
 */

#include "BMP180.h"

#define EEPROM_START_ADDR   ( 0xAA )
#define EEPROM_END_ADDR     ( 0xBF )
#define BMP180_UT_REG_MSB   ( 0xF6 )
#define BMP180_UT_REG_LSB   ( 0xF7 )
#define BMP180_UP_REG_MSB   ( 0xF6 )
#define BMP180_UP_REG_LSB   ( 0xF7 )
#define BMP180_UP_REG_XLSB  ( 0xF8 )


static short int AC1;
static short int AC2;
static short int AC3;
static unsigned short int AC4;
static unsigned short int AC5;
static unsigned short int AC6;
static short int B1;
static short int B2;
static short int MB;
static short int MC;
static short int MD;
//功率模式
static unsigned char OSS;
//标准大气压
static double ATMOSPHERE = 101325.0F;
/*
 * 初始化BMP180（设定功率模式，获取EEP中的校准值，用来进行对温度和大气压进行温度补偿）
 */
void initBMP180( unsigned char oss ) {
	unsigned char cali[22];
	// 设定BMP180 功率
	OSS = oss;
	//读取EEP的值 设备地址0xEF
	HAL_I2C_Mem_Read(&hi2c2, 0xEF, EEPROM_START_ADDR,      I2C_MEMADD_SIZE_8BIT, cali, sizeof(cali), 1);
	AC1 = (signed short int)( (cali[0]<<8)+ cali[1] );
	AC2 = (signed short int)( (cali[2]<<8) + cali[3] );
	AC3 = (signed short int)( (cali[4]<<8) + cali[5] );
	AC4 = (cali[6]<<8) + cali[7];
	AC5 = (cali[8]<<8) + cali[9];
	AC6 = (cali[10]<<8) + cali[11];
	B1 =  (signed short int)( (cali[12]<<8) + cali[13] );
	B2 =  (signed short int)( (cali[14]<<8) + cali[15] );
	MB =  (signed short int)( (cali[16]<<8) + cali[17] );
	MC =  (signed short int)( (cali[18]<<8) + cali[19] );
	MD =  (signed short int)( (cali[20]<<8) + cali[21] );

}
/**
 * 读取未校准的温度值
 */
long readRawUT( void ) {
	unsigned char ut_uncomp[2];
	// 向设备F4写入0x2E
	unsigned char ut_temp = 0x2E;
	HAL_I2C_Mem_Write(&hi2c2, 0xEE, 0xF4, I2C_MEMADD_SIZE_8BIT, &ut_temp, sizeof(ut_temp), 1);
	osDelay(10);
	//读取温度
	HAL_I2C_Mem_Read(&hi2c2, 0xEF, 0xF6, I2C_MEMADD_SIZE_8BIT, ut_uncomp, sizeof(ut_uncomp), 1);

	return (long)((ut_uncomp[0] << 8) + ut_uncomp[1]);
}

/**
 * 读取未校准的大气压值
 */
long readRawUP( void ) {

	unsigned char up_uncomp[3];
	// 向设备F4写入0x34/0x74/0xB4/0xF4(控制采样率)
	unsigned char up_temp = 0xF4;
	HAL_I2C_Mem_Write(&hi2c2, 0xEE, 0xF4, I2C_MEMADD_SIZE_8BIT, &up_temp, sizeof(up_temp), 1);
	osDelay(50);
	//读取气压
	HAL_I2C_Mem_Read(&hi2c2, 0xEF, 0xF6, I2C_MEMADD_SIZE_8BIT, up_uncomp, sizeof(up_uncomp), 1);

	return (long)(((up_uncomp[0] << 16) + (up_uncomp[1] << 8) + up_uncomp[2]) >> (8 - OSS));
}


/**
 * 获取校准后的温度，大气压以及计算后的海拔
 */
void BMP180_readData( float* temperature, long* pressure, float* altitude ) {
	long x1, x2, x3, B3, B5, B6, B7, p;
	unsigned long B4;
	long ut_uncomp = readRawUT();
	long up_uncomp = readRawUP();

    /*
     * UT补正
     *X1 = (UT - AC6) * AC5 / 2^15
     *X2 = MC * 2^11 / (X1 + MD)
     *B5 = X1 + X2
     *T = (B5 + 8) / 2^4
     *temp in 0.1°C
     */
     x1 = (( ut_uncomp - AC6 ) * AC5) >> 15;
     x2 = (MC << 11) /( x1 + MD );
     B5 = x1 + x2;
     *temperature = ((B5 + 8) >> 4 ) * 0.1f;
     /*
      * UP补正
      * B6 = B5- 4000
      * X1 = (B2 * (B6 * B6 / 2^12 )) / 2^11
      * X2 = AC2 * B6 / 2^11
      * X3 = X1 + X2
      * B3 = ((AC1*4 + X3) << oss +2 ) /4
      * X1 = AC3*B6/2^13
      * X2 = (B1 * (B6 * B6 / 2^12 )) / 2^16
      * X3 = ((X1 + X2) + 2) / 2^2
      * B4 = AC4 * (unsigend long)(X3 + 32768) / 2^15
      * B7 = ((unsigned long)UP - B3) * (50000 >> oss )
      * if(B7 < 0x80000000) { p = (B7 * 2) / B4 }
      * else { p = (B7 / B4) * 2 }
      * X1 = (p / 2^8 ) * (p / 2^8 )
      * X1 = (X1 * 3038) / 2^16
      * X2 = (-7357 * p) / 2^16
      * UP = UP + (X1 + X2 + 3791) / 2^4
      */
      B6 = B5 - 4000;
      x1= (B2 * (B6 * B6 >> 12 )) >> 11;
      x2 = AC2 * B6 >> 11;
      x3 = x1 + x2;
      B3 = (((AC1*4 + x3) << OSS ) + 2 ) >> 2;
      x1 = AC3* B6 >> 13;
      x2 = (B1 * (B6 * B6 >> 12 )) >> 16;
      x3 = ((x1 + x2) + 2) >> 2;
      B4 = AC4 * (unsigned long)(x3 + 32768) >> 15;
      B7 = ((unsigned long)up_uncomp - B3) * (50000 >> OSS );
//      if(B7 < 0x80000000) {
//    	  p = (B7 * 2) / B4;
//      } else {
//    	  p = (B7 / B4) * 2;
//      }
//      x1 = (p >> 8 ) * (p >> 8 );
//      x1 = (x1 * 3038) >> 16;
//      x2 = (-7357 * p) >> 16;
  	if (B7 < 0x80000000)
  		p = (B7 * 2) / B4;
  	else
  		p = (B7 / B4) * 2;
  	x1 = (p / (1 << 8)) * (p / (1 << 8));
  	x1 = (x1 * 3038) / (1 << 16);
  	x2 = (-7357 * p) / (1 << 16);
  	//baro press 大气压
    *pressure = p + ((x1 + x2 + 3791) >> 4);
    // hight of sea level  海拔
  	*altitude = 44330 * ( 1 - pow( *pressure/ATMOSPHERE, 1.0F / 5.255F));
}


