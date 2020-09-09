/* Date			: 13.02.2011
 * Author		: Rakesh Malik
 * Subject		: Implement calculating initial basic feasible solution 
 *			  for a transportation problem using Vogel's approximation 
 *			  method and its optimization.
 * Assignment no	: 20
 */

#include <stdio.h>
#include <stdlib.h>

#define INF (0x7FFF)

#define UNCROSSED 		0
#define CROSSED_HORIZONTALLY 	1
#define CROSSED_VERTICALLY 	2
#define INTERSECTED 		3

#define	ROW			0
#define COLUMN			1

void solve_assignment(int**,int,int**);
void print_matrix(int**,int);
void print_lines(int**,int,int**);
void optimal_solution(int,int**,int**,int**,int**,int);

int main(int argc,char *argv[])
{
	FILE *fp;
	int n;						/* order */
	int jobs,machines;				/* number of jobs and machines */
	int M,J;
	int **C;					/* Cost matrix */
	int **assignment;				/* Assignment matrix */
	printf("ASSIGNMENT PROBLEM\n");
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
	fscanf(fp,"%d%d",&machines,&jobs);
	n=(jobs>machines)?jobs:machines;
	C=(int**)calloc(n,sizeof(int*));	
	assignment=(int**)calloc(n,sizeof(int*));
	for(J=0;J<n;J++)
	{
		C[J]=(int*)calloc(n,sizeof(int*));
		assignment[J]=(int*)calloc(n,sizeof(int*));
		if(J<jobs)
			for(M=0;M<machines;M++)
				fscanf(fp,"%d",&C[J][M]);
	}
	solve_assignment(C,n,assignment);
	return 0;
}

void solve_assignment(int **C,int n,int **assignment)
{
	int J,M,i;						/* indices of arrays in iteration */
	int lines; 	            				/* number of lines drawn */

	int **cell_state=(int**)calloc(n,sizeof(int*));		/* State of a cell UNCROSSED/CROSSED_HORIZONTALLY/CROSSED_VERTICALLY/INTERSECTED */
	int **cost=(int**)calloc(n,sizeof(int*));		/* Original cost backup */
	for(J=0;J<n;J++)
	{
		cell_state[J]=(int*)calloc(n,sizeof(int*));
		cost[J]=(int*)calloc(n,sizeof(int*));
		for(M=0;M<n;M++)
		{
			cell_state[J][M]=UNCROSSED;
			cost[J][M]=C[J][M];
		}
	}

	printf("\nThe given assignment problem is as under :\n");	
	print_matrix(C,n);
	printf("\nOrder of the assignment problem = %d",n);

	/* STEP 1 */
	int min;
	printf("\n\nStep 1 :");
	printf("\nSubtracting the minimum element of each row in the cost matrix from all elements of the respective row.\n");	
	for(J=0;J<n;J++)
	{
		min=INF;
		for(M=0;M<n;M++)
			if(C[J][M]<min)
				min=C[J][M];
		for(M=0;M<n;M++)
			C[J][M]-=min;
	}
	print_matrix(C,n);
	printf("\nSubtracting the minimum element of each column in the cost matrix from all elements of the respective column.\n");
	for(M=0;M<n;M++)
	{
		min=INF;
		for(J=0;J<n;J++)
			if(C[J][M]<min)
				min=C[J][M];
		for(J=0;J<n;J++)
			C[J][M]-=min;
	}
	
	print_matrix(C,n);

	/* STEP 2 */
	int maxzeroline;		/* row/column number with maximum zeros */
	int zeros;			/* Number of zeros in current line calculated at a certain point of iteration */
	int maxzeros;			/* Maximum number of zeros in a line calculated at a certain point of iteration */
	int smallestuncrossed;		/* smallest uncrossed element */
	int maxzerolinetype;		/* = 0(line with maximum zero is row) / 1(line with maximum zero is a column) */
	int uncrossedzero;		/* Number of uncrosed zeros remaining */
	printf("\n\nStep 2 :");
	while(1)
	{
		printf("\nDrawing minimum vertical and horizontal lines to cover all the zeros.\n");
		for(lines=0;lines<n;lines++)
		{
			for(maxzeros=0,J=0;J<n;J++)
			{
				zeros=0;
				for(M=0;M<n;M++)
					if(cell_state[J][M]==UNCROSSED && C[J][M]==0)
						zeros++;
				if(zeros>maxzeros)
				{
					maxzeros=zeros;
					maxzeroline=J;
					maxzerolinetype=ROW;
				}
			}
			for(M=0;M<n;M++)
			{
				zeros=0;
				for(J=0;J<n;J++)
					if(cell_state[J][M]==UNCROSSED && C[J][M]==0)
						zeros++;
				if(zeros>maxzeros)
				{
					maxzeros=zeros;
					maxzeroline=M;
					maxzerolinetype=COLUMN;
				}
			}
			for(i=0;i<n;i++)
				if(maxzerolinetype==ROW)
					cell_state[maxzeroline][i]=(cell_state[maxzeroline][i]==UNCROSSED)?CROSSED_HORIZONTALLY:INTERSECTED;
				else
					cell_state[i][maxzeroline]=(cell_state[i][maxzeroline]==UNCROSSED)?CROSSED_VERTICALLY:INTERSECTED;
			uncrossedzero=0;
			for(J=0;J<n;J++)
				for(M=0;M<n;M++)
					if(cell_state[J][M]==UNCROSSED && C[J][M]==0)
						uncrossedzero++;
			if(uncrossedzero==0)
			{
				lines++;
				break;
			}
		}
		print_lines(C,n,cell_state);
		if(lines<n)
			printf("\nAs number of lines (%d) < order of the problem (%d)\nsmallest uncrossed element is subtracted from uncrossed elements and added to intersection and step 2 is repeated.",lines,n);
		else 
			printf("\nAs number of lines (%d) = order of the problem (%d) we go to step 3",lines,n);
		if(lines==n) break;

		smallestuncrossed=INF;
		for(J=0;J<n;J++)
			for(M=0;M<n;M++)
				if(cell_state[J][M]==UNCROSSED && C[J][M]<smallestuncrossed)
					smallestuncrossed=C[J][M];
		for(J=0;J<n;J++)
			for(M=0;M<n;M++)
			{
				C[J][M]+=(cell_state[J][M]==INTERSECTED?1:cell_state[J][M]==UNCROSSED?-1:0)*smallestuncrossed;
				cell_state[J][M]=UNCROSSED;
			}
		print_matrix(C,n);
	}

	/* STEP 4 */
	printf("\n\nstep 3 :");
	printf("\nOptimal solution(s) :\n");
	for(J=0;J<n;J++)
		for(M=0;M<n;M++)
		{
			cell_state[J][M]=UNCROSSED;
			assignment[J][M]=0;
		}
	optimal_solution(n,C,cost,cell_state,assignment,0);
}

