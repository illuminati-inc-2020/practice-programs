/**
 * Author			:	Rakesh Malik
 * Date				:	11/10/2011
 * Subject			:	Generic Quick Sort
 * Assignment no.		:	6
 */

#include <iostream>

using namespace std;

template <class DT>
int partition(DT *list,int size) {
	int pivot=0;
	for(int i=1,j=size-1;i<=j;) {
		if(list[i]<list[pivot]) {
			DT temp=list[i];
			list[i]=list[pivot];
			list[pivot]=temp;
			i++;
			pivot++;
		}else {
			DT temp=list[i];
			list[i]=list[j];
			list[j]=temp;
			j--;
		}
	}
	return pivot;
}
template <class DT>
void quicksort(DT *list,int size) {
	if(size>=1) {
		int pivot=partition(list,size);
		quicksort(list,pivot);
		quicksort(list+pivot+1,size-pivot-1);
	}
}

main() {
	int listi[]={10,3,6,1,2,8,4,5,3,7};
	quicksort(listi,10);
	for(int i=0;i<10;i++)
		cout<<listi[i]<<" ";
	cout<<endl;
	string lists[]={"Keyboard","Mouse","Monitor","CPU","Harddisk"};
	quicksort(lists,5);
	for(int i=0;i<5;i++)
		cout<<lists[i]<<" ";
	cout<<endl;
}
