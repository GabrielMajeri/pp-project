#include "perm.h"

#include <stdlib.h>

static u32* perm_alloc(u32 len) {
    return (u32*)calloc(len, sizeof(u32));
}

u32* perm_identity(u32 len) {
    u32* perm = perm_alloc(len);

    for (u32 k = 0; k < len; ++k) {
        perm[k] = k;
    }

    return perm;
}

void perm_free(u32* perm) {
    free(perm);
}

u32* perm_generate(const u32* random, u32 len) {
    // initializez cu permutarea identica
    u32* perm = perm_identity(len);

    for (u32 k = len - 1; k >= 1; --k) {
        u32 idx = *random++ % (k + 1);

        // swap
        u32 tmp = perm[k];
        perm[k] = perm[idx];
        perm[idx] = tmp;
    }

    return perm;
}

u32* perm_reverse(const u32* perm, u32 len) {
    u32* rev = perm_alloc(len);

    for (u32 k = 0; k < len; ++k) {
        rev[perm[k]] = k;
    }

    return rev;
}
