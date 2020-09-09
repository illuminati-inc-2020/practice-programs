#ifndef __GRAPH_H
#define __GRAPH_H
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int getgraph(int G[10][10],char *fname)
{
	int i,j,v=99999,flag=0;
	char c;
	FILE *fp;
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			G[i][j]=0;
	fp=fopen(fname,"r");
	if(fp==NULL) {
		fprintf(stderr, "File \"%s\" read error\n", fname);
		exit(0);
	}
	c=getc(fp);
	for(i=j=0;feof(fp)==0;)
	{
		while(isdigit(c))
		{
			G[i][j]=G[i][j]*10+c-'0';
			c=getc(fp);
		}
		i++;
		flag=0;
		while(!isdigit(c) && c!=EOF)
		{
			if(c=='\n')
				flag=1;
			c=getc(fp);
		}
		if(flag==1)
		{
			v=i;
			i=0;
			j++;
		}
	}
	fclose(fp);
	return v;
}

#endif
