#ifndef __EEPROM_H
#define __EEPROM_H

#include <reg51.h>
#include "intrins.h"



//---重定义关键词---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

//--定义使用的IO口--//
//万用板定义
//sbit I2C_SCL = P2^0;
//sbit I2C_SDA = P2^1;
//PCB板定义
sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;

//--声明全局变量--//

void I2C_Delay10us();
void I2C_Start();
void I2C_Stop();
uchar I2C_SendByte(uchar dat, uchar ack);
uchar I2C_ReadByte();
void At24c02Write(uchar addr,uchar dat);
uchar At24c02Read(uchar addr);

#endif