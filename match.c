#include "match.h"

#include <stdlib.h>
#include <stdio.h>

#include "bmp.h"

matches match_alloc(void) {
    matches m;

    const int initial_cap = 1024;

    m.dets = (detection*)calloc(initial_cap, sizeof(detection));
    m.capacity = initial_cap;
    m.len = 0;

    return m;
}

void match_free(matches* m) {
    free(m->dets);
    m->dets = NULL;
    m->len = m->capacity = 0;
}

void match_insert(matches* m, detection d) {
    if (m->len == m->capacity) {
        m->capacity *= 2;

        detection* new_dets = realloc(m->dets, m->capacity * sizeof(detection));

        if (new_dets == NULL) {
            free(m->dets);

            printf("Nu pot aloca suficienta memorie\n");
            exit(EXIT_FAILURE);
        } else {
            m->dets = new_dets;
        }
    }

    m->dets[m->len++] = d;
}

void match_template(matches* m, image src,
    const image* patterns, double threshold) {
    u32 pattern_width = patterns[0].width, pattern_height = patterns[0].height;

    for (u32 line = 0; line < src.height; ++line) {
        for (u32 column = 0; column < src.width; ++column) {
            point center = { .x = column, .y = line };

            rectangle window_rect = rectangle_new(
                center.x - pattern_width / 2,
                center.y - pattern_height / 2,
                center.x + pattern_width / 2,
                center.y + pattern_height / 2);

            image window = image_window(src, window_rect);

            for (int i = 0; i < 10; ++i) {
                double corr = image_correlation(patterns[i], window);

                if (corr > threshold) {
                    detection det = {
                        .window = window_rect,
                        .corr = corr,
                        .digit = i
                    };

                    match_insert(m, det);
                }
            }

            image_free(&window);
        }
    }
}

int match_compare(const void* a, const void* b) {
    const detection* da = (const detection*)a;
    const detection* db = (const detection*)b;

    if (da->corr < db->corr) {
        return 1;
    } else if (da->corr > db->corr) {
        return -1;
    } else {
        return 0;
    }
}

void match_sort_det(matches* m) {
    qsort(m->dets, m->len, sizeof(detection), match_compare);
}

bool match_overlap(const detection* a, const detection* b) {
    double overlap = rectangle_overlap(a->window, b->window);

    return overlap > 0.2;
}

void match_remove_nonmax(matches* m) {
    for (int i = 0; i < m->len - 1; ++i) {
        const detection* current = m->dets + i;

        int j = i + 1;
        while (j < m->len) {
            // daca se suprapune spatial
            if (match_overlap(current, m->dets + j)) {
                // sterg din vector
                for (int k = j; k < m->len - 1; ++k) {
                    m->dets[k] = m->dets[k + 1];
                }

                --m->len;
            } else {
                ++j;
            }
        }
    }
}
