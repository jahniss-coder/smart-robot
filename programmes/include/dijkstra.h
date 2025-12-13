#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graphe.h"

//#include // inclure le graphe.h

#define NB_POINTS_MAX 200 // Pour être sûr que jamais on ait autant de points

// On va stocker le chemin que l'on veut que notre robot suive
typedef struct{
    unsigned int points[NB_POINTS_MAX];  // Tableau ou on va stocker nos points par lesquels le robot doit passer
    unsigned int nb_points;  // Nombre de points que l'on a dans notre tableau de points
    //int nb_pas; // Correspond a la longueur -1 (aussi nombre d'arrêtes)
} Chemin;

// Structure pour donner toutes les informations
typedef struct{
    unsigned int point_actuel;   // Le point sur lequel on se trouve
    unsigned int point_precedent;    // Le point depuis lequel on arrive
    Chemin chemin; // Tous les points par lesquels il faut passer pour arriver jusqu'au point actuel
} EtatDuDijkstra;

typedef struct{
    unsigned int ordre[3];   // Ordre dans lequel on va aller aux 3 points
    /** 
    6 possibiltés
    P1 -> P2 -> P3
    P1 -> P3 -> P2
    P2 -> P1 -> P3
    P2 -> P3 -> P1
    P3 -> P1 -> P2
    P3 -> P2 -> P1
    **/
    Chemin chemin_complet;  // Tableau avec tous les points par lesquels on doit passer
}Solution;

/**
 * \brief Algorithme de Dijkstra modifié pour éviter certains points
 * \param g Pointeur vers le graphe
 * \param depart Indice du sommet de départ
 * \param arrivee Indice du sommet d'arrivée
 * \param sommets_a_eviter Tableau des indices des sommets à éviter
 * \param nb_a_eviter Nombre de sommets à éviter
 * \return Le chemin le plus court entre le sommet de départ et le sommet d'arrivée en évitant les sommets spécifiés
 */
Chemin dijkstra_avec_exclusions(G_Graphe* g, unsigned int depart, unsigned int arrivee, 
                                 unsigned int sommets_a_eviter[], unsigned int nb_a_eviter);

/**
 * \brief Algorithme de Dijkstra pour trouver le chemin le plus court entre deux sommets
 * \param g Pointeur vers le graphe
 * \param depart Indice du sommet de départ
 * \param arrivee Indice du sommet d'arrivée
 * \return Le chemin le plus court entre le sommet de départ et le sommet d'arrivée
 */
Chemin dijkstra(G_Graphe* g, unsigned int depart, unsigned int arrivee);

/**
 * \brief Résout le problème du chemin le plus court en passant par des points obligatoires
 * \param g Pointeur vers le graphe
 * \param point_obligatoires Tableau des indices des points obligatoires à visiter
 * \param depart Indice du sommet de départ
 * \param longueur_ville Longueur (largeur) de la ville (utilisée pour les calculs)
 * \return La solution contenant l'ordre des points visités et le chemin complet
 */
Solution resoudre_chemin_plus_court(G_Graphe* g, unsigned int point_obligatoires[3], 
                                     unsigned int depart, unsigned int longueur_ville); 

/**
 * \brief Génère toutes les permutations des indices donnés
 * \param indices Tableau des indices à permuter
 * \param permutations Tableau pour stocker les permutations générées
 */
void permutation(unsigned int indices[3], unsigned int permutations[6][3]);                                     

/**
 * \brief Vérifie si un chemin est autorisé (ne passe pas par des sommets interdits)
 * \param c Le chemin à vérifier
 * \return 1 si le chemin est autorisé, 0 sinon
 */
int chemin_autorise(Chemin c);

/**
 * \brief Vérifie la jonction entre deux segments de chemin pour éviter les demi-tours
 * \param segment1 Le premier segment de chemin
 * \param segment2 Le deuxième segment de chemin
 * \return 1 si la jonction est valide, 0 sinon
 */
int verifier_jonction_segments(Chemin segment1, Chemin segment2);

#endif