#include<stdio.h>

void move(FILE *fp,int n,char a,char b,char c);

int main()
{
	int n;
	FILE *fp;
	char filename[16]="solution_**.sol\0";
	printf("Enter number of disks :   ");
	scanf("%d",&n);
	if(n<10)
	{
		filename[9]='0';
		filename[10]=(char)(n+'0');
	}
	else
	{
		filename[9]=(char)(n/10+'0');
		filename[10]=(char)(n-(n/10)*10+'0');
	}
	fp=fopen(filename,"w");
	fprintf(fp,"TOWERS OF HANOI SOLUTION FOR %d DISKS\n\n",n);
	move(fp,n,'A','B','C');
	fclose(fp);
	printf("Solution wrote in file %s\n\n",filename);
}

void move(FILE *fp,int n,char a,char b,char c)
{
	if(n==1)
		fprintf(fp,"\nmove disk %d from %c to %c",n,a,c);
	else if(n>1)
	{
		move(fp,n-1,a,c,b);
		fprintf(fp,"\nmove disk %d from %c to %c",n,a,c);
		move(fp,n-1,b,a,c);
	}
}
