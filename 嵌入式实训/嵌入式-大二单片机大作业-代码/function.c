//-------------------超级用户检测----------------
void spk_deep();
void spk_deep_error();
void spk_deep_right();
void spk_deep_error_lock();
void checksuper(void)				   		
{										   	
	unsigned char i;
	if(error_flag==1) 			 //若普通密码通过验证,则不验证超级密码
	{	
		error_flag=0;
		for(i=0;i<8;i++)
		{ 	
			if(userpsw[i]!=superpsw[i])  {error_flag=1;break;}
		}
	}
}

//--------------------密码检验--------------
void checkpsw(void)				   		
{										   	
	unsigned char i;
	error_flag=0;
	for(i=0;i<8;i++)
	{
		if(userpsw[i]!=syspsw[i])  {error_flag=1;break;}
	}
}
//--------------------密码输入--------------

void inputpsw(void)					  
{
	unsigned char i;
	for(i=0;i<8;i++)  userpsw[i]=0;
	GotoXY(0,0); 
	Print("input psw:");
	GotoXY(12,1);
	Print("TM:");
	LCD_Write(1,time+0x30);		
	for(i=0;i<8;)
	{			
		flag=0;
		spk_deep();
		while(flag==0);
		if(key=='*') 	 	{ GotoXY(i-1,1);LCD_Write(1,' ');if(i>0) userpsw[--i]=0;}
		else if(key=='#') 	{ GotoXY(i,1);LCD_Write(1,'#');break;}
		else 				{ GotoXY(i,1);LCD_Write(1,'*');userpsw[i++]=key;}
	}
	 spk_deep();
	ltime=0;
	while(ltime<20);
}
//--------------------密码设定---------------
void setpsw(void)					
{
	unsigned char i;
	GotoXY(0,0); 
	Print("set you psw:");
	GotoXY(0,1); 		
	for(i=0;i<8;i++)
	{	
		flag=0;
		spk_deep();
		while(flag==0);
		if(key=='*') break;
		if(key=='#') break;
		syspsw[i]=key;
		LCD_Write(1,key+0x30);
			
	}
	ltime=0;
	while(ltime<20);
	LCD_Write(0,1);
	GotoXY(0,1); 
	Print("set ok!");
	for(i=0;i<20;i++)
	{
		spk_deep();
	}
	spk_deep_right();
	ltime=0;
	while(ltime<50);		//显示欢迎信息时间
	LCD_Write(0,1);
}

//------------------正确处理------------------------
void right(void)
{
 	LCD_Write(0,1);
	GotoXY(10,0);
	spk_deep_right();
	Print("open!");
	ltime=0;
	while(ltime<40);
}
//----------------- 错误处理-------------------------
void error(void)
{
	LCD_Write(0,1);
	GotoXY(0,0);
	Print("Forget?");
	spk_deep_error();
	ltime=0;
	while(ltime<20);               
	LCD_Write(0,1);
	time--;
}
//-------------------封锁系统-------------------------
void lock(void)
{
	int i = 0;
	LCD_Write(0,1);
	GotoXY(0,0);
	Print("warning!!!");
	for(i=0;i<80;i++)
	{
	   	spk_deep_error_lock();
	}
	GotoXY(0,1);
	Print("keep away!");
	ltime=0;
	while(ltime<80);                
	LCD_Write(0,1);	
}

//-------------------修改密码-------------------------
void modify_psw(void)
{
	unsigned char i;
	LCD_Write(0,0x01);
	GotoXY(0,0);
	Print("change psw?");
	GotoXY(0,1);
	flag=0;
	while(flag==0);
	if(key=='#')
	{
	   GotoXY(0,0);
	   Print("input repsw");
	   GotoXY(0,1);	
	   	for(i=0;i<8;i++)
		{	
			syspsw[i]=0;		
		}
	   	for(i=0;i<8;i++)
		{	
			flag=0;
			spk_deep();
			while(flag==0);
			if(key=='*') break;
			if(key=='#') break;
			syspsw[i]=key;
			LCD_Write(1,key+0x30);
				
		}
		
	ltime=0;
	while(ltime<20);
	LCD_Write(0,1);
	GotoXY(0,1); 
	Print("reset ok!");
	for(i=0;i<20;i++)
	{
		spk_deep();
	}
	spk_deep_right();
	ltime=0;
	while(ltime<50);		//显示欢迎信息时间
	LCD_Write(0,1);
	}
	if(key=='*')
	{
		LCD_Write(0,0x01);
		return;
	}
	LCD_Write(0,0x01);			
}

//------------------关闭程序------------------------
void close(void)
{
	GotoXY(10,0);
	Print("close");
	spk_deep_right(); 
	ltime=0;
	while(ltime<40);
	LCD_Write(0,1);
}	 