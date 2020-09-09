#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int isprime(long long int);
int primediv(long long int,long long int**);

int isprime(long long int n)
{
	 register long long int i;
	if(n==1) return 1;
	if(n==2) return 1;
	if(n%2==0) return 0;
	for(i=3;i*i<=n;i+=2)
		if(n%i==0)
			return 0;
	return 1;
}

int primediv(long long int n,long long int **p)
{
	register long long int i,x,y;
	register int count=0;
	*p=NULL;
	if(n%2==0)
	{
		for(y=0,x=1;n%x==0;y++,x*=2);
		if(y>1)
		{
			count+=2;
			*p=(long long int*)realloc(*p,8*count);
			*(*p+count-2)=2;
			*(*p+count-1)=y-1;
			n=n/pow(2,y-1);
		}
	}
	for(i=3;;i+=2)
		if(isprime(i))
		{
			if(isprime(n))
				break;
			for(y=0,x=1;n%x==0;y++,x*=i);
			if(y>1)
			{
				count+=2;
				*p=(long long int*)realloc(*p,8*count);
				*(*p+count-2)=i;
				*(*p+count-1)=y-1;
				n=n/pow(i,y-1);
			}
		}
	if(n!=1)
	{
		count+=2;
		*p=(long long int*)realloc(*p,8*count);
		*(*p+count-2)=n;
		*(*p+count-1)=1;
	}
	return count;
}
