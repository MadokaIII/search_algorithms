/*-----------------------------------------------------------------*/
/** Search Algorithms
 *  @author LAMALMI Daoud
 *  @date 29/11/2023
 *  @file Implementation of search Algorithms
 **/
/*-----------------------------------------------------------------*/

#include "state.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*-----------------------------------------------------------------*/

bool depth_first_search(State *current) {
    States pending, seen;
    State next, *sub_states;
    int nb_states = 0;
    init_states(&pending);
    init_states(&seen);
    init_state(&next);
    push_state(&pending, current);
    while (pending.size > 0) {
        next = pop_state(&pending);
        push_state(&seen, &next);
        print_state(&next);
        if (is_goal_state(next)) {
            *current = copy_state(&next);
            printf("Goal state found!\n");
            return true;
        } else {
            sub_states = possible_states(next, &nb_states);
            for (int i = 0; i < nb_states; i++) {
                if (!is_state_in_states(pending, sub_states[i]) &&
                    !is_state_in_states(seen, sub_states[i]))
                    push_state(&pending, &sub_states[i]);
            }
        }
        free(sub_states);
    }
    return false;
}