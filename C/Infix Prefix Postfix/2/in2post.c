#include<stdio.h>
#include<string.h>
#include<ctype.h>

char* in2post(char *s,char d[MAXSTACK])
{
	int i,dtop=0,stktop=0,temp;
	char stk[MAXSTACK],b,space=' ';
	memset(stk,'\0',20);
	memset(d,'\0',50);
	for(i=0;s[i];i++);
	for(i=0;s[i];i++)
	{
		if(isdigit(s[i]))
		{
			while(isdigit(s[i]))
			{
				push(d,&dtop,&s[i],sizeof(s[i]));
				i++;
			}
			i--;
			push(d,&dtop,&space,sizeof(space));
		}
		else if(isalpha(s[i]))
		{
			while(isalpha(s[i]))
			{
				push(d,&dtop,&s[i],sizeof(s[i]));
				i++;
			}
			i--;
			push(d,&dtop,&space,sizeof(space));
		}
		else if(isoperator(s[i]))
		{
			if(stktop==-1)
				push(stk,&stktop,&s[i],1);
			else
			{
				temp=*(char*)pop(stk,&stktop,1);
				push(stk,&stktop,&temp,1);
				while(temp!='(' && temp!='{' && temp!='[' && precedence(s[i])<=precedence(temp))
				{
					push(d,&dtop,pop(stk,&stktop,1),1);
					push(d,&dtop,&space,1);
					if(stktop>-1)
					{
						temp=*(char*)pop(stk,&stktop,1);
						push(stk,&stktop,&temp,1);
					}
					else
					{
						push(stk,&stktop,&s[i],1);
						break;
					}
				}
				if(temp=='(' || temp=='{' || temp=='[' || precedence(s[i])>precedence(temp))
					push(stk,&stktop,&s[i],1);
			}
		}
		else if(s[i]=='(' || s[i]=='{' || s[i]=='[')
			push(stk,&stktop,&s[i],1);
		else if(s[i]==')' || s[i]=='}' || s[i]==']')
		{
			temp=*(char*)pop(stk,&stktop,1);
			push(stk,&stktop,&temp,1);
			b=(s[i]==')')?'(':(s[i]=='}')?'{':'[';
			while(temp!=b)
			{
				push(d,&dtop,pop(stk,&stktop,1),1);
				push(d,&dtop,&space,1);
				temp=*(char*)pop(stk,&stktop,1);
				push(stk,&stktop,&temp,1);
			}
			pop(stk,&stktop,1);
		}
	}
	while(stktop>-1)
	{
		push(d,&dtop,pop(stk,&stktop,1),1);
		push(d,&dtop,&space,1);
	}
	return d;
}
