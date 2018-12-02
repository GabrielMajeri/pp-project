#ifndef PERM_H
#define PERM_H

#include "types.h"

/// Functii pentru generat permutari

/// Alocheaza permutarea identitate
u32* perm_identity(u32 len);

/// Dealocheaza o permutare
void perm_free(u32* perm);

/// Genereaza o permutare aleatoare folosind algoritmul lui Durstenfeld
/// - `len` este ordinul permutarii
/// - `random` trebuie sa contina `len-1` numere random
u32* perm_generate(const u32* random, u32 len);

/// Genereaza permutarea inversa a unei permutari existente
u32* perm_inverse(const u32* perm, u32 len);

/// Compune doua permutari intr-o permutare noua
u32* perm_compose(const u32* lhs, const u32* rhs, u32 len);

#endif
