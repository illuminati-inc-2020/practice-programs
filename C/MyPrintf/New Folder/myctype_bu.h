#ifndef __MYCTYPE_H
#define __MYCTYPE_H

#include<stdio.h>
#include<stdlib.h>
#include"mymath.h"

#define FLT_DIGIT_MAX 30

char* itoa(char* s,long long int i,int n)
{
	int k=20,negative=0,flag=0;
	unsigned long long mult;
	flag=(n>=0)?1:0;
	s[k--]='\0';
	if(i==0) s[k--]='0';
	negative=(i<0)?1:0; 
	for(mult=10;i;mult*=10)
	{
		n--;
		s[k--]='0'+(i%mult)/(mult/10);
		i=(i>0)?i-i%mult:i+i%mult;
	}
	while(n-- && flag) s[k--]='0';
	if(negative) s[k--]='-';
	return s+k+1;
}

char* ftoa(char* s,double f,int digit)
{
	int i,k=FLT_DIGIT_MAX,j=FLT_DIGIT_MAX+4+digit,negative=0;
	long long f1,mult;
	s[k+1]='.';
	if((int)f==0) s[k--]='0';
	if(f<0.0)
	{
		negative=1;
		f=-f;		
	}
								//Making string for integer part
	for(f1=(long long)f,mult=10;f1>0;mult*=10)		
	{
		s[k--]='0'+(f1%mult)/(mult/10);
		f1-=f1%mult;
	}
	s[k--]='0';
								//Making string for part after decimal point
	for(i=0,mult=10;i<=digit+1;i++)	mult*=10;
	for(f1=(long long)(f*mult),mult=10;j>FLT_DIGIT_MAX+1;mult*=10)	
	{
		s[j--]='0'+(f1%mult)/(mult/10);
		f1-=f1%mult;
	}
	if(s[k+1]=='0') k++;
	if(negative) s[k--]='-';
	s[FLT_DIGIT_MAX+3+digit]='\0';		
	void Putchar(char);
	return roundoff(s+k+1,digit);				//Returning rounded off float-string
}

#endif
