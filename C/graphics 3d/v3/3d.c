#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "BMP.h"

#define TEX_MAX 10

int WIDTH=700;
int HEIGHT=700;

/* Structure Definition */
typedef struct Vertex
{
	GLfloat x,y,z;
	GLfloat X,Y;
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
typedef struct Object
{
	int texn;	
	char texname[TEX_MAX][50];
	GLuint tex[TEX_MAX];	
	BMP bmp[TEX_MAX];
	int vn,tn,qn;
	Vertex v[300];
	Triangle t[300];
	Quad q[300];
}Object;

/* Function Prototypes */
void display(void);												/* GLUT display function */
void reshape(int width, int height);							/* GLUT reshape function */
enum KEY_MODE{NORMAL,SHIFT,CTRL,ALT};
int KEY_MODE=NORMAL;
void mouse(int button, int state,int x, int y);					/* GLUT mouse function */
void keyboard(unsigned char key,int x, int y);					/* GLUT keyboard function */
void special_keyboard(int key,int x, int y);
void motion(int x, int y);										/* GLUT motion function */
void passivemotion(int x, int y);								/* GLUT passive motion function */
GLfloat texx,texy,winx,winy,winz;
void get_mouse_position(int x,int y,GLfloat *texx,GLfloat *texy,GLfloat *winx,GLfloat *winy,GLfloat *winz);

void delete_vertex();
void delete_triangle();
void delete_quad();
void delete_isolated_vertices();
void add_texture();
void delete_texture();
void change_texture();
void MakeObject();
void Print();
void LoadTexture(GLuint *texture,const char *name,BMP *image_return);
void SaveObject(const char* name);
void LoadObject(const char* name);

char filename[50]="\0";
GLfloat angle_x=0,angle_y=0,angle_z=0;
Object obj;
int count=0,new_vertex_count=0;
int v[4];
enum mode{WIRE,SOLID,DRAW};
int mode=DRAW;
int tex_index=0;
int selected_vertex=-1,selected_triangle=-1,selected_quad=-1;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize (WIDTH,HEIGHT);
	glutInitWindowPosition (0,0);
	glutCreateWindow ("3d");

	if(argc>=2)
	{
		strcpy(filename,argv[1]);
		LoadObject(argv[1]);
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
	int i;

	system("cls");
	printf("%f,%f,%f\n\n\n",angle_x,angle_y,angle_z);

	for(i=0;i<obj.texn;i++)
		printf("%c \"%s\"\n",(mode==DRAW&&i==tex_index)?'*':' ',obj.texname[i]);
	printf("\n%s\t",(mode==DRAW)?"Draw":(mode==SOLID)?"Solid":"Wire");
	printf("vertices=%d,triangles=%d,quads=%d\n\n",obj.vn,obj.tn,obj.qn);

	if(selected_vertex==-1 && selected_triangle==-1 && selected_quad==-1)
		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	else
		glutSetCursor(GLUT_CURSOR_CROSSHAIR);		

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1.0f);
	glClearColor(0.0,0.0,0.0,0.0);

	glEnable(GL_DEPTH_TEST);
	Print();
	glDisable(GL_DEPTH_TEST);

	glutPostRedisplay();
	glutSwapBuffers();
}


