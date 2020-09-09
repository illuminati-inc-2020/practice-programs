/* Subject	: Solving a system of linear equations using Gauss-Seidel method
 * Author	: Rakesh Malik
 * Date		: 22/03/2010
 */

#include<stdio.h>
#include<math.h>

int issolvable(int,double[][10],double[]);
void solve(int,double[][10],double[],double[],int);
void display(int,double[][10],double[]);

int main(int c,char *v[])
{
	int i,j,d;
	double A[10][10];		/* Coefficient matrix */
	double X[10];			/* Unknown matrix */
	double b[10];			
	int n;				/* number of unknown variables/equations */
	FILE *fp;
	printf("GAUSS-SEIDEL ITERATION :\n");
	if(c<=1)
	{
		fprintf(stderr,"Filename missing!\n");
		return 1;
	}
	fp=fopen(v[1],"r");
	if(fp==NULL)
	{
		fprintf(stderr,"File read error!\n");
		return 1;
	}
	printf("System of linear equation :\n");
	fscanf(fp,"%d",&n);

	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			fscanf(fp,"%lf",&A[i][j]);
			printf("(%g)%c",A[i][j],j+'a');
			if(j<n-1) printf(" + ");
		}
		fscanf(fp,"%lf",&b[i]);
		printf(" = %g\n",b[i]);
	}
	fclose(fp);
	if(issolvable(n,A,b))
	{
		printf("\nNumber of decimal places to be approximated upto : ");
		scanf("%d",&d);
		solve(n,A,X,b,d);
	}
	else
	{
		fprintf(stderr,"Given system of equations cannot be rearranged to make diagonally dominant\n");
		fprintf(stderr,"Given system of equations cannot be solved by Gauss-Seidel method\n");
		return 1;
	}
	printf("\nSolutions are :\n");
	for(i=0;i<n;i++)
		printf("\t%c = %.*lf\n",i+'a',d,X[i]);
	return 0;
}

void solve(int n,double A[10][10],double X[10],double b[10],int d)
{
	int i,j,k,solved;
	double temp[10];
	printf("AX=b\n");
	display(n,A,b);
	for(i=0;i<n;i++)
	{
		X[i]=0;
		temp[i]=9e99;
	}
	for(k=0,solved=0;!solved;k++)
	{
		printf("\nk=%3d  ",k);
		for(i=0;i<n;i++)
			temp[i]=X[i];
		for(i=0;i<n;i++)
		{
			printf("%c=%.*lf  ",i+'a',d,X[i]);
			X[i]=b[i];
			for(j=0;j<n;j++)
				if(i!=j)
					X[i]-=A[i][j]*X[j];
			X[i]/=A[i][i];
		}
		solved=1;
		for(i=0;i<n;i++)
			if(round(X[i]*pow(10,d))!=round(temp[i]*pow(10,d)))
			{
				solved=0;
				break;
			}
	}
	printf("\nk=%3d  ",k);
	for(i=0;i<n;i++)
		printf("%c=%.*lf  ",i+'a',d,X[i]);
}

int issolvable(int n,double A[][10],double b[])
{
	int i,j,k,solvable;
	double temp,sum;

	for(i=0;i<n;i++)
	{
		sum=0;
		for(k=0;k<n;k++)
			if(k!=i)
				sum+=A[i][k];
		if(A[i][i]<=sum)
		{
			for(j=0;j<n;j++)
			{
				sum=0;
				for(k=0;k<n;k++)
					if(k!=i)
						sum+=A[j][k];
				if(j!=i && A[j][i]>sum)
				{
					for(k=0;k<n;k++)
					{
						temp=A[j][k];
						A[j][k]=A[i][k];
						A[i][k]=temp;
					}
					temp=b[j];
					b[j]=b[i];
					b[i]=temp;
					break;
				}
			}
		}
	}
	solvable=1;
	for(i=0;i<n;i++)
	{
		sum=0;
		for(k=0;k<n;k++)
			if(k!=i)
				sum+=A[i][k];
		if(A[i][i]<=sum)
			solvable=0;
	}
	return solvable;
}

void display(int n,double A[][10],double b[])
{
	int k,j;
	for(k=0;k<n;k++)
	{
		printf("| ");
		for(j=0;j<n;j++)
			printf("%-5.1lf ",A[k][j]);
		printf(" |  | %c | ",k+'a');
		if(k==n/2) printf("=");
		else printf(" ");
	       	printf(" | %-5.1lf |\n",b[k]);
	}
	printf("\n");
}
