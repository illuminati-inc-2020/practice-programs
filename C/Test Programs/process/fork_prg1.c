#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_COUNT 20

char msg[100];

main()
{
	void childProcess();
	void parentProcess();
	pid_t pid,x;
	strcpy(msg,"Program started...\n");
	write(1,msg,strlen(msg));
	x=fork();
	if(x<0)
		perror("Fork error");
	if(x==0)
		childProcess();
	else
		parentProcess();
}

void childProcess()
{
	int i;
	strcpy(msg,"Child process started.\n");
	write(1,msg,strlen(msg));
	for(i=0;i<MAX_COUNT;i++)
	{
		sprintf(msg,"Child process: %d\n",i);
		write(1,msg,strlen(msg));
	}
	strcpy(msg,"Child process terminated.\n");
	write(1,msg,strlen(msg));
}

void parentProcess()
{
	int i,status;
	strcpy(msg,"Parent process started.\n");
	write(1,msg,strlen(msg));
	for(i=0;i<MAX_COUNT;i++)
	{
		sprintf(msg,"Parent process: %d\n",i);
		write(1,msg,strlen(msg));
		if(i==MAX_COUNT/2)
			wait(&status);
	}
	strcpy(msg,"Parent process terminated.\n");
	write(1,msg,strlen(msg));
}
