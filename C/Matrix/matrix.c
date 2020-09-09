#include<stdio.h>

#define MAX 10

int det(int[MAX][MAX],int);
void transpose(int[MAX][MAX],int,int);
void getmat(int[MAX][MAX],int,int);
void putmat(int[MAX][MAX],int,int);
void mat_mul(int[MAX][MAX],int[MAX][MAX],int[MAX][MAX],int,int,int);
void mat_add(int[MAX][MAX],int[MAX][MAX],int[MAX][MAX],int,int);
void mat_sub(int[MAX][MAX],int[MAX][MAX],int[MAX][MAX],int,int);
void adjoint(int[MAX][MAX],int[MAX][MAX],int);

void getch()
{
	getchar();
	getchar();
}
void copymat(int[MAX][MAX],int[MAX][MAX],int,int);

int main()
{
	int choice,i,j;
	int A[MAX][MAX],mA,nA,B[MAX][MAX],mB,nB,C[MAX][MAX]n;
	system("clear");
	while(choice)
	{
		system("clear");
		printf("\e[36;1mMATRIX\n\n1.  Determinant value of a matrix\n2.  Matrix addition\n3.  Matrix subtraction\n4.  Matrix multiplication\n5.  Transpose of a matrix\n6.  Inverse of a matrix\n7.  Adjoint of a matrix\n8.  \n0.  Exit\n\n\t\tEnter your choice_\e[37;1m");
		scanf("%d",&choice);
		switch(choice)
		{
			case 0:
				break;
			case 1:  //Determinant
				printf("\e[32;1mEnter order of the matrix A:   \e[37;1m");
				scanf("%d",&mA);
				printf("\t\t\t\tX");
				scanf("%d",&nA);
				if(mA==nA)
				{
					getmat(A,mA,nA);
					printf("\n\n\e[32;1m(A)%dx%d=",mA,nA);
					putmat(A,mA,nA);
					printf("\n\e[32;1mdet A=\e[33;1m%d",det(A,mA));
				}
				else
					printf("\e[31;1mIt must be a square matrix");
				getch();
				break;
			case 2:  //Matrix addition
				printf("\e[32;1mEnter order of the matrix A:   \e[37;1m");
				scanf("%d",&mA);
				printf("\t\t\t\tX");
				scanf("%d",&nA);
				getmat(A,mA,nA);
				printf("\e[32;1mEnter order of the matrix B:   \e[37;1m");
				scanf("%d",&mB);
				printf("\t\t\t\tX");
				scanf("%d",&nB);
				getmat(B,mB,nB);
				if(mA==mB && nA==nB)
				{
					mat_add(A,B,C,mA,mB);
					printf("\n\n\e[32;1m(A)%dx%d=",mA,nA);
					putmat(A,mA,nA);
					printf("\n\e[32;1m(B)%dx%d=",mB,nB);
					putmat(B,mB,nB);
					printf("\n\e[32;1m(A+B)%dx%d=",mA,nB);
					putmat(C,mA,mB);
				}
				else
					printf("\e[31;1mInvalid order for Addition");
				getch();
				break;

			case 3:  //Matrix Subtraction
				printf("\e[32;1mEnter order of the matrix A:   \e[37;1m");
				scanf("%d",&mA);
				printf("\t\t\t\tX");
				scanf("%d",&nA);
				getmat(A,mA,nA);
				printf("\e[32;1mEnter order of the matrix B:   \e[37;1m");
				scanf("%d",&mB);
				printf("\t\t\t\tX");
				scanf("%d",&nB);
				getmat(B,mB,nB);
				if(mA==mB && nA==nB)
				{
					mat_sub(A,B,C,mA,nA);
					printf("\n\n\e[32;1m(A)%dx%d=",mA,nA);
					putmat(A,mA,nA);
					printf("\n\e[32;1m(B)%dx%d=",mB,nB);
					putmat(B,mB,nB);
					printf("\n\e[32;1m(A-B)%dx%d=",mA,nB);
					putmat(C,mA,nB);
				}
				else
					printf("\e[31;1mInvalid order for subtraction");
				getch();
				break;
			case 4:  //Matrix multiplication
				printf("\e[32;1mEnter order of the matrix A:   \e[37;1m");
				scanf("%d",&mA);
				printf("\t\t\t\tX");
				scanf("%d",&nA);
				getmat(A,mA,nA);
				printf("\e[32;1mEnter order of the matrix B:   \e[37;1m");
				scanf("%d",&mB);
				printf("\t\t\t\tX");
				scanf("%d",&nB);
				getmat(B,mB,nB);
				if(nA==mB)
				{
					mat_mul(A,B,C,mA,nA,nB);
					printf("\n\n\e[32;1m(A)%dx%d=",mA,nA);
					putmat(A,mA,nA);
					printf("\n\e[32;1m(B)%dx%d=",mB,nB);
					putmat(B,mB,nB);
					printf("\n\e[32;1m(A*B)%dx%d=",mA,nB);
					putmat(C,mA,nB);
				}
				else
					printf("\e[31;1mInvalid order for multiplication");
				getch();
				break;
			case 5:  //Transpose
				printf("Enter order of the matrix A:   ");
				scanf("%d",&mA);
				printf("\t\t\t\tX");
				scanf("%d",&nA);
				getmat(A,mA,nA);
				printf("\n\n\e[32;1m(A)%dx%d=",mA,nA);
				putmat(A,mA,nA);
				printf("\n\n\e[32;1mTranspose A =");
				transpose(A,mA,nA);
				putmat(A,nA,mA);
				getch();
				break;
			case 6:  //Inverse
				printf("Enter order of the matrix A:   ");
				scanf("%d",&mA);
				printf("\t\t\t\tX");
				scanf("%d",&nA);
				if(mA==nA)
				{
					getmat(A,mA,mA);
					putmat(A,mA,mA);
					adjoint(A,C,mA);
					printf("\n\n\e[32;1mInverse A =");
					printf("\n\e[33;1m");
					for(i=0;i<mA;i++)
					{
						printf("\t");
						printf("||\t");
						for(j=0;j<mA;j++)
							printf("%d\t",C[i][j]);
						if(i==mA/2) printf("||\t* ( 1 / %d )\n",det(C,mA));
						else printf("||\n");
					}
				}
				else
					printf("\e31;1mIt must be a square matrix");
				getch();
				break;
			case 7:  //Adjoint
				printf("Enter order of the matrix A:   ");
				scanf("%d",&mA);
				printf("\t\t\t\tX");
				scanf("%d",&nA);
				if(mA==nA)
				{
					getmat(A,mA,mA);
					putmat(A,mA,mA);
					adjoint(A,C,mA);
					printf("\n\n\e[32;1mAdj A =");
					putmat(C,mA,mA);
				}
				else
					printf("\e31;1mIt must be a square matrix");
				getch();
				break;
			case 8:  //
				break;
			default:
				printf("\e[31;1mYou have entered wrong choice");
				getch();
				break;
		}
	}
}

