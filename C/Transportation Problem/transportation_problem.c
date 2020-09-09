/* Date			: 10.02.2011
 * Author		: Rakesh Malik
 * Subject		: Implement calculating initial basic feasible solution 
 *			  for a transportation problem using Vogel's approximation 
 *			  method and its optimization.
 * Assignment no	: 19
 */

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define SRC	0
#define	DEST	1

#define	false	0
#define true	1

typedef struct position
{
	int dest,src;
}position;

void solve_tansportation(double**,double*,double*,int,int,double**);
int createloop(double**,int,int,int,int,position*,int,int);
void VAM(double**,double*,double*,int,int,double**);
void print_penalty(double**,double*,double*,int,int,double*,double*,double**);
void print_matrix(double**,double*,double*,int,int,double**);
void print_cell_evaluation(double**,double*,double*,int,int,double**,double**);

int main(int argc,char *argv[])
{
	FILE *fp;
	int nos,nod;					/* number of sources and destinations */
	int src,dest;					/* source and destination index in iteration */
	double **C;					/* Cost matrix */
	double *D;					/* Demand vector */
	double *A;					/* Availability vector */
	double total_availability=0,total_demand=0;	/* Total avilability and demand */
	double **allocation;				/* Allocation matrix */
	printf("TRANSPORTATION PROBLEM\n");
	if(argc<2)
	{
		fprintf(stderr,"Error : Argument missing!\n");
		return 1;
	}
	if((fp=fopen(argv[1],"r"))==NULL)
	{
		fprintf(stderr,"Error : File read error!\n");
		return 1;
	}
	fscanf(fp,"%d%d",&nod,&nos);
	C=(double**)calloc(nos+1,sizeof(double*));
	D=(double*)calloc(nod+1,sizeof(double));
	A=(double*)calloc(nos+1,sizeof(double));
	allocation=(double**)calloc(nos+1,sizeof(double*));
	for(src=0;src<nos;src++)
	{
		C[src]=(double*)calloc(nod+1,sizeof(double));
		allocation[src]=(double*)calloc(nod+1,sizeof(double));
		for(dest=0;dest<nod;dest++)
			fscanf(fp,"%lf",&C[src][dest]);
		fscanf(fp,"%lf",&A[src]);
		total_availability+=A[src];
	}
	for(dest=0;dest<nod;dest++)
	{
		fscanf(fp,"%lf",&D[dest]);
		total_demand+=D[dest];
	}
	if(total_availability<total_demand)
	{
		printf("\nAs the transportation problem is not balanced [i.e. total_availability(%g)<total_demand(%g)] an additional row is added",total_availability,total_demand);
		C[nos]=(double*)calloc(nod+1,sizeof(double));
		allocation[nos]=(double*)calloc(nod+1,sizeof(double));
		A[nos]=total_demand-total_availability;
		nos++;
	}
	else if(total_availability>total_demand)
	{
		printf("\nAs the transportation problem is not balanced [i.e. total_availability(%g)>total_demand(%g)] an additional row is added",total_availability,total_demand);
		D[nod]=total_availability-total_demand;
		nod++;
	}
	else printf("\nAs the transportation problem is balanced [i.e. total_availability(%g)=total_demand(%g)] no additional row/column is added",total_availability,total_demand);
	solve_tansportation(C,D,A,nod,nos,allocation);
	printf("\n");
	return 0;
}

