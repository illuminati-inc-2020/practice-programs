#include<stdio.h>
#include"graph.h"
#include"dfs.h"

void kruskal(int G[10][10],int v,int T[10][10]);

int main(int argc,char* argv[])
{
	printf("Spanning Tree using Kruskal's Algo\n\n");
	int i,j,v,G[10][10],T[10][10];
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
	kruskal(G,v,T);
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

void kruskal(int G[10][10],int v,int T[10][10])
{
	int min,i,j,k,m,n;
	char Temp[10][10];
	for(i=0;i<v;i++)
		for(j=0;j<v;j++)
			if(i==j) Temp[i][j]=1;
			else Temp[i][j]=0;
	for(i=0;i<v;i++)
		for(j=0;j<v;j++)
			if(i==j) T[i][j]=0;
			else T[i][j]=INF;
	for(i=0;i<v-1;i++)
	{
		min=INF;
		for(j=0;j<v;j++)
			for(k=0;k<v;k++)
				if(G[j][k]<min && Temp[j][k]==0)
				{
					min=G[j][k];
					m=j,n=k;
				}
		if(!dfs(T,v,m,n))
			T[m][n]=T[n][m]=min;
		else i--;
		Temp[m][n]=Temp[n][m]=1;
	}
}

