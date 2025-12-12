#ifndef __CREATION_GRAPHE__
#define __CREATION_GRAPHE__
#include "graphe.h"
#include "TAD_robot.h"

#define MAX_CHAINE 3
#define NB_POINTS_MAX 200
#define MAX_CASES_OBLIGATOIRES 3

void recuperationInfoFichier(const char* fileNameVille, unsigned int* l, unsigned int tabPourGraphe[NB_POINTS_MAX][2],
    unsigned int tabCaseObligatoires[MAX_CASES_OBLIGATOIRES], unsigned int* nbLiaisons, unsigned int* nbCasesObligatoires, 
    unsigned int* caseInitRobot, tDirection* orientationInitRobot);

G_Graphe creationGrapheVille(unsigned int tabLiaisonsVille[NB_POINTS_MAX][2], unsigned int nbLiaisons);

#endif