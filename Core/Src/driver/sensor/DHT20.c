/*
 * DHT20.c
 *
 *  Created on: Mar 15, 2022
 *      Author: YiBuBuHuiTou
 */


#include "DHT20.h"



I2C_HandleTypeDef hi2c;

unsigned char DHT20_read_status( void ) {

	// 读取状态字
	unsigned char dht11_status;

	HAL_I2C_Mem_Read(&hi2c, DHT20_READ_ADDR, DHT20_INIT_STATUS_CMD, I2C_MEMADD_SIZE_8BIT, &dht11_status, sizeof(dht11_status), 1);

	return dht11_status;
}

//CRC校验类型：CRC8/MAXIM
//多项式：X8+X5+X4+1
//Poly：0011 0001  0x31
//高位放到后面就变成 1000 1100 0x8c
//C现实代码：
uint8_t Calc_CRC8(uint8_t *message,uint8_t Num)
{
        uint8_t i;
        uint8_t byte;
        uint8_t crc=0xFF;
  for(byte=0; byte<Num; byte++)
  {
    crc^=(message[byte]);
    for(i=8;i>0;--i)
    {
      if(crc&0x80) crc=(crc<<1)^0x31;
      else crc=(crc<<1);
    }
  }
        return crc;
}

void DHT20_init( I2C_HandleTypeDef* i2c ) {

	unsigned char dht11_status;

	//等待500ms,待传感器稳定后采集数据
	osDelay(500);
	//设置i2c 总线
	hi2c = *i2c;

	dht11_status = DHT20_read_status();

	dht11_status &= 0x18;
	if ( dht11_status != 0x18 ){
		//需要初始化寄存器0x1B 0x1C 0x1E

	}

	osDelay(10);
}

void DHT20_read_data( float * rh, float * temp ){
	unsigned char meter[2] = {0x33, 0x00};
	unsigned char raw_data[7];
	unsigned char dht11_status;
	unsigned int raw_rh = 0;
	unsigned int raw_temp = 0;
	//发送测量命令
	HAL_I2C_Mem_Write(&hi2c, DHT20_WRITE_ADDR, DHT20_METER_CMD, I2C_MEMADD_SIZE_8BIT, meter, sizeof(meter), 1);

	osDelay(80);
	do{
		osDelay(20);
		dht11_status = DHT20_read_status();

	} while((dht11_status & 0x80) == 0x80 );

	HAL_I2C_Mem_Read(&hi2c, DHT20_READ_ADDR, DHT20_READ_DATA_CMD, I2C_MEMADD_SIZE_8BIT, raw_data, sizeof(raw_data), 1);

	if( Calc_CRC8 (raw_data, 6) == raw_data[6]) {
		raw_rh = (raw_rh|raw_data[1])<<8;
		raw_rh = (raw_rh|raw_data[2])<<8;
		raw_rh = (raw_rh|raw_data[3]);
		raw_rh = raw_rh >>4;
	    *rh = raw_rh *100*10/1024/1024;  //计算得到湿度值c1（放大了10倍）

		raw_temp = (raw_temp|raw_data[3])<<8;
		raw_temp = (raw_temp|raw_data[4])<<8;
		raw_temp = (raw_temp|raw_data[5]);
		raw_temp = raw_temp&0xfffff;
		*temp = raw_temp *200*10/1024/1024-500;//计算得到温度值t1（放大了10倍）
	} else {
		*rh = 0;
		*temp = 0;
	}

	osDelay(2000);
}


