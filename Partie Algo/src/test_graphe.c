#include <CUnit/Basic.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "creationFichierOrdres.h"
#include "graphe_dijkstra.h"
#include "file.h"
#include "TAD_robot.h"

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
    unsigned int tabGraphe[NB_POINTS_MAX][2];
    unsigned int tabCaseObligatoires[MAX_CASES_OBLIGATOIRES];
    unsigned int nbLiaisons;
    unsigned int nbCasesObligatoires;
    unsigned int caseInitRobot;
    tDirection directionInitRobot;

    recuperationInfoFichier(fileName, &l, tabGraphe, tabCaseObligatoires, &nbLiaisons, &nbCasesObligatoires, &caseInitRobot, &directionInitRobot);
    CU_ASSERT_EQUAL(l, 5);
}

void test_caseInitialeRobot(void) {
    unsigned int l;
    unsigned int tabGraphe[NB_POINTS_MAX][2];
    unsigned int tabCaseObligatoires[MAX_CASES_OBLIGATOIRES];
    unsigned int nbLiaisons;
    unsigned int nbCasesObligatoires;
    unsigned int caseInitRobot;
    tDirection directionInitRobot;

    recuperationInfoFichier(fileName, &l, tabGraphe, tabCaseObligatoires, &nbLiaisons, &nbCasesObligatoires, &caseInitRobot, &directionInitRobot);
    CU_ASSERT_EQUAL(caseInitRobot, 6);
    CU_ASSERT_EQUAL(directionInitRobot, SUD);
}

void test_liaisons_points(void) {
    unsigned int l;
    unsigned int tabGraphe[NB_POINTS_MAX][2];
    unsigned int tabCaseObligatoires[MAX_CASES_OBLIGATOIRES];
    unsigned int nbLiaisons;
    unsigned int nbCasesObligatoires;
    unsigned int caseInitRobot;
    tDirection directionInitRobot;

    recuperationInfoFichier(fileName, &l, tabGraphe, tabCaseObligatoires, &nbLiaisons, &nbCasesObligatoires, &caseInitRobot, &directionInitRobot);
    CU_ASSERT_EQUAL(tabGraphe[0][1], 2);
    CU_ASSERT_EQUAL(tabGraphe[nbLiaisons-1][0], 24);
}

void test_points_obligatoires(void) {
    unsigned int l;
    unsigned int tabGraphe[NB_POINTS_MAX][2];
    unsigned int tabCaseObligatoires[MAX_CASES_OBLIGATOIRES];
    unsigned int nbLiaisons;
    unsigned int nbCasesObligatoires;
    unsigned int caseInitRobot;
    tDirection directionInitRobot;

    recuperationInfoFichier(fileName, &l, tabGraphe, tabCaseObligatoires, &nbLiaisons, &nbCasesObligatoires, &caseInitRobot, &directionInitRobot);
    CU_ASSERT_EQUAL(tabCaseObligatoires[0], 13);
    CU_ASSERT_EQUAL(tabCaseObligatoires[1], 22);
    CU_ASSERT_EQUAL(tabCaseObligatoires[2], 20);
}

/*
    Début des tests de chemin
*/
void test_obtenir_fixer_nb_points(void) {
    Chemin c;
    fixerNbPoints(&c, 5);
    CU_ASSERT_EQUAL(obtenirNbPoints(c), 5);
}

void test_obtenir_chemin(void) {
    Chemin c;
    c.points[0] = 1;
    c.points[1] = 2;
    c.points[2] = 3;
    c.nb_points = 3;

    unsigned int tabPoints[NB_POINTS_MAX] = {0};
    obtenirChemin(c, tabPoints);

    CU_ASSERT_EQUAL(tabPoints[0], 1);
    CU_ASSERT_EQUAL(tabPoints[1], 2);
    CU_ASSERT_EQUAL(tabPoints[2], 3);
}

