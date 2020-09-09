#include <fcntl.h>
#include <X11/Xlib.h>
#include <X11/keysymdef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "as2.c"

int main()
{
	Display *display=XOpenDisplay(NULL);
	int screen_num = DefaultScreen(display);
	Window win,parent_window=RootWindow(display,screen_num);
	
	Colormap cm=DefaultColormap(display,screen_num);
	XColor red;
	XAllocNamedColor(display,cm,"red",&red,&red);
	unsigned long border=WhitePixel(display,screen_num);
	unsigned long background=BlackPixel(display,screen_num);;
	win=XCreateSimpleWindow(display,parent_window,0,0,500,500,20,border,background);
	XMapWindow(display,win);
	XSync(display,0);
	
	XGCValues values;
	GC gc=XCreateGC(display,win,0,&values);
	XSetForeground(display,gc,red.pixel);
	XSetBackground(display,gc,BlackPixel(display,screen_num));
	XSetLineAttributes(display,gc,2,LineSolid,CapNotLast,JoinMiter);
	XSetFillStyle(display,gc,FillSolid);
	
	XSelectInput(display,win,ExposureMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask | KeyReleaseMask |
		       	Button1MotionMask | Button2MotionMask | StructureNotifyMask);
	XEvent an_event;
	char c;
	KeySym keysym;
	while(1)
	{
		XNextEvent(display,&an_event);
		switch(an_event.type)
		{ 
			case Expose:
				printf("\nExposed");
				break;
			case KeyPress:
				XLookupString(&an_event.xkey,&c,1,&keysym,NULL);
				Printf("\nKey %d pressed at (%d,%d)\nInput = %c",
					an_event.xkey.keycode, an_event.xkey.x, an_event.xkey.y,c);
				break;
			case KeyRelease:
				Printf("\nKey %d released at (%d,%d)",
					an_event.xkey.keycode, an_event.xkey.x, an_event.xkey.y);
				break;
			case ButtonPress:
				Printf("\nmouse button %d pressed at (%d,%d)",
						an_event.xbutton.button, an_event.xbutton.x, an_event.xbutton.y);
				break;
			case ButtonRelease:
				Printf("\nmouse button %d released at (%d,%d)",
						an_event.xbutton.button, an_event.xbutton.x, an_event.xbutton.y);
				break;
		}
		XSync(display,0);
	}

	XCloseDisplay(display);
}
