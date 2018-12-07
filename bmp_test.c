#include "bmp.h"
#include <stdlib.h>

int main() {
    image imagine = bmp_read("test_data/peppers.bmp");
    image subimagine = image_subregion(imagine, rectangle_new(100, 150, 301, 402));

    bmp_write(imagine, "test_data/peppers_copy.bmp");
    bmp_write(subimagine, "test_data/peppers_subimg.bmp");

    image_free(&subimagine);
    image_free(&imagine);
}
