#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX 100

void push(char stk[],int *top,char item);
char pop(char stk[],int *top);
char poppush(char stk[],int *top);

int isalnum_(char a);
int differ(char a,char b);
int isoperator(char a);
int isbracket(char a);

int main()
{
	system("clear");
	FILE *fp,*fpn;
	char *text,stk[MAX],stk2[MAX],last='\0';
	int i,j,top=-1,top2=-1,stktop;
	int par=0,brace=0,tabs=0,slc=0,mlc=0,newline=0;
	char cp=0,c=0,cn=0;
	fp=fopen("file1.c","r");
	fpn=fopen("file1.c","r");
	fseek(fp,0L,2);
	text=(char*)calloc(ftell(fp),sizeof(char));
	rewind(fp);
	i=0;
	cn=getc(fpn);
	while((c=getc(fp))!=EOF)
	{
		cn=getc(fpn);
		if(c=='/' && cn=='*' && mlc==0)
			mlc=1;
		else if(c=='*' && cn=='/' && mlc==1)
			mlc=0;
		else if(c=='/' && cn=='/' && slc==0)
			slc=1;
		else if(c=='\n' && slc==1)
			slc=0;
		if(slc==0 && mlc==0)
		{
			if(c=='\'' || c=='\"' || c=='\\')
			{
				stktop=poppush(stk2,&top2);
				if(stktop==c || stktop=='\\')
					pop(stk2,&top2);
				else
					push(stk2,&top2,c);
			}
			else
			{
				stktop=poppush(stk2,&top2);
				if(stktop=='\\')
					pop(stk2,&top2);
			}
			if(top2<=-1)
			{
				if(newline==1 && !isspace(c))
				{
					text[i++]='\n';
					newline=0;
				}
				if(c=='(')
					par++;
				if(c==')')
					par--;
				if(c!='\t' && ((c!=' ' && c!='\n') || !isspace(cp))) 
					text[i++]=c;
				if(par==0 && (c=='{' || c=='}' || c==';' || (c==')' && !ispunct(cn))))
				{
					newline=1;
				}
			}
			else
				text[i++]=c;
		}
		else
			text[i++]=c;
		if(newline==1)
			cp='\n';
		else
			cp=c;
	}
	printf("%s",text);
	fclose(fp);
	fclose(fpn);
	fp=fopen("file1.c","w");
	fclose(fp);
	fp=fopen("file1.c","r+");
	par=brace=tabs=slc=mlc=0;
	int angle=0,_do=0,_case=0;
	for(;*text;text++)
	{
		putc(*text,fp);	
		if(*text=='/' && text[1]=='*' && mlc==0)
			mlc=1;
		else if(*text=='*' && text[1]=='/' && mlc==1)
			mlc=0;
		else if(*text=='/' && text[1]=='/' && slc==0)
			slc=1;
		else if(*text=='\n' && slc==1)
			slc=0;
		if(slc==0 && mlc==0)
		{
			if(*text=='\'' || *text=='\"' || *text=='\\')
			{
				stktop=poppush(stk2,&top2);
				if(stktop==*text || stktop=='\\')
					pop(stk2,&top2);
				else
					push(stk2,&top2,*text);
			}
			else
			{
				if(poppush(stk2,&top2)=='\\')
					pop(stk2,&top2);
			}
			if(top2<=-1)
			{
				if(*text=='<')
				for(i=1;isalnum_(text[i]) || text[i]==' ' || text[i]=='>' || text[i]=='.';i++)
						if(text[i]=='>')
						{
							angle=1;
							break;
						}
				if(*text=='>')
					angle=0;
				if(differ(*text,text[1]))
					if(angle==0)
						putc(' ',fp);
				if(*text=='\n')
				{
					if(text[1]=='{' || text[1]=='}')
						for(i=1;i<tabs;i++)
							putc('\t',fp);
					else
						for(i=1;i<=tabs;i++)
							putc('\t',fp);
				}
				if(par==0)
				{
					if(*text=='{')
					{
						push(stk,&top,'{');
						brace++;
					}
					else if(*text=='}')
					{
						stktop=poppush(stk,&top);
						while(stktop=='t' && top>-1)
						{
							pop(stk,&top);
							tabs--;
							stktop=poppush(stk,&top);
						}
						if(stktop=='{')
							pop(stk,&top);
						brace--;
					}
					if((*text=='}' || *text==';') && top>-1)
					{
						if(!isalnum_(text[1]) && !strncmp(text+2,"else",4) && !isalnum_(text[6]))
						{
							pop(stk,&top);
							tabs--;
						}
						else
						{
							stktop=poppush(stk,&top);
							while(stktop=='t' && top>-1)
							{
								pop(stk,&top);
								tabs--;
								stktop=poppush(stk,&top);
							}
						}
					}
					else if(isalnum_(text[-1]) && *text=='(')
					{
						push(stk,&top,'t');
						tabs++;
						par++;
					}
					if(!isalnum_(*text) && !strncmp(text+1,"do",2) && !isalnum_(text[3]))
					{
						push(stk,&top,'t');
						tabs++;
						_do=1;
					}
					if(!isalnum_(text[-2]) && !strncmp(text-1,"do",2) && !isalnum_(text[1]))
						if(text[1]!='\n')
						{
							putc('\n',fp);
							for(i=1;i<tabs;i++)
								putc('\t',fp);
						}
					if(par==0 && !isalnum_(*text) && !strncmp(text+1,"struct",6) && !isalnum_(text[7]))
					{
						push(stk,&top,'t');
						tabs++;
					}
				}
				else
				{
					if(*text=='(')
						par++;
					else if(*text==')')
						par--;
				}
				stktop=poppush(stk,&top);
				if(stktop=='c' && *text=='\n')
				{
					for(i=1;text[i]!='\n';i++);
					for(i++;text[i]!='\n';i++)
						if( (!isalnum_(text[i-1]) && !strncmp(text+i,"case",4) && text[i+4]==' ') || (!isalnum_(text[i-1]) && !strncmp(text+i,"default",7) && !isalnum_(text[i+7])) || text[i]=='}')
						{
							_case=0;
							pop(stk,&top);
							tabs--;
							break;
						}
				}
				if( (!isalnum(text[-1]) && !strncmp(text,"case",4) && text[4]==' ') || (!isalnum(text[-1]) && !strncmp(text,"default",7) && !isalnum_(text[7])))
				{
					_case=1;
					push(stk,&top,'c');
					tabs++;
				}
				if(*text=='}' && text[1]=='\n' && text[2]==';')
					text++;
				if(text[-1]=='=' && *text=='{' && text[1]=='\n')
					text++;
			}
		}
	}	
	fclose(fp);
}