/*
    Début des tests de création du graphe de la ville
*/
void test_creation_graphe_ville(void) {
    unsigned int tabLiaisonsVille[NB_POINTS_MAX][2] = {
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
void test_direction_robot(void) {
    Robot robot;
    setCaseRobot(&robot, 0);
    setDirection(&robot, NORD);

    CU_ASSERT_EQUAL(getDirection(robot), NORD);

    setDirection(&robot, EST);
    CU_ASSERT_EQUAL(getDirection(robot), EST);

    setDirection(&robot, SUD);
    CU_ASSERT_EQUAL(getDirection(robot), SUD);

    setDirection(&robot, OUEST);
    CU_ASSERT_EQUAL(getDirection(robot), OUEST);
}

void test_directionOuestEst(void) {
    CU_ASSERT_EQUAL(directionOuest(NORD), OUEST);
    CU_ASSERT_EQUAL(directionOuest(OUEST), SUD);
    CU_ASSERT_EQUAL(directionOuest(SUD), EST);
    CU_ASSERT_EQUAL(directionOuest(EST), NORD);

    CU_ASSERT_EQUAL(directionEst(NORD), EST);
    CU_ASSERT_EQUAL(directionEst(EST), SUD);
    CU_ASSERT_EQUAL(directionEst(SUD), OUEST);
    CU_ASSERT_EQUAL(directionEst(OUEST), NORD);
}

void test_ordreChangementDirection(void) {
    Robot robot;
    setCaseRobot(&robot, 0);
    setDirection(&robot, NORD);

    Ordre ordre1, ordre2;
    determinerOrdre(&robot, 1, 5, &ordre1, &ordre2); // Le robot doit aller à l'est

    CU_ASSERT_EQUAL(ordre1, TD); // Tourner à droite
    CU_ASSERT_EQUAL(ordre2, AV); // Avancer
}

void test_determiner_ordres_intersection_a_avancer(void) {
    Robot robot;
    setCaseRobot(&robot, 6);
    setDirection(&robot, SUD);
    
    unsigned int tabLiaisonsVille[NB_POINTS_MAX][2] = {
        {1, 2}, {1, 6}, {2, 3}, {2, 7}, {3, 4},
        {4, 5}, {5, 10}, {6, 11}, {7, 8}, {8, 13},
        {9, 10}, {9, 14}, {10, 15}, {11, 16}, {11, 12},
        {12, 17}, {12, 13}, {13, 14}, {14, 19}, {15, 20},
        {16, 21}, {17, 22}, {18, 19}, {18, 23}, {19, 20},
        {20, 25}, {21, 22}, {22, 23}, {23, 24}, {24, 25}
    };
    unsigned int nbLiaisons = 30;
    G_Graphe g = creationGrapheVille(tabLiaisonsVille, nbLiaisons);

    Chemin c;
    c.points[0] = 6;
    c.points[1] = 11;
    c.points[2] = 12;
    c.points[3] = 13;
    c.points[4] = 14; 
    c.nb_points = 5;

    Ordre tabOrdres[NB_POINTS_MAX];

    determinerOrdres(tabOrdres, c, g , robot, 5);

    // Comparaison avec les valeurs de l'enum Ordre
    CU_ASSERT_EQUAL(tabOrdres[0], AV);  
    CU_ASSERT_EQUAL(tabOrdres[1], TG);
    CU_ASSERT_EQUAL(tabOrdres[2], AV);
    CU_ASSERT_EQUAL(tabOrdres[3], AV);
    CU_ASSERT_EQUAL(tabOrdres[4], AV);
}

void test_intersection_tourner(void) {
    Robot robot;
    setCaseRobot(&robot, 1);
    setDirection(&robot, EST);

    unsigned int tabLiaisonsVille[NB_POINTS_MAX][2] = {
        {1, 2}, {1, 6}, {2, 3}, {2, 7}, {3, 4},
        {4, 5}, {5, 10}, {6, 11}, {7, 8}, {8, 13},
        {9, 10}, {9, 14}, {10, 15}, {11, 16}, {11, 12},
        {12, 17}, {12, 13}, {13, 14}, {14, 19}, {15, 20},
        {16, 21}, {17, 22}, {18, 19}, {18, 23}, {19, 20},
        {20, 25}, {21, 22}, {22, 23}, {23, 24}, {24, 25}
    };
    unsigned int nbLiaisons = 30;
    G_Graphe g = creationGrapheVille(tabLiaisonsVille, nbLiaisons);

    Chemin c;
    c.points[0] = 1;
    c.points[1] = 2;
    c.points[2] = 7;
    c.points[3] = 8;
    c.nb_points = 4;

    Ordre tabOrdres[NB_POINTS_MAX];

    determinerOrdres(tabOrdres, c, g ,robot, 5);

    // Comparaison avec les valeurs de l'enum Ordre
    CU_ASSERT_EQUAL(tabOrdres[0], AV);  
    CU_ASSERT_EQUAL(tabOrdres[1], TD);
    CU_ASSERT_EQUAL(tabOrdres[2], AV);
    CU_ASSERT_EQUAL(tabOrdres[3], TG);
    CU_ASSERT_EQUAL(tabOrdres[4], AV);
}

void test_pas_intersection_avancer(void) {
    Robot robot;
    setCaseRobot(&robot, 2);
    setDirection(&robot, EST);

    unsigned int tabLiaisonsVille[NB_POINTS_MAX][2] = {
        {1, 2}, {1, 6}, {2, 3}, {2, 7}, {3, 4},
        {4, 5}, {5, 10}, {6, 11}, {7, 8}, {8, 13},
        {9, 10}, {9, 14}, {10, 15}, {11, 16}, {11, 12},
        {12, 17}, {12, 13}, {13, 14}, {14, 19}, {15, 20},
        {16, 21}, {17, 22}, {18, 19}, {18, 23}, {19, 20},
        {20, 25}, {21, 22}, {22, 23}, {23, 24}, {24, 25}
    };
    unsigned int nbLiaisons = 30;
    G_Graphe g = creationGrapheVille(tabLiaisonsVille, nbLiaisons);

    Chemin c;
    c.points[0] = 2;
    c.points[1] = 3;
    c.points[2] = 4;
    c.points[3] = 5;
    c.nb_points = 4;

    Ordre tabOrdres[NB_POINTS_MAX];

    determinerOrdres(tabOrdres, c, g ,robot, 5);

    // Comparaison avec les valeurs de l'enum Ordre
    CU_ASSERT_EQUAL(tabOrdres[0], AV);
    CU_ASSERT_EQUAL(tabOrdres[1], NO); // fin des ordres
}

void test_creation_fichier_ordres_avancer_intersection(void) {
    // Chemin à suivre
    Chemin c;
    c.points[0] = 6;
    c.points[1] = 11;
    c.points[2] = 12;
    c.points[3] = 13;
    c.points[4] = 14;
    c.nb_points = 5;

    unsigned int tabLiaisonsVille[NB_POINTS_MAX][2] = {
        {1, 2}, {1, 6}, {2, 3}, {2, 7}, {3, 4},
        {4, 5}, {5, 10}, {6, 11}, {7, 8}, {8, 13},
        {9, 10}, {9, 14}, {10, 15}, {11, 16}, {11, 12},
        {12, 17}, {12, 13}, {13, 14}, {14, 19}, {15, 20},
        {16, 21}, {17, 22}, {18, 19}, {18, 23}, {19, 20},
        {20, 25}, {21, 22}, {22, 23}, {23, 24}, {24, 25}
    };
    unsigned int nbLiaisons = 30;
    G_Graphe g = creationGrapheVille(tabLiaisonsVille, nbLiaisons);

    // Création du fichier d'ordres
    const char* nomFichierOrdres = "test_fichier_ordres.txt";
    creationFichierOrdres(nomFichierOrdres, g , c, 5, SUD);

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
    CU_ASSERT_STRING_EQUAL(ligne, "AV\n");
    fgets(ligne, sizeof(ligne), fichier);
    CU_ASSERT_STRING_EQUAL(ligne, "."); // Marqueur de fin

    fclose(fichier);
}

void test_creation_fichier_ordres_tourner_intersection(void) {
    // Chemin à suivre
    Chemin c;
    c.points[0] = 1;
    c.points[1] = 2;
    c.points[2] = 7;
    c.points[3] = 8;
    c.nb_points = 4;

    unsigned int tabLiaisonsVille[NB_POINTS_MAX][2] = {
        {1, 2}, {1, 6}, {2, 3}, {2, 7}, {3, 4},
        {4, 5}, {5, 10}, {6, 11}, {7, 8}, {8, 13},
        {9, 10}, {9, 14}, {10, 15}, {11, 16}, {11, 12},
        {12, 17}, {12, 13}, {13, 14}, {14, 19}, {15, 20},
        {16, 21}, {17, 22}, {18, 19}, {18, 23}, {19, 20},
        {20, 25}, {21, 22}, {22, 23}, {23, 24}, {24, 25}
    };
    unsigned int nbLiaisons = 30;
    G_Graphe g = creationGrapheVille(tabLiaisonsVille, nbLiaisons);

    // Création du fichier d'ordres
    const char* nomFichierOrdres = "test_fichier_ordres.txt";
    creationFichierOrdres(nomFichierOrdres, g , c, 5, EST);

    // Vérification du contenu du fichier
    FILE* fichier = fopen(nomFichierOrdres, "r");
    CU_ASSERT_PTR_NOT_NULL(fichier);

    char ligne[10];
    fgets(ligne, sizeof(ligne), fichier);
    CU_ASSERT_STRING_EQUAL(ligne, "AV\n");
    fgets(ligne, sizeof(ligne), fichier);
    CU_ASSERT_STRING_EQUAL(ligne, "TD\n");
    fgets(ligne, sizeof(ligne), fichier);
    CU_ASSERT_STRING_EQUAL(ligne, "AV\n");
    fgets(ligne, sizeof(ligne), fichier);
    CU_ASSERT_STRING_EQUAL(ligne, "TG\n");
    fgets(ligne, sizeof(ligne), fichier);
    CU_ASSERT_STRING_EQUAL(ligne, "AV\n");
    fgets(ligne, sizeof(ligne), fichier);
    CU_ASSERT_STRING_EQUAL(ligne, "."); // Marqueur de fin

    fclose(fichier);
}

/*
    tests de Dijkstra si le depart est aussi l'arrivée
*/
void test_dijkstra_depart_egal_arrivee(void) {
    unsigned int tabLiaisonsVille[NB_POINTS_MAX][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 4},
        {0, 5}, {5, 6}, {6, 7}, {7, 8},
        {1, 6}, {2, 7}, {3, 8}, {4, 9},
        {5, 10}, {10, 11}, {11, 12}, {12, 13},
        {6, 11}, {7, 12}, {8, 13}, {9, 14}
    };
    unsigned int nbLiaisons = 20;
    G_Graphe g = creationGrapheVille(tabLiaisonsVille, nbLiaisons);
    
    Chemin resultat = dijkstra(&g, 2, 2);
    
    CU_ASSERT_EQUAL(resultat.nb_points, 1);
    CU_ASSERT_EQUAL(resultat.points[0], 2);
    
    G_vider(&g);
}

/*
    tests de Dijkstra pour un chemin entre 2 points
*/
void test_dijkstra_1_chemin(void) {
    unsigned int tabLiaisonsVille[NB_POINTS_MAX][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 4},
        {0, 5}, {5, 6}, {6, 7}, {7, 8},
        {1, 6}, {2, 7}, {3, 8}, {4, 9},
        {5, 10}, {10, 11}, {11, 12}, {12, 13},
        {6, 11}, {7, 12}, {8, 13}, {9, 14}
    };
    unsigned int nbLiaisons = 20;
    G_Graphe g = creationGrapheVille(tabLiaisonsVille, nbLiaisons);

    // On veut savoir le chemin le plus court entre le point 6 et 13
    
    Chemin resultat = dijkstra(&g, 6, 13);
    
    CU_ASSERT_EQUAL(resultat.nb_points, 4);
    CU_ASSERT_EQUAL(resultat.points[0], 6);
    CU_ASSERT_EQUAL(resultat.points[3], 13);
    
    G_vider(&g);
}

