#include <stdio.h>
#include <string.h>

typedef struct prod {
	char lhs[10];
	char rhs[10];
} prod;

char input[30];
int ip = 0;

int E();
int Edash();
int T();
int Tdash();
int F();
void advance();

int E() {
	if(T()) {
		if(Edash()) {
			return 1;
		} else return 0;
	} else return 0;
}

int Edash() {
	if(input[ip] == '+') {
		advance();
		
		if(T()) {
			if(Edash()) {
				return 1;
			} else return 0;
		} else return 0;
	} else return 1;
}

int T() {
	if(F()) {
		if(Tdash()) {
			return 1;
		} else return 0;
	} else return 0;
}

int Tdash() {
	if(input[ip] == '*') {
		advance();
		
		if(F()) {
			if(Tdash()) {
				return 1;
			} else return 0;
		} else return 0;
	} else return 1;
}

int F() {
	if(input[ip] == '(') {
		advance();
		
		if(E()) {
			if(input[ip] == ')') {
				advance();
				
				return 1;
			} else return 0;
		} else return 0;
	} else if(input[ip] == 'i') {
		advance();
		
		return 1;
	} else return 0;
}

void advance() {
	ip++;
}

void main() {
	printf("Enter input string: ");
	scanf("%s", input);
	
	if(E() && ip == strlen(input)) printf("Accepted.\n");
	else printf("Rejected!\n");
}

