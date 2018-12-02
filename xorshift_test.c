#include "macro.h"
#include "test_utils.h"
#include "xorshift.h"

void test_input(u32 seed, const u32* valid, u32 len) {
    u32 generated[len];
    xors32_vector(seed, len, generated);

    for (u32 i = 0; i < len; ++i) {
        assert_eq(valid[i], generated[i]);
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