void Print()
{
	int i,j,k;
	
	if(mode==DRAW)
	{
		if(selected_vertex!=-1)
		{
			glLoadIdentity();
			glRotatef(angle_x,1,0,0);
			glRotatef(angle_y,0,1,0);
			glRotatef(angle_z,0,0,1);			
			glTranslatef(obj.v[selected_vertex].x,obj.v[selected_vertex].y,obj.v[selected_vertex].z);
			glColor4f(0,1,0,1);
			glutSolidSphere(.01,5,5);
		}

		if(count>0)
		{
			for(i=0;i<count;i++)
			{
				glLoadIdentity();
				glRotatef(angle_x,1,0,0);
				glRotatef(angle_y,0,1,0);
				glRotatef(angle_z,0,0,1);				
				glTranslatef(obj.v[v[i]].x,obj.v[v[i]].y,obj.v[v[i]].z);
				glColor4f(1-(GLfloat)i/3,0,(GLfloat)i/3,1);
				glutSolidSphere(.01,5,5);
			}
		}

		glLoadIdentity();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,obj.tex[tex_index]);

		glColor3f(.1,.1,.1);
		glBegin(GL_QUADS);
		glTexCoord2f(0,0);		glVertex3f(-1, 1, .99);
		glTexCoord2f(1,0);		glVertex3f( 1, 1, .99);
		glTexCoord2f(1,1);		glVertex3f( 1,-1, .99);
		glTexCoord2f(0,1);		glVertex3f(-1,-1, .99);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}	
	
	if(mode==DRAW || mode==SOLID)
	{
		glLoadIdentity();
		glRotatef(angle_x,1,0,0);
		glRotatef(angle_y,0,1,0);
		glRotatef(angle_z,0,0,1);
		glEnable(GL_TEXTURE_2D);
		for(k=0;k<obj.texn;k++)
		{		
			glBindTexture(GL_TEXTURE_2D,obj.tex[k]);			
			glBegin(GL_TRIANGLES);
			for(i=0;i<obj.tn;i++)
			{
				if(mode==DRAW && selected_triangle==i) glColor3f(0,1,0);
				else glColor3f(1,1,1);
				if(obj.t[i].tex==k)
				{
					for(j=0;j<3;j++)
					{
						glTexCoord2f(obj.v[obj.t[i].v[j]].X,obj.v[obj.t[i].v[j]].Y);
						glVertex3f(obj.v[obj.t[i].v[j]].x,obj.v[obj.t[i].v[j]].y,obj.v[obj.t[i].v[j]].z);
					}
				}
			}
			glEnd();
			glBegin(GL_QUADS);
			for(i=0;i<obj.qn;i++)
			{
				if(mode==DRAW && selected_quad==i) glColor3f(0,1,0);
				else glColor3f(1,1,1);
				if(obj.q[i].tex==k)
				{
					for(j=0;j<4;j++)
					{
						glTexCoord2f(obj.v[obj.q[i].v[j]].X,obj.v[obj.q[i].v[j]].Y);
						glVertex3f(obj.v[obj.q[i].v[j]].x,obj.v[obj.q[i].v[j]].y,obj.v[obj.q[i].v[j]].z);
					}
				}
			}
			glEnd();
		}		
		glDisable(GL_TEXTURE_2D);
	}
	
	if(mode==DRAW || mode==WIRE)
	{
		glLoadIdentity();
		glRotatef(angle_x,1,0,0);
		glRotatef(angle_y,0,1,0);
		glRotatef(angle_z,0,0,1);
		glBegin(GL_LINES);
		for(i=0;i<obj.qn;i++)
		{
			if(mode==DRAW && obj.q[i].tex==tex_index) glColor3f(1,0,0);
			else glColor3f(1,1,1);
			for(j=0;j<4;j++)
			{
				glVertex3f(obj.v[obj.q[i].v[j]].x,obj.v[obj.q[i].v[j]].y,obj.v[obj.q[i].v[j]].z);
				glVertex3f(obj.v[obj.q[i].v[(j+1)%4]].x,obj.v[obj.q[i].v[(j+1)%4]].y,obj.v[obj.q[i].v[(j+1)%4]].z);
			}
		}
		for(i=0;i<obj.tn;i++)
		{
			if(mode==DRAW && obj.t[i].tex==tex_index) glColor3f(1,0,0);
			else glColor3f(1,1,1);
			for(j=0;j<3;j++)
			{
				glVertex3f(obj.v[obj.t[i].v[j]].x,obj.v[obj.t[i].v[j]].y,obj.v[obj.t[i].v[j]].z);
				glVertex3f(obj.v[obj.t[i].v[(j+1)%3]].x,obj.v[obj.t[i].v[(j+1)%3]].y,obj.v[obj.t[i].v[(j+1)%3]].z);
			}
		}
		glEnd();
		glColor3f(1,1,0);
		glBegin(GL_POINTS);
		for(i=0;i<obj.vn;i++)
			glVertex3f(obj.v[i].x,obj.v[i].y,obj.v[i].z);
		glEnd();
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
	int i;
	get_mouse_position(x,y,&texx,&texy,&winx,&winy,&winz);
	if(glutGetModifiers()==GLUT_ACTIVE_SHIFT) KEY_MODE=SHIFT;
	else if(glutGetModifiers()==GLUT_ACTIVE_CTRL) KEY_MODE=CTRL;
	else if(glutGetModifiers()==GLUT_ACTIVE_ALT) KEY_MODE=ALT;
	else KEY_MODE=NORMAL;
	switch(button)
	{
		case GLUT_LEFT_BUTTON:	
			if(count<4 && state==GLUT_DOWN)
			{
				new_vertex_count++;
				obj.v[obj.vn].x=winx; 
				obj.v[obj.vn].y=winy; 
				obj.v[obj.vn].z=0;
				obj.v[obj.vn].X=texx; 
				obj.v[obj.vn].Y=texy;
				v[count]=obj.vn;
				for(i=0;i<obj.vn;i++)
					if(obj.v[i].x<=winx+.01 && obj.v[i].x>=winx-.01
						&& obj.v[i].y<=winy+.01 && obj.v[i].y>=winy-.01)
						{
						v[count]=i;
						obj.vn--;
						new_vertex_count--;
						break;
					}
				obj.vn++;
				count++;
			}
			break;
		case GLUT_RIGHT_BUTTON:
			if(count==3)
			{
				obj.t[obj.tn].v[2]=v[2];
				obj.t[obj.tn].v[1]=v[1];
				obj.t[obj.tn].v[0]=v[0];
				obj.t[obj.tn].tex=tex_index;
				obj.tn++;
				count=0;
				new_vertex_count=0;
			}			
			else if(count==4)
			{
				obj.q[obj.qn].v[3]=v[3];
				obj.q[obj.qn].v[2]=v[2];
				obj.q[obj.qn].v[1]=v[1];
				obj.q[obj.qn].v[0]=v[0];
				obj.q[obj.qn].tex=tex_index;
				obj.qn++;
				count=0;
				new_vertex_count=0;
			}	
			else
			{
				obj.vn-=new_vertex_count;
				count=0;
				new_vertex_count=0;
			}
			break;
		case GLUT_MIDDLE_BUTTON:
			obj.vn-=new_vertex_count;
			count=0;
			new_vertex_count=0;
			break;
	}
}

