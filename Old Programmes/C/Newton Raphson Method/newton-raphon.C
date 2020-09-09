/* Author	 	: Rakesh Malik
 * Date			: 18.05.2011
 * Subject		: Newton-Raphson Method to solve equation
 * Assignment no.	: 20
 */

#include<stdio.h>
#include<math.h>

#define f(x)  (x*x+100*x-1600)
#define f_(x) (2*x+100)

void newton_raphson(double,int);

int main()
{
	double x0;
	int n;
	printf("NEWTON RAPHSON METHOD :\n");
	printf("\nf(x)=x3-8x-4=0\n");
	printf("x0=");
	scanf("%lf",&x0);
	printf("Number of decimal places to be corrected upto : ");
	scanf("%d",&n);
	newton_raphson(x0,n);
	printf("\n");
}

void newton_raphson(double x,int n)
{
	double h,temp=9e99;
	int i=0;
	while(round(x*pow(10,n))!=round(temp*pow(10,n)))
	{
		if(f_(x)==0)
		{
			printf("\nf'(%.*lf)=0, Newton-Raphson Method can't proceed further",n,x);
			return;
		}
		h=-f(x)/f_(x);
		printf("\nn=%3d    x=%.*lf    f(x)=%lf    f'(x)=%lf    h=%lf",i,n,x,f(x),f_(x),h);
		temp=x;
		x+=h;
		i++;
	}
	printf("\nn=%3d    x=%.*lf",i,n,x);
}
