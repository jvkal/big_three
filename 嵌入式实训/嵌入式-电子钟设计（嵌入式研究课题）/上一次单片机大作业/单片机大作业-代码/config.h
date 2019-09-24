//一些头文件的信息配置

unsigned char key,flag,error_flag,time;	//键值,按键标志,密码错误标志,试探次数
unsigned char syspsw[8]={0,0,0,0,0,0,0,0};	//设定密码,用户密码,超级密码
unsigned char userpsw[8]={0,0,0,0,0,0,0,0};
unsigned char code superpsw[8]={1,2,3,4,5,6,7,8};
unsigned int ltime;						//系统时间
#include "lcd1602.c"
#include "IRQ.c"
#include "function.c"
#include "spk.c"