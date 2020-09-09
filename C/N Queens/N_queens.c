#include<stdio.h>
#include<stdlib.h>

#define MAX 15

typedef struct position
{
	short x;
	short y;
}
position;

void addqueen(FILE *fp,position p);
int isvalid(position p);

int n,count=0,sol=0;
short board[MAX][MAX];

int main()
{
	position p={0,0};
	char filename[20], i;
	printf("N Queens\n\n");
	printf("Enter board size :   ");
	scanf("%d",&n);
	if(n<1 || n>MAX)
		printf("\nSize of board should be between 1x1 to %dx%d\n", MAX, MAX);
	else
	{
		sprintf(filename, "sol_%dx%d.txt", n, n);
		FILE *fp=fopen(filename,"w");
		fprintf(fp, "N Queens : %dx%d", n, n);
		for(p.y=0;p.y<n;(p.y)++)
			addqueen(fp,p);
		fclose(fp);
		if(sol==0)
		{
			printf("\nNo solution\n");
			remove(filename);
		}
		else
			printf("\n%d solutions found\nOutput stored in file %s\n", sol, filename);
	}
	printf("\nPress enter...");
	getchar();
	getchar();
}

void addqueen(FILE *fp,position p)
{
	int i,j;
	count++;
	board[p.x][p.y]=1;
	position p1;
	if(p.x<n)
	{
		p1.x=p.x+1;
		for(p1.y=0;p1.y<n;(p1.y)++)
			if(isvalid(p1))
				addqueen(fp,p1);
	}
	if(p.x==n-1)
	{
		fprintf(fp,"\n\nSolution no %d :   ",++sol);
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				if(board[i][j])
					fprintf(fp,"%d%c,",i+1,j+'A');
		putc('\n',fp);
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
				fprintf(fp,"[%c]",(board[i][j])?'X':' ');
			putc('\n',fp);
		}
		putc('\n',fp);
	}
	board[p.x][p.y]=0;
}

int isvalid(position p)
{
	if(p.x<0 || p.y<0 ||p.x>n || p.y>n)
		return 0;
	int i;
	for(i=0;i<n;i++)
		if(board[p.x][i]==1)
			return 0;
	for(i=0;i<n;i++)
		if(board[i][p.y]==1)
			return 0;
	int j;
	for(i=p.x,j=p.y;i<n && j<n;i++,j++)
		if(board[i][j]==1)
			return 0;
	for(i=p.x,j=p.y;i>=0 && j>=0;i--,j--)
		if(board[i][j]==1)
			return 0;
	for(i=p.x,j=p.y;i<n && j>=0;i++,j--)
		if(board[i][j]==1)
			return 0;
	for(i=p.x,j=p.y;i>=0 && j<n;i--,j++)
		if(board[i][j]==1)
			return 0;
	return 1;
}
