#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include "BMP.h"
#include "menu.h"
#include "glstdio.h"

#define TEX_MAX 10
enum mode{WIRE,SOLID,DRAW_SOLID,DRAW_WIRE};
enum KEY_MODE{NORMAL,SHIFT,CTRL,ALT};

/* Structure Definition */
typedef struct Vertex
{
	GLfloat x,y,z;
	GLfloat X,Y;
	int fulcrum;
}Vertex;
typedef struct Triangle
{
	int v[3];
	int tex;
}Triangle;
typedef struct Quad
{
	int v[4];
	int tex;	
}Quad;
typedef struct Fulcrum
{
	int parent;			//Parent fulcrum index
	GLfloat x,y,z;		//position
	GLfloat ax,ay,az;	//angle with parent	
	char name[50];
}Fulcrum;
typedef struct Model
{
	int texn;	
	char texname[TEX_MAX][50];
	GLuint tex[TEX_MAX];	
	BMP bmp[TEX_MAX];
	int vn,tn,qn,fn;
	Vertex v[300];
	Triangle t[300];
	Quad q[300];
	Fulcrum f[50];
}Model;

/* Function Prototypes */
int win;														/* Window id */
int WIDTH=700,HEIGHT=700;										/* Window height & width */

void display(void);												/* GLUT display function */
void reshape(int width, int height);							/* GLUT reshape function */
int KEY_MODE=NORMAL;											/* Current Keyboard mode */
void mouse(int button, int state,int x, int y);					/* GLUT mouse function */
void keyboard(unsigned char key,int x, int y);					/* GLUT keyboard function */
void special_keyboard(int key,int x, int y);					/* GLUT special keyboard function */
void motion(int x, int y);										/* GLUT motion function */
void passivemotion(int x, int y);								/* GLUT passive motion function */
GLfloat texx=0,texy=0;											/* Cursor position on current texture */
GLfloat winx=0,winy=0,winz=0;									/* Cursor position on window */

void new_model(void);											/* Loads new blank model as project */
void load();													/* Loads new model from file as project */
void save();													/* Saves model in file*/
void SaveModel(const char* name);								/* Textbox CallBack func tion for save() */
void LoadModel(const char* name);								/* Textbox CallBack func tion for load() */
void quit(void);												/* Quit Program */

void insert_vertex();											/* Inserts a vertex and insert triangle/quad if posible */
void delete_vertex();											/* Deletes a vertex and all its adjacent triangles/quads/vertices */
void delete_isolated_vertices();								/* Deletes all vertices not incident to any triangle/quad */ 
void change_fulcrum();											/* Changes fulcrum of selected vertex */

void delete_triangle();											/* Deletesa triangle and all its adjacent vertices */
	
void delete_quad();												/* Deletesa quadd all its adjacent vertices */

void insert_fulcrum();											/* Inserts a fulcrum as child of current fulcrum */
void delete_fulcrum();											/* Deletes a non-root nd gives all child fulcrumsvertices to parent */
void get_fulcrum_name();										/* Gets a name for current fulcrum */ 
void CALLBACKget_fulcrum_name(const char *name);				/* Textbox CallBack func tion for get_fulcrum_name() */
void set_fulcrum();												/* Selected fulcrum as current fulcrum */

void add_texture();												/* Add a New texture to project */
void CALLBACKadd_texture(const char *name);						/* Textbox CallBack func tion for add_texture() */
void delete_texture();											/* Delete a texture from project */
void change_texture();											/* Changes texture of selected triangle/quad */
void CALLBACKchange_texture(const char *name);					/* Textbox CallBack func tion for change_texture() */
void change_texture_name();										/* Changes a texture name */
void CALLBACKchange_texture_name(const char *name);				/* Textbox CallBack func tion for change_texture_name() */
void LoadTexture(GLuint *texture,const char *name,				/* Loads a texture file and returns its texture and bitmap data */
				 BMP *image_return);



void get_vertex_position(int v,									/* Returns position of vertex v after rotation */
						GLfloat *x,GLfloat *y,GLfloat *z);
void get_fulcrum_position(int l,								/* Returns position of fulcrum v after rotation */
						GLfloat *x,GLfloat *y,GLfloat *z);
void print();													/* Prints all graphics */
void print_stat();												/* Prints all current statistics */

char filename[50]="\0";
Model model;
int mode=DRAW_SOLID;
int current_texture=0;
int current_fulcrum=0;
int selected_vertex=-1;						// Index of selected vertex, -1=none
int selected_triangle=-1;					// Index of selected triangle, -1=none
int selected_quad=-1;						// Index of selected quad, -1=none
int selected_fulcrum=-1;					// Index of selected fulcrum, -1=none
int count=0,new_vertex_count=0,v[4];

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize (WIDTH,HEIGHT);
	glutInitWindowPosition (0,0);
	win=glutCreateWindow ("3d");

	new_model();
	if(argc>=2)
	{
		strcpy(filename,argv[1]);
		LoadModel(argv[1]);
	}
	
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
	if((mode==DRAW_SOLID || mode==DRAW_WIRE) && (selected_vertex==-1 || selected_triangle==-1 || selected_quad==-1 || selected_fulcrum==-1))
		glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	else
		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);				

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1.0f);
	glClearColor(0.0,0.0,0.0,0.0);

	glEnable(GL_DEPTH_TEST);
	print();
	print_stat();	
	GLTextBoxDisplay();
	glDisable(GL_DEPTH_TEST);	

	glutPostRedisplay();
	glutSwapBuffers();
}

