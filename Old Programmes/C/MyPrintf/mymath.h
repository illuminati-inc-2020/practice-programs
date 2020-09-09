#ifndef __MYMATH_H
#define __MYMATH_H

#include<math.h>

int mod(double a,int b)
{
	double x=floor(a);
	return x-floor(x/b)*b;
}

char* roundoff(char* s,int n)
{
	int i=0,j;
	while(s[++i]!='.') if(!s[i]) return s;
	if(s[i]=='.') for(j=0;j<=n;j++,i++);
	if(s[i]>='5')
	{		
		j=i;
		while(j>0)
		{
			if(s[j]>='0' && s[j]<='9')
				if(s[j]=='9')
					s[j]='0';
				else
				{
					s[j]++;
					break;
				}
			j--;
		}
	}
	s[i]='\0';
	if(n==0) s[--i]='\0';
	return s;
}

#endif
