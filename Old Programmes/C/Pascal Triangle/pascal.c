#include <stdio.h>

#define MAX 100

void pascal(int);

int main()
{
	int n;
	printf("enter the order");
	scanf("%d",&n);
	pascal(n);
}
void pascal(int n)
{
	int x[MAX],y[MAX],i,j;
	x[0]=1;
	for(i=1;i<MAX;i++)
		x[i]=0;
	for(i=1;i<n;i++)
	{
		for(j=0;j<n-i;j++)
			printf("   ");
		y[0]=1;
		printf("%-5d ",y[0]);
		for(j=1;j<i;j++)
		{
			y[j]=x[j]+x[j-1];
			printf("%-5d ",y[j]);
		}
		printf("\n");
		for(j=1;j<i;j++)
			x[j]=y[j];
	}
}
