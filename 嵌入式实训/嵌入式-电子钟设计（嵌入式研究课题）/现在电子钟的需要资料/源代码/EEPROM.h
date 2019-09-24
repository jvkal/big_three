#ifndef __EEPROM_H
#define __EEPROM_H

#include <reg51.h>
#include "intrins.h"



//---�ض���ؼ���---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

//--����ʹ�õ�IO��--//
//���ð嶨��
//sbit I2C_SCL = P2^0;
//sbit I2C_SDA = P2^1;
//PCB�嶨��
sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;

//--����ȫ�ֱ���--//

void I2C_Delay10us();
void I2C_Start();
void I2C_Stop();
uchar I2C_SendByte(uchar dat, uchar ack);
uchar I2C_ReadByte();
void At24c02Write(uchar addr,uchar dat);
uchar At24c02Read(uchar addr);

#endif