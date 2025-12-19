/**
 * @file creationFichierOrdres.h
 * @brief Fichier d'en-tête pour la création des ordres de déplacement du robot.
 * @author Delacroix-Henrion Mathieu, Diallo Alioune, Malherbe Ylann, Mathieu Ilan, Olivier Neil, Schetrit Jahnis
 * @date 2025-12
 */

#ifndef CREATION_FICHIER_ORDRES
#define CREATION_FICHIER_ORDRES
#include <stdio.h>
#include "TAD_robot.h"
#include "graphe_dijkstra.h"
#include "chemin.h"

#define MAX_ORDRES 4 /**< Nombre maximum d'ordres possibles. */
#define MAX_CASES 50  /**< Nombre maximum de cases dans un chemin. */

/**
 * @brief Énumération des ordres possibles pour le robot.
 */
typedef enum { AV, TG, TD, NO } Ordre; /**< AV: Avancer, TG: Tourner à gauche, TD: Tourner à droite, NO: Aucun ordre. */

/**
 * @brief Détermine la direction à l'ouest par rapport à la direction actuelle.
 *
 * @param direction La direction actuelle.
 * @return La direction à l'ouest.
 */
tDirection directionOuest(tDirection direction);

/**
 * @brief Détermine la direction à l'est par rapport à la direction actuelle.
 *
 * @param direction La direction actuelle.
 * @return La direction à l'est.
 */
tDirection directionEst(tDirection direction);

/**
 * @brief Détermine l'ordre nécessaire pour changer la direction du robot.
 *
 * @param direction La direction actuelle du robot.
 * @param nlleDirection La nouvelle direction souhaitée pour le robot.
 * @return L'ordre nécessaire pour effectuer le changement de direction (TG, TD ou NO si pas de changement).
 */
Ordre ordreDuChangementDeDirection(tDirection direction, tDirection nlleDirection);

/**
 * @brief Détermine les ordres nécessaires pour que le robot se déplace vers la case suivante.
 *
 * @param robot Pointeur vers le robot.
 * @param caseSuivanteRobot La case vers laquelle le robot doit se déplacer.
 * @param largeurCircuit La largeur du circuit (utilisée pour le calcul des déplacements).
 * @param ordre1 Pointeur vers la première ordre à générer (changement de direction si nécessaire).
 * @param ordre2 Pointeur vers la deuxième ordre à générer (avancer).
 */
void determinerOrdre(Robot* robot, unsigned int caseSuivanteRobot, unsigned int largeurCircuit, Ordre* ordre1, Ordre* ordre2);

/**
 * @brief Détermine la séquence d'ordres pour que le robot suive un chemin donné.
 *
 * @param tabOrdres Tableau pour stocker les ordres générés.
 * @param c Le chemin que le robot doit suivre.
 * @param grapheVille Le graphe représentant la ville.
 * @param robot Le robot.
 * @param largeurCircuit La largeur du circuit.
 */
void determinerOrdres(Ordre tabOrdres[NB_POINTS_MAX], Chemin c, G_Graphe grapheVille, Robot robot, unsigned int largeurCircuit);

/**
 * @brief Affiche sur la sortie standard les ordres pour que le robot suive un chemin donné.
 *
 * @param grapheVille Le graphe représentant la ville.
 * @param plusCourtChemin Le chemin que le robot doit suivre.
 * @param largeurCircuit La largeur du circuit.
 * @param directionInitRobot La direction initiale du robot.
 */
void creationFichierOrdres(G_Graphe grapheVille, Chemin plusCourtChemin, unsigned int largeurCircuit, tDirection directionInitRobot);

#endif
