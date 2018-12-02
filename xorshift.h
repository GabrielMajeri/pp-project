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

/// Genereaza un vector de numere random, plecand de la un seed
void xors32_vector(u32 seed, u32 len, u32* dest);

#endif
