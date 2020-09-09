/* Subject	: Gauss Elimination matrix inversion method
 * Author	: Rakesh Malik
 * Date		: 02/02/2011
 */

#include<stdio.h>

void inverse(double A[10][10],int n);

int main(int argc,char *argv[])
{
	int i,j;
	double A[10][10];		/* Matrix */
	int n;				/* Order */
   	FILE *fp;
	if(argc<=1)
	{
		fprintf(stderr,"Filename missing!\n");
		return;
	}
	fp=fopen(argv[1],"r");
	if(fp==NULL)
	{
		fprintf(stderr,"File read error!\n");
		return;
	}
	fscanf(fp,"%d",&n);
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			fscanf(fp,"%lf",&A[i][j]);
	inverse(A,n);
	fclose(fp);
}

void inverse(double A[10][10],int n)
{
	double I[10][10],temp;
	int i,j,k;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(i==j) I[i][j]=1;
			else I[i][j]=0;
	printf("A : I =\n");
	for(k=0;k<n;k++)
	{
		for(j=0;j<n;j++)
			printf("%8.3lf ",A[k][j]);
		printf(":");
		for(j=0;j<n;j++)
			printf("%8.3lf ",I[k][j]);
		printf("\n");
	}
	printf("\n");
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			temp=-A[j][i]/A[i][i];
			for(k=0;k<n;k++)
			{
				A[j][k]+=A[i][k]*temp;
				I[j][k]+=I[i][k]*temp;
			}
		}
		for(k=0;k<n;k++)
		{
			for(j=0;j<n;j++)
				printf("%8.3lf ",A[k][j]);
			printf(":");
			for(j=0;j<n;j++)
				printf("%8.3lf ",I[k][j]);
			printf("\n");
		}
		printf("\n");
	}
	for(k=0;k<n;k++)
	{
		for(i=n-1;i>=0;i--)
		{
			for(j=i+1;j<n;j++)
				I[i][k]-=A[i][j]*I[j][k];
			I[i][k]/=A[i][i];
		}
	}
	printf("\nInverse(A) =\n");
	for(k=0;k<n;k++)
	{
		for(j=0;j<n;j++)
			printf("%8.3lf ",I[k][j]);
		printf("\n");
	}
}