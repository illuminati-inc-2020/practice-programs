#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <X11/Xlib.h>
#include "BMP.h"

/* Variable Declarations and definitions */
#define WIDTH 700
#define HEIGHT 700
Display *display;											/* Display */
int screen;												/* Screen Number */
GLint att[]={GLX_RGBA,GLX_DEPTH_SIZE,24,GLX_DOUBLEBUFFER,None};						/* Visual Attributes */
Window parent_window;											/* Parent Window */
Window win;												/* Window */
Colormap cm;												/* Colormap */
GLXContext glc;												/* Context */
XSetWindowAttributes swa;										/* Set Window Attributes */
XWindowAttributes gwa;											/* Get Window Attributes */
XEvent event;												/* Event */
GLuint texture;

/* Funtion Prototypes */
void load_data(char*);
void draw(int X,int Y);

/* Function definitions */
main(int argc,char *argv[])
{  
  system("clear");
  display=XOpenDisplay(NULL);										/* Opening Display */
  
  screen=DefaultScreen(display);									/* Getting Default Screen */
  
  XVisualInfo *vis = glXChooseVisual(display, 0, att);							/* Choosing Visual */
  
  parent_window=RootWindow(display,screen);								/* Getting Parent Window */
  swa.colormap=cm=XCreateColormap(display,parent_window,vis->visual,AllocNone);				/* Colormap for Window */
  swa.event_mask=ExposureMask | ButtonPressMask | KeyPressMask;						/* Event Mask of Window */
													/* Creating Window */
  win=XCreateWindow(display,				/* display */
		    parent_window,			/* parent window */
		    100,0,				/* top-left x,y */
		    WIDTH,HEIGHT,			/* width,height */
		    20,					/* border width */
		    vis->depth,				/* depth */
		    InputOutput,			/* class */
		    vis->visual,			/* visual */
		    CWColormap | CWEventMask,&swa	/* window attributes */
		  );  
  XMapWindow(display,win);										/* Mappong the Window */
  XStoreName(display,win,"Vertex Detecter");									/* Window Name */
  XSync(display,0);											/* Flushing Output Buffer */
  
  glc = glXCreateContext(display,vis,NULL,GL_TRUE);							/* Creating Context */
  glXMakeCurrent(display,win,glc);									/* Making the Created Window Context */

  if(argc<2)
  {
    perror("Argument Missing");
    exit(0);
  }
  load_data(argv[1]);												/* Loading data */
  glEnable(GL_DEPTH_TEST);		
  while(1)
  {
    XNextEvent(display,&event);	/* Getting an Event */
    switch(event.type)
    {
      case Expose:      
	XGetWindowAttributes(display,win,&gwa);
	glViewport(0, 0, gwa.width, gwa.height);
	draw(WIDTH/2,HEIGHT/2); 
	break;
      case ButtonPress:
	//printf("(%f,%f)\n",2*(GLdouble)event.xbutton.x/(GLdouble)gwa.width-1,1-2*(GLdouble)event.xbutton.y/(GLdouble)gwa.height);
	printf("vertex(x,y,size,%3.3f,%3.3f, 0.00);\n",(GLdouble)event.xbutton.x/(GLdouble)gwa.width,(GLdouble)event.xbutton.y/(GLdouble)gwa.height);
	break;
      case KeyPress:
	glXMakeCurrent(display, None, NULL);								/* Release Current Context */
	glXDestroyContext(display, glc);								/* Destroy Context */
	XDestroyWindow(display, win);									/* Destroying Window */
	XCloseDisplay(display);										/* Closing display */
	return;
    }   
    glXSwapBuffers(display, win);
    glFlush();
  }
}

void load_data(char *fname)
{
  BMP image;  
  load_BMP(&image,fname);
  print_BMP_info(image);
  glGenTextures(1,&texture);
  glBindTexture(GL_TEXTURE_2D,texture);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);  
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,image.width,image.height,0,GL_RGB,GL_UNSIGNED_BYTE,image.data);
  free_BMP(&image);
}

void draw(int X,int Y)
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  
  /* Drawing */
  glBindTexture(GL_TEXTURE_2D,texture);
  glEnable(GL_TEXTURE_2D);    
  glBegin(GL_POLYGON);
    glTexCoord2f(1,0); glVertex3d(1,1,0);
    glTexCoord2f(0,0); glVertex3d(-1,1,0);
    glTexCoord2f(0,1); glVertex3d(-1,-1,0);
    glTexCoord2f(1,1); glVertex3d(1,-1,0);    
  glEnd();
} 
