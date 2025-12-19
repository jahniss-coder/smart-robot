/**
 * @file creationFichierOrdres.c
 * @brief Implémentation des fonctions pour la création des ordres de déplacement du robot
 * @author Delacroix-Henrion Mathieu, Diallo Alioune, Malherbe Ylann, Mathieu Ilan, Olivier Neil, Schetrit Jahnis
 * @date 2025-12
 */

#include <stdio.h>
#include "TAD_robot.h"
#include "graphe_dijkstra.h"
#include "creationFichierOrdres.h"
#include "graphe.h"
#include "ListeChaineeListe.h"
#include "chemin.h"


/**
 * @brief Détermine l'ordre nécessaire pour changer la direction du robot (TG, TD ou NULL si pas de changement)
 * @param direction La direction actuelle du robot
 * @param nlleDirection La nouvelle direction souhaitée pour le robot
 * @return L'ordre nécessaire pour effectuer le changement de direction (TG, TD ou NO si pas de changement)
 */
Ordre ordreDuChangementDeDirection(tDirection direction, tDirection nlleDirection){
    if (direction == nlleDirection) {
        return NO;
    }
    else if (direction == directionEst(nlleDirection)){
        return TG;
    }
    else if (direction == directionOuest(nlleDirection)) {
        return TD; 
    }
    return NO; // pour éviter un warning
}

/**
 * @brief Détermine les ordres nécessaires pour que le robot se déplace vers la case suivante
 * @param robot Pointeur vers le robot
 * @param caseSuivanteRobot La case vers laquelle le robot doit se déplacer
 * @param largeurCircuit La largeur du circuit (utilisée pour le calcul des déplacements)
 * @param ordre1 Pointeur vers la première ordre à générer (changement de direction si nécessaire)
 * @param ordre2 Pointeur vers la deuxième ordre à générer (avancer)
 */
void determinerOrdre(Robot* robot, unsigned int caseSuivanteRobot, unsigned int largeurCircuit, Ordre* ordre1, Ordre* ordre2) {
    unsigned int caseInitRobot = getCaseRobot(*robot);
    tDirection dirRobot = getDirection(*robot);
    unsigned int diff = caseSuivanteRobot - caseInitRobot;
    tDirection nlleDirection;

    if (diff == 1) {  // Le switch a été remplacer par des ifs car on ne peux mettre de valeurs inconnu a la compilations en label 
        nlleDirection = EST;
    }
    else if (diff == -1) {
        nlleDirection = OUEST;
    }
    else if (diff == largeurCircuit) {
        nlleDirection = SUD;
    }
    else if (diff == -largeurCircuit) {
        nlleDirection = NORD;
    }
    else {
        nlleDirection = dirRobot; // Pas de changement de direction
    }
    *ordre1 = ordreDuChangementDeDirection(dirRobot, nlleDirection);
    setDirection(robot, nlleDirection);
    *ordre2 = AV;
    setCaseRobot(robot, caseSuivanteRobot);    
}

/**
 * @brief Détermine la séquence d'ordres pour que le robot suive un chemin donné
 * @param tabOrdres Tableau pour stocker les ordres générés
 * @param c Le chemin que le robot doit suivre
 * @param grapheVille Le graphe représentant la ville
 * @param robot Le robot
 * @param largeurCircuit La largeur du circuit
 */
void determinerOrdres(Ordre tabOrdres[NB_POINTS_MAX], Chemin c, G_Graphe grapheVille , Robot robot, unsigned int largeurCircuit) {
    Ordre ordre1, ordre2;
    unsigned int plusCourtChemin[NB_POINTS_MAX];
    obtenirChemin(c, plusCourtChemin);
    unsigned int nbCaseChemin = obtenirNbPoints(c);
    unsigned int j = 0;

    for (unsigned int i = 0; i < nbCaseChemin - 1; i++) {
        LCL_Liste sommetsAdjacents = G_obtenirSommetsAdjacents(grapheVille, getCaseRobot(robot));
        determinerOrdre(&robot, plusCourtChemin[i + 1], largeurCircuit, &ordre1, &ordre2);
        if (ordre1 == NO) {
            if (j >= 1 && tabOrdres[j-1] == AV && LCL_longueur(sommetsAdjacents) > 2) {
                tabOrdres[j] = ordre2;
                j = j + 1;
            }
            else if (j == 0) {
                tabOrdres[j] = ordre2;
                j = j + 1;
            }
        }
        else {
            tabOrdres[j] = ordre1;
            j = j + 1;
            tabOrdres[j] = ordre2;
            j = j + 1;
        }
    }
    tabOrdres[j] = NO; // Marqueur de fin des ordres
}

/**
 * @brief affiche sur la sortie standard les ordres pour que le robot suive un chemin donné
 * @param plusCourtChemin Le chemin que le robot doit suivre
 * @param largeurCircuit La largeur du circuit
 * @param directionInitRobot La direction initiale du robot
 */
void creationFichierOrdres(G_Graphe grapheVille , Chemin plusCourtChemin, unsigned int largeurCircuit , tDirection directionInitRobot) {
    // Initialisation du robot
    Robot robot;
    setCaseRobot(&robot, plusCourtChemin.points[0]); // Position initiale du robot
    setDirection(&robot, directionInitRobot); // Direction initiale arbitraire

    // Tableau pour stocker les ordres
    Ordre tabOrdres[NB_POINTS_MAX]; // Initialisation avec AV parce que le robot doit toujours avancer au début
    determinerOrdres(tabOrdres, plusCourtChemin, grapheVille,robot, largeurCircuit);


    // Écriture des ordres dans le fichier
    unsigned int i = 0;
    while (tabOrdres[i] != NO && i < NB_POINTS_MAX) {
        if (tabOrdres[i] == AV) {
            fprintf(stdout, "AV\n");
        }
        else if (tabOrdres[i] == TG) {
            fprintf(stdout,"TG\n");
        }
        else if (tabOrdres[i] == TD) {
            fprintf(stdout, "TD\n");
        }
        i++;
    }
    fprintf(stdout, "."); // Marqueur de fin des ordres
}