void get_vertex_position(int v,GLfloat *x,GLfloat *y,GLfloat *z)
{
	int l;
	GLfloat tx,ty,tz,ax=0,ay=0,az=0;
	for(l=model.v[v].fulcrum;l>=0;l=model.f[l].parent)
	{
		ax+=model.f[l].ax;
		ay+=model.f[l].ay;
		az+=model.f[l].az;
	}
	get_fulcrum_position(model.v[v].fulcrum,x,y,z);
	*x=model.v[v].x;
	*y=model.v[v].y;
	*z=model.v[v].z;
	tx= *x*cos(az*3.141592654/180)+*y*sin(az*3.141592654/180);
	ty=-*x*sin(az*3.141592654/180)+*y*cos(az*3.141592654/180);
	*x=tx,*y=ty;
	ty= *y*cos(ax*3.141592654/180)+*z*sin(ax*3.141592654/180);
	tz=-*y*sin(ax*3.141592654/180)+*z*cos(ax*3.141592654/180);
	*y=ty,*z=tz;
	tz= *z*cos(ay*3.141592654/180)+*x*sin(ay*3.141592654/180);
	tx=-*z*sin(ay*3.141592654/180)+*x*cos(ay*3.141592654/180);
	*z=tz,*x=tx;
}

void get_fulcrum_position(int l,GLfloat *x,GLfloat *y,GLfloat *z)
{
	int i;
	GLfloat tx,ty,tz,ax=0,ay=0,az=0;
	for(i=model.f[l].parent;i>=0;i=model.f[i].parent)
	{
		ax+=model.f[i].ax;
		ay+=model.f[i].ay;
		az+=model.f[i].az;
	}
	*x=model.f[l].x;
	*y=model.f[l].y;
	*z=model.f[l].z;
	tx= *x*cos(az*3.141592654/180)+*y*sin(az*3.141592654/180);
	ty=-*x*sin(az*3.141592654/180)+*y*cos(az*3.141592654/180);
	*x=tx,*y=ty;
	ty= *y*cos(ax*3.141592654/180)+*z*sin(ax*3.141592654/180);
	tz=-*y*sin(ax*3.141592654/180)+*z*cos(ax*3.141592654/180);
	*y=ty,*z=tz;
	tz= *z*cos(ay*3.141592654/180)+*x*sin(ay*3.141592654/180);
	tx=-*z*sin(ay*3.141592654/180)+*x*cos(ay*3.141592654/180);
	*z=tz,*x=tx;
}

void print()
{
	int i,j,k;
	GLfloat x,y,z;
	
	if(mode==DRAW_SOLID || mode==DRAW_WIRE)
	{
		/* Vertices */
		for(i=0;i<model.vn;i++)
		{
			get_vertex_position(i,&x,&y,&z);
			glLoadIdentity();			
			glTranslatef(x,y,z);
			glTranslatef(0,0,-winz-1);

			if(i==selected_vertex)
			{
				glColor3f(0,1,0);
				glutSolidSphere(.01,5,5);
			}
			else if(model.v[i].fulcrum==current_fulcrum)
			{
				glColor3f(1,0,0);
				glutSolidSphere(.007,6,6);
			}
			else
			{
				glBegin(GL_POINTS);
				glColor3f(1,1,1);			
				glVertex3f(0,0,0);
				glEnd();
			}
		}

		/* New vertices */			
		if(count>0)
		{
			for(i=0;i<count;i++)
			{
				get_vertex_position(v[i],&x,&y,&z);						
				glLoadIdentity();
				glTranslatef(x,y,z);
				glColor3f(0,1-(GLfloat)i/3,1);
				glutSolidSphere(.015,5,5);
			}
		}

		/* Background Texture */		
		glLoadIdentity();
		if(model.texn>0)
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,model.tex[current_texture]);
			glColor3f(.1,.1,.1);
			glBegin(GL_QUADS);
			glTexCoord2f(0,0);		glVertex3f(-1, 1, .99);
			glTexCoord2f(1,0);		glVertex3f( 1, 1, .99);
			glTexCoord2f(1,1);		glVertex3f( 1,-1, .99);
			glTexCoord2f(0,1);		glVertex3f(-1,-1, .99);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		}
		
		/* Levers */
		for(i=0;i<model.fn;i++)
		{
			get_fulcrum_position(i,&x,&y,&z);
			glLoadIdentity();		
			glTranslatef(x,y,z);
			if(mode==DRAW_SOLID || mode==DRAW_WIRE) glTranslatef(0,0,-winz-1);
			if(i==current_fulcrum) glColor4f((selected_fulcrum==i)?1:.5,(selected_fulcrum==i)?1:.5,0,1);
			else glColor4f(0,(selected_fulcrum==i)?1:.5,0,1);
			glutWireSphere(.02,6,6);

			
			glLoadIdentity();
			if(mode==DRAW_SOLID || mode==DRAW_WIRE) glTranslatef(0,0,-winz-1);
			if(mode==DRAW_SOLID || mode==DRAW_WIRE) glColor4f(.3,.3,.3,1);
			else glColor4f(1,0,0,1);
			glBegin(GL_LINES);
			glVertex3f(x,y,z);
			get_fulcrum_position(model.f[i].parent,&x,&y,&z);
			glVertex3f(x,y,z);
			glEnd();
		}
	}	
	
	if(mode==DRAW_SOLID || mode==SOLID)
	{
		/* Solid Model */
		glLoadIdentity();
		if(mode==DRAW_SOLID) glTranslatef(0,0,-winz-1);
		glEnable(GL_TEXTURE_2D);
		for(k=0;k<model.texn;k++)
		{		
			glBindTexture(GL_TEXTURE_2D,model.tex[k]);			
			glBegin(GL_TRIANGLES);
			for(i=0;i<model.tn;i++)
			{
				if(mode==DRAW_SOLID && selected_triangle==i) glColor3f(0,1,0);
				else glColor3f(1,1,1);
				if(model.t[i].tex==k)
				{
					for(j=0;j<3;j++)
					{
						glTexCoord2f(model.v[model.t[i].v[j]].X,model.v[model.t[i].v[j]].Y);
						get_vertex_position(model.t[i].v[j],&x,&y,&z);
						glVertex3f(x,y,z);
					}
				}
			}
			glEnd();
			glBegin(GL_QUADS);
			for(i=0;i<model.qn;i++)
			{
				if(mode==DRAW_SOLID && selected_quad==i) glColor3f(0,1,0);
				else glColor3f(1,1,1);
				if(model.q[i].tex==k)
				{
					for(j=0;j<4;j++)
					{
						glTexCoord2f(model.v[model.q[i].v[j]].X,model.v[model.q[i].v[j]].Y);
						get_vertex_position(model.q[i].v[j],&x,&y,&z);
						glVertex3f(x,y,z);
					}
				}
			}
			glEnd();
		}		
		glDisable(GL_TEXTURE_2D);
	}
	
	if(mode==DRAW_SOLID || mode==DRAW_WIRE || mode==WIRE)
	{
		/* Wireframe Model */
		glLoadIdentity();
		if(mode==DRAW_SOLID || mode==DRAW_WIRE) glTranslatef(0,0,-winz-1);
		glBegin(GL_LINES);
		glColor3f(1,1,1);
		for(i=0;i<model.tn;i++)
		{
			for(j=0;j<3;j++)
			{
				get_vertex_position(model.t[i].v[j],&x,&y,&z);
				glVertex3f(x,y,z);
				get_vertex_position(model.t[i].v[(j+1)%3],&x,&y,&z);
				glVertex3f(x,y,z);
			}
		}
		for(i=0;i<model.qn;i++)
		{
			for(j=0;j<4;j++)
			{
				get_vertex_position(model.q[i].v[j],&x,&y,&z);
				glVertex3f(x,y,z);
				get_vertex_position(model.q[i].v[(j+1)%4],&x,&y,&z);
				glVertex3f(x,y,z);
			}
		}
		glEnd();
		
		
	}
}

