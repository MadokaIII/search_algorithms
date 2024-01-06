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
                "Usage: %s <number of iterations> <algorithm> <step_cost>\n",
                argv[0]);
        exit(EXIT_FAILURE);
    }

    int *infos = calloc(3, sizeof(int));
    int iterations, algorithm, step_cost;
    if (sscanf(argv[2], "%d", &algorithm) != 1 ||
        sscanf(argv[1], "%d", &iterations) != 1 ||
        sscanf(argv[3], "%d", &step_cost) != 1) {
        perror("sscanf failed");
        exit(EXIT_FAILURE);
    }

    switch (algorithm) {
    case 0:
        printf("Using depth first search\n");
        for (int i = 0; i < iterations; i++) {
            State state;
            States path;
            init_state(&state);
            init_states(&path);
            uint8_t array[STATE_WIDTH * STATE_HEIGHT] = {1, 2, 3, 4, 5, 6,
                                                         7, 8, 9, 0, 0, 0};
            random_permutation(array, STATE_WIDTH * STATE_HEIGHT);
            array_to_state(&state, array);
            if (depth_first_search(&state, &path, &infos)) {
                printf("Goal found %d/%d \nSeen States : %d\nCreated States "
                       ": %d \nNumber of Iterations : %d\nSize of the path : "
                       "%llu\n",
                       i + 1, iterations, infos[0], infos[1], infos[2],
                       path.size);
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
        printf("Using iterative deepening\n");
        for (int i = 0; i < iterations; i++) {
            State state;
            States path;
            init_state(&state);
            init_states(&path);
            uint8_t array[STATE_WIDTH * STATE_HEIGHT] = {1, 2, 3, 4, 5, 6,
                                                         7, 8, 9, 0, 0, 0};
            random_permutation(array, STATE_WIDTH * STATE_HEIGHT);
            array_to_state(&state, array);
            if (iterative_deepening(&state, &path, &infos)) {
                printf("Goal found %d/%d \nSeen States : %d\nCreated States "
                       ": %d \nNumber of Iterations : %d\nSize of the path : "
                       "%llu\n",
                       i + 1, iterations, infos[0], infos[1], infos[2],
                       path.size);
                while (path.size > 0) {
                    State *state = pop_state(&path);
                    print_state(state);
                }
            } else {
                printf("Goal not found\n");
            }
        }
        break;
    case 2:
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
                    &state, &path, misplaced_cubes, step_cost, &infos)) {
                printf("Goal found %d/%d \nSeen States : %d\nCreated States "
                       ": %d \nNumber of Iterations : %d\nSize of the path : "
                       "%llu\n",
                       i + 1, iterations, infos[0], infos[1], infos[2],
                       path.size);

                while (path.size > 0) {
                    State *state = pop_state(&path);
                    print_state(state);
                }
            } else {
                printf("Goal not found\n");
            }
        }
        break;
    case 3:
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
                    &state, &path, manhattan_distance, step_cost, &infos)) {
                printf("Goal found %d/%d \nSeen States : %d\nCreated States "
                       ": %d \nNumber of Iterations : %d\nSize of the path : "
                       "%llu\n",
                       i + 1, iterations, infos[0], infos[1], infos[2],
                       path.size);
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
    free(infos);
    return 0;
}
