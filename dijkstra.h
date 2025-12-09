#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include // inclure le graphe.h

#define NB_POINTS_MAX 200 // Pour être sûr que jamais on ait autant de points

// On va stocker le chemin que l'on veut que notre robot suive
typedef struct{
    int points[NB_POINTS_MAX];  // Tableau ou on va stocker nos points par lesquels le robot doit passer
    int nb_points;  // Nombre de points que l'on a dans notre tableau de points
    // pas besoin d'ajouter de distance normalement car les distances entre les points sont équivalents
} Chemin;

// Structure pour donner toutes les informations
typedef struct{
    int point_actuel;
    int point_precedent;
    int chemin[NB_POINTS_MAX];  
    int longueur_chemin;    
} pointDijkstra;

/**
   @brief Trouver le chemin pour aller aux points obligatoires
   @return ???
**/
Chemin dijkstra(Graphe* g, int depart, int arrivee);

