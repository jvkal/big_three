//=显示器的定义
#include <reg52.h>
#define  DBPort P0		//LCD数据端口
sbit LcdRs		= P2^0;
sbit LcdRw		= P2^1;
sbit LcdEn  	= P2^2;
sbit Lcdbf      = P0^7;		//LCD忙标志 Busy Flag

void delay(unsigned int t)	 //延时
{    
	while(t--);
}

void  LCD_Wait(void)	//读忙状态
{
	LcdRs=0;
	LcdRw=1;
	LcdEn=1;
	delay(10);LcdEn=0;	//下降沿	
	while(Lcdbf)
	{
	  LcdEn=0;LcdEn=1;	 //仿真才需要此语句,实际硬件中不需要
	}			
} 

void LCD_Write(bit style, unsigned char input)	 //写数据1/命令0
{
	LcdRs=style;
	LcdRw=0;		
	DBPort=input;	
	LcdEn=1;
	delay(10);
	LcdEn=0;			
	LCD_Wait();	
}

void LCD_Initial(void)			  //初始化LCD
{
	LCD_Write(0,0x38);  		 //8位数据端口,2行显示,5*7点阵
	delay(300);
	LCD_Write(0,0x0c);           //显示模式
	LCD_Write(0,0x01);           //清屏
	LCD_Write(0,0x06);           //输入模式
}

void GotoXY(unsigned char x, unsigned char y)  //移动光标到指定位置
{
	if(y==0)	LCD_Write(0,0x80|x);
	if(y==1)    LCD_Write(0,0xc0|x);
}

void Print(unsigned char *str)	 //指定坐标输出字符串
{
	while(*str)  
		LCD_Write(1,*str++);
}


