#include<stdio.h>
#include<ctype.h>
#include"queue.h"
#include"op.h"

int pre_eval(char*);

int main()
{
	char *s;
	int x;
	clrscr();
	scanf("%[^\n]",s);
	printf("\n\n%s\n=%d",s,pre_eval(s));
	getch();
	return 0;
}

int pre_eval(char s[])
{
	char q[MAXQUEUE],temp,space=' ',c1=0,c2=0,c3=0,*temps;
	int qfront=0,qrear=0,num1=0,num2=0,i,j;
	for(;*s;s++)
		insert(q,&qfront,&qrear,s,1);
	insert(q,&qfront,&qrear,&space,1);
	while(qfront!=qrear-1)
	{
		c3=c2;
		c2=c1;
		temp=c1=*(char*)delete(q,&qfront,&qrear,1);
		insert(q,&qfront,&qrear,&temp,1);
		temp=c1;
		while(isdigit(temp))
		{
			num1=num1*10+temp-'0';
			temp=*(char*)delete(q,&qfront,&qrear,1);
			insert(q,&qfront,&qrear,&temp,1);
		}
		num2=num1;
		if(!isdigit(c1))
		{
			delete(q,&qfront,&qrear,1);
			insert(q,&qfront,&qrear,&space,1);
		}
		if(isoperator(c3) && isdigit(c2) && isdigit(c1))
		{
			itoa(operate(num1,c3,num2),temps,10);
			dequeue(q,&qfront,&qrear,1);
			do temp=*(char*)dequeue(q,&qfront,&qrear,1);
			while(temp==' ');
			do temp=*(char*)dequeue(q,&qfront,&qrear,1);
			while(temp==' ');
			dequeue(q,&qfront,&qrear,1);
			for(i=0;temps[i];i++)
				insert(q,&qfront,&qrear,temps+i,1);
		}
		for(j=qfront+1;j<qrear;j++){printf("%c,",q[j]);getch();}putchar('\n');
	}
	return num1;
}
