#include<curses.h>

void printlevel(int level);

int main()
{
	int i,c=KEY_RIGHT;
	enum {up,down,left,right};
	int point_time=0,bonus_point_time=0,length=5,score=0,speed=40,dir=right,level=0;
	int x[1000]={10,9,8,7,6},X=5,Xb=10;
	int y[1000]={10,0,0,0,0},Y=5,Yb=10;
	initscr();
	noecho();
	nodelay(stdscr,true);
	keypad(stdscr,true);
	while(1)
	{
		napms(speed);
		point_time++;
		bonus_point_time++;
		if(point_time==200)
		{
			point_time=0;
			X=rand()%(COLS-6)+3;
			Y=rand()%(LINES-6)+3;
		}
		if(bonus_point_time==500)
		{
			point_time=0;
			Xb=rand()%(COLS-6)+3;
			Yb=rand()%(LINES-6)+3;
		}
		erase();
		for(i=0;i<length;i++)
			mvprintw(y[i],x[i],"%c",(i==0)?
					(dir==right?'>':dir==left?'<':dir==up?'^':'v'):
					((y[i]+x[i])%2?'o':'O'));
		mvprintw(Y,X,"@");
		if(bonus_point_time>350 && bonus_point_time<500) mvprintw(Yb,Xb,"#");
		printlevel(level);
		mvprintw(0,5,"SNAKE");
		mvprintw(LINES-1,5,"Score : %d\t\tF1 change dificulty level\tF2 increase speed \tF3 decrease speed",score);
		for(i=length-1;i>0;i--)
		{
			x[i]=x[i-1];
			y[i]=y[i-1];
		}
		if(mvinch(y[0],x[0])=='@')
		{
			length+=2;
			mvaddch(y[0],x[0],' ');
			point_time=0;
			X=rand()%(COLS-6)+3;
			Y=rand()%(LINES-6)+3;
			score+=10;
		}
		if(mvinch(y[0],x[0])=='#')
		{
			mvaddch(y[0],x[0],' ');
			bonus_point_time=0;
			X=rand()%(COLS-6)+3;
			Y=rand()%(LINES-6)+3;
			score+=50;
		}
		if(mvinch(y[0],x[0])=='=' || mvinch(y[0],x[0])=='o' || mvinch(y[0],x[0])=='O' || mvinch(y[0],x[0])=='|')
		{
			nodelay(stdscr,false);
			mvprintw(LINES/2,COLS/2,"GAME OVER");
			refresh();
			napms(1000);
			getch();
			endwin();
			return 0;
		}
		move(LINES-1,COLS-1);
		refresh();
		c=getch();
		switch(dir)
		{
			case up:
				if(c==KEY_LEFT)
				{
					x[0]=(x[0]<=3)?COLS-3:x[0]-1;
					dir=left;
				}
				else if(c==KEY_RIGHT)
				{
					x[0]=(x[0]>=COLS-3)?3:x[0]+1;
					dir=right;
				}
				else
					y[0]=(y[0]<=3)?LINES-3:y[0]-1;
				break;
			case down:
				if(c==KEY_LEFT)
				{
					x[0]=(x[0]>=COLS-3)?3:x[0]+1;
					dir=right;
				}
				else if(c==KEY_RIGHT)
				{
					x[0]=(x[0]<=3)?COLS-3:x[0]-1;
					dir=left;
				}
				else
					y[0]=(y[0]>=LINES-3)?3:y[0]+1;
				break;
			case left:
				if(c==KEY_LEFT)
				{
					y[0]=(y[0]>=LINES-3)?3:y[0]+1;
					dir=down;
				}
				else if(c==KEY_RIGHT)
				{
					y[0]=(y[0]<=3)?LINES-3:y[0]-1;
					dir=up;
				}
				else
					x[0]=(x[0]<=3)?COLS-3:x[0]-1;
				break;
			case right:
				if(c==KEY_LEFT)
				{
					y[0]=(y[0]<=3)?LINES-3:y[0]-1;
					dir=up;
				}
				else if(c==KEY_RIGHT)
				{
					y[0]=(y[0]>=LINES-3)?3:y[0]+1;
					dir=down;
				}
				else
					x[0]=(x[0]>=COLS-3)?3:x[0]+1;
				break;
		}
		switch(c)
		{
			case 27:
				endwin();
				return 0;
			case KEY_F(2):
				if(speed>10)speed-=5;
				break;
			case KEY_F(3):
				if(speed<100)speed+=5;
			case 'p':
			case 'P':
				nodelay(stdscr,false);
				getch();
				nodelay(stdscr,true);
				break;
			case KEY_F(1):
				level=(level+1)%3;
				break;
			default:
				break;
		}
	}
}
void printlevel(int level)
{
	int i;
	switch(level)
	{
		case 0:
			break;
		case 1:
			for(i=3;i<COLS-3;i++) mvprintw(3,i,"=");
			for(i=3;i<COLS-3;i++) mvprintw(LINES-3,i,"=");
			for(i=3;i<LINES-3;i++) mvprintw(i,3,"|");
			for(i=3;i<LINES-3;i++) mvprintw(i,COLS-3,"|");
			break;
		case 2:
			mvprintw(LINES/2-5,10,"==============================");
			mvprintw(LINES/2+5,COLS-40,"==============================");
			break;
		case 3:
			
			break;
	}
}
