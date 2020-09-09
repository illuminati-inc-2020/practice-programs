#include<stdio.h>
#include<string.h>
#include<unistd.h>

int main()
{
	char  *fish[6]={"\e[36;1m         \\-\\    ",
		     	"\e[36;1m--\\\e[37;1m    / -`  \\  ",
	  	     	"\e[36;1m  \\ \\\e[37;1m/    \e[32;1m  (o \e[36;1m\\",
		     	"\e[36;1m  / /\e[37;1m\\  ---(   /",
		     	"\e[36;1m--/ \e[37;1m   \\ -,  /  ",
		     	"\e[36;1m        /-/     "};
	char *weed1[6]={"\e[31;1m @         @    ",
			"()        () \e[31;1m  @",
			")(\e[31;1m @ \e[32;1m     )(   ()",
			"() )( \e[31;1m  @\e[32;1m ()   )(",
			")( ()  )( )(   ()",
			"() )(  () ()   )("};
	char *weed2[6]={"\e[31;1m@         @    ",
			")(        )( \e[31;1m   @",
			"()\e[31;1m  @\e[32;1m     ()   )(",
			")( () \e[31;1m @ \e[32;1m )(   ()",
			"() )(  () ()   )(",
			")( ()  )( )(   ()"};
	int i,j,k,k1;
	system("clear");
	while(1)
	{
		for(k=0,k1=0;k<81;k++,(k<20 || (k>30 && k<40) || (k>55 && k<70))?k1++:k1--)
		{
			system("clear");
			for(i=0;i<k1;i++)
				printf("\n");
			for(i=0;i<6;i++)
			{
				for(j=0;j<=k;j++)
					printf(" ");
				printf("%s\n",fish[i]);
			}
			for(j=0;j<24-k1;j++)
				printf("\n");
			for(i=0;i<6;i++)
			{
				printf("\e[32;1m");
				printf("%s\n",(k%4<=1)?weed1[i]:weed2[i]);
			}
			usleep(200000);
		}
	}
}
