/**********************************************************************
* 程序名;  时钟实验1
* 功  能： 数码管通过动态扫描显示时间，时间可设定,调整时间时时钟不走.
* 编程者： ZPZ
* 编程时间：2009/8/9
**********************************************************************/
#include<reg52.h>
#define uint unsigned int 
#define uchar unsigned char
 		
sbit  _led=P2^7;
sbit  key1=P2^0;
sbit  key2=P2^1;
sbit  key3=P2^2;
uchar  num=0,temp=0,count=0;
uchar  aa;
uchar hour,min,sec;
uchar code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

void  delay(uint z);
void  display(uchar a,uchar b,uchar c,uchar d,uchar e,uchar f,uchar aa);
void  read_key();
void  led();
void  time_change();

/****************** 主函数  *******************/
void main()
{
	P2=0xff;
	hour=0;
	min=0;
	sec=0;
	TMOD=0x11;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	TH1=(65536-50000)/256;
	TL1=(65536-50000)%256;
	EA=1;
	ET0=1;
	ET1=1;
	TR0=1;
	TR1=1;
	aa=0xff;
    while(1)
    {	
		time_change();	
        display(table[hour/10],table[hour%10],table[min/10],
		         table[min%10],table[sec/10],table[sec%10],0xff);		     
    }
}

  
/****************** 显示函数  *******************/
void display(uchar a,uchar b,uchar c,uchar d,uchar e,uchar f,uchar aa)
{
    if(num==1){P1=0x01&aa;P0=a;delay(2);}else{P1=0x01;P0=a;delay(2);}   //hour
    if(num==1){P1=0x02&aa;P0=b;delay(2);}else{P1=0x02;P0=b;delay(2);}  //hour
    if(num==2){P1=0x04&aa;P0=c;delay(2);}else{P1=0x04;P0=c;delay(2);} //min
    if(num==2){P1=0x08&aa;P0=d;delay(2);}else{P1=0x08;P0=d;delay(2);} //min
    if(num==3){P1=0x10&aa;P0=e;delay(2);}else{P1=0x10;P0=e;delay(2);} //sec
    if(num==3){P1=0x20&aa;P0=f;delay(2);}else{P1=0x20;P0=f;delay(2);} //sec
	
}

/************** 定时器0中断函数  ***************/
void timer0() interrupt 1 
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	temp++;
	
}

/************** 定时器1中断函数  ***************/
void timer1() interrupt 3 
{
	TH1=(65536-50000)/256;
	TL1=(65536-50000)%256;
	count++;
	if(count>=20)
	count=0;
	
}

/****************** 延时子函数  *******************/
void delay(uint z)
{
   uint j,k;
   for(j=z;j>0;j--)
     for(k=120;k>0;k--);
}

/****************** 读按键函数  *******************/
void read_key()
{
  if(key1==0)
  {	 
    _led=0;
    delay(100);
    if(key1==0)
    { 		
	        delay(100);
			_led=1;
			num++;
		    if(num>3){num=0;} 
			while(1)
			{
			   
	            
		
				if(key1==0)
			    {	
				    _led=0;
			        delay(10);
			        if(key1==0)
			        {
			          num++;
				      if(num>3){num=0;break;}  
			        }
					while(!key1);
					delay(10);
					while(!key1);
					_led=1;
				
				}
			    
				if(key2==0)
			    {	
				    _led=0;
			        delay(80);
			        if(key2==0)
			        {
			            if(num==1){hour++;if(hour==24)hour=0;}
			            if(num==2){min++;if(min==60)min=0;}
			            if(num==3){sec++;if(sec==60)sec=0;}
			        }
					while(!key1);
					delay(10);
					while(!key1);
					_led=1;
				
				}
			 
			    if(key3==0)
			    {	
				    _led=0;
			        delay(80);
			        if(key3==0)
			        {
			            
						if(num==1){hour--;if(hour==0)hour=23;}				
			            if(num==2){min--;if(min==0)min=59;}
			            if(num==3){sec--;if(sec==59)sec=59;}
			        }
					while(!key1);
					delay(10);
					while(!key1);
					_led=1;
			    }

				if(count<=15)
				display(table[hour/10],table[hour%10],table[min/10],
		                 table[min%10],table[sec/10],table[sec%10],0xff);
				if(count>15)
	           	display(table[hour/10],table[hour%10],table[min/10],
		                 table[min%10],table[sec/10],table[sec%10],0x00);
				

				
		    }

	 }
	while(!key1);
	delay(10);
	while(!key1);
	_led=1;
  }
	 	
}
	   

/****************** 时间调整函数  *******************/
void time_change()
{
    read_key();
	if(temp>=20)
	{
	 temp=0;
     sec++;
	 if(sec>=60)
	   {
	   	  sec=0;
		  min++;
		  if(min>=60)
		  {
			 min=0;
		     hour++;
			 if(hour>=24)
			 {
			 	hour=0;
			 }
		   }
	    }
	 }
}


