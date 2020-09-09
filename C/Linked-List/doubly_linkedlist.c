#include<stdio.h>
#include<stdlib.h>

struct node
{
	int data;
	struct node *next, *prev;
};
typedef struct node node;

void ins_front(node**,int);
void ins_back(node**,int);
void ins_mid(node**,int,int);
void search_ins_bef(node**,int,int);
void search_ins_aft(node**,int,int);
int del_front(node**);
int del_back(node**);
int del_mid(node**,int);
void linear_search(node**,int);
void bubble_sort1(node**);
void node_swap(node**,int);
void bubble_sort2(node**);
void merge(node**,node**);
void zigzag_merge(node**,node**);
void print(node**);
int length(node**);

void getch()
{
	getchar();
	getchar();
}

int main()
{
	node **x=NULL;
	int choice=1,choice2=2,data,data2,idx,options=0,max=0,list=0,maxlist=0,i,idx2;
	while(choice2!=1)
	{
		system("cls");
		printf("\nLINKED LIST\n1.  Insert node at front\n2.  Insert node at back\n3.  Insert node at an index \n4.  Delete node at front\n5.  Delete node at back\n6.  Delete node at middle\n7.  Print\n8.  Create linked lists\n9.  Switch linked list\n10. %s\n0.  Exit\n",(options==0)?"Show advanced options":"Hide advanced options\n11. Linear Search\n12. Search a data and insert another data before it\n13. Search a data and insert another data after it",max,maxlist,list);
		if(maxlist>0)
		{
			max=length(x+list);
			printf("\tNumber of linked lists=%d\n\tLinked list accessing currently=%d\n\tNumber of nodes in current linked list=%d\n",maxlist,list,max);
		}
		printf("\nEnter your choice_");
		scanf("%d",&choice);
		if(maxlist<=0 && choice!=0 && choice!=8)
		{
			printf("First create a linked list");
			getch();
			continue;
		}
		switch(choice)
		{
			case 1:   //Insertion node at front
				printf("Enter data :   ");
				scanf("%d",&data);
				ins_front(x+list,data);
				break;
			case 2:	  //Insertion node at back
				printf("Enter data :   ");
				scanf("%d",&data);
				ins_back(x+list,data);
				break;
			case 3:   //Insertion node at an index
				printf("Enter data :   ");
				scanf("%d",&data);
				printf("Enter the index of the data before which data is to be inserted :   ");
				scanf("%d",&idx);
				if(idx<1 || idx>max+1)
				{
					printf("Wrong Index, you can enter only index %s%d",(max==0)?"":"between 1 and ",max+1);
					getch();
				}
				else
					ins_mid(x+list,data,idx);
				break;
			case 4:   //Deletion node at front
				if(max==0)
				{
					printf("There's no element to be deleted");
					getch();
				}
				else
					del_front(x+list);
				break;
			case 5:   //Deletion node at back
				if(max==0)
				{
					printf("There's no element to be deleted");
					getch();
				}
				else
					del_back(x+list);
				break;
			case 6:   //Deletion node at middle
				printf("Enter the index of the data to be deleted :   ");
				scanf("%d",&idx);
				if(idx<1 || idx>max)
					if(max==1)
					{
						printf("There's no element to be deleted");
						getch();
					}
					else
					{
						printf("Wrong Index, you can enter only index %s%d",(max==1)?"":"between 1 and ",max);
						getch();
					}
				else
					del_mid(x+list,idx);
				break;
			case 7:   //Print
				print(x+list);
				getch();
				break;
			case 8:  //Create linked list
				printf("Enter number of linked list you want to insert :   ");
				scanf("%d",&data);
				x=(node**)realloc(x,(maxlist+data)*4);
				for(i=maxlist;i<maxlist+data;i++)
					*(x+i)=NULL;
				maxlist+=data;
				break;
			case 9:  //Switch linked list
				printf("Enter index of linked list you want to access :   ");
				scanf("%d",&data);
				if(data>=maxlist || data<0)
				{
					printf("Wrong index");
					getch();
				}
				else
					list=data;
				break;
			case 10:   //Show/Hide  advanced options
				if(!options) 
					options=1;
				else 
					options=0;
				break;
			case 11:   //Linear search
				printf("Enter data :   ");
				scanf("%d",&data);
				linear_search(x+list,data);
				getch();
				break;
			case 12:  //Search and insert before a data
				printf("Enter data to be searched :   ");
				scanf("%d",&data2);
				printf("Enter data to be inserted before it :   ");
				scanf("%d",&data);
				search_ins_bef(x+list,data,data2);
				break;
			case 13:  //Search and insert after a data
				printf("Enter data to be searched :   ");
				scanf("%d",&data2);
				printf("Enter data to be inserted after it :   ");
				scanf("%d",&data);
				search_ins_aft(x+list,data,data2);
				break;
			case 0:   //Exit
				printf("\nDo you really want to exit ");
				choice2=2;
				while(choice2!=1 && choice2!=0)
				{
					printf("\n(0=no/1=yes) :   ");
					scanf("%d",&choice2);
					switch(choice2)
					{
						case '0':
							break;
						case '1':
							break;
						default:
							break;	
					}
				}
				system("clear");
				break;
			default:  //Entry of wrong choice
				printf("You have entered a wrong choice.");
				getch();
				break;
		}
	}
}

