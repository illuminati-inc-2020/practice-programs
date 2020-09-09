#if !defined(_R__OP_H)
#define _R__OP_H

#include<math.h>

char set[10]="=-+*/^";

int precedence(char op)
{
	int i;
	op=(op=='+')?'-':op;
	op=(op=='/')?'*':op;
	for(i=0;set[i];i++)
		if(set[i]==op)
			return i;
	return 0;
}
int isoperator(char c)
{
	int i;
	for(i=0;set[i];i++)
		if(set[i]==c)
			return 1;
	return 0;
}

int operate(int a,char o,int b)
{
	switch(o)
	{
		case '+': return a+b;
		case '-': return a-b;
		case '*': return a*b;
		case '/': return a/b;
		case '^': return pow(a,b);
	}
	return 0;
}

#endif
