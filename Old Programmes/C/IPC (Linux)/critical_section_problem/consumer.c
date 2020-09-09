#include<sys/shm.h>
#include<sys/ipc.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

int critical_section(int x)
{
	getchar();
	return x-1;
}

int main()
{
	int *cnt,shmid,i;
	char msg[20];
	if((shmid=shmget(3500,sizeof(int),0666))==-1)
	{
		perror("shmget() error");
		return 1;
	}
	if((cnt=(int*)shmat(shmid,NULL,0))==(int*)(-1))
	{
		perror("shmat() error");
		return 1;
	}
	while(1)
	{
		sprintf(msg,"cnt=%d.....",*cnt);
		write(1,msg,strlen(msg));
		*cnt=critical_section(*cnt);
		sprintf(msg,"cnt=%d\n",*cnt);
		write(1,msg,strlen(msg));
		getchar();
	}
}

