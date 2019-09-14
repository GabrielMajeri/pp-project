#include "crypto.h"

#include <stdio.h>
#include <stdlib.h>

#include "perm.h"
#include "xorshift.h"

secret_key crypto_read_key(const char* path) {
    FILE* f = fopen(path, "r");

    if (!f) {
        printf("Nu pot deschide fisierul %s\n", path);
        exit(EXIT_FAILURE);
    }

    secret_key key;

    if (fscanf(f, "%u %u", &key.random_init, &key.starting_value) != 2) {
        printf("Nu pot citi cheia secretă din fișier\n");
        exit(EXIT_FAILURE);
    }

    fclose(f);

    return key;
}

image crypto_permute(const u32* perm, image img) {
    u32 width = img.width, height = img.height;
    u32 len = width * height;

    image result = image_alloc(width, height);

    for (u32 k = 0; k < len; ++k) {
        result.data[perm[k]] = img.data[k];
    }

    return result;
}

#define CYPHER_INIT_CODE \
    pixel previous = u32_to_pixel(sv); \
    u32 width = img.width, height = img.height; \
    u32 len = width * height; \
    image result = image_alloc(width, height); \
    const pixel* src_data = img.data; \
    pixel* dest_data = result.data;

image crypto_cypher(const u32* random, u32 sv, image img) {
    CYPHER_INIT_CODE

    for (u32 k = 0; k < len; ++k) {
        pixel current = *src_data++;

        pixel random_pixel = u32_to_pixel(*random++);

        pixel cyphered = pixel_xor(pixel_xor(previous, current), random_pixel);

        previous = *dest_data++ = cyphered;
    }

    return result;
}

image crypto_decypher(const u32* random, u32 sv, image img) {
    CYPHER_INIT_CODE

    for (u32 k = 0; k < len; ++k) {
        pixel current = *src_data++;

        pixel random_pixel = u32_to_pixel(*random++);

        pixel decyphered = pixel_xor(pixel_xor(previous, current), random_pixel);

        *dest_data++ = decyphered;

        previous = src_data[-1];
    }

    return result;
}

#define ENCRYPTION_INIT_CODE \
    const u32 width = img.width, height = img.height; \
    u32 len = 2 * width * height - 1; \
    u32* random_nums = (u32*)calloc(len, sizeof(u32)); \
    xors32_vector(key.random_init, len, random_nums); \
    const u32* random_nums_perm = random_nums; \
    const u32* random_nums_cypher = random_nums + width * height - 1; \
    u32 perm_length = width * height; \
    u32* perm = perm_generate(random_nums_perm, perm_length);

image crypto_encrypt(secret_key key, image img) {
    ENCRYPTION_INIT_CODE

    image permuted = crypto_permute(perm, img);
    image encrypted = crypto_cypher(random_nums_cypher, key.starting_value, permuted);

    image_free(&permuted);
    free(random_nums);
    perm_free(perm);

    return encrypted;
}

image crypto_decrypt(secret_key key, image img) {
    ENCRYPTION_INIT_CODE

    u32* inverse = perm_inverse(perm, perm_length);

    image decyphered = crypto_decypher(random_nums_cypher, key.starting_value, img);
    image decrypted = crypto_permute(inverse, decyphered);

    image_free(&decyphered);
    perm_free(perm);
    perm_free(inverse);
    free(random_nums);

    return decrypted;
}
