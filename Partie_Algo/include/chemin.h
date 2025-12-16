#ifndef __TAD_CHEMIN__
#define __TAD_CHEMIN__

#define NB_POINTS_MAX 200 

typedef struct{
    unsigned int points[NB_POINTS_MAX];  
    unsigned int nb_points;  
} Chemin;

/**
 * \brief Obtient le tableau des points d'un chemin
 * \param c Le chemin dont on veut obtenir les points
 * \param tabPoints Tableau pour stocker les points du chemin
 */
void obtenirChemin(Chemin c, unsigned int tabPoints[NB_POINTS_MAX]);

/**
 * \brief Obtient le nombre de points dans un chemin
 * \param c Le chemin dont on veut obtenir le nombre de points
 * \return Le nombre de points dans le chemin
 */
int obtenirNbPoints(Chemin c);

/**
 * \brief Fixe le nombre de points dans un chemin
 * \param c Pointeur vers le chemin à modifier
 * \param nombre_point Le nombre de points à fixer
 */
void fixerNbPoints(Chemin* c, unsigned int nombre_point);

#endif