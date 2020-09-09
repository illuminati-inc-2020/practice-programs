#if !defined(_R__MATH_H)
#define _R__MATH_H

#include<math.h>

void dec2bin(int m,int n,char *f); 	//converts an n digit decimal m to binary and stores to string f


void dec2bin(int m,int n,char *f)
{
	int mask,k=-1;
	for(mask=pow(2,n-1);mask>0;mask/=2)
		f[++k]=((m&mask)==0)?'0':'1';
}

#endif
