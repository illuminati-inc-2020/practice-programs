/* Date		:	1.3.2011
 * Author 	:	Rakesh Malik
 * Subject	:	Delete all comments in a file
 * Assignment	:	22
 */
#include <stdio.h>

int main(int argc,char *argv[])
{
	FILE *src,*dest;		/* Source and Destination file stream */
	char c1,c2;			/* Buffer for read characters */
	int comment=0;			/* 1 when read characters are in comment 
					   else 0 */
	if((src=fopen(argv[1],"r"))==NULL)
	{
		fprintf(stderr,"ERROR : File %s read error\n",argv[1]);
		return;
	}
	if((dest=fopen(argv[2],"w"))==NULL)
	{
		fprintf(stderr,"ERROR : File %s write error\n",argv[2]);
		return;
	}
	while((c1=getc(src))!=EOF)
	{
		if(c1=='/')
			if((c2=getc(src))=='*')
				comment=1;
			else
				fprintf(dest,"%c%c",c1,c2);
		else
			putc(c1,dest);
		while(comment)
		{
			c1=getc(src);
			if(c1=='*' && (c2=getc(src))=='/')
				comment=0;
		}
	}
	fclose(src);
	fclose(dest);
}
