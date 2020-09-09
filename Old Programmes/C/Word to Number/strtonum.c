#include <stdio.h>
#include <string.h>
#include <ctype.h>

int toNum(char*); 
char *getWord(char*,char**);

int main()
{
	char s[100];
	printf("Enter a number in word : ");
	scanf("%[^\n]",s);
	printf("\t=%d",toNum(s));
   return 0;
}

int toNum(char *s)
{
	int i=0,x,y;
	char buffer[20];
	char one[][6]={"","one","two","three","four","five","six","seven","eight","nine"};
	char ten[][8]={"","ten","twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};
	char eleven[][10]={"ten","eleven","twelve","thirteen","forteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
	y=x=0;
	while(s[0]!='\0')
	{
		getWord(buffer,&s);
		if(strcmp(buffer,"thousand")==0)
		{
			y+=x*1000;
			getWord(buffer,&s);
		}
		else if(strcmp(buffer,"hundred")==0)
		{
			y+=x*100;
			getWord(buffer,&s);
		}
		else
		{
			y+=x;
		}
		x=-1;
		for(i=0;i<10;i++)
			if(strcmp(buffer,eleven[i])==0)
				x=10+i;
		if(x==-1)
		{
			x=0;
			for(i=0;i<10;i++)
				if(strcmp(buffer,ten[i])==0)
					x=i*10;
			if(x!=0)
				getWord(buffer,&s);
			for(i=0;i<10;i++)
				if(strcmp(buffer,one[i])==0)
					x+=i;
		}
	}
   y+=x;
	return y;
}

char *getWord(char *buffer,char **s)
{
	int i;
	for(i=0;!isspace(**s)&&**s!='\0';(*s)++)
		buffer[i++]=**s;
	buffer[i]='\0';
	while(isspace(**s)&&**s!='\0')
		(*s)++;
	return buffer;
}