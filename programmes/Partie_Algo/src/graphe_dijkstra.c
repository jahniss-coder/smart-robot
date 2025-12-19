/**
 * @file graphe_dijkstra.c
 * @brief Implémentation des fonctions pour la création du graphe et la résolution du plus court chemin
 * @author Delacroix-Henrion Mathieu, Diallo Alioune, Malherbe Ylann, Mathieu Ilan, Olivier Neil, Schetrit Jahnis
 * @date 2025-12
 */

#include <stdio.h>
#include <stdlib.h>
#include "graphe_dijkstra.h"
#include "TAD_robot.h"
#include "graphe.h"
#include "file.h"
#include "ListeChaineeListe.h"


/*
    @brief L'objectif ici est de concevoir l'algorithme permettant de créer le graphe à partir du fichier de description de la ville.
    @param  FILE fichierVille
    @return Graphe circuit
*/
void recuperationInfoFichier(const char* fileNameVille, unsigned int* l, unsigned int tabPourGraphe[NB_POINTS_MAX][2],
    unsigned int tabCaseObligatoires[MAX_CASES_OBLIGATOIRES], unsigned int* nbLiaisons, unsigned int* nbCasesObligatoires, 
    unsigned int* caseInitRobot, tDirection* orientationInitRobot) {

    FILE *fichier = fopen(fileNameVille,"r"); // On lit juste ce fichier on n'écrit pas dedans.

    fscanf(fichier, "%u" , l);

    char orientationInitRobotChar; 
    fscanf(fichier, "%u%c", caseInitRobot, &orientationInitRobotChar);

    switch (orientationInitRobotChar)
    {
    case 'N':
        *orientationInitRobot = NORD;
        break;
    case 'S':
        *orientationInitRobot = SUD;
        break;
    case 'E':
        *orientationInitRobot = EST;
        break;
    case 'O':
        *orientationInitRobot = OUEST;
        break;
    default:
        break;
    }

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


/**
 * @brief Algorithme de creation du graphe à partir d'un tableau de liaison
 * @param tabLiaisonsVille Tableau des liaisons entre les points de la ville
 * @param nbLiaisons Nombre de liaisons dans la ville
 * @return Graphe non orienté de la ville avec les distances toutes égales à 1.
 */
G_Graphe creationGrapheVille(unsigned int tabLiaisonsVille[NB_POINTS_MAX][2], unsigned int nbLiaisons) {
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


/**
 * @brief Algorithme de Dijkstra modifié pour éviter certains points
 * @param g Pointeur vers le graphe
 * @param depart Indice du sommet de départ
 * @param arrivee Indice du sommet d'arrivée
 * @param sommets_a_eviter Tableau des indices des sommets à éviter
 * @param nb_a_eviter Nombre de sommets à éviter
 * @return Le chemin le plus court entre le sommet de départ et le sommet d'arrivée en évitant les sommets spécifiés
 */
Chemin dijkstra_avec_exclusions(G_Graphe* g, unsigned int depart, unsigned int arrivee,
                                 unsigned int* sommets_a_eviter, unsigned int nb_a_eviter) {
    Chemin resultat = {0};
    
    unsigned int points_visites[NB_POINTS_MAX][NB_POINTS_MAX];
    for (unsigned int i = 0; i < NB_POINTS_MAX; i++) {
        for(unsigned int j = 0; j < NB_POINTS_MAX; j++) {
            points_visites[i][j] = 0;
        }
    }

    File* file = malloc(sizeof(File));
    initialisation_file(file);

    EtatDuDijkstra initial;
    initial.point_actuel = depart;
    initial.point_precedent = 0;
    initial.chemin.points[0] = depart;
    initial.chemin.nb_points = 1;
    enfiler(file, initial);
    
    points_visites[depart][0] = 1;

    while (!estVideFile(file)) {
        EtatDuDijkstra etat = defiler(file);
        
        if (etat.point_actuel == arrivee) {
            resultat.nb_points = etat.chemin.nb_points;
            for (unsigned int i = 0; i < etat.chemin.nb_points; i++) {
                resultat.points[i] = etat.chemin.points[i];
            }
            liberer_file(file);
            return resultat;
        }
        
        LCL_Liste voisins = G_obtenirSommetsAdjacents(*g, etat.point_actuel);
        
        for (unsigned int i = 0; i < LCL_longueur(voisins); i++) {
            unsigned int voisin = *(unsigned int *)LCL_element(voisins, i);
            
            // Éviter le demi-tour immédiat
            if (voisin == etat.point_precedent) {
                continue;
            }
            
            // Vérifier si ce voisin est un le point à exclure
            int est_a_eviter = 0;
            for (unsigned int k = 0; k < nb_a_eviter; k++) {
                if (voisin == sommets_a_eviter[k]) {
                    est_a_eviter = 1;
                    break;
                }
            }
            
            if (est_a_eviter) {
                continue;
            }
            
            // Éviter de revisiter un point déjà dans le chemin actuel
            int deja_dans_chemin = 0;
            if (voisin != arrivee) {
                for (unsigned int k = 0; k < etat.chemin.nb_points; k++) {
                    if (etat.chemin.points[k] == voisin) {
                        deja_dans_chemin = 1;
                        break;
                    }
                }
            }
            
            if (deja_dans_chemin) {
                continue;
            }
            
            unsigned int index_precedent = (etat.point_actuel == (unsigned int)-1) ? 0 : etat.point_actuel;
            
            if (points_visites[voisin][index_precedent]) {
                continue;
            }
            
            points_visites[voisin][index_precedent] = 1;
            
            EtatDuDijkstra nouvel_etat;
            nouvel_etat.point_actuel = voisin;
            nouvel_etat.point_precedent = etat.point_actuel;
            nouvel_etat.chemin.nb_points = etat.chemin.nb_points + 1;
            
            for (unsigned int j = 0; j < etat.chemin.nb_points; j++) {
                nouvel_etat.chemin.points[j] = etat.chemin.points[j];
            }
            nouvel_etat.chemin.points[etat.chemin.nb_points] = voisin;
            
            enfiler(file, nouvel_etat);
        }
        LCL_vider(&voisins);
    }
    
    liberer_file(file);
    return resultat;
}


/**
 * @brief Algorithme de Dijkstra pour trouver le chemin le plus court entre deux sommets
 * @param g Pointeur vers le graphe
 * @param depart Indice du sommet de départ
 * @param arrivee Indice du sommet d'arrivée
 * @return Le chemin le plus court entre le sommet de départ et le sommet d'arrivée
 */
Chemin dijkstra(G_Graphe* g, unsigned int depart, unsigned int arrivee) {
    return dijkstra_avec_exclusions(g, depart, arrivee, NULL, 0);
}



/**
 * @brief Génère toutes les permutations des indices donnés
 * @param indices Tableau des indices à permuter
 * @param permutations Tableau pour stocker les permutations générées
 */
void permutation(unsigned int arr[3], unsigned int permutations[6][3]) {
    unsigned int perm[6][3] = {
        {0, 1, 2}, {0, 2, 1},
        {1, 0, 2}, {1, 2, 0},
        {2, 0, 1}, {2, 1, 0}
    };
    
    for(unsigned int i = 0; i < 6; i++) {
        for(unsigned int j = 0; j < 3; j++) {
            permutations[i][j] = arr[perm[i][j]];
        }
    }
}

/**
 * @brief Vérifie si un chemin est autorisé (ne passe pas par des sommets interdits)
 * @param c Le chemin à vérifier
 * @return 1 si le chemin est autorisé, 0 sinon
 */
int chemin_autorise(Chemin c) {
    for (unsigned int i = 0; i < c.nb_points - 2; i++) {
        if (c.points[i] == c.points[i + 2]) {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Vérifie si un chemin est autorisé (ne passe pas par des sommets interdits)
 * @param c Le chemin à vérifier
 * @return 1 si le chemin est autorisé, 0 sinon
 */
int verifier_jonction_segments(Chemin segment1, Chemin segment2) {
    if (segment1.nb_points >= 2 && segment2.nb_points >= 2) {
        unsigned int avant_dernier_seg1 = segment1.points[segment1.nb_points - 2];
        unsigned int deuxieme_seg2 = segment2.points[1];
        
        if (avant_dernier_seg1 == deuxieme_seg2) {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Résout le problème du chemin le plus court en passant par des points obligatoires
 * @param g Pointeur vers le graphe
 * @param point_obligatoires Tableau des indices des points obligatoires à visiter
 * @param depart Indice du sommet de départ
 * @param longueur_ville Longueur (largeur) de la ville (utilisée pour les calculs)
 * @return La solution contenant l'ordre des points visités et le chemin complet
 */
Solution resoudre_chemin_plus_court(G_Graphe* g, unsigned int point_obligatoires[3], 
                                     unsigned int depart, unsigned int longueur_ville, tDirection directionInitialeRobot) {
    Solution solution = {0};
    solution.chemin_complet.nb_points = 0;
    unsigned int meilleure_distance = 99999;

    unsigned int point_cles[4];
    point_cles[0] = depart;
    for(unsigned int i = 1; i < 4; i++) {
        point_cles[i] = point_obligatoires[i - 1];
    }

    unsigned int indices_classement[3] = {1, 2, 3};
    unsigned int permutations[6][3];
    permutation(indices_classement, permutations);

    // Tester chaque permutation
    for (unsigned int p = 0; p < 6; p++) {        
        unsigned int parcours[5];
        parcours[0] = 0;
        parcours[1] = permutations[p][0];
        parcours[2] = permutations[p][1];
        parcours[3] = permutations[p][2];
        parcours[4] = 0;

        unsigned int distance_totale = 0;
        unsigned int estValide = 1;
        Chemin segments[4];

        // CALCUL DES SEGMENTS AVEC EXCLUSION
        for (unsigned int i = 0; i < 4; i++) {
            unsigned int index_debut = parcours[i];
            unsigned int index_fin = parcours[i + 1];
            unsigned int sommet_depart = point_cles[index_debut];
            unsigned int sommet_arrivee = point_cles[index_fin];

            // Déterminer le sommet à exclure
            unsigned int sommets_a_eviter = 0;
            unsigned int nb_a_eviter = 1;

            if (i > 0) {
                Chemin segment_precedent = segments[i - 1];
                sommets_a_eviter = segment_precedent.points[segment_precedent.nb_points - 2];
                nb_a_eviter = 1;
            } else {
                if (directionInitialeRobot == SUD) {
                    sommets_a_eviter = depart - longueur_ville;
                }
                else if (directionInitialeRobot == NORD) {
                    sommets_a_eviter = depart + longueur_ville;
                }
                else if (directionInitialeRobot == EST) {
                    sommets_a_eviter = depart - 1;
                }
                else {
                    sommets_a_eviter = depart + 1;
                }
            }

            // Calculer le chemin avec exclusions
            segments[i] = dijkstra_avec_exclusions(g, sommet_depart, sommet_arrivee, 
                                                    &sommets_a_eviter, nb_a_eviter);

            if (segments[i].nb_points == 0) {
                estValide = 0;
                break;
            }

            // Vérifier les demi-tours internes
            if (!chemin_autorise(segments[i])) {
                estValide = 0;
                break;
            }

            distance_totale += (segments[i].nb_points - 1);
        }

        // Vérification des jonctions
        if (estValide) {
            for (unsigned int i = 0; i < 3; i++) {
                if (!verifier_jonction_segments(segments[i], segments[i + 1])) {
                    estValide = 0;
                    break;
                }
            }
        }

        if (!estValide) {
            continue;
        }

        // Si cette permutation est valide et meilleure
        if (distance_totale < meilleure_distance) {
            meilleure_distance = distance_totale;

            for(unsigned int i = 0; i < 3; i++) {
                solution.ordre[i] = point_cles[permutations[p][i]];
            }

            // Reconstruction du chemin complet
            unsigned int index = 0;
            
            for(unsigned int i = 0; i < 4; i++) {
                unsigned int debut = (i == 0) ? 0 : 1;
                
                for(unsigned int j = debut; j < segments[i].nb_points; j++) {
                    if (index < NB_POINTS_MAX) {
                        solution.chemin_complet.points[index] = segments[i].points[j];
                        index++;
                    }
                }
            }
            
            solution.chemin_complet.nb_points = index;
        } 
    }

    return solution;
}