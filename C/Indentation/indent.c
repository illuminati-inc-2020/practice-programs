#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

void indent(FILE*);
int isalnum_(char);

int main(int argc,char* argv[])
{
	FILE *fp=fopen(argv[1],"r");
	printf("\n\nFile name: %s\n\n",argv[1]);
	indent(fp);
	printf("\n\n");
	fclose(fp);
}

void indent(FILE *fp)
{
	int i=0;
	char *buffer=(char*)malloc(sizeof(char));
	char c='\0',cc='\0';
	while(c!=EOF)
	{
		buffer=realloc(buffer,i*sizeof(char));
		c=getc(fp);
		if(isspace(c) && isspace(cc))
			continue;
		cc=buffer[i++]=c;
	}
	printf(buffer);
}

int isalnum_(char c)
{
	if(isalnum(c) || c=='_') return 1;
	else return 0;
}
