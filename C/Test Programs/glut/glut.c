#include <GL/glut.h>

int i;

void display1(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	glFlush ();
}
void display2(void)
{
	i=(i+1)%255;
	glColor3f ((GLfloat)i/255,1-(GLfloat)i/255,0);
	glBegin(GL_POLYGON);
	glVertex3f (0.25, 0.25, 0.0);
	glVertex3f (0.75, 0.25, 0.0);
	glVertex3f (0.75, 0.75, 0.0);
	glVertex3f (0.25, 0.75, 0.0);
	glEnd();
	glFlush ();
	glutPostRedisplay();
}
void init (void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1,1,-1,1,-1,1);
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (250, 250);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("hello");
	init ();
	glutDisplayFunc(display1);
	glutDisplayFunc(display2);
	glutMainLoop();
	return 0;
}