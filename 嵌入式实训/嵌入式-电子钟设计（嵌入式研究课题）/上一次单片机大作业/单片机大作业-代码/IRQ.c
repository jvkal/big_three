//硬件中断请求
//获取键盘的输入
unsigned char keyscan(void)
{
	P1=0x0f;
	if((P1&0x0f)!=0x0f)
	{
		flag=1;
		P1=0xef;
		switch(P1&0x0f)
		{
			case 0x0e:
				while((P1&0x0f)!=0x0f);
					return('*');
			case 0x0d:
				while((P1&0x0f)!=0x0f);
					return(7);
			case 0x0b:
				while((P1&0x0f)!=0x0f);
					return(4);
			case 0x07:
				while((P1&0x0f)!=0x0f);
					return(1);
			default:  
				break;
		}
		P1=0xdf;
		switch(P1&0x0f)
		{
			case 0x0e:
				while((P1&0x0f)!=0x0f);
					return('*');
			case 0x0d:
				while((P1&0x0f)!=0x0f);
					return(8);
			case 0x0b:
				while((P1&0x0f)!=0x0f);
					return(5);
			case 0x07:
				while((P1&0x0f)!=0x0f);
					return(2);
			default:  
				break;
		}

		P1=0xbf;
		switch(P1&0x0f)
		{
			case 0x0e:
				while((P1&0x0f)!=0x0f);
					return('#');
			case 0x0d:
				while((P1&0x0f)!=0x0f);
					return('*');
			case 0x0b:
				while((P1&0x0f)!=0x0f);
					return(6);
			case 0x07:
				while((P1&0x0f)!=0x0f);
					return(3);
			default:  
				break;
		}
	}
	else  return(key);
	
}


void timer0(void) interrupt 1           //定时器0方式1，50ms中断一次
{
	ltime++;
	TH0=(65536-50000)/256; //50ms
	TL0=(65536-50000)%256; 
	key=keyscan();                                
}



