#include <reg51.h>
#include "key.h"
#include "lcd.h"
#include "ds1302.h"
#include "jq8400.h"
//---重定义关键词---//
#ifndef u8
#define u8 unsigned char 
#endif

#ifndef u32 
#define	u32 unsigned int 
#endif

u8 sys_time;
u8 sys_branch;
u8 sys_second;
u8 sys_year;
u8 sys_month;
u8 sys_day;
u8 sys_week; 

u8 sys_c_time = 15;
u8 sys_c_branch = 13;
u8 sys_c_second = 13;
u8 Clock_Data[16] = "Set AlarmClock 0";
bit layout_static = 0;
bit School_Static = 0;
u8 _BIT;

void UpdataDS1302()
{
	TIME[0] = sys_second /10 * 16 + sys_second % 10;
	TIME[1] = sys_branch /10 * 16 + sys_branch % 10;
	TIME[2] = sys_time /10 * 16 + sys_time % 10;
	TIME[3] = sys_day /10 * 16 + sys_day % 10;
	TIME[4] = sys_month /10 * 16 + sys_month % 10;
	TIME[5] = sys_week /10 * 16 + sys_week % 10;
	TIME[6] = sys_year /10 * 16 + sys_year % 10;
	Ds1302Init();
}

void LcdDisplay()
{
	u8 i;
	if(layout_static == 0)
	{
		if(School_Static == 0)
		{
			sys_second = TIME[0] / 16 * 10 + TIME[0] % 16;
			sys_branch = TIME[1] / 16 * 10 + TIME[1] % 16;
			sys_time   = TIME[2] / 16 * 10 + TIME[2] % 16;
			sys_day    = TIME[3] / 16 * 10 + TIME[3] % 16;
			sys_month  = TIME[4] / 16 * 10 + TIME[4] % 16;
			sys_week   = TIME[5] / 16 * 10 + TIME[5] % 16;
			sys_year   = TIME[6] / 16 * 10 + TIME[6] % 16;
		}
		LcdWriteCom(0x80 + 0X44);
		LcdWriteData('0' + sys_time / 10);	//时
		LcdWriteData('0' + sys_time % 10);				 
		LcdWriteData('-');
		LcdWriteData('0' + sys_branch / 10);//分
		LcdWriteData('0' + sys_branch % 10);	
		LcdWriteData('-');
		LcdWriteData('0' + sys_second / 10);//秒
		LcdWriteData('0' + sys_second % 10);

		LcdWriteCom(0x80 + 2);
		LcdWriteData('2');
		LcdWriteData('0');
		LcdWriteData('0' + sys_year / 10);	//年
		LcdWriteData('0' + sys_year % 10);
		LcdWriteData('-');
		LcdWriteData('0' + sys_month / 10);	//月
		LcdWriteData('0' + sys_month % 10);
		LcdWriteData('-');
		LcdWriteData('0' + sys_day / 10);	//日
		LcdWriteData('0' + sys_day % 10);
		LcdWriteData(' ');
		LcdWriteData('0' + sys_week % 10);	//星期		
		
		if(School_Static == 1)
		{
			LcdWriteCom(0x80);
			LcdWriteData('0' + _BIT);
		}else
		{
			LcdWriteCom(0x80);
			LcdWriteData(' ');
		}		
	}else if(layout_static == 1)
	{
		LcdWriteCom(0x80);
		for(i=0;i<15;i++)
		{
			LcdWriteData(Clock_Data[i]);
		}
		
		LcdWriteCom(0x80 + 0X44);
		LcdWriteData('0' + sys_c_time / 10);	//时
		LcdWriteData('0' + sys_c_time % 10);				 
		LcdWriteData('-');
		LcdWriteData('0' + sys_c_branch / 10);//分
		LcdWriteData('0' + sys_c_branch % 10);	
		LcdWriteData('-');
		LcdWriteData('0' + sys_c_second / 10);//秒
		LcdWriteData('0' + sys_c_second % 10);

		if(layout_static == 1)
		{
			LcdWriteCom(0x8F);
			LcdWriteData('0' + _BIT);
		}else
		{
			LcdWriteCom(0x80);
			LcdWriteData(' ');
		}		
	}

}

u8 bs_flag = 0;


void JQ8400_Send(u8 _time)
{
	JQ8400_SendData(0x0A);
	if(_time / 10 == 0)
	{
		JQ8400_SendData(_time);
	}else
	{
		JQ8400_SendData(_time / 10);
		JQ8400_SendData(_time % 10);
	}
	JQ8400_SendData(0x0B);	
}

