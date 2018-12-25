#include "geom.h"

#include "macro.h"

rectangle rectangle_new(int left, int top, int right, int bottom) {
    rectangle r = {
        .lt = { left, top, },
        .rb = { right, bottom, },
    };

    return r;
}

void rectangle_dims(rectangle r, u32* width, u32* height) {
    *width = r.rb.x - r.lt.x;
    *height = r.rb.y - r.lt.y;
}

rectangle rectangle_intersect(rectangle a, rectangle b) {
    if ((a.rb.x < b.lt.x) || (a.rb.y < b.lt.y)
        || (b.rb.x < a.lt.x) || (b.rb.y < a.lt.y)) {
        return rectangle_new(0, 0, 0, 0);
    }

    return rectangle_new(MAX(a.lt.x, b.lt.x), MAX(a.lt.y, b.lt.y),
        MIN(a.rb.x, b.rb.x), MIN(a.rb.y, b.rb.y));
}

u32 rectangle_area(rectangle r) {
    u32 width, height;
    rectangle_dims(r, &width, &height);

    return width * height;
}

double rectangle_overlap(rectangle a, rectangle b) {
    rectangle isect = rectangle_intersect(a, b);

    double isect_area = rectangle_area(isect);
    double union_area = rectangle_area(a) + rectangle_area(b) - isect_area;

    return isect_area / union_area;
}
