#ifndef CRYPTO_H
#define CRYPTO_H

#include "image.h"

/// Cheia secreta utilizata la criptare/decriptare
typedef struct {
    /// Valoarea lui R0, seed-ul pentru RNG
    u32 random_init;
    /// Valoarea de initializare are cifrului XOR
    u32 starting_value;
} secret_key;

/// Citeste cheia secreta dintr-un fisier
secret_key crypto_read_key(const char* path);

/// Permuta pixelii dintr-o imagine
image crypto_permute(const u32* perm, image img);


/// Cripteaza pixelii dintr-o imagine cu un cifru XOR
image crypto_cypher(const u32* random, u32 sv, image img);

/// Decripteaza pixelii dintr-o imagine cu un cifru XOR
image crypto_decypher(const u32* random, u32 sv, image img);


/// Realizeaza permutarea si criptarea unei imagini
image crypto_encrypt(secret_key key, image img);

/// Realizeaza decriptarea si permutarea inversa a unei imagini
image crypto_decrypt(secret_key key, image img);

#endif
