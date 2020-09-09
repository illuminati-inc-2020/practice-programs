#include<stdio.h>

int main()
{
	char  *fish[6]={"\e[36;1m                 \\-\\",
		     	"\e[36;1m        --\\\e[37;1m    / -`  \\",
	  	     	"\e[36;1m          \\ \\\e[37;1m/      \e[31;1m(o\e[37;1m \\",
		     	"\e[36;1m          / /\e[37;1m\\  ---(   /",
		     	"\e[36;1m        --/\e[37;1m    \\ -,  /",
		     	"\e[36;1m                 /-/"};
	int i;
	system("clear");
	for(i=0;i<6;i++)
		printf("%s\n",fish[i]);

	
}
