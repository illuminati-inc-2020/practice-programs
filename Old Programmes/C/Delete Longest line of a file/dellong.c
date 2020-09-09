#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char *argv[])
{
	FILE *fp;
	char *buf,*line;						/* File buffer */
	long i,j,jmax,filesize;
	size_t size;
	if((fp=fopen(argv[1],"r"))==NULL)
		fprintf(stderr,"ERROR : File %s read error\n",argv[1]);
	fseek(fp,0,SEEK_END);
	buf=(char*)calloc((filesize=ftell(fp))+1,sizeof(char));
	line=(char*)calloc((filesize=ftell(fp))+1,sizeof(char));
	rewind(fp);
	for(i=j=0,jmax=0;j>=0;i++)
		if((j=getline(&line,&size,fp))>jmax)
			jmax=j;
	rewind(fp);
	buf[0]='\0';
	printf("\nLongest line(s) (length %d):\n",jmax);
	for(i=j=0;j>=0;i++)
		if((j=getline(&line,&size,fp))<jmax)
			strcat(buf,line);
		else
			printf("(%4d)  %s\n",i,line);
	free(line);
	if((fp=fopen(argv[1],"w"))==NULL)
		fprintf(stderr,"ERROR : File %s write error\n",argv[1]);
	fputs(buf,fp);
	free(buf);
	fclose(fp);
}
