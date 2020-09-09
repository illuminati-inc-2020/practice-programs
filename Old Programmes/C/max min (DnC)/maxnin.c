#include <stdio.h>

void maxmin(int[], int, int , int*, int*);

int comaparison_count=0;

int main() {
	int n;
	printf("Minimum and Maximum using Divide and Conquer\n\n");
	printf("Enter number of elements in set : ");
	scanf("%d", &n);
	int a[n], max=0, min=0, i;
	printf("\nEnter the integers of set : ");
	for(i=0; i<n; i++)
		scanf("%d", &a[i]);
	maxmin(a, 0, n-1, &max, &min);
	printf("\nMinimum = %d\nMaximum = %d\n", max, min);
	printf("\nNumber of comparisons taken %d\n\n", comaparison_count);
	return 0;
}

void maxmin(int a[], int lb, int ub, int *max, int *min) {
	if(ub==lb) {
		*max=*min=a[lb];
	} else if(lb==ub-1) {
		if(a[lb]<a[ub]) {
			*max=a[ub];
			*min=a[lb];
		} else {
			*max=a[lb];
			*min=a[ub];
		}
		comaparison_count++;
	} else if(lb<ub) {
		int max1, min1, mid=(lb+ub)/2;
		maxmin(a, lb, mid, max, min);
		maxmin(a, mid+1, ub, &max1, &min1);
		if(max1>*max)
			*max=max1;
		if(min1<*min)
			*min=min1;
		comaparison_count+=2;
	}
}