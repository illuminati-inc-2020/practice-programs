#include <math.h>

typedef struct RGBf {
	double r,g,b,a;
} RGBf;

typedef struct HSVf {
	double h,s,v;
} HSVf;

typedef struct RGBi {
	unsigned char r,g,b,a;
} RGBi;

typedef struct HSVi {
	unsigned short h;
	unsigned char s,v;
} HSVi;

int max3i(int x,int y,int z);
int min3i(int x,int y,int z);

void HSVtoRGBi(HSVi hsv,RGBi *rgb)
{
	unsigned char h,s,v;
	h=hsv.h,s=hsv.s,v=hsv.v;
	if(h>=0 && h<60)	{	rgb->r=v;
							rgb->g=v-s*v/255+(h*v*s)/(255*60);
							rgb->b=v-s*v/255;
						}	
	if(h>=60 && h<120)	{ 	rgb->r=v-((h-60)*v*s)/(255*60);
							rgb->g=v;
							rgb->b=v-s*v/255;
						}
	if(h>=120 && h<180) {	rgb->r=v-s*v/255;
							rgb->g=v;
							rgb->b=v-s*v/255+((h-120)*v*s)/(255*60);
						}
	if(h>=180 && h<240) {	rgb->r=v-s*v/255;
							rgb->g=v-((h-180)*v*s)/(255*60);
							rgb->b=v;
						}
	if(h>=240 && h<300) {	rgb->r=v-s*v/255+((h-240)*v*s)/(255*60);
							rgb->g=v-s*v/255;
							rgb->b=v;
						}
	if(h>=300 && h<360) {	rgb->r=v;
							rgb->g=v-s*v/255;
							rgb->b=v-((h-300)*v*s)/(255*60);
						}
	rgb->a=255;
}

void RGBtoHSVi(RGBi rgb,HSVi *hsv)
{
	unsigned char r,g,b,max,min;
	r=rgb.r,g=rgb.g,b=rgb.b;
	max=max3i(r,g,b);
	min=min3i(r,g,b);
	hsv->v=max;
	hsv->s=(max==0)?min:(unsigned char)(255-(double)(min*255)/(double)max);
	if(max==min) hsv->h=0;
	else if (r==max && b==min)	hsv->h=0+	(unsigned)(60*((double)(g-min)/(double)(max-min)));
	else if (g==max && b==min)	hsv->h=120-	(unsigned)(60*((double)(r-min)/(double)(max-min)));
	else if (g==max && r==min)	hsv->h=120+	(unsigned)(60*((double)(b-min)/(double)(max-min)));
	else if (b==max && r==min)	hsv->h=240-	(unsigned)(60*((double)(g-min)/(double)(max-min)));
	else if (b==max && g==min)	hsv->h=240+	(unsigned)(60*((double)(r-min)/(double)(max-min)));
	else if (r==max && g==min)	hsv->h=360-	(unsigned)(60*((double)(b-min)/(double)(max-min)));
}

int max3i(int x,int y,int z)
{
	return (x>=y)	
			?	(y>=z)
				?	x		// x>y>z
				:	(z>=x)
					?	z	// z>x>y
					:	x	// x>z>y
			:	(x>=z)
				?	y		// y>x>z
				:	(z>=y)
					?	z	// z>y>x
					:	y	// y>z>x
	;
}

int min3i(int x,int y,int z)
{
	return (x<=y)	
			?	(y<=z)
				?	x		// x<y<z
				:	(z<=x)
					?	z	// z<x<y
					:	x	// x<z<y
			:	(x<=z)
				?	y		// y<x<z
				:	(z<=y)
					?	z	// z<y<x
					:	y	// y<z<x
	;
}