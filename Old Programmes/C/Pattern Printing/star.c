#include <stdio.h>

void star(int);

int main()
{
	int n;
	printf("Enter order : ");
	scanf("%d",&n);
	star(n);
}

void star(int n)
{
	int i,j;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n-i+n*2;j++)
			printf(" ");
		for(j=1;j<=i;j++)
			printf(" *");
		printf("\n");
	}
	for(i=n;i>=1;i--)
	{
		for(j=1;j<=n-i;j++)
			printf(" ");
		for(j=1;j<=i+n*2;j++)
			printf(" *");
		printf("\n");
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n-i;j++)
			printf(" ");
		for(j=1;j<=i+n*2;j++)
			printf(" *");
		printf("\n");
	}
	for(i=n;i>=1;i--)
	{
		for(j=1;j<=n-i+n*2;j++)
			printf(" ");
		for(j=1;j<=i;j++)
			printf(" *");
		printf("\n");
	}
}
