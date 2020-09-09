
/*	ASSIGNMENT 3
 *	Author : Rakesh Malik
 *	Date : 26.09.2010
 *	B.Sc. Computer Science 2nd Year
 *	Text Editor using Ncurses
 *	Version 3.2
 *	(version 3.0 includes cut,copy,paste)
 *	(version 3.1 includes search and replace)
 */

#include<stdlib.h>
#include<curses.h>
#include<ctype.h>
#include<string.h>

#define MAX_WINDOWS 10
#define BUFFER_SIZE 100000
#define COPY_BUFFER_SIZE 1000

typedef struct fwin			//Structure for a file window
{
	WINDOW *win;			//Window
	char name[256];			//File name
	char *buffer;			//File buffer
	int bufpos;			//Size of buffer
	char saved;			//Flag indicates the file is saved(1)/Not saved(0)
}fwin;

fwin *w[MAX_WINDOWS];				//File windows
int current=-1;					//Index of the window currently accessing
int wn=0;					//Number of windows opened

fwin* create_win(fwin*,char*);		//Initilizes a file window
int open_window(fwin*);			/* Opens a file window to edit
					 * returns value :
					 * 2 		window changed 
					 * 1 		minimized 
					 * 0 		closed 
					 * 3		New file
					 * 4		Open file
					 */
void delete_window(fwin*);		//Frees a created file window
void instructions();			//Prints key helps for the text editor in a window
int save(fwin*,char);			/* Saves the contents of current window as existing(0)/new(1) file
					 * returns 1 on success and 0 on failure */
int load(fwin*);			/* Loads a file in a new window to edit
					 * returns 1 on success and 0 on failure */
void show_messege(char*,char,int,...);	//Prints a messege in a small window
int crop(char*,int,int);
int line(fwin* fw);

int main()	
{
	char name[256];					//Buffer for file name
	int i,j;					//used for loops
	int state=1;					//holds return state for a current window colsed(0)/minimized(1)
	char c='Y',msg[300],flag=0;
	initscr();
	start_color();
	noecho();
	keypad(stdscr,true);
	init_pair(1,COLOR_BLACK,COLOR_WHITE);	
	init_pair(2,COLOR_WHITE,COLOR_YELLOW);
	init_pair(3,COLOR_WHITE,COLOR_BLACK);
	init_pair(4,COLOR_WHITE,COLOR_BLUE);
	init_pair(5,COLOR_YELLOW,COLOR_BLACK);
	init_pair(6,COLOR_GREEN,COLOR_BLACK);
	init_pair(7,COLOR_MAGENTA,COLOR_BLACK);
	init_pair(8,COLOR_CYAN,COLOR_BLUE);
	while(1)
	{
		erase();
		if(wn==MAX_WINDOWS) mvprintw(0,0,"| F1 Help | Ctrl+x Exit |");
		else mvprintw(0,0,"| F2 New File | F3 Open File | F1 Help | Ctrl+x Exit |");
		bkgd(COLOR_PAIR(1));
		mvchgat(0,0,COLS,A_NORMAL|A_UNDERLINE,1,NULL);
		refresh();
		if(wn<=COLS/15) j=15;
		else j=COLS/(wn+1);
		for(i=0;i<wn;i++)
			mvprintw(LINES-1,i*j,"%-10.10s%s",w[i]->name,(strlen(w[i]->name)>j?"...":""));
		mvchgat(LINES-1,current*j,j,A_BOLD,1,NULL);
		switch((state==2)?'\n':(state==3)?KEY_F(2):(state==4)?KEY_F(3):getch())
		{
			case KEY_F(1):		//F1	--	Help
				instructions();
				break;
			case KEY_F(2):		//F2	--	New File	
				if(wn<MAX_WINDOWS)
				{
					current++;
					sprintf(name,"NEWFILE_%.2d",wn+1);
					w[wn]=create_win(w[wn],name);
					state=open_window(w[wn++]);
				}
				else show_messege("Close at least one file to open another window",1,0);
				break;
			case KEY_F(3):		//F3	--	Open File	
				if(wn<MAX_WINDOWS)
				{
					w[wn]=create_win(w[wn],name);
					if(load(w[wn]))
					{
						current++;
						w[wn]->saved=1;
						state=open_window(w[wn++]);
					}
					else delete_window(w[wn]);
				}
				else show_messege("Close at least one file to open another window",1,0);
				break;
			case 538:		//Alt+left  --  Switch window
				if(wn>1 && current>0)current--;
				break;
			case 553:		//Alt+right  --  Switch window
				if(wn>1 && current<wn-1)current++;
				break;
			case '\n':		//F12  --  Open selected window
				if(wn>0) state=open_window(w[current]);
				break;
			case 24:		//Cntrl+X	--	Exit
				for(i=0;i<wn && flag==0;i++)
				{
					bkgd(COLOR_PAIR(1));
					refresh();
					show_messege("do you want to save %s\n\t\tyes(y)/no(n)",1,1,w[i]->name,&c);
					if((c='Y' || c=='y') && save(w[i],0))
					{
						delete_window(w[i]);
						memmove(w+i,w+i+1,(wn-i-1)*sizeof(fwin*));
						wn--;
					}
				}
				endwin();
				return 0;
		}
		if(state==0)
		{
			delete_window(w[current]);
			memmove(w+current,w+current+1,(wn-current-1)*sizeof(fwin*));
			wn--;
			if(wn==0) current=-1;
			else current--;
			state=1;
		}
	}
}

