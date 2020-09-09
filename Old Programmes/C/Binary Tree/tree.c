#include<stdio.h>
#include<stdlib.h>
#include"stack.h"
#include"queue.h"

typedef struct node node;
struct node
{
	node* left;
	int data;
	node* right;
};

node* insert_r(node*,int);
void inorder_r(node*);
void preorder_r(node*);
void postorder_r(node*);
void levelorder(node*);
void inorder(node*);
void preorder(node*);
void postorder(node*);
int height(node*);
int width(node*);
void insert(node**,int);
node* getnode(int);
void delete(node**,int);
void mirror(node**);
void printtree(node*);
void create_tree_in_pre(node**,int[],int,int,int[],int,int);
void create_tree_in_post(node**,int[],int,int,int[],int,int);
void create_tree_pre_post(node**,int[],int,int,int[],int,int);

int main()
{
	node* X=NULL;
	int data,c;
	while(1)
	{
		system("clear");
		printf("BINARY TREE\n");
		printf("\n1.  Insert (Recursive)");
		printf("\n2.  Insert");
		printf("\n3.  Delete");
		printf("\n4.  Print tree");
		printf("\n5.  Traverse Level-order ");
		printf("\n6.  Traverse Inorder");
		printf("\n7.  Traverse Preorder");
		printf("\n8.  Traverse Postorder");
		printf("\n9.  Swap left and right childs");
		printf("\n10. Create tree from inorder and preorder");
		printf("\n11. Create tree from inorder and postorder");
		printf("\n12. Create tree from preorder and postorder");
		printf("\n0.  Exit");
		printf("\n\nData :\nInorder\t\t: ");
		inorder_r(X);
		printf("\nPreorder\t: ");
		preorder_r(X);
		printf("\nPostorder\t: ");
		postorder_r(X);
		printf("\nHeight\t: %d",height(X));
		printf("\nWidth\t: %d",width(X));
		printf("\n\nEnter your choice_ ");
		scanf("%d",&c);
		switch(c)
		{
			case 0:
				exit(0);
			case 1:
				printf("Enter data : ");
				scanf("%d",&data);
				X=insert_r(X,data);
				break;
			case 2:
				printf("Enter data : ");
				scanf("%d",&data);
				insert(&X,data);
				break;
			case 3:
				printf("Enter data : ");
				scanf("%d",&data);
				delete(&X,data);
				break;
			case 4:
				printtree(X);
				getchar();getchar();
				break;
			case 5:
				levelorder(X);
				getchar();getchar();
				break;
			case 6:
				inorder(X);
				getchar();getchar();
				break;
			case 7:
				preorder(X);
				getchar();getchar();
				break;
			case 8:
				postorder(X);
				getchar();getchar();
				break;
			case 9:
				mirror(&X);
				break;
			case 10:
				{
					int i,n,in[100],pre[100];
					printf("Enter number of elements : ");
					scanf("%d",&n);
					printf("Enter elements in inorder : ");
					for(i=0;i<n;i++) scanf("%d",&in[i]);
					printf("Enter elements in preorder : ");
					for(i=0;i<n;i++) scanf("%d",&pre[i]);
					create_tree_in_pre(&X,in,0,n-1,pre,0,n-1);
				}
				break;
			case 11:
				{
					int i,n,in[100],post[100];
					printf("Enter number of elements : ");
					scanf("%d",&n);
					printf("Enter elements in inorder : ");
					for(i=0;i<n;i++) scanf("%d",&in[i]);
					printf("Enter elements in postorder : ");
					for(i=0;i<n;i++) scanf("%d",&post[i]);
					create_tree_in_post(&X,in,0,n-1,post,0,n-1);
				}
				break;
			case 12:
				{
					int i,n,pre[100],post[100];
					printf("Enter number of elements : ");
					scanf("%d",&n);
					printf("Enter elements in preorder : ");
					for(i=0;i<n;i++) scanf("%d",&pre[i]);
					printf("Enter elements in postorder : ");
					for(i=0;i<n;i++) scanf("%d",&post[i]);
					create_tree_pre_post(&X,pre,0,n-1,post,0,n-1);
				}
				break;
			default:
				printf("Wrong choice");
				getchar();getchar();
				break;
		}
	}
}

