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
	int flag;
} state;

typedef struct trans1 {
	state state1;
	char input;
	state state2;
} trans1;

// NFA data
char states[10][3], start[3], final[10][3], alpha[5];
trans table[30];

// DFA data
state states1[100], start1, final1[100];
trans1 table1[300];

void cpyState(state* state1, state state2) {
	state1->len = state2.len;
	state1->flag = state2.flag;
	
	for(int i = 0; i < state2.len; i++) {
		strcpy(state1->states[i], state2.states[i]);
	}
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

int containsState(state st, char state[]) {
	for(int i = 0; i < st.len; i++) {
		if(!strcmp(st.states[i], state))
			return 1;
	}
	
	return 0;
}

void insertTrans(trans1* table, state* state1, char input, state* state2, int i) {
	table[i].state1.len = state1->len;
	table[i].state1.flag = state1->flag;
	
	for(int j = 0; j < state1->len; j++) {
		strcpy(table[i].state1.states[j], state1->states[j]);
	}

	table[i].state2.len = state2->len;
	table[i].state2.flag = state2->flag;
	
	for(int j = 0; j < state2->len; j++) {
		strcpy(table[i].state2.states[j], state2->states[j]);
	}
	
	table[i].input = input;
}

void main() {
	int n, f, m, l;
	
	// Reading the NFA
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
	
	printf("Enter the number of transitions: ");
	scanf("%d", &m);
	
	printf("Enter the transition table:\n");
	for(int i = 0; i < m; i++) {
		scanf("%s %c %s", table[i].state1, &table[i].input, table[i].state2);
	}
	
	// Converting to DFA
	int n1 = 0, f1 = 0, m1 = 0;
	
	strcpy(start1.states[0], start); // Start state of DFA
	start1.len = 1;
	start1.flag = 1;
	
	cpyState(&states1[n1], start1); // Adding states
	n1++;
	
	state temp;
	
	cpyState(&temp, start1);
	
	int flag, isDead = 0;
	state dead;
	
	while(1) {
		for(int i = 0; i < l; i++) {
			state temp1;
			temp1.len = 0;
			temp1.flag = 0;
			
			for(int j = 0; j < temp.len; j++) {
				for(int k = 0; k < m; k++) {
					if(!strcmp(temp.states[j], table[k].state1) && alpha[i] == table[k].input && !containsState(temp1, table[k].state2)) {
						strcpy(temp1.states[temp1.len++], table[k].state2);
					}
				}
			}
			
			state state1, state2;
			
			cpyState(&state1, temp);
			
			if(temp1.len == 0) {
				isDead = 1;
				dead.len = 1;
				dead.flag = 1;
				strcpy(dead.states[0], "q-");
				cpyState(&state2, dead);
			} else {
				cpyState(&state2, temp1);
				
				flag = 0;
				
				for(int k = 0; k < n1; k++) {
					if(cmpState(states1[k], temp1))
						flag = 1;
				}
				
				if(!flag)
					cpyState(&states1[n1++], temp1);
			}
			
			insertTrans(table1, &state1, alpha[i], &state2, m1++);
		}
		
		flag = 0;
		
		for(int i = 0; i < n1; i++) {
			if(states1[i].flag == 0) {
				flag = 1;
				cpyState(&temp, states1[i]);
				states1[i].flag = 1;
				break;
			}
		}
		
		if(!flag) {
			if(isDead) {
				for(int i = 0; i < l; i++)
					insertTrans(table1, &dead, alpha[i], &dead, m1++);
			}
			break;
		}
	}
	
	for(int i = 0; i < f; i++) {
		for(int j = 0; j < n1; j++) {
			for(int k = 0; k < states1[j].len; k++) {
				if(!strcmp(final[i], states1[j].states[k])) {
					cpyState(&final1[f1++], states1[j]);
					break;
				}
			}
		}
	}
	
	printf("\nStates of DFA\n");
	for(int i = 0; i < n1; i++) {
		printf("{");
		for(int j = 0; j < states1[i].len; j++) {
			printf(" %s ", states1[i].states[j]);
		}
		printf("}\n");
	}

	printf("\nStart state of DFA\n");
	printf("{");
	printf(" %s ", start1.states[0]);
	printf("}\n");
	
	printf("\nFinal states of DFA\n");
	for(int i = 0; i < f1; i++) {
		printf("{");
		for(int j = 0; j < final1[i].len; j++) {
			printf(" %s ", final1[i].states[j]);
		}
		printf("}\n");
	}
	
	
	printf("\nTransition table of DFA\n");
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
}

