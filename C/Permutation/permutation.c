#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void perm(char c);
int isvalid(char c,int count);

int count=0,len,top=-1;
char **per;
char num[20],p[20];

int main()
{
	int i;
	per=(char**)calloc(100,sizeof(char*));
	system("cls");
	printf("Enter a number :   ");
	scanf("%s",num);
	len=strlen(num);
	for(i=0;i<len;i++)
		perm(num[i]);
	printf("\nPermutation:\n");
	for(i=0;i<=top;i++)
		printf("%s,",per[i]);
	printf("\n\n\n");
}

void perm(char c)
{
	int i,flag=1;
	p[count]=c;
	count++;
	if(count>=len)
	{
		for(i=0;i<=top;i++)
			if(!strncmp(per[i],p,len))
				flag=0;
		if(flag==1)
		{
			if(top%100==0)
				per=(char**)realloc(per,sizeof(char*)*((top/100)+1)*100);
			top++;
			per[top]=(char*)calloc(len,sizeof(char));
			strncpy(per[top],p,len);
		}
		flag=1;
	}
	else
		for(i=0;i<len;i++)
			if(isvalid(num[i],count))
				perm(num[i]);
	count--;
}

int isvalid(char c,int count)
{
	int i,f=0;
	for(i=0;i<len;i++)
		if(num[i]==c)
			f++;
	for(i=0;i<count;i++)
		if(p[i]==c)
			f--;
	if(f>0) return 1;
	return 0;
}
