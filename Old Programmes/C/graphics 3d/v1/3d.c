#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include "BMP.h"

#define WIDTH 500
#define HEIGHT 500

/* Structure Definition */
typedef struct Object
{
	GLuint texture;
	int order;
	int mask[512][512];
	GLfloat depth[512][512];
}Object;

/* Function Prototypes */
void display(void);												/* GLUT display function */
void reshape(int width, int height);							/* GLUT reshape function */
void mouse(int button, int state,int x, int y);					/* GLUT mouse function */
void keyboard(unsigned char key,int x, int y);					/* GLUT keyboard function */
void special_keyboard(int key,int x, int y);
void motion(int x, int y);										/* GLUT motion function */
void passivemotion(int x, int y);								/* GLUT passive motion function */
int button_pressed[3]={0,0,0},mousex,mousey;;

void lighting(void);
enum MODE{TRANSLATION,ROTATION,LIGHT};
int mode=ROTATION;

Object* OpenObject(const char *fname);
void depthate(Object *obj,GLfloat x,GLfloat y,GLfloat value);
void PrintObject(Object *obj,GLfloat size);
void load_texture(GLuint *texture,const char *name);			/* Loads a given texture */

GLfloat angle_x=0,angle_y=0,angle_z=0;
GLfloat x=0,y=0,z=0;
GLfloat light_x=0,light_y=0,light_z=0;
Object *obj;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize (WIDTH,HEIGHT);
	glutInitWindowPosition (0,0);
	glutCreateWindow ("3d");

	obj=OpenObject("fox/fox.txt");

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
	//lighting();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1.0f);
	glClearColor(1.0,1.0,1.0,1.0);

	glLoadIdentity();
	glTranslatef(light_x,light_y,light_z);
	glColor3f(1,1,1);
	glutSolidSphere(0.05,10,10);

	glLoadIdentity();
	glTranslatef(x,y,z);
	glRotatef(angle_x,1,0,0);
	glRotatef(angle_y,0,1,0);
	glRotatef(angle_z,0,0,1);
	if(button_pressed[0]) depthate(obj,(GLfloat)mousex/2/(GLfloat)WIDTH,(GLfloat)mousey/(GLfloat)HEIGHT, 0.01);
	if(button_pressed[2]) depthate(obj,(GLfloat)mousex/2/(GLfloat)WIDTH,(GLfloat)mousey/(GLfloat)HEIGHT,-0.01);
	PrintObject(obj,0.5);

	glutPostRedisplay();
	glutSwapBuffers();
}


void reshape(int width, int height)
{
	glViewport(0,0,width,height);
}

void mouse(int button, int state,int x, int y)
{
	switch(button)
	{
		case GLUT_LEFT_BUTTON:
			button_pressed[0]=!button_pressed[0];	
			mousex=x,mousey=y;
			break;
		case GLUT_RIGHT_BUTTON:
			button_pressed[2]=!button_pressed[2];
			mousex=x,mousey=y;
			break;
	}
}

void keyboard(unsigned char key,int x, int y)
{
	switch(key)
	{
		case 'l':
			mode=LIGHT;
			break;
		case 't':
			mode=TRANSLATION;
			break;
		case 'r':
			mode=ROTATION;
			break;
		case '27':
			exit(0);
			break;
	}
	switch(mode)
	{
		case ROTATION:
			switch(key)
			{
				case '8':
					angle_x-=5;
					break;
				case '2':
					angle_x+=5;
					break;
				case '4':
					angle_y-=5;
					break;
				case '6':
					angle_y+=5;
					break;
				case '7':
					angle_z+=5;
					break;
				case '3':
					angle_z-=5;
					break;
				case '5':
					angle_x=angle_y=angle_z=0;
					break;
			}
			break;
		case TRANSLATION:
			switch(key)
			{
				case '8':
					y+=.1;
					break;
				case '2':
					y-=.1;
					break;
				case '4':
					x+=.1;
					break;
				case '6':
					x-=.1;
					break;
				case '7':
					z+=.1;
					break;
				case '3':
					z-=.1;
					break;
				case '5':
					x=y=z=0;
					break;
			}
			break;
		case LIGHT:
			switch(key)
			{
				case '8':
					light_y+=.1;
					break;
				case '2':
					light_y-=.1;
					break;
				case '4':
					light_x-=.1;
					break;
				case '6':
					light_x+=.1;
					break;
				case '7':
					light_z+=.1;
					break;
				case '3':
					light_z-=.1;
					break;
				case '5':
					light_x=light_y=light_z=0;
					break;
			}
			break;
	}
}

void special_keyboard(int key,int x, int y)
{
}