void optimal_solution(int n,int **C,int **cost,int **cell_state,int **assignment,int i)
{
	int J,M,J1,M1;				/* Indeices of arrays in iterations */
	int totalcost;				/* Total cost of an assignment calculated */
	if(i<n)
	{
		for(J=i;J<n;J++)
			for(M=0;M<n;M++)
				if(cell_state[J][M]==UNCROSSED && C[J][M]==0)
				{
					assignment[J][M]=1;
					for(J1=0;J1<n;J1++)
						for(M1=0;M1<n;M1++)
							if(J1==J || M1==M)
								cell_state[J1][M1]=(cell_state[J1][M1]==CROSSED_HORIZONTALLY)?INTERSECTED:CROSSED_HORIZONTALLY;
					optimal_solution(n,C,cost,cell_state,assignment,i+1);
					assignment[J][M]=0;
					for(J1=0;J1<n;J1++)
						for(M1=0;M1<n;M1++)
							if(J1==J || M1==M)
								cell_state[J1][M1]=(cell_state[J1][M1]==CROSSED_HORIZONTALLY)?UNCROSSED:CROSSED_HORIZONTALLY;
				}
	}
	else
	{
		totalcost=0;
		for(J=0;J<n;J++)
			for(M=0;M<n;M++)
				if(assignment[J][M]==1)
				{
					printf("J%d->M%d ",J+1,M+1);
					totalcost+=cost[J][M];
				}
		printf("     Cost = %d\n",totalcost);
	}
}

void print_matrix(int **C,int n)
{
	int J,M;
	printf("\n\t");
	for(M=0;M<n;M++)
		printf("M%-4d  ",M+1);
	putchar('\n');
	for(J=0;J<n;J++)
	{
		printf("  J%-2d  ",J+1);
		for(M=0;M<n;M++)
			printf("%-8d",C[J][M]);
		putchar('\n');
	}
}

void print_lines(int **C,int n,int **cell_state)
{  
	int J,M;
	printf("\n\t");
	for(M=0;M<n;M++)
		printf("M%-4d  \t",M+1);
	putchar('\n');
	for(J=0;J<n;J++)
	{
		if(J!=0)
		{
			 printf("     ");  
			 for(M=0;M<n;M++)
				printf((cell_state[J][M]==CROSSED_VERTICALLY || cell_state[J][M]==INTERSECTED)?"   |    ":"        ");
			 putchar('\n');
		}
		printf("J%-2d  ",J+1);
		for(M=0;M<n;M++)
		{
			printf((cell_state[J][M]==CROSSED_HORIZONTALLY || cell_state[J][M]==INTERSECTED)?"---":"   ");
			if(C[J][M]==0) putchar('0');
			else putchar((cell_state[J][M]==UNCROSSED)?' ':(cell_state[J][M]==CROSSED_HORIZONTALLY)?'-':'|');
			printf((cell_state[J][M]==CROSSED_HORIZONTALLY || cell_state[J][M]==INTERSECTED)?"----":"    ");
		}
		putchar('\n');
	}
}