void print_stat()
{
	GLfloat X,Y,Z,ax,ay,az,tx,ty,tz;
	glColor3f(1,1,1);
	GLPrintf(-1.00, 0.95,"Model Name : %s",(strlen(filename)==0)?"unnamed":filename);
	GLPrintf(-1.00, 0.90,"Mode : %s",(mode==DRAW_SOLID)?"Draw (Solid)":(mode==DRAW_WIRE)?"Draw (Wire)":(mode==SOLID)?"Preview (Solid)":"Preview (Wire)");
	GLPrintf(-1.00, 0.85,"Lever : %s",model.f[current_fulcrum].name);
	if(mode==DRAW_SOLID || mode==DRAW_WIRE)
	{
		GLPrintf(-1.00, 0.80,"Texture : %s",(model.texn>0)?model.texname[current_texture]:"none");
		ax=-model.f[0].ax,ay=-model.f[0].ay,az=-model.f[0].az;
		X=winx,Y=winy,Z=winz;
		tx= X*cos(az*3.141592654/180)+Y*sin(az*3.141592654/180);
		ty=-X*sin(az*3.141592654/180)+Y*cos(az*3.141592654/180);
		X=tx,Y=ty;
		ty= Y*cos(ax*3.141592654/180)+Z*sin(ax*3.141592654/180);
		tz=-Y*sin(ax*3.141592654/180)+Z*cos(ax*3.141592654/180);
		Y=ty,Z=tz;
		tz= Z*cos(ay*3.141592654/180)+X*sin(ay*3.141592654/180);
		tx=-Z*sin(ay*3.141592654/180)+X*cos(ay*3.141592654/180);
		Z=tz,X=tx;
		GLPrintf( 0.70,-0.95,"(%4.3f,%4.3f,%4.3f)",X,Y,Z);
		if(selected_vertex!=-1)
		{
			GLPrintf( 0.60, 0.95,"Vertex :");
			GLPrintf( 0.60, 0.90,"(%4.3f,%4.3f,%4.3f)",model.v[selected_vertex].x,model.v[selected_vertex].y,model.v[selected_vertex].z);
		}
		else if(selected_triangle!=-1)
		{
			GLPrintf( 0.60, 0.95,"Triangle :");
			GLPrintf( 0.60, 0.90,"(%4.3f,%4.3f,%4.3f)",model.v[model.t[selected_triangle].v[0]].x,model.v[model.t[selected_triangle].v[0]].y,model.v[model.t[selected_triangle].v[0]].z);
			GLPrintf( 0.60, 0.85,"(%4.3f,%4.3f,%4.3f)",model.v[model.t[selected_triangle].v[1]].x,model.v[model.t[selected_triangle].v[1]].y,model.v[model.t[selected_triangle].v[1]].z);
			GLPrintf( 0.60, 0.80,"(%4.3f,%4.3f,%4.3f)",model.v[model.t[selected_triangle].v[2]].x,model.v[model.t[selected_triangle].v[2]].y,model.v[model.t[selected_triangle].v[2]].z);
			GLPrintf( 0.60, 0.75,"Texture : %s",model.texname[model.t[selected_triangle].tex]);
		}
		else if(selected_quad!=-1)
		{
			GLPrintf( 0.60, 0.95,"Quad :");
			GLPrintf( 0.60, 0.90,"(%4.3f,%4.3f,%4.3f)",model.v[model.q[selected_quad].v[0]].x,model.v[model.q[selected_quad].v[0]].y,model.v[model.q[selected_quad].v[0]].z);
			GLPrintf( 0.60, 0.85,"(%4.3f,%4.3f,%4.3f)",model.v[model.q[selected_quad].v[1]].x,model.v[model.q[selected_quad].v[1]].y,model.v[model.q[selected_quad].v[1]].z);
			GLPrintf( 0.60, 0.80,"(%4.3f,%4.3f,%4.3f)",model.v[model.q[selected_quad].v[2]].x,model.v[model.q[selected_quad].v[2]].y,model.v[model.q[selected_quad].v[2]].z);
			GLPrintf( 0.60, 0.75,"(%4.3f,%4.3f,%4.3f)",model.v[model.q[selected_quad].v[3]].x,model.v[model.q[selected_quad].v[3]].y,model.v[model.q[selected_quad].v[3]].z);
			GLPrintf( 0.60, 0.70,"Texture : %s",model.texname[model.q[selected_quad].tex]);
		}
		else if(selected_fulcrum!=-1)
		{
			GLPrintf( 0.60, 0.95,"Fulcrum :");
			GLPrintf( 0.60, 0.90,"(%4.3f,%4.3f,%4.3f)",model.f[selected_fulcrum].x,model.f[selected_fulcrum].y,model.f[selected_fulcrum].z);
			GLPrintf( 0.60, 0.85,"Angle : %4.3f,%4.3f,%4.3f",model.f[selected_fulcrum].ax,model.f[selected_fulcrum].ay,model.f[selected_fulcrum].az);
		}
	}
}

