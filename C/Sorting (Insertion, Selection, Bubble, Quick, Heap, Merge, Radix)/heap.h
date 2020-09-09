#include "sort.h"

int parent(int index)			/*Returns index of an elemnt of heap*/
{
	return (index-1)/2;
}

int left_child(int index)		/*Returns index of left child of an element of heap*/
{
	return index*2+1;
}

int right_child(int index)		/*Returns index of right child of an element of heap*/
{
	return index*2+2;
}

void create_heap(int heap[],int n)	/*Makes an array in 'heap' a heap of size 'n'*/
{
	int i,j,k;
	for(i=1;i<n;i++)
	{
		for(j=i;j!=0;j=parent(j))
		{
			if(heap[j]>heap[parent(j)])
				swap(&heap[j],&heap[parent(j)]);
			else break;
		}
		for(k=0;k<n;k++)
		{
			printf("%d ",heap[k]);
			if(k==i) printf("|");
		}
		printf("\n");
	}
}

void heap_sort(int list[],size_t n)
{
	int i,j,k;
	printf("\nHEAP SORT\nData : ");
	for(i=0;i<n;i++)
		printf("%d ",list[i]);
	/* CREATING HEAP */
	printf("\n\nCreating heap :\n");
	printf("|\t: at left heaped data,at right unheaped data\n\n");
	create_heap(list,n);
	/* DELETING HEAP */
	printf("\nSorting :\n");
	printf("|\t: at left unsorted data,at right sorted data\n\n");
	for(i=n-1;i>=1;i--)
	{
		swap(&list[0],&list[i]);
		for(k=0;k<n;k++)
		{
			if(k==i)printf("|");
			printf("%d ",list[k]);
		}
		printf("\n");
		for(j=0;j<i;)
		{
			if(left_child(j)<i && list[left_child(j)]>=list[j] 
					&& ((right_child(j)<i) ? list[left_child(j)]>=list[right_child(j)] : 1))
			{
				swap(&list[j],&list[left_child(j)]);
				j=left_child(j);
			}
			else if(right_child(j)<i && list[right_child(j)]>=list[j] 
					&& ((left_child(j)<i) ? list[right_child(j)]>=list[left_child(j)] : 1))
			{
				swap(&list[j],&list[right_child(j)]);
				j=right_child(j);
			}
			else break;
			for(k=0;k<n;k++)
			{
				if(k==i)printf("|");
				printf("%d ",list[k]);
			}
			printf("\n\n");
		}
	}
	printf("\n\nSorted data : ");
	for(i=0;i<n;i++)
		printf("%d ",list[i]);
	printf("\n\n");
}
