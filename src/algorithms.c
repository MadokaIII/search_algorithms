/*-----------------------------------------------------------------*/
/** Search Algorithms
 *  @author LAMALMI Daoud
 *  @date 29/11/2023
 *  @file Implementation of search Algorithms
 **/
/*-----------------------------------------------------------------*/

#include "state.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*-----------------------------------------------------------------*/

bool depth_first_search(State *current, States *path, int **infos) {
    States pending, seen, sub_states;
    State next;
    init_states(&pending);
    init_states(&seen);
    init_state(&next);
    push_state(&pending, current);
    while (pending.size > 0) {
        (*infos)[2]++;
        next = *pop_state(&pending);
        push_state(&seen, &next);
        if (is_goal_state(next)) {
            *current = copy_state(&next);
            printf("Goal state found!\n");
            *infos[0] = seen.size;
            State *state = current;
            while (state->predecessor != NULL) {
                push_state(path, state);
                state = state->predecessor;
            }
            return true;
        } else {
            sub_states = possible_states(next);
            for (unsigned long long i = 0; i < sub_states.size; i++) {
                (*infos)[1]++;
                if (!is_state_in_states(pending, sub_states.stack[i]) &&
                    !is_state_in_states(seen, sub_states.stack[i])) {
                    push_state(&pending, &sub_states.stack[i]);
                }
            }
        }
    }
    for (unsigned long long i = 0; i < sub_states.size; i++) {
        free(sub_states.stack[i].predecessor);
    }
    free(sub_states.stack);
    printf("Goal state not found!\n");
    return false;
}

bool depth_first_search_capped(State *current, States *path, int depth_max,
                               int **infos) {
    States pending, seen, sub_states;
    State next;
    init_states(&pending);
    init_states(&seen);
    init_state(&next);
    push_state(&pending, current);
    pending.stack[0].depth = 0;
    while (pending.size > 0) {
        (*infos)[2]++;
        next = *pop_state(&pending);
        push_state(&seen, &next);
        if (is_goal_state(next)) {
            *current = copy_state(&next);
            *infos[0] = seen.size;
            printf("Goal state found on depth %d!\n", depth_max);
            State *state = current;
            while (state->predecessor != NULL) {
                push_state(path, state);
                state = state->predecessor;
            }
            return true;
        } else {
            sub_states = possible_states(next);
            for (unsigned long long i = 0; i < sub_states.size; i++) {
                (*infos)[1]++;
                sub_states.stack[i].depth = next.depth + 1;
                if (!is_state_in_states(pending, sub_states.stack[i]) &&
                    !is_state_in_states(seen, sub_states.stack[i]) &&
                    sub_states.stack[i].depth <= depth_max)
                    push_state(&pending, &sub_states.stack[i]);
            }
        }
    }
    for (unsigned long long i = 0; i < sub_states.size; i++) {
        free(sub_states.stack[i].predecessor);
    }
    free(sub_states.stack);
    printf("Goal state not found on depth %d!\n", depth_max);
    return false;
}

bool iterative_deepening(State *current, States *path, int **infos) {
    for (int i = 0; i < 100; i++) {
        if (depth_first_search_capped(current, path, i, infos))
            return true;
    }
    return false;
}

int misplaced_cubes(State state) {
    int misplaced = 0;
    for (int i = 0; i < STATE_WIDTH; i++) {
        if (state.nb_element[i] != 0 && state.nb_element[i] != 3)
            misplaced++;
        for (int j = 0; j < STATE_HEIGHT - 1; j++) {
            if (state.state[i][j] - state.state[i][j + 1] != 1 &&
                state.state[i][j] != 0)
                misplaced++;
        }
    }
    return misplaced;
}

int manhattan_distance(State state) {
    int distance = 0;
    for (int i = 0; i < STATE_WIDTH; i++) {
        if (state.nb_element[i] != 0 && state.nb_element[i] != 3)
            distance++;
        for (int j = 0; j < STATE_HEIGHT - 1; j++) {
            int element = state.state[i][j];
            if (element != 0) {
                int goal_i = (element - 1) / STATE_HEIGHT;
                int goal_j = (element - 1) % STATE_HEIGHT;
                if (element - state.state[i][j + 1] != 1)
                    distance += abs(i - goal_i) + abs(j - goal_j);
            }
        }
    }
    return distance;
}

double f(State state, int (*heuristic)(State), int step_cost) {
    return (state.depth * step_cost) + heuristic(state);
}

double depth_first_search_capped_heuristic(State *current, States *path,
                                           double threshold,
                                           int (*heuristic)(State),
                                           int step_cost, int **infos) {
    States pending, seen;
    State next;
    double min_cost_exceeding_threshold = INT_MAX;
    init_states(&pending);
    init_states(&seen);
    push_state(&pending, current);
    pending.stack[0].depth = 0;
    while (pending.size > 0) {
        (*infos)[2]++;
        next = *pop_state(&pending);
        push_state(&seen, &next);
        if (is_goal_state(next)) {
            *current = copy_state(&next);
            *infos[0] = seen.size;
            State *state = current;
            while (state->predecessor != NULL) {
                push_state(path, state);
                state = state->predecessor;
            }
            return -1;
        } else {
            States sub_states = possible_states(next);
            for (unsigned long long i = 0; i < sub_states.size; i++) {
                (*infos)[1]++;
                sub_states.stack[i].depth = next.depth + 1;
                double cost = f(sub_states.stack[i], heuristic, step_cost);
                if (cost <= threshold &&
                    !is_state_in_states(pending, sub_states.stack[i]) &&
                    !is_state_in_states(seen, sub_states.stack[i])) {
                    push_state(&pending, &sub_states.stack[i]);
                } else if (cost > threshold) {
                    min_cost_exceeding_threshold =
                        min_cost_exceeding_threshold < cost
                            ? min_cost_exceeding_threshold
                            : cost;
                }
            }
        }
    }
    return min_cost_exceeding_threshold;
}

bool iterative_deepening_with_heuristic(State *current, States *path,
                                        int (*heuristic)(State), int step_cost,
                                        int **infos) {
    double threshold = misplaced_cubes(*current);
    while (true) {
        double temp = depth_first_search_capped_heuristic(
            current, path, threshold, heuristic, step_cost, infos);
        if (temp == -1)
            if (temp == -1)
                return true;
        if (temp == INT_MAX)
            return false;
        threshold = temp;
    }
}