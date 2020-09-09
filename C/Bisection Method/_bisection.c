/* Subject : 	SOLVING EQUATION USING BISECTION METHOD
 */

#include <stdio.h>
#include <ctype.h>
#include "eq.h"
#define MAXSOL 100

int bisection(int*,double*,int,int);
double rnd(double,int);

int main()
{
	int n,eq[100],dig,mode=0;
	double sol[100];
	system("clear");
	printf("\nEnter an equation : ");
	geteq(eq);
	printf("Number of digits after decimal point for solution : ");
	scanf("%d",&dig);
	printf("Enter 1 for verbose _");
	scanf("%d",&mode);
	n=bisection(eq,sol,dig,mode);
	printf("\nReal solution(s) : ");
	for(n--;n>=0;n--) printf("%.*lf, ",dig,sol[n]);
	printf("\n\n");
}

int bisection(int *eq,double *sol,int dig,int mode)
							//dig = number of digits after dacimal point
{
	int i,j,preal,nreal,n=0;
							// preal = number of positive real roots
							// nreal = number of negative real roots
	double a,b,c,fa,fb,fc;
	descartes(eq,&preal,&nreal);
	printf("\nMaximum number positive real solutions = %d",preal);
	printf("\nMaximum number negative real solutions = %d",nreal);
	for(i=0;nreal>0 && i>-MAXSOL;i--)
	{
		a=i,b=i-1;
		fa=f(eq,a);
		fb=f(eq,b);
		if(mode==1)
			printf("\na=%.*lf\tf(a)=%.*lf\tb=%.*lf\tf(b)=%.*lf",dig+1,a,dig+1,fa,dig+1,b,dig+1,fb);
		if(fa==0)
		{
			sol[n++]=a;
			nreal--;
		}
		else if((fa>0 && fb<0) || (fa<0 && fb>0))
		{
			while(rnd(a,dig)!=rnd(b,dig))
			{
				c=(a+b)/2;
				fc=f(eq,c);
				if(mode==1)
					printf("\na=%.*lf\tf(a)=%.*lf\tb=%.*lf\tf(b)=%.*lf\tc=%.*lf\tf(c)=%.*lf",
							dig+1,a,dig+1,fa,dig+1,b,dig+1,fb,dig+1,c,dig+1,fc);
				if(fc==0)
					break;
				else if((fc>0 && fa>0) || (fc<0 && fa<0))
					a=c;
				else
					b=c;
			}
			sol[n++]=c;
			nreal--;
		}
	}
	for(i=0;preal>0 && i<MAXSOL;i++)
	{
		a=i,b=i+1;
		fa=f(eq,a);
		fb=f(eq,b);
		if(mode==1)
			printf("\na=%.*lf\tf(a)=%.*lf\tb=%.*lf\tf(b)=%.*lf",dig+1,a,dig+1,fa,dig+1,b,dig+1,fb);
		if(fa==0)
		{
			sol[n++]=a;
			preal--;
		}
		else if((fa>0 && fb<0) || (fa<0 && fb>0))
		{
			while(rnd(a,dig)!=rnd(b,dig))
			{
				c=(a+b)/2;
				fc=f(eq,c);
				if(mode==1)
					printf("\na=%.*lf\tf(a)=%.*lf\tb=%.*lf\tf(b)=%.*lf\tc=%.*lf\tf(c)=%.*lf",
							dig+1,a,dig+1,fa,dig+1,b,dig+1,fb,dig+1,c,dig+1,fc);
				if(fc==0)
					break;
				else if((fc>0 && fa>0) || (fc<0 && fa<0))
					a=c;
				else
					b=c;
			}
			sol[n++]=c;
			preal--;
		}
	}
	return n;
}

double rnd(double x,int dig)
{
	char s[50];
	sprintf(s,"%.*lf",dig,x);
	return atof(s);
}
