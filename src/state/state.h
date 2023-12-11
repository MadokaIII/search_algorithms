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
    struct s_state *predecessor;
    int depth;
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

/**
 * Initializes a State object by setting all its elements to 0.
 *
 * @param state The State object to initialize.
 */
void init_state(State *state);

/**
 * Initializes a Movement object by setting all its elements to 0.
 *
 * @param movement The Movement object to initialize.
 */
void init_movement(Movement *movement);

/**
 * Initializes a States object by setting its size to 0 and its stack to NULL.
 *
 * @param states The States object to initialize.
 */
void init_states(States *states);

/**
 * Pushes a State object onto the stack of a States object.
 *
 * @param states The States object.
 * @param state The State object to push.
 */
void push_state(States *states, State *state);

/**
 * Pops a State object from the stack of a States object.
 *
 * @param states The States object.
 * @return A pointer to the popped State object.
 */
State *pop_state(States *states);

/**
 * Returns a pointer to the top State object on the stack of a States object.
 *
 * @param states The States object.
 * @return A pointer to the top State object.
 */
State *top_state(States *states);

/**
 * Checks if a State object is present in a States object.
 *
 * @param states The States object.
 * @param state The State object to check.
 * @return true if the State object is present, false otherwise.
 */
bool is_state_in_states(States states, State state);

/**
 * Creates a copy of a State object.
 *
 * @param state The State object to copy.
 * @return The copied State object.
 */
State copy_state(State *state);

/**
 * Checks if two State objects are the same.
 *
 * @param s1 The first State object.
 * @param s2 The second State object.
 * @return true if the State objects are the same, false otherwise.
 */
bool is_same_state(State s1, State s2);

/**
 * Checks if a State object is a goal state.
 *
 * @param state The State object to check.
 * @return true if the State object is a goal state, false otherwise.
 */
bool is_goal_state(State state);

/**
 * Calculates the sum of all elements in a State object.
 *
 * @param state The State object.
 * @return The sum of all elements.
 */
int sum_elements(State *state);

/**
 * Adds an element to a State object at a specified index.
 *
 * @param state The State object.
 * @param element The element to add.
 * @param index The index at which to add the element.
 * @return true if the element was added successfully, false otherwise.
 */
bool add_element(State *state, uint8_t element, uint8_t index);

/**
 * Converts an array of elements to a State object.
 *
 * @param state The State object to populate.
 * @param array The array of elements.
 */
void array_to_state(State *state, uint8_t array[]);

/**
 * Checks if a Movement object is valid for a given State object.
 *
 * @param state The State object.
 * @param movement The Movement object to check.
 * @return true if the Movement object is valid, false otherwise.
 */
bool is_movement_valid(State state, Movement movement);

/**
 * Returns an array of possible Movement objects for a given State object.
 *
 * @param state The State object.
 * @param nb_movement A pointer to an integer to store the number of possible
 * movements.
 * @return An array of possible Movement objects.
 */
Movement *possible_movements(State state, int *nb_movement);

/**
 * Generates all possible States objects that can be reached from a given State
 * object.
 *
 * @param state The State object.
 * @return A States object containing all possible states.
 */
States possible_states(State state);

/**
 * Checks if one State object is a predecessor of another State object.
 *
 * @param a The first State object.
 * @param b The second State object.
 * @return true if a is a predecessor of b, false otherwise.
 */
bool is_predecessor(State *a, State *b);

/**
 * Applies a Movement object to a State object.
 *
 * @param state The State object to modify.
 * @param movement The Movement object to apply.
 */
void apply_movement_to_state(State *state, Movement movement);

/**
 * Prints the contents of a State object.
 *
 * @param state The State object to print.
 */
void print_state(State *state);

/**
 * Prints the raw contents of a State object.
 *
 * @param state The State object to print.
 */
void print_raw_state(State *state);

#endif // STATE_H