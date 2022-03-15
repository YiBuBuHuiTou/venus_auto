/*
 * DHT20.h
 *
 *  Created on: Mar 15, 2022
 *      Author: YiBuBuHuiTou
 */

#ifndef INC_DRIVER_SENSOR_DHT20_H_
#define INC_DRIVER_SENSOR_DHT20_H_

#include "main.h"
#include "cmsis_os.h"
#include "io_cfg.h"
#include "i2c.h"
#include "io_cfg.h"


// DHT20 读/写设备地址
#define DHT20_READ_ADDR   ( 0x39 )
#define DHT20_WRITE_ADDR  ( 0x38 )
// DHT20 初始化状态取得命令
#define DHT20_INIT_STATUS_CMD ( 0x71 )
// DHT20 测量命令
#define DHT20_METER_CMD    ( 0xAC )
// DHT20 数据取得命令
#define DHT20_READ_DATA_CMD ( 0x71 )



extern void DHT20_init( I2C_HandleTypeDef* i2c );
extern void DHT20_read_data( float * rh, float * temp );


#endif /* INC_DRIVER_SENSOR_DHT20_H_ */
