#include "geom.h"
#include "test_utils.h"

void test_dimensions() {
    rectangle r = rectangle_new(16, 42, 30, 200);

    u32 width, height;
    rectangle_dims(r, &width, &height);

    assert_eq(width, 14);
    assert_eq(height, 158);
}

void test_intersection() {
    rectangle a = rectangle_new(15, 60, 200, 100);
    rectangle b = rectangle_new(20, 30, 150, 250);

    rectangle isect = rectangle_intersect(a, b);

    assert_eq(isect.lt.x, 20);
    assert_eq(isect.lt.y, 60);
    assert_eq(isect.rb.x, 150);
    assert_eq(isect.rb.y, 100);
}

int main() {
    test_dimensions();
    test_intersection();
}
