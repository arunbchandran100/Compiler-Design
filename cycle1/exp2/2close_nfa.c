#include <stdio.h>
#include <string.h>

#define MAX_STATES 10
#define MAX_TRANSITIONS 20

// Define a structure for NFA transitions
typedef struct {
    char state1[3];
    char input[3];
    char state2[3];
} Transition;

// Define a structure for NFA states with epsilon closure information
typedef struct {
    char states[MAX_STATES][3];
    int len;    // Number of states in the closure
    int flag;   // Flag to mark if the state is processed
} State;

State nfaStates[MAX_STATES], epsilonClosure[MAX_STATES];
Transition nfaTransitions[MAX_TRANSITIONS];

int stateCount;       // Number of states in the NFA
int transitionCount;  // Number of transitions in the NFA

// Function to add a state to the given state array if it doesn't exist
int addState(State *stateArray, char state[3], int k) {
    int flag = 0;

    for (int i = 0; i < k; i++) {
        if (!strcmp(stateArray[i].states[0], state))
            flag = 1;
    }

    if (!flag) {
        strcpy(stateArray[k].states[0], state);
        stateArray[k].len = 1;
        k++;
    }

    return k;
}

// Recursive function to compute the epsilon closure of a state
void computeEpsilonClosure(char state[3], State *closure, int *closureSize) {
    if (addState(closure, state, *closureSize)) {
        // Check epsilon transitions from the current state
        for (int j = 0; j < transitionCount; j++) {
            if (!strcmp(nfaTransitions[j].state1, state) && !strcmp(nfaTransitions[j].input, "e")) {
                computeEpsilonClosure(nfaTransitions[j].state2, closure, closureSize);
            }
        }
    }
}

// Function to display the epsilon closure of a state
void displayEpsilonClosure(int closureSize, int i) {
    printf("Epsilon closure of %s = {", nfaStates[i].states[0]);

    for (int j = 0; j < closureSize; j++)
        printf(" %s", epsilonClosure[j].states[0]);

    printf(" }\n");
}

int main() {
    // Read the NFA details from the user
    printf("Enter the number of states: ");
    scanf("%d", &stateCount);

    printf("Enter the states:\n");
    for (int i = 0; i < stateCount; i++) {
        scanf("%s", nfaStates[i].states[0]);
        nfaStates[i].len = 1;
        nfaStates[i].flag = 0;
    }

    printf("Enter the number of transitions: ");
    scanf("%d", &transitionCount);

    printf("Enter the transition table:\n");
    for (int i = 0; i < transitionCount; i++) {
        scanf("%s %s %s", nfaTransitions[i].state1, nfaTransitions[i].input, nfaTransitions[i].state2);
    }

    printf("\n");

    // Compute and display epsilon closure for each state
    for (int i = 0; i < stateCount; i++) {
        int closureSize = 0;

        computeEpsilonClosure(nfaStates[i].states[0], epsilonClosure, &closureSize);

        displayEpsilonClosure(closureSize, i);
    }

    return 0;
}