void passivemotion(int x, int y)
{
	mousex=x,mousey=y;
}

void motion(int x, int y)
{
	mousex=x,mousey=y;
}

void load_texture(GLuint *texture,const char *name)
{	
	BMP image;
	printf("loading %s\n",name);
	load_BMP(&image,name);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1,texture);
	glBindTexture(GL_TEXTURE_2D,*texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST); 
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,image.width,image.height,0,GL_RGB,GL_UNSIGNED_BYTE,image.data);
	free_BMP(&image);
}

void lighting(void)
{	
	GLfloat light_position[3];
	GLfloat LightAmbient[]= { 0.7, 0.7, 0.7, 1.0 };
	GLfloat LightDiffuse[]= { 1.0, 1.0, 1.0, 1.0 };	
	light_position[0]=light_x;
	light_position[1]=light_y;
	light_position[2]=light_z;
	glLoadIdentity();
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
}

Object* OpenObject(const char *fname)
{
	char imagename[50],maskname[50],depthname[50];
	BMP mask,depth,image;
	Object *obj;
	int i,j;
	FILE *fp;

	if((fp=fopen(fname,"rt"))==NULL)
	{
		fprintf(stderr,"File \"%s\" read error\n",fname);
		exit(0);
	}
	fscanf(fp,"%s%s%s",imagename,maskname,depthname);
	fclose(fp);

	obj=(Object*)malloc(sizeof(Object));

	load_BMP(&image,imagename);
	load_BMP(&mask,maskname);	
	load_BMP(&depth,depthname);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1,&obj->texture);
	glBindTexture(GL_TEXTURE_2D,obj->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST); 
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,image.width,image.height,0,GL_RGB,GL_UNSIGNED_BYTE,image.data);	
	obj->order=image.width;

	for(i=0;i<obj->order;i++)
		for(j=0;j<obj->order;j++)
		{
			if(mask.data[3*(j*mask.width+i)+2]==0xff)
				obj->mask[i][j]=1;
			else
				obj->mask[i][j]=0;
			obj->depth[i][j]=(GLfloat)depth.data[3*(j*depth.width+i)+2]/(GLfloat)0xff;
		}

	free_BMP(&image);
	free_BMP(&mask);
	free_BMP(&depth);
	return obj;
}

void PrintObject(Object *obj,GLfloat size)
{
	int i,j;
	GLfloat x=-size/2,y=size/2,z=0;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,obj->texture);
	glBegin(GL_QUADS);
		for(i=0;i<obj->order-1;i++)
		{
			for(j=0;j<obj->order-1;j++)
			{
				if(obj->mask[i][j]==1)
					continue;
				glTexCoord2f((GLfloat)i/(GLfloat)obj->order,(GLfloat)j/(GLfloat)obj->order); 
				glVertex3f(x+(GLfloat)i*size/(GLfloat)obj->order,y+(GLfloat)-j*size/(GLfloat)obj->order,z+obj->depth[i][j]*size);
				glTexCoord2f((GLfloat)(i+1)/(GLfloat)obj->order,(GLfloat)j/(GLfloat)obj->order); 
				glVertex3f(x+(GLfloat)(i+1)*size/(GLfloat)obj->order,y+(GLfloat)-j*size/(GLfloat)obj->order,z+obj->depth[i+1][j]*size);
				glTexCoord2f((GLfloat)(i+1)/(GLfloat)obj->order,(GLfloat)(j+1)/(GLfloat)obj->order); 
				glVertex3f(x+(GLfloat)(i+1)*size/(GLfloat)obj->order,y+(GLfloat)-(j+1)*size/(GLfloat)obj->order,z+obj->depth[i+1][j+1]*size);
				glTexCoord2f((GLfloat)i/(GLfloat)obj->order,(GLfloat)(j+1)/(GLfloat)obj->order); 
				glVertex3f(x+(GLfloat)i*size/(GLfloat)obj->order,y+(GLfloat)-(j+1)*size/(GLfloat)obj->order,z+obj->depth[i][j+1]*size);
			}
		}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void depthate(Object *obj,GLfloat x,GLfloat y,GLfloat value)
{
	int i,j,X,Y;
	if(x>1.0 || x<0.0 || y>1.0 || y<0.0)
		return;
	X=x*(GLfloat)obj->order;
	Y=y*(GLfloat)obj->order;
	obj->depth[X][Y]+=value;
	for(i=0;i<obj->order;i++)
		for(j=0;j<obj->order;j++)
			obj->depth[i][j]=(100*(fabs(i-X)+fabs(j-Y))*obj->depth[i][j]+obj->depth[X][Y])/(100*(fabs(i-X)+fabs(j-Y))+1);
}
