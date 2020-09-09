#include <stdio.h>
#include <unistd.h>
#include <string.h>
main()
{
	char msg[100];
	pid_t pid,x;
	strcpy(msg,"Program started...\n");
	write(1,msg,strlen(msg));
	pid=getpid();
	sprintf(msg,"PID: %ld\n",pid);
	write(1,msg,strlen(msg));
	x=fork();
	if(x<0)
	{
		perror("Fork error");
	}
	pid=getpid();
	sprintf(msg,"PID: %ld (%ld)\n",pid,x);
	write(1,msg,strlen(msg));
}
