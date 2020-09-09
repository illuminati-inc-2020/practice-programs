#include <fcntl.h>
#include <X11/Xlib.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define none 0
#define RLE8 1
#define RLE4 2

struct rgb_24bit
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char transparent : 1;
};
struct BMP_54byte_header
{
	unsigned short signature;		// 0x4d42
	unsigned long size;
	unsigned short reserved1;		// 0
	unsigned short reserved2;		// 0	XCopyArea(display,pm,win,gc,0,0,image->width,image->height,0,0);
	unsigned long offset;
	unsigned long bitmap_info_header_size;	// 40
	unsigned long width;
	unsigned long height;
	unsigned short planes;			// 1
	unsigned short bits_per_pixel;		// 1,4,9,24
	unsigned long compression_type;		//0=none,1=RLE8,2=RLE4
	unsigned long image_data_size;
	unsigned long horizontal_resolution_per_meter;
	unsigned long vertical_resolution_per_meter;
	unsigned long number_of_colors;
	unsigned long number_of_important_colors;
	struct rgb_24bit **data;
};

int main(int argc,char *argv[])
{
	int i,j;
	if(argc<2) {perror("argument missing");return;}
	Display *display=XOpenDisplay(NULL);
	int screen_num = DefaultScreen(display);
	Window win,parent_window=RootWindow(display,screen_num);
	unsigned long border=WhitePixel(display,screen_num);
	unsigned long background=BlackPixel(display,screen_num);
	win=XCreateSimpleWindow(display,parent_window,0,0,1000,800,20,border,background);
	XMapWindow(display,win);
	XSync(display,0);
	
	XGCValues values;
	GC gc=XCreateGC(display,win,0,&values);
	XSetBackground(display,gc,BlackPixel(display,screen_num));
	XSetForeground(display,gc,WhitePixel(display,screen_num));
	XSetLineAttributes(display,gc,2,LineSolid,CapNotLast,JoinMiter);
	XSetFillStyle(display,gc,FillSolid);
	
	FILE *fp=fopen(argv[1],"r");
	
	struct BMP_54byte_header *image=(struct BMP_54byte_header*)calloc(sizeof(struct BMP_54byte_header),1);
	fread(&image->signature,			sizeof(unsigned short),	1,fp);
	fread(&image->size,				sizeof(unsigned long),	1,fp);
	fread(&image->reserved1,			sizeof(unsigned short),	1,fp);
	fread(&image->reserved2,			sizeof(unsigned short),	1,fp);
	fread(&image->offset,				sizeof(unsigned long),	1,fp);
	fread(&image->bitmap_info_header_size,		sizeof(unsigned long),	1,fp);
	fread(&image->width,				sizeof(unsigned long),	1,fp);
	fread(&image->height,				sizeof(unsigned long),	1,fp);
	fread(&image->planes,				sizeof(unsigned short),	1,fp);
	fread(&image->bits_per_pixel,			sizeof(unsigned short),	1,fp);
	fread(&image->compression_type,			sizeof(unsigned long),	1,fp);
	fread(&image->image_data_size,			sizeof(unsigned long),	1,fp);
	fread(&image->horizontal_resolution_per_meter,	sizeof(unsigned long),	1,fp);
	fread(&image->vertical_resolution_per_meter,	sizeof(unsigned long),	1,fp);
	fread(&image->number_of_colors,			sizeof(unsigned long),	1,fp);
	fread(&image->number_of_important_colors,	sizeof(unsigned long),	1,fp);
	
	image->data=(struct rgb_24bit**)calloc(sizeof(struct rgb_24bit*),image->height);
	for(i=0;i<image->height;i++)
		image->data[i]=(struct rgb_24bit*)calloc(sizeof(struct rgb_24bit),image->width);
		
	printf("BITMAP HEADER FILE :\n");
	printf("signature : %x\n",image->signature);
	printf("size : %lu\n",image->size);
	printf("reserved : %hu\n",image->reserved1);
	printf("reserved : %hu\n",image->reserved2);
	printf("offset : %lu\n",image->offset);
	printf("BITMAP HEADER INFO :\n");
	printf("size : %lu\n",image->bitmap_info_header_size);
	printf("resolution in pixel : %lux%lu\n",image->width,image->height);
	printf("plane : %hu\n",image->planes);
	printf("Bits per pixel : %hu\n",image->bits_per_pixel);
	printf("Compression type : %hu\n",image->compression_type);
	printf("image data size : %lu\n",image->image_data_size);
	printf("resolution in meter : %lux%lu\n",image->horizontal_resolution_per_meter,image->vertical_resolution_per_meter);
	printf("number of colors : %lu\n",image->number_of_colors);
	printf("number of important colors : %lu\n",image->number_of_important_colors);
	
	char junk;
	for(i=0;i<image->height;i++)
	{
		for(j=0;j<image->width;j++)
		{
			fread(&image->data[i][j].blue,sizeof(unsigned char),1,fp);
			fread(&image->data[i][j].green,sizeof(unsigned char),1,fp);
			fread(&image->data[i][j].red,sizeof(unsigned char),1,fp);
			image->data[i][j].transparent=1;
		}
		fread(&junk,sizeof(char),4-(image->width*3)%4,fp);
	}
	
	Colormap cm=DefaultColormap(display,DefaultScreen(display));
	XColor color;
	char s[14];
	Pixmap pm=XCreatePixmap(display,win,image->width,image->height,DefaultDepth(display,screen_num));
	for(i=0;i<image->height;i++)
		for(j=0;j<image->width;j++)
		{
			sprintf(s,"rgb:%2.2x/%2.2x/%2.2x",image->data[i][j].red,image->data[i][j].green,image->data[i][j].blue);
			XAllocNamedColor(display,cm,s,&color,&color);
			XSetForeground(display,gc,color.pixel);			
			XDrawPoint(display,pm,gc,j,image->height-i);
		}	
	XCopyArea(display,pm,win,gc,0,0,image->width,image->height,0,0);	
	XSync(display,0);
	getchar();
	fclose(fp);
	XCloseDisplay(display);
}
