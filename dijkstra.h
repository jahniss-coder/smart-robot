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
   @param g: Graphe des liaisons entre les points
   @param depart: Point de départ sur lequel on se trouve
   @param arrivee: Point ou l'on souhaite arriver
   @return un chemin, le chemin le plus court
**/
Chemin dijkstra(Graphe* g, int depart, int arrivee);


/**
   @brief Trouver le chemin pour aller aux points obligatoires
   @param g Graphe des liaisons entre les points
   @param point_obligatoires tableau contenant les points de passage obligatoires dans la ville
   @param depart point de départ du robot
   @param longueur_ville longueur de la ville
   @return la solution du chemin le plus court
**/
Solution resoudre_chemin_plus_court(Graphe* g, int point_obligatoires[3], int depart, int longueur_ville);

/**
   @brief pouvoir permuter l'ordre dans lequel on passe aux points
   @param arr: tableau 1D ou l'on va stocker les 3 points ou l'on se trouve
   @param permutations: tableau 2D pour stocker les 6 possibilités
**/
void permutation(int arr[3], int permutations[6][3]);






#endif