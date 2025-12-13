#include "dijkstra.h"
#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"

Chemin dijkstra(G_Graphe* g, unsigned int depart, unsigned int arrivee) {
    // BUT: explore les voisins directs, puis les voisins des voisins...
    // Trouver le plus court chemin du point de départ au point d'arrivée
    // Le resultat que l'on souhaite est un chemin, pas encore le chemin final
    // Initiliasiation du chemin que l'on va renvoyer de toute la structure à 0
    // SI on trouve aucun chemin (normalement pas possible), nb_points restera à 0
    Chemin resultat = {0};

    // Comme on a un carre, on va faire un tableau pour noter les points déja visités
    //points_visites[point_actuel][point_precedent]
    // On met +1 pour ajouter une ligne et colonne si on a pas de predecesseur
    unsigned int points_visites[NB_POINTS_MAX][NB_POINTS_MAX];
    // ligne i: point précédent
    // colonne j: point
    // On initialise tout a 0 et vaudra 1 quand visité
    // Utilisation de la table 2D car si on est à 2 en venant de 1, on ne pourra pas noté qu'on est à 2 en venant de 3
    // On s'arrange pour ne pas faire de demi-tour
    for (unsigned int i = 0; i < NB_POINTS_MAX; i++) {
        for(unsigned int j = 0; j < NB_POINTS_MAX; j++) {
            points_visites[i][j] = 0;
        }
    }


    // On crée notre file pour faire le parcours
    File* file = malloc(sizeof(File)); // Ne pas oublier d'allouer la mémoire à la file
    // initialisation de la file
    initialisation_file(file);

    // état initial du Dijkstra
    EtatDuDijkstra initial;
    initial.point_actuel = depart;     // On commence bien sur le point de départ du robot
    initial.point_precedent = 0;  // On a pas de point précédent au départ (-1 indique pas de précédent)
    initial.chemin.points[0] = depart;    // Le premier point du chemin que l'on va faire est le point de départ
    initial.chemin.nb_points = 1;    // Au depart, on a pas avancé de case
    enfiler(file, initial);    //On enfile l'état initial du Dijkstra

    // On met à jour pour la situation initiale
    // On informe que l'on a visité la case départ puisque l'on est dessus
    // L'indice 0 indique qu'il n'y a pas de predecesseur
    points_visites[depart][0] = 1;
    // Boucle principale du dijkstra
    while (!estVideFile(file)) {
        // Tant qu'on a pas vidé toute la file, on récupère l'etat de la pile qu'on defile
        // L'etat recupéré sera la chemin que l'on est en train d'explorer

        EtatDuDijkstra etat = defiler(file);
        // Vérification si on est arrivé à l'endroit que l'on voulait
        if (etat.point_actuel == arrivee) {
            // Si le point sur lequel on est correspond au point d'arrivée
            // Le nombre de point de ce chemin prend le nombre de point du Dijkstra que l'on était en train de faire
            resultat.nb_points = etat.chemin.nb_points;
            for (unsigned int i = 0; i < etat.chemin.nb_points; i++) {
                // On va copier tous les points par lesquels il faut passer
                resultat.points[i] = etat.chemin.points[i];
            }
            // On retourne le resultat = le plus court chemin du départ à l'arrivée
            liberer_file(file);
            return resultat;
        }
        // Si on est pas à l'arrivée, alors on recupère l'adresse du noeud actuel ou l'on se trouve
        LCL_Liste voisins = G_obtenirSommetsAdjacents(*g, etat.point_actuel);
        // On parcourt tous les voisins du point actuel (tous les voisins du noeud )
        for (unsigned int i = 0; i < LCL_longueur(voisins); i++) {
            unsigned int voisin =  *(unsigned int *) LCL_element(voisins,i);
            // Si le voisin que l'on a correspond au noeud dont on regarde les voisins, alors on passe car correspond au demi-tour
            if (voisin == etat.point_precedent) {
                continue;
            }
            // operateur ternaire: CONDITION ? VALEUR_SI_VRAI : VALEUR_SI_FAUX
            // Si le point actuel est -1 (impossible), alors on lui met la valeur 0, sinon, il garde sa valeur car ok
            // BUT: Verifier que l'on a pas de valeurs negatives car pas possible
            unsigned int index_precedent = (etat.point_actuel == (unsigned int)-1) ? 0 : etat.point_actuel;

            // Si on a deja visité le voisin en venant de point_actuel, on ne retourne pas explorer car déjà fait
            // Concrètement, ça veut dire qu'on a déjà trouvé un chemin plus court pour arriver à ce voisin là
            // Si le voisin a déjà été accédé par le point actuel, on continue et passe
            if (points_visites[voisin][index_precedent]) {
                continue;
            }

            points_visites[voisin][index_precedent] = 1;
            // On va créer un nouvel état pour le voisin que l'on veut explorer
            // Le point actuel devient le voisin qu'on explore
            // Le point précédent devient donc le point d'où on vient (le point actuel dans etat)
            // Il faut incrémenter le nombre de points car maintenant, on est chez le voisin,
            EtatDuDijkstra nouvel_etat;
            nouvel_etat.point_actuel = voisin;
            nouvel_etat.point_precedent = etat.point_actuel;
            nouvel_etat.chemin.nb_points = etat.chemin.nb_points + 1;
            // On va copier le chemin actuel dans le nouvel état et donc ajouter le voisin à la fin du chemin puisque l'on est chez lui
            for (unsigned int j = 0; j < etat.chemin.nb_points; j++) {
                nouvel_etat.chemin.points[j] = etat.chemin.points[j];
            }
            nouvel_etat.chemin.points[etat.chemin.nb_points] = voisin;
            // On va alors enfiler le nouvel état pour l'explorer plus tard
            //On va ensuite continuer avec les autres voisins ce qu'on vient de faire
            enfiler(file, nouvel_etat);
            // La boucle va continuer lorsque tous les voisins seront traités et donc le while reprend et défile le prochain état de la file
        }
        LCL_vider(&voisins);
    }
    liberer_file(file); 
    // Si jamais, JAMAIS on trouve aucun chemin (normalement pas possible)
    // Mais ça voudrait dire qu'il y a 0 chemin entre le départ et l'arrivée donc bizarre

    liberer_file(file);
    return resultat;
}

