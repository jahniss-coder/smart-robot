#include <stdio.h>
#include "creationGraphe.h"

int main() {
    int l;
    int tabPourGraphe[MAX_LIAISONS][2] = {0};
    int tabCaseObligatoires[MAX_CASES_OBLIGATOIRES] = {0};
    int nbLiaisons;
    int nbCasesObligatoires;
    int caseInitRobot;
    char orientationInitRobot;

    recuperationInfoFichier("ville.txt", &l, tabPourGraphe, tabCaseObligatoires, &nbLiaisons, &nbCasesObligatoires, &caseInitRobot, &orientationInitRobot);

    // Affichage des résultats pour vérification
    printf("Largeur de la ville : %u\n", l);
    printf("Position initiale du robot : Case %u, Orientation %c\n", caseInitRobot, orientationInitRobot);

    printf("Liaisons entre les cases :\n");
    for (int i = 0; i < nbLiaisons; i++) {
        printf("%u - %u\n", tabPourGraphe[i][0], tabPourGraphe[i][1]);
    }

    printf("Cases obligatoires :\n");
    for (int i = 0; i < nbCasesObligatoires; i++) {
        printf("%u\n", tabCaseObligatoires[i]);
    }

    return 0;
}
