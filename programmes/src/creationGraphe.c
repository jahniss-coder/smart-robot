#include <stdio.h>
#include <stdlib.h>
#include "creationGraphe.h"

/*
    @brief L'objectif ici est de concevoir l'alogrithme permettant de créer le graphe à partir du fichier de description de la ville.
    @param  FILE fichierVille
    @return Graphe cricuit
*/

void recuperationInfoFichier(const char* fileNameVille, unsigned int* l, unsigned int tabPourGraphe[MAX_LIAISONS][2],
    unsigned int tabCaseObligatoires[MAX_CASES_OBLIGATOIRES], unsigned int* nbLiaisons, unsigned int* nbCasesObligatoires, 
    unsigned int* caseInitRobot, char* orientationInitRobot) {

    FILE *fichier = fopen(fileNameVille,"r"); // On lit juste ce fichier on n'écrit pas dedans.

    fscanf(fichier, "%u" , l);

    fscanf(fichier, "%u%c", caseInitRobot, orientationInitRobot);

    // Lecture des cases de liaisons nécessaires pour créer le graphe par la suite
    *nbLiaisons = 0;
    unsigned int case1, case2;
    char dash; 
    do {
        fscanf(fichier, "%u%c", &case1, &dash);
        if (dash == '-') {
            tabPourGraphe[*nbLiaisons][0] = case1;
            fscanf(fichier,"%u", &case2);
            tabPourGraphe[*nbLiaisons][1] = case2;
            (*nbLiaisons)++;
        }
        else {
            tabCaseObligatoires[0] = case1;
        }
    }while (dash == '-');

    // On lit les autres cases cases obligatoires si jamais il y en a et on les stocke
    char endChar;
    unsigned int caseObligatoire;
    *nbCasesObligatoires = 1; // On met à 1 car on a déjà mis la première case obligatoire dans le tableau avec le while d'avant
    do {
        endChar = fgetc(fichier);
        if (endChar != '.') {
            ungetc(endChar, fichier);
            fscanf(fichier, "%u", &caseObligatoire);
            tabCaseObligatoires[*nbCasesObligatoires] = caseObligatoire;
            (*nbCasesObligatoires)++;
        }
        else {
            *nbCasesObligatoires = *nbCasesObligatoires - 1; // Parce que sinon la dernière valeur est dupliquée.
        }
    } while (endChar != '.');
}

G_Graphe creationGrapheVille(unsigned int tabLiaisonsVille[MAX_LIAISONS][2], unsigned int nbLiaisons) {
    // Graphe non orienté, non étiqueté, non valué
    G_Graphe g = G_graphe(false, NULL, NULL, NULL, NULL, NULL, NULL);
    
    for (unsigned int i = 0; i < nbLiaisons; i++) {
        unsigned int sommet1 = tabLiaisonsVille[i][0];
        unsigned int sommet2 = tabLiaisonsVille[i][1];
        
        // Ajouter sommet1 s'il n'est pas déjà présent
        if (!G_sommetPresent(g, sommet1)) {
            if (G_ajouterSommet(&g, sommet1, NULL) == -1) {
                printf("Erreur lors de l'ajout du sommet %u (errno=%d)\n", sommet1, errno);
            }
        }
        
        // Ajouter sommet2 s'il n'est pas déjà présent
        if (!G_sommetPresent(g, sommet2)) {
            if (G_ajouterSommet(&g, sommet2, NULL) == -1) {
                printf("Erreur lors de l'ajout du sommet %u (errno=%d)\n", sommet2, errno);
            }
        }
        
        // Ajouter l'arc SANS valeur (NULL car graphe non valué)
        if (G_ajouterArc(&g, sommet1, sommet2, NULL) == -1) {
            printf("Erreur lors de l'ajout de l'arc %u -> %u (errno=%d)\n", 
                   sommet1, sommet2, errno);
        }
    }
    
    return g;
}


/*
int main() {
    unsigned int l;
    unsigned int tabPourGraphe[MAX_LIAISONS][2] = {0};
    unsigned int tabCaseObligatoires[MAX_CASES_OBLIGATOIRES] = {0};
    unsigned int nbLiaisons;
    unsigned int nbCasesObligatoires;
    unsigned int caseInitRobot;
    char orientationInitRobot;

    recuperationInfoFichier("ville.txt", &l, tabPourGraphe, tabCaseObligatoires, &nbLiaisons, &nbCasesObligatoires ,&caseInitRobot, &orientationInitRobot);

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
*/