#include "image.h"

#include <stdlib.h>

image image_alloc(u32 width, u32 height) {
    pixel* data = (pixel*)calloc(width * height, sizeof(pixel));

    image imagine = {
        .width = width,
        .height = height,
        .data = data,
    };

    return imagine;
}

void image_free(image* imagine) {
    // dealochez memoria
    free(imagine->data);

    // setez campurile 0 ca sa nu refolosesc din greseala imaginea
    imagine->width = imagine->height = 0;
    imagine->data = NULL;
}

image image_subregion(image src, rectangle r) {
    u32 width, height;
    rectangle_dims(r, &width, &height);

    image result = image_alloc(width, height);

    u32 offset_x = r.a.x,
        offset_y = r.a.y;

    const u32 src_width = src.width;

    const pixel* src_data = src.data;
    pixel* dest_data = result.data;

    // copiez pixelii in destinatie
    for (u32 line = 0; line < height; ++line) {
        u32 src_line = offset_y + line;

        for (u32 column = 0; column < width; ++column) {
            u32 src_column = offset_x + column;

            pixel p = src_data[src_line * src_width + src_column];
            dest_data[line * width + column] = p;
        }
    }

    return result;
}