void main(void)
{
	LcdInit();
	
//	Ds1302Init();
	
	JQ8400_SendData(0x0A);
	JQ8400_SendData(0x03);
	JQ8400_SendData(0x00);
	JQ8400_SendData(0x0C);
	
	while(1)
	{
		switch(KeyScan())	
		{
			case 1:
				if(School_Static == 0)
				{
					layout_static = ~layout_static;
					School_Static = 0;
					_BIT = 0;
				
					if(layout_static == 1)
					{
						LcdWriteCom(0x8F);
						LcdWriteData('0' + _BIT);
					}else
					{
						LcdWriteCom(0x80);
						LcdWriteData(' ');
					}
						
					LcdWriteCom(0x01);					
				}

				break;
			case 2:
				if(layout_static == 0)
				{
					if(School_Static == 1)
					{
						UpdataDS1302();
					}
					
					School_Static = ~School_Static;
					_BIT = 0;

					if(School_Static == 1)
					{
						LcdWriteCom(0x80);
						LcdWriteData('0' + _BIT);
					}else
					{
						LcdWriteCom(0x80);
						LcdWriteData(' ');
					}					
				}
				break;
				
			case 3:
				if(layout_static == 1)//闹钟
				{
					if(_BIT == 0)
					{
						_BIT = 3;
					}
					else
					{
						_BIT --;
					}
					
				}else if(School_Static == 1)
				{
					if(_BIT == 0)
					{
						_BIT = 7;
					}
					else
					{
						_BIT --;
					}					
				}
				break;
			case 4:
				if(layout_static == 1)
				{
					if(_BIT == 3)
					{
						_BIT = 0;
					}
					else
					{
						_BIT ++;
					}
					
				}else if(School_Static == 1)
				{
					if(_BIT == 7)
					{
						_BIT = 0;
					}
					else
					{
						_BIT ++;
					}					
				}
				break;
			case 5:
				if(layout_static == 1)//闹钟
				{
					if(_BIT == 1)
					{
						if(sys_c_time == 0)
						{
							sys_c_time = 23;
						}else
						{
							sys_c_time --;
						}
					}
					else if(_BIT == 2)
					{
						if(sys_c_branch == 0)
						{
							sys_c_branch = 59;
						}else
						{
							sys_c_branch --;
						}
					}else if(_BIT == 3)
					{
						
						if(sys_c_second == 0)
						{
							sys_c_second = 59;
						}
						else
						{
							sys_c_second --;
						}
					}
				}else if(School_Static == 1)
				{
					if(_BIT == 1)
					{
						if(sys_year <= 0)
						{
							sys_year = 99;
						}else
						{
							sys_year --;
						}
					}
					else if(_BIT == 2)
					{
						if(sys_month <= 0)
						{
							sys_month = 12;
						}else
						{
							sys_month --;
						}
						
					}
					else if(_BIT == 3)
					{
						if(sys_day <= 0)
						{
							sys_day = 31;
						}else
						{
							sys_day--;
						}
					}
					else if(_BIT == 4)
					{
						if(sys_week <= 1)
						{
							sys_week = 7;
						}else
						{
							sys_week --;
						}
					}
					else if(_BIT == 5)
					{
						if(sys_time <= 0)
						{
							sys_time = 23;
						}else
						{
							sys_time--;
						}
					}
					else if(_BIT == 6)
					{
						if(sys_branch <= 0)
						{
							sys_branch = 59;
						}else
						{
							sys_branch --;
						}
					}	
					else if(_BIT == 7)
					{
						if(sys_second <= 0)
						{
							sys_second = 59;
						}else
						{
							sys_second --;
						}
					}					
				}
				break;
			
			case 6:
				if(layout_static == 1)//闹钟
				{
					if(_BIT == 1)
					{
						sys_c_time ++;
						if(sys_c_time >= 24)
						{
							sys_c_time = 0;
						}
					}
					else if(_BIT == 2)
					{
						sys_c_branch ++;
						if(sys_c_branch >= 60)
						{
							sys_c_branch = 0;
						}
					}else if(_BIT == 3)
					{
						sys_c_second ++;
						if(sys_c_second >= 60)
						{
							sys_c_second = 0;
						}						
					}
				}else if(School_Static == 1)
				{
					if(_BIT == 1)
					{
						sys_year ++;
					}
					else if(_BIT == 2)
					{
						sys_month ++;
						if(sys_month > 12)
						{
							sys_month = 0;
						}
						
					}
					else if(_BIT == 3)
					{
						sys_day ++;
						if(sys_day > 31)
						{
							sys_day = 0;
						}
					}
					else if(_BIT == 4)
					{
						sys_week ++;
						if(sys_week > 7)
						{
							sys_week = 1;
						}
					}
					else if(_BIT == 5)
					{
						sys_time ++;
						if(sys_time >= 24)
						{
							sys_time = 0;
						}
					}
					else if(_BIT == 6)
					{
						sys_branch ++;
						if(sys_branch >= 60)
						{
							sys_branch = 0;
						}
					}	
					else if(_BIT == 7)
					{
						sys_second ++;
						if(sys_second >= 60)
						{
							sys_second = 0;
						}
					}					
				}				
				break;
			default:
				break;
		}
		
		if(School_Static == 0)
		{
			Ds1302ReadTime();
			if((sys_branch == 0)&&(sys_second == 0))
			{
				bs_flag ++;
			}else
			{
				bs_flag = 0;
			}
			if((sys_time == sys_c_time)&&(sys_branch == sys_c_branch)&&(sys_second == sys_c_second))
			{
				bs_flag = 0;
				JQ8400_Send(25);//闹铃
			}
				
			if(bs_flag == 1)
			{
				JQ8400_Send(sys_time);
			}
			
			
		}
		
		
		LcdDisplay();	
	}
}

