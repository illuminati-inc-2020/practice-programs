#include<stdio.h>

int main()
{
	typedef enum {red=1,green,blue,yellow} colours;
	colours c=blue;
	printf("%s",c);
}
