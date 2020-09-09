#ifndef __MYCTYPE_H
#define __MYCTYPE_H

#include<stdlib.h>
#include<math.h>
#include<string.h>
#include"mymath.h"

#define FLT_DIGIT_MAX 50
#define INT_DIGIT_MAX 20

char* itoa(char* s,long long int i,int n)
{
	int k=INT_DIGIT_MAX,negative=0,flag=0;
	unsigned long long mult;
	flag=(n>=0)?1:0;
	s[k--]='\0';
	if(i==0) s[k--]='0';
	if(i<0)
	{
		negative=1;
	       i=-i;
	}	       
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

char* llutoa(char* s,long long unsigned i,int n)
{
	int k=INT_DIGIT_MAX,flag=0;
	unsigned long long mult;
	flag=(n>=0)?1:0;
	s[k--]='\0';
	if(i==0) s[k--]='0';
	for(mult=10;i;mult*=10)
	{
		n--;
		s[k--]='0'+(i%mult)/(mult/10);
		i=(i>0)?i-i%mult:i+i%mult;
	}
	while(n-- && flag) s[k--]='0';
	return s+k+1;
}

char* ftoa(char* s,double f,int digit)
{
	char *d;
	int c,negative=0;
	double i;
	bzero(s,FLT_DIGIT_MAX+1+digit+1);
	d=s=s+FLT_DIGIT_MAX;
	*s--='.';
	if(f<0)
	{
		negative=1;
		f=-f;		
	}
	i=floor(f);					//'i' holds integer part of 'f'
	f=f-i;						//'f' holds only decimal part
	if(i==0)
	{
		*s--='0';
		*s--='0';
	}
	while(i>0.0)					//Extracting integer part
	{
		*s--=mod(i,10)+'0';
		i=floor(i/10);
	}
	s++;
	for(c=0,*d++;c<=digit;c++)			//Extracting fraction part
	{
		f*=10;
		*d++=(int)f+'0';
		f=f-(int)f;
	}
	*d='\0';
	d=roundoff(s,digit);
	if(*d=='0') d++;
	if(negative) *--d='-';
	return d;
}

#endif
