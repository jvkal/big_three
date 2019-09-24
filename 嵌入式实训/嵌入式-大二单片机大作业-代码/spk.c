#include <reg52.h> 
sbit beep = P3^5;

void delay_spk(unsigned int i)
{
	while(i--);
}

void spk_deep_init()
{
	unsigned char i=100;
	while(i--)
	{
		beep = 0;
		delay_spk(200);
		beep = 1;
		delay_spk(100);	
		beep = 0;
		delay_spk(50);
		beep = 1;
		delay_spk(80);	
	}
}

void spk_deep()
{
	unsigned char i=20000;
	while(i--)
	{
		beep=~beep;
		//beep = 0;
		delay_spk(200);
		//beep = 1;
		//delay_spk(500);
	}
}
void spk_deep_error()
{
   	unsigned char i=100;
	while(i--)
	{
		beep=~beep;
		delay_spk(500);
	}
}

void spk_deep_right()
{
   	unsigned char i=100;
	while(i--)
	{
		beep = 0;
		delay_spk(50);
		beep = 1;
		delay_spk(80);
	}
}

void spk_deep_error_lock()
{
   	unsigned char i=10;
	while(i--)
	{
		beep=~beep;
		delay_spk(2000);
	}
}