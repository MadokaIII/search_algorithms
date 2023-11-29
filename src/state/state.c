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
    assert(state != NULL);
    memset(state, 0, STATE_SIZE);
}

void print_char_as_binary(unsigned char octet) {
    for (int i = 7; i >= 0; i--) {
        putchar((octet & (1 << i)) ? '1' : '0');
    }
}

void print_state_as_binary(State state) {
    for (unsigned long i = 0; i < STATE_SIZE; i++) {
        print_char_as_binary(((unsigned char *)&state)[i]);
    }
    printf("\n");
}
