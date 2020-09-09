#include<stdio.h>
#include"graph.h"
#include"stack.h"

#define INF 99999

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
		if(TOP(open)==-1) 
			return 0;
	}
}
