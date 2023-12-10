#include "algorithms.h"
#include <state.h>
#include <stdint.h>
#include <stdio.h>

int main(void) {
    State state;
    int nb_movement;
    init_state(&state);
    uint8_t array[STATE_WIDTH * STATE_HEIGHT] = {5, 1, 3, 9, 8, 7,
                                                 6, 2, 4, 0, 0, 0};
    array_to_state(&state, array);
    print_state(&state);
    char *test = depth_first_search(&state) ? "true" : "false";
    print_state(&state);
    printf("%s\n", test);
    return 0;
}
