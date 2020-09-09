/*	Author	: Rakesh Malik
 *	Date	: 20.11.2010 
 *	Subject	: Floyd's Algo
 *	Assignment 9
 */

#include<stdio.h>
#include<stdlib.h>
#include"graph.h"

#define INF 99999

void floyd(int d[10][10],int n);

int main(int argc,char* argv[])
{
	int G[10][10];
	int i,j,v;
	printf("Shortest Distance Using Floyd's Algo\n\n");
	if(argc<=1) 
	{
		char filename[256];
		printf("Enter filename : ");
		scanf("%[^\n]", filename);
		v=getgraph(G, filename);
	}
	else
		v=getgraph(G,argv[1]);
	printf("\nInput Graph : \n\n");
	for(i=0;i<v;i++)
		printf("\tv%d", i);
	printf("\n");
	for(i=0;i<v;i++)
	{
		printf("v%d\t", i);
		for(j=0;j<v;j++)
			if(G[i][j]==INF)
				printf("INF\t");
			else
				printf("%d\t",G[i][j]);
		printf("\n");
	}
	floyd(G,v);
	printf("\nShortest Distance : \n\n");
	for(i=0;i<v;i++)
		printf("\tv%d", i);
	printf("\n");
	for(i=0;i<v;i++)
	{
		printf("v%d\t", i);
		for(j=0;j<v;j++)
			if(G[i][j]==INF)
				printf("INF\t");
			else
				printf("%d\t",G[i][j]);
		printf("\n");
	}
}

void floyd(int d[10][10],int n)
{
	int i,j,k;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			for(k=0;k<n;k++)
				if(d[j][k] > d[j][i]+d[i][k])
					d[j][k]=d[j][i]+d[i][k];
}