/*
    tests de Dijkstra pour le chemin entier en passant par les points obligatoires
    ceulement les 3 chemins en partant de la case départ
*/
void test_dijkstra_points_obligatoires(void) {
    unsigned int tabLiaisonsVille[NB_POINTS_MAX][2] = {
        {1,2}, {1,6}, {2,3}, {2,7}, {3,4},
        {4,5}, {5,10}, {6,11}, {7,8}, {8,13},
        {9,14}, {10,15}, {11,16}, {11,12}, {12,17},
        {12,13}, {14,19}, {15,20}, {16,21}, {17,22},
        {18,19}, {18,23}, {19,20}, {20,25}, {21,22},
        {22,23}, {23, 24}
    };
    unsigned int nbLiaisons = 27;
    G_Graphe g = creationGrapheVille(tabLiaisonsVille, nbLiaisons);
    
    // Test avec des points intermédiaires
    // De 6 (case départ robot) vers 13, 22, 20
    Chemin chemin1 = dijkstra(&g, 6, 13);
    CU_ASSERT_TRUE(chemin1.nb_points > 0);
    CU_ASSERT_EQUAL(chemin1.points[0], 6);
    CU_ASSERT_EQUAL(chemin1.points[chemin1.nb_points - 1], 13);
    
    Chemin chemin2 = dijkstra(&g, 6, 22);
    CU_ASSERT_TRUE(chemin2.nb_points > 0);
    CU_ASSERT_EQUAL(chemin2.points[0], 6);
    CU_ASSERT_EQUAL(chemin2.points[chemin2.nb_points - 1], 22);
    
    Chemin chemin3 = dijkstra(&g, 6, 20);
    CU_ASSERT_TRUE(chemin3.nb_points > 0);
    CU_ASSERT_EQUAL(chemin3.points[0], 6);
    CU_ASSERT_EQUAL(chemin3.points[chemin3.nb_points - 1], 20);
    
    G_vider(&g);
}

