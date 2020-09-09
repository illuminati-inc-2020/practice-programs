/* Assignment		:	5
 * Author		:	Rakesh Malik
 * Date			:	18.7.2011
 * Subject		:	Linear Search and Binary Search
 */

#include <stdio.h>

int LinearSearch(int[],int,int);
int Sorted(int[],int);
int BinarySearch(int[],int,int);

int main()
{
	int choice,key,n,i,A[100];
	printf("Enter number of data : ");
	scanf("%d",&n);
	printf("Enter data : ");
	for(i=0;i<n;i++)
		scanf("%d",&A[i]);
	printf("\nSEARCHING");
	printf("\n1. Linear Search");
	printf("\n2. Binary Search");
	printf("\n0. Exit");
	while(1)
	{
		printf("\nEnter your choice_");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				printf("\nEnter key :");
				scanf("%d",&key);
				if(LinearSearch(A,n,key))
					printf("\nData found");
				else
					printf("\nData not found");
				break;
			case 2:
				if(Sorted(A,n))
				{
					printf("\nEnter key :");
					scanf("%d",&key);
					if(BinarySearch(A,n,key))
						printf("\nData found");
					else
						printf("\nData not found");
				}
				else
					printf("\nData must be sorted in ascending order");
				break;
			default :
				return 0;
		}
	}
}

int LinearSearch(int A[],int n,int key)
{
	int i;
	for(i=0;i<n;i++)
		if(A[i]==key)
			return 1;
	return 0;
}

int Sorted(int A[],int n)
{
	int i;
	for(i=1;i<n;i++)
		if(A[i]>A[i+1])
			return 0;
	return 1;
}

int BinarySearch(int A[],int n,int key)
{
	int lb,ub,mid;
	lb=0;
	ub=n-1;
	while(lb<ub)
	{
		mid=(lb+ub)/2;
		if(A[mid]==key)		return 1;
		else if(key<A[mid])	ub=mid-1;
		else			lb=mid+1;
	}
	if(A[(lb+ub)/2]==key)		return 1;
	else				return 0;
}
