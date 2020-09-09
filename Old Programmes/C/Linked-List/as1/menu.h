#ifndef __MENU_H
#define __MENU_H

#include<stdio.h>
#include<stdarg.h>
#include<stdlib.h>

void menu(char*,char*,int,...);

/*
 * function 'menu' takes as argument
 * 	header	->	header string of the menu
 * 	tailer	->	string for the last option to exit from menu
 * 	length	->	number of options
 * 	...	->	string for the options by order and then the corresponding functions to
 * 			be called respectively
 */

void menu(char *header,char *tailer,int length,...)
{
	va_list options;
	int i,choice=-1;
	void (*fnc)(void);
	while(choice!=length+1)
	{
		system("clear");
		va_start(options,length);
		printf("%s\n\n",header);
		for(i=1;i<=length;i++)
		{
			printf("%d. ",i);
			puts(va_arg(options,char*));
		}
		printf("%d. ",length+1);
		puts(tailer);
		printf("\n\n\tEnter your choice_ ");
		scanf("%d",&choice);
		if(choice>0 & choice<=length)
		{
			for(i=1;i<choice;i++)
				va_arg(options,void);
			fnc=va_arg(options,void(*)(void));
			(*fnc)();
		}
		else if(choice>length+1 || choice<=0)
		{
			fprintf(stderr,"\n\nYou have entered a wrong choice");
			putchar('\n');
			sleep(1);
		}
	}
}

#endif
