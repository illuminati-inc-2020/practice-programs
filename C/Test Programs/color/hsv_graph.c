#include <fcntl.h>
#include <X11/Xlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

Display *display;
Window win;
GC gc;
Colormap cm;
XColor col;

draw(int h,int s,int v,unsigned char r,unsigned char g,unsigned char b)
{
  char str[20];
  sprintf(str,"rgb:%2.2x/%2.2x/%2.2x",r,g,b);
  XAllocNamedColor(display,cm,str,&col,&col);
  XSetForeground(display,gc,col.pixel);
  XDrawArc(display,win,gc,256-s,256-s,s*2,s*2,h*64,64);
}

int main()
{
	display=XOpenDisplay(NULL);
	int screen_num = DefaultScreen(display);
	Window parent_window=RootWindow(display,screen_num);
	
	cm=DefaultColormap(display,screen_num);
	unsigned long border=WhitePixel(display,screen_num);
	unsigned long background=BlackPixel(display,screen_num);;
	win=XCreateSimpleWindow(display,parent_window,0,0,800,600,20,border,background);
	XMapWindow(display,win);
	XSync(display,0);
	
	XGCValues values;
	gc=XCreateGC(display,win,0,&values);
	XSetBackground(display,gc,BlackPixel(display,screen_num));
	XSetLineAttributes(display,gc,2,LineSolid,CapNotLast,JoinMiter);
	XSetFillStyle(display,gc,FillSolid);

	double r,g,b;
	double h=360,s=255,v=255;
	for(v=255;v>=0;v-=50)
	{
	  for(s=0;s<256;s++)
	  {
	    r=v;g=v-s*v/255;b=v-s*v/255;
	    for(h=0;h<360;h++)
	    {
	      if(h>=0 && h<60) g+=(v*s)/(255*60);
	      if(h>=60 && h<120) r-=(v*s)/(255*60);
	      if(h>=120 && h<180) b+=(v*s)/(255*60);
	      if(h>=180 && h<240) g-=(v*s)/(255*60);
	      if(h>=240 && h<300) r+=(v*s)/(255*60);
	      if(h>=300 && h<360) b-=(v*s)/(255*60);
	      draw((int)h,(int)s,(int)v,(unsigned char)r,(unsigned char)g,(unsigned char)b);
	      printf("rgb (%3.3d/%3.3d/%3.3d) - hsv (%3.3d/%3.3d/%3.3d)\n",(unsigned char)r,(unsigned char)g,(unsigned char)b,(int)h,(unsigned char)s,(unsigned char)v);
	      //getchar();	    
	    }
	  }
	}
	XCloseDisplay(display);
}




