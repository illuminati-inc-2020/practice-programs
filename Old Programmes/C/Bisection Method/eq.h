#ifndef _EQ_H
#define _EQ_H
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAX 100

void geteq(int *eq);
int *f_x(int *eq,int *eq1);
void descartes(int *eq,int *preal,int *nreal);
double f(int *eq,double x);


void geteq(int *eq)
{
	int i,coeff,pow,neg=0,left=1;
	for(i=0;i<MAX;i++) eq[i]=0;
	char *s=(char*)malloc(MAX*5);
	scanf("%s",s);
	for(i=0;i<MAX;i++) eq[i]=0;
	while(*s)
	{
		neg=0;
		while(*s=='=' || *s==' ' || *s=='+' || *s=='-' || *s=='(' || *s==')')
		{
			if(*s=='=') left=0;
			if(*s=='-') neg=!neg;
			s++;
		}
		if(left==0) neg=!neg;
		if(!isdigit(*s)) coeff=1;
		else 
			for(coeff=0;isdigit(*s);s++)
				coeff=coeff*10+(*s-'0');
		if(neg) coeff=-coeff;
		while(*s==' ' || *s=='*') s++;
		if(*s=='x')
		{
			s++;
			while(*s==' ' || *s=='^') s++;
			if(!isdigit(*s)) pow=1;
			else 
				for(pow=0;isdigit(*s);s++)
					pow=pow*10+(*s-'0');
		}
		else pow=0;
		eq[pow]+=coeff;
	}
}

void descartes(int *eq,int *preal,int *nreal)
{
	int last,i,eq1[MAX];
	for(last=-1,*preal=0,i=0;i<MAX;i++)
	{
		if((eq[i]>0 && last==1) || (eq[i]<0 && last==0)) (*preal)++;
		if(eq[i]>0) last=0;
		else if(eq[i]<0) last=1;
	}
	f_x(eq,eq1);
	for(last=-1,*nreal=0,i=0;i<MAX;i++)
	{
		if((eq1[i]>0 && last==1) || (eq1[i]<0 && last==0)) (*nreal)++;
		if(eq1[i]>0) last=0;
		else if(eq1[i]<0) last=1;
	}
}

int *f_x(int *eq,int *eq1)
{
	int i;
	for(i=0;i<MAX;i++)
	{
		if(i%2==0) eq1[i]=eq[i];
		else eq1[i]=-eq[i];
	}
	return eq1;
}

double f(int *eq,double x)
{
	int i;
	double y=0;
	for(i=0;i<MAX;i++)
		y+=eq[i]*pow(x,i);
	return y;
}

#endif
