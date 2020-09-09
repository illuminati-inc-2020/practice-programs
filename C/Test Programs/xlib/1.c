#include <fcntl.h>
#include <X11/Xlib.h>
#include <stdlib.h>
#include <math.h>
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
	glEnd;
	float i,j;
	for(i=0;i<100;i+=.01)
	{
		//XDrawLine(display,win,gc,100,i,i,100);
		//XDrawArc(display,win,gc,i,i,i,i,64,i*64);
		XDrawPoint(display,win,gc,i*30,500-(sin(i))*100);
		XDrawPoint(display,win,gc,i*30,500-(1/sin(i))*100);
		XDrawPoint(display,win,gc,i*30,500-(1/tan(i))*100);
		XDrawPoint(display,win,gc,i*30,500-(1/cos(i))*100);
		XDrawPoint(display,win,gc,i*30,500-(tan(i))*100);
		XDrawPoint(display,win,gc,i*30,500-(cos(i))*100);
		XSync(display,0);
		usleep(1000);
	}
	sleep(1);	

	XCloseDisplay(display);
}
