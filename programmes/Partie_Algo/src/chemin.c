/**
 * @file chemin.c
 * @brief Implémentation des fonctions pour la gestion des chemins dans le graphe
 * @author Delacroix-Henrion Mathieu, Diallo Alioune, Malherbe Ylann, Mathieu Ilan, Olivier Neil, Schetrit Jahnis
 * @date 2025-12
 */

#include "chemin.h"
#include <stdio.h>
#include <string.h>

/**
 * @brief Obtient le tableau des points d'un chemin
 * @param c Le chemin dont on veut obtenir les points
 * @param tabPoints Tableau pour stocker les points du chemin
 */
void obtenirChemin(Chemin c, unsigned int tabPoints[NB_POINTS_MAX]) {
    for (unsigned int i = 0; i < c.nb_points; i++) {
        tabPoints[i] = c.points[i];
    }
}

/**
 * @brief Obtient le nombre de points dans un chemin
 * @param c Le chemin dont on veut obtenir le nombre de points
 * @return Le nombre de points dans le chemin
 */
int obtenirNbPoints(Chemin c) {
    return c.nb_points;
}

/**
 * @brief Fixe le nombre de points dans un chemin
 * @param c Pointeur vers le chemin à modifier
 * @param nombre_point Le nombre de points à fixer
 */
void fixerNbPoints(Chemin* c, unsigned int nombre_point) {
    c->nb_points = nombre_point;
}
