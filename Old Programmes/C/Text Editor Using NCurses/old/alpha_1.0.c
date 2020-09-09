//	ASSIGNMENT 3
//	Author : Rakesh Malik
//	Date : 21.09.2010 -24.09.2010
//	B.Sc. Computer Science 2nd Year
//	Text Editor using Ncurses
//	Version 1.0

#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
#include<ctype.h>
#include<string.h>

#define MAX_WINDOWS 5

typedef struct fwin			//Structure for a file window
{
	WINDOW *win;			//Window
	char name[256];			//File name
	unsigned char saved:1;		//Flag indicates if the file is saved
	char *buffer;			//File buffer
	int bufpos;			//Current position in buffer
	int bufsize;			//Size of buffer
	short x;			//Current column
	short y;			//Current lines
}fwin;

void show_error(char*);
fwin* create_win(fwin*,char*);
void open_window(fwin*);
void delete_window(fwin*);
void instructions();
int save(fwin*,char);
int load(fwin*);

int main()	
{
	char name[256];
	fwin *w[MAX_WINDOWS];
	int current=-1,n=0,i;
	initscr();
	start_color();
	noecho();
	keypad(stdscr,true);
	init_pair(1,COLOR_BLACK,COLOR_WHITE);	
	while(1)
	{
		erase();
		mvprintw(0,0,"| F1 Help | F2 New | F3 Open | F12 Switch window | Ctrl+x Exit |");
		bkgd(COLOR_PAIR(1));
		refresh();
		if(n>0)
			mvprintw(5,10,"Files opened :");
		for(i=0;i<n;i++)
			mvprintw(7+i,12,"Window %c%.2d. %s",(i==current)?'*':' ',i+1,w[i]->name);
		switch(getch())
		{
			case KEY_F(1):		//F1	--	Help
				instructions();
				break;
			case KEY_F(2):		//F2	--	New File	
				if(n<MAX_WINDOWS)
				{
					sprintf(name,"NEWFILE_%.2d",n+1);
					w[n]=create_win(w[n],name);
					open_window(w[n++]);
					current++;
				}
				else show_error("Close at least one file to open another window");
				break;
			case KEY_F(3):		//F3	--	Open File	
				if(n<MAX_WINDOWS)
				{
					w[n]=create_win(w[n],name);
					if(load(w[n]))
					{
						open_window(w[n++]);
						current++;
					}
					else
					{
						delete_window(w[n]);
						show_error("File read error");
					}
				}
				else show_error("Close at least one file to open another window");
				break;
			case KEY_F(11):
				break;
			case KEY_F(12):
				if(n>0)
				{
					current=(current+1)%n;
					open_window(w[current]);
				}
				break;
			case 24:		//Cntrl+X	--	Exit
				endwin();
				return 0;
			default:
				break;
		}
	}
}

void show_error(char* err)
{
	char l=strlen(err)+10;
	init_pair(2,COLOR_WHITE,COLOR_RED);
	WINDOW* wine=newwin(1,l,20,(COLS-l)/2);
	wbkgd(wine,COLOR_PAIR(2));
	wrefresh(wine);
	mvwprintw(wine,0,1,"ERROR : %s",err);
	wrefresh(wine);
	wgetch(wine);
	delwin(wine);
}

fwin* create_win(fwin *fw,char*name)
{
	fw=(fwin*)malloc(sizeof(fwin));
	fw->win=newwin(LINES-4,COLS-4,2,2);
	strcpy(fw->name,name);
	fw->buffer=(char*)calloc(1,1000);
	fw->saved=0;
       	fw->bufpos=0;
       	fw->bufsize=0;
       	fw->x=0;
       	fw->y=1;
	return fw;
}

void delete_window(fwin *fw)
{
	free(fw->buffer);
	delwin(fw->win);
	free(fw);
}

