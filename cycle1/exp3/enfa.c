#include <stdio.h>
#include <string.h>

typedef struct trans {
	char state1[3];
	char input[3];
	char state2[3];
} trans;

typedef struct closure {
	int len;
	char states[10][3];
} closure;

char states[10][3], start[3], final[10][3];
closure cl[10];

int add_state(char state[3], int i, int k) {
	int flag = 0;
	
	for(int j = 0; j < k; j++) {
		if(!strcmp(cl[i].states[j], state)) flag = 1;
	}
	
	if(!flag) {
		strcpy(cl[i].states[k], state);
		k++;
		cl[i].len = k;
	}
	
	return k;
}

int isDup(trans table[], int len, char state1[], char input[], char state2[]) {
	int flag = 0;
	
	for(int i = 0; i < len; i++) {
		if(!strcmp(table[i].state1, state1) && !strcmp(table[i].input, input) && !strcmp(table[i].state2, state2))
			flag = 1;
	}
	
	return flag;
}

void main() {
	int n, m, f;
	
	// Reading the e-nfa
	printf("Enter the no of states: ");
	scanf("%d", &n);
	
	printf("Enter the states:\n");
	for(int i = 0; i < n; i++){
		scanf("%s", states[i]);
	}
	
	printf("Enter the start state: ");
	scanf("%s", start);
	
	printf("Enter the number of final states: ");
	scanf("%d", &f);
	
	printf("Enter the final states\n");
	for(int i = 0; i < f; i++) {
		scanf("%s", final[i]);
	}
	
	printf("Enter the number of transitions: ");
	scanf("%d", &m);
	
	trans table[m], table1[m * m];
	
	printf("Enter the transition table:\n");
	for(int i = 0; i < m; i++) {
		scanf("%s %s %s", table[i].state1, table[i].input, table[i].state2);
	}
	
	int l;
	
	// Finding e-closure of all states
	for(int i = 0; i < n; i++){
		l = 0;
		
		l = add_state(states[i], i, l);
		
		for(int p = 0; p < l; p++) {
			for(int j = 0; j < m; j++){
				if(!strcmp(cl[i].states[p], table[j].state1)){
					if(!strcmp(table[j].input, "e")) {
						l = add_state(table[j].state2, i, l);
					}
				}
			}
		}
	}
	
	// Finding e-closure
	printf("\nE-closure\n");
	for(int i = 0; i < n; i++) {
		printf("%s: ", states[i]);
		for(int j = 0; j < cl[i].len; j++) {
			printf(" %s ", cl[i].states[j]);
		}
		printf("\n");
	}
	
	int s1 = 0, m1 = 0, f1 = 0;
	char start1[10][3];
	char final1[10][3];
	
	// Finding new start states
	for(int i = 0; i < n; i++) {
		if(!strcmp(states[i], start)) {
			for(int j = 0; j < cl[i].len; j++) {
				strcpy(start1[s1], cl[i].states[j]);
				s1++;
			}
			
			break;
		}
	}
	
	printf("\nThe start states of new NFA:\n");
	for(int i = 0; i < s1; i++) {
		printf("%s\n", start1[i]);
	}
	
	// Finding new final states
	for(int k = 0; k < f; k++) {
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < cl[i].len; j++) {
				if(!strcmp(final[k], cl[i].states[j])) {
					strcpy(final1[f1], states[i]);
					f1++;
				}
			}
		}
	}
	
	printf("\nThe final states of new NFA:\n");
	for(int i = 0; i < f1; i++) {
		printf("%s\n", final1[i]);
	}
	
	// Finding the transition table
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < cl[i].len; j++) {
			for(int k = 0; k < m; k++) {
				if(!strcmp(table[k].state1, cl[i].states[j]) && strcmp(table[k].input, "e")) {
					for(int p = 0; p < n; p++) {
						if(!strcmp(states[p], table[k].state2)) {
							for(int q = 0; q < cl[p].len; q++) {
								if(!isDup(table1, m1, states[i], table[k].input, cl[p].states[q])) {
									strcpy(table1[m1].state1, states[i]);
									strcpy(table1[m1].input, table[k].input);
									strcpy(table1[m1].state2, cl[p].states[q]);
									m1++;
								}
							}
							
							break;
						}
					}
				}
			}
		}
	}
	
	printf("\nTransition table of new NFA:\n");
	for(int i = 0; i < m1; i++) {
		printf("%s %s %s\n", table1[i].state1, table1[i].input, table1[i].state2);
	}
}

