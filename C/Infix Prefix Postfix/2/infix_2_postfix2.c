#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void getch();

int main()
{
	char s[50];
	char* in2post(char[]);
	system("clear");
	printf("\n\n\n\n\t\e[34;1mEnter an expression in infix:\e[37;1m\n\t\t");
	memset(s,'\0',50);
	scanf("%[^\n]",s);
  	printf("\n\t\e[32;1mIn postfix it is :\n\t\t%s\e[37;1m",in2post(s));
	getch();
	system("clear");
}

char* in2post(char *s)
{
	int isnum(char[],int),isletter(char),issign(char),isunary(char[],int),precedence(char);
	void push(char[],int*,char);
	char pop(char[],int*);
	int i,dtop=-1,stktop=-1,max=0;
	int flag=0;			/* 0=last obj. is operator ,1= last obj. is operand */
	char stk[20],d[50];
	memset(stk,'\0',20);
	memset(d,'\0',50);
	for(i=0;s[i];i++);
	s[i]=')';	
	push(stk,&stktop,'(');
	for(i=0;s[i];i++)
	{
		if(s[i]==' ')
			continue;
		else if(isnum(s,i))
		{
			if(flag==1)
			{
				printf("\n\t\t\t\e[31;1mSYNTAX ERROR\e[37;1m");
				getch();
				system("clear");
				exit(0);
			}
			flag=1;
			while(isnum(s,i))
			{
				push(d,&dtop,s[i]);
				i++;
			}
			i--;
			push(d,&dtop,' ');
		}
		else if(isletter(s[i]))
		{
			if(flag==1)
			{
				printf("\n\t\t\t\e[31;1mSYNTAX ERROR\e[37;1m");
				getch();
				system("clear");
				exit(0);
			}
			flag=1;
			push(d,&dtop,s[i]);
			push(d,&dtop,' ');
		}
		else if(issign(s[i]))
		{
			if(isunary(s,i))
				push(d,&dtop,s[i]);
			else
			{
				if(flag==0)
				{
					printf("\n\t\t\t\e[31;1mSYNTAX ERROR\e[37;1m");
					getch();
					system("clear");
					exit(0);
				}
				flag=0;
				if(stk[stktop]=='(' || precedence(s[i])>precedence(stk[stktop]))
					push(stk,&stktop,s[i]);
				else
				{
					push(d,&dtop,pop(stk,&stktop));
					push(stk,&stktop,s[i]);
					push(d,&dtop,' ');
				}
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
		else
		{
			printf("\n\t\t\t\e[31;1m'%c' not allowed\e[37;1m\n\n\n\n\n\n",s[i]);
			exit(0);
		}
	}
	if(stktop!=-1)
	{
		printf("\n\t\t\t\e[31;1mSYNTAX ERROR\e[37;1m");
		getch();
		system("clear");
		exit(0);
	}
	return d;
}

int isnum(char s[],int i)
{
	if((s[i]>='0' && s[i]<='9') || (s[i]=='.' && s[i+1]>='0' && s[i+1]<=57))	return 1;
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
	if(*top==-1)
	{
		printf("\n\t\t\t\e[31;1mSYNTAX ERROR\e[37;1m");
		getch();
		system("clear");
		exit(0);
	}
	else
	{
		item=stk[*top];
		(*top)--;
		return item;
	}
}

int precedence(char op)
{
	char* list="-+*/^";
	int i;
	for(i=0;list[i];i++)
		if(list[i]==op)
			return i;
}

int isunary(char s[],int i)
{
	int j,k;
	if(s[i]=='+' || s[i]=='-')
	{
		for(j=i-1;s[j]==' ';j--);
		for(k=i+1;s[k]==' ';k++);
		if((!isnum(s,j) && !isletter(s[j]) && s[j]!=')') || (isnum(s,k) && isletter(s[k])))
			return 1;
	}
	return 0;
}

void getch()
{
	int x=getchar();
	x=getchar();
}
