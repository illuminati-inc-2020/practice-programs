#include<stdio.h>
#include<stdlib.h>
#include"stack.h"

typedef struct node node;
struct node
{
	node* left;
	int data;
	node* right;
};

void inorder(node*);
void preorder(node*);
void postorder(node*);
node* getnode(int);
void create_tree_in_pre(node**,int[],int,int,int[],int,int);

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
	printf("\nOutput :\n\tInorder : ");
	inorder(tree);
	printf("\n\tPreorder : ");
	preorder(tree);
	printf("\n\tPostorder : ");
	postorder(tree);
	printf("\n");
	fclose(fp);
}

void inorder(node* root)
{
	node *temp=root,*stack[MAXSTACK];
	CREATESTACK(stack);
	while(1)
	{
		while(temp)
		{
			PUSH(stack,temp);
			temp=temp->left;
		}
		if(!UNDERFLOW(stack))
		{
			temp=POP(stack);
			printf("%d ",temp->data);
			temp=temp->right;
		}
		else break;
	}
}
void preorder(node* root)
{
	node *temp=root,*stack[MAXSTACK];
	CREATESTACK(stack);
	while(1)
	{
		while(temp)
		{
			PUSH(stack,temp);
			printf("%d ",temp->data);
			temp=temp->left;
		}
		if(!UNDERFLOW(stack))
		{
			temp=POP(stack);
			temp=temp->right;
		}
		else break;
	}
}
void postorder(node* root)
{
	node *temp=root,*stk1[MAXSTACK],*stk2[MAXSTACK];
	CREATESTACK(stk1);
	CREATESTACK(stk2);
	while(1)
	{
		while(temp)
		{
			PUSH(stk1,temp);
			temp=temp->left;
		}
		if(!UNDERFLOW(stk1))
		{
			temp=POP(stk1);
			PUSH(stk2,temp);
			temp=temp->right;
		}
		else break;
		if(!temp)
			while(!UNDERFLOW(stk2))
				printf("%d ",POP(stk2)->data);
	}
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
