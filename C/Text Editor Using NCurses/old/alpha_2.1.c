
/*	ASSIGNMENT 3
 *	Author : Rakesh Malik
 *	Date : 26.09.2010
 *	B.Sc. Computer Science 2nd Year
 *	Text Editor using Ncurses
 *	Version 2.1
 *	(This version includes cut, copy, paste)
 */

#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
#include<ctype.h>
#include<string.h>

#define MAX_WINDOWS 10
#define BUFFER_SIZE 1000
#define COPY_BUFFER_SIZE 200

typedef struct fwin			//Structure for a file window
{
	WINDOW *win;			//Window
	char name[256];			//File name
	char *buffer;			//File buffer
	int bufpos;			//Size of buffer
	char saved;			//Flag indicates the file is saved(1)/Not saved(0)
}fwin;

void show_messege(char*,char);		//Prints a messege in a small window
fwin* create_win(fwin*,char*);		//Initilizes a file window
int open_window(fwin*);			/* Opens a file window to edit
					 * returns 1 when minimized and 0 when closed */
void delete_window(fwin*);		//Frees a created file window
void instructions();			//Prints key helps for the text editor in a window
int save(fwin*,char);			/* Saves the contents of current window as existing(0)/new(1) file
					 * returns 1 on success and 0 on failure */
int load(fwin*);			/* Loads a file in a new window to edit
					 * returns 1 on success and 0 on failure */

int main()	
{
	char name[256];					//Buffer for file name
	fwin *w[MAX_WINDOWS];				//File windows
	int current=-1;					//Index of the window currently accessing
	int n=0;					//Number of windows opened
	int i;						//used for loops
	int state=1;					//holds return state for a current window colsed(0)/minimized(1)
	initscr();
	start_color();
	noecho();
	keypad(stdscr,true);
	init_pair(1,COLOR_BLACK,COLOR_WHITE);	
	init_pair(2,COLOR_WHITE,COLOR_RED);
	init_pair(3,COLOR_WHITE,COLOR_BLACK);
	init_pair(4,COLOR_WHITE,COLOR_BLUE);
	init_pair(5,COLOR_YELLOW,COLOR_BLACK);
	init_pair(7,COLOR_MAGENTA,COLOR_BLACK);
	while(1)
	{
		erase();
		if(n==0 || n==1) mvprintw(0,0,"| F2 New File | F3 Open File | F1 Help | Ctrl+x Exit |");
		else if(n==MAX_WINDOWS) mvprintw(0,0,"| F11 Switch Window | F12 Open Selected Window | F1 Help | Ctrl+x Exit |");
		else mvprintw(0,0,"| F2 New File | F3 Open File | F11 Switch Window | F12 Open Selected Window | F1 Help | Ctrl+x Exit |");
		bkgd(COLOR_PAIR(1));
		mvchgat(0,0,COLS,A_NORMAL|A_UNDERLINE,1,NULL);
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
					state=open_window(w[n++]);
					current++;
				}
				else show_messege("Close at least one file to open another window",1);
				break;
			case KEY_F(3):		//F3	--	Open File	
				if(n<MAX_WINDOWS)
				{
					w[n]=create_win(w[n],name);
					if(load(w[n]))
					{
						w[n]->saved=1;
						state=open_window(w[n++]);
						current++;
					}
					else delete_window(w[n]);
				}
				else show_messege("Close at least one file to open another window",1);
				break;
			case KEY_F(11):		//F11  --  Switch window
				if(n>1)current=(current+1)%n;
				break;
			case KEY_F(12):		//F12  --  Open selected window
				if(n>1) state=open_window(w[current]);
				break;
			case 24:		//Cntrl+X	--	Exit
				if(n>0)
				{
					char c='Y';
					char msg[300];
					for(i=0;i<n && c!='C';i++)
					{
						bkgd(COLOR_PAIR(1));
						refresh();
						sprintf(msg,"do you want to save %s : yes(y)/no(n)/cancel(c)",w[i]->name);
						show_messege(msg,0);
						c=toupper(getch());
						switch(c)
						{
							case 'Y':
								if(save(w[i],0))
								{
									delete_window(w[i]);
									memmove(w+i,w+i+1,(n-i-1)*sizeof(fwin*));
									n--;
								}
								else	c='C';
								break;
							case 'C':
							case 'N':
								break;
							default:
								i--;
								break;
						}
					}
				}
				endwin();
				return 0;
			default:
				break;
		}
		if(state==0)
		{
			delete_window(w[current]);
			memmove(w+current,w+current+1,(n-current-1)*sizeof(fwin*));
			n--;
			if(n==0) current=-1;
			else current--;
		}
	}
}