void permutation(unsigned int arr[3], unsigned int permutations[6][3]) {
    // On remplit toutes les possibilités dans l'ORDRE que l'on peut avoir
                        // i = 0   // i = 1
    unsigned int perm[6][3] = { {0, 1, 2}, {0, 2, 1}, // j = 0
                        {1, 0, 2}, {1, 2, 0},  // j = 1
                        {2, 0, 1}, {2, 1, 0}};  // j = 2
    // BUT:
    // Si les trois points obligatoires sont: "13, 22, 20"
    // si i = 0 et j = 0 alors perm[0][0] = {0, 1, 2}
    // et donc on aura dans l'ordre: 18, 22, 20 = arr[0], arr[1], arr[2]
    // si i = 1 et j = 2 alors perm[1][2] = {2, 1, 0}
    // et donc on aura dans l'ordre: 20, 22, 18 = arr[2], arr[1], arr[0]
    for(unsigned int i = 0; i < 6; i++) {
        for(unsigned int j = 0; j < 3; j++) {
            permutations[i][j] = arr[perm[i][j]];
        }
    }
}

// ✅ FONCTION CORRIGÉE : Vérifie qu'il n'y a pas de demi-tour DANS un segment
int chemin_autorise(Chemin c) {
    for (unsigned int i = 0; i < c.nb_points - 2; i++) {
        if (c.points[i] == c.points[i + 2]) {
            printf("❌ Demi-tour détecté dans segment : %u -> %u -> %u\n", 
                   c.points[i], c.points[i+1], c.points[i+2]);
            return 0;
        }
    }
    return 1;
}

