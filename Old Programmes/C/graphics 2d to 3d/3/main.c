#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846264338327950288

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
float anglex=0,angley=0,anglez=0;

/* Structures */
struct Vertex3f
{
	float c[3];
};
struct Vertex2f
{
	float c[2];
};
struct Model
{
	int order;
	int vn;
	struct Vertex3f v[100];
}mdl;

/* Functions */
void CopyVertex3f(struct Vertex3f *v,float x, float y,float z);
void CreateSphere(float R,int order);
void PrintWire();

int main(int argc, char** argv)
{
	CreateSphere(0.5,5);

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize (WIDTH,HEIGHT);
	glutInitWindowPosition (0,0);
	win=glutCreateWindow ("3d");

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1.0f);
	glClearColor(0.0,0.0,0.0,0.0);

	glLoadIdentity();
	glRotatef(anglex,1,0,0);
	glRotatef(angley,0,1,0);
	glRotatef(anglez,0,0,1);

	PrintWire();
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
			break;
		case GLUT_KEY_PAGE_DOWN:
			break;
		case GLUT_KEY_HOME:
			anglex=angley=anglez=0;
			break;
	}
}

void passivemotion(int x, int y)
{
}

void motion(int x, int y)
{
}

void CreateSphere(float R,int order)
{
	float a,b;
	mdl.order=order;
	mdl.vn=0;
	CopyVertex3f(&mdl.v[mdl.vn++], 0.0,-R, 0.0);
	for(a=-PI/2+PI/order;a<=PI/2-PI/order;a+=PI/order)
	{
		for(b=-PI;b<PI;b+=2*PI/order)
		{
			CopyVertex3f(&mdl.v[mdl.vn++],R*cos(a)*cos(b),R*sin(a),R*cos(a)*sin(b));
			printf("%g,%g\n",a*180/PI,b*180/PI);
		}
		printf("\n");
	}
	CopyVertex3f(&mdl.v[mdl.vn++], 0.0, R, 0.0);
}

void PrintWire()
{
	int i;
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_POINTS);
	glColor3f(1,1,1);
	for(i=0;i<mdl.vn;i++)
		glVertex3fv(mdl.v[i].c);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(1,1,1);
	for(i=1;i<mdl.order+1;i++)
	{
		glVertex3fv(mdl.v[0].c);
		glVertex3fv(mdl.v[i].c);
	}
	for(i=mdl.vn-mdl.order-1;i<mdl.vn-1;i++)
	{
		glVertex3fv(mdl.v[mdl.vn-1].c);
		glVertex3fv(mdl.v[i].c);
	}
	for(i=1;i<mdl.order-1;i++)
		for(j=1)
	{
		glVertex3fv(mdl.v[mdl.vn-1].c);
		glVertex3fv(mdl.v[i].c);
	}
	glEnd();
	glDisable(GL_DEPTH_TEST);
}

void CopyVertex3f(struct Vertex3f *v,float x, float y,float z)
{
	v->c[0]=x;
	v->c[1]=y;
	v->c[2]=z;
}