#ifndef DIJKSTRA_H
#define DIJKSTRA_H

//#include // inclure le graphe.h

#define NB_POINTS_MAX 200 // Pour être sûr que jamais on ait autant de points

// On va stocker le chemin que l'on veut que notre robot suive
typedef struct{
    int points[NB_POINTS_MAX];  // Tableau ou on va stocker nos points par lesquels le robot doit passer
    int nb_points;  // Nombre de points que l'on a dans notre tableau de points
    //int nb_pas; // Correspond a la longueur -1 (aussi nombre d'arrêtes)
} Chemin;

// Structure pour donner toutes les informations
typedef struct{
    int point_actuel;   // Le point sur lequel on se trouve
    int point_precedent;    // Le point depuis lequel on arrive
    int chemin[NB_POINTS_MAX];      // Tous les points par lesquels il faut passer pour arriver jusqu'au point actuel
    int nb_points;    // Le nombre de points dans le chemin
} EtatDuDijkstra;

typedef struct{
    int ordre[3];   // Ordre dans lequel on va aller aux 3 points
    /** 
    6 possibiltés
    P1 -> P2 -> P3
    P1 -> P3 -> P2
    P2 -> P1 -> P3
    P2 -> P3 -> P1
    P3 -> P1 -> P2
    P3 -> P2 -> P1
    **/
    int chemin_complet[NB_POINTS_MAX];  // Tableau avec tous les points par lesquels on doit passer
    int longueur_chemin_complet;
}Solution;

/**
   @brief Trouver le chemin pour aller aux points obligatoires
   @return ???
**/
Chemin dijkstra(Graphe* g, int depart, int arrivee);









#endif