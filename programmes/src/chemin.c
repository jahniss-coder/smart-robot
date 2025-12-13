#include "chemin.h"
#include <stdio.h>
#include <string.h>

void obtenirChemin(Chemin c, unsigned int tabPoints[NB_POINTS_MAX]) {
    for (unsigned int i = 0; i < c.nb_points; i++) {
        tabPoints[i] = c.points[i];
    }
}

int obtenirNbPoints(Chemin c) {
    return c.nb_points;
}

void fixerNbPoints(Chemin* c, unsigned int nombre_point) {
    c->nb_points = nombre_point;
}