/* show_messege() prints a messege :
 * mode 1-delay		void show_messege(char* msg,char mode,int n,<n arg.s for msg...>,unsigned int delay);
 * mode 2-getch		void show_messege(char* msg,char mode,int n,<n arg.s for msg...>,char* c);
 * mode 3-scan		void show_messege(char* msg,char mode,int n,<n arg.s for msg...>,char *fmt,<args.s for fmt...>);
 */

void show_messege(char* msg,char mode,int n,...)	
{
	int i;
	va_list arg;
	va_start(arg,n);
	char l=strlen(msg)+4;				//Length of messege
	char *s;					//Used for mode 1,2
	WINDOW* win=newwin(4,60,20,(COLS-60)/2);
	wbkgd(win,COLOR_PAIR(2));
	wmove(win,1,2);
	vwprintw(win,msg,arg);
	for(i=0;i<n;i++) va_arg(arg,void);
	wrefresh(win);
	switch(mode)
	{
		case 0:
			napms(va_arg(arg,unsigned int));
			break;
		case 1:
			s=va_arg(arg,char*);
			*s=wgetch(win);
			break;
		case 2:
			s=va_arg(arg,char*);
			echo();
			wmove(win,2,5);
			wrefresh(win);
			vwscanw(win,s,arg);
			noecho();
			break;
	}
	va_end(arg);
	wclear(win);
	wrefresh(win);
	refresh();
	delwin(win);
}

fwin* create_win(fwin *fw,char*name)
{
	fw=(fwin*)malloc(sizeof(fwin));			//Allocating space for the structure
	fw->win=newwin(LINES-4,COLS-2,2,1);		//Creating window
	strcpy(fw->name,name);				//Copying the name
	fw->buffer=(char*)calloc(1,BUFFER_SIZE);	//Allocating space for the buffer
       	fw->bufpos=0;					//Setting buffer position to beginning
	fw->saved=1;					//Flag reset,indicates not saved
	return fw;
}

void delete_window(fwin *fw)
{
	free(fw->buffer);				//Freeing buffer
	delwin(fw->win);				//Deleting window
	free(fw);					//Freing structure
}

int crop(char* s,int m,int n)
{
	int i=0,k=0,l=0;
	for(;*s && i<m+n;i++)
	{
		for(;*s!='\n' && *s;s++)
			if(i<m) l++;
		if(*s=='\n')
		{
			if(i<m) l++;
			s++;
		}
	}
	return l;
}

int line(fwin* fw)			//returns current line number
{
	int i,n,j,cols,lines;
	getmaxyx(fw->win,lines,cols);
	for(i=0,n=0,j=0;fw->buffer[i] && i<fw->bufpos;i++,j++) 
		if(fw->buffer[i]=='\n' || j==cols)
		{
			n++;
			j=0;
		}
	return n;
}

