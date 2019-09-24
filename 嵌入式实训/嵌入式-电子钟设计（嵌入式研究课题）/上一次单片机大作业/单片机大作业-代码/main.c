#include "config.h"
#include <reg52.h>
sbit act = P3^2;
//初始化信息
void init_sys(void)
{	    
	int i =0;
	//TMOD是定时器0和1的8位寄存器，0X01是指定时器0设置为1工作方式	
	TMOD=0x01;
	//5000表示需要定时器定时一次需要计数的个数，晶振为12M时程序在这里大约延时50毫秒
	//商存入高8位寄存器后余下的数存入低8位即可
	TH0=(65536-50000)/256; //50ms
	TL0=(65536-50000)%256;
	//CPU开启中断  								
    EA=1;ET0=1; 
	//定时中断0的优先度置为1
	PT0=1;
	//启动定时器0     											
    TR0=1;
	spk_deep_init();
}

void main()
{
	LCD_Initial();						 //lcd显示器初始化
	init_sys();
	act=1;							 //硬件系统初始化
	setpsw();
	act=0;							 //密码设置
	while(1)
	{		
		time=3;							   //限定尝试3次
		while(1)					   
		{
			inputpsw();					  		//输入密码
			checkpsw();							//密码验证
			checksuper();						//验证是否是超级密码						
			if(error_flag==0)  	
			{
				right();  		//正确处理
				act=0;
				modify_psw();	//询问是否修改密码
				close();		//关闭程序
				act=1;
				break;
			}
			else if(time>1)
			{
				error();		//允许2次尝试错误
			}		
			else				
			{
				lock();
				break;	 //3次错误,系统锁定
			}	
		}

	}
}