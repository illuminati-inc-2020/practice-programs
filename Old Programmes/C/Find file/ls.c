#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc,char *argv[])
{
	DIR *dp=opendir((argc>1)?argv[1]:".");
	struct dirent *entry;
	while((entry=readdir(dp))!=NULL)
	{
		printf("%s\n",entry->d_name);
	}
	closedir(dp);
}
