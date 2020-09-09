#include<stdio.h>
#include<string.h>

#define Gy 30
#define R 31
#define G 32
#define Y 33
#define B 34
#define P 35
#define C 36
#define W 37

#define SCREEN_SIZE 100

void patternf1(int,char*,int,char*,int,char*,int,char*,int,int);
void patternf2(int,char*,int,char*,int,char*,int,char*,int,int);
void patterni(int n,char*,int,char*,int,int);
/*
int main()
{
	int i=0,j;
	while(i>=0)
	{
		system("clear");
		patterni(i,"-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_",R,"ABCDEFGHIJKL",G,i);
		usleep(100000);
		i++;
	}
}*/

void patternf1(int n,char *s,int cs,char *l,int cl,char *r,int cr,char *m,int cm,int p)
{
	int i,ls=strlen(s),x,ll=strlen(l),lr=strlen(r),lm=strlen(m),y;
	n=n%(SCREEN_SIZE+ls)-ls;
	p=p%(SCREEN_SIZE+ls)-ls;
	printf("\e[%d;1m%s",cl,l);
	if((n>=-ls && n<=0) || (p>=-ls && p<=0))
	{
		x=(n>=-ls && n<=0)?-n:0;y=(p>=-lm && p<=0)?-p:0;
		for(i=0;i<SCREEN_SIZE-ll-lr;i++)
		{
			if(i>=p && i<p+lm) printf("\e[%d;1m",cm);
			else printf("\e[%d;1m",cs);
			printf("%c",(i>=p && i<p+lm)?m[y++]:(i>=n && i<ls+n)?s[x++]:' ');
			if(i>=p && i<p+lm && (n>=-ls && n<=0))x++;
		}
	}
	else
	{
		x=0;y=0;
		for(i=0;i<SCREEN_SIZE-ll-lr;i++)
		{
			if(i>=p && i<p+lm) printf("\e[%d;1m",cm);
			else printf("\e[%d;1m",cs);
			printf("%c",(i>=p && i<p+lm)?m[y++]:(i>=n &&i<=n+ls)?s[x++]:' ');
			if(i>=p && i<p+lm && i>=n) x++;
		}
	}
	printf("\e[%d;1m%s\n",cr,r);
}

void patternf2(int n,char *s,int cs,char *l,int cl,char *r,int cr,char *m,int cm,int p)
{
	int i,ls=strlen(s),x,ll=strlen(l),lr=strlen(r),lm=strlen(m),y;
	n=n%(SCREEN_SIZE+ls)-ls;
	p=p%(SCREEN_SIZE+ls)-ls;
	printf("\e[%d;1m%s",cl,l);
	if((n>=-ls && n<=0) || (p>=-ls && p<=0))
	{
		x=(n>=-ls && n<=0)?-n:0;y=(p>=-lm && p<=0)?-p:0;
		for(i=0;i<SCREEN_SIZE-ll-lr;i++)
		{
			if(i>=p && i<p+lm && m[y]!=' ') printf("\e[%d;1m",cm);
			else printf("\e[%d;1m",cs);
			printf("%c",(i>=p && i<p+lm && m[y]!=' ')?m[y]:(i>=n && i<ls+n)?s[x++]:' ');
			if(i>=p && i<p+lm)
			{
				if(m[y]!=' ' && (n>=-ls && n<=0)) x++;
				y++;
			}
		}
	}
	else
	{
		x=0;y=0;
		for(i=0;i<SCREEN_SIZE-ll-lr;i++)
		{
			if(i>=p && i<p+lm && m[y]!=' ') printf("\e[%d;1m",cm);
			else printf("\e[%d;1m",cs);
			printf("%c",(i>=p && i<p+lm && m[y]!=' ')?m[y]:(i>=n &&i<=n+ls)?s[x++]:' ');
			if(i>=p && i<p+lm)
			{
				if(m[y]!=' ' && i>=n) x++;
				y++;
			}
		}
	}
	printf("\e[%d;1m%s\n",cr,r);
}

void patterni(int n,char *s,int cs,char *m,int cm, int p)
{
	int ls=strlen(s),lm=strlen(m),i,j,y=0;
	n=n%SCREEN_SIZE;
	p=p%(SCREEN_SIZE+lm)-lm;
	if(p<0)
	{
		y=-p;
		for(i=0;i<SCREEN_SIZE;i++)
		{
			printf("\e[%d;1m",cs);
			if(i>=0 && i<lm+p) printf("\e[%d;1m",cm);
			printf("%c",(i>=0 && i<lm+p)?m[y++]:s[n]);
			n=(n+1)%SCREEN_SIZE;
		}
	}
	else
	{
		for(i=0;i<SCREEN_SIZE;i++)
		{
			printf("\e[%d;1m",cs);
			if(i>=p && i<lm+p) printf("\e[%d;1m",cm);
			printf("%c",(i>=p && i<p+lm)?m[y++]:s[n]);
			n=(n+1)%SCREEN_SIZE;
		}
	}
	printf("\n");
}
