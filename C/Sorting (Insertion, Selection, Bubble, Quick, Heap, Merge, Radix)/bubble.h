#include "sort.h"

void bubble_sort(int list[],size_t n)
{
	int i,j,k,flag=0;				/*flag=1 when list is sorted*/
	printf("\nBUBBLE SORT\nData : ");
	for(i=0;i<n;i++)
		printf("%d ",list[i]);
	printf("\n[ ]\t: Elements checked if they are to be swapped\n\n");
	for(i=0;i<n-1;i++)
	{
		flag=0;
		printf("loop %d:\n",i+1);
		for(j=0;j<n-i-1;j++)
		{
			putchar('\t');
			for(k=0;k<n;k++)
			{
				if(k==j || k==j+1) putchar('[');
				printf("%d",list[k]);
				if(k==j || k==j+1) putchar(']');
				printf("\t");
			}
			if(list[j]>list[j+1])
			{
				printf("\t%d, %d swapped",list[j], list[j+1]);
				swap(&list[j],&list[j+1]);
				flag=1;
			}
			putchar('\n');
		}
		if(flag==0) break;
	}
	printf("\nSorted data : ");
	for(i=0;i<n;i++)
		printf("%d ",list[i]);
	printf("\n\n");
}