void push(char stk[],int *top,char item)
{
	if(*top>=MAX)
	{
		printf("Overflow");
		exit(1);
	}
	else
		stk[++(*top)]=item;
}

char pop(char stk[],int *top)
{
	if(*top<0)
	{
		printf("Underflow");
		exit(1);
	}
	else
		return stk[(*top)--];
}

char poppush(char stk[],int *top)
{
	char c;
	if(*top<=-1)
		return 0;
	c=pop(stk,top);
	push(stk,top,c);
	return c;
}

int isalnum_ (char a)
{
	if(isalnum(a) || a=='_')
		return 1;
	return 0;
}

int differ(char a,char b)
{
	if( (isalnum_(a) && (ispunct(b) && b!='_' && b!=',')) || (ispunct(a) && a!='_' && isalnum_(b)))
	  	return 1;
	if( (ispunct(a) && (b=='\'' || b=='\"' || b=='(' || b==')' || b=='[' || b==']' || b=='{' || b=='}')) || ((a=='\'' || a=='\"' || a=='(' || a==')' || a=='[' || a==']' || a=='{' || a=='}') && ispunct(a)) ) 
		return 1;
	return 0;
}

int isoperator(char a)
{
	char *s="~`!@#$%^&*_+-=:;<>?,./\\|";
	for(;*s;s++)
		if(*s==a)
			return 1;
	return 0;
}

int isbracket(char a)
{
	char *s="(){}[]";
	for(;*s;s++)
		if(*s==a)
			return 1;
	return 0;
}
