#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STATES 10
#define ALPHABET_SIZE 2

int nfa[MAX_STATES][MAX_STATES];
char alphabet[ALPHABET_SIZE] = {'0', '1'};
int dfa[MAX_STATES][ALPHABET_SIZE];
int dfaStates = 0;

// Function to calculate epsilon closure of a state in the NFA
void epsilonClosure(int state, bool visited[MAX_STATES], char closure[MAX_STATES]) {
    visited[state] = true;
    closure[strlen(closure)] = '0' + state;

    for (int i = 0; i < MAX_STATES; i++) {
        if (nfa[state][i] == 1 && !visited[i]) {
            epsilonClosure(i, visited, closure);
        }
    }
}

// Function to get epsilon closure of a state in the NFA
void getEpsilonClosure(int state, char closure[MAX_STATES]) {
    bool visited[MAX_STATES];
    memset(visited, false, sizeof(visited));

    epsilonClosure(state, visited, closure);
}

// Function to calculate the next state set for a given input
void transitionWithInput(char currentStateSet[MAX_STATES], char input, char nextStateSet[MAX_STATES]) {
    nextStateSet[0] = '\0';

    for (int i = 0; i < strlen(currentStateSet); i++) {
        for (int j = 0; j < MAX_STATES; j++) {
            if (nfa[currentStateSet[i] - '0'][j] == 1 && nfa[currentStateSet[i] - '0'][j] == input - '0') {
                char epsilonClosureSet[MAX_STATES];
                getEpsilonClosure(j, epsilonClosureSet);

                for (int k = 0; k < strlen(epsilonClosureSet); k++) {
                    if (strchr(nextStateSet, epsilonClosureSet[k]) == NULL) {
                        nextStateSet[strlen(nextStateSet)] = epsilonClosureSet[k];
                    }
                }
            }
        }
    }
}

// Function to check if a state set already exists in the DFA
int stateExists(char stateSet[MAX_STATES]) {
    for (int i = 0; i < dfaStates; i++) {
        if (strcmp(stateSet, dfa[i]) == 0) {
            return i;
        }
    }
    return -1;
}

// Function to convert NFA to DFA
void convertNFAToDFA(int initialState) {
    char currentStateSet[MAX_STATES];
    char nextStateSet[MAX_STATES];

    getEpsilonClosure(initialState, currentStateSet);

    while (currentStateSet[0] != '\0' && dfaStates < MAX_STATES) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            transitionWithInput(currentStateSet, alphabet[i], nextStateSet);

            int stateIndex = stateExists(nextStateSet);

            if (stateIndex == -1) {
                strcpy(dfa[dfaStates], nextStateSet);
                dfaStates++;
            }

            dfa[dfaStates - 1][i] = stateIndex == -1 ? dfaStates : stateIndex;
        }

        // Move to the next state set
        strcpy(currentStateSet, nextStateSet);
    }
}

// Function to print the DFA transition table
void printDFA() {
    printf("DFA Transition Table:\n");
    printf("States\t");

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        printf("%c\t", alphabet[i]);
    }
    printf("\n");

    for (int i = 0; i < dfaStates; i++) {
        printf("{%s}\t", dfa[i]);

        for (int j = 0; j < ALPHABET_SIZE; j++) {
            printf("{%d}\t", dfa[i][j] + 1);
        }
        printf("\n");
    }
}

int main() {
    int nfaStates, nfaTransitions, initialState;

    printf("Enter the number of states in the NFA: ");
    scanf("%d", &nfaStates);

    printf("Enter the number of transitions in the NFA: ");
    scanf("%d", &nfaTransitions);

    // Initialize NFA matrix with zeros
    for (int i = 0; i < nfaStates; i++) {
        for (int j = 0; j < nfaStates; j++) {
            nfa[i][j] = 0;
        }
    }

    printf("Enter the transitions in the format (state1 input state2):\n");
    for (int i = 0; i < nfaTransitions; i++) {
        int state1, state2;
        char input;
        scanf("%d %c %d", &state1, &input, &state2);
        nfa[state1][state2] = 1; // Assuming 1 represents a transition
    }

    // Display NFA matrix
    printf("\nNFA Transition Table:\n");
    for (int i = 0; i < nfaStates; i++) {
        for (int j = 0; j < nfaStates; j++) {
            printf("%d ", nfa[i][j]);
        }
        printf("\n");
    }

    printf("Enter the initial state of the NFA: ");
    scanf("%d", &initialState);

    convertNFAToDFA(initialState);
    printDFA();

    return 0;
}
