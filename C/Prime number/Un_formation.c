# include<stdio.h>
# include<stdlib.h>

long long int gcd(long long int,long long int);
long long int Un_formation(long long int,long long int **);

int main()
{
	long long int n,*p=NULL,k,i;
	printf("enter the number");
	scanf("%lld",&n);
	k=Un_formation(n,&p);
	for(i=0;i<k;i++)
		printf("%lld\t",*(p+i));
}

//----------------------------------Un formation-------------------

long long int Un_formation(long long int n,long long int **p)
{
	long long int i,j,l=2;
	for(i=1;i<n/2;i++)
	{
       	   j=gcd(n,i);
	   if(j==1)
	   {
		   *p=(long long int*)realloc(*p,l*8);			  
		   *(*p+l-2)=i;
		   *(*p+l-1)=n-i;
		   l+=2;
	   }
	}
	return (l-2);
}

//------------------gcd calcualtion---------------------------------


long long int gcd(long long int n ,long long int c)
{
	while(n!=c)
		if(n>c) n=n-c;
		else c=c-n;
	return n;
}
