#include<GL/gl.h>
#include<GL/glx.h>
#include<X11/Xlib.h>
#include<stdlib.h>
#include<stdio.h>

main()
{
  Display *dpy=XOpenDisplay(NULL);
  int screen=DefaultScreen(dpy);
  int errorcode[10],eventcode[10];
  printf("%d\n",glXQueryExtension(dpy,errorcode,eventcode));
  printf("%s\n",glXQueryExtensionsString(dpy,screen));
  int nelements;
  GLXFBConfig *get=glXGetFBConfigs(dpy,screen,&nelements);
  printf("%d\n",nelements);
  int attriblist[1]={GLX_WINDOW_BIT};
  GLXFBConfig *choose=glXChooseFBConfig(dpy,screen,attriblist,&nelements);
  printf("%d\n",nelements);
  Window parent=RootWindow(dpy,screen);
  GLXWindow win=glXCreateWindow(dpy,choose[0],parent,attriblist);
  //GLXWindow win=glXCreateWindow(dpy,,win,);
  
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0,1.0,1.0);
  glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
  glBegin(GL_POLYGON);
  glVertex2f(-0.5,-0.5);
  glVertex2f(-0.5,0.5);
  glVertex2f(0.5,0.5);
  glVertex2f(0.5,-0.5);
  glEnd();
  glFlush();
  
  //glXDestroyWindow(dpy,win);
  
}
