#include<stdio.h>
#include<string.h>

int main()
{
	char s[50];
	char* in2post(char[]);
	system("clear");
	printf("\n\n\t\e[34;1mEnter an expression in infix:\e[37;1m\n\t\t");
	memset(s,'\0',50);
	scanf("%s",s);
  	printf("\n\t\e[32;1mIn postfix it is :\n\t\t%s\n\n\e[37;1m",in2post(s));
}

char* in2post(char *s)
{
	int isnum(char),isletter(char),issign(char);
	int precedence(char);
	void push(char[],int*,char);
	char pop(char[],int*);
	int i,dtop=-1,stktop=-1,max=0;
	char stk[20],d[50];
	memset(stk,'\0',20);
	memset(d,'\0',50);
	for(i=0;s[i];i++);
	s[i]=')';	
	push(stk,&stktop,'(');
	for(i=0;s[i];i++)
	{
		if(isnum(s[i]))
		{
			while(isnum(s[i]))
			{
				push(d,&dtop,s[i]);
				i++;
			}
			i--;
			push(d,&dtop,' ');
		}
		else if(isletter(s[i]))
		{
			push(d,&dtop,s[i]);
			push(d,&dtop,' ');
		}
		else if(issign(s[i]))
		{
			if(stk[stktop]=='(' || precedence(s[i])>precedence(stk[stktop]))
				push(stk,&stktop,s[i]);
			else
			{
				push(d,&dtop,pop(stk,&stktop));
				push(stk,&stktop,s[i]);
				push(d,&dtop,' ');
			}
		}
		else if(s[i]=='(')
			push(stk,&stktop,'(');
		else if(s[i]==')')
		{
			while(stk[stktop]!='(')
			{
				push(d,&dtop,pop(stk,&stktop));
				push(d,&dtop,' ');
			}
			pop(stk,&stktop);
		}
	}
	return d;
}

int isnum(char c)
{
	if(c>='0' && c<='9')	return 1;
	return 0;
}

int isletter(char c)
{
	if((c>='a' && c<='z') || (c>='A' && c<='Z'))	return 1;
	return 0;
}

int issign(char c)
{
	if(c=='+' || c=='-' || c=='/' || c=='*' || c=='^')	return 1;
	return 0;
}

void push(char stk[],int *top,char item)
{
	(*top)++;
	stk[*top]=item;
}

char pop(char stk[],int *top)
{
	char item;
	item=stk[*top];
	(*top)--;
	return item;
}

int precedence(char op)
{
	char* list="-+*/^";
	int i;
	for(i=0;list[i];i++)
		if(list[i]==op)
			return i;
}
