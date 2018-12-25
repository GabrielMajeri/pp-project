#ifndef MACRO_H
#define MACRO_H

/// Header cu macro-uri utile

/// Nr. de elemente al unui vector
#define ARRAY_LEN(arr) (sizeof(arr) / sizeof(arr[0]))

/// Returneaza minimul dintre doua valori
#define MIN(a, b) \
    ((a) < (b) ? (a) : (b))

/// Returneaza maximul dintre doua valori
#define MAX(a, b) \
    ((a) > (b) ? (a) : (b))

/// Asigura ca x-ul este in intervalul [min, max]
#define CLAMP(x, min, max) \
    MIN(max, MAX(min, x))

#endif