void copymat(int A[MAX][MAX],int B[MAX][MAX],int m,int n)
{
	int i,j;
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			B[i][j]=A[i][j];
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
					if(j!=k)
						minor[_i][_j++]=A[i][j];
			d=(k%2==0)?d+A[0][k]*det(minor,order-1):d-A[0][k]*det(minor,order-1);
		}
		return d;
	}
}

void transpose(int A[MAX][MAX],int m,int n)
{
	int i,j,buf;
	if(n>m) m=n;
	for(i=0;i<m-1;i++)
		for(j=0;j<m;j++)
			if(i<j)
				{
					buf=A[j][i];
					A[j][i]=A[i][j];
					A[i][j]=buf;
				}				
}

void getmat(int A[MAX][MAX],int m,int n)
{
	int i,j;
	printf("\e[32;1mEnter the matrix :\e[37;1m\n");
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
		{
			printf("element %d%d=",i+1,j+1);
			scanf("%d",&A[i][j]);
		}
}

void putmat(int A[MAX][MAX],int m,int n)
{
	int i,j;
	printf("\n\e[33;1m");
	for(i=0;i<m;i++)
	{
		printf("||\t");
		for(j=0;j<n;j++)
			printf("%d\t",A[i][j]);
		printf("||\n");
	}
}

void mat_mul(int A[MAX][MAX],int B[MAX][MAX],int C[MAX][MAX],int m,int n,int p)
{
				//(C)mxp = (A)mxn * (B)nxp
	int i,j,k,buf;
	for(i=0;i<m;i++)
		for(j=0;j<p;j++)
		{
			buf=0;
			for(k=0;k<n;k++)
				buf+=A[i][k]*B[k][j];
			C[i][j]=buf;
		}
}

void mat_add(int A[MAX][MAX],int B[MAX][MAX],int C[MAX][MAX],int m,int n)
{
	int i,j;
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			C[i][j]=A[i][j]+B[i][j];
}

void mat_sub(int A[MAX][MAX],int B[MAX][MAX],int C[MAX][MAX],int m,int n)
{
	int i,j;
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			C[i][j]=A[i][j]-B[i][j];
}

void adjoint(int A[MAX][MAX],int C[MAX][MAX],int m)
{
	int i,j,k,l,_i,_j,minor[MAX][MAX];
	for(i=0;i<m;i++)
		for(j=0;j<m;j++)
		{
			for(_i=0,k=0;k<m;k++)
				if(k!=i)
				{
					for(_j=0,l=0;l<m;l++)
						if(l!=j)
							minor[_i][_j++]=A[k][l];
					_i++;
				}
			C[i][j]=((i+j)%2==0)?det(minor,m-1):-det(minor,m-1);
		}
	transpose(C,m,m);
}
