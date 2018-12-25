#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"
#include "chi.h"
#include "crypto.h"
#include "match.h"

#define MAX_PATH_LEN 1024

void encryption(void) {
    char* path = (char*)malloc(MAX_PATH_LEN);

    printf("Calea imaginii care va fi criptata:\n");
    scanf("%s", path);

    image unencrypted = bmp_read(path);

    printf("Valorile testului Chi^2 pentru imagine necriptata\n");
    chi2_print(chi2_image(path));

    printf("Calea catre fisierul cu cheia secreta:\n");
    scanf("%s", path);

    secret_key key = crypto_read_key(path);

    image encrypted = crypto_encrypt(key, unencrypted);
    image_free(&unencrypted);

    printf("Calea la care sa salvez imaginea criptata:\n");
    scanf("%s", path);

    bmp_write(encrypted, path);
    image_free(&encrypted);

    printf("Valorile testului Chi^2 pentru imaginea criptata\n");
    chi2_print(chi2_image(path));

    free(path);

    printf("\n");
}

void decryption(void) {
    char* path = (char*)malloc(MAX_PATH_LEN);

    printf("Calea imaginii de decriptat:\n");
    scanf("%s", path);

    image encrypted = bmp_read(path);

    printf("Calea fisierului care contine cheia secreta:\n");
    scanf("%s", path);

    secret_key key = crypto_read_key(path);

    image decrypted = crypto_decrypt(key, encrypted);
    image_free(&encrypted);

    printf("Calea la care sa salvez imaginea decriptata:\n");
    scanf("%s", path);

    bmp_write(decrypted, path);
    image_free(&decrypted);

    free(path);

    printf("\n");
}

void template_matching(void) {
    char* path = (char*)malloc(MAX_PATH_LEN);

    printf("Calea directorului in care se afla sabloanele 'cifraX.bmp':\n");
    scanf("%s", path);

    image patterns[10];

    char* image_path = (char*)malloc(MAX_PATH_LEN + 100);

    for (int digit = 0; digit < 10; ++digit) {
        sprintf(image_path, "%s/cifra%d.bmp", path, digit);

        patterns[digit] = bmp_read(image_path);

        image_to_grayscale(patterns[digit]);
    }

    free(image_path);

    printf("Calea imaginii cu cifre:\n");
    scanf("%s", path);

    image digits = bmp_read(path);

    image_to_grayscale(digits);

    matches mat = match_alloc();

    printf("Rulez algoritmul de detectie pentru fiecare cifra...\n");

    for (int digit = 0; digit < 10; ++digit) {
        printf("Caut cifra %d...\n", digit);

        const double threshold = 0.5;
        match_template(&mat, digits, digit, patterns[digit], threshold);
    }

    printf("Sortez detectiile...\n");
    match_sort_det(&mat);

    printf("Elimin non-maximele...\n");
    match_remove_nonmax(&mat);

    for (int i = 0; i < mat.len; ++i) {
        const detection* det = mat.dets + i;

        const u32 colors[] = {
            // cifra 0 - rosu
            0xFF0000,
            // cifra 1 - galben
            0xFFFF00,
            // cifra 2 - verde
            0x00FF00,
            // cifra 3 - cyan
            0x00FFFF,
            // cifra 4 - magenta
            0xFF00FF,
            // cifra 5 - albastru
            0x0000FF,
            // cifra 6 - argintiu
            0xC0C0C0,
            // cifra 7 - portocaliu
            0xFF8C00,
            // cifra 8 - mov
            0x800080,
            // cifra 9 - rosu inchis
            0x800000,
        };

        pixel color = u32_to_pixel(colors[det->digit]);

        image_draw_rect(digits, det->window, color);
    }

    match_free(&mat);

    printf("Introduceti calea la care sa salvez imaginea cu detectiile:\n");
    scanf("%s", path);

    bmp_write(digits, path);

    image_free(&digits);

    for (int digit = 0; digit < 10; ++digit) {
        image_free(&patterns[digit]);
    }

    free(path);

    printf("\n");
}

int main() {
    encryption();

    decryption();

    template_matching();
}