void reshape(int width, int height)
{
	glViewport(0,0,width,height);
	WIDTH=width;
	HEIGHT=height;
}

void mouse(int button, int state,int x, int y)
{
	texx=(GLfloat)x/(GLfloat)WIDTH;
	texy=(GLfloat)y/(GLfloat)HEIGHT;
	winx=2*(GLfloat)x/(GLfloat)WIDTH-1;
	winy=1-2*(GLfloat)y/(GLfloat)HEIGHT;

	if(glutGetModifiers()==GLUT_ACTIVE_SHIFT) KEY_MODE=SHIFT;
	else if(glutGetModifiers()==GLUT_ACTIVE_CTRL) KEY_MODE=CTRL;
	else if(glutGetModifiers()==GLUT_ACTIVE_ALT) KEY_MODE=ALT;
	else KEY_MODE=NORMAL;
	
	if(state==GLUT_DOWN && menu.active)
	{
		GLDestroyPopupMenu();
		return;
	}

	if(mode==DRAW_SOLID || mode==DRAW_WIRE)
	{
		switch(button)
		{
			case GLUT_LEFT_BUTTON:
				switch(state)
				{
					case GLUT_DOWN:
						insert_vertex();
						break;
				}
				break;
			case GLUT_RIGHT_BUTTON:
				model.vn-=new_vertex_count;
				count=0;
				new_vertex_count=0;
				switch(state)
				{
					case GLUT_DOWN:
						break;
					case GLUT_UP:
						if(selected_vertex!=-1)
						{
							GLCreatePopupMenu(win,x,y,2,
								"Delete Vertex",&delete_vertex,
								"Add Vertex to Current Fulcrum",&change_fulcrum);
						}
						else if(selected_triangle!=-1)
						{
							GLCreatePopupMenu(win,x,y,1,
								"Delete Triangle",&delete_triangle);
						}
						else if(selected_quad!=-1)
						{
							GLCreatePopupMenu(win,x,y,1,
								"Delete Quad",&delete_quad);
						}
						else if(selected_fulcrum!=-1)
						{
							GLCreatePopupMenu(win,x,y,3,
								"Delete Fulcrum",&delete_fulcrum,
								"Change Fulcrum Name",&get_fulcrum_name,
								"Set as Current Fulcrum",&set_fulcrum);
						}
						else
						{
							GLCreatePopupMenu(win,x,y,10,
								"Insert Vertex",&insert_vertex,
								"Insert Fulcrum",&insert_fulcrum,
								"Add New Texture File",&add_texture,
								"Change Current Texture Name",&change_texture_name,
								"Delete Current Texture File",&delete_texture,
								"Change Current Texture File",&change_texture,
								"New Model",&new_model,
								"Load Model",&load,
								"Save Model",&save,
								"Exit",&quit);
						}
						break;
				}
				break;
			case GLUT_MIDDLE_BUTTON:
				model.vn-=new_vertex_count;
				count=0;
				new_vertex_count=0;
				break;
		}
	}
	else
	{
		switch(button)
		{
			case GLUT_RIGHT_BUTTON:
				switch(state)
				{
					case GLUT_UP:
						GLCreatePopupMenu(win,x,y,4,
							"New Model",&new_model,
							"Load Model",&load,
							"Save Model",&save,
							"Exit",&quit);
				}
				break;
		}
	}
}

void keyboard(unsigned char key,int x, int y)
{
	if(menu.active)
	{
		GLDestroyPopupMenu();
		return;
	}
	GLTextBoxInput(key);

	switch(key)
	{		
		case '\t':		//Change Texture
			if(mode==DRAW_SOLID || mode==DRAW_WIRE)
				current_texture=(current_texture+1)%model.texn;
			else
				current_fulcrum=(current_fulcrum+1)%model.fn;
			break;
		case ' ':		// Change Mode
			mode=(mode==DRAW_SOLID)?DRAW_WIRE:(mode==DRAW_WIRE)?WIRE:(mode==WIRE)?SOLID:DRAW_SOLID;
			break;	
		case '=':		//Elevate
			if(selected_vertex!=-1)
				model.v[selected_vertex].z+=.01;
			else if(selected_fulcrum!=-1)
				model.f[selected_fulcrum].z+=.01;
			break;
		case '-':			
			if(selected_vertex!=-1)
				model.v[selected_vertex].z-=.01;
			else if(selected_fulcrum!=-1)
				model.f[selected_fulcrum].z-=.01;
			break;			
		case 127:		//Delete
			if(mode==DRAW_SOLID || mode==DRAW_WIRE)
			{
				delete_vertex();
				delete_triangle();
				delete_quad();
			}
			else if(mode==WIRE && current_fulcrum!=0)
				delete_fulcrum();
			break;
		case '8':
			model.f[current_fulcrum].ax+=3;
			break;
		case '2':
			model.f[current_fulcrum].ax-=3;
			break;
		case '4':
			model.f[current_fulcrum].ay+=3;
			break;
		case '6':
			model.f[current_fulcrum].ay-=3;
			break;
		case '7':
			model.f[current_fulcrum].az-=3;
			break;
		case '9':
			model.f[current_fulcrum].az+=3;
			break;
		case '5':
			model.f[current_fulcrum].ax=model.f[current_fulcrum].ay=model.f[current_fulcrum].az=0;
			break;
	}
}

