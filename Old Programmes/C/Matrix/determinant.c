#include<stdio.h>

#define MAX 10

int det(int[MAX][MAX],int);
void putdet(char*,int[MAX][MAX],int);
int getdet(int[MAX][MAX]);


void getch()
{
	getchar();
	getchar();
}

int main()
{
	int choice,i,j;
	int A[MAX][MAX],mA,nA,B[MAX][MAX],mB,nB,C[MAX][MAX];
	system("clear");
	mA=getdet(A);
	putdet("A",A,mA);
	getch();
}

int det(int A[MAX][MAX],int order)
{
	int i,j,k,minor[MAX][MAX],_i,_j,d;
	if(order==1) 
		return A[0][0];
	else
	{
		d=0;
		for(k=0;k<order;k++)
		{
			for(i=1,_i=0;i<order;i++,_i++)
				for(j=0,_j=0;j<order;j++)
					if(i!=0 && j!=k)
						minor[_i][_j++]=A[i][j];
			d=(k%2==0)?d+A[0][k]*det(minor,order-1):d-A[0][k]*det(minor,order-1);
		}
		return d;
	}
}

void putdet(char* name,int A[MAX][MAX],int order)
{
	int i,j;
	printf("\n\e[32;1m(%s)%d=\n",name,order);
	for(i=0;i<order;i++)
	{
		printf("\t\e[33;1m|\t");
		for(j=0;j<order;j++)
			printf("%d\t",A[i][j]);
		printf("|");
		if(i==0) printf("\t\e[32;1m=\e[37;1m%d",det(A,order));
		printf("\n");
	}
}

int getdet(int A[MAX][MAX])
{
	int i,j,order;
	printf("\e[32;1mEnter the order of the determinant :   \e[37;1m");
	scanf("%d",&order);
	printf("\e[32;1mEnter the determinant :\e[37;1m\n");
	for(i=0;i<order;i++)
		for(j=0;j<order;j++)
		{
			printf("(a)%d%d=",i+1,j+1);
			scanf("%d",&A[i][j]);
		}
	return order;
}
