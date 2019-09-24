#ifndef __KEY_H_
#define __KEY_H_

#include <reg51.h>
#include <intrins.h>
//---�ض���ؼ���---//
#ifndef u8
#define u8 unsigned char 
#endif

#ifndef u32 
#define	u32 unsigned int 
#endif




//--����ʹ�õ�IO��--//
sbit KEY1 = P1^0;
sbit KEY2 = P1^1;
sbit KEY3 = P1^2;
sbit KEY4 = P1^3;
sbit KEY5 = P1^4;
sbit KEY6 = P1^5;

//--����ȫ�ֺ���--//

void Delay10ms();
u8 KeyScan();
#endif
	