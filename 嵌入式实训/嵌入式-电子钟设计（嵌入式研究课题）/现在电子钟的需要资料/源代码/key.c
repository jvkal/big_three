#include "key.h"
void Delay10ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 18;
	j = 235;
	do
	{
		while (--j);
	} while (--i);
}


u8 KeyScan()
{
	u8 i = 0;
	u8 keyValue = 0;
	if(KEY1 == 0)
	{
		Delay10ms();
		if(KEY1 == 0)
		{
			keyValue = 1;
			i = 0;
			while ((i<50) && (KEY1==0))	 	//¼ì²â°´¼üÊÇ·ñËÉ¿ª
			{
				Delay10ms();
				i++;
			}
		}
	}

	if(KEY2 == 0)
	{
		Delay10ms();
		if(KEY2 == 0)
		{
			keyValue = 2;
			i = 0;
			while ((i<50) && (KEY2==0))	 	//¼ì²â°´¼üÊÇ·ñËÉ¿ª
			{
				Delay10ms();
				i++;
			}
		}
	}
	
	if(KEY3 == 0)
	{
		Delay10ms();
		if(KEY3 == 0)
		{
			keyValue = 3;
			i = 0;
			while ((i<50) && (KEY3==0))	 	//¼ì²â°´¼üÊÇ·ñËÉ¿ª
			{
				Delay10ms();
				i++;
			}
		}
	}
	
	if(KEY4 == 0)
	{
		Delay10ms();
		if(KEY4 == 0)
		{
			keyValue = 4;
			i = 0;
			while ((i<50) && (KEY4==0))	 	//¼ì²â°´¼üÊÇ·ñËÉ¿ª
			{
				Delay10ms();
				i++;
			}
		}
	}

	if(KEY5 == 0)
	{
		Delay10ms();
		if(KEY5 == 0)
		{
			keyValue = 5;
			i = 0;
			while ((i<20) && (KEY5==0))	 	//¼ì²â°´¼üÊÇ·ñËÉ¿ª
			{
				Delay10ms();
				i++;
			}
		}
	}
	
	if(KEY6 == 0)
	{
		Delay10ms();
		if(KEY6 == 0)
		{
			keyValue = 6;
			i = 0;
			while ((i<20) && (KEY6==0))	 	//¼ì²â°´¼üÊÇ·ñËÉ¿ª
			{
				Delay10ms();
				i++;
			}
		}
	}
	return keyValue;
}