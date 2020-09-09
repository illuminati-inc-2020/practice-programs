#define MAX 10

typedef struct Stack
{
	int data[MAX],top;
}Stack;

void CreateStack(Stack *s)
{
	s->top=-1;
}

int StackUnderflow(Stack s)
{
	if(s.top<=-1)
		return 1;
	else
		return 0;
}

int StackOverflow(Stack s)
{
	if(s.top>=MAX)
		return 1;
	else
		return 0;
}
int Push(Stack *s,int data)
{
	if(!StackOverflow(*s))
	{
		s->data[++s->top]=data;
		return 1;
	}
	else
		return 0;
}

int Pop(Stack *s)
{
	if(!StackUnderflow(*s))
		return s->data[s->top--];
	else
		return 0;
}

int DisplayStack(Stack s)
{
	int i;
	for(i=0;i<=s.top;i++)
		printf("%d ",s.data[i]);
}
