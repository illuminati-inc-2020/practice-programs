/* Subject			: Solving differancial equation using Euler's method
 * Author			: Rakesh Malik
 * Date				: 23.03.2011
 * Assignment no.		: 25
 */

#include<stdio.h>

#define f(x,y) (x*y)

double euler(double,double,double,double,int);

int main()
{
	double h,x0,y0,xn,yn;
	int d;
	printf("Solving differancial equation using Euler's method\n");
	printf("\ndy/dx = f(x,y) = x*y");
	printf("\ngiven y(x0)=y0, To be computed y(xn), where \n");
	printf("x0 = ");
	scanf("%lf",&x0);
	printf("y0 = ");
	scanf("%lf",&y0);	
	printf("xn = ");
	scanf("%lf",&xn);
	printf("length of each step (h)  = ");
	scanf("%lf",&h);
	printf("Number of decimal places to be corrected upto : ");
	scanf("%d",&d);
	yn=euler(x0,y0,xn,h,d);
	printf("y = %.*lf\n",d,yn);
}

double euler(double x0,double y0,double xn,double h,int d)
{
	double x,y;
	printf("y(%g) = %.*lf\n",x0,d,y0);
	for(x=x0,y=y0;x<xn;)
	{
		y=y+h*f(x,y);
		x+=h;
		printf("y(%.g) = %.*lf\n",x,d,y);
	}
	return y;
}