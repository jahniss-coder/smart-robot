#ifndef CREATION_FICHIER_ORDRES
#define CREATION_FICHIER_ORDRES
#include <stdio.h>
#include "TAD_robot.h"
#include "graphe_dijkstra.h"
#include "chemin.h"

#define MAX_ORDRES 4 // Il ne peut pas y avoir plus de 4 ordres sachant que les demi tour ne sont pas pris en compte car ils feraient perdre trop de temps au directionRobot
#define MAX_CASES 50 // constante pour le plus court chemin.

typedef enum { AV , TG , TD, NO } Ordre; // NULL correspond à aucun ordre

tDirection directionOuest(tDirection direction);

tDirection directionEst(tDirection direction);

/**
 * \brief Détermine l'ordre nécessaire pour changer la direction du robot (TG, TD ou NULL si pas de changement)
 * \param direction La direction actuelle du robot
 * \param nlleDirection La nouvelle direction souhaitée pour le robot
 * \return L'ordre nécessaire pour effectuer le changement de direction (TG, TD ou NULL si pas de changement)
 */
Ordre ordreDuChangementDeDirection(tDirection direction, tDirection nlleDirection);

/**
 * \brief Détermine les ordres nécessaires pour que le robot se déplace vers la case suivante
 * \param robot Pointeur vers le robot
 * \param caseSuivanteRobot La case vers laquelle le robot doit se déplacer
 * \param largeurCircuit La largeur du circuit (utilisée pour le calcul des déplacements)
 * \param ordre1 Pointeur vers la première ordre à générer (changement de direction si nécessaire)
 * \param ordre2 Pointeur vers la deuxième ordre à générer (avancer)
 */
void determinerOrdre(Robot* robot, unsigned int caseSuivanteRobot, unsigned int largeurCircuit, Ordre* ordre1, Ordre* ordre2);

/**
 * \brief Détermine la séquence d'ordres pour que le robot suive un chemin donné
 * \param tabOrdres Tableau pour stocker les ordres générés
 * \param c Le chemin que le robot doit suivre
 * \param grapheVille Le graphe représentant la ville
 * \param robot Le robot
 * \param largeurCircuit La largeur du circuit
 */
void determinerOrdres(Ordre tabOrdres[NB_POINTS_MAX], Chemin c, G_Graphe grapheVille , Robot robot, unsigned int largeurCircuit);


/**
 * \brief Crée un fichier contenant les ordres pour que le robot suive un chemin donné
 * \param nomFichierOrdres Le nom du fichier dans lequel écrire les ordres
 * \param plusCourtChemin Le chemin que le robot doit suivre
 * \param largeurCircuit La largeur du circuit
 * \param directionInitRobot La direction initiale du robot
 */
void creationFichierOrdres(const char* nomFichierOrdres, G_Graphe grapheVille , Chemin plusCourtChemin, unsigned int largeurCircuit , tDirection directionInitRobot);

#endif