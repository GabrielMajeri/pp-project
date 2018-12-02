#include "pixel.h"

pixel pixel_rgb_to_grayscale(pixel p) {
    u8 aux = 0.299 * p.red + 0.587 * p.green + 0.114 * p.blue;

    p.red = p.blue = p.green = aux;

    return p;
}

pixel pixel_xor(pixel lhs, pixel rhs) {
    lhs.red ^= rhs.red;
    lhs.green ^= rhs.green;
    lhs.blue ^= rhs.blue;

    return lhs;
}

pixel u32_to_pixel(u32 value) {
    pixel p = {
        .blue = (u8)(value),
        .green = (u8)(value >> 8),
        .red = (u8)(value >> 16),
    };

    return p;
}

u32 pixel_to_u32(pixel p) {
    u32 low = p.blue;
    u32 middle = p.green;
    u32 high = p.red;

    return (high << 16) | (middle << 8) | low;
}
