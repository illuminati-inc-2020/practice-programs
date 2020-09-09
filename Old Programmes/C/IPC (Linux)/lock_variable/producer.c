#include<sys/shm.h>
#include<sys/ipc.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

int critical_section(int x)
{
	getchar();
	return x+1;
}

int main()
{
	int *cnt,shmid,i,*lock,lock_id;
	char msg[20];
	if((lock_id=shmget(1000,2*sizeof(int),IPC_CREAT|0666))==-1)
	{
		perror("lock shmget() error");
		return 1;
	}
	if((lock=(int*)shmat(lock_id,NULL,0))==(int*)(-1))
	{
		perror("lock shmat() error");
		return 1;
	}
	lock[0]=lock[1]=0;
	if((shmid=shmget(3500,sizeof(int),IPC_CREAT|0666))==-1)
	{
		perror("shmget() error");
		return 1;
	}
	if((cnt=(int*)shmat(shmid,NULL,0))==(int*)(-1))
	{
		perror("shmat() error");
		return 1;
	}
	*cnt=0;
	while(1)
	{
		getchar();
		sprintf(msg,"read cnt=%d.....",*cnt);
		write(1,msg,strlen(msg));
		lock[0]=1;
		sprintf(msg,"\nlock={%d,%d}",lock[0],lock[1]);
		write(1,msg,strlen(msg));
		while(lock[1]==1)
		{
			write(1,".",1);
			sleep(1);
		}
		*cnt=critical_section(*cnt);
		lock[0]=0;
		sprintf(msg,"written cnt=%d\n",*cnt);
		write(1,msg,strlen(msg));
	}
}
