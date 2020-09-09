#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

char whole_word=0,match_case=0;

void find(char *dname,const char *name);

int main(int argc,char *argv[])
{
	int i;
	char dname[1000]="\0",name[256]="\0";
	for(i=1;i<argc;i++)
	{
		if(argv[i][0]=='-')
		{
			if(strcmp(argv[i],"-w")==0)		whole_word=1;
			else if(strcmp(argv[i],"-c")==0)	match_case=1;
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

void find(char *dname,const char *name)
{
	DIR *cdp,*dp=opendir(dname);
	struct dirent *entry;
	char path[1000];
	struct stat st;
	if(dp==NULL) return;
	while((entry=readdir(dp))!=NULL)
	{
		if(strcmp(entry->d_name,".")==0		||
		   strcmp(entry->d_name,"..")==0	)
			continue;
		sprintf(path,"%s/%s",dname,entry->d_name);
		stat(path,&st);
		if(	( whole_word &&  match_case && strcmp(entry->d_name,name)==0		)||
			( whole_word && !match_case && strcasecmp(entry->d_name,name)==0	)||
			(!whole_word &&  match_case && strstr(entry->d_name,name)		)||
			(!whole_word && !match_case && strcasestr(entry->d_name,name)		))
			if(S_ISREG(st.st_mode))
				printf("%s\n",path);
		if(!S_ISDIR(st.st_mode))
			continue;
		if(cdp=opendir(path))
		{
			find(path,name);
			closedir(cdp);
		}
	}
	closedir(dp);
}
