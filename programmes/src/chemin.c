#include "chemin.h"

void obtenirChemin(Chemin c, (unsigned int) tabPoints[NB_POINTS_MAX]){
    return c.points;
}

int obtenirNbPoints(Chemin c){
    return c.nb_points;
}

void fixerNbPoints(Chemin* c, unsigned int nombre_point){
    c->nb_points = nombre_point;
}