/*
    test si les permutations s'executent dans l'ordre correct
*/
void test_permutation_ordre_correct(void) {
    unsigned int arr[3] = {10, 20, 30};
    unsigned int permutations[6][3];
    
    permutation(arr, permutations);
    
    // Verification des 6 permutations
    CU_ASSERT_EQUAL(permutations[0][0], 10);
    CU_ASSERT_EQUAL(permutations[0][1], 20);
    CU_ASSERT_EQUAL(permutations[0][2], 30);
    
    CU_ASSERT_EQUAL(permutations[1][0], 10);
    CU_ASSERT_EQUAL(permutations[1][1], 30);
    CU_ASSERT_EQUAL(permutations[1][2], 20);
    
    CU_ASSERT_EQUAL(permutations[2][0], 20);
    CU_ASSERT_EQUAL(permutations[2][1], 10);
    CU_ASSERT_EQUAL(permutations[2][2], 30);
    
    CU_ASSERT_EQUAL(permutations[5][0], 30);
    CU_ASSERT_EQUAL(permutations[5][1], 20);
    CU_ASSERT_EQUAL(permutations[5][2], 10);
}

void test_permutation_points_ville(void) {
    unsigned int arr[3] = {13, 22, 20};
    unsigned int permutations[6][3];
    
    permutation(arr, permutations);
    
    // Verification que les permutations ont les bonnes valeurs
    for(unsigned int i = 0; i < 6; i++) {
        bool contient13 = false, contient22 = false, contient20 = false;
        for(unsigned int j = 0; j < 3; j++) {
            if(permutations[i][j] == 13){
                 contient13 = true;
                }
            if(permutations[i][j] == 22){
                contient22 = true;
            } 
            if(permutations[i][j] == 20){
                contient20 = true;
            } 
        }
        CU_ASSERT_TRUE(contient13);
        CU_ASSERT_TRUE(contient22);
        CU_ASSERT_TRUE(contient20);
    }
}

