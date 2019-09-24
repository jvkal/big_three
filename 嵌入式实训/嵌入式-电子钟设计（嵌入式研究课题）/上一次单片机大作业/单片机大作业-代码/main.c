#include "config.h"
#include <reg52.h>
sbit act = P3^2;
//��ʼ����Ϣ
void init_sys(void)
{	    
	int i =0;
	//TMOD�Ƕ�ʱ��0��1��8λ�Ĵ�����0X01��ָ��ʱ��0����Ϊ1������ʽ	
	TMOD=0x01;
	//5000��ʾ��Ҫ��ʱ����ʱһ����Ҫ�����ĸ���������Ϊ12Mʱ�����������Լ��ʱ50����
	//�̴����8λ�Ĵ��������µ��������8λ����
	TH0=(65536-50000)/256; //50ms
	TL0=(65536-50000)%256;
	//CPU�����ж�  								
    EA=1;ET0=1; 
	//��ʱ�ж�0�����ȶ���Ϊ1
	PT0=1;
	//������ʱ��0     											
    TR0=1;
	spk_deep_init();
}

void main()
{
	LCD_Initial();						 //lcd��ʾ����ʼ��
	init_sys();
	act=1;							 //Ӳ��ϵͳ��ʼ��
	setpsw();
	act=0;							 //��������
	while(1)
	{		
		time=3;							   //�޶�����3��
		while(1)					   
		{
			inputpsw();					  		//��������
			checkpsw();							//������֤
			checksuper();						//��֤�Ƿ��ǳ�������						
			if(error_flag==0)  	
			{
				right();  		//��ȷ����
				act=0;
				modify_psw();	//ѯ���Ƿ��޸�����
				close();		//�رճ���
				act=1;
				break;
			}
			else if(time>1)
			{
				error();		//����2�γ��Դ���
			}		
			else				
			{
				lock();
				break;	 //3�δ���,ϵͳ����
			}	
		}

	}
}