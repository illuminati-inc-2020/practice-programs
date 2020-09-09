#ifndef __GLSTDIO_H
#define __GLSTDIO_H

#include <stdarg.h>
#include <GL/glut.h>

struct TextBox
{
	char buf[50];
	char lebel[50];
	int bufpos;
	int active;
	void (*callback_func)(const char*);
}textbox={"\0",0,0};


void GLPrintf(GLfloat x,GLfloat y,const char *fmt,...);
void GLTextBoxFunc(const char *lebel,void (*callback_func)(const char*));
void GLTextBoxDisplay(void);
void GLTextBoxInput(unsigned char key);

void GLPrintf(GLfloat x,GLfloat y,const char *fmt,...)
{
	int i;
	char string[100];
	va_list ap;
	va_start(ap,fmt);
	vsprintf(string,fmt,ap);
	va_end(ap);
	glLoadIdentity();
	glRasterPos2f(x,y);
	for(i=0;i<strlen(string);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,string[i]);
}

void GLTextBoxFunc(const char *lebel,void (*callback_func)(const char*))
{
	strcpy(textbox.lebel,lebel);
	textbox.active=1;
	textbox.callback_func=callback_func;
}

void GLTextBoxDisplay(void)
{
	if(!textbox.active)
		return;
	GLPrintf(-1.00,-0.95,"%s : %s|",textbox.lebel,textbox.buf);
	glutPostRedisplay();
	glutSwapBuffers();
}

void GLTextBoxInput(unsigned char key)
{
	if(!textbox.active)
		return;
	switch(key)
	{
		case 13:
			textbox.active=0;
			(*textbox.callback_func)(textbox.buf);
			break;
		case 27:
			textbox.active=0;
			textbox.buf[0]='\0';
			break;
		case '\b':
			if(textbox.bufpos>0)
			{
				textbox.bufpos--;
				textbox.buf[textbox.bufpos]='\0';				
			}
			break;
		case 127:
			break;
		default:
			if(textbox.bufpos<50)
				textbox.buf[textbox.bufpos++]=key;
			break;
	}
}

#endif