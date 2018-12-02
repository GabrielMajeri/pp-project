#include "macro.h"
#include "perm.h"
#include "test_utils.h"

int main() {
    // exemplu din prezentarea proiectului
    const u32 rng[] = { 3, 1, 1, 2, 0 };
    const u32 expected[] = { 5, 0, 2, 4, 1, 3 };
    const u32 n = ARRAY_LEN(expected);

    u32* perm = perm_generate(rng, n);

    for (u32 i = 0; i < n; ++i) {
        assert_eq(expected[i], perm[i]);
    }

    perm_free(perm);
}
