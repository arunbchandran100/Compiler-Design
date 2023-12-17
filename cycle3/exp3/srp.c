#include <stdio.h>
#include <string.h>

#define MAX 20

typedef struct stack {
	int top;
	char arr[MAX];
} stack;

typedef struct prod {
	char lhs[MAX];
	char rhs[MAX];
} prod;

char terminals[10];
int t = 0;

void initStack(stack* st) {
	st->top = -1;
}

void push(stack* st, char c) {
	st->arr[++st->top] = c;
}

char pop(stack* st) {
	char c = st->arr[st->top--];
	return c;
}

int checkAccept(stack* st, char c, char start) {
	if(st->arr[st->top] == start && st->arr[st->top - 1] == '$' && c == '$')
		return 1;
	return 0;
}

void main() {
	int n;
	prod grammar[30];
	
	printf("Enter the number of productions: ");
	scanf("%d", &n);
	
	printf("\nEnter the productions (Eg: S = aBc):\n");
	for(int i = 0; i < n; i++) {
		scanf("%s = %s", grammar[i].lhs, grammar[i].rhs);
	}
	
	printf("\nNB: Due to Shift-Reduce and Reduce-Reduce conflicts, the outputs may be incorrect.\n");
	
	while(1) {
		stack st;
		char input[20];
		int ip = 0;
		printf("\nEnter the input string: ");
		scanf("%s", input);

		initStack(&st);

		push(&st, '$');

		input[strlen(input) + 1] = '\0';
		input[strlen(input)] = '$';
		
		char c;
		char str[MAX];
		int ip1 = -1, flag = 0, flag1 = 0;

		while(1) {
			while(1) {
				c = pop(&st);
				
				if(c == '$') {
					push(&st, c);
					
					for(int i = 0; i <= ip1; i++) {
						push(&st, str[i]);
					}
					
					ip1 = -1;
					c = input[ip++];
					
					if(c == '$') {
						// REJECT
						
						printf("Rejected!\n");
						flag1 = 1;
					} else {
						// SHIFT
						
						push(&st, c);
					}
					
					break;
				} else {
					ip1++;
					str[ip1 + 1] = '\0';
					
					for(int i = ip1; i > 0; i--) {
						str[i] = str[i - 1];			
					}
					
					str[0] = c;
					
					flag = 0;
					
					for(int i = 0; i < n; i++) {
						if(!strcmp(grammar[i].rhs, str)) {
							// REDUCE
							
							push(&st, grammar[i].lhs[0]);
							ip1 = -1;
							flag = 1;
							break;
						}
					}
					
					if(flag) {
						break;
					}
				}
			}
			
			if(flag1) break;

			if(checkAccept(&st, input[ip], grammar[0].lhs[0])) {
				// ACCEPT
				
				printf("Accepted.\n");
				break;
			}
		}
	}
}