void solve_tansportation(double **C,double *D,double *A,int nod,int nos,double **allocation)
{
	int flag,i;
	int src,dest;					/* source and destination index in iteration */
	int noa;					/* Number of allocation */
	double *u,*v,**ce;				/* u,v vector and cell evaluation matrix */
	position *loop;					/* Loop sequence */
	double min;
	u=(double*)calloc(nod,sizeof(double));
	v=(double*)calloc(nos,sizeof(double));
	ce=(double**)calloc(nos,sizeof(double*));
	for(src=0;src<nos;src++)
		ce[src]=(double*)calloc(nod,sizeof(double));
	loop=(position*)calloc(nos*nod,sizeof(position));
	
	print_matrix(C,D,A,nod,nos,allocation);
	printf("\n\nSTEP 1 :\n--------\n");
	VAM(C,D,A,nod,nos,allocation);
	printf("\nThe initial basic feasible soution is : ");
	printf("\nAllocations are shown in [] adjacent to costs");
	print_matrix(C,D,A,nod,nos,allocation);
	
	while(1)
	{
		printf("\n\nSTEP 2 :\n--------\n");
		/* Checking degeneracy */
		noa=0;
		for(src=0;src<nos;src++)
			for(dest=0;dest<nod;dest++)
				if(allocation[src][dest])
					noa++;
		/* Completion of basis during degeneracy */
		if(noa<nos+nod-1)
		{
			printf("\nThe solution is degenegate as number of allocation (%d) < m+n-1 = %d+%d-1 = %d.",noa,nos,nod,nos+nod-1);
			flag=false;
			for(src=0;flag==false && src<nos;src++)
				for(dest=0;flag==false && dest<nod;dest++)
					if(!createloop(allocation,nod,nos,dest,src,loop,0,0))
					{
						flag=true;
						allocation[src][dest]=DBL_MIN;
						printf("\nA small quantity \'e\' is allocated in cell (%d,%d) to complete the basis.",src+1,dest+1);
					}
		}
		else
			printf("\nThe solution is non-degenegate as number of allocation (%d) = m+n-1 = %d+%d-1 = %d.",noa,nos,nod,nos+nod-1);
		/* u and v calculation */
		printf("\n\nSTEP 3 :\n--------\n");
		for(src=0;src<nos;src++)
			u[src]=DBL_MIN;
		for(dest=0;dest<nod;dest++)
			v[dest]=DBL_MIN;
		u[0]=0;
		while(1)
		{
			flag=false;
			for(src=0;src<nos;src++)
				for(dest=0;dest<nod;dest++)
					if(allocation[src][dest])
					{	
						if(u[src]!=DBL_MIN && v[dest]==DBL_MIN)
						{
							v[dest]=C[src][dest]-u[src];
							flag=true;
						}
						else if(u[src]==DBL_MIN && v[dest]!=DBL_MIN)
						{
							u[src]=C[src][dest]-v[dest];
							flag=true;
						}
					}
			if(flag==false) break;
		}
		/* Cell evaluation */
		for(src=0;src<nos;src++)
			for(dest=0;dest<nod;dest++)
				if(!allocation[src][dest])
					ce[src][dest]=C[src][dest]-u[src]-v[dest];
		printf("\nCell evaluations are shown in () adjacent to costs.");
		print_cell_evaluation(C,u,v,nod,nos,allocation,ce);
		/* Optimality test */
		flag=false;
		for(src=0;flag==false && src<nos;src++)
			for(dest=0;flag==false && dest<nod;dest++)
				if(!allocation[src][dest] && ce[src][dest]<0)
				{
					loop[0].dest=dest,loop[0].src=src;
					flag=true;
				}
		if(flag==false)
		{
			printf("\nThis is an optimal solution of transportation problem as all the cell evaluations are positive.");
			return;
		}
		/* Loop formation */
		else
		{
			printf("\n\nSTEP 4 :\n--------\n");
			printf("\nThis solution is not an optimal solution as cell evaluation for cell (%d,%d) is negative.",loop[0].src+1,loop[0].dest+1);
			createloop(allocation,nod,nos,loop[0].dest,loop[0].src,loop,0,0);
			min=DBL_MAX;
			printf("\nA loop is formed : (%d,%d) ",loop[0].src+1,loop[0].dest+1);
			for(i=1;loop[i].src>=0;i++)
			{
				printf("(%d,%d) ",loop[i].src+1,loop[i].dest+1);
				if(allocation[loop[i].src][loop[i].dest]<min)
					min=allocation[loop[i].src][loop[i].dest];
			}
			for(i=0;loop[i].src>=0;i++)
				if(min!=DBL_MIN || (min==DBL_MIN && (allocation[loop[i].src][loop[i].dest]==DBL_MIN || allocation[loop[i].src][loop[i].dest]==0)))
					if(i%2==0)
						allocation[loop[i].src][loop[i].dest]+=min;
					else
						allocation[loop[i].src][loop[i].dest]-=min;
			print_matrix(C,D,A,nod,nos,allocation);
		}
	}
}

