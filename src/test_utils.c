#include "test_utils.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EPSILON 0.1

void assert_eq(u32 expected, u32 actual) {
    if (expected != actual) {
        fprintf(stderr, "Test failed:\n");
        fprintf(stderr, "\t%u != %u\n", expected, actual);

        exit(EXIT_FAILURE);
    }
}

void assert_almost_eq(double expected, double actual) {
    double diff = fabs(expected - actual);

    if (diff > EPSILON) {
        fprintf(stderr, "Test failed:\n");
        fprintf(stderr, "\t%lf !~= %lf\n", expected, actual);

        exit(EXIT_FAILURE);
    }
}
