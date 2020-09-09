#include "sort.h"

void quick_sort(int list[],int lb,int ub)		/*lb=lower bound,ub=upper bound*/
{
	int p;						/*p=position of pivot*/
	int stack[2*MAX],top=-1,i,n=ub-lb+1;
	printf("\nQUICK SORT\nData : ");
	for(i=0;i<n;i++)
		printf("%d ",list[i]);
	printf("\n[ ]\t: Current partition");
	printf("\n( )\t: Pivot of current partition\n\n");
	push(stack,&top,lb);
	push(stack,&top,ub);
	while(!underflow(stack,top))
	{
		ub=pop(stack,&top);
		lb=pop(stack,&top);
		p=partition(list,lb,ub);
		for(i=0;i<n;i++)
		{
			if(i==lb) printf("[");
			if(i==p) printf("(");
			printf("%d",list[i]);
			if(i==p) printf(")");
			if(i==ub) printf("]");
			printf("\t");
		}
		printf("\n");
		if(lb<p)
		{
			push(stack,&top,lb);
			push(stack,&top,p-1);
		}
		if(p<ub)
		{
			push(stack,&top,p+1);
			push(stack,&top,ub);
		}
	}
	printf("\nSorted data : ");
	for(i=0;i<n;i++)
		printf("%d ",list[i]);
	printf("\n\n");
}

int partition(int list[],int lb,int ub)		/*Partitions an array and returns the position of pivot*/
{
	int i=lb+1,j=ub,pivot=lb,temp;
	while(i<=j)
	{
		if(list[i]<list[pivot])
		{
			swap(&list[i],&list[pivot]);
			i++;
			pivot++;
		}
		else
		{
			swap(&list[i],&list[j]);
			j--;
		}
	}
	return pivot;
}
