#include "image.h"

#include <math.h>
#include <stdlib.h>

#include "macro.h"

image image_alloc(u32 width, u32 height) {
    pixel* data = (pixel*)calloc(width * height, sizeof(pixel));

    image imagine = {
        .width = width,
        .height = height,
        .data = data,
    };

    return imagine;
}

void image_free(image* imagine) {
    // dealochez memoria
    free(imagine->data);

    // setez campurile 0 ca sa nu refolosesc din greseala imaginea
    imagine->width = imagine->height = 0;
    imagine->data = NULL;
}

image image_window(image src, rectangle window_rect) {
    int src_width = src.width, src_height = src.height;

    u32 window_width, window_height;
    rectangle_dims(window_rect, &window_width, &window_height);

    // iau in considerare si linia / coloana din centru
    ++window_width;
    ++window_height;

    image result = image_alloc(window_width, window_height);

    const pixel* src_data = src.data;
    pixel* window_data = result.data;

    for (u32 line = 0; line < window_height; ++line) {
        for (u32 column = 0; column < window_width; ++column) {
            int src_line = window_rect.lt.y + line;
            int src_column = window_rect.lt.x + column;

            if (src_line >= 0 && src_column >= 0
                && src_line < src_height && src_column < src_width) {
                u32 window_k = line * window_width + column;
                u32 src_k = src_line * src_width + src_column;

                window_data[window_k] = src_data[src_k];
            }
        }
    }

    return result;
}

void image_to_grayscale(image color) {
    u32 width = color.width, height = color.height;
    pixel* data = color.data;

    for (u32 k = 0; k < width * height; ++k) {
        data[k] = pixel_rgb_to_grayscale(data[k]);
    }
}

double image_mean(image gray) {
    u32 count = gray.width * gray.height;

    double sum = 0.0;

    for (u32 k = 0; k < count; ++k) {
        sum += gray.data[k].red;
    }

    return sum / count;
}

double image_std_dev(image gray) {
    u32 count = gray.width * gray.height;

    double mean = image_mean(gray);
    double sum = 0.0;

    for (u32 k = 0; k < count; ++k) {
        double diff = gray.data[k].red - mean;

        sum += diff * diff;
    }

    return sqrt(sum / (count - 1));
}

double image_correlation(image a, image b) {
    u32 count = a.width * a.height;

    double sigma_a = image_std_dev(a);
    double sigma_b = image_std_dev(b);
    double sigma_term = 1.0 / (sigma_a * sigma_b);

    double sum = 0.0;

    for (u32 k = 0; k < count; ++k) {
        double diff_a = a.data[k].red - sigma_a;
        double diff_b = b.data[k].red - sigma_b;

        sum += diff_a * diff_b * sigma_term;
    }

    return sum / count;
}

void image_draw_rect(image img, rectangle r, pixel color) {
    rectangle img_rect = rectangle_new(0, 0, img.width - 1, img.height - 1);
    rectangle isect = rectangle_intersect(r, img_rect);

    pixel* data = img.data;

    for (int column = isect.lt.x; column <= isect.rb.x; ++column) {
        // marginea de sus
        data[isect.lt.y * img.width + column] = color;

        // marginea de jos
        data[isect.rb.y * img.width + column] = color;
    }

    for (int line = isect.lt.y; line <= isect.rb.y; ++line) {
        // marginea din stanga
        data[line * img.width + isect.lt.x] = color;

        // marginea din dreapta
        data[line * img.width + isect.rb.x] = color;
    }
}
