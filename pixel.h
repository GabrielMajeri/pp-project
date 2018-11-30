#ifndef PIXEL_H
#define PIXEL_H

#include "types.h"

/// Un pixel in format R8-G8-B8.
typedef struct {
    /// Canale de culoare
    u8 red, green, blue;
    // compilatorul mai lasa aici 1 byte de padding
} pixel;

/// Transforma un pixel color intr-un pixel cu tonuri de gri
pixel pixel_rgb_to_grayscale(pixel p);

#endif
