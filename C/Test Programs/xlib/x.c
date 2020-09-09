#include <X11/Xlib.h>

#include <stdio.h>
#include <stdlib.h>		
#include <unistd.h>	

Window
create_simple_window(Display* display, int width, int height, int x, int y)
{
  int screen_num = DefaultScreen(display);
  int win_border_width = 2;
  Window win;
  win = XCreateSimpleWindow(display, RootWindow(display, screen_num),
                            x, y, width, height, win_border_width,
                            BlackPixel(display, screen_num),
                            WhitePixel(display, screen_num));

  XMapWindow(display, win);
  XFlush(display);
  return win;
}

main(int argc, char* argv[])
{
  Display* display;		
  int screen_num;		
  Window win;	
  GC gc;			
  Colormap screen_colormap;    
  XColor red, brown, blue, yellow, green;
  display = XOpenDisplay(NULL);
  if (display == NULL) {
    fprintf(stderr, "cannot connect to X server\n");
    exit(1);
  }
  screen_num = DefaultScreen(display);
  win = create_simple_window(display, 100, 100, 0, 0);
  sleep(3);
}
