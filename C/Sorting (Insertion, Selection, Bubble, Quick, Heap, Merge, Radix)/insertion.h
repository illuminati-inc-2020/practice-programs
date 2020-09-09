#include "sort.h"

void insertion_sort(int list[],size_t n)
{
	int fu;				/*fu=index of first unsorted element*/
	int temp;
	int index;			/*index=reative position for list[fu] in sorted part*/
	int flag;			/*flag=1 indicates that correct index is found*/
	int i;				
	printf("\nINSERTION SORT\nData : ");
	for(i=0;i<n;i++)
		printf("%d ",list[i]);
	printf("\n*\t: Position where first unsorted data is to be inserted");
	printf("\n[ ]\t: First unsorted data \n\n");
	for(fu=1;fu<n;fu++)
	{
		flag=0;
		/*finding relative position for first unsorted element*/
		for(index=0;index<fu;index++)
			if(list[index]>list[fu])
			{
				flag=1;
				break;
			}
		for(i=0;i<n;i++)
		{
			if(i==index) printf("  *");
			printf("\t");
			if(i==fu) putchar('[');
			printf("%d",list[i]);
			if(i==fu) putchar(']');
		}
		printf("\n");
		if(flag==1)
		{
			temp=list[fu];
			/*shifting*/
			for(i=fu-1;i>=index;i--)
				list[i+1]=list[i];
			list[index]=temp;
		}
	}
	printf("\nSorted data : ");
	for(i=0;i<n;i++)
		printf("%d ",list[i]);
	printf("\n\n");
}
