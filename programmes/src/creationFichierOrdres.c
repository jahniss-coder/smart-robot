#include <stdio.h>
#include "TAD_robot.h"
#include "dijkstra.h"

#define MAX_ORDRES 4 // Il ne peut pas y avoir plus de 4 ordres sachant que les demi tour ne sont pas pris en compte car ils feraient perdre trop de temps au directionRobot
#define MAX_CASES 50 // constante pour le plus court chemin.

typedef enum { AV , TG , TD, NULL } Ordre; // NULL correspond à aucun ordre

tDirection directionOuest(tDirection direction) {
    switch (direction)
    {
        case OUEST : 
            return SUD;
        case SUD :
            return EST;
        case EST :
            return NORD;
        case NORD : 
            return OUEST;
    }        
}

tDirection directionEst(tDirection direction){
    switch (direction)
    {
        case OUEST : 
            return NORD;
        case SUD :
            return OUEST;
        case EST :
            return SUD;
        case NORD : 
            return EST;
    }
}

Ordre ordreDuChangementDeDirection(tDirection direction, tDirection nlleDirection){
    if (direction == nlleDirection)
        return NULL;
    else {
        if (direction == directionOuest(nlleDirection))
            return TG;
        else{ 
            if (direction == directionEst(nlleDirection))
                return TD; 
            }
    }
}

void determinerOrdre(Robot* robot, unsigned int caseSuivanteRobot, unsigned int largeurCircuit, Ordre* ordre1, Ordre* ordre2) {
    unsigned int caseInitRobot = getCaseRobot(*robot);
    tDirection dirRobot = getDirection(*robot);
    unsigned int diff = caseSuivanteRobot - caseInitRobot;
    tDirection nlleDirection;

    switch (diff)
    {
    case 1 :{
        nlleDirection = EST;
        break;
    }
    case -1 : {
        nlleDirection = OUEST;
        break;
    }
    case largeurCircuit : {
        nlleDirection = NORD;
        break;
    }
    case -largeurCircuit : {
        nlleDirection = SUD;
        break;
    }
    default:
        break;
    }

    ordre1 = ordreDuChangementDeDirection(dirRobot, nlleDirection);
    setDirection(*robot, nlleDirection);
    ordre2 = AV;
    setCaseRobot(*robot, caseSuivanteRobot);    
}


void determinerOrdres(char tabOrdres[MAX_ORDRES] , Chemin c , Robot robot , unsigned int largeurCircuit ) {

    Ordre ordre1, ordre2;
    unsigned int nbCaseChemin = c.nb_points;
    unsigned int plusCourtChemin[MAX_CASES] = c.points; 
    unsigned int i;
    unsigned int j = 0;

    for (i = 0, i < nbCaseChemin - 1, i++) {
        determinerOrdre(&robot, plusCourtChemin[i + 1], largeurCircuit, &ordre1, &ordre2);
        if (ordre1 == NUL) 
            tabOrdres[j] = ordre2;
        else {
            tabOrdres[j] = ordre1;
            tabOrdres[j + 1] = ordre2;
            j++;
        }
        j++;
        
    }
}

void creationFichierOrdres(const char* nomFichierOrdres, Chemin plusCourtChemin){
    FILE* fichier = fopen(nomFichierOrdres, "w"); // Le fichier doit déjà exister pour être ouvert en écriture.
    nbOrdres = plusCourtChemin.nb_points - 1;
    unsigned int tabOrdres[MAX_ORDRES] = plusCourtChemin.points;
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nomFichierOrdres);
        return;
    }

    for (unsigned int i = 0; i < nbOrdres; i++) {
        switch (tabOrdres[i]) {
            case AV:
                fprintf(fichier, "AV\n");
                break;
            case TG:
                fprintf(fichier, "TG\n");
                break;
            case TD:
                fprintf(fichier, "TD\n");
                break;
            default:
                break;
        }
    }
    fprintf(fichier, "."); // Marqueur de fin des ordres
    fclose(fichier);
}


