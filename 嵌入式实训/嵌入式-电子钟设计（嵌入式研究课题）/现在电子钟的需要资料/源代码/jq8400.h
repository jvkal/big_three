#ifndef __JQ8400_H_
#define __JQ8400_H_



//---重定义关键词---//
#ifndef u8
#define u8 unsigned char 
#endif

#ifndef u32 
#define	u32 unsigned int 
#endif

#include <reg51.h>

sbit sda = P2^0;


void JQ8400_SendData(u8 addr);

#endif
	