void ins_front(node **head,int data)
{
	node *temp;
	temp=(node*)malloc(sizeof(node));
	temp->data=data;
	temp->next=*head;
	*head=temp;
}

void ins_back(node **head,int data)
{
	node *temp,**temp1;
	temp=(node*)malloc(sizeof(node));
	temp->data=data;
	temp->next=NULL;
	for(temp1=head;*temp1!=NULL;temp1=&(*temp1)->next);
	*temp1=temp;
}

void ins_mid(node **head,int data,int idx)
{
	node *temp,**temp1;
	int i;
	temp=(node*)malloc(sizeof(node));
	temp->data=data;
	for(temp1=head,i=1;i<idx;temp1=&(*temp1)->next,i++);
	temp->next=*temp1;
	*temp1=temp;
}

void search_ins_bef(node **head,int data,int data2)
{
	node *newnode, *temp;
	int nsearch=0;
	newnode=(node*)malloc(sizeof(node));
	newnode->data=data;
	for(temp=*head;temp;temp=temp->next)
		if(temp->data==data2)
			nsearch++;
	printf("%d match(s) found\n", nsearch);
	if(nsearch>0)
	{
		int i=0, pos=0;
		if(nsearch>1)
		{
			printf("Enter the position to be inserted before : ");
			scanf("%d", &pos);
		}
		for(;i<pos;head=&(*head)->next,i++)
			if((*head)->data==data2)
				i++;
		newnode->next=*head;
		*head=newnode;
	}
	getchar();
}

void search_ins_aft(node **head,int data,int data2)
{
	node *newnode,*temp;
	int nsearch=0;
	newnode=(node*)malloc(sizeof(node));
	newnode->data=data;
	for(temp=*head;temp;temp=temp->next)
		if(temp->data==data2)
			nsearch++;
	printf("%d match(s) found\n", nsearch);
	if(nsearch>0)
	{
		int i=0, pos=0;
		if(nsearch>1)
		{
			printf("Enter the position to be inserted before : ");
			scanf("%d", &pos);
		}
		for(;i<pos;head=&(*head)->next,i++)
			if((*head)->data==data2)
				i++;
		newnode->next=(*head)->next;
		(*head)->next=newnode;
	}
	getchar();
}

int del_front(node **head)
{
	node *temp,*temp1;
	int buf;
	temp1=*head;
	*head=(*head)->next;
	buf=temp1->data;
	free(temp1);
	return buf;
}

int del_back(node **head)
{
	node **temp,*temp1;
	int buf;
	for(temp=head;(*temp)->next!=NULL;temp=&(*temp)->next);
	temp1=*temp;
	*temp=NULL;
	buf=temp1->data;
	free(temp1);
	return buf;
}

int del_mid(node **head,int idx)
{
	node *temp,**temp1;
	int i,buf;
	for(temp1=head,i=1;i<idx;temp1=&(*temp1)->next,i++);
	temp=*temp1;
	*temp1=(*temp1)->next;
	buf=temp->data;
	free(temp);
	return buf;
}

void linear_search(node **head,int data)
{
	node *temp;
	for(temp=*head;temp!=NULL;temp=temp->next)
		if(temp->data==data)
		{
			printf("Data found");
			return;
		}
	printf("Data not found");
}

void print(node **head)
{
	node *temp;
	int i=1;
	printf("\t\tIndex\t\tData\n\n");
	for(temp=*head;temp;temp=temp->next,i++)
	{
		printf("\t\t%d->\t\t%d\n",i,temp->data);
	}
}

int length(node **head)
{
	node *temp;
	int max=0;
	for(temp=*head;temp;temp=temp->next)
		max++;
	return max;

}
