#include <stdio.h>
#include <math.h>

void circle(int);

int main()
{
	int r;
	printf("Enter radius : ");
	scanf("%d",&r);
	circle(r);
}

void circle(int r)
{
	int x,y;
	for(x=-r;x<=r;x++)
	{
		for(y=-r;y<=r;y++)
			if(y<=(int)round(sqrt(r*r-x*x))&&y>=-(int)round(sqrt(r*r-x*x)))
				printf("* ");
			else
				printf("  ");
		printf("\n");
	}
}
