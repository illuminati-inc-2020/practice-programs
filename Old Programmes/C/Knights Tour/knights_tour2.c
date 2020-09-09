#include<stdio.h>
#include<string.h>

typedef struct position
{
	short x;
	short y;
}
position;

long long int count=0;			//number of comperison
long long int count2=0;			//number of solution
int MAX;
position movement[8]={	{1,2},
			{2,1},
			{-1,2},
			{-2,1},
			{1,-2},
			{2,-1},
			{-1,-2},
			{-2,-1}};
position sol[64];
short board[8][8]={	{0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0}};

void move(FILE *fp,position p,int n);
int isvalid(position p);

int main()
{
	position p;
	FILE *fp;
	int i,j;
	char filename[15]="sol_*X*_**.sol\0";
	bzero(sol,64*sizeof(position));
	printf("Enter board size :   ");
	scanf("%d",&MAX);
	printf("Enter a position :   \nx = ");
	scanf("%d",&p.x);
	printf("y = ");
	scanf("%d",&p.y);
	filename[4]=filename[6]=MAX+'0';
	filename[8]=p.x+'1';
	filename[9]=p.y+'A';
	if(p.x>=0 || p.y>=0)
	{
		fp=fopen(filename,"w");
		fprintf(fp,"SOLUTION FOR KNIGHTS TOUR IN %dX%d CHESS BOARD FROM POSITION %d%c\n\n",MAX,MAX,p.x+1,p.y+'A');
		move(fp,p,0);
		fclose(fp);
		if(count2==0)
		{
			printf("\nno solution!\n\n");
			remove(filename);
		}
		else
			printf("\nThe solution is written in file %s\n\n",filename);
	}
	else
	{
		filename[8]=filename[9]='x';
		fp=fopen(filename,"w");
		fprintf(fp,"SOLUTION FOR KNIGHTS TOUR IN %dX%d CHESS BOARD FROM ALL POSITION\n\n",MAX,MAX,p.x+1,p.y+'A');
		for(p.x=0;p.x<MAX;p.y++)
			for(p.y=0;p.y<MAX;p.y++)
				move(fp,p,0);
		fclose(fp);
		if(count2==0)
		{
			printf("\nno solution!\n\n");
			remove(filename);
		}
		else
			printf("\nThe solution is written in file %s\n\n",filename);
	}
}

void move(FILE *fp,position p,int n)
{
	count++;
	register int i,j;
	register position p1;
	board[p.x][p.y]=n+1;
	sol[n]=p;
	if(n<MAX*MAX)
	{
		if(n>=MAX*MAX-1)
		{
			count2++;
			//printf("\nsolution no %lld found",count2);
			fprintf(fp,"\nSOLUTION NO %lld :\n---------------------------\nComparison no %lld\n\n",count2,count);
			for(i=0;i<MAX;i++)
			{
				for(j=0;j<MAX;j++)
					fprintf(fp,"%d\t",board[i][j]);
				fprintf(fp,"\n");
			}
		}
		for(i=0;i<8;i++)
		{
			p1.x=p.x+movement[i].x;
			p1.y=p.y+movement[i].y;
			if(isvalid(p1))
				move(fp,p1,n+1);
		}
		board[p.x][p.y]=0;
	}
}

int isvalid(register position p)
{
	if(p.x<0 || p.y<0 || p.x>=MAX || p.y>=MAX)
		return 0;
	else if(board[p.x][p.y]!=0)
		return 0;
	else 
		return 1;
}
