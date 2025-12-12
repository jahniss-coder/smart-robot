#include <stdio.h>
#include "creationGraphe.h"

int main() {
    unsigned int l;
    unsigned int tabPourGraphe[MAX_LIAISONS][2] = {0};
    unsigned int tabCaseObligatoires[MAX_CASES_OBLIGATOIRES] = {0};
    unsigned int nbLiaisons;
    unsigned int nbCasesObligatoires;
    unsigned int caseInitRobot;
    char orientationInitRobot;

    recuperationInfoFichier("ville.txt", &l, tabPourGraphe, tabCaseObligatoires, &nbLiaisons, &nbCasesObligatoires, &caseInitRobot, &orientationInitRobot);

    // Affichage des résultats pour vérification
    printf("Largeur de la ville : %u\n", l);
    printf("Position initiale du robot : Case %u, Orientation %c\n", caseInitRobot, orientationInitRobot);

    printf("Liaisons entre les cases :\n");
    for (unsigned int i = 0; i < nbLiaisons; i++) {
        printf("%u - %u\n", tabPourGraphe[i][0], tabPourGraphe[i][1]);
    }

    printf("Cases obligatoires :\n");
    for (unsigned int i = 0; i < nbCasesObligatoires; i++) {
        printf("%u\n", tabCaseObligatoires[i]);
    }

    return 0;
}
