#include <stdio.h>
#include <math.h>
#include <unistd.h>

void circle(int);

int main()
{
	int r;
	printf("Enter size : ");
	scanf("%d",&r);
	circle(r);
}

void circle(int r)
{
	int x,y;
	for(x=0;;x++)
	{
		for(y=-r;y<=r;y++)
			if(y<=(int)round(sin(x)))
				printf("*");
		printf(" *  *\n");
		usleep(100000);
	}
}
