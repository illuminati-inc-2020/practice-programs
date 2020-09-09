#include <string.h>
#include <stdio.h>

int main()
{
	char b[100]="Asif is a bad boy";
	memmove(b+14,b+13,10);
	strcpy(b+10,"good");
	printf(b);
}