int move_left(fwin *fw)
{
	int cols,lines,i;
	getmaxyx(fw->win,lines,cols);
	if(fw->bufpos>0)
	{
		if(fw->buffer[fw->bufpos]=='\n')
		{
			fw->bufpos--;
			while(fw->buffer[fw->bufpos]==' ') fw->bufpos--;
			fw->bufpos++;
		}
		if(fw->buffer[fw->bufpos-1]=='\n')
		{
			wmove(fw->win,--fw->y,fw->x=cols-1);
			while((char)winch(fw->win)==' ' && fw->x!=0)
				wmove(fw->win,fw->y,--fw->x);
			if(fw->x>0) wmove(fw->win,fw->y,++fw->x);
		}
		else if(fw->buffer[fw->bufpos-1]=='\t')
		{
			wmove(fw->win,fw->y,--fw->x);
			for(i=0;(char)winch(fw->win)==' ' && i<8-fw->x%8;i++)
				wmove(fw->win,fw->y,--fw->x);
			wmove(fw->win,fw->y,++fw->x);
		}
		else
			wmove(fw->win,fw->y,--fw->x);
		fw->bufpos--;
		return 1;
	}
	else return 0;
}

int move_right(fwin *fw)
{
	int i;
	if(fw->bufpos<fw->bufsize)
	{
		if(fw->buffer[fw->bufpos]=='\n')
			wmove(fw->win,++fw->y,fw->x=0);
		else if(fw->buffer[fw->bufpos]=='\t')
			for(i=0;i<fw->x%8;i++)
				wmove(fw->win,fw->y,++fw->x);
		else
			wmove(fw->win,fw->y,++fw->x);
		fw->bufpos++;
		return 1;
	}
	else return 0;
}

void open_window(fwin *fw)
{
	int move_right(fwin*),move_left(fwin*);
	int lines,cols,c;
	char x=0,y=1,xmax,ymax,x1,y1,replace=0,*mode[2]={"insert ","replace"};
	keypad(fw->win,true);
	getmaxyx(fw->win,lines,cols);
	init_pair(3,COLOR_WHITE,COLOR_BLACK);
	wbkgd(fw->win,COLOR_PAIR(3));
	mvwprintw(fw->win,0,0,"%s",fw->name);
	mvwprintw(fw->win,lines-1,5,"%7s(%d,%d)         ",mode[replace],fw->x,fw->y);
	while(1)
	{
		erase();
		mvprintw(0,0,"| F1 Help | F2 New | F3 Open | F5 Save | F6 Save as | Esc Minimize window | Cntrl+Insert Close window |");
		refresh();
		werase(fw->win);
		if(fw->bufsize%1000==0 && fw->bufsize!=0) fw->buffer=realloc(fw->buffer,fw->bufsize+1000);
		mvwprintw(fw->win,0,0,"%s",fw->name);
		wmove(fw->win,fw->y,fw->x);
		wmove(fw->win,fw->y,fw->x);
		mvwprintw(fw->win,lines-1,5,"Mode : %7s\t\t\t\tLine : %d\tCharacter : %d",mode[replace],fw->y,fw->x);
		mvwprintw(fw->win,lines-1,100,"%c",fw->buffer[fw->bufpos]);
		mvwprintw(fw->win,1,0,fw->buffer);
		wmove(fw->win,fw->y,fw->x);
		wrefresh(fw->win);
		c=getch();
		if(isprint(c) || isspace(c))
		{
			if(!replace)
				memmove(fw->buffer+fw->bufpos+1,fw->buffer+fw->bufpos,fw->bufsize-fw->bufpos);
			fw->buffer[fw->bufpos++]=c;
			switch(c)
			{
				case '\t':
					wmove(fw->win,fw->y,fw->x+=8-fw->x%8);
					break;
				case '\n':
					wmove(fw->win,++fw->y,fw->x=0);
					break;
				default:
					wmove(fw->win,fw->y,++fw->x);	
					break;
			}
			fw->bufsize++;
		}
		else
		{
			switch(c)
			
			{
				case 127:		//Backspace
					if(move_left(fw))
					{
						memmove(fw->buffer+fw->bufpos,fw->buffer+fw->bufpos+1,
								fw->bufsize-fw->bufpos);
						fw->bufsize--;
					}
					break;
				case KEY_UP:		//Up
					if(fw->y>1)
					{
						int i,j;
						for(i=0;fw->buffer[fw->bufpos]!='\n';i++)
							move_left(fw);
						do if(!move_left(fw)) break;
						while(fw->buffer[fw->bufpos-1]!='\n');
						for(j=1;j<i && fw->buffer[fw->bufpos]!='\n';j++)
							move_right(fw);
					}
					break;
				case KEY_DOWN:		//Down
					{
						int i;
						for(i=0;fw->buffer[fw->bufpos]!='\n' && fw->buffer[fw->bufpos];i++)
							move_right(fw);
						if(fw->buffer[fw->bufpos])
						{
							i+=cols-fw->x-1;
							for(;i<cols;i++)
								move_right(fw);
						}
					}
					break;
				case KEY_RIGHT:		//Right
					move_right(fw);
					break;
				case KEY_LEFT:		//Left
					move_left(fw);
					break;	
				case KEY_DC:		//Delete
					if(fw->bufsize>0)
					{
						memmove(fw->buffer+fw->bufpos,fw->buffer+fw->bufpos+1,
								fw->bufsize-fw->bufpos);
						fw->bufsize--;
					}
					break;
				case KEY_F(5):		//F5
					if(!save(fw,false)) show_error("File write error");
					break;
				case KEY_F(6):		//F6
					if(!save(fw,true)) show_error("File write error");
					break;
				case 535:		//Ctrl+Insert
					replace=!replace;
					wmove(fw->win,lines-1,5);
					waddstr(fw->win,mode[replace]);
					wmove(fw->win,fw->y,fw->x);
					break;
				case 27:		//Esc
					return;
				case 24:		//Cntrl + insert
					delete_window(fw);
					return;
			}
		}
		wrefresh(fw->win);
		refresh();
	}
}

