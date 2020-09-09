/*	Author : Rakesh Malik
 *	Date : 23.11.2010 - 02.12.2010
 *	B.Sc. Computer Science 2nd Year
 *	Stack Operations
 */

#ifndef _STACK_H
#define _STACK_H

#define MAXSTACK 200

int underflow(int stack[],int top)
{
	if(top<0) return 1;
	else return 0;
}

int overflow(int stack[],int top)
{
	if(top>=MAXSTACK) return 1;
	else return 0;
}

void push(int stack[],int *top,int item)
{
	if(overflow(stack,*top)) fprintf(stderr,"stack overflow\n");
	else stack[++(*top)]=item;
}

int pop(int stack[],int *top)
{
	if(underflow(stack,*top)) fprintf(stderr,"stack underflow\n");
	else return stack[(*top)--];
	return 0;
}


#endif