void special_keyboard(int key,int x, int y)
{
	if(menu.active)
	{
		GLDestroyPopupMenu();
		return;
	}

	switch(key)
	{
		case GLUT_KEY_UP:		//Rotation
			if(selected_vertex!=-1)
				model.v[selected_vertex].y+=.01;
			else if(selected_fulcrum!=-1)
				model.f[selected_fulcrum].y+=.01;
			break;
		case GLUT_KEY_DOWN:
			if(selected_vertex!=-1)
				model.v[selected_vertex].y-=.01;
			else if(selected_fulcrum!=-1)
				model.f[selected_fulcrum].y-=.01;
			break;
		case GLUT_KEY_LEFT:
			if(selected_vertex!=-1)
				model.v[selected_vertex].x-=.01;
			else if(selected_fulcrum!=-1)
				model.f[selected_fulcrum].x-=.01;
			break;
		case GLUT_KEY_RIGHT:
			if(selected_vertex!=-1)
				model.v[selected_vertex].x+=.01;
			else if(selected_fulcrum!=-1)
				model.f[selected_fulcrum].x+=.01;
			break;
		case GLUT_KEY_PAGE_UP:
			winz+=(winz>=1)?0:.01;
			break;
		case GLUT_KEY_PAGE_DOWN:
			winz-=(winz<=-1)?0:.01;
			break;
		case GLUT_KEY_HOME:
			winz=0;
			break;
		case GLUT_KEY_END:
			winz=-1;
			break;
	}
}

void passivemotion(int x, int y)
{
	int i;
	GLfloat X[4],Y[4],Z[4],minz=999999;
	
	if(menu.active)
		return;

	texx=(GLfloat)x/(GLfloat)WIDTH;
	texy=(GLfloat)y/(GLfloat)HEIGHT;
	winx=2*(GLfloat)x/(GLfloat)WIDTH-1;
	winy=1-2*(GLfloat)y/(GLfloat)HEIGHT;

	selected_vertex=-1;
	for(i=0;i<model.vn;i++)
	{
		get_vertex_position(i,&X[0],&Y[0],&Z[0]);
		if(	X[0]<=winx+.01 && 
			X[0]>=winx-.01 && 
			Y[0]<=winy+.01 && 
			Y[0]>=winy-.01 &&
			Z[0]>=winz-.01 &&
			Z[0]<minz )
		{
			minz=Z[0];
			selected_vertex=i;
			selected_triangle=selected_quad=selected_fulcrum=-1;
		}
	}
	selected_triangle=-1;
	for(i=0;i<model.tn;i++)
	{
		get_vertex_position(model.t[i].v[0],&X[0],&Y[0],&Z[0]);
		get_vertex_position(model.t[i].v[1],&X[1],&Y[1],&Z[1]);
		get_vertex_position(model.t[i].v[2],&X[2],&Y[2],&Z[2]);
		if(	(X[0]+X[1]+X[2])/3<=winx+.02 &&
			(X[0]+X[1]+X[2])/3>=winx-.02 &&
			(Y[0]+Y[1]+Y[2])/3<=winy+.02 &&
			(Y[0]+Y[1]+Y[2])/3>=winy-.02 &&
			(Z[0]+Z[1]+Z[2])/3>=winz-.02 &&
			(Z[0]+Z[1]+Z[2])/3<minz )
		{
			minz=(Z[0]+Z[1]+Z[2])/3;
			selected_triangle=i;
			selected_vertex=selected_quad=selected_fulcrum=-1;
		}
	}
	selected_quad=-1;
	for(i=0;i<model.qn;i++)
	{
		get_vertex_position(model.q[i].v[0],&X[0],&Y[0],&Z[0]);
		get_vertex_position(model.q[i].v[1],&X[1],&Y[1],&Z[1]);
		get_vertex_position(model.q[i].v[2],&X[2],&Y[2],&Z[2]);
		get_vertex_position(model.q[i].v[3],&X[3],&Y[3],&Z[3]);
		if(	(X[0]+X[1]+X[2]+X[3])/4<=winx+.02 &&
			(X[0]+X[1]+X[2]+X[3])/4>=winx-.02 &&
			(Y[0]+Y[1]+Y[2]+Y[3])/4<=winy+.02 &&
			(Y[0]+Y[1]+Y[2]+Y[3])/4>=winy-.02 &&
			(Z[0]+Z[1]+Z[2]+Z[3])/4>=winz-.02 &&
			(Z[0]+Z[1]+Z[2]+Z[3])/4<minz )
		{
			minz=(Z[0]+Z[1]+Z[2]+Z[3])/4;
			selected_quad=i;
			selected_vertex=selected_triangle=selected_fulcrum=-1;
		}
	}
	selected_fulcrum=-1;
	for(i=0;i<model.fn;i++)
	{
		get_fulcrum_position(i,&X[0],&Y[0],&Z[0]);
		if(	X[0]<=winx+.01 && 
			X[0]>=winx-.01 && 
			Y[0]<=winy+.01 && 
			Y[0]>=winy-.01 &&
			Z[0]>=winz-.01 &&
			Z[0]<minz)
		{
			minz=Z[0];
			selected_fulcrum=i;
			selected_vertex=selected_triangle=selected_quad=-1;
		}
	}
}

