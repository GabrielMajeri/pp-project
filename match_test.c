#include "bmp.h"
#include "image.h"
#include "match.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    image patterns[10];

    for (int i = 0; i < 10; ++i) {
        char path[100];
        sprintf(path, "test_data/cifra%d.bmp", i);

        patterns[i] = bmp_read(path);

        image_to_grayscale(patterns[i]);
    }

    image digits = bmp_read("test_data/test.bmp");

    image_to_grayscale(digits);

    matches mat = match_alloc();

    const double threshold = 0.5;

    match_template(&mat, digits, patterns, threshold);

    match_sort_det(&mat);
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

    bmp_write(digits, "recognized.bmp");

    image_free(&digits);

    for (int i = 0; i < 10; ++i) {
        image_free(&patterns[i]);
    }
}
