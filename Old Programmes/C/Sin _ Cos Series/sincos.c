/* Date		:	17/07/2011
 * Subject	:	Determination of value of sin(x) and cos(x) using series approximated by 
 * 			sin^2(x)+cos^2(x)=1. And determination of tan(x) from it.
 * Author	:	Rakesh Malik
 */

#include <stdio.h>
#include <math.h>
#include <float.h>

#define PI 3.14159265358979323846264338327950288

void sct(double x,double *sin,double *cos,double *tan,double tol);

int main()
{
	double x,sin,cos,tan;
	int d;
	printf("Number of decimal digits to be approximated upto : ");
	scanf("%d",&d);
	printf("Enter an angle (x) : ");
	scanf("%lf",&x);
	sct(x*PI/180,&sin,&cos,&tan,pow(10,-d));
	printf("\nsin x = %.*lf\ncos x = %.*lf\n tan x = %.*lf\n",d,sin,d,cos,d,tan);
}

void sct(double x,double *sin,double *cos,double *tan,double tol)
{
	double 	e=DBL_MAX,		/* error in i-th iteration */
		i,			/* iteration number */
		s,			/* i-th term of sine series */
		c;			/* i-th term of cos series */
	*sin=s=x;
	*cos=c=1;
	for(i=1;fabs(e)>tol;i++)
	{
		e=1-((*sin)*(*sin)+(*cos)*(*cos));
		s*=-x*x/((2*i)*(2*i+1));
		c*=-x*x/((2*i-1)*(2*i));
		(*sin)+=s;
		(*cos)+=c;
		printf("%.*lf,%.*lf\n",10,*sin,10,*cos);
	}
	(*tan)=(*sin)/(*cos);
}
