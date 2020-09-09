/* Author	 	: Rakesh Malik
 * Date			: 18.05.2011
 * Subject		: Regula-Falsi Method to solve equation
 * Assignment no.	: 21
 */

#include <stdio.h>
#include <math.h>

#define f(x) (x*x*x+2*x-2)

void bisection(double a,double b,int n);

int main()
{
	double a,b;
	int n;
	printf("\nRegula-Falsi Method :\n");
	printf("\nf(x)=x3+2x-2=0");
	printf("\ninterval of root [a,b] where\na=");
	scanf("%lf",&a);
	printf("b=");
	scanf("%lf",&b);
	printf("To be corrected upto decimal places : ");
	scanf("%d",&n);
	printf("\nf(%.*lf)=%g\nf(%.*lf)=%g",n,a,f(a),n,b,f(b));
	if(f(a)*f(b)>0)
	{
		printf("\n f(a) and f(b) must be of opposite sign\n");
		return 0;
	}
	bisection(a,b,n);
	printf("\n");
}

void bisection(double a,double b,int n)
{
	int i=0;
	double x,h,temp=9e99;
	while(round(x*pow(10,n))!=round(temp*pow(10,n)))
	{
		h=(fabs(f(a))/(fabs(f(a))+fabs(f(b))))*(b-a);
		temp=x;
		x=a+h;
		printf("\nn=%3d    a=%.*lf    b=%.*lf    h=%lf    x=a+h=%.*lf    f(x)=%g",i,n,a,n,b,h,n,x,f(x));
		if(f(a)*f(b)<0)
			a=x;
		else
			b=x;
		i++;
	}
	h=(fabs(f(a))/(fabs(f(a))+fabs(f(b))))*(b-a);
	x=a+h;
	printf("\nn=%3d    a=%.*lf    b=%.*lf    h=%lf    x=a+h=%.*lf    f(x)=%g",i,n,a,n,b,h,n,x,f(x));
	printf("\n\nx=%.*lf correct upto %d decimal places",n,x,n);
}