#include<stdio.h>

void printnum(int i);

int main()
{
	unsigned long long int key,dec;
	unsigned long long int pow=1,bin[5];
	int i,x;
	system("clear");
	for(i=0;i<5;i++) bin[i]=0;
	printf("\n\n\t\tEnter a number in decimal :   ");  
	scanf("%d",&dec);
	i=0;
	for(key=1,x=0;i<3;key*=2,x++)
	{
		if(x%10==0 && x)
		{
			pow=1;
			i++;
		}
		if((dec&key) == key)
			bin[i]+=pow;
		pow*=10;
	}
	printf("\n\t\t( %d )base10 = ( ",dec);
	for(i=4;bin[i]==0;i--);
	printf("%d",bin[i]);	
	for(i--;i>=0;i--) 
		printnum(bin[i]);
	printf(" )base2");
	printf("\n\n");
}

void printnum(int i)
{
	int x,len,pow;
	for(len=0,pow=1;len<10;len++,pow*=10)
		if(i/pow==0)
			break;
	for(x=1;x<=10-len;x++)
		printf("0");
	printf("%d",i);
}
