#ifndef _R__IO_H
#define _R__IO_H

#include<stdio.h>

char getch();
void clrscr();

char getch()
{
	getchar();
	return getchar();
}

void clrscr()
{
	system("clear");
}

#endif
