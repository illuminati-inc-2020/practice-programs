/* Author	 	: Rakesh Malik
 * Date			: 16.05.2011
 * Subject		: Lagrange's Interpolation Formula
 * Assignment no.	: 16
 */

#include<stdio.h>

double lagrange_interpolation(double,double[],double[],int);
int fact(int);

int main()
{
	int n,i;
	double x[100],fx[100],X,fX;
	printf("Enter number of data : ");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("Enter value of x%d : ",i+1);
		scanf("%lf",&x[i]);
		printf("Enter value of f(x%d) : ",i+1);
		scanf("%lf",&fx[i]);
	}
	printf("\n\n x :\t");
	for(i=0;i<n;i++)
		printf("%g\t",x[i]);
	printf("\n f(x) :\t");
	for(i=0;i<n;i++)
		printf("%g\t",fx[i]);
	printf("\n\nEnter value of x : ");
	scanf("%lf",&X);
	fX=lagrange_interpolation(X,x,fx,n);
	printf("\n\nUsing Lagrange's interpolation method :\n\tf(x)=f(%g)=%g",X,fX);
	printf("\n");
}

double lagrange_interpolation(double X,double x[],double fx[],int n)
{
	double fX=0,w;
	int i,j;
	for(i=0;i<n;i++)
	{
		w=1;
		for(j=0;j<n;j++)
			if(j!=i)
				w*=X-x[j];
		for(j=0;j<n;j++)
			if(j!=i)
				w/=x[i]-x[j];
		fX+=w*fx[i];
	}
	return fX;
}