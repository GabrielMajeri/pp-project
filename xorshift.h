#ifndef XORSHIFT_H
#define XORSHIFT_H

#include "types.h"

/// Retine starea generatorului pseudorandom XorShift32
typedef struct {
    u32 previous;
} xors32_state;

/// Initializeaza generatorul
xors32_state xors32_init(u32 seed);

/// Genereaza urmatorul numar random
u32 xors32_next(xors32_state* state);

/// Genereaza urmatorul numar random in intervalul [0, max)
u32 xors32_next_range(xors32_state* state, u32 max);

#endif
