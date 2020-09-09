#include<stdio.h>
#include<math.h>
#include<ctype.h>

int isprime(int n);
int main(int argc,char *argv[])
{
	int m,n,i,count=0;
	m=atoi(argv[1]);
	n=atoi(argv[2]);
	for(i=m;i<=n-2;i++)
	{
		if(isprime(i) && isprime(i+2))
			printf("%d : (%d,%d)\n",++count,i,i+2);
	}
}
int isprime(int n)
{
	int i,j;
	i=sqrt(n);
	if(n==1) return 0;
	if(n==2) return 1;
	if(n%2==0) return 0;
	for(j=3;j<=i;j+=2)
	{
		if(n%j==0)
			return 0;
	}
	return 1;
}

