#include <fcntl.h>
#include <X11/Xlib.h>
#include <stdlib.h>
#include <GL/gl.h>

int main()
{
	Display *display=XOpenDisplay(NULL);
	int screen_num = DefaultScreen(display);
	Window win,parent_window=RootWindow(display,screen_num);
	unsigned long border=WhitePixel(display,screen_num);
	unsigned long background=BlackPixel(display,screen_num);
	win=XCreateSimpleWindow(display,parent_window,0,0,1500,1000,20,border,background);
	XMapWindow(display,win);
	XSync(display,0);
	
	XGCValues values;
	GC gc=XCreateGC(display,win,0,&values);
	XSetBackground(display,gc,BlackPixel(display,screen_num));
	XSetForeground(display,gc,WhitePixel(display,screen_num));
	XSetLineAttributes(display,gc,2,LineSolid,CapNotLast,JoinMiter);
	XSetFillStyle(display,gc,FillSolid);
	glBegin;
	glVertex2d(5,5);
	glEnd;
	sleep(1);	

	XCloseDisplay(display);
}
