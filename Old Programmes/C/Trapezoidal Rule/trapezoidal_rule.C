/* Author	 	: Rakesh Malik
 * Date			: 18.05.2011
 * Subject		: Trapezoidal Rule forNumerical Integration
 * Assignment no.	: 17
 */

#include<stdio.h>

#define f(x)  (4*(x)-3*(x)*(x))

double trapezoidal(int,double,double);

int main()
{
	int n;
	double a,b;
	printf("TRAPEZOIDAL RULE OF INTEGRATION :\n\n");
	printf("f(x)=4x-3x2\n");
	printf("a=");
	scanf("%lf",&a);
	printf("b=");
	scanf("%lf",&b);
	printf("n=");
	scanf("%d",&n);
	trapezoidal(n,a,b);
	printf("\n");
}

double trapezoidal(int n,double a,double b)
{
	double h=(b-a)/n,I=0;
	int j;
	I+=f(a)+f(b);
	printf("\nh=(b-a)/n\n =(%g-%g)/%d\n =%g",a,b,n,h);
	printf("\n\n%g to %g INTEGRATION f(x)\n =(%g/2)*[f(%g)+f(%g)\n\t+2*{",a,b,h,a,b);
	for(j=1;j<n;j++)
	{
		if(j%5==0) printf("\n\t");
		if(j!=1) printf("+");
		I+=2*f(a+j*h);
		printf("f(%g)",a+j*h);
	}
	I*=h/2;
	printf("}]\n =%g",I);
	return I;
}