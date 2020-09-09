#include <stdio.h>

#define MAXQUEUE 5
#include "macro_queue.h"

int main() {
	int s[MAXQUEUE];
	CREATEQUEUE(s);
	while(1) {
		system("cls");
		printf("QUEUE\n(size=5)\n\n1. Push\n2. Pop\n3. Display\n0. Exit\n");
		printf("Enter your Choice_");
		int choice=0, x, i;
		scanf("%d", &choice);
		printf("\n");
		switch(choice) {
		case 1:
			if(OVERFLOW(s))
				printf("Queue Full\n");
			else {
				printf("Enter a number : ");
				scanf("%d", &x);
				ENQUEUE(s, x);
				printf("%d inserted\n", x);
			}
			break;
		case 2:
			if(UNDERFLOW(s))
				printf("Queue Empty\n");
			else {
				x=DEQUEUE(s);
				printf("%d deleted\n", x);
			}
			break;
		case 3:
			if(s_top==-1)
				printf("Queue is empty");
			else {
				for(i=s_rear+1; i<=s_front; i++)
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