void keyboard(unsigned char key,int x, int y)
{
	texx=(GLfloat)x/(GLfloat)WIDTH;
	texy=(GLfloat)y/(GLfloat)HEIGHT;
	winx=2*(GLfloat)x/(GLfloat)WIDTH-1;
	winy=1-2*(GLfloat)y/(GLfloat)HEIGHT;
	switch(key)
	{		
		case '\t':		//Change Texture
			tex_index=(tex_index+1)%obj.texn;
			break;
		case ' ':		// Change Mode
			if(mode==DRAW) mode=SOLID;
			else if(mode==SOLID) mode=WIRE;
			else mode=DRAW;
			break;	
		case '=':		//Elevate
			if(selected_vertex!=-1)
				obj.v[selected_vertex].z-=.01;
			break;
		case '-':
			if(selected_vertex!=-1)
				obj.v[selected_vertex].z+=.01;
			break;			
		case 127:		//Delete
			obj.vn-=new_vertex_count;
			count=new_vertex_count=0;
			delete_vertex();
			delete_triangle();
			delete_quad();
			break;
		case 27:		//Exit
			exit(0);
		case 'a':	//Add Texture 
			add_texture();
			break;
		case 'c':	//Change Texture 
			change_texture();
			break;
		case 'd':	//Delete Texture 
			delete_texture();
			break;
		case 's':	//Save
			if(strlen(filename)==0)
			{
				printf("SAVE:\nFilename : ");
				scanf("%s",filename);
			}
			SaveObject(filename);
			break;
		case 'l':	//Load
			printf("LOAD:\nFilename : ");
			scanf("%s",filename);
			LoadObject(filename);
			break;	
		case 'r':	//Reload
			if(strlen(filename)!=0)
				LoadObject(filename);
			break;
	}
}

