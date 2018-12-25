#ifndef BMP_H
#define BMP_H

#include "image.h"

/// Citire / scriere pentru formatul BMP

/// Citeste un fisier bitmap in memorie
image bmp_read(const char* src);

/// Salveaza o imagine intr-un fisier BMP pe disk
void bmp_write(image img, const char* dest);

#endif
