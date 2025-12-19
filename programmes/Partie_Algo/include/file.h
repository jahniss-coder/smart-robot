/**
 * @file file.h
 * @brief Fichier d'en-tête pour la gestion des files utilisées dans l'algorithme de Dijkstra.
 * @author Delacroix-Henrion Mathieu, Diallo Alioune, Malherbe Ylann, Mathieu Ilan, Olivier Neil, Schetrit Jahnis
 * @date 2025-12
 */

#ifndef FILE_H
#define FILE_H

#include "graphe_dijkstra.h"

#define MAX_FILE 500 /**< Taille maximale de la file. */

/**
 * @brief Structure représentant une file utilisée dans l'algorithme de Dijkstra.
 */
typedef struct {
    EtatDuDijkstra elements[MAX_FILE]; /**< Tableau qui stocke les états. */
    int debut; /**< Indice du premier élément de la file. */
    int fin;   /**< Indice après le dernier élément de la file. */
} File;

/**
 * @brief Initialise une file.
 *
 * @param f Pointeur vers la file à initialiser.
 */
void initialisation_file(File* f);

/**
 * @brief Vérifie si une file est vide.
 *
 * @param f Pointeur vers la file.
 * @return 1 si la file est vide, 0 sinon.
 */
int estVideFile(File* f);

/**
 * @brief Vérifie si une file est pleine.
 *
 * @param f Pointeur vers la file.
 * @return 1 si la file est pleine, 0 sinon.
 */
int estPleineFile(File* f);

/**
 * @brief Enfile un état du Dijkstra dans la file.
 *
 * @param f Pointeur vers la file.
 * @param pD État du Dijkstra à enfiler.
 */
void enfiler(File* f, EtatDuDijkstra pD);

/**
 * @brief Libère la mémoire allouée pour la file.
 *
 * @param f Pointeur vers la file.
 */
void liberer_file(File* f);

/**
 * @brief Défiler l'élément en tête de file.
 *
 * @param f Pointeur vers la file.
 * @return L'état du Dijkstra défilé.
 */
EtatDuDijkstra defiler(File* f);

#endif
