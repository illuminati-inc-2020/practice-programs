#include<stdio.h>
#include"graph.h"

#define INF 99999

int belongs(int set[],int size,int e);
int dijkstra(int G[10][10],int v,int v1,int v2, int[]);

int main(int argc,char* argv[]) {
	int i, j, v, v1, v2, G[10][10], came_from[10];
	printf("Shortest Distance using Dijkstra's Algo\n\n");
	if(argc<=1) {
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
	for(i=0;i<v;i++) {
		printf("v%d\t", i);
		for(j=0;j<v;j++)
			if(G[i][j]==INF)
				printf("INF\t");
			else
				printf("%d\t",G[i][j]);
		printf("\n");
	}
	printf("\nEnter first vertex : ");	
	scanf("%d",&v1);
	printf("Enter second vertex : ");	
	scanf("%d",&v2);
	if(v1>=0 && v1<v && v2>=0 && v2<v) {
		printf("\nShortest distance : %d\n",dijkstra(G,v,v1,v2, came_from));
		printf("Shortest path : ");
		for(i=v2; i!=v1; i=came_from[i])
			printf("v%d <- ", i);
		printf("v%d\n", v1);
	} else
		fprintf(stderr,"Error!\n");
}

int belongs(int set[],int size,int e) {
	int j;
	for(j=0;j<=size;j++)
		if(set[j]==e)
			return 1;
	return 0;
}

int dijkstra(int G[10][10],int v,int v1,int v2, int came_from[10]) {
	int i, j, P[10], S[10], scount=-1;
	for(i=0;i<v;i++)
		P[i]=INF;
	P[v1]=0;
	S[++scount]=v1;
	while(S[scount]!=v2) {
		int min=INF;
		scount++;
		for(i=0;i<v;i++)
			if(!belongs(S,scount-2,i) && P[i]<min) {
				min=P[i];
				S[scount]=i;
			}
		for(i=0;i<v;i++)
			if(!belongs(S,scount,i) && min+G[S[scount]][i]<P[i]) {
				P[i]=min+G[S[scount]][i];
				came_from[i]=S[scount];
				printf("%d<-%d\n", i, S[scount]);
			}
	}
	return P[v2];
}
