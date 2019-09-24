#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {

	//公约数 1 
	/*
	int a , b , c;
	scanf("%d%d",&a,&b);
	c = a % b;
	while(c!=0)
	{
		a = b;
		b = c;
		c = a % b;
	}
	printf("最小公约数： %d",b);
	return 0;
	*/
	
	//公约数 2 
	/*
	int a , b , c ;
	int num;
	int n;
	printf("请输入要计算多少数？");
	scanf("%d",&n);
	printf("请输入第1个数=");
	scanf("%d",&a);
	for(num=0;num<n-1;num++){
		printf("请输入第%d个数=",num+2);
		scanf("%d",&b);
		c = a % b;
		while(c!=0){
			a = b;
			b = c;
			c = a % b;
		}
	}
	 printf("最小公约数： %d",b);
	 return 0; 
	 */
	 
	 //种树 
	 /*
	int begin,end;
	int tree[10001];
	int length;
	int pp;
	int i,j,sum=0;
	int o; 
	printf("请输入马路长度：");
	scanf("%d",&length);
	printf("请输入有多少修路地带：");
	scanf("%d",&pp);
	
	for(i=0;i<length;i++){
		tree[i]=1;//让树都种上 
	}
		o=1;
	for(i=0;i<pp;i++){
		
		printf("请输入修路开始位置%d:",o);
		scanf("%d",&begin);
		
		printf("请输入修路结束位置%d:",o);
		scanf("%d",&end);
		for(j=begin;j<end;j++){
			tree[j]=0;
		}
		o++;
	}
	for(i=0;i<=length;i++){
		if(tree[i]==1){
			sum++; 
		}
	}	 
	printf("剩余树总数： %d",sum-1);
	*/
	int x_p,x_one_p,x_two_p,x_three_p,x_four_p;
	int a,b,c,d;//四个同学 
	for(a=1;a<=4;a++)
	{
		for(b=1;b<=4;b++)
		{
			for(c=1;c<=4;c++)
			{
				for(d=1;d<=4;d++)
				{
					x_p=(a!=b)&&(a!=c)&&(a!=d)&&(b!=c)&&(c!=d)&&(b!=d);
					
					x_one_p=(((a==1)&&(b!=4)&&(c!=3)) || ((a!=1)&&(b==4)&&(c!=3)) || ((a!=1)&&(b!=4)&&(c==3)));
					
					x_two_p=(((b==1)&&(a!=4)&&(c!=2)&&(d!=3)) || ((b!=1)&&(a==4)&&(c!=2)&&(d!=3))
						||((b!=1)&&(a!=4)&&(c==2)&&(d!=3))||((b!=1)&&(a!=4)&&(c!=2)&&(d==3)));
						
					x_three_p=(((b==4)&&(a!=3))||((b!=4)&&(a==3)));
					
					x_four_p =(((c==1)&&(d!=4)&&(b!=2)&&(a!=3))||((c!=1)&&(d==4)&&(b!=2)&&(a!=3))
						||((c!=1)&&(d!=4)&&(b==2)&&(a!=3))||((c!=1)&&(d!=4)&&(b!=2)&&(a==3)));
					
					if(x_p&&x_one_p&&x_two_p&&x_three_p&&x_four_p) 
					{
						printf("a=%d,b=%d,c=%d,d=%d",a,b,c,d);
					}
				}
			}
		}
	}
	
	return 0;
}