void special_keyboard(int key,int x, int y)
{
	texx=(GLfloat)x/(GLfloat)WIDTH,texy=(GLfloat)y/(GLfloat)HEIGHT;
	switch(key)
	{
		case GLUT_KEY_F12:	//Clear
			obj.vn=obj.tn=obj.qn=count=new_vertex_count=0;
			break;
		case GLUT_KEY_UP:		//Rotation
			angle_x-=4;
			break;
		case GLUT_KEY_DOWN:
			angle_x+=4;
			break;
		case GLUT_KEY_LEFT:
			angle_y-=4;
			break;
		case GLUT_KEY_RIGHT:
			angle_y+=4;
			break;
		case GLUT_KEY_PAGE_UP:
			angle_z+=4;
			break;
		case GLUT_KEY_PAGE_DOWN:
			angle_z-=4;
			break;
		case GLUT_KEY_HOME:		//Front view
			angle_x=angle_y=angle_z=0;
			break;
		case GLUT_KEY_END:		//Back view
			angle_y=180;
			angle_x=angle_z=0;
			break;
	}
}

void passivemotion(int x, int y)
{
	int i;
	get_mouse_position(x,y,&texx,&texy,&winx,&winy,&winz);
	selected_vertex=-1;
	for(i=0;i<obj.vn;i++)
		if(	obj.v[i].x<=winx+.01 && 
			obj.v[i].x>=winx-.01 && 
			obj.v[i].y<=winy+.01 && 
			obj.v[i].y>=winy-.01 )
		{
			selected_vertex=i;
			break;
		}
	selected_triangle=-1;
	for(i=0;i<obj.tn;i++)
		if(	(obj.v[obj.t[i].v[0]].x+obj.v[obj.t[i].v[1]].x+obj.v[obj.t[i].v[2]].x)/3<=winx+.02 &&
			(obj.v[obj.t[i].v[0]].x+obj.v[obj.t[i].v[1]].x+obj.v[obj.t[i].v[2]].x)/3>=winx-.02 &&
			(obj.v[obj.t[i].v[0]].y+obj.v[obj.t[i].v[1]].y+obj.v[obj.t[i].v[2]].y)/3<=winy+.02 &&
			(obj.v[obj.t[i].v[0]].y+obj.v[obj.t[i].v[1]].y+obj.v[obj.t[i].v[2]].y)/3>=winy-.02)
		{
			selected_triangle=i;
			break;
		}
	selected_quad=-1;
	for(i=0;i<obj.qn;i++)
		if(	(obj.v[obj.q[i].v[0]].x+obj.v[obj.q[i].v[1]].x+obj.v[obj.q[i].v[2]].x+obj.v[obj.q[i].v[3]].x)/4<=winx+.02 &&
			(obj.v[obj.q[i].v[0]].x+obj.v[obj.q[i].v[1]].x+obj.v[obj.q[i].v[2]].x+obj.v[obj.q[i].v[3]].x)/4>=winx-.02 &&
			(obj.v[obj.q[i].v[0]].y+obj.v[obj.q[i].v[1]].y+obj.v[obj.q[i].v[2]].y+obj.v[obj.q[i].v[3]].y)/4<=winy+.02 &&
			(obj.v[obj.q[i].v[0]].y+obj.v[obj.q[i].v[1]].y+obj.v[obj.q[i].v[2]].y+obj.v[obj.q[i].v[3]].y)/4>=winy-.02)
		{
			selected_quad=i;
			break;
		}
}

