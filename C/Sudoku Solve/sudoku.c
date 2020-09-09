#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

typedef struct square
{
	short x;
	short y;
}
square;

int count=0,sol=0;
short matrix[9][9],questn[9][9];

void sudoku(FILE *fp,square p);
int rulemaintained(square p,short n);

int main(int argc, char* argv[])
{
	int i,j;
	FILE *fp;
	square p={0,0};
	char filename[1000];
	if(argc<=1)
	{
		printf("Enter the filename :   ");
		scanf("%s",filename);
	}
	else
		strcpy(filename, argv[1]);
	printf("Input file : %s\n", argv[1]);
	fp=fopen(filename,"r");
	if(fp==NULL || ferror(fp))
	{
		printf("Enter the sudoku in file %s\n\n",filename);
		exit(0);
	}
	for(i=0;i<9;i++)
		for(j=0;j<9;j++)
		{
			questn[i][j]=matrix[i][j]=getc(fp)-'0';
			getc(fp);
		}
	fclose(fp);
	printf("The sudoku is :\n");
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			printf("%d ",matrix[i][j]);
			if(j==2 || j==5) putchar(' ');
		}
		putchar('\n');
		if(i==2 || i==5) putchar('\n');
	}
	printf("\n\nThe solution is written in %s\n", filename);
	fp=fopen(filename,"a");
	sudoku(fp,p);
	fclose(fp);
}

void sudoku(FILE *fp,square p)
{
	count++;
	int i,j;
	square p1;
	p1.x=p.x+1;
	p1.y=p.y;
	if(p1.x>=9)
	{
		p1.x=0;
		p1.y=p.y+1;
	}
	if(count>81)
	{
		fprintf(fp,"\n\nSolution no %d :\n",++sol);
		for(i=0;i<9;i++)
		{
			for(j=0;j<9;j++)
			{
				fprintf(fp,"%d ",matrix[i][j]);
				if(j==2 || j==5) putc(' ',fp);
			}
			fprintf(fp,"\n");
			if(i==2 || i==5) putc('\n',fp);
		}
	}
	if(questn[p.x][p.y]==0)
	{
		if(p.y<9)
			for(i=1;i<=9;i++)
				if(rulemaintained(p,i))
					{
						matrix[p.x][p.y]=i;
						sudoku(fp,p1);
					}
		matrix[p.x][p.y]=0;
	}
	else
		sudoku(fp,p1);
	count--;
}

int rulemaintained(square p,short n)
{
	short i,j,rowmin,colmin;
	for(i=0;i<9;i++)
		if(matrix[i][p.y]==n)
			return 0;
	for(i=0;i<9;i++)
		if(matrix[p.x][i]==n)
			return 0;
	rowmin=p.x-p.x%3;
	colmin=p.y-p.y%3;
	for(i=rowmin;i<rowmin+3;i++)
		for(j=colmin;j<colmin+3;j++)
			if(matrix[i][j]==n)
				return 0;
	return 1;
}
