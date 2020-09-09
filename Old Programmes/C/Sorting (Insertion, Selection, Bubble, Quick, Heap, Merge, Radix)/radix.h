void radix_sort(char* list[],size_t n)
{
	int i,j,k;
	int maxlen=0;				/* maxlen=legth of longest string*/
	int len=0;				/* 'len' is used for calculating length of strings*/
	int index;				/* index of string with smallest character of current radix*/
	int min;				/* smallest unsorted character of current radix*/
	int fu;					/* fu=position of first unsorted string according to current radix*/
	char *temp;				
	printf("\nRADIX SORT\nData : ");
	for(j=0;j<n;j++)
		printf("%s ",list[j]);
	printf("\n[ ]\t: Character at current radix position\n\n");
	for(i=0;i<n;i++)
	{
		len=strlen(list[i]);
		maxlen=(len>maxlen)?len:maxlen;
	}
	for(i=maxlen-1;i>=0;i--)
	{
		for(fu=0;fu<n-1;fu++)
		{
			/*finding smallest unsorted character*/
			for(index=fu,min=0xFF,j=index;j<n;j++)	
				if(list[j][i]<min)
					min=list[index=j][i];
			temp=list[index];
			/*shifting*/
			for(j=index-1;j>=fu;j--)	
				list[j+1]=list[j];
			list[fu]=temp;
		}
		printf("Current radix position : %d\n",i);
		for(k=0;k<n;k++)
			printf("%-*.*s[%c]%-*.*s\n",i,i,list[k],(list[k][i])?list[k][i]:' ',maxlen-i,maxlen-i,list[k]+i+1);
		printf("\n");
	}
	printf("\n\nSorted data : ");
	for(i=0;i<n;i++)
		printf("%s ",list[i]);
	printf("\n");
}
