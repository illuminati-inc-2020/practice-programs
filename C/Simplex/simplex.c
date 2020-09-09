/* Date			: 15.02.2011
 * Author		: Rakesh Malik
 * Subject		: Simplex algorithm
 * Assignment no	: 21
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <string.h>

#define E	0
#define GE	1
#define LE	2

#define M	1e100

#define MAXIMIZE 0
#define MINIMIZE 1

int normalize_LPP(char,double**,double**,double***,char**,int*,int*);
void simplex(char,double*,double*,double**,int,int,int);
void print_LPP(char,double*,double*,double**,char*,int,int);
void print_table(double*,double*,double**,int,int,int*,double*,int,int);

int main(int argc,char *argv[])
{
	FILE *fp;
	int v,e;
	int n;												/* Number of variables */
	int m;												/* Number of equations */
	int p;												/* number of slack,surplus,artificial variables */
	double *c;
	double *b;
	double **A;
	char *sign;
	char buf[10];
	char object;
	printf("SIMPLEX METHOD FOR SOLVING LPP :\n");
	if(argc<2)
	{
		fprintf(stderr,"\nError : Argument missing.");
		return 1;
	}
	if((fp=fopen(argv[1],"r"))==NULL)
	{
		fprintf(stderr,"\nError : File doesn't exist or file read error.");
		return 1;
	}
	fscanf(fp,"%d%d%s",&m,&n,buf);
	if(strcmp(buf,"minimize")==0) object=MINIMIZE;
	else object=MAXIMIZE;
	c=(double*)calloc(sizeof(double),n);
	for(v=0;v<n;v++)
		fscanf(fp,"%lf",&c[v]);
	b=(double*)calloc(sizeof(double),m);
	A=(double**)calloc(sizeof(double*),m);
	sign=(char*)calloc(sizeof(char),m);
	for(e=0;e<m;e++)
	{
		A[e]=(double*)calloc(sizeof(double),n);
		for(v=0;v<n;v++)
			fscanf(fp,"%lf",&A[e][v]);
		fscanf(fp,"%s",buf);
		if(strcmp(buf,">=")==0) sign[e]=GE;
		else if(strcmp(buf,"<=")==0) sign[e]=LE;
		else sign[e]=E;
		fscanf(fp,"%lf",&b[e]);
	}
	fclose(fp);
	print_LPP(object,c,b,A,sign,m,n);
	p=normalize_LPP(object,&c,&b,&A,&sign,&m,&n);
	printf("\nAfter introducing slack, surplus and artificial variables.\n");
	print_LPP(MAXIMIZE,c,b,A,sign,m,n);
	simplex(object,c,b,A,m,n,p);
	printf("\n");
	return 0;
}

int normalize_LPP(char object,double **c,double **b,double ***A,char **sign,int *m,int *n)
{
	int e,v,e_;
	int p=0;								/* total number of slack,surplus and artificial variables */
	if(object==MINIMIZE)
		for(v=0;v<*n;v++)
			(*c)[v]*=-1;
	for(e=0;e<*m;e++)
	{
		/* converting >= to<= */
		if((*b)[e]<0)
		{
			for(v=0;v<*n;v++)
				(*A)[e][v]*=-1;
			(*b)[e]*=-1;
			(*sign)[e]=((*sign)[e]==GE)?LE:((*sign)[e]==LE)?GE:E;
		}
		/* Introducing slack variables */
		if((*sign)[e]==LE)
		{
			(*n)++;
			p++;
			printf("\nSlack variable x%d introduced.",*n);
			(*c)=(double*)realloc(*c,sizeof(double)*(*n));
			(*c)[*n-1]=0;
			for(e_=0;e_<*m;e_++)
			{
				(*A)[e_]=(double*)realloc((*A)[e_],sizeof(double)*(*n));
				(*A)[e_][*n-1]=(e_==e)?1:0;
			}
			(*sign)[e]=E;
		}
		else if((*sign)[e]==E)
		{
			(*n)++;
			p++;
			printf("\nArtificial variable x%d introduced.",*n);
			(*c)=(double*)realloc(*c,sizeof(double)*(*n));
			(*c)[*n-1]=-M;
			for(e_=0;e_<*m;e_++)
			{
				(*A)[e_]=(double*)realloc((*A)[e_],sizeof(double)*(*n));
				(*A)[e_][*n-1]=(e_==e)?1:0;
			}
			(*sign)[e]=E;
		}
		/* Introducing surplus and artificial variables */
		else
		{
			(*n)+=2;
			p+=2;
			printf("\nSurplus variable x%d introduced.",*n-1);
			printf("\nArtificial variable x%d introduced.",*n);
			(*c)=(double*)realloc(*c,sizeof(double)*(*n));
			(*c)[*n-2]=0;
			(*c)[*n-1]=-M;
			for(e_=0;e_<*m;e_++)
			{
				(*A)[e_]=(double*)realloc((*A)[e_],sizeof(double)*(*n));
				(*A)[e_][*n-2]=(e_==e)?-1:0;
				(*A)[e_][*n-1]=(e_==e)?1:0;
			}
			(*sign)[e]=E;
		}
	}
	return p;
}

