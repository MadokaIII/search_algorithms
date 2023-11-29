#define _POSIX_C_SOURCE 200809L
#define STATE_SIZE 4
#define NUM_ARRANGEMENTS 1
#define ARRANGEMENT_LENGTH 5
#define NB_OBJECTS 9
#define NB_ROWS 3
#define NB_COLS 4
#define NUM_STRINGS 3
#define MAX_STRING_LENGTH 5
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int position;
    char character;
} SplitDecision;

typedef struct s_state {
    unsigned char first_octet;
    unsigned char second_octet;
    unsigned char third_octet;
    unsigned char forth_octet;
} State;

void init_state(State *state) { memset(state, 0, STATE_SIZE); }

void print_char_as_binary(unsigned char octet) {
    for (int i = 7; i >= 0; i--) {
        putchar((octet & (1 << i)) ? '1' : '0');
    }
}

void print_state_as_binary(State state) {
    for (unsigned long i = 0; i < STATE_SIZE; i++) {
        print_char_as_binary(((unsigned char *)&state)[i]);
    }
    printf("\n");
}

bool is_representation_valid(int representation[]) {
    bool test[NB_OBJECTS];
    for (int i = 0; i < NB_COLS * NB_ROWS; i++) {
        if (representation[i] >= 0 && representation[i] < NB_OBJECTS) {
            test[representation[i]] = true;
        } else {
            return false;
        }
    }
    for (int i = 0; i < NB_OBJECTS; i++) {
        if (!test[i]) {
            return false;
        }
    }
    return true;
}

int factorial(int n) {
    if (n == 0)
        return 1;
    int fact = 1;
    for (int i = 2; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

int countUniquePermutations(char *str) {
    int freq[256] = {0};
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        freq[(unsigned char)str[i]]++;
    }

    int permutations = factorial(length);
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            permutations /= factorial(freq[i]);
        }
    }
    return permutations;
}

void swap(char *x, char *y) {
    char temp = *x;
    *x = *y;
    *y = temp;
}

bool shouldSwap(char *str, int start, int curr) {
    for (int i = start; i < curr; i++) {
        if (str[i] == str[curr]) {
            return false;
        }
    }
    return true;
}

void permute(char *str, int l, int r, char permutations[][ARRANGEMENT_LENGTH], int *index) {
    if (l == r) {
        strcpy(permutations[*index], str);
        (*index)++;
    } else {
        for (int i = l; i <= r; i++) {
            if (shouldSwap(str, l, i)) {
                swap((str + l), (str + i));
                permute(str, l + 1, r, permutations, index);
                swap((str + l), (str + i)); // backtrack
            }
        }
    }
}

double calculateEntropy(int *freq, int total) {
    double entropy = 0.0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            double p = (double)freq[i] / total;
            entropy -= p * log2(p);
        }
    }
    return entropy;
}

void findBestSplit(char permutations[][ARRANGEMENT_LENGTH], int numPermutations, int *bestPosition,
                   char *bestChar) {
    double maxEntropy = -1.0;
    int length = ARRANGEMENT_LENGTH - 1; // Adjust to ignore the null terminator

    for (int pos = 0; pos < length; pos++) {
        int freq[256] = {0}; // Frequency array for ASCII characters

        // Calculate frequency of each character at the current position
        for (int i = 0; i < numPermutations; i++) {
            unsigned char currentChar = permutations[i][pos];
            freq[currentChar]++;
        }

        // Calculate entropy for this position
        double entropy = calculateEntropy(freq, numPermutations);
        if (entropy > maxEntropy) {
            maxEntropy = entropy;
            *bestPosition = pos;

            // Find the character that contributes most to this entropy
            int maxFreq = 0;
            for (int i = 0; i < 256; i++) {
                if (freq[i] > maxFreq) {
                    maxFreq = freq[i];
                    *bestChar = (char)i;
                }
            }
        }
    }
}

void recursiveSplit(char permutations[][ARRANGEMENT_LENGTH], int numPermutations,
                    SplitDecision *decisions, int numDecisions) {
    if (numPermutations <= 1) {
        if (numPermutations == 1) {
            printf("Path to permutation %s: ", permutations[0]);
            for (int i = 0; i < numDecisions; i++) {
                printf("(%d, '%c') ", decisions[i].position, decisions[i].character);
            }
            printf("\n");
        }
        return;
    }

    int bestPosition;
    char bestChar;
    findBestSplit(permutations, numPermutations, &bestPosition, &bestChar);

    char(*sublist1)[ARRANGEMENT_LENGTH] = malloc(numPermutations * sizeof(*sublist1));
    char(*sublist2)[ARRANGEMENT_LENGTH] = malloc(numPermutations * sizeof(*sublist2));
    SplitDecision *newDecisions = malloc((numDecisions + 1) * sizeof(SplitDecision));

    if (!sublist1 || !sublist2 || !newDecisions) {
        fprintf(stderr, "Failed to allocate memory\n");
        free(sublist1);
        free(sublist2);
        free(newDecisions);
        return;
    }

    // Copy existing decisions and add the new one
    memcpy(newDecisions, decisions, numDecisions * sizeof(SplitDecision));
    newDecisions[numDecisions].position = bestPosition;
    newDecisions[numDecisions].character = bestChar;
    numDecisions++;

    int index1 = 0, index2 = 0;
    for (int i = 0; i < numPermutations; i++) {
        if (permutations[i][bestPosition] == bestChar) {
            strcpy(sublist1[index1++], permutations[i]);
        } else {
            strcpy(sublist2[index2++], permutations[i]);
        }
    }

    recursiveSplit(sublist1, index1, newDecisions, numDecisions);
    recursiveSplit(sublist2, index2, newDecisions, numDecisions);

    free(sublist1);
    free(sublist2);
    free(newDecisions);
}

int main(void) {
    char arrangements[NUM_ARRANGEMENTS][ARRANGEMENT_LENGTH] = {"3321"};
    int totalPermutations = 0;

    for (int i = 0; i < NUM_ARRANGEMENTS; i++) {
        totalPermutations += countUniquePermutations(arrangements[i]);
    }

    char(*permutations)[ARRANGEMENT_LENGTH] = malloc(totalPermutations * sizeof(*permutations));
    if (!permutations) {
        fprintf(stderr, "Failed to allocate memory for permutations\n");
        return 1;
    }

    int index = 0;
    for (int i = 0; i < NUM_ARRANGEMENTS; i++) {
        permute(arrangements[i], 0, strlen(arrangements[i]) - 1, permutations, &index);
    }

    // Find the best split for the entire set
    int bestPosition;
    char bestChar;
    findBestSplit(permutations, totalPermutations, &bestPosition, &bestChar);

    // Split the permutations into two sublists
    char(*sublist1)[ARRANGEMENT_LENGTH] = malloc(totalPermutations * sizeof(*sublist1));
    char(*sublist2)[ARRANGEMENT_LENGTH] = malloc(totalPermutations * sizeof(*sublist2));
    if (!sublist1 || !sublist2) {
        fprintf(stderr, "Failed to allocate memory for sublists\n");
        free(permutations);
        return 1;
    }

    int index1 = 0, index2 = 0;
    for (int i = 0; i < totalPermutations; i++) {
        if (permutations[i][bestPosition] == bestChar) {
            strcpy(sublist1[index1++], permutations[i]);
        } else {
            strcpy(sublist2[index2++], permutations[i]);
        }
    }

    SplitDecision decisions[MAX_STRING_LENGTH]; // Assuming a reasonable maximum depth
    recursiveSplit(permutations, totalPermutations, decisions, 0);

    free(permutations);
    return 0;
}
