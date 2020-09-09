#include "sort.h"

void selection_sort(int list[],size_t n)
{
	int index,min,fu,k;			/*fu=index of first unsorted element
						  min=smallest unsorted element
						  index=index of min*/
	printf("\nSELECTION SORT\nData : ");
	for(k=0;k<n;k++)
		printf("%d ",list[k]);
	printf("\n[ ]\t: First unsorted element");
	printf("\n( )\t: The element to swapped with first unsorted element\n\n");
	for(fu=0;fu<n-1;fu++)
	{
		index=fu;
		min=list[index];
		/*finding minimum unsorted element*/
		for(k=index+1;k<n;k++)
			if(list[k]<min)
			{
				min=list[k];
				index=k;
			}
		for(k=0;k<n;k++)
		{
			if(k==fu) putchar('[');
			if(k==index) putchar('(');
			printf("%d",list[k]);
			if(k==index) putchar(')');
			if(k==fu) putchar(']');
			printf("\t");
		}
		printf("\t\t%d, %d swapped\n",list[fu],list[index]);
		swap(&list[index],&list[fu]);
	}
	printf("\nSorted data : ");
	for(k=0;k<n;k++)
		printf("%d ",list[k]);
	printf("\n\n");
}
