#ifndef __KEY_H_
#define __KEY_H_

#include <reg51.h>
#include <intrins.h>
//---重定义关键词---//
#ifndef u8
#define u8 unsigned char 
#endif

#ifndef u32 
#define	u32 unsigned int 
#endif




//--定义使用的IO口--//
sbit KEY1 = P1^0;
sbit KEY2 = P1^1;
sbit KEY3 = P1^2;
sbit KEY4 = P1^3;
sbit KEY5 = P1^4;
sbit KEY6 = P1^5;

//--声明全局函数--//

void Delay10ms();
u8 KeyScan();
#endif
	