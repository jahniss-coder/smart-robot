#include <stdio.h>
#include "TAD_robot.h"
#include "dijkstra.h"

#define MAX_ORDRES 4 // Il ne peut pas y avoir plus de 4 ordres sachant que les demi tour ne sont pas pris en compte car ils feraient perdre trop de temps au directionRobot
#define MAX_CASES 50 // constante pour le plus court chemin.

typedef enum { AV , TG , TD, NO } Ordre; // NAO correspond à aucun ordre (NO ORDER car NULL est un mot clé) 

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
        default : return OUEST; // pour éviter un warning
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
        default : return EST; // pour éviter un warning
    }
}

Ordre ordreDuChangementDeDirection(tDirection direction, tDirection nlleDirection){
    if (direction == nlleDirection)
        return NO;
    else {
        if (direction == directionOuest(nlleDirection))
            return TG;
        else{ 
            if (direction == directionEst(nlleDirection))
                return TD; 
            }
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
        nlleDirection = NORD;
    }
    else if (diff == -largeurCircuit) {
        nlleDirection = SUD;
    }
    else {
    }


    *ordre1 = ordreDuChangementDeDirection(dirRobot, nlleDirection);
    setDirection(*robot, nlleDirection);
    *ordre2 = AV;
    setCaseRobot(*robot, caseSuivanteRobot);    
}


void determinerOrdres(char tabOrdres[MAX_ORDRES] , Chemin c , Robot robot , unsigned int largeurCircuit ) {

    Ordre ordre1, ordre2;
    unsigned int nbCaseChemin = c.nb_points;
    unsigned int *plusCourtChemin = c.points; 
    unsigned int i;
    unsigned int j = 0;

    for (i = 0; i < nbCaseChemin - 1; i++) {
        determinerOrdre(&robot, plusCourtChemin[i + 1], largeurCircuit, &ordre1, &ordre2);
        if (ordre1 == NO) 
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
    unsigned int nbOrdres = plusCourtChemin.nb_points - 1;
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nomFichierOrdres);
        return;
    }

    for (unsigned int i = 0; i < nbOrdres; i++) {
        switch (plusCourtChemin.points[i]) {
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


