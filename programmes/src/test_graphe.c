#include <stdio.h>
#include <CUnit/Basic.h>
#include <string.h>
#include <stdbool.h>
#include "creationGraphe.h"
#include "creationFichierOrdres.h"

const char* fileName = "ville.txt";

int init_suite_success(void) {
    return 0;
}

int clean_suite_success(void) {
    return 0;
}

/*
    Tests de récupération des éléments du fichier de description de la ville
*/
void test_largeur_ville(void) {
    unsigned int l;
    unsigned int tabGraphe[MAX_LIAISONS][2];
    unsigned int tabCaseObligatoires[MAX_CASES_OBLIGATOIRES];
    unsigned int nbLiaisons;
    unsigned int nbCasesObligatoires;
    unsigned int caseInitRobot;
    char directionInitRobot;

    recuperationInfoFichier(fileName, &l, tabGraphe, tabCaseObligatoires, &nbLiaisons, &nbCasesObligatoires, &caseInitRobot, &directionInitRobot);
    CU_ASSERT_EQUAL(l, 5);
}

void test_caseInitialeRobot(void) {
    unsigned int l;
    unsigned int tabGraphe[MAX_LIAISONS][2];
    unsigned int tabCaseObligatoires[MAX_CASES_OBLIGATOIRES];
    unsigned int nbLiaisons;
    unsigned int nbCasesObligatoires;
    unsigned int caseInitRobot;
    char directionInitRobot;

    recuperationInfoFichier(fileName, &l, tabGraphe, tabCaseObligatoires, &nbLiaisons, &nbCasesObligatoires, &caseInitRobot, &directionInitRobot);
    CU_ASSERT_EQUAL(caseInitRobot, 6);
    CU_ASSERT_EQUAL(directionInitRobot, 'S');
}

void test_liaisons_points(void) {
    unsigned int l;
    unsigned int tabGraphe[MAX_LIAISONS][2];
    unsigned int tabCaseObligatoires[MAX_CASES_OBLIGATOIRES];
    unsigned int nbLiaisons;
    unsigned int nbCasesObligatoires;
    unsigned int caseInitRobot;
    char directionInitRobot;

    recuperationInfoFichier(fileName, &l, tabGraphe, tabCaseObligatoires, &nbLiaisons, &nbCasesObligatoires, &caseInitRobot, &directionInitRobot);
    CU_ASSERT_EQUAL(tabGraphe[0][1], 2);
    CU_ASSERT_EQUAL(tabGraphe[nbLiaisons-1][0], 23);
}

void test_points_obligatoires(void) {
    unsigned int l;
    unsigned int tabGraphe[MAX_LIAISONS][2];
    unsigned int tabCaseObligatoires[MAX_CASES_OBLIGATOIRES];
    unsigned int nbLiaisons;
    unsigned int nbCasesObligatoires;
    unsigned int caseInitRobot;
    char directionInitRobot;

    recuperationInfoFichier(fileName, &l, tabGraphe, tabCaseObligatoires, &nbLiaisons, &nbCasesObligatoires, &caseInitRobot, &directionInitRobot);
    CU_ASSERT_EQUAL(tabCaseObligatoires[0], 13);
    CU_ASSERT_EQUAL(tabCaseObligatoires[1], 22);
    CU_ASSERT_EQUAL(tabCaseObligatoires[2], 20);
}

/*
    Début des tests de création du graphe de la ville
*/
void test_creation_graphe_ville(void) {
    unsigned int tabLiaisonsVille[MAX_LIAISONS][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 4},
        {0, 5}, {5, 6}, {6, 7}, {7, 8},
        {1, 6}, {2, 7}, {3, 8}, {4, 9},
        {5, 10}, {10, 11}, {11, 12}, {12, 13},
        {6, 11}, {7, 12}, {8, 13}, {9, 14}
    };
    unsigned int nbLiaisons = 20;
    G_Graphe g = creationGrapheVille(tabLiaisonsVille, nbLiaisons);

    // Vérification du nombre de sommets
    LCL_Liste sommets = G_sommets(g);
    CU_ASSERT_EQUAL(LCL_longueur(sommets), 15); // Il devrait y avoir 15 sommets (0 à 14)

    // Vérification de la présence de certains arcs
    CU_ASSERT_TRUE(G_arcPresent(g, 0, 1));
    CU_ASSERT_TRUE(G_arcPresent(g, 5, 6));
    CU_ASSERT_TRUE(G_arcPresent(g, 10, 11));
    CU_ASSERT_FALSE(G_arcPresent(g, 0, 14)); // Cet arc ne devrait pas exister
}

