/*-----------------------------------------------------------------*/
/** Search Algorithms
 *  @author LAMALMI Daoud
 *  @date 29/11/2023
 *  @file Implementation for States
 **/
/*-----------------------------------------------------------------*/

#include "state.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*-----------------------------------------------------------------*/

void init_state(State *state) {
    memset(state, 0, sizeof(State));
}

void init_movement(Movement *movement) {
    memset(movement, 0, sizeof(Movement));
}

void init_states(States *states) {
    states->size = 0;
    states->stack = NULL;
}

void push_state(States *states, State *state) {
    states->stack = realloc(states->stack, (states->size + 1) * sizeof(State));
    states->stack[states->size] = *state;
    states->size++;
}

State *pop_state(States *states) {
    assert(states->size > 0);
    states->size--;
    return &states->stack[states->size];
}

State *top_state(States *states) {
    assert(states->size > 0);
    return &states->stack[states->size - 1];
}

bool is_state_in_states(States states, State state) {
    for (unsigned long long i = 0; i < states.size; i++) {
        if (is_same_state(states.stack[i], state))
            return true;
    }
    return false;
}

State copy_state(State *state) {
    State copy;
    init_state(&copy);
    memcpy(&copy, state, sizeof(State));
    return copy;
}

bool is_same_state(State s1, State s2) {
    for (int i = 0; i < STATE_WIDTH; i++) {
        if (s1.nb_element[i] != s2.nb_element[i])
            return false;
        for (int j = 0; j < STATE_HEIGHT; j++) {
            if (s1.state[i][j] != s2.state[i][j])
                return false;
        }
    }
    return true;
}

bool is_goal_state(State state) {
    for (int i = 0; i < STATE_WIDTH; i++) {
        if (state.nb_element[i] != 0 && state.nb_element[i] != 3)
            return false;
        for (int j = 0; j < STATE_HEIGHT - 1; j++) {
            if (state.state[i][j] - state.state[i][j + 1] != 1 &&
                state.state[i][j] != 0)
                return false;
        }
    }
    return true;
}

int sum_elements(State *state) {
    int sum = 0;
    for (int i = 0; i < STATE_WIDTH; i++) {
        sum += state->nb_element[i];
    }
    return sum;
}

bool add_element(State *state, uint8_t element, uint8_t index) {
    assert(element <= 9 && element >= 0 && index >= 0 && index < STATE_WIDTH);
    if (state->nb_element[index] == STATE_HEIGHT || sum_elements(state) >= 9)
        return false;
    if (element != 0) {
        state->state[index][state->nb_element[index]] = element;
        state->nb_element[index]++;
    }
    return true;
}

void array_to_state(State *state, uint8_t array[]) {
    init_state(state);
    for (int i = 0; i < STATE_WIDTH; i++) {
        for (int j = 0; j < STATE_HEIGHT; j++) {
            add_element(state, array[i * STATE_HEIGHT + j], i);
        }
    }
}

bool is_movement_valid(State state, Movement movement) {
    assert(sum_elements(&state) == 9);
    return state.nb_element[movement.to] != 3 &&
           state.nb_element[movement.from] != 0;
}

Movement *possible_movements(State state, int *nb_movement) {
    Movement *movements = calloc(STATE_WIDTH * STATE_HEIGHT, sizeof(Movement));
    Movement movement;
    *nb_movement = 0;
    for (int i = 0; i < STATE_WIDTH; i++) {
        for (int j = 0; j < STATE_WIDTH; j++) {
            init_movement(&movement);
            if (i != j) {
                movement.from = i;
                movement.to = j;
                if (is_movement_valid(state, movement)) {
                    movements[*nb_movement] = movement;
                    (*nb_movement)++;
                }
            }
        }
    }
    return movements;
}

States possible_states(State state) {
    int nb_states;
    Movement *movements = possible_movements(state, &nb_states);
    States states;
    init_states(&states);
    for (int i = 0; i < nb_states; i++) {
        push_state(&states, &state);
        apply_movement_to_state(&states.stack[i], movements[i]);
        states.stack[i].predecessor = malloc(sizeof(State));
        if (states.stack[i].predecessor != NULL) {
            *(states.stack[i].predecessor) = copy_state(&state);
        }
    }
    free(movements);
    return states;
}

void apply_movement_to_state(State *state, Movement movement) {
    assert(is_movement_valid(*state, movement));
    state->state[movement.to][state->nb_element[movement.to]] =
        state->state[movement.from][state->nb_element[movement.from] - 1];
    state->state[movement.from][state->nb_element[movement.from] - 1] = 0;
    state->nb_element[movement.from]--;
    state->nb_element[movement.to]++;
}

void state_to_string(State *s, char *buffer) {
    const char *blocks[4] = {"\u2585", "\u2583", "\u2584"};
    char *ptr = buffer;

    // Add the top label
    ptr += sprintf(ptr, "┌─────────────────────┐\n");
    ptr += sprintf(ptr, "│    Current State    │\n");
    ptr += sprintf(ptr, "├─────────────────────┤\n");

    // Add the state grid contents
    for (int j = STATE_HEIGHT - 1; j >= 0; j--) {
        ptr += sprintf(ptr, "│");
        for (int i = 0; i < STATE_WIDTH; i++) {
            int number = s->state[i][j];
            if (number == 0) {
                ptr += sprintf(ptr, "     "); // Adjust for empty cells
            } else {
                const char *block = blocks[number % 3];
                const char *color = ANSI_COLOR_RESET; // Default no color
                if (number <= 3)
                    color = ANSI_COLOR_BLUE;
                else if (number <= 6)
                    color = ANSI_COLOR_RED;
                else if (number <= 9)
                    color = ANSI_COLOR_YELLOW;
                ptr +=
                    sprintf(ptr, "%s  %s  %s", color, block, ANSI_COLOR_RESET);
            }
        }
        ptr += sprintf(ptr, " │\n");
    }

    // Add the bottom label "Number of Elements"
    ptr += sprintf(ptr, "├─────────────────────┤\n");
    ptr += sprintf(ptr, "│ Number of Elements: │\n");

    // Add the number of elements
    ptr += sprintf(ptr, "│");
    for (int i = 0; i < STATE_WIDTH; i++) {
        ptr += sprintf(ptr, "  %d", s->nb_element[i]);
        ptr += sprintf(ptr, "  ");
    }
    ptr += sprintf(ptr, " │\n");

    // Add the bottom border of the box
    ptr += sprintf(ptr, "└─────────────────────┘\n");
}

void print_state(State *s) {
    char stateString[MAX_STATE_STRING_SIZE];
    state_to_string(s, stateString);
    printf("%s", stateString);
}

void print_raw_state(State *s) {
    for (int j = STATE_HEIGHT - 1; j >= 0; j--) {
        for (int i = 0; i < STATE_WIDTH; i++) {
            printf("%d ", s->state[i][j]);
        }
        printf("\n");
    }
}