/*
    tests que le TAD file est correct
*/
void test_file_initialisation(void) {
    File* f = malloc(sizeof(File)); // Ne pas oublier d'allouer la mémoire à la file
    initialisation_file(f);
    
    CU_ASSERT_TRUE(estVideFile(f));
    CU_ASSERT_FALSE(estPleineFile(f));

    liberer_file(f);
}

/*
    tests que la file enfile et defile
*/
void test_file_enfiler_defiler(void) {
    File* f = malloc(sizeof(File)); // Ne pas oublier d'allouer la mémoire à la file
    initialisation_file(f);
    
    EtatDuDijkstra etat;
    etat.point_actuel = 5;
    etat.point_precedent = -1;
    etat.chemin.points[0] = 5;
    etat.chemin.nb_points = 1;
    
    enfiler(f, etat);
    CU_ASSERT_FALSE(estVideFile(f));
    
    EtatDuDijkstra etat_recupere = defiler(f);
    CU_ASSERT_EQUAL(etat_recupere.point_actuel, 5);
    CU_ASSERT_EQUAL(etat_recupere.chemin.nb_points, 1);
    CU_ASSERT_TRUE(estVideFile(f));
    liberer_file(f);
}

/*
    tests que l'on a bien une liste fifo
*/
void test_file_ordre_fifo(void) {
    File* f = malloc(sizeof(File)); // Ne pas oublier d'allouer la mémoire à la file
    initialisation_file(f);
    
    // Enfiler 5 états
    for(int i = 0; i < 5; i++) {
        EtatDuDijkstra etat;
        etat.point_actuel = i;
        etat.point_precedent = -1;
        etat.chemin.nb_points = 1;
        etat.chemin.points[0] = i;
        enfiler(f, etat);
    }
    
    // Vérifier l'ordre FIFO
    for(int i = 0; i < 5; i++) {
        EtatDuDijkstra etat = defiler(f);
        CU_ASSERT_EQUAL(etat.point_actuel, i);
    }
    
    CU_ASSERT_TRUE(estVideFile(f));
    liberer_file(f);
}   

/*
    Tests pour la solution
*/
void test_solution_graphe_simple_5x5(void) {
    // On crée le graphe 5x5
    unsigned int tabLiaisonsVille[NB_POINTS_MAX][2] = {
        {1, 2}, {1, 6}, {2, 3}, {2, 7}, {3, 4},
        {4, 5}, {5, 10}, {6, 11}, {7, 8}, {8, 13},
        {9, 10}, {9, 14}, {10, 15}, {11, 16}, {11, 12},
        {12, 17}, {12, 13}, {13, 14}, {14, 19}, {15, 20},
        {16, 21}, {17, 22}, {18, 19}, {18, 23}, {19, 20},
        {20, 25}, {21, 22}, {22, 23}, {23, 24}, {24, 25}
    };
    unsigned int nbLiaisons = 30;
    G_Graphe g = creationGrapheVille(tabLiaisonsVille, nbLiaisons);

    // Points obligatoires à visiter
    unsigned int points_obligatoires[3] = {13, 22, 20};
    unsigned int depart = 6;
    unsigned int longueur_ville = 5;

    // Calcul de la solution
    Solution solution = resoudre_chemin_plus_court(&g, points_obligatoires, depart, longueur_ville);

    CU_ASSERT_TRUE(solution.chemin_complet.nb_points > 0);
    CU_ASSERT_EQUAL(solution.chemin_complet.points[0], depart); // Le premier point du chemin est bien le départ

    // Le dernier point du chemin complet doit être le point de départ
    CU_ASSERT_EQUAL(solution.chemin_complet.points[solution.chemin_complet.nb_points - 1], depart);

    // Les points de passage doivent être un de ces trois points
    CU_ASSERT_TRUE(solution.ordre[0] == 13 || solution.ordre[0] == 22 || solution.ordre[0] == 20);
    CU_ASSERT_TRUE(solution.ordre[1] == 13 || solution.ordre[1] == 22 || solution.ordre[1] == 20);
    CU_ASSERT_TRUE(solution.ordre[2] == 13 || solution.ordre[2] == 22 || solution.ordre[2] == 20);

    G_vider(&g);
}

