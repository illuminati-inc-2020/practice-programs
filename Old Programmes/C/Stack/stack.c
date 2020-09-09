#include <stdio.h>

#define MAXSTACK 5
#include "macro_stack.h"

int main() {
	int s[MAXSTACK];
	CREATESTACK(s);
	while(1) {
		system("cls");
		printf("STACK\n(size=5)\n\n1. Push\n2. Pop\n3. Display\n0. Exit\n");
		printf("Enter your Choice_");
		int choice=0, x, i;
		scanf("%d", &choice);
		printf("\n");
		switch(choice) {
		case 1:
			if(OVERFLOW(s))
				printf("Stack Overflow\n");
			else {
				printf("Enter a number : ");
				scanf("%d", &x);
				PUSH(s, x);
				printf("%d pushed\n", x);
			}
			break;
		case 2:
			if(UNDERFLOW(s))
				printf("Stack Underflow\n");
			else {
				x=POP(s);
				printf("%d popped\n", x);
			}
			break;
		case 3:
			if(s_top==-1)
				printf("Stack is empty");
			else {
				for(i=0; i<=s_top; i++)
					printf("%d ", s[i]);
				printf("\n");
			}
			break;
		case 0:
			return 0;
		}
		printf("\nPress any key...\n");
		getchar();
		getchar();
	}
}