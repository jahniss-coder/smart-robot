#include <stdio.h>
#include "creationGraphe.h"
#include "dijkstra.h"
#include "creationFichierOrdres.h"

const char* fileName = "fichierInstructions.txt";


int main(int argc, char ** argv) {

       if (argc < 2) {
        printf("Utilisation: %s <fichier_entre_labyrinthe> <fichier_sortie_labyrinthe>\n", argv[0]);
        return 1;
    }

    const char* nomFichierVille = argv[1];
    unsigned int largeurVille;
    unsigned int tabPourGraphe[MAX_LIAISONS][2] = {0};
    unsigned int tabCaseObligatoires[MAX_CASES_OBLIGATOIRES] = {0};
    unsigned int nbLiaisons;
    unsigned int nbCasesObligatoires;
    unsigned int caseInitRobot;
    char directionInitRobot;

    recuperationInfoFichier(nomFichierVille, &largeurVille, tabPourGraphe, tabCaseObligatoires, &nbLiaisons, &nbCasesObligatoires, &caseInitRobot, &directionInitRobot);

    G_Graphe g = creationGrapheVille(tabPourGraphe, nbLiaisons);

    Solution plusCourtChemin = resoudre_chemin_plus_court(&g, tabCaseObligatoires, caseInitRobot, largeurVille);

    creationFichierOrdres(fileName, g, plusCourtChemin.chemin, largeurVille, directionInitRobot);

    return 0;
}
