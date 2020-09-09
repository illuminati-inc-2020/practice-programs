#include<stdio.h>

int main()
{
	unsigned int key,dec;
	unsigned long long int pow=1,bin=0;
	system("clear");
	printf("\n\n\tEnter a number in decimal :   ");  
	scanf("%d",&dec);
	for(key=1;key<=1023;key*=2)
	{
		if((dec&key) == key)
			bin+=pow;
		pow*=10;
	}
	printf("\t\t( %d )base10\t= ( %u )base2\n\n\n\n\n",dec,bin);
}
