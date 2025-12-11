#ifndef __CREATION_GRAPHE__
#define __CREATION_GRAPHE__
#include "graphe.h"

#define MAX_CHAINE 3
#define MAX_LIAISONS 100
#define MAX_CASES_OBLIGATOIRES 3

void recuperationInfoFichier(const char* fileNameVille, unsigned int* l, unsigned int tabPourGraphe[MAX_LIAISONS][2],
    unsigned int tabCaseObligatoires[MAX_CASES_OBLIGATOIRES], unsigned int* nbLiaisons, unsigned int* nbCasesObligatoires, 
    unsigned int* caseInitRobot, char* orientationInitRobot);

G_Graphe creationGrapheVille(unsigned int tabLiaisonsVille[MAX_LIAISONS][2], unsigned int nbLiaisons);

#endif