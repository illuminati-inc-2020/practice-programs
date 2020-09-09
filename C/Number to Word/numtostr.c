#include <stdio.h>
#include <string.h>

#define MAX 5

char *toString(char*,int);

int main()
{
	int n;
	char buffer[50];
	printf("Enter a number : ");
	scanf("%d",&n);
	printf("\t=%s",toString(buffer,n));
	return 0;
}

char *toString(char *s,int n)
{
	int i;
	char one[][6]={"","one","two","three","four","five","six","seven","eight","nine"};
	char ten[][8]={"","ten","twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};
	char eleven[][10]={"ten","eleven","twelve","thirteen","forteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
	char digit[MAX];
	if(n==0)
	{
		strcpy(s,"zero");
      return s;
	}
	for(i=0;i<MAX;i++)
		digit[i]=0;
	for(i=MAX-1;n>0;i--)
	{
		digit[i]=n%10;
		n/=10;
	}
	strcpy(s,"");
	if(digit[MAX-5]==1)
		strcat(s,eleven[digit[MAX-4]]);
	else
	{
		strcat(s,ten[digit[MAX-5]]);
		strcat(s," ");
		strcat(s,one[digit[MAX-4]]);
	}
	if(digit[MAX-5]!=0||digit[MAX-4]!=0)
		strcat(s," thousand ");
	if(digit[MAX-3]>0)
	{
		strcat(s,one[digit[MAX-3]]);
		strcat(s," hundred ");
	}
	if(digit[MAX-2]==1)
		strcat(s,eleven[digit[MAX-1]]);
	else
	{
		strcat(s,ten[digit[MAX-2]]);
		strcat(s," ");
		strcat(s,one[digit[MAX-1]]);
	}

	return s;
}