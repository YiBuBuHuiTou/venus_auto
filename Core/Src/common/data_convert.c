/*
 * data_convert.c
 *
 *  Created on: 2022年3月13日
 *      Author: YiBuBuHuiTou
 */


void float2char(float* src, unsigned char* dst) {
	int temp = *src * 1000;
	dst[0] = ( unsigned char)((temp && 0xFF000000) >> 24);
	dst[1] = ( unsigned char)((temp && 0x00FF0000) >> 16);
	dst[2] = ( unsigned char)((temp && 0x0000FF00) >> 8);
	dst[3] = ( unsigned char)(temp && 0x000000FF);
}

void int2char(int* src, unsigned char* dst) {
	dst[0] = ( unsigned char)((*src && 0xFF000000) >> 24);
	dst[1] = ( unsigned char)((*src && 0x00FF0000) >> 16);
	dst[2] = ( unsigned char)((*src && 0x0000FF00) >> 8);
	dst[3] = ( unsigned char)(*src && 0x000000FF);
}
