#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
int top=-1;
char stack[50];
int precedence(char operator)
{
	switch (operator) {
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case '^':
		return 3;
	default:
		return -1;
	}
}
void push(char ch)
{
	top++;
	stack[top]=ch;
}
char pop()
{
	return stack[top--];
}	
int isOperator(char ch)
{
	return (ch == '+' || ch == '-' || ch == '*' || ch == '/'
			|| ch == '^');
}
char* infixToPostfix(char* infix)
{
	int i, j;
	int len = strlen(infix);
	char* postfix = malloc(len);
	char stack[100];
	int top = -1;

	for (i = 0, j = 0; i < len; i++) {
	
		if (isalnum(infix[i])) {
			postfix[j++] = infix[i];
		}
		else if (infix[i] == '(') {
			stack[++top] = infix[i];
		}
	
		else if (infix[i] == ')') {
			while (top > -1 && stack[top] != '(')
				postfix[j++] = stack[top--];
			
				top--;
		}
		else if (isOperator(infix[i])) {
			while (top > -1 && precedence(stack[top])>= precedence(infix[i]))
				postfix[j++] = stack[top--];
			stack[++top] = infix[i];
		}
	}

	while (top > -1) {
		if (stack[top] == '(') {
			return "Invalid Expression";
		}
		postfix[j++] = stack[top--];
	}
	postfix[j] = '\0';
	return postfix;
}

int main()
{
	char temp[]={'p','q','r','s','t','u','v','w'};
	char lhs[10],rhs[100];
	printf("Enter the LHS:");
	scanf("%s",lhs);
	printf("Enter the RHS:");
	scanf("%s",rhs);
	char *postfix = infixToPostfix(rhs);
	printf("%s\n", postfix);
	int n=strlen(postfix);
	int j=0;
	for(int i=0;i<n;i++)
	{
		if(!isOperator(postfix[i]))
		{
			push(postfix[i]);
		}
		else
		{
			char a=pop();
			char b=pop();
			printf("%c=%c %c %c\n",temp[j],b,postfix[i],a);
			push(temp[j++]);
		}
				
	}
	printf("%s=%c\n",lhs,pop());
	return 0;
}