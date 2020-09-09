#ifndef __LINKED_LIST_H
#define __LINKED_LIST_H

#include<stdio.h>
#include<stdlib.h>

struct node				//Structure for a node of linked list
{
	int data;
	struct node *next;
};
struct linked_list			//Structure for a linked list
{
	struct node **head;
	int len;
};

typedef struct node node;
typedef struct linked_list list;

void ins(list*,int,int);
int del(list*,int);
void linear_search(list,int);
void print(list,int,int);
list* createlist(list*);

list* createlist(list *X)			//Create linked list at list 'X'
{
	X=(list*)malloc(sizeof(list));
	X->head=(node**)malloc(sizeof(node*));
	*(X->head)=NULL;
	return X;				//Returns intialized list
}

void ins(list *X,int data,int idx)		//Insert 'data' in list 'X' at 'idx' position
{
	node *temp,**temp1;
	int i;
	temp=(node*)malloc(sizeof(node));
	temp->data=data;
	for(temp1=X->head,i=0;i<idx;temp1=&(*temp1)->next,i++);
	temp->next=*temp1;
	*temp1=temp;
	(X->len)++;
}

int del(list *X,int idx)			//Delete node at 'idx' in list 'X'
{
	node *temp,**temp1;
	int i,buf;
	for(temp1=X->head,i=1;i<idx;temp1=&(*temp1)->next,i++);
	temp=*temp1;
	*temp1=(*temp1)->next;
	buf=temp->data;
	free(temp);
	(X->len)--;
	return buf;				//Returns deleted data
}

void linear_search(list X,int data)		//Linear search of a 'data' in linked list 'X'
{
	node *temp;
	char found=0;
	int i=1;
	for(temp=*(X.head);temp!=NULL;temp=temp->next,i++)
	{
		if(temp->data==data)
		{
			if(found)
				printf(",%d",i);
			else
			{
				found=1;
				printf("Data found at position(s) %d",i);
			}
		}
	}
	if(!found)
		printf("Data not found");
}

void print(list X,int lb,int ub)		//Print linked list 'X' from lower bound 'lb' to upper bound 'ub'
{
	node *temp;
	int i=1;
	printf("\t\tIndex\t\tData\n\n");
	for(temp=*(X.head);i<=ub && temp;temp=temp->next,i++)
		if(i>=lb)
			printf("\t\t%d->\t\t%d\n",i,temp->data);
}

#endif
