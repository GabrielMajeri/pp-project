#include "geom.h"

rectangle rectangle_new(u32 left, u32 top, u32 right, u32 bottom) {
    rectangle r = {
        .a = { left, top, },
        .b = { right, bottom, },
    };

    return r;
}

#include <stdio.h>

void rectangle_dims(rectangle r, u32* width, u32* height) {
    *width = r.b.x - r.a.x;
    *height = r.b.y - r.a.y;
}
