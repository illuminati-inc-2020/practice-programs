/* Subject	: Solving a system of linear equations using Gauss Elimination method
 * Author	: Rakesh Malik
 * Date		: 22/03/2010
 */

#include<stdio.h>

int issolvable(int,double[][10],double[]);
void solve(int,double[][10],double[],double[]);
void display(int,double[][10],double[]);

int main(int c,char *v[])
{
	int i,j;
	double A[10][10];		/* Coefficient matrix */
	double X[10];			/* Unknown matrix */
	double b[10];			
	int n;				/* number of unknown variables/equations */
   FILE *fp;
	if(c<=1)
	{
		fprintf(stderr,"Filename missing!\n");
		return;
	}
	fp=fopen(v[1],"r");
	if(fp==NULL)
	{
		fprintf(stderr,"File read error!\n");
		return;
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
		solve(n,A,X,b);
	else
	{
		fprintf(stderr,"Given system of equations cannot be solved!\n");
		return;
	}
	printf("Solutions are :\n");
	for(i=0;i<n;i++)
		printf("\t%c = %g\n",i+'a',X[i]);
}

void solve(int n,double A[][10],double X[],double b[])
{
	int i,j,k;
	double temp;
	printf("AX=b\n");
	display(n,A,b);
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			temp=-A[j][i]/A[i][i];
			for(k=0;k<n;k++)
				A[j][k]+=A[i][k]*temp;
			b[j]+=b[i]*temp;
			display(n,A,b);
		}
	}
	for(i=n-1;i>=0;i--)
	{
		X[i]=b[i];
		for(j=i+1;j<n;j++)
			X[i]-=A[i][j]*X[j];
		X[i]/=A[i][i];
	}
}

int issolvable(int n,double A[][10],double b[])
{
	int i,j,k,solvable,temp;
	for(i=0;i<n;i++)
		if(A[i][i]==0)
			for(j=0;j<n;j++)
				if(j!=i && A[j][i]!=0)
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
	solvable=1;
	for(i=0;i<n;i++)
		if(A[i][i]==0)
			solvable=0;
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
