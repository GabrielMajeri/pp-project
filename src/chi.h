#ifndef CHI_H
#define CHI_H

#include "image.h"

/// Calculeaza valorea testului χ^2 pentru un canal al unei imagini.
/// Canalul este specificat prin offset-ul in bytes in fiecare pixel.
double chi2_channel(image img, intptr_t channel);

/// Rezultatul testului χ^2 pentru
typedef struct {
    double red, green, blue;
} chi2_values;

/// Calculeaza valorile testului χ^2 pentru o imagine BMP
chi2_values chi2_image(const char* path);

/// Afiseaza rezultatuletestului χ^2
void chi2_print(chi2_values values);

#endif
