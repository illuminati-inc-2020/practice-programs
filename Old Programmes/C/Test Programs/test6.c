# include <stdio.h>
# include <stdlib.h>
struct bit
{ 
	unsigned int x : 1 ;
} ;
int main ( ) 
{ 
	printf ( "%d" , sizeof ( struct bit ) ) ;
} /*	for(i=0;i<10;i++)
	{
		printf("%d\t",i);
		{
			static int i=3;
			printf("%d\n",i);
			i++;
		}
	}
*/
/*	char s[10];
	scanf("%[^\n]",s);
	printf("%s",s);
	int *p=NULL;
	p=(int*)realloc(p,8*sizeof(int));
	for(i=0;i<8;i++)
		*(p+i)=i;
	p=(int*)realloc(p,10*sizeof(int));
	for(j=i;j<10;j++)
		*(p+j)=j;
	for(i=0;i<10;i++)
		printf("%d\t",*(p+i));
}*/
