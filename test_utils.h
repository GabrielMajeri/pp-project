#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "types.h"

/// Verifica ca doua numere sunt egale,
/// altfel iese din program cu un error code
void assert_eq(u32 expected, u32 actual);

#endif
