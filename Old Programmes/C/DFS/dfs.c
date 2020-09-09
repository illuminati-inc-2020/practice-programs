#include<stdio.h>
#include"graph.h"
#include"stack.h"

#define INF 99999

int dfs(int G[10][10],int v,int v1,int v2);

int main(int argc,char* argv[])
{
	int i, j, v1, v2, v, G[10][10];
	printf("Depth First Search (DFS)\n\n");
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
			 printf("%d\t",G[i][j]);
		printf("\n");
	}
	printf("\nEnter starting vertex : ");
	scanf("%d",&v1);
	printf("Enter vertex to be searched : ");
	scanf("%d",&v2);
	printf("\nVertex v%d %sfound from vertex v%d\n",v2, dfs(G,v,v1,v2)?"":"not ", v1);
}

int dfs(int G[10][10],int v,int v1,int v2)
{
	int i,j,temp,flag;
	int open[MAXSTACK],close[MAXSTACK];
	CREATESTACK(open);
	CREATESTACK(close);
	PUSH(open,v1);
	while(1)
	{
		temp=POP(open);
		for(i=0;i<v;i++)
			if(G[temp][i]!=0 && G[temp][i]!=INF)
			{
				flag=1;
				for(j=0;j<=TOP(open);j++)
					if(open[j]==i)
						flag=0;
				for(j=0;j<=TOP(close);j++)
					if(close[j]==i)
						flag=0;
				if(flag==1)
					PUSH(open,i);
			}
		PUSH(close,temp);
		for(j=0;j<=TOP(open);j++)
			if(open[j]==v2)
				return 1;
		for(j=0;j<=TOP(close);j++)
			if(close[j]==v2)
				return 1;
		if(UNDERFLOW(open)) 
			return 0;
	}
}
