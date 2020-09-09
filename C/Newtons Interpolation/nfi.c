/* Author	 	: Rakesh Malik
 * Date			: 16.05.2011
 * Subject		: Newton's Forward Interpolation Formula
 * Assignment no.	: 14
 */

#include<stdio.h>

double newton_forward_interpolation(double,double[],double[],int);
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
	fX=newton_forward_interpolation(X,x,fx,n);
	printf("\n\nUsing Newton's forward interpolation method :\n\tf(x)=f(%g)=%g",X,fX);
	printf("\n");
}

double newton_forward_interpolation(double X,double x[],double fx[],int n)
{
	double fX,h,u,temp;
	int i,j;
	h=x[1]-x[0];
	u=(X-x[0])/h;
	printf("\n\nx=%g, x0=%g, h=%g",X,x[0],h);
	printf("\n\nu=(x-x0)/h=(%g-%g)/%g=%g",X,x[0],h,u);
	printf("\n\nForward differance table : \n   f(x) :\t");
	for(i=0;i<n;i++)
		printf("%g\t",fx[i]);
	for(fX=i=0;i<n;i++)
	{
		temp=fx[0]/fact((int)i);
		for(j=0;j<i;j++)
			temp*=(u-j);
		fX+=temp;
		printf("\nFD%df(x) :\t",i);
		for(j=0;j<n-i-1;j++)
		{
			fx[j]=fx[j+1]-fx[j];
			printf("%g\t",fx[j]);
		}

	}
	return fX;
}

int fact(int n)
{
	int x=1;
	for(;n>1;n--)
		x*=n;
	return x;
}
