#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct statement {
	char lhs[2];
	char rhs[30];
} statement;

typedef struct map {
	char c;
	char val[8];
} map;

map m[100];
int k = 0;

int isConstant(char str[]) {
	for(int i = 0; i < strlen(str); i++) {
		if(str[i] == '-') {
			if(i != 0)
				return 0;
		} else if(str[i] < '0' || str[i] > '9')
			return 0;
	}
	
	return 1;
}

int mapContains(char c) {
	for(int i = 0; i < k; i++) {
		if(m[i].c == c)
			return 1;
	}
	
	return 0;
}

void mapAdd(char c, char* val) {
	m[k].c = c;
	strcpy(m[k].val, val);
	k++;
}

char* mapGet(char c) {
	for(int i = 0; i < k; i++) {
		if(m[i].c == c)
			return m[i].val;
	}
}

void propogate(char rhs[]) {
	for(int i = 0; i < strlen(rhs); i++) {
		if(mapContains(rhs[i])) {
			char str[8];
			strcpy(str, mapGet(rhs[i]));
			
			for(int j = strlen(rhs) + strlen(str) - 1; j > i; j--) {
				rhs[j] = rhs[j - strlen(str) + 1];
			}
			
			for(int j = 0; j < strlen(str); j++) {
				rhs[i + j] = str[j];
			}
		}
	}
}

void main() {
	int n;
	
	printf("Enter the number of statements: ");
	scanf("%d", &n);
	statement statements[n];
	
	printf("Enter the statements:\n");
	for(int i = 0; i < n; i++) {
		scanf("%s = %s", statements[i].lhs, statements[i].rhs);
		
		if(isConstant(statements[i].rhs)) {
			mapAdd(statements[i].lhs[0], statements[i].rhs);
		}
		
		propogate(statements[i].rhs);
	}
	
	printf("\nAfter Constant Propogation\n");
	for(int i = 0; i < n; i++) {
		printf("%s = %s\n", statements[i].lhs, statements[i].rhs);
	}
}
