int post_eval(char*);

int post_eval(char *s)
{
	char stk[MAXSTACK];
	int i,j,stktop=0,num,temp;
	for(i=0;s[i];i++)
	{
		if(isdigit(s[i]))
		{
			for(num=0;isdigit(s[i]);i++)
				num=num*10+s[i]-48;
			i--;
			push(stk,&stktop,&num,sizeof(num));
		}
		else if(isoperator(s[i]))
		{
			temp=operate(*(int*)pop(stk,&stktop,sizeof(int)),s[i],*(int*)pop(stk,&stktop,sizeof(int)));
			push(stk,&stktop,&temp,sizeof(int));
		}
	}
	return *(int*)pop(stk,&stktop,sizeof(int));
}
