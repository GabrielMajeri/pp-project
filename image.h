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

/// Extrage o fereastra cu un anumit centru dintr-o imagine.
/// Pixelii care ies din imagine vor fi colorati negru.
image image_window(image src, rectangle window_rect);

/// Converteste o imagine color intr-un cu tonuri de gri
void image_to_grayscale(image color);

/// Calculeaza media aritmetica a intensitatilor pixelilor
/// dintr-o imagine cu tonuri de gri
double image_mean(image img);

/// Calculeaza deviatia standard a intensitatilor pixelilor
/// dintr-o imagine cu tonuri de gri
double image_std_dev(image gray);

/// Calculeaza corelatia dintre doua imagini cu tonuri de gri
double image_correlation(image a, image b);

/// Deseneaza un dreptunghi colorat pe imagine
void image_draw_rect(image img, rectangle r, pixel color);

#endif
