#include "bmp.h"
#include <stdlib.h>

int main() {
    image imagine = bmp_read("test_data/peppers.bmp");
    image subimagine = image_subregion(imagine, rectangle_new(100, 150, 301, 402));

    bmp_write(imagine, "copy.bmp");
    bmp_write(subimagine, "subimg.bmp");

    image_free(&subimagine);
    image_free(&imagine);
}
