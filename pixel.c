#include "pixel.h"

pixel pixel_rgb_to_grayscale(pixel p) {
    u8 aux = 0.299 * p.red + 0.587 * p.green + 0.114 * p.blue;

    p.red = p.blue = p.green = aux;

    return p;
}
