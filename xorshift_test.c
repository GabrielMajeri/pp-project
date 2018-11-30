#include "macro.h"
#include "test_utils.h"
#include "xorshift.h"

void test_input(u32 seed, const u32* valid, int n) {
    xors32_state state = xors32_init(seed);

    for (int i = 0; i < n; ++i) {
        const u32 expected = valid[i];
        const u32 result = xors32_next(&state);

        assert_eq(expected, result);
    }
}

int main() {
    // testez cu exemplele din prezentarea proiectului
    const u32 seed = 1000;
    const u32 valid[] = {
        266172694,
        3204629577,
        385443340,
        2099747088,
        1321081938,
        733430728,
        3121244111,
        680290934,
    };

    test_input(seed, valid, ARRAY_LEN(valid));
}
