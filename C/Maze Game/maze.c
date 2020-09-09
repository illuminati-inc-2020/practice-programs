#include<stdio.h>
#include<stdlib.h>

typedef struct position
{
	short x;
	short y;
}
position;

char maze[30][100];

void play();
void move(position p,int dir);
int getnum(void);

int main()
{
	system("clear");
	printf("\n\n\n\n\n\n\t\t\e[31;1mMAZE\n\n\t\t\e[37;1m1. Play\n\t\t0. Quit\n\n\n\t\t\e[33;1mEnter your choice_\e[37;1m");
	while(1)
	{
		switch(getnum())
		{
			case 1:
				play();
				break;
			case 0:
				system("clear");
				printf("\n\n\n\n\n\n\t\t\e[34;1m***********\n\t\t\e[32;1m THANK YOU\n\t\t\e[34;1m***********\e[37;1m\n\n\n");
				sleep(1);
				system("clear");
				exit(0);
				break;
			default:
				break;
		}
	}
}

void play()
{
	int i;
	FILE *lev;
	lev=fopen("1.lev","r");
	for(i=0;i<30;i++)
	{
		fgets(maze[i],99,lev);
		//getc(lev);
	}
	position p={1,1};
	move(p,2);
	fclose(lev);
}

void move(position p,int dir)
{
	int i,j;
	position p1;
	system("clear");
	printf("\e[33;1m");
	for(i=0;i<30;i++)
	{
		for(j=0;j<98;j++)
			if(i==p.y && j==p.x)
			{
				printf("\e[32;1m");
				putchar(dir==8?'^':dir==2?'v':dir==4?'<':'>');
				printf("\e[33;1m");
			}
			else
				putchar(maze[i][j]);
		putchar('\n');
	}
	printf("\e[34;1m");
	printf("\n\t    (up) 8\n(left) 4\t+\t(right) 6\t\t\t\t0: Back to Main Menu\n\t   (down) 2");
	printf("\e[33;1m");
	printf("\n\n\t\t\tEnter your choice_\e[37;1m");
	switch(getnum())
	{
		case 8:			//Up
			p1.x=p.x;
			p1.y=p.y-1;
			if(maze[p1.y][p1.x]==' ')
				move(p1,8);
			else
				move (p,8);
			break;
		case 2:			//Down
			p1.x=p.x;
			p1.y=p.y+1;
			if(maze[p1.y][p1.x]==' ')
				move(p1,2);
			else
				move (p,2);
			break;
		case 4:			//Left
			p1.x=p.x-1;
			p1.y=p.y;
			if(maze[p1.y][p1.x]==' ')
				move(p1,4);
			else
				move (p,4);
			break;
		case 6:			//Right
			p1.x=p.x+1;
			p1.y=p.y;
			if(maze[p1.y][p1.x]==' ')
				move(p1,6);
			else
				move (p,6);
			break;
		case 0:
			main();
		default :
			move (p,dir);
	}
}

int getnum(void)
{
	int n;
	scanf("%d",&n);
	return n;
}
