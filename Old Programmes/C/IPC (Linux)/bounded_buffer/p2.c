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
	if((buffer_shmid=shmget(1000,sizeof(int)*BUFSIZE,0666))==-1)
	{
		perror("\nBuffer shmget() error");
		return 1;
	}
	if((buffer=(int*)shmat(buffer_shmid,NULL,0))==(int*)(-1))
	{
		perror("\nBuffer shmat() error");
		return 1;
	}
	if((cnt_shmid=shmget(1500,sizeof(int),0666))==-1)
	{
		perror("\nCount shmget() error");
		return 1;
	}
	if((cnt=(int*)shmat(cnt_shmid,NULL,0))==(int *)(-1))
	{
		perror("\nCount shmat() error");
		return 1;
	}
	while(1)
	{
		sleep(1);
		if(*cnt>0)
		{
			sprintf(msg,"\nbuffer[%d]=%d",(*cnt)-1,buffer[(*cnt)-1]);
			(*cnt)--;
			write(1,msg,strlen(msg));
		}
		else
		{
			sprintf(msg,"\nBuffer empty");
			write(1,msg,strlen(msg));
			while(*cnt<=0);
		}
	}
}

