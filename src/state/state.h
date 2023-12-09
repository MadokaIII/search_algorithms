/*-----------------------------------------------------------------*/
/** Search Algorithms
 *  @author LAMALMI Daoud
 *  @date 29/11/2023
 *  @file Interface for States
 **/
/*-----------------------------------------------------------------*/

#ifndef STATE_H
#define STATE_H
#include <stdint.h>
#include <string.h>

/*-----------------------------------------------------------------*/

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
typedef uint8_t State[STATE_WIDTH][STATE_HEIGHT];

/*-----------------------------------------------------------------*/

void init_state(State *state);

#endif // STATE_H
