#include <stdio.h>
#include <string.h>

typedef struct trans {
	char state1[3];
	char input;
	char state2[3];
} trans;

typedef struct state {
	int len;
	char states[10][3];
} state;

typedef struct trans1 {
	state state1;
	char input;
	state state2;
} trans1;

int store[10];

// DFA data
int n, f, m, l;
char states[10][3], start[3], final[10][3], alpha[5];
trans table[50];

// Minimised DFA data
int n1, f1, m1, l;
state states1[10], start1, final1[10];
trans1 table1[50];

void removeState(int k) {
	for(int i = k; i < n - 1; i++) {
		strcpy(states[i], states[i + 1]);
	}
	
	n--;
}

void removeTrans(int k) {
	for(int i = 2 * k; i < m - 2; i++) {
		strcpy(table[i].state1, table[i + 2].state1);
		table[i].input = table[i + 2].input;
		strcpy(table[i].state2, table[i + 2].state2);
	}
	
	m -= 2;
}

int isFinal(char state[]) {
	for(int i = 0; i < f; i++) {
		if(!strcmp(final[i], state))
			return 1;
	}
	
	return 0;
}

int goTo(char st[], char c) {
	for(int i = 0; i < m; i++) {
		if(!strcmp(table[i].state1, st) && table[i].input == c) {
			for(int j = 0; j < n; j++) {
				if(!strcmp(states[j], table[i].state2))
					return j;
			}
		}
	}
}

int contains(state st[], int n, char state[3]) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < st[i].len; j++) {
			if(!strcmp(st[i].states[j], state))
				return 1;
		}
	}
	
	return 0;
}

int cmpState(state state1, state state2) {
	if(state1.len != state2.len)
		return 0;
	
	int count = 0;
	
	for(int i = 0; i < state1.len; i++) {
		for(int j = 0; j < state2.len; j++) {
			if(!strcmp(state1.states[i], state2.states[j]))
				count++;
		}
	}
	
	if(count == state1.len)
		return 1;
	else
		return 0;
}

int containsState(state states[], int n, state st) {
	for(int i = 0; i < n; i++) {
		if(cmpState(states[i], st))
			return 1;
	}
	
	return 0;
}

int is_clique(int n, int graph[n][n], int b) {
	for(int i = 1; i < b; i++) {
		for(int j = i + 1; j < b; j++)
			if(graph[store[i]][store[j]] == 1)
				return 0;
	}
	
	return 1;
}

void combine(int n)
{
	states1[n1].len = 0;
	
	int flag = 0;
	
	for(int i = 1; i < n; i++) {
		if(!contains(states1, n1, states[store[i]])) {
			strcpy(states1[n1].states[states1[n1].len++], states[store[i]]);
			flag = 1;
		}
	}
	
	if(flag)
		n1++;
}

void findCliques(int n, int graph[n][n], int i, int l, int k) {
	for (int j = i; j < n - (k - l); j++) {
		store[l] = j;
		
		if (is_clique(n, graph, l + 1)) {
			if (l < k)
				findCliques(n, graph, j + 1, l + 1, k);
			else
				combine(l + 1);
		}
	}
}

void cpyState(state* state1, state state2) {
	state1->len = state2.len;
	
	for(int i = 0; i < state2.len; i++) {
		strcpy(state1->states[i], state2.states[i]);
	}
}

void insertTrans(trans1* table, state state1, char input, state state2, int i) {
	table[i].state1.len = state1.len;
	
	for(int j = 0; j < state1.len; j++) {
		strcpy(table[i].state1.states[j], state1.states[j]);
	}

	table[i].state2.len = state2.len;
	
	for(int j = 0; j < state2.len; j++) {
		strcpy(table[i].state2.states[j], state2.states[j]);
	}
	
	table[i].input = input;
}

