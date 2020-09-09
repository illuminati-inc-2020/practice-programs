#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char *argv[])
{
	FILE *fp;
	char *mainbuf,*buf;			/* File buffer */
	char c;
	char *off;				
	long i,filesize;
	int occ;				/* Number of occurances of searchstring */
	if((fp=fopen(argv[1],"r"))==NULL)
		fprintf(stderr,"ERROR : File %s read error\n",argv[1]);
	fseek(fp,0,SEEK_END);
	mainbuf=buf=(char*)calloc((filesize=ftell(fp))+100,sizeof(char));
	rewind(fp);
	for(i=0;(c=getc(fp))!=EOF;i++)
		buf[i]=c;
	buf[filesize]='\0';
	for(occ=0;(off=strstr(buf,argv[2]))!=NULL;occ++)
		buf=off+strlen(argv[2]);
	if(strlen(argv[2])<strlen(argv[3]))
	{
		filesize=ftell(fp)+occ*(strlen(argv[3])-strlen(argv[2]));
		mainbuf=buf=(char*)realloc(mainbuf,filesize*sizeof(char)+1);
	}
	for(buf=mainbuf;(off=strstr(buf,argv[2]))!=NULL;buf=off+strlen(argv[3]))
	{
		memmove(off+strlen(argv[3]),off+strlen(argv[2]),filesize-(off-mainbuf));
		strncpy(off,argv[3],strlen(argv[3]));
	}
	if((fp=fopen(argv[1],"w"))==NULL)
		fprintf(stderr,"ERROR : File %s write error\n",argv[1]);
	fputs(mainbuf,fp);
	fclose(fp);
}