int open_window(fwin *fw)
{
	WINDOW *head,*tail;				
	head=newwin(1,COLS-2,1,1);			//Head is header used to show file name
	tail=newwin(1,COLS-2,LINES-2,1);		//Tail is tailer used to show cursor position & mode
	int c;						//Used for reading character
	int i,j;					//Used for loops
	int x=0,y=1;					//'x'=current line,'y'=current column in window
	int lines,cols;					//'lines'=max lines,'cols'=max columns in window
	getmaxyx(fw->win,lines,cols);
	int bufsize;					//Number of characters in buffer
	char replace=0;					//Flag indicates Replace(1)/Insert(0) mode
	char *mode[2]={"insert ","replace"};		//String to be used by flag 'replace'
	int hstart=-1,hend=-1;				//highlight position start 'hstart' and endd 'hend'
	char copy_buffer[COPY_BUFFER_SIZE];		//Buffer for copy
	int n=0;					//Position of first line shown in window in buffer
	int offset=0;					//Position of first character shown in window in buffer
	char pattern[100],pattern2[100];		//Used for search and replace
	char case_sensitive=1;				//Searching case sensitive(1)/case insensitive(0)

	keypad(fw->win,true);
	wbkgd(fw->win,COLOR_PAIR(3));
	wbkgd(head,COLOR_PAIR(3));
	wbkgd(tail,COLOR_PAIR(3));
	while(1)
	{
		erase();
		if(wn==MAX_WINDOWS) mvprintw(0,0,"| F1 Help | F4 Save | F5 Save as | F6 Cut | F7 Copy | F8 Paste | Cntrl+X Close | F1 Help |");
		else mvprintw(0,0,"| F2 New File | F3 Open File | F4 Save | F5 Save as | F6 Cut | F7 Copy | F8 Paste | Cntrl+X Close | F1 Help |");
		mvchgat(0,0,COLS,A_NORMAL|A_UNDERLINE,1,NULL);
		if(wn<=COLS/15) j=15;
		else j=COLS/(wn+1);
		for(i=0;i<wn;i++)
			mvprintw(LINES-1,i*j,"%-10.10s%s",w[i]->name,(strlen(w[i]->name)>j?"...":""));
		mvchgat(LINES-1,current*j,j,A_BOLD,1,NULL);
		refresh();	
		werase(head);
		mvwprintw(head,0,(cols-strlen(fw->name))/2,"%s",fw->name);
		mvwchgat(head,0,(cols-strlen(fw->name))/2,strlen(fw->name),A_NORMAL|A_BOLD,5,NULL);
		wrefresh(head);
	
			//Synchronization of buffer position with cursor position
		werase(fw->win);
		bufsize=strlen(fw->buffer);
		offset=crop(fw->buffer,n,lines);
		mvwprintw(fw->win,0,0,fw->buffer+offset);
		wmove(fw->win,0,0);
		hstart=(hstart>hend)?hend:hstart;
		for(i=0,x=0,y=0;i<fw->bufpos-offset;i++)	
		{
			if(i>=hstart-offset && i<=hend-offset)
				if(fw->buffer[i]=='\t') wchgat(fw->win,8-x%8,A_STANDOUT,3,NULL);
				else wchgat(fw->win,1,A_STANDOUT,3,NULL);
			if(fw->buffer[offset+i]=='\n')
				wmove(fw->win,++y,x=0);
			else if(fw->buffer[offset+i]=='\t')
				if(8*(1+x/8)>=cols)wmove(fw->win,++y,x=0);
				else wmove(fw->win,y,x=8*(1+x/8));
			else
				if(x==cols-1)wmove(fw->win,++y,x=0);
				else wmove(fw->win,y,++x);
		}
		if(y>=lines-1) n++;
		if(y<=0) n--;

		werase(tail);
		mvwprintw(tail,0,5,"Mode : %7s\t\t\t\tLine : %d\tCharacter : %d",mode[replace],line(fw),x);
		mvwchgat(tail,0,5,20,A_NORMAL|A_BOLD,7,NULL);
		mvwchgat(tail,0,25,cols-25,A_NORMAL|A_BOLD,6,NULL);
		wrefresh(tail);

			//Reading character
		wrefresh(fw->win);
		c=getch();			
			//If c=printable or white space character
		if(isprint(c) || isspace(c))	
		{
			if(!replace || (replace && fw->buffer[fw->bufpos]=='\n'))
				memmove(fw->buffer+fw->bufpos+1,fw->buffer+fw->bufpos,bufsize-fw->bufpos);
			fw->buffer[fw->bufpos++]=c;
			hstart=hend=fw->bufpos;
			fw->saved=0;
		}
			//If c=control character
		else			
		{
			switch(c)
			
			{
				case 127:		//Backspace  --  Delete character backward
					if(fw->bufpos>0)
					{
						fw->bufpos--;
						hstart=hend=fw->bufpos;
						memmove(fw->buffer+fw->bufpos,fw->buffer+fw->bufpos+1,bufsize-fw->bufpos);
					}
					fw->saved=0;
					break;
				case 561:		//ctrl+up  --  Move and disselect up
				case KEY_UP:		//Up  --  Move up
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
				case 520:		//ctrl+down  --  Move and select down
				case KEY_DOWN:		//Down  --  Move down
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
				case 540:		//ctrl+left  --  Move and disselect left
				case KEY_LEFT:		//Left  --  Move left
					if(fw->bufpos>=0)
					{
						fw->bufpos--;
						if(c==KEY_LEFT) hstart=hend=fw->bufpos;
						else hend=fw->bufpos;
					}
					break;	
				case 555:		//ctrl+right  --  Move and select right
				case KEY_RIGHT:		//Right  --  Move right
					if(fw->bufpos<bufsize)
					{
						fw->bufpos++;
						if(c==KEY_RIGHT) hstart=hend=fw->bufpos;
						else hend=fw->bufpos;
					}
					break;
				case KEY_DC:		//Delete  --  Delete character or string at cursor
					memmove(fw->buffer+hstart,fw->buffer+hend+1,bufsize-hend+1);
					fw->bufpos=hend=hstart=hstart;
					fw->saved=0;
					break;
				case KEY_F(1):		//F1  --  Help
					instructions();
					break;
				case KEY_F(2):		//F2  --  New File
					return 3;
					break;
				case KEY_F(3):		//F3  --  Open File
					return 4;
					break;
				case KEY_F(4):		//F4  --  Save
					save(fw,0);
					break;
				case KEY_F(5):		//F5  --  Save as
					save(fw,1);
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
				case KEY_F(12):
					case_sensitive=!case_sensitive;
					break;
				case 538:		//Alt+left  --  next window
					if(wn>1 && current>0)current--;
					return 2;
				case 553:		//Alt+right  --  previous window
					if(wn>1 && current<wn-1)current++;
					return 2;
				case 530:		//cntl+home  --  Move and disselect till beginning of line
				case KEY_HOME:		//home  --  Go to beginning of line
					if(fw->buffer[fw->bufpos]=='\n') fw->bufpos--;
					while(fw->buffer[fw->bufpos]!='\n' && fw->bufpos>0) fw->bufpos--;
					if(fw->buffer[fw->bufpos]=='\n') fw->bufpos++;
					if(c==KEY_HOME) hstart=hend=fw->bufpos;
					else hend=fw->bufpos;
					break;
				case 525:		//cntl+end  --  Move and select till end of line
				case KEY_END:		//end  --  Goto end of line
					while(fw->buffer[fw->bufpos]!='\n' && fw->bufpos<bufsize) fw->bufpos++;
					if(c==KEY_END) hstart=hend=fw->bufpos;
					else hend=fw->bufpos;
					break;
				case 1:			//ctrl+A  --  Select All
					hstart=0;
					hend=fw->bufpos=bufsize-1;
					break;
				case 535:		//Ctrl+Insert  --  Change mode insert/replace
					replace=!replace;
					wmove(fw->win,lines-1,5);
					waddstr(fw->win,mode[replace]);
					break;
				case 27:		//Esc  -- Minimize window
					delwin(head);
					delwin(tail);
					return 1;
				case 24:		//Cntrl+X  --  Close window
					if(!fw->saved)
					{
						char ch;
						show_messege("do you want to save \n\t\tyes(y)/no(n)/cancel(c)",1,0,&ch);
						switch(toupper(ch))
						{
							case 'Y':
								if(save(fw,false))
								{
									delwin(head);
									delwin(tail);
									return 0;
								}
								break;
							case 'N':
								delwin(head);
								delwin(tail);
								return 0;
							default:
								break;
						}
					}
					else
					{
						delwin(head);
						delwin(tail);
						return 0;
					}
					break;
				case 20:		//ctrl+T  --  Find and replace again
				case 7:			//ctrl+G  --  Find again
				case 18:		//ctrl+R  --  Find and replace
				case 6:			//ctrl+F  --  Find
					{
						char *x;
						if(c==6||c==18)
							show_messege("Enter pattern to search (case %ssensitive) :\n\t\t",
									2,1,(case_sensitive)?"":"in","%[^\n]",pattern);
						if(case_sensitive) x=strstr(fw->buffer+fw->bufpos,pattern);
						else x=(char*)strcasestr(fw->buffer+fw->bufpos,pattern);
						if(x==NULL) x=strstr(fw->buffer,pattern);
						if(x!=NULL)
						{
							hstart=x-fw->buffer;
							hend=hstart+strlen(pattern)-1;
							fw->bufpos=hend+1;
						}
						else show_messege("Pattern not found",0,0,500);
						if((c==18||c==20) && x!=NULL)
						{
							if(c==18) show_messege("Enter pattern to replace :\n\t\t",
									2,0,"%[^\n]",pattern2);
							memmove(fw->buffer+hstart,fw->buffer+hend+1,bufsize-hend+1);
							fw->bufpos=hend=hstart=hstart;
							memmove(fw->buffer+fw->bufpos+strlen(pattern2),
									fw->buffer+fw->bufpos,bufsize-fw->bufpos);
							for(i=fw->bufpos;i<fw->bufpos+strlen(pattern2);i++)
								fw->buffer[i]=pattern2[i-fw->bufpos];
						}
						if(line(fw)<n || line(fw)>=n+lines) n=line(fw)-lines+1;
					}
					break;
			}
		}
		refresh();
	}
}