void show_messege(char* err,char stop)
{
	char l=strlen(err)+4;				//Length of messege
	WINDOW* wine=newwin(3,l,20,(COLS-l)/2);
	wbkgd(wine,COLOR_PAIR(2));
	wrefresh(wine);
	mvwprintw(wine,1,2,"%s",err);
	wrefresh(wine);
	if(stop) wgetch(wine);
	wclear(wine);
	delwin(wine);
}

fwin* create_win(fwin *fw,char*name)
{
	fw=(fwin*)malloc(sizeof(fwin));			//Allocating space for the structure
	fw->win=newwin(LINES-4,COLS-2,2,1);		//Creating window
	strcpy(fw->name,name);				//Copying the name
	fw->buffer=(char*)calloc(1,BUFFER_SIZE);	//Allocating space for the buffer
       	fw->bufpos=0;					//Setting buffer position to beginning
	fw->saved=0;					//Flag reset,indicates not saved
	return fw;
}

void delete_window(fwin *fw)
{
	free(fw->buffer);				//Freeing buffer
	delwin(fw->win);				//Deleting window
	free(fw);					//Freing structure
}

int open_window(fwin *fw)
{
	WINDOW *head,*tail;
	head=newwin(1,COLS-2,1,1);
	tail=newwin(1,COLS-2,LINES-2,1);
	int c;						//Used for reading character
	int i,j;					//Used for loops
	int x=0,y=1;					//'x'=current line,'y'=current column in window
	int lines,cols;					//'lines'=max lines,'cols'=max columns in window
	int bufsize;					//Number of characters in buffer
	char replace=0;					//Flag indicates Replace(1)/Insert(0) mode
	char *mode[2]={"insert ","replace"};		//String to be used by flag 'replace'
	int hstart=-1,hend=-1;				//highlight position start 'hstart' and endd 'hend'
	char copy_buffer[COPY_BUFFER_SIZE];				//Buffer for copy
	keypad(fw->win,true);
	getmaxyx(fw->win,lines,cols);
	wbkgd(fw->win,COLOR_PAIR(3));
	wbkgd(head,COLOR_PAIR(3));
	wbkgd(tail,COLOR_PAIR(3));
	while(1)
	{
		erase();
		mvprintw(0,0,"| F4 Save | F5 Save as | F6 Cut | F7 Copy | F8 Paste | Esc Minimize | Cntrl+X Close |");
		mvchgat(0,0,COLS,A_NORMAL|A_UNDERLINE,1,NULL);
		refresh();
		
		werase(head);
		mvwprintw(head,0,(cols-strlen(fw->name))/2,"%s",fw->name);
		mvwchgat(head,0,(cols-strlen(fw->name))/2,strlen(fw->name),A_NORMAL|A_BOLD,5,NULL);
		wrefresh(head);
		
		werase(tail);
		mvwprintw(tail,0,5,"Mode : %7s\t\t\t\tLine : %d\tCharacter : %d",mode[replace],y,x);
		mvwchgat(tail,0,5,cols-5,A_NORMAL|A_BOLD,7,NULL);
		wrefresh(tail);
		
		werase(fw->win);
		bufsize=strlen(fw->buffer);
		mvwprintw(fw->win,0,0,fw->buffer);
		wmove(fw->win,0,0);
		for(i=0,x=0,y=0;i<fw->bufpos;i++)	//Synchronization of buffer position with cursor position
		{
			if(i>=hstart && i<=hend) wchgat(fw->win,1,A_STANDOUT,3,NULL);
			if(fw->buffer[i]=='\n')
				wmove(fw->win,++y,x=0);
			else if(fw->buffer[i]=='\t')
				if(8*(1+x/8)>=cols)wmove(fw->win,++y,x=0);
				else wmove(fw->win,y,x=8*(1+x/8));
			else
				if(x==cols-1)wmove(fw->win,++y,x=0);
				else wmove(fw->win,y,++x);
		}
		wrefresh(fw->win);
		c=getch();				//Reading character
		if(isprint(c) || isspace(c))			//If charecter is to be printed
		{
			if(!replace)
				memmove(fw->buffer+fw->bufpos+1,fw->buffer+fw->bufpos,bufsize-fw->bufpos);
			fw->buffer[fw->bufpos++]=c;
			hstart=hend=fw->bufpos;
		}
		else						//If control character
		{
			switch(c)
			
			{
				case 127:		//Backspace
					if(fw->bufpos>0)
					{
						fw->bufpos--;
						hstart=hend=fw->bufpos;
						memmove(fw->buffer+fw->bufpos,fw->buffer+fw->bufpos+1,bufsize-fw->bufpos);
					}
					break;
				case 561:		//ctrl+up
				case KEY_UP:		//Up
					if(fw->buffer[fw->bufpos]=='\n') fw->bufpos--;
					for(i=0;fw->buffer[fw->bufpos]!='\n' && fw->bufpos>0;i++)
						fw->bufpos--;
					if(fw->bufpos>0)
					{
						fw->bufpos--;
						while(fw->buffer[fw->bufpos]!='\n' && fw->bufpos>0)
							fw->bufpos--;
						if(fw->bufpos>0) fw->bufpos++;
						for(j=0;j<i-1 && fw->buffer[fw->bufpos]!='\n';j++)
							fw->bufpos++;
					}
					if(c==KEY_UP) hstart=hend=fw->bufpos;
					else hend=fw->bufpos;
					break;
				case 520:		//ctrl+down
				case KEY_DOWN:		//Down
					i=0;
					if(fw->buffer[fw->bufpos]=='\n')
					{
						fw->bufpos--;
						i++;
					}
					for(;fw->buffer[fw->bufpos]!='\n' && fw->bufpos>0;i++)
						fw->bufpos--;
					if(fw->buffer[fw->bufpos]=='\n') fw->bufpos++;
					else i++;
					while(fw->buffer[fw->bufpos]!='\n' && fw->bufpos<bufsize)
						fw->bufpos++;
					if(fw->bufpos<bufsize)
					{
						if(fw->buffer[fw->bufpos]=='\n') fw->bufpos++;
						if(fw->bufpos<bufsize)
						{
							j=0;
							while(j<i-1 && fw->buffer[fw->bufpos]!='\n' && fw->bufpos<bufsize)
							{
								fw->bufpos++;					
								j++;
							}
						}
					}
					if(c==KEY_DOWN) hstart=hend=fw->bufpos;
					else hend=fw->bufpos;
					break;
				case 540:		//ctrl+left
				case KEY_LEFT:		//Left
					if(fw->bufpos>=0)
					{
						fw->bufpos--;
						if(c==KEY_LEFT) hstart=hend=fw->bufpos;
						else hend=fw->bufpos;
					}
					break;	
				case 555:		//ctrl+right
				case KEY_RIGHT:		//Right
					if(fw->bufpos<bufsize)
					{
						fw->bufpos++;
						if(c==KEY_RIGHT) hstart=hend=fw->bufpos;
						else hend=fw->bufpos;
					}
					break;
				case KEY_DC:		//Delete
					memmove(fw->buffer+hstart,fw->buffer+hend+1,bufsize-hend+1);
					fw->bufpos=hend=hstart=hstart;
					break;
				case KEY_F(4):		//F4  --  Save
					save(fw,false);
					break;
				case KEY_F(5):		//F5  --  Save as
					save(fw,true);
					break;
				case KEY_F(6):		//F6  --  Cut
					bzero(copy_buffer,COPY_BUFFER_SIZE);
					strncpy(copy_buffer,fw->buffer+hstart,hend-hstart+1);
					memmove(fw->buffer+hstart,fw->buffer+hend+1,bufsize-hend+1);
					fw->bufpos=hend=hstart=hstart;
					break;
				case KEY_F(7):		//F7  --  Copy
					bzero(copy_buffer,COPY_BUFFER_SIZE);
					strncpy(copy_buffer,fw->buffer+hstart,hend-hstart+1);
					break;
				case KEY_F(8):		//F8  --  Paste
					memmove(fw->buffer+fw->bufpos+strlen(copy_buffer),
							fw->buffer+fw->bufpos,
							bufsize-fw->bufpos);
					strncpy(fw->buffer+fw->bufpos,copy_buffer,strlen(copy_buffer));
					break;
				case 530:		//cntl+home
				case KEY_HOME:		//home
					if(fw->buffer[fw->bufpos]=='\n') fw->bufpos--;
					while(fw->buffer[fw->bufpos]!='\n' && fw->bufpos>0) fw->bufpos--;
					if(fw->buffer[fw->bufpos]=='\n') fw->bufpos++;
					if(c==KEY_HOME) hstart=hend=fw->bufpos;
					else hend=fw->bufpos;
					break;
				case 525:		//cntl+end
				case KEY_END:		//end
					while(fw->buffer[fw->bufpos]!='\n' && fw->bufpos<bufsize) fw->bufpos++;
					if(c==KEY_END) hstart=hend=fw->bufpos;
					else hend=fw->bufpos;
					break;
				case 535:		//Ctrl+Insert  --  Change mode insert/replace
					replace=!replace;
					wmove(fw->win,lines-1,5);
					waddstr(fw->win,mode[replace]);
					break;
				case 27:		//Esc  -- Minimize window
					return 1;
				case 24:		//Cntrl+X  --  Close window
					show_messege("Do you want to save : yes(y)/no(n)/cancel(c)",0);
					switch(toupper(getch()))
					{
						case 'Y':
							if(save(fw,false)) return 0;
							else show_messege("File write error",1);
							break;
						case 'N':
							return 0;
						default:
							break;
					}
			}
		}
		wrefresh(fw->win);
		refresh();
	}
}

