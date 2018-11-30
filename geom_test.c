#include "geom.h"
#include "test_utils.h"

int main() {
    rectangle r = rectangle_new(16, 42, 30, 200);

    u32 width, height;
    rectangle_dims(r, &width, &height);

    assert_eq(width, 14);
    assert_eq(height, 158);
}
