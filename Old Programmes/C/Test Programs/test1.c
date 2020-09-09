#include<stdio.h>

int main()
{
	FILE *fp;
	fp=fopen("file1","r+");
//	fputs("RAKESH",fp);
	fseek(fp,-4,2);
	fflush(fp);
	fputs("MALIK",fp);
	printf("%d",ftell(fp));
	fclose(fp);
}
