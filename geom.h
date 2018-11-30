#ifndef GEOM_H
#define GEOM_H

#include "types.h"

/// Tipuri de date si functii legate de geometrie

/// Un punct din plan
typedef struct {
    /// Coordonatele X si Y ale punctului
    u32 x, y;
} point;

/// Un dreptunghi, identificat prin coltul
/// stanga-sus si cel dreapta-jos
typedef struct {
    point a, b;
} rectangle;

/// Construieste un nou dreptunghi din coordonate
rectangle rectangle_new(u32 left, u32 top, u32 right, u32 bottom);

/// Calculeaza latimea si inaltimea unui dreptunghi
void rectangle_dims(rectangle r, u32* width, u32* height);

#endif
