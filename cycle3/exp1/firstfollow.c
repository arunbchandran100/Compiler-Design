#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct prod {
	char lhs[20];
	char rhs[20];
} prod;

typedef struct firstStruct {
	char arr[10];
	int count;
} firstStruct;

typedef struct followStruct {
	char arr[10];
	int count;
} followStruct;

int n;
prod grammar[50];
char temps[] = "PQRUVWXYZ";
int tempIndex = 0;

int contains(firstStruct* f, char c) {
	for(int i = 0; i < f->count; i++) {
		if(f->arr[i] == c)
			return 1;
	}
	
	return 0;
}

firstStruct* first(char c) {
	firstStruct* f = (firstStruct*) malloc(sizeof(firstStruct));
	f->count = 0;
	int flag;
	
	for(int i = 0; i < n; i++) {
		if(grammar[i].lhs[0] == c) {
			if((grammar[i].rhs[0] >= 'A' && grammar[i].rhs[0] <= 'Z') || grammar[i].rhs[0] == 'e') { // RHS starts with non-terminal
				for(int j = 0; j < strlen(grammar[i].rhs); j++) {
					if(j != 0 && (grammar[i].rhs[j] < 'A' || grammar[i].rhs[j] >'Z')) {
						f->arr[f->count++] = grammar[i].rhs[j];
						break;
					}
					
					if(grammar[i].rhs[j] != 'e') {
						firstStruct* f1 = first(grammar[i].rhs[j]);
					
						if(contains(f1, 'e')) {
							for(int k = 0; k < f1->count; k++) {
								if(f1->arr[k] == 'e')
									continue;
								
								flag = 0;
								
								for(int l = 0; l < f->count; l++) {
									if(f->arr[l] == f1->arr[k]) {
										flag = 1;
									}
								}
								
								if(!flag)
									f->arr[f->count++] = f1->arr[k];
							}
							
							if(grammar[i].rhs[j + 1] == '\0') {
								f->arr[f->count++] = 'e';
								break;
							}
							
							continue;
						} else {
							for(int k = 0; k < f1->count; k++) {
								flag = 0;
								
								for(int l = 0; l < f->count; l++) {
									if(f->arr[l] == f1->arr[k]) {
										flag = 1;
									}
								}
								
								if(!flag)
									f->arr[f->count++] = f1->arr[k];
							}
							
							break;
						}
					} else {
						if(grammar[i].rhs[j + 1] == '\0') {
							f->arr[f->count++] = 'e';
							break;
						}
					}
				}
			} else { // RHS starts with terminal
				flag = 0;
				for(int j = 0; j < f->count; j++) {
					if(f->arr[j] == grammar[i].rhs[0]) {
						flag = 1;
					}
				}
				
				if(!flag)
					f->arr[f->count++] = grammar[i].rhs[0];
			}
		}
	}

	return f;
}

followStruct* follow(char c) {
	followStruct* f = (followStruct*) malloc(sizeof(followStruct));
	int flag;
	
	if(grammar[0].lhs[0] == c) {
		f->arr[f->count++] = '$';
	}
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < strlen(grammar[i].rhs); j++) {
			flag = 0;
			
			if(grammar[i].rhs[j] == c) {
				if(grammar[i].rhs[j + 1] == '\0') {
					if(grammar[i].lhs[0] == c)
						break;
					
					followStruct* f2 = follow(grammar[i].lhs[0]);
					
					for(int k = 0; k < f2->count; k++) {
						flag = 0;
						
						for(int l = 0; l < f->count; l++) {
							if(f->arr[l] == f2->arr[k]) {
								flag = 1;
							}
						}
						
						if(!flag) {
							f->arr[f->count++] = f2->arr[k];
						}
					}
				} else if(grammar[i].rhs[j + 1] >= 'A' && grammar[i].rhs[j + 1] <= 'Z') {
					firstStruct* f1 = first(grammar[i].rhs[j + 1]);
					
					int m = 2;
					
					while(grammar[i].rhs[j + m] != '\0' && contains(f1, 'e')) {
						for(int k = 0; k < f1->count; k++) {
							if(f1->arr[k] == 'e')
								continue;
							
							flag = 0;
							
							for(int l = 0; l < f->count; l++) {
								if(f->arr[l] == f1->arr[k]) {
									flag = 1;
								}
							}
							
							if(!flag) {
								f->arr[f->count++] = f1->arr[k];
							}
						}
						
						flag = 0;
						
						if(grammar[i].rhs[j + m] >= 'A' && grammar[i].rhs[j + m] <= 'Z') {
							f1 = first(grammar[i].rhs[j + m]);
							m++;
						} else {
							f->arr[f->count++] = grammar[i].rhs[j + m];
							flag = 1;
							break;
						}
					}
					
					if(!flag) {
						for(int k = 0; k < f1->count; k++) {
							if(f1->arr[k] == 'e')
								continue;
							
							flag = 0;
							
							for(int l = 0; l < f->count; l++) {
								if(f->arr[l] == f1->arr[k]) {
									flag = 1;
								}
							}
							
							if(!flag) {
								f->arr[f->count++] = f1->arr[k];
							}
						}
						
						if(grammar[i].rhs[j + m] == '\0') {
							if(grammar[i].lhs[0] == c)
								break;
							
							followStruct* f2 = follow(grammar[i].lhs[0]);
							
							for(int k = 0; k < f2->count; k++) {
								flag = 0;
								
								for(int l = 0; l < f->count; l++) {
									if(f->arr[l] == f2->arr[k]) {
										flag = 1;
									}
								}
								
								if(!flag) {
									f->arr[f->count++] = f2->arr[k];
								}
							}
						}
					}
				} else {
					f->arr[f->count++] = grammar[i].rhs[j + 1];
				}
			}
		}
	}
	
	return f;
}

