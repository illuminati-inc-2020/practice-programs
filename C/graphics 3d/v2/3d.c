#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "BMP.h"

int WIDTH=500;
int HEIGHT=500;

/* Structure Definition */
typedef struct Vertex
{
	GLfloat x,y,z;
	GLfloat X,Y;
}Vertex;
typedef struct Triangle
{
	Vertex *v[3];
	GLuint *tex;
}Triangle;
typedef struct Quad
{
	Vertex *v[4];
	GLuint *tex;
}Quad;

typedef struct Object
{
	char fname[50],bname[50];
	GLuint front,back;
	int vn,tn,qn;
	Vertex v[100];
	Triangle t[100];
	Quad q[1000];
}Object;

/* Function Prototypes */
void display(void);												/* GLUT display function */
void reshape(int width, int height);							/* GLUT reshape function */
void mouse(int button, int state,int x, int y);					/* GLUT mouse function */
void keyboard(unsigned char key,int x, int y);					/* GLUT keyboard function */
void special_keyboard(int key,int x, int y);
void motion(int x, int y);										/* GLUT motion function */
void passivemotion(int x, int y);								/* GLUT passive motion function */
int button_pressed[3]={0,0,0};
GLfloat mousex,mousey;;

void delete_vertex();
void elevate(GLfloat value);
void MakeObject();
void PrintObject(GLfloat size);
void PrintPoint();
void LoadTexture(GLuint *texture,const char *name);
void SaveObject();
void LoadObject();

GLfloat angle_x=0,angle_y=0,angle_z=0;
Object obj;
int count=0,new_vertex_count=0;
Vertex *v[4];
enum mode{FRONT,BACK,WIRE,SOLID,DRAW};
int mode=FRONT,mode2=DRAW;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize (WIDTH,HEIGHT);
	glutInitWindowPosition (0,0);
	glutCreateWindow ("3d");

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
	system("cls");
	printf("\"%s\" : \"%s\"\n",obj.fname,obj.bname);
	printf("%s\t",(mode2==DRAW)?"Draw":(mode2==SOLID)?"Solid":"Wire");
	if(mode2==DRAW)
		printf("%s\t",(mode==FRONT)?"Front":"Back");
	printf("vertices=%d,triangles=%d,quads=%d\n\n",obj.vn,obj.tn,obj.qn);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1.0f);
	glClearColor(0.0,0.0,0.0,0.0);

	if(mode2!=DRAW)
		glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	glRotatef(angle_x,1,0,0);
	glRotatef(angle_y,0,1,0);
	glRotatef(angle_z,0,0,1);
	PrintObject(1);
	PrintPoint();
	if(mode2!=DRAW)
		glDisable(GL_DEPTH_TEST);

	glutPostRedisplay();
	glutSwapBuffers();
}

void MakeObject()
{
	printf("\nEnter front texture file name : ");
	scanf("%s",obj.fname);
	LoadTexture(&obj.front,obj.fname);
	printf("\nEnter back texture file name : ");
	scanf("%s",obj.bname);
	LoadTexture(&obj.back,obj.bname);
	obj.vn=0;
	obj.tn=0;
	obj.qn=0;
}

void LoadTexture(GLuint *texture,const char *name)
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

