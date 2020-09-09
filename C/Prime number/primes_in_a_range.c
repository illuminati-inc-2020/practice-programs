#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int isprime(long long int);
int primediv(long long int,long long int**);

int main()
{
	int m,n,i;
	system("clear");
	printf("\e[32;1mEnter range :   \e[37;1m");
	scanf("%d",&m);
	printf("\e[32;1m\t\t\tto\t\e[37;1m");
	scanf("%d",&n);
	printf("\e[32;1m\nPrimes are :\n\e[37;1m");
	for(i=m;i<=n;i++)
		if(isprime(i))
			printf("%d,",i);
	getchar();getchar();system("clear");
}

int isprime(long long int n)
{
	int i;
	if(n==1) return 0;
	if(n==2) return 1;
	if(n%2==0) return 0;
	for(i=3;i<=sqrt(n);i+=2)
		if(n%i==0)
			return 0;
	return 1;
}

