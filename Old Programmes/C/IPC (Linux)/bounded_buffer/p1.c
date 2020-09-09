#include<sys/shm.h>
#include<sys/ipc.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

#define BUFSIZE 10

int main()
{
	int *buffer,buffer_shmid,*cnt,cnt_shmid,i;
	char msg[20];
	if((buffer_shmid=shmget(1000,sizeof(int)*BUFSIZE,IPC_CREAT|0666))==-1)
	{
		perror("Buffer shmget() error");
		return 1;
	}
	if((buffer=(int*)shmat(buffer_shmid,NULL,0))==(int*)(-1))
	{
		perror("Buffer shmat() error");
		return 1;
	}
	if((cnt_shmid=shmget(1500,sizeof(int),IPC_CREAT|0666))==-1)
	{
		perror("Count shmget() error");
		return 1;
	}
	if((cnt=(int*)shmat(cnt_shmid,NULL,0))==(int*)(-1))
	{
		perror("Count shmat() error");
		return 1;
	}
	*cnt=0;
	while(1)
	{
		if(*cnt<BUFSIZE)
		{
			sprintf(msg,"Enter integer : ");
			write(1,msg,strlen(msg));
			scanf("%d",&i);
			if(i==-1)
			{
				sprintf(msg,"Producer process terminated\n");
				write(1,msg,strlen(msg));
				return 1;
			}
			buffer[(*cnt)++]=i;
		}
		else
		{
			sprintf(msg,"Buffer full\n");
			write(1,msg,strlen(msg));
			while(*cnt>=BUFSIZE);
		}
	}
}

