#include<stdio.h>
#include<stdlib.h>

struct node
{
	int data;
	struct node *next;
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
		system("clear");
		printf("\nLINKED LIST\e[35;1m\n1.  Insert node at front\n2.  Insert node at back\n3.  Insert node at an index \n4.  Delete node at front\n5.  Delete node at back\n6.  Delete node at middle\n7.  Print\n8.  Create linked lists\n9.  Switch linked list\n10. %s\n0.  Exit\n",(options==0)?"Show advanced options":"Hide advanced options\n11. Linear Search\n12. Bubble sort using data swap\n13. Swap adjacent nodes\n14. Bubble sort using node swap\n15. Clear linked list\n16. Search a data and insert another data before it\n17. Search a data and insert another data after it\n18. Merge\n19. Zigzag Merge",max,maxlist,list);
/*		if(maxlist>0)
		{
			max=length(x+list);
			printf("\t\e[32;1mNumber of linked lists=\e[37;1m%d\n\t\e[32;1mLinked list accessing currently=\e[37;1m%d\n\t\e[32;1mNumber of nodes in current linked list=\e[37;1m%d\n",maxlist,list,max);
		}
*/		printf("\n\e[34;1mEnter your choice_\e[37;1m");
		scanf("%d",&choice);
		if(maxlist<=0 && choice!=0 && choice!=8)
		{
			printf("\e[31;1mFirst create a linked list");
			getch();
			continue;
		}
		switch(choice)
		{
			case 1:   //Insertion node at front
				printf("\e[32;1mEnter data :   \e[37;1m");
				scanf("%d",&data);
				ins_front(x+list,data);
				break;
			case 2:	  //Insertion node at back
				printf("\e[32;1mEnter data :   \e[37;1m");
				scanf("%d",&data);
				ins_back(x+list,data);
				break;
			case 3:   //Insertion node at an index
				printf("\e[32;1mEnter data :   \e[37;1m");
				scanf("%d",&data);
				printf("\e[32;1mEnter the index of the data before which data is to be inserted :   \e[37;1m");
				scanf("%d",&idx);
				if(idx<1 || idx>max+1)
				{
					printf("\e[31;1mWrong Index, you can enter only index %s%d",(max==0)?"":"between 1 and ",max+1);
					getch();
				}
				else
					ins_mid(x+list,data,idx);
				break;
			case 4:   //Deletion node at front
				if(max==0)
				{
					printf("\e[31;1mThere's no element to be deleted");
					getch();
				}
				else
					del_front(x+list);
				break;
			case 5:   //Deletion node at back
				/*if(max==0)
				{
					printf("\e[31;1mThere's no element to be deleted");
					getch();
				}
				else*/
					del_back(x+list);
				break;
			case 6:   //Deletion node at middle
				printf("\e[32;1mEnter the index of the data to be deleted :   \e[37;1m");
				scanf("%d",&idx);
				if(idx<1 || idx>max)
					if(max==1)
					{
						printf("\e[31;1mThere's no element to be deleted");
						getch();
					}
					else
					{
						printf("\e[31;1mWrong Index, you can enter only index %s%d",(max==1)?"":"between 1 and ",max);
						getch();
					}
				else
					del_mid(x+list,idx);
				break;
			case 7:   //Print
				if(*x!=NULL)
					print(x+list);
				getch();
				break;
			case 8:  //Create linked list
				printf("\e[32;1mEnter number of linked list you want to insert :   \e[37;1m");
				scanf("%d",&data);
				x=(node**)realloc(x,(maxlist+data)*4);
				for(i=maxlist;i<maxlist+data;i++)
					*(x+i)=NULL;
				maxlist+=data;
				break;
			case 9:  //Switch linked list
				printf("\e[32;1mEnter index of linked list you want to access :   \e[37;1m");
				scanf("%d",&data);
				if(data>=maxlist || data<0)
				{
					printf("\e[31;1mWrong index");
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
				printf("\e[32;1mEnter data :   \e[37;1m");
				scanf("%d",&data);
				linear_search(x+list,data);
				getch();
				break;
			case 12:  //Bubble Sort using data swap
				bubble_sort1(x+list);
				break;
			case 13:  //Swap adjacent nodes
				printf("\e[32;1mEnter the index of the first data to be swapped :   \e[37;1m");
				scanf("%d",&idx);
				if(idx<1 || idx>=max)
					if(max<=1)
					{
						printf("\e[31;1mThere's too few element to be swapped");
						getch();
					}
					else
					{
						printf("\e[31;1mWrong Index, you can enter only index %s%d",(max==2)?"":"between 1 and ",max-1);
						getch();
					}
				else
					node_swap(x+list,idx);
				break;
			case 14:  //Bubble sort using node swap
				bubble_sort2(x+list);
				break;
			case 15:  //Clear linked list
				printf("\e[32;1mEnter index of linked list you want to clear :   \e[37;1m");
				scanf("%d",&idx);
				if(idx>=maxlist || idx<0)
				{
					printf("\e[31;1mWrong index");
					getch();
				}
				else
				{
					for(i=1;i<maxlist;i++)
						del_back(x+idx);
					*(x+idx)=NULL;
				}
				break;
			case 16:  //Search and insert before a data
				printf("\e[32;1mEnter data to be searched :   \e[37;1m");
				scanf("%d",&data2);
				printf("\e[32;1mEnter data to be inserted before it :   \e[37;1m");
				scanf("%d",&data);
				search_ins_bef(x+list,data,data2);
				break;
			case 17:  //Search and insert after a data
				printf("\e[32;1mEnter data to be searched :   \e[37;1m");
				scanf("%d",&data2);
				printf("\e[32;1mEnter data to be inserted after it :   \e[37;1m");
				scanf("%d",&data);
				search_ins_aft(x+list,data,data2);
				break;
			case 18:  //Merge
				printf("\e[32;1mEnter index of the first linked list :   \e[37;1m");
				scanf("%d",&idx);
				printf("\e[32;1mEnter index of the second linked list :   \e[37;1m");
				scanf("%d",&idx2);
				if(idx>=maxlist || idx<0 || idx2>=maxlist || idx2<0 || idx==idx2)
				{
					printf("\e[31;1mWrong index or same index");
					getch();
				}
				else
					merge(x+idx,x+idx2);
				break;
			case 19:  //Zigzag merge
				printf("\e[32;1mEnter index of the first linked list :   \e[37;1m");
				scanf("%d",&idx);
				printf("\e[32;1mEnter index of the second linked list :   \e[37;1m");
				scanf("%d",&idx2);
				if(idx>=maxlist || idx<0 || idx2>=maxlist || idx2<0 || idx==idx2)
				{
					printf("\e[31;1mWrong index or same index");
					getch();
				}
				else
					zigzag_merge(x+idx,x+idx2);
				break;
			case 0:   //Exit
				printf("\n\e[34;1mDo you really want to exit ");
				choice2=2;
				while(choice2!=1 && choice2!=0)
				{
					printf("\n\e[34;1m(0=no/1=yes) :   \e[37;1m");
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
				printf("\e[31;1mYou have entered a wrong choice.");
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
	if(*head==NULL)
	{
		temp->next=temp;
		*head=temp;
	}
	else
	{
		temp->next=(*head)->next;
		(*head)->next=temp;
	}
}

void ins_back(node **head,int data)
{
	node *temp;
	temp=(node*)malloc(sizeof(node));
	temp->data=data;
	temp->next=temp;
	if(*head==NULL)
		*head=temp;
	else
	{
		temp->next=(*head)->next;
		(*head)->next=temp;
		*head=temp;
	}
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
	node *temp;
	int flag=0;
	temp=(node*)malloc(sizeof(node));
	temp->data=data;
	for(;*head;head=&(*head)->next)
		if((*head)->data==data2)
		{
			flag=1;
			break;
		}
	if(flag==0)
	{
		printf("\e[31;1mData not found");
		getchar();
		return;
	}
	temp->next=*head;
	*head=temp;
}

void search_ins_aft(node **head,int data,int data2)
{
	node *temp,**temp1;
	int flag=0;
	temp=(node*)malloc(sizeof(node));
	temp->data=data;
	for(;*temp1;temp1=&(*temp1)->next)
		if((*temp1)->data==data2)
		{
			flag=1;
			break;
		}
	if(flag==0)
	{
		printf("\e[31;1mData not found");
		getch();
		return;
	}
	temp->next=(*temp1)->next;
	(*temp1)->next=temp;

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
	node *temp1;
	int buf;
	for(; (*head)->next!=NULL;*head=(*head)->next);
	temp1=(*head)->next;
	(*head)->next=(*head)->next->next;
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
			printf("\e[34;1mData found");
			return;
		}
	printf("\e[31;1mData not found");
}

void bubble_sort1(node **head)
{
	node *temp,**temp1;
	int i,j,buffer,max=length(head);
	for(i=0;i<max-1;i++)
		for(temp=*head,j=0;j<max-i-1;temp=temp->next,j++)
			if(temp->data > temp->next->data)
			{
				buffer=temp->data;
				temp->data=temp->next->data;
				temp->next->data=buffer;
			}
}

void node_swap(node **head,int idx)
{
	node *temp1;
	int i;
	for(i=1;i<idx;head=&(*head)->next,i++);
	temp1=*head;
	*head=(*head)->next;
	temp1->next=temp1->next->next;
	(*head)->next=temp1;
}

void bubble_sort2(node **head)
{
	node *temp1,**temp;
	int i,j,max=length(head);
	for(i=1;i<max;i++)
		for(temp=head,j=1;j<=max-i;temp=&(*temp)->next,j++)
			if((*temp)->data > (*temp)->next->data)
			{
				temp1=*temp;
				*temp=(*temp)->next;
				temp1->next=temp1->next->next;
				(*temp)->next=temp1;
			}
}

void merge(node **x,node **y)
{
	for(;*x;x=&(*x)->next);
	*x=*y;
}

void zigzag_merge(node **x,node **y)
{
	node  *t,*tx,*ty;
	for(tx=*x,ty=*y,t=ty->next;tx->next && ty->next;tx=ty->next,ty=t,t=t->next)
	{
		ty->next=tx->next;
		tx->next=ty;
	}	
	if(!tx->next)
		tx->next=ty;
}

void print(node **head)
{
	node *temp;
	int i=1;
	printf("\t\tIndex\t\tData\n\n");
	temp=*head;
	do
	{
		temp=temp->next;
		printf("\t\t%d->\t\t%d\n",i,temp->data);
		i++;
	}
	while(temp!=*head);
}

int length(node **head)
{
	node *temp;
	int max=0;
	for(temp=*head;temp;temp=temp->next)
		max++;
	return max;

}
