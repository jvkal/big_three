#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {

	//��Լ�� 1 
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
	printf("��С��Լ���� %d",b);
	return 0;
	*/
	
	//��Լ�� 2 
	/*
	int a , b , c ;
	int num;
	int n;
	printf("������Ҫ�����������");
	scanf("%d",&n);
	printf("�������1����=");
	scanf("%d",&a);
	for(num=0;num<n-1;num++){
		printf("�������%d����=",num+2);
		scanf("%d",&b);
		c = a % b;
		while(c!=0){
			a = b;
			b = c;
			c = a % b;
		}
	}
	 printf("��С��Լ���� %d",b);
	 return 0; 
	 */
	 
	 //���� 
	 /*
	int begin,end;
	int tree[10001];
	int length;
	int pp;
	int i,j,sum=0;
	int o; 
	printf("��������·���ȣ�");
	scanf("%d",&length);
	printf("�������ж�����·�ش���");
	scanf("%d",&pp);
	
	for(i=0;i<length;i++){
		tree[i]=1;//���������� 
	}
		o=1;
	for(i=0;i<pp;i++){
		
		printf("��������·��ʼλ��%d:",o);
		scanf("%d",&begin);
		
		printf("��������·����λ��%d:",o);
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
	printf("ʣ���������� %d",sum-1);
	*/
	int x_p,x_one_p,x_two_p,x_three_p,x_four_p;
	int a,b,c,d;//�ĸ�ͬѧ 
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
