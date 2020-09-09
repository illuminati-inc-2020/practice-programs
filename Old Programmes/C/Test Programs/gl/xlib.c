#include<X11/Xlib.h>
#include<stdlib.h>
#include<stdio.h>
#include"abc.xpm"

void ERROR(const char *msg)
{
  fprintf(stderr,"ERROR : %s\n",msg);
  exit(1);
}

main()
{
  /* Display */
  Display *dpy;
  if((dpy=XOpenDisplay(NULL))==NULL) ERROR("Display create error");  
  
  /* Screen */
  int screen=DefaultScreen(dpy);
  
  /* Visual */
  Visual *vis=DefaultVisual(dpy,screen);
  
  /* Cursor */
  
  //Cursor cur=XCreatePixmapCursor();
  
  /* Window */
  XSetWindowAttributes attribute;
  //attribute.background_pixmap;
  attribute.background_pixel=WhitePixel(dpy,screen);
  //attribute.border_pixmap;
  attribute.border_pixel=WhitePixel(dpy,screen);;
  //attribute.bit_gravity;
  attribute.win_gravity=NorthWestGravity;
  //attribute.backing_store;
  //attribute.backing_planes;
  //attribute.backing_pixel;
  //attribute.save_under;
  //attribute.event_mask;
  //attribute.do_not_propagate_mask;
  //attribute.override_redirect;
  //attribute.colormap;
  //attribute.cursor=cur;
  Window win=XCreateWindow(dpy,
			  RootWindow(dpy,screen),
			  0,0 				/*x,y*/,
			  400,400 			/*width,height*/,
			  2 				/*border width*/,
			  24 				/*depth*/,
			  InputOutput,
			  vis,
			  CWBackPixel|CWBorderPixel|CWWinGravity,
			  &attribute
	 );
  XMapWindow(dpy,win);
  XSync(dpy,0);
    
  /* GC */
  XGCValues values;
  GC gc=XCreateGC(dpy,win,0,&values);
  XSetBackground(dpy,gc,BlackPixel(dpy,screen));
  XSetForeground(dpy,gc,WhitePixel(dpy,screen));
  
  Pixmap curpm=XCreateBitmapFromData(dpy,win,"abc.xpm",50,50);
  XCopyArea(dpy,curpm,win,gc,0,0,50,50,0,0);
  XSync(dpy,0);
  
  /* Event */
  getchar();
  
  /* Exit */
  XUnmapWindow(dpy,win);
  XDestroyWindow(dpy,win);
  XCloseDisplay(dpy);
}
