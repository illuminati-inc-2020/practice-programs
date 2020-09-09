#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

char match_case=0;

void find(char *dname,char *name);
int search(char *s1,char *s2);

int main(int argc,char *argv[])
{
	int i;
	char dname[1000]="\0",name[256]="\0";
	for(i=1;i<argc;i++)
	{
		if(argv[i][0]=='-')
		{
			if(strcmp(argv[i],"-c")==0)	match_case=1;
		}
		else if(name[0]=='\0')
			strcpy(name,argv[i]);
		else if(dname[0]=='\0')
			strcpy(dname,argv[i]);
	}
	if(name[0]=='\0')
	{
		fprintf(stderr,"ERROR : No input files\n");
		return 1;
	}
	find(dname,name);
	return 0;
}

void find(char *dname,char *name)
{
	DIR *cdp,*dp=opendir(dname);
	struct dirent *entry;
	char path[1000];
	if(dp==NULL) return;
	while((entry=readdir(dp))!=NULL)
	{
		if(strcmp(entry->d_name,".")==0		||
		   strcmp(entry->d_name,"..")==0	)
			continue;
		sprintf(path,"%s/%s",dname,entry->d_name);
		if(search(entry->d_name,name))
			printf("%s\n",path);
		if(cdp=opendir(path))
		{
			find(path,name);
			closedir(cdp);
		}
	}
	closedir(dp);
}

int search(char *s1,char *s2)
{
	char part[10][256];
	return 1;
}
