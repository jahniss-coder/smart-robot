/**
 * @file chemin.h
 * @brief Fichier d'en-tête pour la gestion des chemins dans le graphe.
 * @author Delacroix-Henrion Mathieu, Diallo Alioune, Malherbe Ylann, Mathieu Ilan, Olivier Neil, Schetrit Jahnis
 * @date 2025-12
 */

#ifndef __TAD_CHEMIN__
#define __TAD_CHEMIN__

#define NB_POINTS_MAX 200 /**< Nombre maximum de points dans un chemin. */

/**
 * @brief Structure représentant un chemin dans le graphe.
 */
typedef struct {
    unsigned int points[NB_POINTS_MAX]; /**< Tableau des points du chemin. */
    unsigned int nb_points;             /**< Nombre de points dans le chemin. */
} Chemin;

/**
 * @brief Obtient le tableau des points d'un chemin.
 *
 * @param c Le chemin dont on veut obtenir les points.
 * @param tabPoints Tableau pour stocker les points du chemin.
 */
void obtenirChemin(Chemin c, unsigned int tabPoints[NB_POINTS_MAX]);

/**
 * @brief Obtient le nombre de points dans un chemin.
 *
 * @param c Le chemin dont on veut obtenir le nombre de points.
 * @return Le nombre de points dans le chemin.
 */
int obtenirNbPoints(Chemin c);

/**
 * @brief Fixe le nombre de points dans un chemin.
 *
 * @param c Pointeur vers le chemin à modifier.
 * @param nombre_point Le nombre de points à fixer.
 */
void fixerNbPoints(Chemin* c, unsigned int nombre_point);

#endif