/*
    Tests pour vérifier qu'on passe bien par les trois points obligatoires
*/
void test_solution_parcours_points_obligatoires(void) {
    unsigned int tabLiaisonsVille[NB_POINTS_MAX][2] = {
        {1, 2}, {1, 6}, {2, 3}, {2, 7}, {3, 4},
        {4, 5}, {5, 10}, {6, 11}, {7, 8}, {8, 13},
        {9, 10}, {9, 14}, {10, 15}, {11, 16}, {11, 12},
        {12, 17}, {12, 13}, {13, 14}, {14, 19}, {15, 20},
        {16, 21}, {17, 22}, {18, 19}, {18, 23}, {19, 20},
        {20, 25}, {21, 22}, {22, 23}, {23, 24}, {24, 25}
    };
    unsigned int nbLiaisons = 30;
    G_Graphe g = creationGrapheVille(tabLiaisonsVille, nbLiaisons);

    // Points obligatoires à visiter
    unsigned int points_obligatoires[3] = {13, 22, 20};
    unsigned int depart = 6;
    unsigned int longueur_ville = 5;

    // Calcul de la solution
    Solution solution = resoudre_chemin_plus_court(&g, points_obligatoires, depart, longueur_ville);

    // On vérifie que pendant le parcours on passe bien par les points
    bool trouve13 = false, trouve22 = false, trouve20 = false;
    for(unsigned int i = 0; i < solution.chemin_complet.nb_points; i++) {
        if(solution.chemin_complet.points[i] == 13) {
            trouve13 = true;
        }
        if(solution.chemin_complet.points[i] == 22) {
            trouve22 = true;
        }
        if(solution.chemin_complet.points[i] == 20) {
            trouve20 = true;
        }
    }
    CU_ASSERT_TRUE(trouve13);
    CU_ASSERT_TRUE(trouve20);
    CU_ASSERT_TRUE(trouve22);

    G_vider(&g);
}

/*
    Vérifier que le robot retourne bien à la case départ
*/
void test_solution_retour_au_depart(void) {
    unsigned int tabLiaisonsVille[NB_POINTS_MAX][2] = {
        {1, 2}, {1, 6}, {2, 3}, {2, 7}, {3, 4},
        {4, 5}, {5, 10}, {6, 11}, {7, 8}, {8, 13},
        {9, 10}, {9, 14}, {10, 15}, {11, 16}, {11, 12},
        {12, 17}, {12, 13}, {13, 14}, {14, 19}, {15, 20},
        {16, 21}, {17, 22}, {18, 19}, {18, 23}, {19, 20},
        {20, 25}, {21, 22}, {22, 23}, {23, 24}, {24, 25}
    };
    unsigned int nbLiaisons = 30;
    G_Graphe g = creationGrapheVille(tabLiaisonsVille, nbLiaisons);

    // Points obligatoires à visiter
    unsigned int points_obligatoires[3] = {13, 22, 20};
    unsigned int depart = 6;
    unsigned int longueur_ville = 5;

    // Calcul de la solution
    Solution solution = resoudre_chemin_plus_court(&g, points_obligatoires, depart, longueur_ville);

    // Vérification que le premier point et le dernier soient identiques
    CU_ASSERT_EQUAL(solution.chemin_complet.points[solution.chemin_complet.nb_points - 1], depart);
    CU_ASSERT_EQUAL(solution.chemin_complet.points[0], depart);

    G_vider(&g);
}