node* insert_r(node* root,int data)
{
	if(root)
		if(data < root->data) root->left=insert_r(root->left,data);
		else if(data > root->data) root->right=insert_r(root->right,data);
		else return root;
	else
	{
		root=(node*)malloc(sizeof(node));
		root->data=data;
		root->left=root->right=NULL;
	}
	return root;
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
void levelorder(node* root)
{
	node *queue[MAXQUEUE],*temp;
	CREATEQUEUE(queue);
	if(root)
	{
		printf("%d ",root->data);
		ENQUEUE(queue,root->left);
		ENQUEUE(queue,root->right);
		while(!EMPTY(queue))
		{
			temp=DEQUEUE(queue);
			printf("%d ",temp->data);
			if(temp->left) ENQUEUE(queue,temp->left);
			if(temp->right) ENQUEUE(queue,temp->right);
		}
	}
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

int height(node* root)
{
	node *queue[100],*temp;
	int front=-1,rear=-1,c=-1,c1=0;
	if(root)
	{
		queue[++rear]=root;
		queue[++rear]=NULL;
		c=-1;
		while(1)
		{
			temp=queue[++front];
			if(!temp)
			{
				queue[++rear]=NULL;
				c++;
				if(c1==0) break;
				c1=0;
			}
			else
			{
				if(temp->left)
				{
					c1++;
					queue[++rear]=temp->left;
				}
				if(temp->right)
				{
					c1++;
					queue[++rear]=temp->right;
				}
			}
		}
	}
	return c;
}

int width(node* root)
{
	node *queue[100],*temp;
	int front=-1,rear=-1,c=0,c1=0;
	if(root)
	{
		queue[++rear]=root;
		queue[++rear]=NULL;
		c=1;
		while(1)
		{
			temp=queue[++front];
			if(!temp)
			{
				queue[++rear]=NULL;
				c=(c1>c)?c1:c; 
				if(c1==0) break;
				c1=0;
			}
			else
			{
				if(temp->left)
				{
					c1++;
					queue[++rear]=temp->left;
				}
				if(temp->right)
				{
					c1++;
					queue[++rear]=temp->right;
				}
			}
		}
	}
	return c;
}

void insert(node** root,int data)
{
	node *t,*t1;
	if(!(*root))
		*root=getnode(data);
	else
	{
		while(t)
		{
			t1=t;
			if(data<t->data) t=t->left;
			else if(data>t->data) t=t->right;
			else return;
		}
		if(data<t1->data) t1->left=getnode(data);
		else t1->right=getnode(data);
	}
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

void mirror(node **root)
{
	node *q[MAXQUEUE],*temp,*temp1;
	if(root)
	{
		CREATEQUEUE(q);
		ENQUEUE(q,*root);
		while(!EMPTY(q))
		{
			temp=DEQUEUE(q);
			if(temp)
			{
				temp1=temp->left;
				temp->left=temp->right;
				temp->right=temp1;
				ENQUEUE(q,temp->left);
				ENQUEUE(q,temp->right);
			}
		}
	}
}

void printtree(node *root)
{
	node *queue[MAXQUEUE],*temp;
	int flag=0,h=height(root),w=1,i;
	for(i=0;i<=h;i++) w*=2;
	CREATEQUEUE(queue);
	if(root)
	{
		for(i=0;i<w;i++) putchar(' ');
		printf("%d\n",root->data);
		w/=2;
		ENQUEUE(queue,root->left);
		ENQUEUE(queue,root->right);
		ENQUEUE(queue,(node*)(-1));
		while(!EMPTY(queue))
		{
			for(i=0;i<w;i++) putchar(' ');
			temp=DEQUEUE(queue);
			if(temp==NULL)
			{
				printf("%-*c",w,' ');
				ENQUEUE(queue,NULL);
				ENQUEUE(queue,NULL);
			}
			else if(temp==(node*)(-1))
			{
				w/=2;
				if(flag==0) break;
				flag=0;
				printf("\n");
				ENQUEUE(queue,(node*)(-1));
			}
			else
			{
				flag=1;
				printf("%-*d",w,temp->data);
				ENQUEUE(queue,temp->left);
				ENQUEUE(queue,temp->right);
			}
		}
	}

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

void create_tree_in_post(node **root,int in[],int ilb,int iub,int post[],int plb,int pub)
{
	int i,root_data;
	if(iub>=ilb)
	{
		*root=getnode(root_data=post[pub]);
		for(i=ilb;i<=iub;i++)
		       if(in[i]==root_data) break;
		create_tree_in_post(&(*root)->left,in,ilb,i-1,post,plb,i-ilb+plb-1);
		create_tree_in_post(&(*root)->right,in,i+1,iub,post,i-ilb+plb,pub-1);
	}
}

void create_tree_pre_post(node **root,int pre[],int prlb,int prub,int post[],int polb,int poub)
{
	int i,j,right_root,left_root;
	if(prub>=prlb)
	{
		*root=getnode(pre[prlb]);
		if(prub>prlb)
		{
			left_root=pre[prlb+1];
			right_root=post[poub-1];
			for(i=polb;i<=poub-1;i++)
			       if(post[i]==left_root) break;
			for(j=prlb+1;j<=prub;j++)
			       if(pre[j]==right_root) break;
			create_tree_pre_post(&(*root)->left,pre,prlb+1,j-1,post,polb,i);
			create_tree_pre_post(&(*root)->right,pre,j,prub,post,i+1,poub-1);
		}
	}
}
