#include "algorithms.h"
#include <state.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void random_permutation(uint8_t *array, int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1); // Get a random index from 0 to i
        // Swap array[i] and array[j]
        uint8_t temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

int main(int argc, char **argv) {
    srand(time(NULL));

    if (argc != 4) {
        fprintf(stderr,
                "Usage: %s <number of iterations> <heuristic> <step_cost>\n",
                argv[0]);
        exit(EXIT_FAILURE);
    }

    int iterations, heuristic, step_cost;
    if (sscanf(argv[2], "%d", &heuristic) != 1 ||
        sscanf(argv[1], "%d", &iterations) != 1 ||
        sscanf(argv[3], "%d", &step_cost) != 1) {
        perror("sscanf failed");
        exit(EXIT_FAILURE);
    }
    switch (heuristic) {
    case 0:
        printf("Using misplaced cubes heuristic\n");
        for (int i = 0; i < iterations; i++) {
            State state;
            States path;
            init_state(&state);
            init_states(&path);
            uint8_t array[STATE_WIDTH * STATE_HEIGHT] = {1, 2, 3, 4, 5, 6,
                                                         7, 8, 9, 0, 0, 0};
            random_permutation(array, STATE_WIDTH * STATE_HEIGHT);
            array_to_state(&state, array);
            if (iterative_deepening_with_heuristic(
                    &state, &path, misplaced_cubes, step_cost)) {
                printf("Goal found %d/%d \n", i + 1, iterations);
                while (path.size > 0) {
                    State *state = pop_state(&path);
                    print_state(state);
                }
            } else {
                printf("Goal not found\n");
            }
        }
        break;
    case 1:
        printf("Using Manhattan distance heuristic\n");
        for (int i = 0; i < iterations; i++) {
            State state;
            States path;
            init_state(&state);
            init_states(&path);
            uint8_t array[STATE_WIDTH * STATE_HEIGHT] = {1, 2, 3, 4, 5, 6,
                                                         7, 8, 9, 0, 0, 0};
            random_permutation(array, STATE_WIDTH * STATE_HEIGHT);
            array_to_state(&state, array);
            if (iterative_deepening_with_heuristic(
                    &state, &path, manhattan_distance, step_cost)) {
                printf("Goal found %d/%d \n", i + 1, iterations);
                while (path.size > 0) {
                    State *state = pop_state(&path);
                    print_state(state);
                }
            } else {
                printf("Goal not found\n");
            }
        }
        break;
    default:
        printf("Invalid heuristic\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}