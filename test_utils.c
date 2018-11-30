#include "test_utils.h"

#include <stdio.h>
#include <stdlib.h>

void assert_eq(u32 expected, u32 actual) {
    if (expected != actual) {
        fprintf(stderr, "Test failed:\n");
        fprintf(stderr, "\t%u != %u\n", expected, actual);

        exit(EXIT_FAILURE);
    }
}
