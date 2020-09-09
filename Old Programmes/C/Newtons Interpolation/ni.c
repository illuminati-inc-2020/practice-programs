/* Author	 	: Rakesh Malik
 * Date			: 16.05.2011
 * Subject		: Newton's Forward and Backward Interpolation Formula
 * Assignment no.	: 14
 */

#include<stdio.h>

double newton_forward_interpolation(double,double[],double[],int);
double newton_backward_interpolation(double,double[],double[],int);
int fact(int);

int main()
{
	int n,i,choice;
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
	printf("\n1. Use Newton's forward interpolation");
	printf("\n2. Use Backward's forward interpolation");
	printf("\nEnter your choice_");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
			fX=newton_forward_interpolation(X,x,fx,n);
			printf("\nUsing Newton's forward interpolation method :");
			printf("\n\tf(x)=f(%g)=%g",X,fX);
			break;
		case 2:
			fX=newton_backward_interpolation(X,x,fx,n);
			printf("\nUsing Newton's backward interpolation method :");
			printf("\n\tf(x)=f(%g)=%g",X,fX);
			break;
		default:
			return 0;
	}
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

double newton_backward_interpolation(double X,double x[],double fx[],int n)
{
	double fX,h,u,temp;
	int i,j;
	h=x[1]-x[0];
	u=(X-x[n-1])/h;
	printf("\n\nx=%g, xn=%g, h=%g",X,x[n-1],h);
	printf("\n\nu=(x-xn)/h=(%g-%g)/%g=%g",X,x[n-1],h,u);
	printf("\n\nForward differance table : \n   f(x) :\t");
	for(i=0;i<n;i++)
		printf("%g\t",fx[i]);
	for(fX=i=0;i<n;i++)
	{
		temp=fx[n-1-i]/fact((int)i);
		for(j=0;j<i;j++)
			temp*=(u+j);
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
