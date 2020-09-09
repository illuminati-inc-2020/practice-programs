#if !defined(_R__QUEUE_H)
#define _R__QUEUE_H

#include<stdio.h>
#include<stdlib.h>

#if!defined(MAXQUEUE)
#define MAXQUEUE 1000
#endif

void insert(char queue[],int *front,int *rear,void *item,size_t size)
{
	int i;
	if(*rear>MAXQUEUE)
	{
		printf("Queue Full");
		exit(0);
	}
	else
	{
		if(*rear==*front) *front=*rear=0;
		for(i=0;i<size;i++)
			queue[(*rear)++]=*(((char*)item)++);
	}
}

void *delete_front(char queue[],int *front,int *rear,size_t size)
{
	void *item;
	if(*rear==*front)
	{
		printf("Queue Empty");
		exit(0);
	}
	else
	{
		item=&queue[*front];
		(*front)+=size;
		return item;
	}
	return NULL;
}

void *delete_rear(char queue[],int *front,int *rear,size_t size)
{
	int i;
	if(*rear==*front)
	{
		printf("Queue Empty");
		exit(0);
	}
	else
	{
		(*rear)-=size;
		return &queue[*rear];
	}
	return NULL;
}

#endif