int createloop(double **allocation,int nod,int nos,int x,int y,position *loop,int count,int dir)
{
	int src,dest;					/* source and destination index in iteration */
	int i,flag=false;					/* 0 if loop not found else length */
	if(count==0)		
		for(i=0;i<nos*nod;i++)
			loop[i].dest=loop[i].src=-1;
	loop[count].dest=x,loop[count].src=y;
	if(dir==0)
	{
		for(dest=x+1,src=y;flag==0 && dest<nod;dest++)
			if(allocation[src][dest]!=0)
				flag=createloop(allocation,nod,nos,dest,src,loop,count+1,!dir);
			else if(count>0 && loop[0].dest==dest && loop[0].src==src)
				flag=true;
		for(dest=x-1,src=y;flag==0 && dest>=0;dest--)
			if(allocation[src][dest]!=0)
				flag=createloop(allocation,nod,nos,dest,src,loop,count+1,!dir);
			else if(count>0 && loop[0].dest==dest && loop[0].src==src)
				flag=true;
	}
	else
	{
		for(dest=x,src=y+1;flag==0 && src<nos;src++)
			if(allocation[src][dest]!=0)
				flag=createloop(allocation,nod,nos,dest,src,loop,count+1,!dir);
			else if(count>0 && loop[0].dest==dest && loop[0].src==src)
				flag=true;
		for(dest=x,src=y-1;flag==0 && src>=0;src--)
			if(allocation[src][dest]!=0)
				flag=createloop(allocation,nod,nos,dest,src,loop,count+1,!dir);
			else if(count>0 && loop[0].dest==dest && loop[0].src==src)
				flag=true;
	}
	if(flag==0) loop[count].dest=loop[count].src=-1;
	return flag;
}

void VAM(double **C,double *D,double *A,int nod,int nos,double **allocation)
{
	int src,dest;					/* source and destination index in iteration */
	double *src_penalty,*dest_penalty;		/* penalties */
	double min1,min2;				/* first and second minimum cost of a row/column */
	double max;					/* maximum penalty */
	int type;					/* maximum penalty holder type (SRC/DEST) */
	int src_index,dest_index;			/* maximum penalty holder index */
	int remaining_src,remaining_dest;		/* number of src/dest not exhausted/full */
	double *cD,*cA;					/* Current availability and demands */
	dest_penalty=(double*)calloc(nod,sizeof(double));
	src_penalty=(double*)calloc(nos,sizeof(double));
	cD=(double*)calloc(nod,sizeof(double));
	cA=(double*)calloc(nos,sizeof(double));
	for(src=0;src<nos;src++)
		cA[src]=A[src];
	for(dest=0;dest<nod;dest++)
		cD[dest]=D[dest];
	printf("\nWe use Vogel's Approximation Method to get the initial basic feasible solution.");
	printf("\nAllocations are shown in [] adjacent to costs");
	printf("\nand penalties are shown in () adjacent to each availability/demand.");
	for(remaining_src=nos,remaining_dest=nod;remaining_dest>0 && remaining_src>0;)
	{
		/* Calculating penalty */
		for(src=0;src<nos;src++)
			if(cA[src])
			{
				min1=DBL_MAX;
				for(dest=0;dest<nod;dest++)
					 if(cD[dest] && C[src][dest]<=min1)
					 {
						min1=C[src][dest];
						dest_index=dest;
					 }
				min2=DBL_MAX;
				for(dest=0;dest<nod;dest++)
					 if(cD[dest] && C[src][dest]<=min2 && dest!=dest_index)
						min2=C[src][dest];
				if(min2==DBL_MAX) min2=min1;
				src_penalty[src]=min2-min1;
			}
		for(dest=0;dest<nod;dest++)
			if(cD[dest])
			{
				min1=DBL_MAX;
				for(src=0;src<nos;src++)
					if(cA[src] && C[src][dest]<=min1)
					{
						min1=C[src][dest];
						src_index=src;
					}
				min2=DBL_MAX;
				for(src=0;src<nos;src++)
					if(cA[src] && C[src][dest]<=min2 && src!=src_index)
						min2=C[src][dest];
				if(min2==DBL_MAX) min2=min1;
				dest_penalty[dest]=min2-min1;
			}
		/* Finding maximum penalty */
		max=-DBL_MAX;
		for(src=0;src<nos;src++)
			if(cA[src] && src_penalty[src]>max)
			{
				max=src_penalty[src];
				type=SRC;
				src_index=src;
			}
		 for(dest=0;dest<nod;dest++)
			if(cD[dest] && dest_penalty[dest]>max)
			{
				max=dest_penalty[dest];
				type=DEST;
				dest_index=dest;
			}
		/* Finding minimum cost */
		if(type==SRC)
		{
			min1=DBL_MAX;
			for(dest=0;dest<nod;dest++)
				if(cD[dest] && C[src_index][dest]<min1)
				{
					min1=C[src_index][dest];
					dest_index=dest;
				}
		}
		else
		{
			min1=DBL_MAX;
			for(src=0;src<nos;src++)
				if(cA[src] && C[src][dest_index]<min1)
				{
					min1=C[src][dest_index];
					src_index=src;
				}
		}		
		
		/* Allocation */
		allocation[src_index][dest_index]=(cA[src_index]<cD[dest_index])?cA[src_index]:cD[dest_index];
		print_penalty(C,cD,cA,nod,nos,dest_penalty,src_penalty,allocation);
		cA[src_index]-=allocation[src_index][dest_index];
		cD[dest_index]-=allocation[src_index][dest_index];
		if(!cA[src_index]) remaining_src--;
		if(!cD[dest_index]) remaining_dest--;
	}
}

