/**
 * @file main.c
 * @brief Programme principal pour la résolution du plus court chemin dans un labyrinthe
 * @author Delacroix-Henrion Mathieu, Diallo Alioune, Malherbe Ylann, Mathieu Ilan, Olivier Neil, Schetrit Jahnis
 * @date 2025-12
 */

#include <stdio.h>
#include <stdlib.h>
#include "creationFichierOrdres.h"
#include "graphe_dijkstra.h"

#define BIN_DIR "bin/" /**< @brief Répertoire de sortie pour les exécutables */

/**
 * @brief Fonction principale du programme
 * @param argc Nombre d'arguments en ligne de commande
 * @param argv Tableau des arguments en ligne de commande
 * @return 0 en cas de succès, 1 en cas d'erreur
 */
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

    Solution plusCourtChemin = resoudre_chemin_plus_court(&g, tabCaseObligatoires, caseInitRobot, largeurVille, directionInitRobot);

    creationFichierOrdres(g, plusCourtChemin.chemin_complet, largeurVille, directionInitRobot);

    return 0;
}