/*
    Vérifier que le chemin est le meilleur possible
*/
void test_solution_meilleur_chemin(void) {
    unsigned int tabLiaisonsVille[NB_POINTS_MAX][2] = {
        {1, 2}, {1, 6}, {2, 3}, {2, 7}, {3, 4},
        {4, 5}, {5, 10}, {6, 11}, {7, 8}, {8, 13},
        {9, 10}, {9, 14}, {10, 15}, {11, 16}, {11, 12},
        {12, 17}, {12, 13}, {13, 14}, {14, 19}, {15, 20},
        {16, 21}, {17, 22}, {18, 19}, {18, 23}, {19, 20},
        {20, 25}, {21, 22}, {22, 23}, {23, 24}, {24, 25}
    };
    unsigned int nbLiaisons = 30;
    G_Graphe g = creationGrapheVille(tabLiaisonsVille, nbLiaisons);

    // Points obligatoires à visiter
    unsigned int points_obligatoires[3] = {13, 22, 20};
    unsigned int depart = 6;
    unsigned int longueur_ville = 5;

    Solution solution = resoudre_chemin_plus_court(&g, points_obligatoires, depart, longueur_ville);

    // Vérification que le chemin est valide
    for(unsigned int i = 0; i < solution.chemin_complet.nb_points - 1; i++) {
        unsigned int point_actuel = solution.chemin_complet.points[i];
        unsigned int point_suivant = solution.chemin_complet.points[i + 1];
        CU_ASSERT_TRUE(G_arcPresent(g, point_actuel, point_suivant) || G_arcPresent(g, point_suivant, point_actuel));
    }

    G_vider(&g);
}

/*
    Vérifier la continuité du chemin
*/
void test_solution_continuite_chemin(void) {
    unsigned int tabLiaisonsVille[NB_POINTS_MAX][2] = {
        {1, 2}, {1, 6}, {2, 3}, {2, 7}, {3, 4},
        {4, 5}, {5, 10}, {6, 11}, {7, 8}, {8, 13},
        {9, 10}, {9, 14}, {10, 15}, {11, 16}, {11, 12},
        {12, 17}, {12, 13}, {13, 14}, {14, 19}, {15, 20},
        {16, 21}, {17, 22}, {18, 19}, {18, 23}, {19, 20},
        {20, 25}, {21, 22}, {22, 23}, {23, 24}, {24, 25}
    };
    unsigned int nbLiaisons = 30;
    G_Graphe g = creationGrapheVille(tabLiaisonsVille, nbLiaisons);

    // Points obligatoires à visiter
    unsigned int points_obligatoires[3] = {13, 22, 20};
    unsigned int depart = 6;
    unsigned int longueur_ville = 5;

    Solution solution = resoudre_chemin_plus_court(&g, points_obligatoires, depart, longueur_ville);

    // Vérification que le chemin effectue est valide
    for(unsigned int i = 0; i < solution.chemin_complet.nb_points - 1; i++) {
        unsigned int point_actuel = solution.chemin_complet.points[i];
        unsigned int point_suivant = solution.chemin_complet.points[i + 1];
        CU_ASSERT_TRUE(G_arcPresent(g, point_actuel, point_suivant) || G_arcPresent(g, point_suivant, point_actuel));
    }

    G_vider(&g);
}