void main() {
	// Reading the DFA
	printf("Enter the no of states: ");
	scanf("%d", &n);
	
	printf("Enter the states:\n");
	for(int i = 0; i < n; i++) {
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
	
	printf("Enter the number of alphabets: ");
	scanf("%d", &l);
	
	printf("Enter the alphabets\n");
	for(int i = 0; i < l; i++) {
		scanf(" %c", &alpha[i]);
	}
	
	m = 0;
	printf("Enter the transitions\n");
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < l; j++) {
			strcpy(table[m].state1, states[i]);
			table[m].input = alpha[j];
			printf("%s %c ", states[i], alpha[j]);
			scanf("%s", table[m].state2);
			m++;
		}
	}
	
	// Minimising using Myhill-Nerode Theorem
	printf("\nMinimised DFA\n");
	
	int flag;
	
	// Eliminating unreachable states
	do {
		flag = 0;
		
		for(int i = 0; i < n; i++) {
			if(!strcmp(states[i], start))
				continue;
			
			int flag1 = 0;
			
			for(int j = 0; j < m; j++) {
				if(strcmp(table[j].state1, states[i]) && !strcmp(table[j].state2, states[i]))
					flag1 = 1;
			}
			
			if(!flag1) {
				flag = 1;
				removeState(i);
				removeTrans(i);
			}
		}
	} while(flag);
	
	// Table filling
	int mTbl[n][n];
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			mTbl[i][j] = 0;
		}
	}
	
	// Marking if either state is final but not both
	for(int i = 0; i < n; i++) {
		for(int j = i + 1; j < n; j++) {
			if((isFinal(states[i]) && !isFinal(states[j])) || (!isFinal(states[i]) && isFinal(states[j])) ) {
				mTbl[i][j] = 1;
				mTbl[j][i] = 1;
			}
		}
	}
	
	int s1, s2;
	
	// Marking the states by checking if their transitions are marked
	do {
		flag = 0;
		
		for(int i = 0; i < n; i++) {
			for(int j = i + 1; j < n; j++) {
				if(mTbl[i][j])
					continue;
				
				for(int k = 0; k < l; k++) {
					s1 = goTo(states[i], alpha[k]);
					s2 = goTo(states[j], alpha[k]);
					
					if(mTbl[s1][s2] || mTbl[s2][s1]) {
						mTbl[i][j] = 1;
						mTbl[j][i] = 1;
						flag = 1;
					}
				}
			}
		}
	} while(flag);
	
	// Combining states
	n1 = 0;
	
	for(int k = n; k > 0; k--) {
		findCliques(n, mTbl, 0, 1, k);
	}
	
	printf("\nStates:\n");
	for(int i = 0; i < n1; i++) {
		printf("{");
		for(int j = 0; j < states1[i].len; j++) {
			printf(" %s ", states1[i].states[j]);
		}
		printf("}\n");
	}
	
	// Transition table of min DFA
	m1 = 0;
	
	for(int i = 0; i < n1; i++) {
		for(int j = 0; j < l; j++) {
			for(int k = 0; k < m; k++) {
				if(!strcmp(table[k].state1, states1[i].states[0]) && table[k].input == alpha[j]) {
					for(int i1 = 0; i1 < n1; i1++) {
						for(int j1 = 0; j1 < states1[i1].len; j1++) {
							if(!strcmp(states1[i1].states[j1], table[k].state2)) {
								insertTrans(table1, states1[i], alpha[j], states1[i1], m1++);
							}
						}
					}
				}
			}
		}
	}
	
	printf("\nTransition table:\n");
	for(int i = 0; i < m1; i++) {
		printf("{");
		for(int j = 0; j < table1[i].state1.len; j++) {
			printf(" %s ", table1[i].state1.states[j]);
		}
		printf("}");

		printf(" %c ", table1[i].input);		

		printf("{");
		for(int j = 0; j < table1[i].state2.len; j++) {
			printf(" %s ", table1[i].state2.states[j]);
		}
		printf("}\n");
	}
	
	// Start state of min DFA
	for(int i = 0; i < n1; i++) {
		for(int j = 0; j < states1[i].len; j++) {
			if(!strcmp(states1[i].states[j], start)) {
				cpyState(&start1, states1[i]);
			}
		}
	}
	
	printf("\nStart state: {");
	for(int i = 0; i < start1.len; i++) {
		printf(" %s ", start1.states[i]);
	}
	printf("}\n");
	
	// Final states of min DFA
	f1 = 0;
	for(int i = 0; i < n1; i++) {
		for(int j = 0; j < states1[i].len; j++) {
			for(int k = 0; k < f; k++) {
				if(!strcmp(states1[i].states[j], final[k]) && !containsState(final1, f1, states1[i])) {
					cpyState(&final1[f1++], states1[i]);
				}
			}
		}
	}
	
	printf("\nFinal states:\n");
	for(int i = 0; i < f1; i++) {
		printf("{");
		for(int j = 0; j < final1[i].len; j++) {
			printf(" %s ", final1[i].states[j]);
		}
		printf("}\n");
	}
}

