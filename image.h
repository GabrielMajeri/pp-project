#ifndef IMAGE_H
#define IMAGE_H

#include "pixel.h"
#include "geom.h"

/// Operatii cu imagini

/// O imagine este o regiune dreptunghiulara de pixeli
typedef struct {
    u32 width, height;
    pixel* data;
} image;

/// Alocheaza o imagine cu NxM pixeli
image image_alloc(u32 width, u32 height);
/// Elibereaza memoria unei imagini
void image_free(image* img);

/// Extrage un dreptunghi dintr-o imagine sursa
image image_subregion(image src, rectangle r);

#endif
