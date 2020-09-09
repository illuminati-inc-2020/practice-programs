#include<stdio.h>
#include<stdlib.h>

typedef struct node node;
struct node
{
	node* left;
	int data;
	node* right;
};

void inorder_r(node*);
void preorder_r(node*);
void postorder_r(node*);
node* insert_r(node*,int);
node* getnode(int);
void delete(node**,int);

int main()
{
	int data,i,choice=-1;
	node *tree=NULL;
	while(choice)
	{
		printf("\nBINARY SEARCH TREE : ");
		printf("\n1. Insert\t2. Delete\t3. Display\t0. Exit");
		printf("\n\tEnter your choice_ ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				printf("\nEnter data to be inserted : ");
				scanf("%d",&data);
				tree=insert_r(tree,data);
				break;
			case 2:
				printf("\nEnter data to be deleted : ");
				scanf("%d",&data);
				delete(&tree,data);
				break;
			case 3:
				printf("\nInorder : ");
				inorder_r(tree);
				printf("\nPreorder : ");
				preorder_r(tree);
				printf("\nPostorder : ");
				postorder_r(tree);
				break;
		}
	}
}
void inorder_r(node* root)
{
	if(root)
	{
		inorder_r(root->left);
		printf("%d ",root->data);
		inorder_r(root->right);
	}
}
void preorder_r(node* root)
{
	if(root)
	{
		printf("%d ",root->data);
		preorder_r(root->left);
		preorder_r(root->right);
	}
}
void postorder_r(node* root)
{
	if(root)
	{
		postorder_r(root->left);
		postorder_r(root->right);
		printf("%d ",root->data);
	}
}
node* insert_r(node* root,int data)
{
	if(root)
		if(data < root->data) root->left=insert_r(root->left,data);
		else if(data > root->data) root->right=insert_r(root->right,data);
		else return root;
	else root=getnode(data);
	return root;
}
node* getnode(int data)
{
	node* temp=(node*)malloc(sizeof(node));
	temp->data=data;
	temp->left=temp->right=NULL;
}

void delete(node** root,int data)
{
	node **temp,*buf,*right;
	for(temp=root;(*temp)->data!=data;)
	{
		if(data>(*temp)->data) temp=&(*temp)->right;
		else temp=&(*temp)->left;
		if(*temp==NULL) return;
	}
	right=(*temp)->right;
	buf=*temp;
	*temp=(*temp)->left;
	while(*temp)
		temp=&(*temp)->right;
	*temp=right;
	free(buf);
}
