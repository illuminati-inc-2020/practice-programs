#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include "BMP.h"
#include "color.h"
#include "glstdio.h"

#define WIDTH 512
#define HEIGHT 512												/* Window height & width */
int win;														/* Window id */
void display(void);												/* GLUT display function */
void reshape(int width, int height);							/* GLUT reshape function */
void mouse(int button, int state,int x, int y);					/* GLUT mouse function */
void keyboard(unsigned char key,int x, int y);					/* GLUT keyboard function */
void special_keyboard(int key,int x, int y);					/* GLUT special keyboard function */
void motion(int x, int y);										/* GLUT motion function */
void passivemotion(int x, int y);								/* GLUT passive motion function */

double depth(int i,int j);

#define PART 64
GLuint tex;
RGBi **bitmap;
int mousex,mousey;
HSVi hsv;
double anglex=0,angley=0,anglez=0;

RGBi** GLLoadTexture(GLuint *texture,const char *name);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize (WIDTH,HEIGHT);
	glutInitWindowPosition (0,0);
	win=glutCreateWindow ("3d");

	bitmap=GLLoadTexture(&tex,"bookr.bmp");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special_keyboard);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(passivemotion);
	glutMainLoop();
	return 0;
}

void display(void)
{
	int i,j;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1.0f);
	glClearColor(0.0,0.0,0.0,0.0);

	gluPerspective(45.0f,(GLfloat)WIDTH/(GLfloat)HEIGHT,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glRotatef(anglex,1,0,0);
	glRotatef(angley,0,1,0);
	glRotatef(anglez,0,0,1);
	glOrtho(-0.25,1.25,-0.25,1.25,-3,3);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tex);
	glBegin(GL_QUADS);
	for(i=0;i<PART-1;i++)
	{
		for(j=0;j<PART-1;j++)
		{
			if( (bitmap[j*512/PART][i*512/PART].r==0 && bitmap[j*512/PART][i*512/PART].g==0 && bitmap[j*512/PART][i*512/PART].b==0 ) ||
				(bitmap[j*512/PART][i*512/PART+512/PART].r==0 && bitmap[j*512/PART][i*512/PART+512/PART].g==0 && bitmap[j*512/PART][i*512/PART+512/PART].b==0 ) ||
				(bitmap[j*512/PART+512/PART][i*512/PART+512/PART].r==0 && bitmap[j*512/PART+512/PART][i*512/PART+512/PART].g==0 && bitmap[j*512/PART+512/PART][i*512/PART+512/PART].b==0 ) ||
				(bitmap[j*512/PART+512/PART][i*512/PART].r==0 && bitmap[j*512/PART+512/PART][i*512/PART].g==0 && bitmap[j*512/PART+512/PART][i*512/PART].b==0 ))
				continue;
			glTexCoord2f((double)i/(double)(PART-1),(double)j/(double)(PART-1));
			glVertex3d((double)i/(double)(PART-1),1-(double)j/(double)(PART-1),depth(i*512/PART,j*512/PART));

			glTexCoord2f((double)(i+1)/(double)(PART-1),(double)j/(double)(PART-1));
			glVertex3d((double)(i+1)/(double)(PART-1),1-(double)j/(double)(PART-1),depth(i*512/PART+512/PART,j*512/PART));

			glTexCoord2f((double)(i+1)/(double)(PART-1),(double)(j+1)/(double)(PART-1));
			glVertex3d((double)(i+1)/(double)(PART-1),1-(double)(j+1)/(double)(PART-1),depth(i*512/PART+512/PART,j*512/PART+512/PART));
			
			glTexCoord2f((double)i/(double)(PART-1),(double)(j+1)/(double)(PART-1));
			glVertex3d((double)i/(double)(PART-1),1-(double)(j+1)/(double)(PART-1),depth(i*512/PART,j*512/PART+512/PART));
			
		}
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);

	RGBtoHSVi(bitmap[mousey][mousex],&hsv);
	GLPrintf(-.9,.9,"(%3.3d:%3.3d:%3.3d)::(%3.3d:%3.3d:%3.3d)",bitmap[mousey][mousex].r,bitmap[mousey][mousex].g,bitmap[mousey][mousex].b,hsv.h,hsv.s,hsv.v);

	glutPostRedisplay();
	glutSwapBuffers();
}

double depth(int i,int j)
{
	double z=0;
	RGBtoHSVi(bitmap[j][i],&hsv);
	z+=(((double)(hsv.v)/(double)256)+((double)(hsv.v)/(double)256))/2;
	return z;
}

void reshape(int width, int height)
{
	glViewport(0,0,width,height);
}

void mouse(int button, int state,int x, int y)
{
	switch(button)
	{
	}
}

void keyboard(unsigned char key,int x, int y)
{
	switch(key)
	{
		case 27:
			exit(0);
	}
}

void special_keyboard(int key,int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_LEFT:
			angley+=5;
			break;
		case GLUT_KEY_RIGHT:
			angley-=5;
			break;
		case GLUT_KEY_UP:
			anglex+=5;
			break;
		case GLUT_KEY_DOWN:
			anglex-=5;
			break;
		case GLUT_KEY_PAGE_UP:
			anglez+=5;
			break;
		case GLUT_KEY_PAGE_DOWN:
			anglez-=5;
			break;
		case GLUT_KEY_HOME:
			anglex=angley=anglez=0;
	}
}

void passivemotion(int x, int y)
{
	mousex=x;mousey=y;
}

void motion(int x, int y)
{
	
}

void quit(void)
{
	glutDestroyWindow(win);
	exit(0);
}


RGBi** GLLoadTexture(GLuint *texture,const char *name)
{	
	int i,j;
	BMP image;
	RGBi **bitmap;
	load_BMP(&image,name);
	bitmap=(RGBi**)calloc(sizeof(RGBi*),image.height);
	for(i=0;i<image.height;i++)
	{
		bitmap[i]=(RGBi*)calloc(sizeof(RGBi),image.width);
		for(j=0;j<image.width;j++)
		{
			bitmap[i][j].r=image.data[3*(i*image.width+j)+0];
			bitmap[i][j].g=image.data[3*(i*image.width+j)+1];
			bitmap[i][j].b=image.data[3*(i*image.width+j)+2];
		}
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1,texture);
	glBindTexture(GL_TEXTURE_2D,*texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,image.width,image.height,0,GL_RGB,GL_UNSIGNED_BYTE,image.data);
	return bitmap;
}
