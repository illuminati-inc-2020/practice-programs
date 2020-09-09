#ifndef __GLMENU_H
#define __GLMENU_H

#include <GL/glut.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "glstdio.h"

struct GLMenu
{
	int win;
	int active;
	int id;
	int nentries;
	char **lebel;
	void (**func)(void);
	int curposx,curposy;
}menu;

void GLCreatePopupMenu(int win,int x,int y,int nentries,...);
void popup_menu_mouse(int button, int state,int x, int y);
void popup_menu_motion(int x, int y);
void popup_menu_display(void);
int  GLDestroyPopupMenu(void);

void GLCreatePopupMenu(int win,int x,int y,int nentries,...)
{
	int i,lebel_length,max_lebel_length=0;
	char lebel[50];
	va_list ap;
	menu.win=win;
	menu.nentries=nentries;
	menu.lebel=(char**)malloc(sizeof(char*)*nentries);
	menu.func=(void(**)(void))malloc(sizeof(void(*)(void))*nentries);
	va_start(ap,nentries);
	for(i=0;i<nentries;i++)
	{
		strcpy(lebel,(const char*)va_arg(ap,char*));
		lebel_length=glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_10,lebel);
		max_lebel_length=(lebel_length>max_lebel_length)?lebel_length:max_lebel_length;
		menu.lebel[i]=(char*)malloc(sizeof(char)*(strlen(lebel)+1));
		strcpy(menu.lebel[i],lebel);
		menu.func[i]=(void(*)(void))va_arg(ap,void*);
	}	
	va_end(ap);
	menu.active=1;
	menu.id=glutCreateSubWindow(win,x,y,max_lebel_length+10,nentries*15);
	glutDisplayFunc(popup_menu_display);
	glutMouseFunc(popup_menu_mouse);
	glutPassiveMotionFunc(popup_menu_motion);
	glutMainLoop();
}

void popup_menu_display(void)
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1.0f);
	glClearColor(0.5,0.5,0.5,0.5);
	for(i=0;i<menu.nentries;i++)
	{
		if(menu.curposy>=i*15 && menu.curposy<(i+1)*15)
		{
			glColor3f(0,0,0);
			glBegin(GL_QUADS);
			glVertex2f(-1,(float)(menu.nentries-i*2-2)/(float)menu.nentries);
			glVertex2f( 1,(float)(menu.nentries-i*2-2)/(float)menu.nentries);
			glVertex2f( 1,(float)(menu.nentries-i*2)/(float)menu.nentries);
			glVertex2f(-1,(float)(menu.nentries-i*2)/(float)menu.nentries);
			glEnd();
		}
		glColor3f(1,1,1);
		GLPrintf(-.9,(float)(menu.nentries-i*2-1)/(float)menu.nentries,menu.lebel[i]);
	}
	glutSwapBuffers();
	glutPostRedisplay();
}

void popup_menu_mouse(int button, int state,int x, int y)
{
	int i;
	menu.curposx=x,menu.curposy=y;
	for(i=0;i<menu.nentries;i++)
		if(state==GLUT_DOWN && menu.curposy>=i*15 && menu.curposy<(i+1)*15)
		{
			glutSetWindow(menu.win);
			(*menu.func[i])();
			break;
		}	
	GLDestroyPopupMenu();
}

void popup_menu_motion(int x, int y)
{
	menu.curposx=x,menu.curposy=y;
}

int GLDestroyPopupMenu(void)
{
	int i;
	if(menu.active==0)
		return 0;
	glutSetWindow(menu.win);
	for(i=0;i<menu.nentries;i++)
		free(menu.lebel[i]);
	free(menu.lebel);
	free(menu.func);
	glutDestroyWindow(menu.id);
	menu.active=0;
	menu.nentries=0;
	return 1;
}

#endif