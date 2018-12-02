#include "chi.h"

#include "bmp.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

double chi2_channel(image img, intptr_t channel) {
    u32* histogram = (u32*)calloc(256, sizeof(u32));

    u32 width = img.width, height = img.height;
    const pixel* data = img.data;

    for (u32 line = 0; line < height; ++line) {
        for (u32 column = 0; column < width; ++column) {
            const pixel* pixel = &data[line * width + column];
            const u8* pixel_bytes = (u8*)pixel;

            u8 value = *(pixel_bytes + channel);
            ++histogram[value];
        }
    }

    const double estimated = (double)(width * height) / 256;
    double chi = 0;

    for (u32 k = 0; k < 256; ++k) {
        double diff = histogram[k] - estimated;
        chi += (diff * diff) / estimated;
    }

    free(histogram);

    return chi;
}

chi2_values chi2_image(const char* path) {
    image img = bmp_read(path);

    double red = chi2_channel(img, offsetof(pixel, red));
    double green = chi2_channel(img, offsetof(pixel, green));
    double blue = chi2_channel(img, offsetof(pixel, blue));

    image_free(&img);

    chi2_values vals = {
        .red = red,
        .green = green,
        .blue = blue,
    };

    return vals;
}

void chi2_print(chi2_values vals) {
    printf("Rezultatele testului chi^2:\n");
    printf("(R=%.2f, G=%.2f, B=%.2f)\n", vals.red, vals.green, vals.blue);
}