void motion(int x, int y)
{
	int i;
	GLfloat new_texx,new_texy,new_winx,new_winy,new_winz;
	get_mouse_position(x,y,&new_texx,&new_texy,&new_winx,&new_winy,&new_winz);
	if(selected_vertex!=-1)
	{
		obj.vn-=new_vertex_count;
		count=new_vertex_count=0;
		if(KEY_MODE!=CTRL)
		{
			obj.v[selected_vertex].x+=(new_winx-winx);
			obj.v[selected_vertex].y+=(new_winy-winy);
		}
		if(KEY_MODE!=SHIFT)
		{
			obj.v[selected_vertex].X+=(new_texx-texx);
			obj.v[selected_vertex].Y+=(new_texy-texy);
		}
	}
	else if(selected_triangle!=-1)
	{
		obj.vn-=new_vertex_count;
		count=new_vertex_count=0;
		for(i=0;i<3;i++)
		{
			if(KEY_MODE!=CTRL)
			{
				obj.v[obj.t[selected_triangle].v[i]].x+=(new_winx-winx);
				obj.v[obj.t[selected_triangle].v[i]].y+=(new_winy-winy);
			}
			if(KEY_MODE!=SHIFT)
			{
				obj.v[obj.t[selected_triangle].v[i]].X+=(new_texx-texx);
				obj.v[obj.t[selected_triangle].v[i]].Y+=(new_texy-texy);
			}
		}
	}
	else if(selected_quad!=-1)
	{
		obj.vn-=new_vertex_count;
		count=new_vertex_count=0;
		for(i=0;i<4;i++)
		{
			if(KEY_MODE!=CTRL)
			{
				obj.v[obj.q[selected_quad].v[i]].x+=(new_winx-winx);
				obj.v[obj.q[selected_quad].v[i]].y+=(new_winy-winy);
			}
			if(KEY_MODE!=SHIFT)
			{
				obj.v[obj.q[selected_quad].v[i]].X+=(new_texx-texx);
				obj.v[obj.q[selected_quad].v[i]].Y+=(new_texy-texy);
			}
		}
	}
	texx=new_texx,texy=new_texy;
	winx=new_winx,winy=new_winy,winz=new_winz;
}

