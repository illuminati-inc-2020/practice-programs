#include<stdio.h>
#include<math.h>
int main()
{
	long long unsigned int i;
	int a;
	for(i=1,a=0;i!=0;i*=2,a++)
/*		if(i*2!=0)*/printf("%lld=2^%d\n",i,a);
}
