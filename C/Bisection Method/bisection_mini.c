/* Author	 	: Rakesh Malik
 * Date			: 18.05.2011
 * Subject		: Method of Bisection to solve equation
 * Assignment no.	: 19
 */

#include <stdio.h>
#include <math.h>

#define f(x) ((x)*(x)*(x)-9*(x)-1)

void bisection(double a,double b,int n);

int main()
{
	double a;
	int n;
	printf("\nMethod of Bisection :\n");
	printf("\nf(x)=x3-9x-1=0");
	for(a=-100;a<100;a++)
		if((f(a)>0&&f(a+1)<0)||(f(a)<0&&f(a+1)>0))
			break;
	if(a==100) printf("\nNo root of f(x)=0 found in interval [-100,100]\n");
	else printf("\nThere exist a root of f(x)=0 in interval [%g,%g]\n",a,a+1);
	printf("\nNumber of decimal digits to be approximated upto : ");
	scanf("%d",&n);
	bisection(a,a+1,n);
	printf("\n");
}

void bisection(double a,double b,int n)
{
	int i=0;
	double x;
	while(round(a*pow(10,n))!=round(b*pow(10,n)))
	{
		x=(a+b)/2;
		printf("\nn=%3d    a=%.*lf    b=%.*lf    x=(a+b)/2=%.*lf    f(x)=%g",i,n,a,n,b,n,x,f(x));
		if(f(a)*f(x)>0)
			a=x;
		else
			b=x;
		i++;
	}
	x=(a+b)/2;
	printf("\nn=%3d    a=%.*lf    b=%.*lf    x=(a+b)/2=%.*lf    f(x)=%g",i,n,a,n,b,n,x,f(x));
	printf("\n\nx=%.*lf correct upto %d decimal places",n,x,n);
}
