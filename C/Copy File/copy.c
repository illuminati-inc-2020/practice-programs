#include <stdio.h>

int main(int argc,char *argv[])
{
	FILE *src,*dest;
	char buf;
	if((src=fopen(argv[1],"r"))==NULL)
		fprintf(stderr,"ERROR : File %s read error\n",argv[1]);
	if((dest=fopen(argv[2],"w"))==NULL)
		fprintf(stderr,"ERROR : File %s write error\n",argv[2]);
	while((buf=getc(src))!=EOF)
		putc(buf,dest);
	fclose(src);
	fclose(dest);
}
