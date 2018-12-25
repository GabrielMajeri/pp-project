#ifndef MATCH_H
#define MATCH_H

#include <stdbool.h>

#include "geom.h"
#include "image.h"

/// Modulul de template matching

/// Structura care retine o detectie dintr-o imagine
typedef struct {
    /// Fereastra de detectare
    rectangle window;

    /// Scorul de corelatie intre fereastra si sablon
    double corr;

    /// Cifra care a fost detectata
    u8 digit;
} detection;

/// Structura care retine toate detectiile dintr-o imagine, alocate dinamic
typedef struct {
    detection* dets;
    int capacity, len;
} matches;

/// Alocheaza un vector de detectii, initial vid
matches match_alloc(void);

/// Elibereaza memoria alocata pentru un vector de detectii
void match_free(matches* m);

/// Insereaza o dedectie in vectorul de detectii
void match_insert(matches* m, detection d);

/// Cauta un sablon intr-o imagine sursa, si returneaza toate detectiile
void match_template(matches* m, image src, char digit, image pattern, double threshold);

/// Sorteaza detectiile descrescator dupa corelatie
void match_sort_det(matches* m);

/// Verifica daca doua detectii se suprapun
bool match_overlap(const detection* a, const detection* b);

/// Algoritmul de eliminare a non-maximelor,
/// care lucreaza pe un vector de dedectii deja sortat
void match_remove_nonmax(matches* m);

#endif
