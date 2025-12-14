#include <stdio.h>
#include <stdlib.h>
#include "creationFichierOrdres.h"
#include "graphe_dijkstra.h"

#define BIN_DIR "bin/"

int main(int argc, char ** argv) {
    if (argc < 2) {
        printf("Utilisation: %s <fichier_entre_labyrinthe>\n", argv[0]);
        return 1;
    }

    const char* nomFichierVille = argv[1];
    unsigned int largeurVille;
    unsigned int tabPourGraphe[NB_POINTS_MAX][2] = {0};
    unsigned int tabCaseObligatoires[MAX_CASES_OBLIGATOIRES] = {0};
    unsigned int nbLiaisons;
    unsigned int nbCasesObligatoires;
    unsigned int caseInitRobot;
    tDirection directionInitRobot;

    recuperationInfoFichier(nomFichierVille, &largeurVille, tabPourGraphe, tabCaseObligatoires, &nbLiaisons, &nbCasesObligatoires, &caseInitRobot, &directionInitRobot);

    G_Graphe g = creationGrapheVille(tabPourGraphe, nbLiaisons);

    Solution plusCourtChemin = resoudre_chemin_plus_court(&g, tabCaseObligatoires, caseInitRobot, largeurVille);

    // Construction du chemin complet pour le fichier de sortie
    char fichierSortie[256];
    snprintf(fichierSortie, sizeof(fichierSortie), "%s%s", BIN_DIR, "fichierInstructions.txt");

    creationFichierOrdres(fichierSortie, g, plusCourtChemin.chemin_complet, largeurVille, directionInitRobot);

    return 0;
}
