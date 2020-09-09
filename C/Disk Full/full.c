#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

time_t t1,t2;
int file_no;
unsigned long filesize(FILE*);
int write(char[]);

int main() {
	time(&t1);
	for(file_no=0;;file_no++) {
		char name[50];
		sprintf(name,"__temp_%6.6d.tmp", file_no);
		if(write(name)==0)
		break;
	}
	printf("\nDisk full\nPress enter to quit...");
	getch();
	return 0;
}

/* Returns 0 if disk is full and returns 1 if a 2GB file is full written */
int write(char name[]) {
	FILE *fp=fopen(name, "w");
	unsigned long i, n=8*1024*1024, m=256;
	for(i=0;i<m;i++) {
		unsigned long j, elapsedtime;
		system("cls");
		printf("\n%u MB written ",file_no*(m*n/(1024*1024))+(n*i/(1024*1024)));
		printf("\nWriting %u MB to file %s...", (m*n)/(1024*1024), name);
		elapsedtime=difftime(time(&t2), t1);
		printf("\nTotal time elapsed : %u min %u sec", elapsedtime/60, elapsedtime%60);
		for(j=0;j<n;j++)
			putc('\0', fp);
		if(n*(i+1)!=ftell(fp)) {
			fclose(fp);
			return 0;
		}
	}
	fclose(fp);
	return 1;
}