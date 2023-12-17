#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct statement {
	char lhs[2];
	char rhs[30];
} statement;

int k = 0;
char temps[] = "pqrstuvwxyz";
statement statements1[30];
int n1 = 0;

typedef struct stack {
	int TOP;
	int SIZE;
	char *arr;
} stack;

typedef struct expression {
	char *infix;
	char *postfix;
} expression;

void push(stack *s, char x) {
	if(s->TOP >= s->SIZE - 1) {
		printf("Overflow!\n");
		exit(0);
	} else {
		s->arr[++s->TOP] = x;
	}
}

char pop(stack *s) {
	if(s->TOP == -1) {
		printf("Underflow!\n");
		exit(0);
	} else {
		char x = s->arr[s->TOP];
		s->TOP--;
		return x;
	}
}

int ISP(char X) {
	if(X == '+' || X == '-')
		return 2;
	else if(X == '*' || X == '/')
		return 4;
	else if(X >= '0' && X <= '9' || X >= 'a' && X<= 'z' || X >= 'A' && X<= 'Z')
		return 8;
	else if(X == '(')
		return 0;
}

int ICP(char X) {
	if(X == '+' || X == '-')
		return 1;
	else if(X == '*' || X == '/')
		return 3;
	else if(X >= '0' && X <= '9' || X >= 'a' && X<= 'z' || X >= 'A' && X<= 'Z')
		return 7;
	else if(X == '(')
		return 9;
	else if(X == ')')
		return 0;
}

void infix_to_postfix(expression *exp) {
	int i = 0, j = 0;
	stack s;
	
	s.TOP = -1;
	s.SIZE = strlen(exp->infix);
	s.arr = (char*) malloc(s.SIZE * sizeof(char));
	
	push(&s, '(');
	
	while(s.TOP > -1) {	
		char X = pop(&s);
		
		if(exp->infix[i] == '(') {
			push(&s, X);
			push(&s, exp->infix[i]);
		} else if(exp->infix[i] == ')') {
			while(X != '(')
			{
				exp->postfix[j] = X;
				X = pop(&s);
				j++;
			}
		} else if(exp->infix[i] >= 'a' && exp->infix[i] <= 'z' || exp->infix[i] >= 'A' && exp->infix[i] <= 'Z' || exp->infix[i] >= '0' && exp->infix[i] <= '9') {
			push(&s, X);
			exp->postfix[j] = exp->infix[i];
			j++;
		} else if(exp->infix[i] == '+' || exp->infix[i] == '-' || exp->infix[i] == '*' || exp->infix[i] == '/' || exp->infix[i] == '(' || exp->infix[i] == ')') {
			if(ISP(X) >= ICP(exp->infix[i])) {
				while(ISP(X) >=  ICP(exp->infix[i])) {
					exp->postfix[j] = X;
					X = pop(&s);
					j++;
				}
				push(&s, X);
				push(&s, exp->infix[i]);
			} else {
				push(&s, X);
				push(&s, exp->infix[i]);
			} 
		} else if(exp->infix[i] != ' ') {
			printf("Invalid statement!\n");
			exit(0);
		}
		
		i++;
	}
}

void icg(char c, char* str) {
	if(strlen(str) < 2) {
		statements1[n1].lhs[0] = c;
		statements1[n1].lhs[1] = '\0';
		
		statements1[n1].rhs[0] =  str[0];
		statements1[n1].rhs[1] = '\0';
		
		n1++;
		
		return;
	}
	
	int i = 0;
	char temp[2];
	
	while(i < strlen(str)) {
		if(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
			statements1[n1].rhs[0] = str[i - 2];
			statements1[n1].rhs[1] = str[i];
			statements1[n1].rhs[2] = str[i - 1];
			statements1[n1].rhs[3] = '\0';
			statements1[n1].lhs[0] = temps[k];
			statements1[n1].lhs[1] = '\0';
			n1++;
			
			str[i - 2] = temps[k++];
			
			for(int j = i - 1; j < strlen(str) - 2; j++) {
				str[j] = str[j + 2];
			}
			
			str[strlen(str) - 2] = '\0';
			i = -1;
		}
		
		i++;
	}
	
	statements1[n1].lhs[0] = c;
	statements1[n1].lhs[1] = '\0';
	
	statements1[n1].rhs[0] =  temps[k - 1];
	statements1[n1].rhs[1] = '\0';
	
	n1++;
}

void main() {
	int n;
	
	printf("Enter the number of statements: ");
	scanf("%d", &n);
	statement statements[n];
	
	printf("Enter the statements:\n");
	for(int i = 0; i < n; i++) {
		scanf("%s = %s", statements[i].lhs, statements[i].rhs);
	}
	
	expression exp;
	
	for(int i = 0; i < n; i++) {
		exp.infix = statements[i].rhs;
		exp.postfix = (char*) malloc(strlen(exp.infix) * sizeof(char));
		
		exp.infix[strlen(exp.infix)] = ')';
		
		infix_to_postfix(&exp);
		
		icg(statements[i].lhs[0], exp.postfix);
	}
	
	printf("\nIntermediate Code:\n");
	for(int i = 0; i < n1; i++) {
		printf("%s = %s\n", statements1[i].lhs, statements1[i].rhs);
	}
}
