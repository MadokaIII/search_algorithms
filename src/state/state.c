/*-----------------------------------------------------------------*/
/** Search Algorithms
 *  @author LAMALMI Daoud
 *  @date 29/11/2023
 *  @file Interface for States
 **/
/*-----------------------------------------------------------------*/

#include "state.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

/*-----------------------------------------------------------------*/

void init_state(State *state) {
    memset(state, 0, sizeof(State));
}
