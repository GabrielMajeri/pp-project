#ifndef GEOM_H
#define GEOM_H

#include "types.h"

/// Tipuri de date si functii legate de geometrie

/// Un punct din plan
typedef struct {
    /// Coordonatele X si Y ale punctului
    int x, y;
} point;

/// Un dreptunghi, identificat prin coltul
/// stanga-sus si cel dreapta-jos
typedef struct {
    point lt, rb;
} rectangle;

/// Construieste un nou dreptunghi din coordonate
rectangle rectangle_new(int left, int top, int right, int bottom);

/// Calculeaza latimea si inaltimea unui dreptunghi
void rectangle_dims(rectangle r, u32* width, u32* height);

/// Calculeaza intersectia a doua dreptunghiuri.
rectangle rectangle_intersect(rectangle a, rectangle b);

#endif
