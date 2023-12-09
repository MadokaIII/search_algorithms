#include <state.h>
#include <stdio.h>

int main(void) {
    State state;
    init_state(&state);
    printf("%d\n", state[0][0]);
    return 0;
}
