#include<stdio.h>
#include"graph.h"

#define INF 99999

typedef struct e
{
	int u,v;
}edge;

int belongs(int set[],int size,int e);
void prim(int G[10][10],int v,int T[10][10]);

int main(int argc,char* argv[])
{
	int i,j,v,G[10][10],T[10][10];
	printf("Spanning Tree using Prim's Algo\n\n");
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
	prim(G,v,T);
	printf("\nSpanning Tree : \n\n");
	for(i=0;i<v;i++)
		printf("\tv%d", i);
	printf("\n");
	for(i=0;i<v;i++)
	{
		printf("v%d\t", i);
		for(j=0;j<v;j++)
			if(T[i][j]==INF)
				printf("INF\t");
			else
				printf("%d\t",T[i][j]);
		printf("\n");
	}
}

void prim(int G[10][10],int v,int T[10][10])
{
	int min,B[10],Bcnt=-1,i,j,k;
	edge e;
	for(i=0;i<v;i++)
		for(j=0;j<v;j++)
			if(i==j) T[i][j]=0;
			else T[i][j]=INF;
	B[++Bcnt]=0;
	for(k=0;k<v-1;k++)
	{
		min=INF;
		for(i=0;i<v;i++)
			for(j=0;j<v;j++)
				if(G[i][j]<min && belongs(B,Bcnt,i) && !belongs(B,Bcnt,j))
				{
					min=G[i][j];
					e.u=i;
					e.v=j;
				}
		T[e.u][e.v]=T[e.v][e.u]=min;
		B[++Bcnt]=e.v;
	}
}

int belongs(int set[],int size,int e)
{
	int j;
	for(j=0;j<=size;j++)
		if(set[j]==e)
			return 1;
	return 0;
}
