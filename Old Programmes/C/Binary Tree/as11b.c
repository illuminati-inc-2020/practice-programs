#include<stdio.h>
#include<stdlib.h>
#include"queue.h"

typedef struct node node;
struct node
{
	node* left;
	int data;
	node* right;
};

node* getnode(int);
void create_tree_in_pre(node**,int[],int,int,int[],int,int);
int height(node*);
int width(node*);

int main(int argc,char* argv[])
{
	FILE *fp;
	int n,in[100],pre[100],i;
	node *tree=NULL;
	if(argc!=2)
	{
		fprintf(stderr,"error : missing filename\n");
		return;
	}
	fp=fopen(argv[1],"r");
	fscanf(fp,"%d",&n);
	printf("Input :\n\tInorder : ");
	for(i=0;i<n;i++)
	{
		fscanf(fp,"%d",&in[i]);
		printf("%d ",in[i]);
	}
	printf("\n\tPreorder : ");
	for(i=0;i<n;i++)
	{
		fscanf(fp,"%d",&pre[i]);
		printf("%d ",pre[i]);
	}
	create_tree_in_pre(&tree,in,0,n-1,pre,0,n-1);
	printf("\nOutput :");
	printf("\n\tHeight : %d\n\tWidth : %d\n",height(tree),width(tree));
	fclose(fp);
}

int height(node* root)
{
	node *queue[MAXQUEUE],*temp;
	int front=-1,rear=-1,c=-1,c1=0;
	CREATEQUEUE(queue);
	if(root)
	{
		ENQUEUE(queue,root);
		ENQUEUE(queue,NULL);
		c=-1;
		while(1)
		{
			temp=DEQUEUE(queue);
			if(!temp)
			{
				ENQUEUE(queue,NULL);
				c++;
				if(c1==0) break;
				c1=0;
			}
			else
			{
				if(temp->left)
				{
					c1++;
					ENQUEUE(queue,temp->left);
				}
				if(temp->right)
				{
					c1++;
					ENQUEUE(queue,temp->right);
				}
			}
		}
	}
	return c;
}

int width(node* root)
{
	node *queue[MAXQUEUE],*temp;
	int front=-1,rear=-1,c=0,c1=0;
	CREATEQUEUE(queue);
	if(root)
	{
		ENQUEUE(queue,root);
		ENQUEUE(queue,NULL);
		c=1;
		while(1)
		{
			temp=DEQUEUE(queue);
			if(!temp)
			{
				ENQUEUE(queue,NULL);
				c=(c1>c)?c1:c; 
				if(c1==0) break;
				c1=0;
			}
			else
			{
				if(temp->left)
				{
					c1++;
					ENQUEUE(queue,temp->left);
				}
				if(temp->right)
				{
					c1++;
					ENQUEUE(queue,temp->right);
				}
			}
		}
	}
	return c;
}

node* getnode(int data)
{
	node* temp=(node*)malloc(sizeof(node));
	temp->data=data;
	temp->left=temp->right=NULL;
}

void create_tree_in_pre(node **root,int in[],int ilb,int iub,int pre[],int plb,int pub)
{
	int i,root_data;
	if(iub>=ilb)
	{
		*root=getnode(root_data=pre[plb]);
		for(i=ilb;i<=iub;i++)
		       if(in[i]==root_data) break;
		create_tree_in_pre(&(*root)->left,in,ilb,i-1,pre,plb+1,i-ilb+plb);
		create_tree_in_pre(&(*root)->right,in,i+1,iub,pre,i+1-ilb+plb,pub);
	}
}
