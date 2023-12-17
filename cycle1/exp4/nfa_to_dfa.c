#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STATES 10
#define ALPHABET_SIZE 2

typedef struct {
    char state[MAX_STATES];
    char input;
    char nextState[MAX_STATES];
} Transition;

void epsilonClosure(int nfa[MAX_STATES][MAX_STATES], int nfaStates, int currentState, bool visited[MAX_STATES]) {
    visited[currentState] = true;
    
    for (int i = 0; i < nfaStates; i++) {
        if (nfa[currentState][i] == 1 && !visited[i]) {
            epsilonClosure(nfa, nfaStates, i, visited);
        }
    }
}

void getEpsilonClosure(int nfa[MAX_STATES][MAX_STATES], int nfaStates, int currentState, char closure[MAX_STATES]) {
    bool visited[MAX_STATES];
    memset(visited, false, sizeof(visited));

    epsilonClosure(nfa, nfaStates, currentState, visited);

    int index = 0;
    for (int i = 0; i < nfaStates; i++) {
        if (visited[i]) {
            closure[index++] = '0' + i;
        }
    }
    closure[index] = '\0';
}

void transitionWithInput(int nfa[MAX_STATES][MAX_STATES], int nfaStates, char currentStateSet[MAX_STATES], char input, char nextStateSet[MAX_STATES]) {
    char epsilonClosureSet[MAX_STATES];
    int epsilonClosureSize;

    for (int i = 0; i < MAX_STATES; i++) {
        nextStateSet[i] = '\0';
    }

    for (int i = 0; i < strlen(currentStateSet); i++) {
        epsilonClosureSize = 0;
        getEpsilonClosure(nfa, nfaStates, currentStateSet[i] - '0', epsilonClosureSet);

        for (int j = 0; j < strlen(epsilonClosureSet); j++) {
            for (int k = 0; k < nfaStates; k++) {
                if (nfa[epsilonClosureSet[j] - '0'][k] == 1 && nfa[epsilonClosureSet[j] - '0'][k] == input - '0') {
                    char nextState[MAX_STATES];
                    getEpsilonClosure(nfa, nfaStates, k, nextState);

                    for (int l = 0; l < strlen(nextState); l++) {
                        if (strchr(nextStateSet, nextState[l]) == NULL) {
                            nextStateSet[strlen(nextStateSet)] = nextState[l];
                        }
                    }
                }
            }
        }
    }
}

void printDFA(int dfa[MAX_STATES][ALPHABET_SIZE], int dfaStates, char alphabet[ALPHABET_SIZE]) {
    printf("DFA Transition Table:\n");
    
    printf("States\t");
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        printf("%c\t", alphabet[i]);
    }
    printf("\n");

    for (int i = 0; i < dfaStates; i++) {
        printf("{%d}\t", i + 1);

        for (int j = 0; j < ALPHABET_SIZE; j++) {
            printf("{%d}\t", dfa[i][j] + 1);
        }
        printf("\n");
    }
}

int main() {
    int nfa[MAX_STATES][MAX_STATES];
    int nfaStates, nfaTransitions;
    char alphabet[ALPHABET_SIZE] = {'0', '1'};
    
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

    int dfa[MAX_STATES][ALPHABET_SIZE];
    int dfaStates = 0;

    char initialStateSet[MAX_STATES] = "0"; // Assuming the initial state is always 0 in the NFA
    char currentStateSet[MAX_STATES];
    char nextStateSet[MAX_STATES];

    getEpsilonClosure(nfa, nfaStates, 0, initialStateSet);

    for (int i = 0; i < strlen(initialStateSet); i++) {
        currentStateSet[i] = initialStateSet[i];
    }

    // DFA construction
    while (dfaStates < MAX_STATES) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            transitionWithInput(nfa, nfaStates, currentStateSet, alphabet[i], nextStateSet);

            char nextStateSetCopy[MAX_STATES];
            for (int j = 0; j < strlen(nextStateSet); j++) {
                nextStateSetCopy[j] = nextStateSet[j];
            }

            getEpsilonClosure(nfa, nfaStates, nextStateSet[0] - '0', nextStateSet);
            int stateExists = -1;

            for (int j = 0; j < dfaStates; j++) {
                if (strcmp(nextStateSet, currentStateSet) == 0) {
                    stateExists = j;
                    break;
                }
            }

            if (stateExists == -1) {
                for (int j = 0; j < strlen(nextStateSet); j++) {
                    currentStateSet[j] = nextStateSet[j];
                }

                for (int j = 0; j < strlen(nextStateSetCopy); j++) {
                    dfa[dfaStates][i] = nextStateSetCopy[j] - '0';
                }

                dfaStates++;
            } else {
                dfa[dfaStates][i] = stateExists;
            }
        }

        currentStateSet[0] = '\0';
        for (int i = 0; i < strlen(nextStateSet); i++) {
            currentStateSet[i] = nextStateSet[i];
        }

        int stateExists = -1;
        for (int i = 0; i < dfaStates; i++) {
            if (strcmp(nextStateSet, currentStateSet) == 0) {
                stateExists = i;
                break;
            }
        }

        if (stateExists == -1) {
            for (int i = 0; i < strlen(nextStateSet); i++) {
                currentStateSet[i] = nextStateSet[i];
            }
            dfaStates++;
        }
    }

    // Print the DFA
    printDFA(dfa, dfaStates, alphabet);

    return 0;
}