// ✅ NOUVELLE FONCTION : Vérifie les demi-tours ENTRE segments
int verifier_jonction_segments(Chemin segment1, Chemin segment2) {
    // Vérifier qu'on ne fait pas demi-tour entre deux segments
    // Cas problématique : [..., A, B] puis [B, A, ...]
    if (segment1.nb_points >= 2 && segment2.nb_points >= 2) {
        unsigned int avant_dernier_seg1 = segment1.points[segment1.nb_points - 2];
        unsigned int premier_seg2 = segment2.points[0];
        unsigned int deuxieme_seg2 = segment2.points[1];
        
        // Si l'avant-dernier point du segment1 = deuxième point du segment2
        // Cela crée un demi-tour : A -> B -> A
        if (avant_dernier_seg1 == deuxieme_seg2) {
            printf("❌ Demi-tour entre segments : ...%u -> %u (fin seg1) puis %u -> %u... (début seg2)\n",
                   avant_dernier_seg1, premier_seg2, premier_seg2, deuxieme_seg2);
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

    printf("Points clés : %u, %u, %u, %u\n", point_cles[0], point_cles[1], point_cles[2], point_cles[3]);

    // Précalculer tous les chemins entre points clés
    Chemin distances[4][4];
    for(unsigned int i = 0; i < 4; i++) {
        for(unsigned int j = 0; j < 4; j++) {
            if(i != j) {
                distances[i][j] = dijkstra(g, point_cles[i], point_cles[j]);
                printf("Chemin [%u->%u] : longueur = %u\n", 
                       point_cles[i], point_cles[j], distances[i][j].nb_points);
                for (unsigned int k = 0; k < distances[i][j].nb_points; k++) {
                    printf("%u ", distances[i][j].points[k]);
                }
                printf("\n");
            }
        }
    }

    unsigned int indices_classement[3] = {1, 2, 3};
    unsigned int permutations[6][3];
    permutation(indices_classement, permutations);

    // Tester chaque permutation
    for (unsigned int p = 0; p < 6; p++) {
        printf("\n=== Test permutation %u ===\n", p);
        
        unsigned int parcours[5];
        parcours[0] = 0;
        parcours[1] = permutations[p][0];
        parcours[2] = permutations[p][1];
        parcours[3] = permutations[p][2];
        parcours[4] = 0;
        
        printf("Ordre : %u -> %u -> %u -> %u -> %u\n",
               point_cles[parcours[0]], point_cles[parcours[1]], 
               point_cles[parcours[2]], point_cles[parcours[3]], 
               point_cles[parcours[4]]);

        unsigned int distance_totale = 0;
        unsigned int estValide = 1;

        // ✅ VÉRIFICATION 1 : Tous les segments existent et pas de demi-tour INTERNE
        Chemin segments[4];
        for (unsigned int i = 0; i < 4; i++) {
            unsigned int index_debut = parcours[i];
            unsigned int index_fin = parcours[i + 1];
            segments[i] = distances[index_debut][index_fin];

            if (segments[i].nb_points == 0) {
                printf("❌ Pas de chemin entre %u et %u\n", 
                       point_cles[index_debut], point_cles[index_fin]);
                estValide = 0;
                break;
            }

            if (!chemin_autorise(segments[i])) {
                estValide = 0;
                break;
            }

            distance_totale += (segments[i].nb_points - 1);
        }

        // ✅ VÉRIFICATION 2 : Pas de demi-tour ENTRE segments
        if (estValide) {
            for (unsigned int i = 0; i < 3; i++) {
                if (!verifier_jonction_segments(segments[i], segments[i + 1])) {
                    printf("❌ Jonction invalide entre segment %u et %u\n", i, i+1);
                    estValide = 0;
                    break;
                }
            }
        }

        // ✅ Si cette permutation est valide et meilleure
        if (estValide && distance_totale < meilleure_distance) {
            printf("✅ Meilleur chemin trouvé ! Distance = %u\n", distance_totale);
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

    printf("\n=== SOLUTION FINALE ===\n");
    printf("Distance totale : %u\n", meilleure_distance);
    printf("Ordre des points obligatoires : %u, %u, %u\n", 
           solution.ordre[0], solution.ordre[1], solution.ordre[2]);
    printf("Chemin complet (%u points) : ", solution.chemin_complet.nb_points);
    for (unsigned int i = 0; i < solution.chemin_complet.nb_points; i++) {
        printf("%u", solution.chemin_complet.points[i]);
        if (i < solution.chemin_complet.nb_points - 1) printf(" -> ");
    }
    printf("\n");

    return solution;
}