/*
    Début des tests sur creation fichier ordres
*/
void test_determiner_ordres(void) {
    // Initialisation du robot
    Robot robot;
    setCaseRobot(robot, 6); // Position initiale du robot
    setDirection(robot, SUD); // Direction initiale du robot

    // Chemin à suivre
    Chemin c;
    c.points[0] = 6;
    c.points[1] = 11;
    c.points[2] = 12;
    c.points[3] = 13;
    c.nb_points = 4;

    // Tableau pour stocker les ordres
    char* tabOrdres[MAX_ORDRES] = {0};

    // Appel de la fonction à tester
    determinerOrdres(tabOrdres, c, robot, 5);

    // Vérification des ordres générés
    CU_ASSERT_STRING_EQUAL(tabOrdres[0], "AV");
    CU_ASSERT_STRING_EQUAL(tabOrdres[1], "TG");
    CU_ASSERT_STRING_EQUAL(tabOrdres[2], "AV");
    CU_ASSERT_STRING_EQUAL(tabOrdres[3], "AV");
}

void test_creation_fichier_ordres(void) {
    // Chemin à suivre
    Chemin c;
    c.points[0] = 6;
    c.points[1] = 11;
    c.points[2] = 12;
    c.points[3] = 13;
    c.nb_points = 4;

    // Création du fichier d'ordres
    const char* nomFichierOrdres = "test_fichier_ordres.txt";
    creationFichierOrdres(nomFichierOrdres, c);

    // Vérification du contenu du fichier
    FILE* fichier = fopen(nomFichierOrdres, "r");
    CU_ASSERT_PTR_NOT_NULL(fichier);

    char ligne[10];
    fgets(ligne, sizeof(ligne), fichier);
    CU_ASSERT_STRING_EQUAL(ligne, "AV\n");
    fgets(ligne, sizeof(ligne), fichier);
    CU_ASSERT_STRING_EQUAL(ligne, "TG\n");
    fgets(ligne, sizeof(ligne), fichier);
    CU_ASSERT_STRING_EQUAL(ligne, "AV\n");
    fgets(ligne, sizeof(ligne), fichier);
    CU_ASSERT_STRING_EQUAL(ligne, "AV\n");
    fgets(ligne, sizeof(ligne), fichier);
    CU_ASSERT_STRING_EQUAL(ligne, "."); // Marqueur de fin

    fclose(fichier);
}


int main(void) {
    CU_pSuite pSuite = NULL;

    // Initialisation du registre de tests CUnit
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    // Ajout d'une suite de tests au registre
    pSuite = CU_add_suite("Suite_de_tests_graphe_ville", init_suite_success, clean_suite_success);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Ajout des tests à la suite
    if ((NULL == CU_add_test(pSuite, "test_largeur_ville", test_largeur_ville)) ||
        (NULL == CU_add_test(pSuite, "test_caseInitialeRobot", test_caseInitialeRobot)) ||
        (NULL == CU_add_test(pSuite, "test_liaisons_points", test_liaisons_points)) ||
        (NULL == CU_add_test(pSuite, "test_points_obligatoires", test_points_obligatoires)) ||
        (NULL == CU_add_test(pSuite, "test_creation_graphe_ville", test_creation_graphe_ville)) ||
        (NULL == CU_add_test(pSuite, "test_determiner_ordres", test_determiner_ordres)) ||
        (NULL == CU_add_test(pSuite, "test_creation_fichier_ordres", test_creation_fichier_ordres))
       )
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Exécution des tests en mode basique
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
