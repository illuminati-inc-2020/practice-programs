/*  ASSIGNMENT 3
 *  Author : Rakesh Malik
 *  Date : 25.09.2010 - 26.09.2010
 *  B.Sc. Computer Science 2nd Year
 *  Text Editor using Ncurses
 */

#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
#include<ctype.h>
#include<string.h>

typedef struct fwin      //Structure for a file window
{
  WINDOW *win;      //Window
  char name[256];      //File name
  char *buffer;      //File buffer
  int bufpos;      //Size of buffer
  char saved;      //Flag indicates the file is saved(1)/Not saved(0)
}fwin;

void show_messege(char*,char);    //Prints a messege in a small window
fwin* create_win(fwin*,char*);    //Initilizes a file window
int open_window(fwin*);      /* Opens a file window to edit
		           * returns 1 when minimized and 0 when closed */
void delete_window(fwin*);    //Frees a created file window
void instructions();      //Prints key helps for the text editor in a window
int save(fwin*,char);      /* Saves the contents of current window as existing(0)/new(1) file
           * return 1 saved successfully else 0 */
int load(fwin*);      /* Loads a file in a new window to edit
           * returns 1 if successfully loaded else 0 */

int main()  
{
  char name[256];          //Buffer for file name
  fwin *w;
  initscr();
  start_color();
  noecho();
  keypad(stdscr,true);
  init_pair(1,COLOR_BLACK,COLOR_WHITE);  
  while(1)
  {
    erase();
    mvprintw(0,0,"| F2 New | F3 Open | Ctrl+x Exit |");
    bkgd(COLOR_PAIR(1));
    refresh();
    switch(getch())
    {
      case KEY_F(2):    //F2  --  New File  
        w=create_win(w,"NEWFILE");
        open_window(w);
        break;
      case KEY_F(3):    //F3  --  Open File  
        w=create_win(w,name);
        if(load(w))
          open_window(w);
        else
        {
          delete_window(w);
          show_messege("File read error",1);
        }
        break;
      case 24:    //Cntrl+X  --  Exit
        endwin();
        return 0;
      default:
        break;
    }
  }
}

void show_messege(char* err,char stop)
{
  char l=strlen(err)+2;        //Length of messege
  init_pair(2,COLOR_WHITE,COLOR_RED);
  WINDOW* wine=newwin(1,l,20,(COLS-l)/2);
  wbkgd(wine,COLOR_PAIR(2));
  wrefresh(wine);
  mvwprintw(wine,0,1,"%s",err);
  wrefresh(wine);
  if(stop) wgetch(wine);
  wclear(wine);
  delwin(wine);
}

fwin* create_win(fwin *fw,char*name)
{
  fw=(fwin*)malloc(sizeof(fwin));      //Allocating space for the structure
  fw->win=newwin(LINES-4,COLS-4,2,2);    //Creating window
  strcpy(fw->name,name);        //Copying the name
  fw->buffer=(char*)calloc(1,(LINES-6)*(COLS-4));  //Allocating space for the buffer
  fw->bufpos=0;          //Setting buffer position to beginning
  fw->saved=0;          //Flag reset,indicates not saved
  return fw;
}

void delete_window(fwin *fw)
{
  free(fw->buffer);        //Freeing buffer
  delwin(fw->win);        //Deleting window
  free(fw);          //Freing structure
}

int open_window(fwin *fw)
{
  int c;            //Used for reading character
  int i,j;          //Used for loops
  int x=0,y=1;          //'x'=current line,'y'=current column in window
  int lines,cols;          //'lines'=max lines,'cols'=max columns in window
  int bufsize;          //Number of characters in buffer
  char replace=0;          //Flag indicates Replace(1)/Insert(0) mode
  char *mode[2]={"insert ","replace"};    //String to be used by flag 'replace'
  keypad(fw->win,true);
  getmaxyx(fw->win,lines,cols);
  init_pair(3,COLOR_WHITE,COLOR_BLACK);
  wbkgd(fw->win,COLOR_PAIR(3));
  mvwprintw(fw->win,0,0,"%s",fw->name);
  mvwprintw(fw->win,lines-1,5,"%7s(%d,%d)         ",mode[replace],x,y);
  while(1)
  {
    erase();
    mvprintw(0,0,"| F2 New | F3 Open | F5 Save | F6 Save as | ctrl+X Close file |");
    refresh();
    werase(fw->win);
    mvwprintw(fw->win,0,cols/2,"%s",fw->name);
    mvwprintw(fw->win,lines-1,5,"Mode : %7s\t\t\t\tLine : %d\tCharacter : %d",mode[replace],y,x);
    mvwprintw(fw->win,lines-1,100,"%c",fw->buffer[fw->bufpos]);
    mvwprintw(fw->win,1,0,fw->buffer);
    wmove(fw->win,1,0);
    wrefresh(fw->win);        
    for(i=0,x=0,y=1;i<fw->bufpos;i++)  //Synchronization of buffer position with cursor position
    {
      if(fw->buffer[i]=='\n')
        wmove(fw->win,++y,x=0);
      else if(fw->buffer[i]=='\t')
        if(8*(1+x/8)>=cols)wmove(fw->win,++y,x=0);
        else wmove(fw->win,y,x=8*(1+x/8));
      else
        if(x==cols)wmove(fw->win,++y,x=0);
        else wmove(fw->win,y,++x);
    }
    wrefresh(fw->win);
    bufsize=strlen(fw->buffer);
    c=getch();        //Reading character
    if(isprint(c) || isspace(c))    //If charecter is to be printed
    {
      if(!replace)
        memmove(fw->buffer+fw->bufpos+1,fw->buffer+fw->bufpos,bufsize-fw->bufpos);
      fw->buffer[fw->bufpos++]=c;
    }
    else          //If control character
    {
      switch(c)
      
      {
        case 127:    //Backspace
          fw->bufpos--;
          memmove(fw->buffer+fw->bufpos,fw->buffer+fw->bufpos+1,bufsize-fw->bufpos);
          break;
        case KEY_UP:    //Up
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
          break;
        case KEY_DOWN:    //Down
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
              for(j=0;j<i-1 && fw->buffer[fw->bufpos]!='\n' && fw->bufpos<bufsize;j++)
              fw->bufpos++;          
          }
          break;
        case KEY_RIGHT:    //Right
          if(fw->bufpos<bufsize) fw->bufpos++;
          break;
        case KEY_LEFT:    //Left
          if(fw->bufpos>=0) fw->bufpos--;
          break;  
        case KEY_DC:    //Delete
          memmove(fw->buffer+fw->bufpos,fw->buffer+fw->bufpos+1,bufsize-fw->bufpos);
          break;
        case KEY_F(5):    //F5
          if(!save(fw,false)) show_messege("File write error",1);
          break;
        case KEY_F(6):    //F6
          if(!save(fw,true)) show_messege("File write error",1);
          break;
        case 535:    //Ctrl+Insert  --  Change mode insert/replace
          replace=!replace;
          wmove(fw->win,lines-1,5);
          waddstr(fw->win,mode[replace]);
          break;
        case 24:    //Cntrl+X  --  Close window
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
    mvwprintw(wins,0,5,"File %s saved successfully...",fw->name);
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
    strcpy(fw->name,filename);
    mvwprintw(winl,0,5,"File %s loaded successfully...",fw->name);
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
