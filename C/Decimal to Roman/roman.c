#include <stdio.h>
#include <string.h>

#define MAX 5

char *toRoman(char *s,int n);

int main()
{
	char buffer[50];
	int n;
	printf("Enter a number : ");
	scanf("%d",&n);
	printf("\t= %s",toRoman(buffer,n));
   return 0;
}

char *toRoman(char *s,int n)
{
	int i;
	char one[10][5]={"","I","II","III","IV","V","VI","VII","VIII","IX"};
	char ten[10][5]={"","X","XX","XXX","XL","L","LX","LXX","LXXX","XC"};
	char hundred[10][5]={"","C","CC","CCC","CD","D","DC","DCC","DCCC","CM"};
	char thousand[10][5]={"","M","MM","MMM","","","","","",""};
	char digit[MAX];
	for(i=0;i<MAX;i++)
		digit[i]=0;
	for(i=MAX-1;n>0;i--)
	{
		digit[i]=n%10;
		n/=10;
	}
	strcpy(s,"");
	strcat(s,thousand[digit[MAX-4]]);
	strcat(s,hundred[digit[MAX-3]]);
	strcat(s,ten[digit[MAX-2]]);
	strcat(s,one[digit[MAX-1]]);
	return s;
}
