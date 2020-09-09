#ifndef _R__ARRAY_H
#define _R__ARRAY_H

#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>

int getarr(int arr[]);
int getarrf(float arr[]);
char* strrev(char* str);
int strsearch(char *s,char *p);
int* binarysearch_m(int[],size_t,int);
int binarysearch(int[],size_t,int);
void bubblesort(int arr[],int n);

void bubblesort(int arr[],int n)
{
	int buf,i,j;
	for(i=0;i<n-1;i++)
		for(j=0;j<n-i-1;j++)
			if(arr[j]>arr[j+1])
			{
				buf=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=buf;
			}
}

char* strrev(char* str)
{
	int i,max=strlen(str)-1,temp;
	for(i=0;i<=max/2;i++)
	{
		temp=str[i];
		str[i]=str[max-i];
		str[max-i]=temp;
	}
	return str;
}

int strsearch(char *s,char *p)
{
	int i,j,flag=0;
	for(i=0;s[i];i++)
	{
		flag=1;
		for(j=0;p[j];j++)
			if(s[i+j]!=p[j])
			{
				flag=0;
				break;
			}
		if(flag==1) break;
	}
	return flag;
}

int getarr(int arr[])
{
	int i=0,j,flag=0;
	char c;
	arr[0]=0;
	while(1)
	{
		c=getchar();
		if(c=='\n') break;
		if(isdigit(c))
		{
			if(flag==0) arr[i]=arr[i]*10+c-'0';
			else arr[i]=arr[i]*10-c+'0';
		}
		else if(c=='-')	flag=1;
		else if(c==' ' || c==',')
		{
			arr[++i]=0;
			flag=0;
		}
	}
	return i+1;
}

int* binarysearch_m(int arr[],size_t size,int item)
{
	if(size<=0) return NULL;
	if(item==arr[size/2]) return arr+size/2;
	else if(item<arr[size/2]) return binarysearch_m(arr,size/2,item);
	else return binarysearch_m(arr+size/2+1,size/2,item);
}

int binarysearch(int arr[],size_t size,int item)
{
	if(size<=0) return 0;
	if(item==arr[size/2]) return 1;
	else if(item<arr[size/2]) return binarysearch(arr,size/2,item);
	else return binarysearch(arr+size/2+1,size/2,item);
}

int getarrf(float arr[])
{
	int i=0,j,k,flag1=0,flag2=0,flag3=0;
	char s[1000];
	arr[0]=0;
	for(j=0;(s[j]=getchar())!='\n';j++);s[j+1]='\0';
	for(j=0;s[j];j++)
	{
		if(isdigit(s[j]))
		{
			if(flag1==0) arr[i]=arr[i]*10+s[j]-'0';
			else arr[i]=arr[i]*10-s[j]+'0';
		}
		else if(s[j]=='-') flag1=1;
		else if(s[j]=='.') flag2=1;
		else if(s[j]==' ' || s[j]==',' || s[j]=='\n')
		{
			if(flag2==1) arr[i]/=pow(10,flag3-1);
			arr[++i]=flag1=flag2=flag3=0;
		}
		if(flag2==1)
			flag3++;
	}
	return i;
}

#endif




