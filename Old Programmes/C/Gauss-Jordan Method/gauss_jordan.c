/* Subject	: Solving a system of linear equations using Gauss-Jordan method
 * Author	: Rakesh Malik
 * Date		: 22/04/2010
 */

#include<stdio.h>
#include<math.h>

void solve(int,double[][10],double[],double[]);
void display(int,double[][10],double[]);

int main(int c,char *v[])
{
	int i,j;
	int d;				/* number of decimal digits to be corrected upto */
	double A[10][10];		/* Coefficient matrix */
	double X[10];			/* Solution matrix to be solved */
	double b[10];			/* Right hand side matrix */
	int n;				/* number of unknown variables/equations */
	FILE *fp;
	printf("GAUSS-JORDAN ITERATION :\n\n");
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
	printf("\nNumber of decimal places to be corrected upto : ");
	scanf("%d",&d);
	solve(n,A,X,b);
	printf("\nSolutions are :\n");
	for(i=0;i<n;i++)
		printf("\t%c = %.*lf\n",i+'a',d,X[i]);
	return 0;
}

void solve(int n,double A[10][10],double X[10],double b[10])
{
	int i,j,k;
	double temp,B[10][20],C[10][20];
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			C[i][j]=B[i][j]=A[i][j];
		for(j=n;j<2*n;j++)
			C[i][j]=B[i][j]=(i==j-n)?1:0;
	}
	for(k=0;k<n;k++)
	{
		for(i=0;i<n;i++)
		{
			for(j=0;j<2*n;j++)
				printf("%-7.3g %c ",B[i][j],(j==k-1 || j==n+k-1)?'|':' ');
			if(i==k)
			{
				temp=1/C[k][k];
				for(j=k;j<n+k;j++)
				      B[i][j]=C[k][j+1]*temp;	
			}
			else
			{
				temp=-C[i][k]/C[k][k];
				for(j=k;j<n+k;j++)
				      B[i][j]=C[i][j+1]+C[k][j+1]*temp;	
			}
			printf("\n");
		}
		printf("\n");
		for(i=0;i<n;i++)
		{
			for(j=n+k;j>=k+1;j--)
				B[i][j]=B[i][j-1];
			for(j=0;j<=k;j++)
				B[i][j]=(i==j)?1:0;
			for(j=0;j<2*n;j++)
				C[i][j]=B[i][j];
		}		
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<2*n;j++)
			printf("%-7.3g %c ",B[i][j],(j==n-1)?'|':' ');
		printf("\n");
	}
	for(i=0;i<n;i++)
	{
		X[i]=0;
		for(j=0;j<n;j++)
			X[i]+=B[i][j+n]*b[j];
	}
}