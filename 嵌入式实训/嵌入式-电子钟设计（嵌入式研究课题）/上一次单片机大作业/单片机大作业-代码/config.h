//һЩͷ�ļ�����Ϣ����

unsigned char key,flag,error_flag,time;	//��ֵ,������־,��������־,��̽����
unsigned char syspsw[8]={0,0,0,0,0,0,0,0};	//�趨����,�û�����,��������
unsigned char userpsw[8]={0,0,0,0,0,0,0,0};
unsigned char code superpsw[8]={1,2,3,4,5,6,7,8};
unsigned int ltime;						//ϵͳʱ��
#include "lcd1602.c"
#include "IRQ.c"
#include "function.c"
#include "spk.c"