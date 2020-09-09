#include <stdio.h>
#include <stdlib.h>

void print_spriral_matrix(int n);

int main()
{
	int n;						/* Order of matrix */
	printf("Enter order of the matrix : ");
	scanf("%d",&n);
	print_spriral_matrix(n);
}

void print_spriral_matrix(int n)
{
	int **A,i,j,k,l,x;
	A=(int**)calloc(n,sizeof(int*));
	for(i=0;i<n;i++)
		A[i]=(int*)calloc(n,sizeof(int));
	for(x=1,i=j=0,k=0,l=1;x<=n*n;x++,i+=k,j+=l)
	{
		A[i][j]=x;
		if(i+k<0 || j+l<0 || i+k>=n || j+l>=n || A[i+k][j+l]!=0)
		{
			if(k==0 && l==1)		k=1,l=0;
			else if(k==1 && l==0)		k=0,l=-1;
			else if(k==0 && l==-1)		k=-1,l=0;
			else				k=0,l=1;
		}
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			printf("%5d ",A[i][j]);
		putchar('\n');
	}
}