void motion(int x, int y)
{
	int i;
	GLfloat winX,winY,winZ,tx,ty,tz,texX,texY;
	
	texX=(GLfloat)x/(GLfloat)WIDTH;
	texY=(GLfloat)y/(GLfloat)HEIGHT;

	winX=2*(GLfloat)x/(GLfloat)WIDTH-1;
	winY=1-2*(GLfloat)y/(GLfloat)HEIGHT;
	winZ=winz;
	tx= winX*cos(model.f[0].az*3.141592654/180)+winY*sin(model.f[0].az*3.141592654/180);
	ty=-winX*sin(model.f[0].az*3.141592654/180)+winY*cos(model.f[0].az*3.141592654/180);
	winX=tx,winY=ty;
	ty= winY*cos(model.f[0].ax*3.141592654/180)+winZ*sin(model.f[0].ax*3.141592654/180);
	tz=-winY*sin(model.f[0].ax*3.141592654/180)+winZ*cos(model.f[0].ax*3.141592654/180);
	winY=ty,winZ=tz;
	tz= winZ*cos(model.f[0].ay*3.141592654/180)+winX*sin(model.f[0].ay*3.141592654/180);
	tx=-winZ*sin(model.f[0].ay*3.141592654/180)+winX*cos(model.f[0].ay*3.141592654/180);
	winZ=tz,winX=tx;

	model.vn-=new_vertex_count;
	count=0;
	new_vertex_count=0;

	if(mode==DRAW_SOLID || mode==DRAW_WIRE)
	{
		if(selected_vertex!=-1)
		{
			if(KEY_MODE!=CTRL)
			{
				
				model.v[selected_vertex].x+=winX-winx;
				model.v[selected_vertex].y+=winY-winy;
			}
			if(KEY_MODE!=SHIFT)
			{
				model.v[selected_vertex].X+=texX-texx;
				model.v[selected_vertex].Y+=texY-texy;
			}
		}
		else if(selected_triangle!=-1)
		{
			for(i=0;i<3;i++)
			{
				if(KEY_MODE!=CTRL)
				{
					model.v[model.t[selected_triangle].v[i]].x+=winX-winx;
					model.v[model.t[selected_triangle].v[i]].y+=winY-winy;
				}
				if(KEY_MODE!=SHIFT)
				{
					model.v[model.t[selected_triangle].v[i]].X+=texX-texx;
					model.v[model.t[selected_triangle].v[i]].Y+=texY-texy;
				}
			}
		}
		else if(selected_quad!=-1)
		{
			for(i=0;i<4;i++)
			{
				if(KEY_MODE!=CTRL)
				{
					model.v[model.q[selected_quad].v[i]].x+=winX-winx;
					model.v[model.q[selected_quad].v[i]].y+=winY-winy;
				}
				if(KEY_MODE!=SHIFT)
				{
					model.v[model.q[selected_quad].v[i]].X+=texX-texx;
					model.v[model.q[selected_quad].v[i]].Y+=texY-texy;
				}
			}
		}
		else if(selected_fulcrum!=-1)
		{
			model.f[selected_fulcrum].x+=winX-winx;
			model.f[selected_fulcrum].y+=winY-winy;
		}
	}
	winx=winX,winy=winY;
	texx=texX,texy=texY;
}

void quit(void)
{
	glutDestroyWindow(win);
	exit(0);
}

void new_model(void)
{
	model.texn=0;
	model.vn=0;
	model.tn=0;
	model.qn=0;
	model.fn=1;
	model.f[0].parent=-1;
	model.f[0].x=model.f[0].y=model.f[0].z=0;
	model.f[0].ax=model.f[0].ay=model.f[0].az=0;
	strcpy(model.f[0].name,"Base");
	filename[0]=0;
}

void LoadTexture(GLuint *texture,const char *name,BMP *image_return)
{	
	load_BMP(image_return,name);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1,texture);
	glBindTexture(GL_TEXTURE_2D,*texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,image_return->width,image_return->height,0,GL_RGB,GL_UNSIGNED_BYTE,image_return->data);
}

void SaveModel(const char* name)
{
	FILE *fp;
	int i;

	if((fp=fopen(name,"wb"))==NULL)
	{
		fprintf(stderr,"save error\n");
		return;
	}
	
	fwrite(&model.texn,sizeof(int),1,fp);
	for(i=0;i<model.texn;i++)
	{
		fwrite(model.texname[i],sizeof(char),50,fp);
		fwrite(&model.bmp[i].width,sizeof(unsigned long),1,fp);
		fwrite(&model.bmp[i].height,sizeof(unsigned long),1,fp);
		fwrite(model.bmp[i].data,sizeof(unsigned char),model.bmp[i].height*model.bmp[i].width*3,fp);
	}
	fwrite(&model.vn,sizeof(int),1,fp);
	fwrite(model.v,sizeof(Vertex),model.vn,fp);
	fwrite(&model.tn,sizeof(int),1,fp);
	fwrite(model.t,sizeof(Triangle),model.tn,fp);
	fwrite(&model.qn,sizeof(int),1,fp);
	fwrite(model.q,sizeof(Quad),model.qn,fp);
	fwrite(&model.fn,sizeof(int),1,fp);
	fwrite(model.f,sizeof(Fulcrum),model.fn,fp);

	fclose(fp);
	strcpy(filename,name);
}

