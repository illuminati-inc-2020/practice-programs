void merge_sort(int list[],int n)
{
	int i,j;
	int lb=0,ub=1,mid;			/*lb=lower bound
						  ub=upper bound
						  mid=(lb+ub)/2 */
	int len=2;				/*lenght of current subarray*/
	printf("\nMERGE SORT\nData : ");
	for(i=0;i<n;i++)
		printf("%d ",list[i]);
	printf("\n( )\t: Subarrays currently being merged\n\n");
	while(len/2<n)
	{
		ub=(lb+len-1>=n)?n-1:lb+len-1;
		mid=((lb*2+len-1)/2>=n)?n-1:(lb*2+len-1)/2;
		for(j=0;j<n;j++)
		{
			if(j==lb || j==mid+1) printf("(");
			printf("%d",list[j]);
			if(j==ub || j==mid) printf(")");
			printf("\t");
		}
		printf("\n",i);
		merge(list,lb,mid,ub);
		if(ub==n-1)
		{
			len*=2;
			lb=0;
		}
		else
			lb=ub+1;
	}
	printf("\nSorted data : ");
	for(i=0;i<n;i++)
		printf("%d ",list[i]);
	printf("\n\n");
}

void merge(int list[],int lb,int mid,int ub)	/*Merges two sorted list to one sorted list*/
{
	int temp[100],i,j,k=0,m;
	void merge(int list[],int lb,int mid,int ub);
	for(i=lb,j=mid+1;i<=mid&&j<=ub;)
		if(list[i]<list[j])
			temp[k++]=list[i++];
		else
			temp[k++]=list[j++];
	for(;i<=mid;i++)
		temp[k++]=list[i];
	for(;j<=ub;j++)
		temp[k++]=list[j];
	for(i=lb;i<=ub;i++)
		list[i]=temp[i-lb];
}
