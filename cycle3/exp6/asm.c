#include <stdio.h>
#include <string.h>

int regIndex = -1;
char registers[][3] = {"AX", "BX", "CX", "DX", "SP", "BP", "SI", "DI"};

typedef struct statement {
	char lhs[2];
	char rhs[4];
} statement;

void move(char a, char b) {
	regIndex++;
	printf("MOV %s, %c\n", registers[regIndex], b);
	printf("MOV %c, %s\n", a, registers[regIndex]);
	regIndex--;
}

void add(char a, char b, char c) {
	regIndex++;
	printf("MOV %s, %c\n", registers[regIndex], b);
	regIndex++;
	printf("MOV %s, %c\n", registers[regIndex], c);
	printf("ADD %s, %s\n", registers[regIndex - 1], registers[regIndex]);
	printf("MOV %c, %s\n", a, registers[regIndex - 1]);
	regIndex = regIndex - 2;
}

void sub(char a, char b, char c) {
	regIndex++;
	printf("MOV %s, %c\n", registers[regIndex], b);
	regIndex++;
	printf("MOV %s, %c\n", registers[regIndex], c);
	printf("SUB %s, %s\n", registers[regIndex - 1], registers[regIndex]);
	printf("MOV %c, %s\n", a, registers[regIndex - 1]);
	regIndex = regIndex - 2;
}

void mul(char a, char b, char c) {
	regIndex++;
	printf("MOV %s, %c\n", registers[regIndex], b);
	regIndex++;
	printf("MOV %s, %c\n", registers[regIndex], c);
	printf("MUL %s, %s\n", registers[regIndex - 1], registers[regIndex]);
	printf("MOV %c, %s\n", a, registers[regIndex - 1]);
	regIndex = regIndex - 2;
}

void div(char a, char b, char c) {
	regIndex++;
	printf("MOV %s, %c\n", registers[regIndex], b);
	regIndex++;
	printf("MOV %s, %c\n", registers[regIndex], c);
	printf("DIV %s, %s\n", registers[regIndex - 1], registers[regIndex]);
	printf("MOV %c, %s\n", a, registers[regIndex - 1]);
	regIndex = regIndex - 2;
}

void main() {
	int n;
	
	printf("Enter the number of statements in Intermediate Code: ");
	scanf("%d", &n);
	statement statements[n];
	
	printf("Enter the statements:\n");
	for(int i = 0; i < n; i++) {
		scanf("%s = %s", statements[i].lhs, statements[i].rhs);
	}
	
	printf("\nGenerated Code:\n");
	for(int i = 0; i < n; i++) {
		if(strlen(statements[i].rhs) == 1) {
			move(statements[i].lhs[0], statements[i].rhs[0]);	
		} else {
			switch(statements[i].rhs[1]) {
				case '+':
						add(statements[i].lhs[0], statements[i].rhs[0], statements[i].rhs[2]);
						break;
				case '-':
						sub(statements[i].lhs[0], statements[i].rhs[0], statements[i].rhs[2]);
						break;
				case '*':
						mul(statements[i].lhs[0], statements[i].rhs[0], statements[i].rhs[2]);
						break;
				case '/':
						div(statements[i].lhs[0], statements[i].rhs[0], statements[i].rhs[2]);
						break;
				default:
						printf("Invalid statement!\n");
						return;
			}
		}
	}
}
