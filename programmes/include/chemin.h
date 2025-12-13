#ifndef __TAD_CHEMIN__
#define __TAD_CHEMIN__

#define NB_POINTS_MAX 200 

typedef struct{
    unsigned int points[NB_POINTS_MAX];  
    unsigned int nb_points;  
} Chemin;

/**
    @param 

*/
void obtenirChemin(Chemin c, (unsigned int)* tabPoints[NB_POINTS_MAX]);

int obtenirNbPoints(Chemin c);

void fixerNbPoints(Chemin* c);

#endif