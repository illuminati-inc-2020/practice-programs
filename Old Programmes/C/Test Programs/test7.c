#include<stdio.h>
#include<stdlib.h>
int main()
{
	int x[10][10];
	printf("%d",sizeof(x)/sizeof(x[0][0]));
}
