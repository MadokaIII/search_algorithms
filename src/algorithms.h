/*-----------------------------------------------------------------*/
/** Search Algorithms
 *  @author LAMALMI Daoud
 *  @date 29/11/2023
 *  @file Implementation of search Algorithms
 **/
/*-----------------------------------------------------------------*/

#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include "state.h"
#include <stdbool.h>

/*-----------------------------------------------------------------*/

/**
 * Depth First Search algorithm.
 *
 * @param current The current state.
 * @param path The path to the goal state.
 * @return True if the goal state is found, false otherwise.
 */
bool depth_first_search(State *current, States *path);
/**
 * Depth First Search algorithm with a maximum depth.
 *
 * @param current The current state.
 * @param path The path to the goal state.
 * @param depth_max The maximum depth to search.
 * @return True if the goal state is found within the maximum depth, false
 * otherwise.
 */
bool depth_first_search_capped(State *current, States *path, int depth_max);

/**
 * Iterative Deepening algorithm.
 *
 * @param current The current state.
 * @param path The path to the goal state.
 * @return True if the goal state is found, false otherwise.
 */
bool iterative_deepening(State *current, States *path);

/**
 * Calculate the number of misplaced cubes in the state.
 *
 * @param state The state to evaluate.
 * @return The number of misplaced cubes.
 */
int misplaced_cubes(State state);

/**
 * Calculate the Manhattan distance of the state.
 *
 * @param state The state to evaluate.
 * @return The Manhattan distance.
 */
int manhattan_distance(State state);

/**
 * Calculate the cost function value for a state.
 *
 * @param state The state to evaluate.
 * @param heuristic The heuristic function.
 * @param step_cost The cost of each step.
 * @return The cost function value.
 */
double f(State state, int (*heuristic)(State), int step_cost);

/**
 * Depth First Search algorithm with a maximum depth and heuristic function.
 *
 * @param current The current state.
 * @param path The path to the goal state.
 * @param threshold The threshold value for the heuristic function.
 * @param heuristic The heuristic function.
 * @param step_cost The cost of each step.
 * @return The minimum cost exceeding the threshold.
 */
double depth_first_search_capped_heuristic(State *current, States *path,
                                           double threshold,
                                           int (*heuristic)(State),
                                           int step_cost);
/**
 * Iterative Deepening algorithm with a heuristic function.
 *
 * @param current The current state.
 * @param path The path to the goal state.
 * @param heuristic The heuristic function.
 * @param step_cost The cost of each step.
 * @return True if the goal state is found, false otherwise.
 */
bool iterative_deepening_with_heuristic(State *current, States *path,
                                        int (*heuristic)(State), int step_cost);

#endif // ALGORITHMS_H