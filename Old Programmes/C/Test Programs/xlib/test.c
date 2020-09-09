#include<X11/Xlib.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
	Display *disp=XOpenDisplay(":0.0");	
	if(disp==NULL)
	{
		fprintf(stderr,"error");
		return 1;
	}
	int screen_no;
	printf("all planes: %d\n",XAllPlanes());
	printf("screen no: %d\n",screen_no=XDefaultScreen(disp));
	printf("black pixel value : %d\n",BlackPixel(disp,screen_no));
	printf("white pixel value : %d\n",WhitePixel(disp,screen_no));
	printf("connection no: %d\n",XConnectionNumber(disp));
	Colormap col=XDefaultColormap(disp,screen_no);
	int i,depth_count,*depths;
	printf("depth : %d\n",XDefaultDepth(disp,screen_no));
	depths=calloc(30,sizeof(int));
	depths=XListDepths(disp,screen_no,&depth_count);
	printf("depth count : %d\n",depth_count);
	printf("depths : ");
	for(i=0;i<depth_count;i++)
		printf("%d,",depths[i]);
	printf("\n");
	GC gc=XDefaultGC(disp,screen_no);
	Window win=XDefaultRootWindow(disp);
	Screen *scr=XScreenOfDisplay(disp,screen_no);
	printf("entries in color map : %d\n",XDisplayCells(disp,screen_no));
	printf("available screens : %d\n",XScreenCount(disp));
	printf("max request size : %d\n",XMaxRequestSize(disp));
	//Visual visual=DefaultVisual(disp,screen_no);
	XPixmapFormatValues *xpfv;
	int count[100];
	xpfv=XListPixmapFormats(disp,count);
	if(xpfv)
		printf("pixmap values { \n\tdepth=%d\n\tbits per pixel = %d\n\tscanline pad = %d\n}",xpfv->depth,xpfv->bits_per_pixel,xpfv->scanline_pad);
}
