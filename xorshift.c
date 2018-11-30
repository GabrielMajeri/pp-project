#include "xorshift.h"

xors32_state xors32_init(u32 seed) {
    xors32_state state = {
        .previous = seed,
    };

    return state;
}

u32 xors32_next(xors32_state* state) {
    u32 r = state->previous;

    r ^= r << 13;
    r ^= r >> 17;
    r ^= r << 5;

    state->previous = r;

    return r;
}