void get_mouse_position(int x,int y,GLfloat *texx,GLfloat *texy,GLfloat *winx,GLfloat *winy,GLfloat *winz)
{
	GLfloat tx,ty,tz;
	*texx=(GLfloat)x/(GLfloat)WIDTH;
	*texy=(GLfloat)y/(GLfloat)HEIGHT;
	tx=*texx,ty=*texy;
	*texx= tx*cos(angle_z*3.141592654/180)+ty*sin(angle_z*3.141592654/180);
	*texy=-tx*sin(angle_z*3.141592654/180)+ty*cos(angle_z*3.141592654/180);
	tx=*texx,ty=*texy;
	*texy= ty*cos(angle_x*3.141592654/180);
	tx=*texx,ty=*texy;
	*texx= tx*cos(angle_y*3.141592654/180);
	
	*winx=2*(GLfloat)x/(GLfloat)WIDTH-1;
	*winy=1-2*(GLfloat)y/(GLfloat)HEIGHT;
	*winz=0;
	tx=*winx,ty=*winy,tz=*winz;
	*winx= tx*cos(angle_z*3.141592654/180)+ty*sin(angle_z*3.141592654/180);
	*winy=-tx*sin(angle_z*3.141592654/180)+ty*cos(angle_z*3.141592654/180);
	tx=*winx,ty=*winy,tz=*winz;
	*winy= ty*cos(angle_x*3.141592654/180)+tz*sin(angle_x*3.141592654/180);
	*winz=-ty*sin(angle_x*3.141592654/180)+tz*cos(angle_x*3.141592654/180);
	tx=*winx,ty=*winy,tz=*winz;
	*winz= tz*cos(angle_y*3.141592654/180)+tx*sin(angle_y*3.141592654/180);
	*winx=-tz*sin(angle_y*3.141592654/180)+tx*cos(angle_y*3.141592654/180);
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

void SaveObject(const char* name)
{
	FILE *fp;
	int i;

	if((fp=fopen(name,"wb"))==NULL)
	{
		fprintf(stderr,"save error\n");
		return;
	}
	
	fwrite(&obj.texn,sizeof(int),1,fp);
	for(i=0;i<obj.texn;i++)
	{
		fwrite(obj.texname[i],sizeof(char),50,fp);
		fwrite(&obj.bmp[i].width,sizeof(unsigned long),1,fp);
		fwrite(&obj.bmp[i].height,sizeof(unsigned long),1,fp);
		fwrite(obj.bmp[i].data,sizeof(unsigned char),obj.bmp[i].height*obj.bmp[i].width*3,fp);
	}
	fwrite(&obj.vn,sizeof(int),1,fp);
	fwrite(obj.v,sizeof(Vertex),obj.vn,fp);
	fwrite(&obj.tn,sizeof(int),1,fp);
	fwrite(obj.t,sizeof(Triangle),obj.tn,fp);
	fwrite(&obj.qn,sizeof(int),1,fp);
	fwrite(obj.q,sizeof(Quad),obj.qn,fp);

	fclose(fp);
}

void LoadObject(const char* name)
{
	FILE *fp;
	int i;
	if((fp=fopen(name,"rb"))==NULL)
	{
		fprintf(stderr,"load error\n");
		return;
	}
	
	fread(&obj.texn,sizeof(int),1,fp);
	for(i=0;i<obj.texn;i++)
	{
		fread(obj.texname[i],sizeof(char),50,fp);
		fread(&obj.bmp[i].width,sizeof(unsigned long),1,fp);
		fread(&obj.bmp[i].height,sizeof(unsigned long),1,fp);
		obj.bmp[i].data=(unsigned char*)calloc(sizeof(unsigned char),obj.bmp[i].height*obj.bmp[i].width*3);
		fread(obj.bmp[i].data,sizeof(unsigned char),obj.bmp[i].height*obj.bmp[i].width*3,fp);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glGenTextures(1,&obj.tex[i]);
		glBindTexture(GL_TEXTURE_2D,obj.tex[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,obj.bmp[i].width,obj.bmp[i].height,0,GL_RGB,GL_UNSIGNED_BYTE,obj.bmp[i].data);
	}
	fread(&obj.vn,sizeof(int),1,fp);
	fread(obj.v,sizeof(Vertex),obj.vn,fp);
	fread(&obj.tn,sizeof(int),1,fp);
	fread(obj.t,sizeof(Triangle),obj.tn,fp);
	fread(&obj.qn,sizeof(int),1,fp);
	fread(obj.q,sizeof(Quad),obj.qn,fp);

	fclose(fp);
}

void delete_vertex()
{
	int j;
	if(selected_vertex==-1) return;

	//Deleteing adjacent triangles
	for(j=0;j<obj.tn;)
	{
		if(obj.t[j].v[0]==selected_vertex || obj.t[j].v[1]==selected_vertex || obj.t[j].v[2]==selected_vertex)
		{
			memmove(&obj.t[j],&obj.t[j+1],(obj.tn-j)*sizeof(Triangle));
			obj.tn--;
		}
		else
		{
			if(obj.t[j].v[0]>selected_vertex) obj.t[j].v[0]--;
			if(obj.t[j].v[1]>selected_vertex) obj.t[j].v[1]--;
			if(obj.t[j].v[2]>selected_vertex) obj.t[j].v[2]--;
			j++;
		}
	}
	//Deleteing adjacent quads
	for(j=0;j<obj.qn;)
	{	
		if(obj.q[j].v[0]==selected_vertex || obj.q[j].v[1]==selected_vertex || obj.q[j].v[2]==selected_vertex || obj.q[j].v[3]==selected_vertex)
		{
			memmove(&obj.q[j],&obj.q[j+1],(obj.qn-j)*sizeof(Quad));
			obj.qn--;
		}
		else
		{
			if(obj.q[j].v[0]>selected_vertex) obj.q[j].v[0]--;
			if(obj.q[j].v[1]>selected_vertex) obj.q[j].v[1]--;
			if(obj.q[j].v[2]>selected_vertex) obj.q[j].v[2]--;
			if(obj.q[j].v[3]>selected_vertex) obj.q[j].v[3]--;
			j++;
		}
	} 
	//Deleteing vertex
	memmove(&obj.v[selected_vertex],&obj.v[selected_vertex+1],(obj.vn-selected_vertex)*sizeof(Vertex));
	obj.vn--;

	delete_isolated_vertices();

	selected_vertex=-1;
}

void delete_triangle()
{
	if(selected_triangle==-1) return;

	memmove(&obj.t[selected_triangle],&obj.t[selected_triangle+1],(obj.tn-selected_triangle)*sizeof(Triangle));
		obj.tn--;

	delete_isolated_vertices();

	selected_triangle=-1;
}

void delete_quad()
{
	if(selected_quad==-1) return;

	memmove(&obj.q[selected_quad],&obj.q[selected_quad+1],(obj.qn-selected_quad)*sizeof(Quad));
		obj.qn--;

	delete_isolated_vertices();

	selected_quad=-1;
}

void delete_isolated_vertices()
{
	int i,j,flag;
	for(i=0;i<obj.vn;)
	{
		flag=0;
		for(j=0;flag==0 && j<=obj.tn;j++)
			if(obj.t[j].v[0]==i || obj.t[j].v[1]==i || obj.t[j].v[2]==i)
			{
				flag=1;
				break;
			}
		for(j=0;flag==0 && j<=obj.qn;j++)
			if(obj.q[j].v[0]==i || obj.q[j].v[1]==i || obj.q[j].v[2]==i || obj.q[j].v[3]==i)
			{
				flag=1;
				break;
			}
		if(flag==0)
		{
			for(j=0;flag==0 && j<obj.tn;j++)
			{
				if(obj.t[j].v[0]>i) obj.t[j].v[0]--;
				if(obj.t[j].v[1]>i) obj.t[j].v[1]--;
				if(obj.t[j].v[2]>i) obj.t[j].v[2]--;
			}
			for(j=0;flag==0 && j<obj.qn;j++)
			{
				if(obj.q[j].v[0]>i) obj.q[j].v[0]--;
				if(obj.q[j].v[1]>i) obj.q[j].v[1]--;
				if(obj.q[j].v[2]>i) obj.q[j].v[2]--;
				if(obj.q[j].v[3]>i) obj.q[j].v[3]--;
			}
			memmove(&obj.v[i],&obj.v[i+1],(obj.vn-i)*sizeof(Vertex));
			obj.vn--;
		}
		else
			i++;
	}
}

void add_texture()
{
	char str[50];
	printf("\nADD TEXTURE:\nTexture file name : ");
	scanf("%s",str);
	LoadTexture(&obj.tex[obj.texn],str,&obj.bmp[obj.texn]);
	printf("Texture name : ");
	scanf("%s",obj.texname[obj.texn]);
	obj.texn++;
}

void delete_texture()
{
	int i,j;
	char str[50];
	printf("\nDELETE TEXTURE:\nTexture name : ");
	scanf("%s",&str);
	for(i=0;i<obj.texn;i++)
		if(strcmp(str,obj.texname[i])==0)
			break;
	if(i<obj.texn)
	{
		for(j=0;j<obj.tn;)
			if(obj.t[j].tex==i)
			{
				memmove(&obj.t[j],&obj.t[j+1],(obj.tn-j)*sizeof(Triangle));
				obj.tn--;
			}
			else j++;
		for(j=0;j<obj.qn;)
			if(obj.q[j].tex==i)
			{
				memmove(&obj.q[j],&obj.q[j+1],(obj.qn-j)*sizeof(Quad));
				obj.qn--;
			}
			else j++;
		delete_isolated_vertices();
		memmove(&obj.texname[i],&obj.texname[i+1],(obj.texn-i)*sizeof(char)*50);
		memmove(&obj.tex[i],&obj.tex[i+1],(obj.texn-i)*sizeof(GLuint));
		memmove(&obj.bmp[i],&obj.bmp[i+1],(obj.texn-i)*sizeof(BMP));
		obj.texn--;
	}
	else
		fprintf(stderr,"\nNo such texture");
}

void change_texture()
{
	int i;
	char str[50];
	printf("\nCHANGE TEXTURE:\nOld texture name : ");
	scanf("%s",&str);
	for(i=0;i<obj.texn;i++)
		if(strcmp(str,obj.texname[i])==0)
			break;
	if(i<obj.texn)
	{
		printf("New texture file name : ");
		scanf("%s",str);
		LoadTexture(&obj.tex[i],str,&obj.bmp[i]);
		printf("Texture name : ");
		scanf("%s",obj.texname[i]);
	}
	else
		fprintf(stderr,"\nNo such texture");
}