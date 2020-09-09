#include<stdio.h>
#include<curses.h>

main()
{
	MEVENT *X;
	initscr();
	keypad(stdscr,true);
	while(1)
	{
		printw("\t%d\n",getch());
		refresh();
	}
	endwin();
}