void print_LPP(char object,double *c,double *b,double **A,char *sign,int m,int n)
{
	int e,v;
	printf("\n%s z = ",(object==MAXIMIZE)?"Maximize":"Minimize");
	for(v=0;v<n;v++)
		if(fabs(c[v])>=M)
			printf("%s%gMx%d",(c[v]<0)?" - ":(v!=0)?" + ":"",fabs(c[v])/M,v+1);
		else 
			printf("%s%gx%d",(c[v]<0)?" - ":(v!=0)?" + ":"",fabs(c[v]),v+1);
	printf("\nSubject to \t");
	for(e=0;e<m;e++)
	{
		for(v=0;v<n;v++)
			printf("%s%gx%d",(A[e][v]<0)?" - ":(v!=0)?" + ":"",fabs(A[e][v]),v+1);
		printf(" %s %g\n\t\t",(sign[e]==E)?"=":(sign[e]==GE)?">=":"<=",b[e]);
	}
	for(v=0;v<n;v++)
		printf("x%d%s",v+1,(v==n-1)?"":", ");
	printf(" >= 0\n");
}

void simplex(char object,double *c,double *b,double **A,int m,int n,int p)
{
	int flag,i;
	int e,v;	
	int *B;									/* Basis */
	double *P;								/* z-c */
	double **A_,*b_;						/* Temporary storage for A and b */
	int key_row,key_column;
	double min;
	double *x;
	double z;
	B=(int*)calloc(sizeof(int),m);
	P=(double*)calloc(sizeof(double),n);
	A_=(double**)calloc(sizeof(double*),m);
	for(e=0;e<m;e++)
		A_[e]=(double*)calloc(sizeof(double),n);
	b_=(double*)calloc(sizeof(double),m);
	x=(double*)calloc(sizeof(double),n-p);
	while(1)
	{
		/* Calculating basis */
		for(i=0;i<m;i++)
			for(v=0;v<n;v++)
			{
				flag=0;
				for(e=0;e<m;e++)
					if(!((A[e][v]==1 && i==e) || (A[e][v]==0 && i!=e)))
						flag=1;
				if(flag==0)
				{
					B[i]=v;
					break;
				}
			}
		
		/* Calculating (zj-cj) */
		for(v=0;v<n;v++)
		{
			P[v]=0;
			for(e=0;e<m;e++)
				P[v]+=A[e][v]*c[B[e]];
			P[v]-=c[v];
		}

		/* Finding Key column */
		min=DBL_MAX;
		flag=0;
		for(v=0;v<n;v++)
		{
			if(flag==0 && P[v]<0)
				flag=1;
			if(P[v]<0 && P[v]<min)
			{
				min=P[v];
				key_column=v;
			}
		}

		/* Solution */
		if(flag==0)
		{
			print_table(c,b,A,m,n,B,P,-1,-1);
			printf("\nThe solution is : ");
			for(e=0;e<m;e++)
				if(B[e]<n-p)
					x[B[e]]=b[e];
			for(i=0;i<n-p;i++)
				printf("\nx%d = %g",i+1,x[i]);
			z=0;
			for(i=0;i<n-p;i++)
				z+=c[i]*x[i];
			if(object==MAXIMIZE) printf("\nz(max) = %g",z);
			else printf("\nz(min) = %g",-z);
			return;
		}

		/* Finding Key Row */
		min=DBL_MAX;
		flag=0;
		for(e=0;e<m;e++)
		{
			if(flag==0 && A[e][key_column]>0)
				flag=1;
			if(A[e][key_column]>0 && b[e]/A[e][key_column]<min)
			{
				min=b[e]/A[e][key_column];
				key_row=e;
			}
		}

		/* Unbounded solution */
		if(flag==0)
		{
			print_table(c,b,A,m,n,B,P,-1,key_column);
			printf("\nSolution is unbounded.");
			return;
		}

		print_table(c,b,A,m,n,B,P,key_row,key_column);
		printf("\na%d is entering vector.",key_column+1);
		printf("\na%d is departing vector.",B[key_row]+1);
		printf("\ny%d%d=%g is key/pivot element.",key_column+1,key_row+1,A[key_row][key_column]);

		/* Calculating y(i,j) */
		for(e=0;e<m;e++)
		{
			for(v=0;v<n;v++)
				if(e!=key_row)
					A_[e][v]=A[e][v]-A[e][key_column]*A[key_row][v]/A[key_row][key_column];
				else
					A_[e][v]=A[e][v]/A[key_row][key_column];
			if(e!=key_row)
				b_[e]=b[e]-A[e][key_column]*b[key_row]/A[key_row][key_column];
			else
				b_[e]=b[e]/A[key_row][key_column];
		}		
		for(e=0;e<m;e++)
		{
			for(v=0;v<n;v++)
				A[e][v]=A_[e][v];
			b[e]=b_[e];
		}
	}
}


