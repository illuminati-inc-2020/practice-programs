#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>
#include<X11/Xlib.h>

/* Structure Definitions */
typedef struct object_struct										/* Structure for an Object */
{
  int X;
  int Y;
  GLdouble x;
  GLdouble y;
} object;

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
object plane={WIDTH/2,HEIGHT,0,0};

/* Funtion Prototypes */
void draw_plane(int X,int Y);

main()
{
  display=XOpenDisplay(NULL);										/* Opening Display */
  
  screen=DefaultScreen(display);									/* Getting Default Screen */
  
  XVisualInfo *vis = glXChooseVisual(display, 0, att);							/* Choosing Visual */
  
  parent_window=RootWindow(display,screen);								/* Getting Parent Window */
  swa.colormap=cm=XCreateColormap(display,parent_window,vis->visual,AllocNone);				/* Colormap for Window */
  swa.event_mask=ExposureMask | ButtonPressMask | KeyPressMask | PointerMotionMask;			/* Event Mask of Window */
													/* Creating Window */
  win=XCreateWindow(display,				/* display */
		    parent_window,			/* parent window */
		    100,0,				/* top-left x,y */
		    WIDTH,HEIGHT,				/* width,height */
		    20,					/* border width */
		    vis->depth,				/* depth */
		    InputOutput,			/* class */
		    vis->visual,			/* visual */
		    CWColormap | CWEventMask,&swa	/* window attributes */
		  );  
  XMapWindow(display,win);										/* Mappong the Window */
  XStoreName(display,win,"Fighter");									/* Window Name */
  XSync(display,0);											/* Flushing Output Buffer */
  
  glc = glXCreateContext(display,vis,NULL,GL_TRUE);							/* Creating Context */
  glXMakeCurrent(display,win,glc);									/* Making the Created Window Context */
    
  glEnable(GL_DEPTH_TEST);
  while(1)
  {
    XCheckMaskEvent(display,ExposureMask | KeyPressMask | ButtonPressMask | PointerMotionMask,&event);
													/* Gettingh an Event */
    switch(event.type)
    {
      case Expose:      
	XGetWindowAttributes(display,win,&gwa);
	glViewport(0, 0, gwa.width, gwa.height);
	draw_plane(plane.X,plane.Y); 
	glXSwapBuffers(display, win);
	break;
      case MotionNotify:
	draw_plane(event.xbutton.x,event.xbutton.y);
	glXSwapBuffers(display, win);
	break;
      case KeyPress:
	glXMakeCurrent(display, None, NULL);								/* Release Current Context */
	glXDestroyContext(display, glc);								/* Destroy Context */
	XDestroyWindow(display, win);									/* Destroying Window */
	XCloseDisplay(display);										/* Closing display */
	return;
    }
  }
}

void draw_plane(int X,int Y)
{
  const int speed=5;											/* Plane speed */
  
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glTranslated(0.0,0.0,0.0);
  if(X>plane.X+speed) glRotated(15, 0.0, 1.0, 0.0);  
  else if(X<plane.X-speed) glRotated(15, 0.0,-1.0, 0.0);
  if(Y>plane.Y+speed) glRotated(15, 1.0, 0.0, 0.0);
  else if(Y<plane.Y-speed) glRotated(15,-1.0,-0.0, 0.0);
  glShadeModel(GL_SMOOTH);
 
  /* Updating plane position */
  if(X<plane.X+speed && X>plane.X-speed) plane.X=plane.X;
  else if(X>plane.X) plane.X=plane.X+speed;
  else if(X<plane.X) plane.X=plane.X-speed;
  if(Y<plane.Y+speed && Y>plane.Y-speed) plane.Y=plane.Y;
  else if(Y>plane.Y) plane.Y=plane.Y+5;
  else if(Y<plane.Y) plane.Y=plane.Y-5;
  GLdouble x=plane.x=2*(GLdouble)plane.X/(GLdouble)gwa.width-1;
  GLdouble y=plane.y=1-2*(GLdouble)plane.Y/(GLdouble)gwa.height; 
  
  /* Getting Texture */
  GLuint texture;
  glGenTextures(1,&texture);
  glBindTexture(GL_TEXTURE_2D,texture);
  glTexImage2D(GL_TEXTURE_2D,0,0,);
  
  /* Drawing Plane */
  glBegin(GL_TRIANGLES);
  glTexCoord2f(0.00,0.10); glVertex3d(x+0.00,y+0.10,0.01);
  glTexCoord2f(0.10,0.05); glVertex3d(x-0.10,y-0.05,0.01);
  glTexCoord2f(0.10,0.05); glVertex3d(x+0.10,y-0.05,0.01);
  glEnd();
  /*glBegin(GL_POLYGON);
  glColor3f(0.0,0.0,1.0); glVertex3d(x+0.00,y+0.15,0.01);
  glColor3f(0.0,0.0,1.0); glVertex3d(x-0.05,y-0.10,0.00);
  glColor3f(0.0,0.0,1.0); glVertex3d(x+0.00,y-0.08,0.00);
  glColor3f(0.0,0.0,1.0); glVertex3d(x+0.05,y-0.10,0.00);
  glEnd(); 
  glBegin(GL_TRIANGLES);
  glColor3f(1.0, 0.0,0.0); glVertex3d(x+0.00,y+0.10,0.01);
  glColor3f(1.0, 0.0,0.0); glVertex3d(x-0.10,y-0.05,0.01);
  glColor3f(1.0, 0.0,0.0); glVertex3d(x+0.10,y-0.05,0.01);
  glEnd();*/
} 
