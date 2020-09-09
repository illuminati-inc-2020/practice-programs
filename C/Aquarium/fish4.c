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
	int i,j,k,k1,x=0,c=0;
					/*	c	=scene count
						k	=frame count		*/
	system("clear");
	while(c++>=0)
	{
		for(k=0,k1=0;k<81;k++,(k<20 || (k>30 && k<40) || (k>55 && k<70))?k1++:k1--)
		{
			system("clear");
			(k==10 || k==35)?x=15:x;
			(x>0)?x--:x;
			for(i=0;i<x;i++)
				printf("\n");
			if(k>12 && k<25)
			{
				printf("%s",(c%4==0)?"             ":(c%4==1)?"                         ":(c%4==2)?"                                                     ":"   ");
				printf("\e[36;1m%s",(k%5==0||k%5==4)?"o  ":(k%5==1||k%5==3)?" o ":"  o");
			}
			if(k>40 && k<55)
			{
				printf("%s",(c%4==0)?"         ":(c%4==1)?"                                                                                     ":(c%4==2)?"            ":"                                  ");
				printf("\e[36;1m%s",(k%5==0||k%5==4)?"o  ":(k%5==1||k%5==3)?" o ":"  o");
			}
			for(i=0;i<k1-x;i++)
				printf("\n");
			for(i=0;i<6;i++)
			{
				for(j=0;j<=k;j++)
					printf(" ");
				printf("%s\n",fish[i]);
			}
			for(i=0;i<24-k1;i++)
				printf("\n");
			for(i=0;i<6;i++)
			{
				printf("\e[32;1m");
				printf("%s\n",(k%4<=1)?weed1[i]:weed2[i]);
			}
			usleep(100000);
		}
	}
}
