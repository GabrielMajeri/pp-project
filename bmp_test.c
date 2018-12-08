#include "bmp.h"
#include <stdlib.h>

int main() {
    image imagine = bmp_read("test_data/peppers.bmp");

    bmp_write(imagine, "test_data/peppers_copy.bmp");

    rectangle window_rect = rectangle_new(-100, -50, 200, 810);

    image window = image_window(imagine, window_rect);
    bmp_write(window, "test_data/peppers_window.bmp");

    image_free(&window);
    image_free(&imagine);
}