void instructions()
{
	refresh();
	WINDOW* wini=newwin(20,70,5,20);
	wbkgd(wini,COLOR_PAIR(4));
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
	int i,flag=0;
	char c=0,filename[256];
	WINDOW* wins=newwin(3,80,20,20);
	wbkgd(wins,COLOR_PAIR(2));
	wrefresh(wins);
	if(save_as || !fw->saved)
	{
		mvwprintw(wins,1,2,"SAVE : Enter file name :  ");
		wrefresh(wins);
		echo();
		wscanw(wins,"%s",filename);
		noecho();
	}
	else
		strcpy(filename,fw->name);
	wclear(wins);
	wrefresh(wins);
	fp=fopen(filename,"w");
	if(fp && !ferror(fp))
	{
		for(i=0;fw->buffer[i];i++)
			putc(fw->buffer[i],fp);
		fw->saved=1;
		strcpy(fw->name,filename);
		mvwprintw(wins,1,2,"File %s saved successfully...",fw->name);
		fclose(fp);
		flag=1;
	}
	else mvwprintw(wins,1,2,"File write error",fw->name);
	wrefresh(wins);
	napms(500);
	wclear(wins);
	delwin(wins);
	erase();
	refresh();
	return flag;
}

int load(fwin* fw)
{
	FILE* fp;
	int i,flag=0;
	char c=0,filename[256];
	WINDOW* winl=newwin(3,80,20,20);
	wbkgd(winl,COLOR_PAIR(2));
	mvwprintw(winl,1,2,"LOAD : Enter file name :  ");
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
		strcpy(fw->name,filename);
		mvwprintw(winl,1,2,"File %s loaded successfully...",fw->name);
		fclose(fp);
		flag=1;
	}
	else mvwprintw(winl,1,2,"File read error",fw->name);
	wrefresh(winl);
	napms(500);
	wrefresh(winl);
	wclear(winl);
	delwin(winl);
	erase();
	refresh();
	return 1;
}
