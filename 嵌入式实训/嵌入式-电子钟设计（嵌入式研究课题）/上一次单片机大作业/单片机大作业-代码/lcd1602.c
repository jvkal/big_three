//=��ʾ���Ķ���
#include <reg52.h>
#define  DBPort P0		//LCD���ݶ˿�
sbit LcdRs		= P2^0;
sbit LcdRw		= P2^1;
sbit LcdEn  	= P2^2;
sbit Lcdbf      = P0^7;		//LCDæ��־ Busy Flag

void delay(unsigned int t)	 //��ʱ
{    
	while(t--);
}

void  LCD_Wait(void)	//��æ״̬
{
	LcdRs=0;
	LcdRw=1;
	LcdEn=1;
	delay(10);LcdEn=0;	//�½���	
	while(Lcdbf)
	{
	  LcdEn=0;LcdEn=1;	 //�������Ҫ�����,ʵ��Ӳ���в���Ҫ
	}			
} 

void LCD_Write(bit style, unsigned char input)	 //д����1/����0
{
	LcdRs=style;
	LcdRw=0;		
	DBPort=input;	
	LcdEn=1;
	delay(10);
	LcdEn=0;			
	LCD_Wait();	
}

void LCD_Initial(void)			  //��ʼ��LCD
{
	LCD_Write(0,0x38);  		 //8λ���ݶ˿�,2����ʾ,5*7����
	delay(300);
	LCD_Write(0,0x0c);           //��ʾģʽ
	LCD_Write(0,0x01);           //����
	LCD_Write(0,0x06);           //����ģʽ
}

void GotoXY(unsigned char x, unsigned char y)  //�ƶ���굽ָ��λ��
{
	if(y==0)	LCD_Write(0,0x80|x);
	if(y==1)    LCD_Write(0,0xc0|x);
}

void Print(unsigned char *str)	 //ָ����������ַ���
{
	while(*str)  
		LCD_Write(1,*str++);
}


