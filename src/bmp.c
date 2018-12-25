#include "bmp.h"

#include <stdio.h>
#include <stdlib.h>

static u32 compute_padding(u32 width) {
    if (width % 4 == 0) {
        return 0;
    } else {
        return 4 - (3 * width) % 4;
    }
}

image bmp_read(const char* src) {
    FILE* f = fopen(src, "rb");

    if (!f) {
        fprintf(stderr, "Nu pot deschide fisierul %s\n", src);
        exit(EXIT_FAILURE);
    }

    // citim dimensiunea imaginii

    u32 width = 0;
    fseek(f, 18, SEEK_SET);
    fread(&width, sizeof(width), 1, f);

    u32 height = 0;
    fseek(f, 22, SEEK_SET);
    fread(&height, sizeof(height), 1, f);

    fseek(f, 54, SEEK_SET);

    image imagine = image_alloc(width, height);

    const u32 padding = compute_padding(width);

    for (u32 line = 0; line < height; ++line) {
        for (u32 column = 0; column < width; ++column) {
            u8 bgr[3];

            fread(bgr, sizeof(u8), 3, f);

            pixel p = {
                .blue = bgr[0],
                .green = bgr[1],
                .red = bgr[2],
            };

            imagine.data[width * (height - line - 1) + column] = p;
        }

        // sar peste padding
        fseek(f, padding, SEEK_CUR);
    }

    fclose(f);

    return imagine;
}

// Functie care scrie header-ul pentru un BMP cu pixeli color pe 24 de biti
static void bmp_write_header(FILE* f, u32 width, u32 height) {
    fwrite("BM", sizeof(char), 2, f);

    // calculez dimensiunea in bytes
    u32 size = 54 + width * height * 3;

    // adun padding-ul
    size += height * compute_padding(width);

    fwrite(&size, sizeof(u32), 1, f);

    // bytes rezervati
    const u32 zero = 0;
    fwrite(&zero, sizeof(u32), 1, f);

    u32 offset = 54;
    fwrite(&offset, sizeof(u32), 1, f);

    // Dimensiunea header-ului care urmeaza
    u32 hdr_size = 40;
    fwrite(&hdr_size, sizeof(u32), 1, f);

    // Dimensiuni
    fwrite(&width, sizeof(u32), 1, f);
    fwrite(&height, sizeof(u32), 1, f);

    u16 color_planes = 1;
    fwrite(&color_planes, sizeof(u16), 1, f);

    // Biti per pixel
    u16 bpp = 24;
    fwrite(&bpp, sizeof(u16), 1, f);

    // fara compresie
    u32 compression = 0;
    fwrite(&compression, sizeof(u32), 1, f);

    // image size
    u32 image_size = size - 54;
    fwrite(&image_size, sizeof(u32), 1, f);

    // hor / vert res
    fwrite(&zero, sizeof(u32), 1, f);
    fwrite(&zero, sizeof(u32), 1, f);

    // nr culori
    fwrite(&zero, sizeof(u32), 1, f);
    // nr culori importante
    fwrite(&zero, sizeof(u32), 1, f);
}

void bmp_write(image imagine, const char* dest) {
    FILE* f = fopen(dest, "wb");

    if (!f) {
        fprintf(stderr, "Nu pot deschide fisierul pentru scriere: %s\n", dest);
        exit(EXIT_FAILURE);
    }

    u32 width = imagine.width, height = imagine.height;
    bmp_write_header(f, width, height);

    u32 padding = compute_padding(width);

    for (u32 line = 0; line < height; ++line) {
        for (u32 column = 0; column < width; ++column) {
            pixel p = imagine.data[width * (height - line - 1) + column];

            u8 bgr[3] = { p.blue, p.green, p.red };
            fwrite(bgr, sizeof(u8), 3, f);
        }

        // inserez padding
        const u8 zero = 0;
        for (u32 k = 0; k < padding; ++k) {
            fwrite(&zero, sizeof(u8), 1, f);
        }
    }

    fclose(f);
}