void print_penalty(double **C,double *D,double *A,int nod,int nos,double *dest_penalty,double *src_penalty,double **allocation)
{
	int src,dest;					/* source and destination index in iteration */
	printf("\n\t");
	for(dest=0;dest<nod;dest++)
		if(D[dest]) printf("      D%-2d\t",dest+1);		
	printf("\n\t");
	for(dest=0;dest<nod;dest++)
		if(D[dest]) printf("----------------");
	putchar('\n');
	for(src=0;src<nos;src++)
		if(A[src]) 
		{
			printf("  S%-2d  |",src+1);
			for(dest=0;dest<nod;dest++)
				if(D[dest])
				{
					printf("%8g",C[src][dest]);
					if(allocation[src][dest]==DBL_MIN)
						printf("[e]");
					else if(allocation[src][dest]!=0)
						printf("[%g]",allocation[src][dest]);
					printf("\t");
				}
			printf("| %8g (%g)\n",A[src],src_penalty[src]);
		}
	printf("\t");
	for(dest=0;dest<nod;dest++)
		if(D[dest]) printf("----------------");
	printf("\n\t");
	for(dest=0;dest<nod;dest++)
		if(D[dest]) printf("%8g(%g)\t",D[dest],dest_penalty[dest]);
	printf("\n");
}

void print_cell_evaluation(double **C,double *u,double *v,int nod,int nos,double **allocation,double **ce)
{
	int src,dest;					/* source and destination index in iteration */
	printf("\n\t");
	for(dest=0;dest<nod;dest++)
		printf("      D%-2d\t",dest+1);		
	printf("  u(i)\n\t");
	for(dest=0;dest<nod;dest++)
		printf("----------------");
	putchar('\n');
	for(src=0;src<nos;src++)
	{
		printf("  S%-2d  |",src+1);
		for(dest=0;dest<nod;dest++)
			{
				printf("%8g",C[src][dest]);
				if(allocation[src][dest]==DBL_MIN)
					printf("[e]");
				else if(allocation[src][dest]!=0)
					printf("[%g]",allocation[src][dest]);
				else
					printf("(%g)",ce[src][dest]);
				printf("\t");
			}
		printf("| %-8g\n",u[src]);
	}
	printf("\t");
	for(dest=0;dest<nod;dest++)
		printf("----------------");
	printf("\nv(j)\t");
	for(dest=0;dest<nod;dest++)
		printf("%8g\t",v[dest]);
	printf("\n");
}

void print_matrix(double **C,double *D,double *A,int nod,int nos,double **allocation)
{
	int src,dest;					/* source and destination index in iteration */
	printf("\n\t");
	for(dest=0;dest<nod;dest++)
		printf("      D%-2d\t",dest+1);		
	printf("\n\t");
	for(dest=0;dest<nod;dest++)
		printf("----------------");
	putchar('\n');
	for(src=0;src<nos;src++)
	{
		printf("  S%-2d  |",src+1);
		for(dest=0;dest<nod;dest++)
			{
				printf("%8g",C[src][dest]);
				if(allocation[src][dest]==DBL_MIN)
					printf("[e]");
				else if(allocation[src][dest]!=0)
					printf("[%g]",allocation[src][dest]);
				printf("\t");
			}
		printf("| %-8g\n",A[src]);
	}
	printf("\t");
	for(dest=0;dest<nod;dest++)
		printf("----------------");
	printf("\n\t");
	for(dest=0;dest<nod;dest++)
		printf("%8g\t",D[dest]);
	printf("\n");
}