void PrintObject(GLfloat size)
{
	int i,j;
	glEnable(GL_TEXTURE_2D);
	if((mode==FRONT && mode2==DRAW) || mode2==SOLID)
	{		
		glBindTexture(GL_TEXTURE_2D,obj.front);
		if(mode2==DRAW)
		{
			glColor3f(.1,.1,.1);
			glBegin(GL_QUADS);
			glTexCoord2f(0,0);		glVertex3f(-1, 1, 0);
			glTexCoord2f(1,0);		glVertex3f( 1, 1, 0);
			glTexCoord2f(1,1);		glVertex3f( 1,-1, 0);
			glTexCoord2f(0,1);		glVertex3f(-1,-1, 0);
			glEnd();
		}
		glColor3f(1,1,1);
		glBegin(GL_TRIANGLES);
		for(i=0;i<obj.tn;i++)
		{
			if(obj.t[i].tex==&obj.front)
			for(j=0;j<3;j++)
			{
				glTexCoord2f(obj.t[i].v[j]->X,obj.t[i].v[j]->Y);
				glVertex3f(obj.t[i].v[j]->x,obj.t[i].v[j]->y,obj.t[i].v[j]->z);
			}
		}
		glEnd();
		glBegin(GL_QUADS);
		for(i=0;i<obj.qn;i++)
		{
			if(obj.q[i].tex==&obj.front)
			for(j=0;j<4;j++)
			{
				glTexCoord2f(obj.q[i].v[j]->X,obj.q[i].v[j]->Y);
				glVertex3f(obj.q[i].v[j]->x,obj.q[i].v[j]->y,obj.q[i].v[j]->z);
			}
		}
		glEnd();
	}
	if((mode==BACK && mode2==DRAW) || mode2==SOLID)
	{
		glBindTexture(GL_TEXTURE_2D,obj.back);
		if(mode2==DRAW)
		{
			glColor3f(.1,.1,.1);
			glBegin(GL_QUADS);
			glTexCoord2f(0,0);		glVertex3f(-1, 1, 0);
			glTexCoord2f(1,0);		glVertex3f( 1, 1, 0);
			glTexCoord2f(1,1);		glVertex3f( 1,-1, 0);
			glTexCoord2f(0,1);		glVertex3f(-1,-1, 0);
			glEnd();
		}
		glColor3f(1,1,1);
		glBegin(GL_TRIANGLES);
		for(i=0;i<obj.tn;i++)
		{
			if(obj.t[i].tex==&obj.back)
			for(j=0;j<3;j++)
			{
				glTexCoord2f(obj.t[i].v[j]->X,obj.t[i].v[j]->Y);
				glVertex3f(obj.t[i].v[j]->x,obj.t[i].v[j]->y,obj.t[i].v[j]->z);
			}
		}
		glEnd();
		glBegin(GL_QUADS);
		for(i=0;i<obj.qn;i++)
		{
			if(obj.q[i].tex==&obj.back)
			for(j=0;j<4;j++)
			{
				glTexCoord2f(obj.q[i].v[j]->X,obj.q[i].v[j]->Y);
				glVertex3f(obj.q[i].v[j]->x,obj.q[i].v[j]->y,obj.q[i].v[j]->z);
			}
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}

void PrintPoint()
{
	int i,j;
	if(mode2==SOLID)
		return;
	glBegin(GL_LINES);
	for(i=0;i<obj.qn;i++)
	{
		if(obj.q[i].tex==&obj.front) glColor3f(1,0,0);
		else glColor3f(0,1,0);
		for(j=0;j<4;j++)
		{
			glVertex3f(obj.q[i].v[j]->x,obj.q[i].v[j]->y,obj.q[i].v[j]->z);
			glVertex3f(obj.q[i].v[(j+1)%4]->x,obj.q[i].v[(j+1)%4]->y,obj.q[i].v[(j+1)%4]->z);
		}
	}
	for(i=0;i<obj.tn;i++)
	{
		if(obj.t[i].tex==&obj.front) glColor3f(1,0,0);
		else glColor3f(0,1,0);
		for(j=0;j<3;j++)
		{
			glVertex3f(obj.t[i].v[j]->x,obj.t[i].v[j]->y,obj.t[i].v[j]->z);
			glVertex3f(obj.t[i].v[(j+1)%3]->x,obj.t[i].v[(j+1)%3]->y,obj.t[i].v[(j+1)%3]->z);
		}
	}
	glEnd();
	glColor3f(1,1,0);
	glBegin(GL_POINTS);
	for(i=0;i<obj.vn;i++)
		glVertex3f(obj.v[i].x,obj.v[i].y,obj.v[i].z);
	glEnd();
}

void reshape(int width, int height)
{
	glViewport(0,0,width,height);
	WIDTH=width;
	HEIGHT=height;
	//glutReshapeWindow(WIDTH,HEIGHT);
}

void mouse(int button, int state,int x, int y)
{
	int i;
	switch(button)
	{
		case GLUT_LEFT_BUTTON:
			button_pressed[0]=!button_pressed[0];	
			mousex=(GLfloat)x/(GLfloat)WIDTH,mousey=(GLfloat)y/(GLfloat)HEIGHT;
			break;
		case GLUT_RIGHT_BUTTON:
			button_pressed[2]=!button_pressed[2];
			mousex=(GLfloat)x/(GLfloat)WIDTH,mousey=(GLfloat)y/(GLfloat)HEIGHT;
			break;
	}
	
	if(button_pressed[0]) 
	{
		new_vertex_count++;
		obj.v[obj.vn].x=mousex*2-1; 
		obj.v[obj.vn].y=1-mousey*2; 
		obj.v[obj.vn].z=0;
		obj.v[obj.vn].X=mousex; 
		obj.v[obj.vn].Y=mousey;
		v[count]=&obj.v[obj.vn];
		for(i=0;i<obj.vn;i++)
			if(obj.v[i].x<=mousex*2-1+.01 && obj.v[i].x>=mousex*2-1-.01
				&& obj.v[i].y<=1-mousey*2+.01 && obj.v[i].y>=1-mousey*2-.01)
			{
				v[count]=&obj.v[i];
				obj.vn--;
				new_vertex_count--;
				break;
			}
		obj.vn++;
		count++;
	}
	if(count==3 && button_pressed[2])
	{
		obj.t[obj.tn].v[2]=v[2];
		obj.t[obj.tn].v[1]=v[1];
		obj.t[obj.tn].v[0]=v[0];
		obj.t[obj.tn].tex=(mode==FRONT)?&obj.front:&obj.back;
		obj.tn++;
		count=0;
		new_vertex_count=0;
	}
	if(count==4 && button_pressed[2])
	{
		obj.q[obj.qn].v[3]=v[3];
		obj.q[obj.qn].v[2]=v[2];
		obj.q[obj.qn].v[1]=v[1];
		obj.q[obj.qn].v[0]=v[0];
		obj.q[obj.qn].tex=(mode==FRONT)?&obj.front:&obj.back;
		obj.qn++;
		count=0;
		new_vertex_count=0;
	}
	if(count>4 || (count<=2 && button_pressed[2]))
	{
		obj.vn-=new_vertex_count;
		count=0;
		new_vertex_count=0;
	}
}

void keyboard(unsigned char key,int x, int y)
{
	mousex=(GLfloat)x/(GLfloat)WIDTH,mousey=(GLfloat)y/(GLfloat)HEIGHT;
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
		case 'c':						// Clear
			obj.vn=obj.tn=obj.qn=0;
			count=new_vertex_count=0;
			break;
		case 'd':						// Delete Vertex
			obj.vn-=new_vertex_count;
			count=0;
			new_vertex_count=0;
			delete_vertex();
			break;
		case '=':
			elevate(-0.01);
			break;
		case '-':
			elevate( 0.01);
			break;
		case '\t':
			mode=!mode;
			break;
		case 'm':
			if(mode2==DRAW) mode2=SOLID;
			else if(mode2==SOLID) mode2=WIRE;
			else mode2=DRAW;
			break;
		case 's':
			SaveObject();
			break;
		case 'l':
			LoadObject();
			break;
		case 'n':
			MakeObject();
			break;
		case 'f':
			printf("\nEnter front texture file name : ");
			scanf("%s",obj.fname);
			LoadTexture(&obj.front,obj.fname);
			break;
		case 'b':
			printf("\nEnter back texture file name : ");
			scanf("%s",obj.bname);
			LoadTexture(&obj.back,obj.bname);
			break;
		case 'q':
			exit(0);
	}
}

void SaveObject()
{
	FILE *fp;
	int i,j,temp;
	if((fp=fopen("output","wb"))==NULL)
	{
		fprintf(stderr,"save error\n");
		exit(0);
	}
	
	fwrite(obj.fname,sizeof(char),50,fp);
	fwrite(obj.bname,sizeof(char),50,fp);
	fwrite(&obj.vn,sizeof(int),1,fp);
	fwrite(obj.v,sizeof(Vertex),obj.vn,fp);
	fwrite(&obj.tn,sizeof(int),1,fp);
	for(i=0;i<obj.tn;i++)
	{
		for(j=0;j<3;j++)
		{
			temp=obj.t[i].v[j]-obj.v;
			fwrite(&temp,sizeof(int),1,fp);
		}
		if(obj.t[i].tex==&obj.front) temp=FRONT;
		else temp=BACK;
		fwrite(&temp,sizeof(int),1,fp);
	}
	fwrite(&obj.qn,sizeof(int),1,fp);
	for(i=0;i<obj.qn;i++)
	{
		for(j=0;j<4;j++)
		{
			temp=obj.q[i].v[j]-obj.v;
			fwrite(&temp,sizeof(int),1,fp);
		}
		if(obj.q[i].tex==&obj.front) temp=FRONT;
		else temp=BACK;
		fwrite(&temp,sizeof(int),1,fp);
	}

	fclose(fp);
}

void LoadObject()
{
	FILE *fp;
	int i,j,temp;
	if((fp=fopen("output","rb"))==NULL)
	{
		fprintf(stderr,"load error\n");
		exit(0);
	}
	
	fread(obj.fname,sizeof(char),50,fp);
	LoadTexture(&obj.front,obj.fname);
	fread(obj.bname,sizeof(char),50,fp);
	LoadTexture(&obj.back,obj.bname);
	fread(&obj.vn,sizeof(int),1,fp);
	fread(obj.v,sizeof(Vertex),obj.vn,fp);
	fread(&obj.tn,sizeof(int),1,fp);
	for(i=0;i<obj.tn;i++)
	{
		for(j=0;j<3;j++)
		{			
			fread(&temp,sizeof(int),1,fp);
			obj.t[i].v[j]=temp+obj.v;
		}
		fread(&temp,sizeof(int),1,fp);
		if(temp==FRONT) obj.t[i].tex=&obj.front;
		else obj.t[i].tex=&obj.back;
	}
	fread(&obj.qn,sizeof(int),1,fp);
	for(i=0;i<obj.qn;i++)
	{
		for(j=0;j<4;j++)
		{
			fread(&temp,sizeof(int),1,fp);
			obj.q[i].v[j]=temp+obj.v;
		}
		fread(&temp,sizeof(int),1,fp);
		if(temp==FRONT) obj.q[i].tex=&obj.front;
		else obj.q[i].tex=&obj.back;
	}

	fclose(fp);
}

void elevate(GLfloat value)
{
	int i;
	for(i=0;i<obj.vn;i++)
		if(obj.v[i].x<=mousex*2-1+.01 && obj.v[i].x>=mousex*2-1-.01
			&& obj.v[i].y<=1-mousey*2+.01 && obj.v[i].y>=1-mousey*2-.01)
		{
			obj.v[i].z+=value;
		}
}

void delete_vertex()
{
	int i,j,flag;
	for(i=0;i<obj.vn;i++)
		if(obj.v[i].x<=mousex*2-1+.01 && obj.v[i].x>=mousex*2-1-.01
			&& obj.v[i].y<=1-mousey*2+.01 && obj.v[i].y>=1-mousey*2-.01)
		{
			for(j=0;j<obj.tn;j++)
			{
				if(obj.t[j].v[0]==&obj.v[i] || obj.t[j].v[1]==&obj.v[i] || obj.t[j].v[2]==&obj.v[i])
				{
					memmove(&obj.t[j],&obj.t[j+1],(99-j)*sizeof(Triangle*));
					obj.tn--;
				}
				if(obj.t[j].v[0]>&obj.v[i]) obj.t[j].v[0]--;
				if(obj.t[j].v[1]>&obj.v[i]) obj.t[j].v[1]--;
				if(obj.t[j].v[2]>&obj.v[i]) obj.t[j].v[2]--;
			}
			for(j=0;j<obj.qn;j++)
			{	
				if(obj.q[j].v[0]==&obj.v[i] || obj.q[j].v[1]==&obj.v[i] || obj.q[j].v[2]==&obj.v[i] || obj.q[j].v[3]==&obj.v[i])
				{
					memmove(&obj.q[j],&obj.q[j+1],(99-j)*sizeof(Quad*));
					obj.qn--;
				}
				if(obj.q[j].v[0]>&obj.v[i]) obj.q[j].v[0]--;
				if(obj.q[j].v[1]>&obj.v[i]) obj.q[j].v[1]--;
				if(obj.q[j].v[2]>&obj.v[i]) obj.q[j].v[2]--;
				if(obj.q[j].v[3]>&obj.v[i]) obj.q[j].v[3]--;
			}
			memmove(&obj.v[i],&obj.v[i+1],(99-i)*sizeof(Vertex*));
			obj.vn--;
		}
	for(i=0;i<obj.vn;)
	{
		flag=0;
		for(j=0;flag==0 && j<=obj.tn;j++)
			if(obj.t[j].v[0]==&obj.v[i] || obj.t[j].v[1]==&obj.v[i] || obj.t[j].v[2]==&obj.v[i])
			{
				flag=1;
				break;
			}
		for(j=0;flag==0 && j<=obj.qn;j++)
			if(obj.q[j].v[0]==&obj.v[i] || obj.q[j].v[1]==&obj.v[i] || obj.q[j].v[2]==&obj.v[i] || obj.q[j].v[3]==&obj.v[i])
			{
				flag=1;
				break;
			}
		if(flag==0)
		{
			for(j=0;flag==0 && j<obj.tn;j++)
			{
				if(obj.t[j].v[0]>&obj.v[i]) obj.t[j].v[0]--;
				if(obj.t[j].v[1]>&obj.v[i]) obj.t[j].v[1]--;
				if(obj.t[j].v[2]>&obj.v[i]) obj.t[j].v[2]--;
			}
			for(j=0;flag==0 && j<obj.qn;j++)
			{
				if(obj.q[j].v[0]>&obj.v[i]) obj.q[j].v[0]--;
				if(obj.q[j].v[1]>&obj.v[i]) obj.q[j].v[1]--;
				if(obj.q[j].v[2]>&obj.v[i]) obj.q[j].v[2]--;
				if(obj.q[j].v[3]>&obj.v[i]) obj.q[j].v[3]--;
			}
			memmove(&obj.v[i],&obj.v[i+1],(99-i)*sizeof(Vertex*));
			obj.vn--;
		}
		else
			i++;
	}
}

void special_keyboard(int key,int x, int y)
{
	mousex=(GLfloat)x/(GLfloat)WIDTH,mousey=(GLfloat)y/(GLfloat)HEIGHT;
}

void passivemotion(int x, int y)
{
	mousex=(GLfloat)x/(GLfloat)WIDTH,mousey=(GLfloat)y/(GLfloat)HEIGHT;
}

void motion(int x, int y)
{
	mousex=(GLfloat)x/(GLfloat)WIDTH,mousey=(GLfloat)y/(GLfloat)HEIGHT;
}

