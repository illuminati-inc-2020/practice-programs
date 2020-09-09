#if !defined(_R__STACK_H)
#define _R__STACKE_H

#include<stdio.h>
#include<stdlib.h>

#if!defined(MAXSTACK)
#define MAXSTACK 1000
#endif

void push(char stack[],int *top,void *item,size_t size)
{
	int i;
	char* x;
	x=(char*)item;
	if(*top>MAXSTACK)
	{
		printf("Stack Overflow");
		exit(0);
	}
	else
		for(i=0;i<size;i++)
			stack[(*top)++]=*(x++);
}

void *pop(char stack[],int *top,size_t size)
{
	if(*top<0)
	{
		printf("Stack Underflow");
		exit(0);
	}
	else
	{
		(*top)-=size;
		return &stack[*top];
	}
	return NULL;
}

#endif