#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bmp.h"
#include "crypto.h"
#include "perm.h"
#include "xorshift.h"

void assert_image_eq(image expected, image actual, const char* image_name) {
    for (u32 i = 0; i < expected.width * expected.height; ++i) {
        if (memcmp(&expected.data[i], &actual.data[i], sizeof(pixel)) != 0) {
            printf("Image mismatch: %s\n", image_name);
            exit(EXIT_FAILURE);
        }
    }
}

void test_reversible_encryption() {
    secret_key key = crypto_read_key("test_data/secret_key.txt");
    image original = bmp_read("test_data/peppers.bmp");

    image encrypted = crypto_encrypt(key, original);

    image decrypted = crypto_decrypt(key, encrypted);

    bmp_write(decrypted, "test_data/peppers_restored.bmp");

    image_free(&decrypted);
    image_free(&encrypted);
    image_free(&original);
}

void test_decrypt_validation_image() {
    secret_key key = crypto_read_key("test_data/secret_key.txt");
    image encrypted = bmp_read("test_data/enc_peppers_ok.bmp");
    image target = bmp_read("test_data/peppers.bmp");

    image decrypted = crypto_decrypt(key, encrypted);

    assert_image_eq(target, decrypted, "encrypted peppers");

    image_free(&decrypted);
    image_free(&target);
    image_free(&encrypted);
}

void test_permute_validation_image() {
    secret_key key = crypto_read_key("test_data/imagine5x5/secret_key.txt");

    image original = bmp_read("test_data/imagine5x5/imagine_5x5.bmp");

    // calculez imaginea permutata
    u32 perm_len = original.width * original.height;

    u32* random_numbers = (u32*)calloc(perm_len - 1, sizeof(u32));
    xors32_vector(key.random_init, perm_len - 1, random_numbers);

    u32* perm = perm_generate(random_numbers, perm_len);

    image permuted = crypto_permute(perm, original);

    free(random_numbers);
    perm_free(perm);
    image_free(&original);

    // compar cu imaginea corecta
    image expected = bmp_read("test_data/imagine5x5/permuted_imagine_5x5.bmp");

    assert_image_eq(expected, permuted, "permuted 5x5");

    image_free(&expected);
    image_free(&permuted);
}

void test_decrypt_5x5_validation_image() {
    secret_key key = crypto_read_key("test_data/imagine5x5/secret_key.txt");

    image original = bmp_read("test_data/imagine5x5/imagine_5x5.bmp");
    image encrypted = bmp_read("test_data/imagine5x5/enc_imagine_5x5.bmp");

    image decrypted = crypto_decrypt(key, encrypted);

    assert_image_eq(original, decrypted, "decrypted 5x5");

    image_free(&decrypted);
    image_free(&encrypted);
    image_free(&original);
}

int main() {
    test_permute_validation_image();
    test_reversible_encryption();
    test_decrypt_5x5_validation_image();
    test_decrypt_validation_image();
}