void main() {
	int t = 0;
	char non_terminals[10];
	
	printf("Enter the number of productions: ");
	scanf("%d", &n);
	
	printf("\nEnter the productions (Eg: S = aBc):\n");
	for(int i = 0; i < n; i++) {
		scanf("%s = %s", grammar[i].lhs, grammar[i].rhs);
	}
	
	int flag;
	
	// Adding the non-terminals
	for(int i = 0; i < n; i++) {
		flag = 0;
		
		for(int j = 0; j < t; j++) {
			if(non_terminals[j] == grammar[i].lhs[0])
				flag = 1;
		}
		
		if(!flag) {
			non_terminals[t++] = grammar[i].lhs[0];
		}
		
		for(int j = 0; j < strlen(grammar[i].rhs); j++) {
			if(grammar[i].rhs[j] >= 'A' && grammar[i].rhs[j] <= 'Z') {
				flag = 0;
				
				for(int k = 0; k < t; k++) {
					if(non_terminals[k] == grammar[i].rhs[j])
						flag = 1;
				}
				
				if(!flag) {
					non_terminals[t++] = grammar[i].rhs[j];
				}
				
				continue;
			}
		}
	}
	
	for(int i = 0; i < t; i++) {
		flag = 0;
		
		int temp = n;
		
		// Eliminating indirect left recursion
		while(!flag) {
			flag = 1;
			
			for(int j = 0; j < temp; j++) {
				if(grammar[j].lhs[0] == non_terminals[i]) {
					if(grammar[j].rhs[0] >= 'A' && grammar[j].rhs[0] <= 'Z' && grammar[j].rhs[0] > non_terminals[i]) {
						flag = 0;
						
						for(int k = 0; k < temp; k++) {
							if(grammar[k].lhs[0] == grammar[j].rhs[0]) {
								grammar[n].lhs[0] = non_terminals[i];
								grammar[n].lhs[1] = '\0';
								strcpy(grammar[n].rhs, grammar[k].rhs);
								strcat(grammar[n].rhs, &grammar[j].rhs[1]);
								n++;
							}
						}
						
						for(int k = j; k + 1 < n; k++) {
							strcpy(grammar[k].lhs, grammar[k + 1].lhs);
							strcpy(grammar[k].rhs, grammar[k + 1].rhs);
						}
						
						temp--;
						n--;
						j--;
					}
				}
			}
		}
		
		// Eliminating direct left recursion
		for(int l = 0; l < n; l++) {
			if(grammar[l].lhs[0] == non_terminals[i] && grammar[l].lhs[0] == grammar[l].rhs[0]) {
				for(int j = 0; ; j++) {
					if(grammar[l].rhs[j + 1] == '\0') {
						grammar[l].rhs[j] = temps[tempIndex];
						break;
					}
					
					grammar[l].rhs[j] = grammar[l].rhs[j + 1];
				}
				
				for(int j = 0; j < n; j++) {
					if(j == l)
						continue;
					
					if(grammar[j].lhs[0] == grammar[l].lhs[0]) {
						for(int k = 0; ; k++) {
							if(grammar[j].rhs[k] == '\0') {
								grammar[j].rhs[k] = temps[tempIndex];
								grammar[j].rhs[k + 1] = '\0';
								break;
							}
						}
					}
				}
				
				grammar[l].lhs[0] = temps[tempIndex];
				grammar[n].lhs[0] = temps[tempIndex];
				grammar[n].lhs[1] = '\0';
				grammar[n].rhs[0] = 'e';
				grammar[n].rhs[1] = '\0';
				n++;
				tempIndex++;
			}
		}
	}
	
	printf("\nAfter eliminating direct and indirect left recursions\n");
	for(int i = 0; i < n; i++) {
		printf("%s = %s\n", grammar[i].lhs, grammar[i].rhs);
	}
	
	// Adding the new non-terminals
	for(int i = 0; i < n; i++) {
		flag = 0;
		
		for(int j = 0; j < t; j++) {
			if(non_terminals[j] == grammar[i].lhs[0])
				flag = 1;
		}
		
		if(!flag) {
			non_terminals[t++] = grammar[i].lhs[0];
		}
		
		for(int j = 0; j < strlen(grammar[i].rhs); j++) {
			if(grammar[i].rhs[j] >= 'A' && grammar[i].rhs[j] <= 'Z') {
				flag = 0;
				
				for(int k = 0; k < t; k++) {
					if(non_terminals[k] == grammar[i].rhs[j])
						flag = 1;
				}
				
				if(!flag) {
					non_terminals[t++] = grammar[i].rhs[j];
				}
				
				continue;
			}
		}
	}
	
	firstStruct* f;
	followStruct* fl;
	
	// FIRST
	printf("\n");
	for(int i = 0; i < t; i++) {
		printf("FIRST(%c):", non_terminals[i]);
		
		f = first(non_terminals[i]);
		
		for(int j = 0; j < f->count; j++) {
			printf(" %c", f->arr[j]);
		}
		
		printf("\n");
	}
	
	// FOLLOW
	printf("\n");
	for(int i = 0; i < t; i++) {
		printf("FOLLOW(%c):", non_terminals[i]);
		
		fl = follow(non_terminals[i]);
		
		for(int j = 0; j < fl->count; j++) {
			printf(" %c", fl->arr[j]);
		}
		
		printf("\n");
	}
}

