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
	int *cnt,shmid,i,*turn,turn_id,*lock,lock_id;
	char msg[20];
	if((turn_id=shmget(1000,sizeof(int),0666))==-1)
	{
		perror("turn shmget() error");
		return 1;
	}
	if((turn=(int*)shmat(turn_id,NULL,0))==(int*)(-1))
	{
		perror("turn shmat() error");
		return 1;
	}
	if((lock_id=shmget(1500,2*sizeof(int),0666))==-1)
	{
		perror("lock shmget() error");
		return 1;
	}
	if((lock=(int*)shmat(lock_id,NULL,0))==(int*)(-1))
	{
		perror("lock shmat() error");
		return 1;
	}
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
		getchar();
		sprintf(msg,"read cnt=%d.....",*cnt);
		write(1,msg,strlen(msg));
		*turn=0;
		lock[1]=1;
		sprintf(msg,"\nturn=%d,lock={%d,%d}",*turn,lock[0],lock[1]);
		write(1,msg,strlen(msg));
		while(lock[0]==1 && *turn==0)
		{
			write(1,".",1);
			sleep(1);
		}
		*cnt=critical_section(*cnt);
		lock[1]=0;
		sprintf(msg,"written cnt=%d\n",*cnt);
		write(1,msg,strlen(msg));
	}
}

