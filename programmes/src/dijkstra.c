#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"
#include "graphe.h"
#include "file.h"
#include "ListeChaineeListe.h"


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

Chemin dijkstra(G_Graphe* g, unsigned int depart, unsigned int arrivee) {
    return dijkstra_avec_exclusions(g, depart, arrivee, NULL, 0);
}

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

int chemin_autorise(Chemin c) {
    for (unsigned int i = 0; i < c.nb_points - 2; i++) {
        if (c.points[i] == c.points[i + 2]) {
            return 0;
        }
    }
    return 1;
}

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

Solution resoudre_chemin_plus_court(G_Graphe* g, unsigned int point_obligatoires[3], 
                                     unsigned int depart, unsigned int longueur_ville) {
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
        parcours[0] = 0; // Index de départ
        parcours[1] = permutations[p][0];
        parcours[2] = permutations[p][1];
        parcours[3] = permutations[p][2];
        parcours[4] = 0; // Retour au départ

        unsigned int distance_totale = 0;
        unsigned int estValide = 1;
        Chemin segments[4];

        // CALCUL DES SEGMENTS AVEC EXCLUSION
        for (unsigned int i = 0; i < 4; i++) {
            unsigned int index_debut = parcours[i];
            unsigned int index_fin = parcours[i + 1];
            unsigned int sommet_depart = point_cles[index_debut];
            unsigned int sommet_arrivee = point_cles[index_fin];

            // Déterminer le sommet à exclure qui est dans le segment précédent
            // C'est le point juste avant le point de jonction dans le segment précédent
            unsigned int sommets_a_eviter;
            unsigned int nb_a_eviter = 1; // On retire dans tous les cas un seul point celui à éviter

            if (i > 0) {
                Chemin segment_precedent = segments[i - 1];
                segment_precedent.nb_points = segment_precedent.nb_points - 1; // Indices commencent à 0
                sommets_a_eviter = segment_precedent.points[segment_precedent.nb_points - 1]; // exclure le point de jonction                
            }

            // Calculer le chemin avec exclusions
            segments[i] = dijkstra_avec_exclusions(g, sommet_depart, sommet_arrivee, 
                                                    &sommets_a_eviter, nb_a_eviter);

            // Vérifications
            if (segments[i].nb_points == 0) {
                estValide = 0;
                break;
            }

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

        // Si cette permutation est valide et meilleure
        if (estValide && distance_totale < meilleure_distance) {
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
                        solution.chemin_complet.points[index++] = segments[i].points[j];
                    }
                }
            }
            
            solution.chemin_complet.nb_points = index;
        }
    }

    return solution;
}