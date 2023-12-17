#include <stdio.h>
#include <string.h>

#define MAX_STATES 10
#define MAX_TRANSITIONS 20

typedef struct {
    char state1[3];
    char input[3];
    char state2[3];
} Transition;

char states[MAX_STATES][3];
Transition transitions[MAX_TRANSITIONS];

int state_count;
int transition_count;

int is_state_in_closure(char state[3], char closure[MAX_STATES][3], int closure_size) {
    for (int i = 0; i < closure_size; i++) {
        if (strcmp(state, closure[i]) == 0) {
            return 1; // State is already in the closure
        }
    }
    return 0; // State is not in the closure
}

void compute_epsilon_closure(char state[3], char closure[MAX_STATES][3], int *closure_size) {
    if (is_state_in_closure(state, closure, *closure_size)) {
        return; // State is already in the closure
    }

    strcpy(closure[(*closure_size)++], state);

    for (int i = 0; i < transition_count; i++) {
        if (strcmp(transitions[i].state1, state) == 0 && strcmp(transitions[i].input, "e") == 0) {
            compute_epsilon_closure(transitions[i].state2, closure, closure_size);
        }
    }
}

int main() {
    printf("Enter the number of states: ");
    scanf("%d", &state_count);

    printf("Enter the states:\n");
    for (int i = 0; i < state_count; i++) {
        scanf("%s", states[i]);
    }

    printf("Enter the number of transitions: ");
    scanf("%d", &transition_count);

    printf("Enter the transition table:\n");
    for (int i = 0; i < transition_count; i++) {
        scanf("%s %s %s", transitions[i].state1, transitions[i].input, transitions[i].state2);
    }

    printf("\nNFA without epsilon transitions:\n");

    for (int i = 0; i < state_count; i++) {
        char epsilon_closure[MAX_STATES][3];
        int closure_size = 0;

        compute_epsilon_closure(states[i], epsilon_closure, &closure_size);

        printf("Epsilon closure of %s = {", states[i]);
        for (int j = 0; j < closure_size; j++) {
            printf(" %s", epsilon_closure[j]);
        }
        printf(" }\n");

        for (int j = 0; j < transition_count; j++) {
            if (strcmp(transitions[j].input, "e") != 0) {
                // Adjust transitions for NFA without ε
                if (is_state_in_closure(transitions[j].state1, epsilon_closure, closure_size)) {
                    printf("Transition from %s on input '%s' to %s\n", states[i], transitions[j].input, transitions[j].state2);
                }
            }
        }

        printf("\n");
    }

    return 0;
}