/*
    Début test creation fichier a partir du meilleur chemin
*/
void test_fichier_ordres_a_partir_meilleur_chemin(void) {
    unsigned int tabLiaisonsVille[NB_POINTS_MAX][2] = {
        {1, 2}, {1, 6}, {2, 3}, {2, 7}, {3, 4},
        {4, 5}, {5, 10}, {6, 11}, {7, 8}, {8, 13},
        {9, 10}, {9, 14}, {10, 15}, {11, 16}, {11, 12},
        {12, 17}, {12, 13}, {13, 14}, {14, 19}, {15, 20},
        {16, 21}, {17, 22}, {18, 19}, {18, 23}, {19, 20},
        {20, 25}, {21, 22}, {22, 23}, {23, 24}, {24, 25}
    };
    unsigned int nbLiaisons = 30;
    G_Graphe g = creationGrapheVille(tabLiaisonsVille, nbLiaisons);

    // Points obligatoires à visiter
    unsigned int points_obligatoires[3] = {13, 22, 20};
    unsigned int depart = 6;
    unsigned int longueur_ville = 5;

    Solution solution = resoudre_chemin_plus_court(&g, points_obligatoires, depart, longueur_ville);

    const char* nomFichierOrdres = "test_fichier_ordres_solution.txt";
    creationFichierOrdres(nomFichierOrdres, g , solution.chemin_complet, longueur_ville, SUD);
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
    CU_ASSERT_STRING_EQUAL(ligne, "AV\n");
    fgets(ligne, sizeof(ligne), fichier);
    CU_ASSERT_STRING_EQUAL(ligne, "TD\n");
    fgets(ligne, sizeof(ligne), fichier);
    CU_ASSERT_STRING_EQUAL(ligne, "AV\n");
    fgets(ligne, sizeof(ligne), fichier);
    CU_ASSERT_STRING_EQUAL(ligne, "TG\n");
    fgets(ligne, sizeof(ligne), fichier);
    CU_ASSERT_STRING_EQUAL(ligne, "AV\n");
    fgets(ligne, sizeof(ligne), fichier);
    CU_ASSERT_STRING_EQUAL(ligne, "TD\n");
    fgets(ligne, sizeof(ligne), fichier);
    CU_ASSERT_STRING_EQUAL(ligne, "AV\n");
    fgets(ligne, sizeof(ligne), fichier);
    CU_ASSERT_STRING_EQUAL(ligne, "TD\n");
    fgets(ligne, sizeof(ligne), fichier);
    CU_ASSERT_STRING_EQUAL(ligne, "AV\n");
    fgets(ligne, sizeof(ligne), fichier);
    CU_ASSERT_STRING_EQUAL(ligne, "AV\n");
    fgets(ligne, sizeof(ligne), fichier);
    CU_ASSERT_STRING_EQUAL(ligne, "TD\n");
    fgets(ligne, sizeof(ligne), fichier);
    CU_ASSERT_STRING_EQUAL(ligne, "AV\n");
    fgets(ligne, sizeof(ligne), fichier);
    CU_ASSERT_STRING_EQUAL(ligne, "TG\n");
    fgets(ligne, sizeof(ligne), fichier);
    CU_ASSERT_STRING_EQUAL(ligne, "AV\n");
    fgets(ligne, sizeof(ligne), fichier);
    CU_ASSERT_STRING_EQUAL(ligne, "TD\n");
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
        (NULL == CU_add_test(pSuite, "test_obtenir_fixer_nb_points", test_obtenir_fixer_nb_points)) ||
        (NULL == CU_add_test(pSuite, "test_obtenir_chemin", test_obtenir_chemin)) ||
        (NULL == CU_add_test(pSuite, "test_creation_graphe_ville", test_creation_graphe_ville)) ||
        (NULL == CU_add_test(pSuite, "test_direction_robot", test_direction_robot)) ||
        (NULL == CU_add_test(pSuite, "test_directionOuestEst", test_directionOuestEst)) ||
        (NULL == CU_add_test(pSuite, "test_ordreChangementDirection", test_ordreChangementDirection)) ||
        (NULL == CU_add_test(pSuite, "test_determiner_ordres_intersection_a_avancer", test_determiner_ordres_intersection_a_avancer)) ||
        (NULL == CU_add_test(pSuite, "test_intersection_tourner", test_intersection_tourner)) || 
        (NULL == CU_add_test(pSuite, "test_pas_intersection_avancer", test_pas_intersection_avancer)) ||
        (NULL == CU_add_test(pSuite, "test_creation_fichier_ordres_avancer_intersection", test_creation_fichier_ordres_avancer_intersection)) ||
        (NULL == CU_add_test(pSuite, "test_creation_fichier_ordres_tourner_intersection", test_creation_fichier_ordres_tourner_intersection)) ||
        (NULL == CU_add_test(pSuite, "test_dijkstra_depart_egal_arrivee", test_dijkstra_depart_egal_arrivee)) ||
        (NULL == CU_add_test(pSuite, "test_dijkstra_1_chemin", test_dijkstra_1_chemin)) ||
        (NULL == CU_add_test(pSuite, "test_dijkstra_points_obligatoires", test_dijkstra_points_obligatoires)) ||
        (NULL == CU_add_test(pSuite, "test_permutation_ordre_correct", test_permutation_ordre_correct)) ||
        (NULL == CU_add_test(pSuite, "test_permutation_points_ville", test_permutation_points_ville)) ||
        (NULL == CU_add_test(pSuite, "test_file_initialisation", test_file_initialisation)) ||
        (NULL == CU_add_test(pSuite, "test_file_enfiler_defiler", test_file_enfiler_defiler)) ||
        (NULL == CU_add_test(pSuite, "test_file_ordre_fifo", test_file_ordre_fifo)) ||
        (NULL == CU_add_test(pSuite, "test_solution_graphe_simple_5x5", test_solution_graphe_simple_5x5)) ||
        (NULL == CU_add_test(pSuite, "test_solution_parcours_points_obligatoires", test_solution_parcours_points_obligatoires)) ||
        (NULL == CU_add_test(pSuite, "test_solution_retour_au_depart", test_solution_retour_au_depart)) ||
        (NULL == CU_add_test(pSuite, "test_solution_meilleur_chemin", test_solution_meilleur_chemin)) ||
        (NULL == CU_add_test(pSuite, "test_solution_continuite_chemin", test_solution_continuite_chemin)) ||
        (NULL == CU_add_test(pSuite, "test_fichier_ordres_a_partir_meilleur_chemin", test_fichier_ordres_a_partir_meilleur_chemin)))
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
