/*	Author : Rakesh Malik
 *	Date : 23.11.2010
 *	B.Sc. Computer Science 2nd Year
 *	sorting (Bubble sort, Insertion Sort, Selection Sort, Heap Sort, Merge Sort, Quick Sort, Radix Sort) (non-recursive)
 */


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"stack.h"

#define MAX 100				//List size
/*
void swap(int*,int*);
void bubble_sort(int[],size_t);
void selection_sort(int[],size_t);
void insertion_sort(int[],size_t);
int partition(int[],int,int);
void quick_sort(int[],int,int);
void merge(int[],int,int,int);
void merge_sort(int[],int);
int parent(int);
int left_child(int);
int right_child(int);
void create_heap(int[],int);
void heap_sort(int[],size_t);
void radix_sort(char*[],size_t);
*/
#include"bubble.h"
#include"insertion.h"
#include"selection.h"
#include"merge.h"
#include"quick.h"
#include"heap.h"
#include"radix.h"

int main(int argc,char *argv[])
{
	FILE* fp;
	char *v[MAX],filename[20];
	int i,n=0,list[MAX],choice;
	if(argc==2)
	{	
		fp=fopen(argv[1],"r");
		if(fp)
		{
			for(i=0;feof(fp)==0;i++)
				fscanf(fp,"%d",&list[i]);
			n=i-1;
			fclose(fp);
		}
	}
	while(1)
	{
		system("clear");
		printf("\nSort :\n");
		if(n>0)
		{
			printf("\nData : ");
			for(i=0;i<n;i++)
				printf("%d ",list[i]);
			printf("\n");
		}
		printf("\n1. Load List");
		printf("\n2. Modified Bubble Sort");
		printf("\n3. Insertion Sort");
		printf("\n4. Selection Sort");
		printf("\n5. Quick Sort");
		printf("\n6. Merge Sort");
		printf("\n7. Heap Sort");
		printf("\n8. Radix Sort");
		printf("\n0. Exit");
		printf("\n\tEnter your choice _");
		scanf("%d",&choice);
		system("clear");
		if(n<=0 && choice>1 && choice<8)
			fprintf(stderr,"\nError : Load data file");
		else switch(choice)
		{
			case 0:
				return 0;
			case 1:
				printf("\nEnter the filename : ");
				scanf("%s",filename);
				fp=fopen(filename,"r");
				if(fp)
				{
					for(i=0;feof(fp)==0;i++)
						fscanf(fp,"%d",&list[i]);
					n=i-1;
					fclose(fp);
				}
				else fprintf(stderr,"\nError : File read error");
				break;
			case 2:
				bubble_sort(list,n);
				getchar();getchar();
				break;
			case 3:
				selection_sort(list,n);
				getchar();getchar();
				break;
			case 4:
				insertion_sort(list,n);
				getchar();getchar();
				break;
			case 5:
				quick_sort(list,0,n-1);
				getchar();getchar();
				break;
			case 6:
				merge_sort(list,n);
				getchar();getchar();
				break;
			case 7:
				heap_sort(list,n);
				getchar();getchar();
				break;
			case 8:
				{
					int n=0;
					printf("\nEnter the filename : ");
					scanf("%s",filename);
					fp=fopen(filename,"r");
					if(fp)
					{
						for(i=0;feof(fp)==0;i++)
						{
							v[i]=(char*)calloc(50,1);
							fscanf(fp,"%s",v[i]);
						}
						n=i-1;
						fclose(fp);
						radix_sort(v,n);
						getchar();getchar();
					}
					else fprintf(stderr,"\nError : File read error");
				}
				break;
			default:
				fprintf(stderr,"\nError : Wrong choice");

		}
	}
}
