/* Subject : 	SOLVING EQUATION USING BISECTION METHOD
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "eq.h"
#define MAXSOL 100

int solution(int*,double*,int,int);
void bisection(int*,double,double,double*,int*,int*,int,int);
double rnd(double,int);

int main(int argc,char *argv[])
{
	int n,eq[100],dig,mode=0;
	double sol[100];
	if(argc==2 && strcmp(argv[1],"v")==0) mode=1;
	system("clear");
	printf("\nEnter an equation : ");
	geteq(eq);
	printf("Number of digits after decimal point for solution : ");
	scanf("%d",&dig);
	n=solution(eq,sol,dig,mode);
	printf("\nReal solution(s) : ");
	for(n--;n>=0;n--) printf("%.*lf, ",dig,sol[n]);
	printf("\n\n");
}

int solution(int *eq,double *sol,int dig,int mode)
							// eq = equation f(x)=0, sol = roots of f(x)=0 
							// dig = number of digits after dacimal point for rounding off
							// mode = 1(verbose)
{
	int i,j,preal,nreal,n=0;
							// preal = number of positive real roots
							// nreal = number of negative real roots
							// n = number of roots
	double a,b,c,fa,fb,fc;				
							// a = upper bound for range of solution
							// b = upper bound for range of solution
							// c = (a+b)/2
							// fa=f(a), fb=f(b), fc=f(c) 
	descartes(eq,&preal,&nreal);
	if(mode==1)
	{
		printf("\nMaximum number positive real solutions = %d",preal);
		printf("\nMaximum number negative real solutions = %d",nreal);
	}
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
			if(a!=0)nreal--;
		}
		if((fa>0 && fb<0) || (fa<0 && fb>0))
			bisection(eq,a,b,sol,&n,&nreal,dig,mode);
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
			if(a!=0)preal--;
		}
		if((fa>0 && fb<0) || (fa<0 && fb>0))
			bisection(eq,a,b,sol,&n,&preal,dig,mode);
	}
	return n;
}

void bisection(int *eq,double a,double b,double *sol,int* n,int *roots,int dig,int mode)
{
	double fa,fb,c,fc;
	fa=f(eq,a);
	fb=f(eq,b);
	c=(a+b)/2;
	fc=f(eq,c);
	if(rnd(a,dig)!=rnd(b,dig))
	{	
		if(mode==1)
			printf("\na=%.*lf\tf(a)=%.*lf\tb=%.*lf\tf(b)=%.*lf\tc=%.*lf\tf(c)=%.*lf",
				dig+1,a,dig+1,fa,dig+1,b,dig+1,fb,dig+1,c,dig+1,fc);
		if(fc==0)
		{
			sol[(*n)++]=c;
			(*roots)--;
		}
		if((fc>0 && fa>0) || (fc<0 && fa<0))
			bisection(eq,c,b,sol,n,roots,dig,mode);
		if((fc>0 && fb>0) || (fc<0 && fb<0))
			bisection(eq,a,c,sol,n,roots,dig,mode);
	}
	else
	{
		sol[(*n)++]=c;
		(*roots)--;
	}
}

double rnd(double x,int dig)
{
	char s[50];
	sprintf(s,"%.*lf",dig,x);
	return atof(s);
}
