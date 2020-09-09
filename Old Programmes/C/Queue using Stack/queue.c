#include <stdio.h>
#include "stack.h"

typedef struct Queue
{
	Stack s1,s2;
}Queue;

int Insert(Queue *q,int data);
int Delete(Queue *q);
int QueueFull(Queue q);
int QueueEmpty(Queue q);
void CreateQueue(Queue *q);
void DisplayQueue(Queue *q);

int main()
{
	Queue q;
	int choice,data;
	CreateQueue(&q);
	printf("\nQueue using Stacks :");
	printf("\n1. Insert");
	printf("\n2. Delete");
	printf("\n3. Check if empty");
	printf("\n4. Check if full");
	printf("\n5. Display");
	printf("\n0. Exit");
	while(1)
	{
		printf("\nEnter your choice_");
		scanf("%d",&choice);
		switch(choice)
		{
			case 0:
				return 0;
			case 1:
				printf("Enter data : ");
				scanf("%d",&data);
				Insert(&q,data);
				break;
			case 2:
				Delete(&q);
				break;
			case 3:
				if(QueueEmpty(q))
					printf("\nQueue empty");
				else
					printf("\nQueue not empty");
				break;
			case 4:
				if(QueueFull(q))
					printf("\nQueue full");
				else
					printf("\nQueue not full");
				break;
			case 5:
				DisplayQueue(&q);
				break;
		}
	}
}

int Insert(Queue *q,int data)
{
	while(!StackUnderflow(q->s2))
		Push(&q->s1,Pop(&q->s2));
	Push(&q->s1,data);
}

int Delete(Queue *q)
{
	while(!StackUnderflow(q->s1))
		Push(&q->s2,Pop(&q->s1));
	return Pop(&q->s2);
}

int QueueFull(Queue q)
{
	return StackOverflow(q.s1)||StackOverflow(q.s2);
}

int QueueEmpty(Queue q)
{
	return StackUnderflow(q.s1)&&StackUnderflow(q.s2);
}

void CreateQueue(Queue *q)
{
	CreateStack(&q->s1);
	CreateStack(&q->s2);
}

void DisplayQueue(Queue *q)
{
	while(!StackUnderflow(q->s2))
		Push(&q->s1,Pop(&q->s2));
	DisplayStack(q->s1);
}