void LoadModel(const char* name)
{
	FILE *fp;
	int i;
	if((fp=fopen(name,"rb"))==NULL)
	{
		fprintf(stderr,"load error\n");
		return;
	}
	
	fread(&model.texn,sizeof(int),1,fp);
	for(i=0;i<model.texn;i++)
	{
		fread(model.texname[i],sizeof(char),50,fp);
		fread(&model.bmp[i].width,sizeof(unsigned long),1,fp);
		fread(&model.bmp[i].height,sizeof(unsigned long),1,fp);
		model.bmp[i].data=(unsigned char*)calloc(sizeof(unsigned char),model.bmp[i].height*model.bmp[i].width*3);
		fread(model.bmp[i].data,sizeof(unsigned char),model.bmp[i].height*model.bmp[i].width*3,fp);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glGenTextures(1,&model.tex[i]);
		glBindTexture(GL_TEXTURE_2D,model.tex[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,model.bmp[i].width,model.bmp[i].height,0,GL_RGB,GL_UNSIGNED_BYTE,model.bmp[i].data);
	}
	fread(&model.vn,sizeof(int),1,fp);
	fread(model.v,sizeof(Vertex),model.vn,fp);
	fread(&model.tn,sizeof(int),1,fp);
	fread(model.t,sizeof(Triangle),model.tn,fp);
	fread(&model.qn,sizeof(int),1,fp);
	fread(model.q,sizeof(Quad),model.qn,fp);
	fread(&model.fn,sizeof(int),1,fp);
	fread(model.f,sizeof(Fulcrum),model.fn,fp);

	fclose(fp);
	strcpy(filename,name);
}

void save()
{	
	if(strlen(filename)==0)
		GLTextBoxFunc("Save Model",SaveModel);
	else 
		SaveModel(filename);
}

void load()
{
	GLTextBoxFunc("Load Model",LoadModel);
}

void insert_vertex()
{
	int i,new_vertex_index=-1,repeat=0;
	GLfloat X,Y,Z,tx,ty,tz,ax,ay,az;

	if(count<4)
	{
		new_vertex_index=selected_vertex;
		for(i=0;i<count;i++)
		{
			get_vertex_position(v[i],&X,&Y,&Z);
			if(	X<=winx+.01 && 
				X>=winx-.01 && 
				Y<=winy+.01 && 
				Y>=winy-.01 &&
				Z>=winz-.01)
				if(!(count==3 && i==0))
				{
					repeat=1;
					break;
				}
		}
		if(!repeat)
		{
			if(new_vertex_index==-1)
			{
				ax=-model.f[0].ax,ay=-model.f[0].ay,az=-model.f[0].az;
				X=winx,Y=winy,Z=winz;
				tx= X*cos(az*3.141592654/180)+Y*sin(az*3.141592654/180);
				ty=-X*sin(az*3.141592654/180)+Y*cos(az*3.141592654/180);
				X=tx,Y=ty;
				ty= Y*cos(ax*3.141592654/180)+Z*sin(ax*3.141592654/180);
				tz=-Y*sin(ax*3.141592654/180)+Z*cos(ax*3.141592654/180);
				Y=ty,Z=tz;
				tz= Z*cos(ay*3.141592654/180)+X*sin(ay*3.141592654/180);
				tx=-Z*sin(ay*3.141592654/180)+X*cos(ay*3.141592654/180);
				Z=tz,X=tx;
				model.v[model.vn].x=X;
				model.v[model.vn].y=Y;
				model.v[model.vn].z=Z;
				model.v[model.vn].X=texx;
				model.v[model.vn].Y=texy;
				model.v[model.vn].fulcrum=current_fulcrum;
				v[count]=model.vn;
				model.vn++;
				new_vertex_count++;				
			}
			else
				v[count]=new_vertex_index;
			count++;
		}
	}	
	
	if(count==4)
	{
		if(v[0]==v[3])
		{
			model.t[model.tn].v[2]=v[2];
			model.t[model.tn].v[1]=v[1];
			model.t[model.tn].v[0]=v[0];
			model.t[model.tn].tex=current_texture;
			model.tn++;
			count=0;
			new_vertex_count=0;
		}		
		else
		{
			model.q[model.qn].v[3]=v[3];
			model.q[model.qn].v[2]=v[2];
			model.q[model.qn].v[1]=v[1];
			model.q[model.qn].v[0]=v[0];
			model.q[model.qn].tex=current_texture;
			model.qn++;
			count=0;
			new_vertex_count=0;
		}
	}
	else if(count>4)
	{
		model.vn-=new_vertex_count;
		count=0;
		new_vertex_count=0;
	}
}

void delete_vertex()
{
	int j;
	
	if(count>0)

	{
		model.vn-=new_vertex_count;
		count=0;
		new_vertex_count=0;
		return;
	}
	if(selected_vertex==-1) return;

	//Deleteing adjacent triangles
	for(j=0;j<model.tn;)
	{
		if(model.t[j].v[0]==selected_vertex || model.t[j].v[1]==selected_vertex || model.t[j].v[2]==selected_vertex)
		{
			memmove(&model.t[j],&model.t[j+1],(model.tn-j)*sizeof(Triangle));
			model.tn--;
		}
		else
		{
			if(model.t[j].v[0]>selected_vertex) model.t[j].v[0]--;
			if(model.t[j].v[1]>selected_vertex) model.t[j].v[1]--;
			if(model.t[j].v[2]>selected_vertex) model.t[j].v[2]--;
			j++;
		}
	}
	//Deleteing adjacent quads
	for(j=0;j<model.qn;)
	{	
		if(model.q[j].v[0]==selected_vertex || model.q[j].v[1]==selected_vertex || model.q[j].v[2]==selected_vertex || model.q[j].v[3]==selected_vertex)
		{
			memmove(&model.q[j],&model.q[j+1],(model.qn-j)*sizeof(Quad));
			model.qn--;
		}
		else
		{
			if(model.q[j].v[0]>selected_vertex) model.q[j].v[0]--;
			if(model.q[j].v[1]>selected_vertex) model.q[j].v[1]--;
			if(model.q[j].v[2]>selected_vertex) model.q[j].v[2]--;
			if(model.q[j].v[3]>selected_vertex) model.q[j].v[3]--;
			j++;
		}
	} 
	//Deleteing vertex
	memmove(&model.v[selected_vertex],&model.v[selected_vertex+1],(model.vn-selected_vertex)*sizeof(Vertex));
	model.vn--;

	delete_isolated_vertices();

	selected_vertex=-1;
}

void delete_triangle()
{
	if(count>0)
	{
		model.vn-=new_vertex_count;
		count=0;
		new_vertex_count=0;
		return;
	}
	if(selected_triangle==-1) return;

	memmove(&model.t[selected_triangle],&model.t[selected_triangle+1],(model.tn-selected_triangle)*sizeof(Triangle));
		model.tn--;

	delete_isolated_vertices();

	selected_triangle=-1;
}

void delete_quad()
{
	if(count>0)
	{
		model.vn-=new_vertex_count;
		count=0;
		new_vertex_count=0;
		return;
	}
	if(selected_quad==-1) return;

	memmove(&model.q[selected_quad],&model.q[selected_quad+1],(model.qn-selected_quad)*sizeof(Quad));
		model.qn--;

	delete_isolated_vertices();

	selected_quad=-1;
}

void delete_isolated_vertices()
{
	int i,j,flag;
	for(i=0;i<model.vn;)
	{
		flag=0;
		for(j=0;flag==0 && j<=model.tn;j++)
			if(model.t[j].v[0]==i || model.t[j].v[1]==i || model.t[j].v[2]==i)
			{
				flag=1;
				break;
			}
		for(j=0;flag==0 && j<=model.qn;j++)
			if(model.q[j].v[0]==i || model.q[j].v[1]==i || model.q[j].v[2]==i || model.q[j].v[3]==i)
			{
				flag=1;
				break;
			}
		if(flag==0)
		{
			for(j=0;flag==0 && j<model.tn;j++)
			{
				if(model.t[j].v[0]>i) model.t[j].v[0]--;
				if(model.t[j].v[1]>i) model.t[j].v[1]--;
				if(model.t[j].v[2]>i) model.t[j].v[2]--;
			}
			for(j=0;flag==0 && j<model.qn;j++)
			{
				if(model.q[j].v[0]>i) model.q[j].v[0]--;
				if(model.q[j].v[1]>i) model.q[j].v[1]--;
				if(model.q[j].v[2]>i) model.q[j].v[2]--;
				if(model.q[j].v[3]>i) model.q[j].v[3]--;
			}
			memmove(&model.v[i],&model.v[i+1],(model.vn-i)*sizeof(Vertex));
			model.vn--;
		}
		else
			i++;
	}
}

void insert_fulcrum()
{
	model.f[model.fn].parent=current_fulcrum;
	model.f[model.fn].x=winx;
	model.f[model.fn].y=winy;
	model.f[model.fn].z=winz;
	model.f[model.fn].ax=model.f[model.fn].ay=model.f[model.fn].az=0;
	selected_fulcrum=current_fulcrum=model.fn;
	get_fulcrum_name();
	model.fn++;
}

void delete_fulcrum()
{
	int i,parent;
	if(selected_fulcrum<=0)
		return;
	parent=model.f[selected_fulcrum].parent;
	for(i=0;i<model.vn;i++)
		if(model.v[i].fulcrum==selected_fulcrum)
			model.v[i].fulcrum=parent;
	for(i=0;i<model.fn;i++)
		if(model.f[i].parent==selected_fulcrum)
			model.f[i].parent=parent;
	memmove(&model.f[selected_fulcrum],&model.f[selected_fulcrum+1],(model.fn-selected_fulcrum)*sizeof(Fulcrum));
	model.fn--;
	selected_fulcrum=parent;
}

void get_fulcrum_name()
{
	if(selected_fulcrum==-1) return;
	current_fulcrum=selected_fulcrum;
	selected_fulcrum=-1;
	GLTextBoxFunc("New Fulcrum Name",CALLBACKget_fulcrum_name);
}
void CALLBACKget_fulcrum_name(const char *name)
{
	strcpy(model.f[current_fulcrum].name,name);
}

void change_fulcrum()
{
	model.v[selected_vertex].fulcrum=current_fulcrum;
	selected_vertex=-1;
}

void set_fulcrum()
{
	if(selected_fulcrum!=-1)
		current_fulcrum=selected_fulcrum;
	selected_fulcrum=-1;
}

void add_texture()
{
	GLTextBoxFunc("Texture Filename",CALLBACKadd_texture);
}
void CALLBACKadd_texture(const char *name)
{
	LoadTexture(&model.tex[model.texn],name,&model.bmp[model.texn]);
	strcpy(model.texname[model.texn],name);
	model.texn++;
}

void delete_texture()
{
	int j;
	for(j=0;j<model.tn;)
		if(model.t[j].tex==current_texture)
		{
			memmove(&model.t[j],&model.t[j+1],(model.tn-j)*sizeof(Triangle));
			model.tn--;
		}
		else j++;
	for(j=0;j<model.qn;)
		if(model.q[j].tex==current_texture)
		{
			memmove(&model.q[j],&model.q[j+1],(model.qn-j)*sizeof(Quad));
			model.qn--;
		}
		else j++;
	delete_isolated_vertices();
	memmove(&model.texname[current_texture],&model.texname[current_texture+1],(model.texn-current_texture)*sizeof(char)*50);
	memmove(&model.tex[current_texture],&model.tex[current_texture+1],(model.texn-current_texture)*sizeof(GLuint));
	memmove(&model.bmp[current_texture],&model.bmp[current_texture+1],(model.texn-current_texture)*sizeof(BMP));
	model.texn--;
}

void change_texture()
{
	GLTextBoxFunc("New Texture Filename",CALLBACKchange_texture);
}
void CALLBACKchange_texture(const char *name)
{
	LoadTexture(&model.tex[current_texture],name,&model.bmp[current_texture]);
	strcpy(model.texname[current_texture],name);
}

void change_texture_name()
{
	GLTextBoxFunc("New Texture Name for Current Texture",CALLBACKchange_texture_name);
}
void CALLBACKchange_texture_name(const char *name)
{
	strcpy(model.texname[current_texture],name);
}
