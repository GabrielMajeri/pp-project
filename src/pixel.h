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

/// Face or exclusiv intre doi pixeli
pixel pixel_xor(pixel lhs, pixel rhs);

/// Transforma un intreg fara semn intr-un pixel,
/// pentru a putea face XOR cu aceasta valoare
pixel u32_to_pixel(u32 value);

/// Transforma un pixel intr-un intreg fara semn,
/// si seteaza byte-ul cel mai significativ ca 0
u32 pixel_to_u32(pixel p);

#endif
