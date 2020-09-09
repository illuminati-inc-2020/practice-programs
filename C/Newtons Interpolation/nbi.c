/* Author	 	: Rakesh Malik
 * Date			: 16.05.2011
 * Subject		: Newton's Backward Interpolation Formula
 * Assignment no.	: 15
 */

#include<stdio.h>

double newton_Backward_interpolation(double,double[],double[],int);
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
	fX=newton_Backward_interpolation(X,x,fx,n);
	printf("\n\nUsing Newton's Backward interpolation method :\n\tf(x)=f(%g)=%g",X,fX);
	printf("\n");
}

double newton_Backward_interpolation(double X,double x[],double fx[],int n)
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