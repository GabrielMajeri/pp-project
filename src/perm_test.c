#include "macro.h"
#include "perm.h"
#include "test_utils.h"

void assert_perm_eq(const u32* expected, const u32* perm, u32 len) {
    for (u32 i = 0; i < len; ++i) {
        assert_eq(expected[i], perm[i]);
    }
}

void test_example_permutation() {
    // exemplu din prezentarea proiectului
    const u32 rng[] = { 3, 1, 1, 2, 0 };
    const u32 expected[] = { 5, 0, 2, 4, 1, 3 };
    const u32 n = ARRAY_LEN(expected);

    u32* perm = perm_generate(rng, n);
    assert_perm_eq(expected, perm, n);

    // calculeaza inversa
    const u32 expected_rev[] = { 1, 4, 2, 5, 3, 0 };
    u32* perm_rev = perm_inverse(perm, n);
    assert_perm_eq(expected_rev, perm_rev, n);

    // verific ca inversa este corecta
    u32* perm_id = perm_identity(n);
    u32* perm_comp = perm_compose(perm_rev, perm, n);
    assert_perm_eq(perm_id, perm_comp, n);

    perm_free(perm_comp);
    perm_free(perm_id);
    perm_free(perm_rev);
    perm_free(perm);
}

int main() {
    test_example_permutation();
}
