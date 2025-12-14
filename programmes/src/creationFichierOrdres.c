#include <stdio.h>
#include "TAD_robot.h"
#include "dijkstra.h"
#include "creationFichierOrdres.h"
#include "graphe.h"
#include "ListeChaineeListe.h"
#include "chemin.h"

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

void determinerOrdres(Ordre tabOrdres[NB_POINTS_MAX], Chemin c, G_Graphe grapheVille , Robot robot, unsigned int largeurCircuit) {
    Ordre ordre1, ordre2;
    unsigned int plusCourtChemin[NB_POINTS_MAX];
    obtenirChemin(c, plusCourtChemin);
    unsigned int nbCaseChemin = obtenirNbPoints(c);
    unsigned int j = 0;

    for (unsigned int i = 0; i < nbCaseChemin - 1; i++) {
        LCL_Liste sommetsAdjacents = G_obtenirSommetsAdjacents(grapheVille, getCaseRobot(robot));
        determinerOrdre(&robot, plusCourtChemin[i + 1], largeurCircuit, &ordre1, &ordre2);
        printf("Robot case: %u -> %u\n", plusCourtChemin[i], plusCourtChemin[i + 1]);
        printf("ordre1: %d, ordre2: %d\n", ordre1, ordre2);
        if (ordre1 == NO) {
            if (j >= 1 && tabOrdres[j-1] == AV && LCL_longueur(sommetsAdjacents) > 2) {
                tabOrdres[j] = ordre2;
                j = j + 1;
                printf("Il y a une intersection au point %u, on avance\n", getCaseRobot(robot));
            }
            else if (j == 0) {
                tabOrdres[j] = ordre2;
                j = j + 1;
                printf("Premier ordre il faut avancer\n");
            }
            else {
                printf("Pas d'intersection on ne met pas d'ordre pour avancer\n");
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
    for (unsigned int k = j + 1; k < nbCaseChemin; k++) {
        printf("tabOrdres[%u] = %d\n", k, tabOrdres[k]);
    }
}

void creationFichierOrdres(const char* nomFichierOrdres, G_Graphe grapheVille , Chemin plusCourtChemin, unsigned int largeurCircuit , tDirection directionInitRobot) {
    FILE* fichier = fopen(nomFichierOrdres, "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nomFichierOrdres);
        return;
    }

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
            fprintf(fichier, "AV\n");
            printf("Ecriture ordre AV\n");
        }
        else if (tabOrdres[i] == TG) {
            fprintf(fichier, "TG\n");
            printf("Ecriture ordre TG\n");
        }
        else if (tabOrdres[i] == TD) {
            fprintf(fichier, "TD\n");
            printf("Ecriture ordre TD\n");
        }
        i++;
    }
    fputc('.', fichier); // Marqueur de fin des ordres
    fclose(fichier);
}


