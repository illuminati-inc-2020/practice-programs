/*	Author 	: Rakesh Malik
 *	Date	: 09.11.2010
 *	Subject	: Warshell's Algo for transitive closure
 */

#include<stdio.h>
#include"graph.h"

int main(int argc,char* argv[])
{
	char i,j,k,v,G[10][10];
	v=getgraph(G,argv[1]);
	for(k=0;k<v;k++)				// k=table number
		for(i=0;i<v;i++)			// i=row number
			for(j=0;j<v;j++)		// j=column number
				G[i][j]=G[i][j]|(G[i][k]&G[k][j]);
	printf("\nTransitive closure :\n");
	for(i=0;i<v;i++)
	{
		for(j=0;j<v;j++)
			printf("%d ",G[i][j]);
		putchar('\n');
	}
}
