#include <state.h>
#include <stdlib.h>

int main(void) {
    State state;
    init_state(&state);
    state_to_array(state, NULL);
    return 0;
}
