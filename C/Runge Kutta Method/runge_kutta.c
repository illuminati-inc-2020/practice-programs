/* Subject			: Solving differancial equation using Runge-Kutta's forth order method
 * Author			: Rakesh Malik
 * Date				: 23.03.2011
 * Assignment no.		: 26
 */

#include<stdio.h>

#define f(x,y) ((x)*(y))

double rk(double,double,double,double);

int main()
{
	double h,x0,y0,xn,yn;
	int d;
	printf("Solving differancial equation using Range Kutta method of fourth order\n");
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
	yn=rk(x0,y0,xn,h);
	printf("y = %.*lf\n",d,yn);
}

double rk(double x0,double y0,double xn,double h)
{
	int i;
	double x,y,k1,k2,k3,k4,k;
	for(i=0,x=x0,y=y0;x<xn;x+=h,i++)
	{
		printf("x%d = %g, y%d = %g\n",i,x,i,y);
		k1=h*f(x,y);
		k2=h*f(x+h/2,y+k1/2);
		k3=h*f(x+h/2,y+k2/2);
		k4=h*f(x+h,y+k3);
		k=(k1+2*k2+2*k3+k4)/6;
		printf("k1 = %g, k2 = %g, k3 = %g, k4 = %g\nk = %g\n\n",k1,k2,k3,k4,k);
		y=y+k;
	}
	return y;
}