void instructions()
{
	init_pair(2,COLOR_WHITE,COLOR_BLUE);
	refresh();
	WINDOW* wini=newwin(20,70,5,20);
	wbkgd(wini,COLOR_PAIR(2));
	waddstr(wini,"\t\t\tHELP\n");
	waddstr(wini,"\tctrl + insert\t\tChange mode (insert/replace)\n");
	wrefresh(wini);
	getch();
	wclear(wini);
	refresh();
	delwin(wini);
}

int save(fwin *fw,char save_as)
{
	FILE* fp;
	int i,successful=0;
	char c=0,filename[256];
	init_pair(2,COLOR_BLUE,COLOR_YELLOW);
	WINDOW* wins=newwin(1,80,20,20);
	wbkgd(wins,COLOR_PAIR(2));
	wrefresh(wins);
	if(save_as || !fw->saved)
	{
		wprintw(wins,"SAVE : Enter file name :  ");
		wrefresh(wins);
		echo();
		wscanw(wins,"%s",filename);
		noecho();
	}
	wclear(wins);
	wrefresh(wins);
	fp=fopen(filename,"w");
	if(fp && !ferror(fp))
	{
		for(i=0;fw->buffer[i];i++)
			putc(fw->buffer[i],fp);
		fw->saved=1;
		strcpy(fw->name,filename);
		mvwprintw(wins,0,5,"File saved successfully...");
		successful=1;
		fclose(fp);
		wrefresh(wins);
		napms(500);
		wclear(wins);
	}
	delwin(wins);
	erase();
	refresh();
	return successful;
}

int load(fwin* fw)
{
	FILE* fp;
	int i,successful=0;
	char c=0,filename[256];
	init_pair(2,COLOR_BLUE,COLOR_YELLOW);
	WINDOW* winl=newwin(1,80,20,20);
	wbkgd(winl,COLOR_PAIR(2));
	wprintw(winl,"LOAD : Enter file name :  ");
	wrefresh(winl);
	echo();
	wscanw(winl,"%s",filename);
	noecho();
	fp=fopen(filename,"r");
	wclear(winl);
	wrefresh(winl);
	if(fp && !ferror(fp))
	{
		for(i=0;;i++)
		{
			if((c=getc(fp))==EOF) break;
			fw->buffer[i]=c;
		}
		fw->bufsize=strlen(fw->buffer);
		strcpy(fw->name,filename);
		mvwprintw(winl,0,5,"File loaded successfully...");
		successful=1;
		fclose(fp);
		wrefresh(winl);
		napms(500);
		wrefresh(winl);
		wclear(winl);
	}
	delwin(winl);
	erase();
	refresh();
	return successful;
}
