/*-----------------------------------------------------------------*/
/** Search Algorithms
 *  @author LAMALMI Daoud
 *  @date 29/11/2023
 *  @file Interface for States
 **/
/*-----------------------------------------------------------------*/

#ifndef STATE_H
#define STATE_H

/*-----------------------------------------------------------------*/

/**
 * Defines the size of the State structure.
 */
#define STATE_SIZE 3

/**
 * @struct State
 * @brief Represents a state with three octets.
 *
 * Each octet in the State structure represents a part of the state. The structure is used
 * to encapsulate the state information in a compact form, with each octet potentially
 * representing different aspects or data points of the state.
 * @note The State structure is not meant to be used as a generic data structure. It is specifically
 * designed to represent the state of the search algorithms.
 */
typedef struct s_state {
    unsigned char octet[STATE_SIZE];
} State;

/*-----------------------------------------------------------------*/

/**
 * @brief Initializes a State struct by setting all its octets to zero.
 *
 * This function sets each octet in the State structure to zero. It serves as an initializer,
 * ensuring that the State starts from a known, zeroed state. This function does not allocate
 * memory but expects a pointer to a pre-allocated State structure.
 *
 * @param state
 *   - Pointer to the State struct to be initialized.
 *   - The state pointer must not be NULL.
 *
 * @post After the function call, each octet in the State is set to zero.
 * @warning
 *   - The function does not perform NULL checking on the input pointer.
 *   - The caller must ensure that the pointer is valid and points to allocated memory for a State.
 */
void init_state(State *state);

/**
 * @brief Prints a character as its binary representation.
 *
 * This function takes a single character (octet) and prints its binary representation
 * to the standard output. It is primarily used for debugging or visualizing the binary
 * state of data.
 *
 * @param octet The character to be printed in binary.
 *
 * @post The binary representation of the octet is printed to stdout.
 */
void print_char_as_binary(unsigned char octet);

/**
 * @brief Prints the binary representation of a State struct.
 *
 * This function prints the binary representation of each octet in the State structure.
 * It is useful for debugging or visualizing the state data in a binary form. The function
 * iterates through each octet of the State and prints it using 'print_char_as_binary'.
 *
 * @param state
 *   - The State struct whose binary representation is to be printed.
 *   - The State struct should be properly initialized.
 *
 * @post The binary representation of the state is printed to stdout, followed by a newline.
 */
void print_state_as_binary(State state);

void state_to_array(State state, unsigned *array);

#endif // STATE_H
