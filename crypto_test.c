#include "bmp.h"
#include "crypto.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void test_reversible_encryption() {
    secret_key key = crypto_read_key("test_data/secret_key.txt");
    image original = bmp_read("test_data/peppers.bmp");

    image encrypted = crypto_encrypt(key, original);

    image decrypted = crypto_decrypt(key, encrypted);

    bmp_write(decrypted, "peppers_restored.bmp");

    image_free(&decrypted);
    image_free(&encrypted);
    image_free(&original);
}

void test_decrypt_validation_image() {
    secret_key key = crypto_read_key("test_data/secret_key.txt");
    image encrypted = bmp_read("test_data/enc_peppers_ok.bmp");
    image target = bmp_read("test_data/peppers.bmp");

    image decrypted = crypto_decrypt(key, encrypted);

    for (u32 i = 0; i < target.width * target.height; ++i) {
        if (memcmp(&decrypted.data[i], &encrypted.data[i], sizeof(pixel)) != 0) {
            printf("Decrypted image mismatch\n");
            exit(EXIT_FAILURE);
        }
    }

    image_free(&decrypted);
    image_free(&target);
    image_free(&encrypted);
}

int main() {
    test_reversible_encryption();
    //test_decrypt_validation_image();
}
