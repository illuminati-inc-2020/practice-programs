#include<stdio.h>
typedef enum palette{GRAY=30,RED,GREEN,YELLOW,BLUE,PURPLE,CYAN,WHITE} colour;
int textcolour(colour);
int main()
{
	textcolour(RED);
	printf("Rakesh");
	textcolour(GREEN);
	printf(" Malik");
}
int textcolour(colour c)
{
	printf("\e[%d;1m",c);
}
