#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_COUNT 20

char msg[100];

int g=10;

main()
{
	void childProcess();
	void parentProcess();
	pid_t x;
	strcpy(msg,"Program started...\n");
	write(1,msg,strlen(msg));
	x=vfork();
	if(x<0)
		perror("Fork error");
	if(x==0)
		childProcess();
	else
		parentProcess();
}

void childProcess()
{
	g++;
	sprintf(msg,"Child Value :%d\n",g);
	write(1,msg,strlen(msg));
	exit(0);
}

void parentProcess()
{
	g++;
	sprintf(msg,"Parent Value :%d\n",g);
	write(1,msg,strlen(msg));
}
