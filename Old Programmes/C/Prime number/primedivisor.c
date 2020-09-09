#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include"prime.h"


int main()
{
	int i,count;
	long long int n,*p;
	system("clear");
	printf("\e[32;1mEnter a number :   \e[37;1m");
	scanf("%lld",&n);
	printf("\t\t\t=");
	count=primediv(n,&p);
	for(i=0;i<count;i+=2)
		printf("%s %lld^%d",(i==0)?"":" *",*(p+i),*(p+i+1));
	getchar();getchar();system("clear");
}
