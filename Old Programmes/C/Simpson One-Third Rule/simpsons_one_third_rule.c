/* Author	 	: Rakesh Malik
 * Date			: 18.05.2011
 * Subject		: Simpson's One-Third Rule for Numerical Integration
 * Assignment no.	: 18
 */

#include<stdio.h>

#define f(x)  (4*(x)-3*(x)*(x))

double simpson_one_third(int,double,double,int);

int main()
{
	int n,d;
	double a,b;
	printf("SIMPSON'S ONE-THIRD RULE :\n\n");
	printf("f(x)=4x-3x2\n");
	printf("a=");
	scanf("%lf",&a);
	printf("b=");
	scanf("%lf",&b);
	printf("n=");
	scanf("%d",&n);
	printf("Number of dacimal digits to be approximated upto : ");
	scanf("%d",&d);
	if(n%2!=0)
	{
	  printf("n must be even\n");
	  return 0;
	}
	simpson_one_third(n,a,b,d);
	printf("\n");
}

double simpson_one_third(int n,double a,double b,int d)
{
	double h=(b-a)/n,I;
	int j;
	I=f(a)+f(b);
	printf("\nh=(b-a)/n\n =(%g-%g)/%d\n =%g",a,b,n,h);
	printf("\n\n%g to %g INTEGRATION f(x)\n =(%g/3)*[f(%g)+f(%g)\n\t+",a,b,h,a,b);
	for(j=1;j<n;j++)
	{
		if(j%5==0) printf("\n\t");
		if(j!=1) printf("+");
		if(j%2==0)
		{
			I+=2*f(a+j*h);
			printf("2*f(%g)",a+j*h);
		}
		else
		{
			I+=4*f(a+j*h);
			printf("4*f(%g)",a+j*h);
		}
	}
	I*=h/3;
	printf("]\n =%.*lf",d,I);
	return I;
}