void print_table(double *c,double *b,double **A,int m,int n,int *B,double *P,int key_row,int key_column)
{
	int e,v;
	printf("\n                      _______");
	for(v=0;v<n;v++)
		printf("_______");
	printf("\n                     |cj    |");
	for(v=0;v<n;v++)
		if(fabs(c[v])>=M)
			printf("%6.3gM",c[v]/M);
		else
			printf("%7.2g",c[v]);
	printf("|\n ____________________________");
	for(v=0;v<n;v++)
		printf("_______");
	printf("|\n|    cB|     B|    xB|     b|");
	for(v=0;v<n;v++)
		printf("    a%-2d",v+1);
	printf("|\n|____________________________");
	for(v=0;v<n;v++)
		printf("_______");
	printf("|\n");
	for(e=0;e<m;e++)
	{
		if(fabs(c[B[e]])>=M) 
			printf("|%5.3gM|",c[B[e]]/M);
		else
			printf("|%6.3g|",c[B[e]]);
		printf("   a%-2d|",B[e]+1);
		printf("   x%-2d|",B[e]+1);
		printf("%6.3g|",b[e]);
		for(v=0;v<n;v++)
			printf("%6.3g%c",A[e][v],(e==key_row && v==key_column)?'*':' ');
		printf("|\n");
	}
	printf("|____________________________");
	for(v=0;v<n;v++)
		printf("_______");
	printf("|\n|          (zj-cj)          |");
	for(v=0;v<n;v++)
			if(fabs(P[v])>=M)
				printf("%6.3gM",P[v]/M);
			else
				printf("%7.3g",P[v]);
	printf("|\n|____________________________");
	for(v=0;v<n;v++)
		printf("____%s",(v==key_column)?" /\\":(key_column>=0 && v==B[key_row])?" \\/":"___");
	printf("|\n");
}