void instructions()
{
	refresh();
	WINDOW* win=newwin(20,70,5,20);
	wbkgd(win,COLOR_PAIR(4));
	mvwaddstr(win,0,31,"HELP");
	mvwchgat(win,0,31,4,A_BOLD,8,NULL);
	wmove(win,2,0);
	waddstr(win,"\tctrl + <arrow>\t\tSelect text\n");
	waddstr(win,"\tctrl + a\t\tSelect all\n");
	waddstr(win,"\tF6\t\t\tCut\n");
	waddstr(win,"\tF7\t\t\tCopy\n");
	waddstr(win,"\tF8\t\t\tPaste\n");
	waddstr(win,"\thome\t\t\tGoto beginning of line\n");
	waddstr(win,"\tend\t\t\tGoto end of line\n");
	waddstr(win,"\tctrl + insert\t\tChange mode (insert/replace)\n");
	waddstr(win,"\tctrl + f\t\tFind pattern\n");
	waddstr(win,"\tctrl + r\t\tFind and replace pattern\n");
	waddstr(win,"\tctrl + g\t\tFind pattern again\n");
	waddstr(win,"\tctrl + t\t\tFind and replace pattern again\n");
	waddstr(win,"\tF12\t\t\tToggle between search sensitive/insensitive mode\n");
	mvwaddstr(win,18,59,"Alpha v3.1");
	mvwaddstr(win,19,49,"Author : Rakesh Malik");
	wmove(win,0,0);
	wrefresh(win);
	getch();
	wclear(win);
	refresh();
	delwin(win);
}

