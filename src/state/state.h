/*-----------------------------------------------------------------*/
/** Search Algorithms
 *  @author LAMALMI Daoud
 *  @date 29/11/2023
 *  @file Interface for States
 **/
/*-----------------------------------------------------------------*/

#ifndef STATE_H
#define STATE_H
#include <stdbool.h>
#include <stdint.h>
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RESET "\x1b[0m"

/*-----------------------------------------------------------------*/

#define MAX_STATE_STRING_SIZE 1024

/**
 * Defines the height of the State structure.
 */
#define STATE_HEIGHT 3

/**
 * Defines the width of the State structure.
 */
#define STATE_WIDTH 4

/**
 * @struct State
 * @brief Represents a state with three octets.
 *
 * Each octet in the State structure represents a part of the state. The
 * structure is used to encapsulate the state information in a compact form,
 * with each octet representing data points of the state.
 * @note The State structure is not meant to be used as a generic data
 * structure. It is specifically designed to represent the state of the search
 * algorithms.
 */
typedef struct s_state {
    uint8_t state[STATE_WIDTH][STATE_HEIGHT];
    uint8_t nb_element[STATE_WIDTH];
} State;

typedef struct s_movement {
    uint8_t from;
    uint8_t to;
} Movement;

typedef struct s_states {
    State *stack;
    unsigned long long size;
} States;

/*-----------------------------------------------------------------*/

void init_state(State *state);

void init_movement(Movement *movement);

State copy_state(State *state);

bool is_same_state(State s1, State s2);

bool is_goal_state(State state);

int sum_elements(State *state);

bool add_element(State *state, uint8_t element, uint8_t index);

void array_to_state(State *state, uint8_t array[]);

bool is_movement_valid(State state, Movement movement);

Movement *possible_movements(State state, int *nb_movement);

State *possible_states(State state, int *nb_states);

void apply_movement_to_state(State *state, Movement movement);

void print_state(State *state);

void init_states(States *states);

void push_state(States *states, State *state);

State pop_state(States *states);

State top_state(States *states);

bool is_state_in_states(States states, State state);

void print_raw_state(State *s);

#endif // STATE_H
