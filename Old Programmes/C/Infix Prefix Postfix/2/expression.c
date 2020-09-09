#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

#include"stack.c"
#include"array.c"
#include"op.c"
#include"in2post.c"
#include"in2pre.c"
#include"posteval.c"

int main()
{
	char s[MAXSTACK],d[MAXSTACK];
	int choice=1;
	while(choice)
	{
		system("clear");
		printf("1. Infix to Prefix & Postfix conversion\n");
		printf("2. Prefix to Infix & Postfix conversion\n");
		printf("3. Postfix to Infix & Prefix conversion\n");
		printf("4. Infix Evaluation\n");
		printf("5. Prefix Evaluation\n");
		printf("6. Postfix Evaluation\n");
		printf("0. Exit\n");
		printf("Enter your choice_");
		scanf("%d",&choice);
		getchar();
		switch(choice)
		{
			case 1:
				printf("\nInfix :\n\n\t");
				scanf("%s",s);
				printf("\n\nPrefix :\n\n\t");
				printf("%s",in2pre(s));
				printf("\n\nPostfix :\n\n\t");
				printf("%s",in2post(s,d));
				break;
			case 2:
			case 3:
			case 5:
				printf("\n\t\tUnder construction");
				break;
			case 4:
				printf("\nInfix :\n\n\t");
				scanf("%[^\n]",s);
				printf("\n\n\t\t=%d",post_eval(in2post(s,d)));
				break;
			case 6:
				printf("\nPostfix :\n\n\t");
				scanf("%[^\n]",s);
				printf("\n\n\t\t=%d",post_eval(s));
				break;
			case 0:
				break;
			default:
				printf("\n\t\tWrong choice");
				break;
		}
		if(choice!=0) {getchar();getchar();}
	}
}