int save(fwin *fw,char save_as)
{
	FILE* fp;				//File to be saved into
	int i;					//Used for loops
	int flag=0;				//holds return value
	char filename[256];			//holds file name
	if(save_as || !fw->saved) show_messege("Enter file name : ",2,0,"%s",filename);
	else strcpy(filename,fw->name);
	fp=fopen(filename,"w");
	if(fp && !ferror(fp))
	{
		for(i=0;fw->buffer[i];i++)
			putc(fw->buffer[i],fp);
		fw->saved=1;
		strcpy(fw->name,filename);
		show_messege("File %s saved successfully...",0,1,filename,500);
		fclose(fp);
		flag=1;
	}
	else show_messege("File write error",0,0,500);
	return flag;
}

int load(fwin* fw)
{
	FILE* fp;				//File to be loaded from
	int flag=0;				//holds return value
	char filename[256];			//holds file name
	char c;					//holds each character of file
	int i;					//Used for loop
	show_messege("Enter file name to be loaded : ",2,0,"%s",filename);
	fp=fopen(filename,"r");
	if(fp && !ferror(fp))
	{
		for(i=0;;i++)
		{
			if((c=getc(fp))==EOF) break;
			fw->buffer[i]=c;
		}
		strcpy(fw->name,filename);
		show_messege("File %s loaded successfully...",0,1,filename,500);
		fclose(fp);
		fw->saved=1;
		flag=1;
	}
	else show_messege("File read error",0,0,500);
	return flag;
}
