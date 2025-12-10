#include "dijkstra.h"
#include "file.h"
#include <stdio.h>
#include <stdlib.h>

Chemin dijkstra(Graphe* g, int depart, int arrivee){
    // BUT: explore les voisins directs, puis les voisins des voisins...
    // Trouver le plus court chemin du point de départ au point d'arrivée


    // Le resultat que l'on souhaite est un chemin, pas encore le chemin final
    // Initiliasiation du chemin que l'on va renvoyer de toute la structure à 0
    // SI on trouve aucun chemin (normalement pas possible), nb_points restera à 0
    Chemin resultat = {0};
    
    // Comme on a un carre, on va faire un tableau pour noter les points déja visités
    //points_visites[point_actuel][point_precedent]
    // On met +1 pour ajouter une ligne et colonne si on a pas de predecesseur
    int points_visites[NB_POINTS_MAX + 1][NB_POINTS_MAX + 1];
    // ligne i: point précédent
    // colonne j: point 

    // On initialise tout a 0 et vaudra 1 quand visité
    // Utilisation de la table 2D car si on est à 2 en venant de 1, on ne pourra pas noté qu'on est à 2 en venant de 3
    // On s'arrange pour ne pas faire de demi-tour
    for(int i = 0; i<= NB_POINTS_MAX; i++){
        for(int j = 0; j<= NB_POINTS_MAX; j++){
            points_visites[i][j] = 0;
        }
    }

    // On crée notre file pour faire le parcours
    File* file;
    // initialisation de la file
    initialisation_file(&file);

    // état initial du Dijkstra
    EtatDuDijkstra initial;
    initial.point_actuel = depart;     // On commence bien sur le point de départ du robot
    initial.point_precedent = -1;  // On a pas de point précédent au départ
    initial.chemin[0] = depart;    // Le premier point du chemin que l'on va faire est le point de départ
    initial.nb_points = 1;    // Au depart, on a pas avancé de case
    enfiler(&file, initial);    //On enfile l'état initial du Dijkstra
    
    // On met à jour pour la situation initiale
    // On informe que l'on a visité la case départ puisque l'on est dessus
    // L'indice 0 indique qu'il n'y a pas de predecesseur 
    points_visites[depart][0] = 1;

    // Boucle principale du dijkstra
    while(!estVideFile(&file)){
        // Tant qu'on a pas vidé toute la file, on récupère l'etat de la pile qu'on defile
        // L'etat recupéré sera la chemoin que l'on est en train d'explorer
        EtatDuDijkstra etat = defiler(&file);

        // Vérification si on est arrivé à l'endroit que l'on voulait
        if (etat.point_actuel == arrivee){
            // Si le point sur lequel on est correspond au point d'arrivée
            // Le nombre de point de ce chemin prend le nombre de point du Dijkstra que l'on était en train de faire
            resultat.nb_points = etat.nb_points;
            for(int i = 0; i < etat.nb_points; i++){
                // On va copier tous les points par lesquels il faut passer
                resultat.points[i] = etat.chemin[i];
            }
            // On retourne le resultat = le plus court chemin du départ à l'arrivée
            return resultat;
        }
        // Si on est pas à l'arrivée, alors on recupère l'adresse du noeud acutel ou l'on se trouve
        Noeud* noeud = &g->noeuds[etat.point_actuel];

        // On parcrout tous les voisins du point actuel (tous les voisins du noeud )
        for(int i = 0; i < noeud->nb_voisins; i++){
            // On recupère le numéro du point voisin
            int voisin = noeud->voisin[i];
            // Si le voisin que l'on a correspond au noeud dont on regarde les voisins, alors on passe car correspond au demi-tour
            if(voisin == etat.point_precedent){
                continue;
            }
            // operateur ternaire: CONDITION ? VALEUR_SI_VRAI : VALEUR_SI_FAUX
            // Si le point actuel est -1 (impossible), alors on lui met la valeur 0, sinon, il garde sa valeur car ok
            // BUT: Verifier que l'ona pas de valeurs negatives car pas possible
            int index_precedent = (etat.point_actuel == -1) ? 0 : etat.point_actuel;
            
            // Si on a deja visit le voidin en venant de point_actuerl, on ne retourne pas explorer car déjà fait
            // Concretement, ca veut dire qu'on a deja trouvé un chemin plus court pout arriver à ce voisin la
            // Si le voisin à déja été accédé par le point actuel, on continue et passe 
            if(points_visites[voisin][index_precedent]){
                continue;
            }
            
            points_visites[voisin][index_precedent] = 1;

            // On va creer un nouvel etat pour le voisin que l'on veut explorer
            // Le poitn actuel devient le voisin qu'on explore
            // Le point precedent devient donc le point d'ou on vient (le pont actuel dans etat)
            // Il faut incrementer le nombre de points car maintenant, on est chez le voisi,
            EtatDuDijkstra nouvel_etat;
            nouvel_etat.point_actuel = voisin;
            nouvel_etat.point_precedent = etat.point_actuel;
            nouvel_etat.nb_points = etat.nb_points + 1;

            // On va copier le chemin actuel dans le nouvel etat et donc ajouter le voisin a la fin du chemin puisque l'on est chez lui
            for(int j = 0; j < etat.nb_points; j++){
                nouvel_etat.chemin[i] = etat.chemin[i];
            }
            nouvel_etat.chemin[etat.nb_points] = voisin;

            // On va alors enfiler le nouvel état pour l'explorer plus tard
            //On va ensuite continuer avec les autres voisins ce qu'on vient de faire
            enfiler(&file, nouvel_etat);
            // La boucle va continuer lorsque tous les voisins seront traités et donc le while reprend et defile le prochain etat de la file
        }
    }
    // Si jamais, JAMAIS on trouve aucun chemin (normalzmnt pas possible)
    // Mais ca voudrait dire qu'il uy a 0 chemin entre le départ et l'arrivée donc bizarre
    return resultat;
}

void permutation(int arr[3], int permutations[6][3]){
    // On rempli toutes les possibilités dans l'ORDRE que l'on peut avoir
                        // i = 0   // i = 1
    int perm[6][3] = { {0, 1, 2}, {0, 2, 1}, // j = 0
                        {1, 0, 2}, {1, 2, 0},  // j = 1
                        {2, 0, 1}, {2, 1, 0}};  // j = 2

    // BUT:
    // Si les trois points obligatoires sont: "13, 22, 20"
    // si i = 0 et j = 0 alors perm[0][0] = {0, 1, 2}
    // et donc on aura dans l'ordre: 18, 22, 20 = arr[0], arr[1], arr[2]
    // si i = 1 et j = 2 alors perm[1][2] = {2, 1, 0}
    // et donc on aura dans l'ordre: 20, 22, 18 = arr[2], arr[1], arr[0]
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 3; j++){
            permutations[i][j] = arr[perm[i][j]];
        }
    }
}

Solution resoudre_chemin_plus_court(Graphe* g, int point_obligatoires[3], int depart, int longueur_ville){
    // Au depart, on initilialise la solution à 0
    Solution solution = {0};
    solution.longueur_chemin_complet = 0;

    // Pour pouvoir comparer les distances
    int meilleure_distance = 99999;

    // On va stocker les points clés: départ + Points oblgatoires
    int point_cles[4];
    point_cles[0] = depart;
    for(int i = 1; i < 4; i++){
        point_cles[i] = point_obligatoires[i - 1];
    }

    // On va calculer les distances entre les points cles
    // On a 4 points obligatoires et on veut un tableau 2D pour noté la distance qu'il y a entre eux 
    // A l'issu de cela, on aura le chemin de A->B, A->C, A->D, B->A, B->C...
     printf("Calcul des plus courts chemins...\n"); 
    chemin distance[4][4];
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; i++){
            // On ne peut pas être sur le point 6 en venant du point 6 donc on exclu le cas i = J
            if(i != j){
                distance[i][j] = dijkstra(g, point_cles[i], point_cles[j]);
                // on a forcément un point(le pemier du parcours)
                if(distance[i][j].nb_points>0){
                    // Affichage des deux points qu'on relie + les points par lesquels on passe + la distance 
                    int distance_temp = distance[i][j].nb_points - 1;
                    printf("%d -> %d :", points_cles[i], point_cles[j]);
                    for(int k = 0; k < distance[i][j].nb_points - 1; k++){
                        printf("%d", distance[i][j].chemin[k]);
                        if(k < distance[i][j].nb_points){
                            printf("->");
                        }
                    }
                    printf("\n");
                    printf("nombre de pas :%d", distance_temp);
                }
                else{
                    // On verifie pour trouver l'erreur au cas ou
                    printf("Chemin impossible entre les points %d et %d",points_cles[i], point_cles[j]);
                }  
            }
        }
    }
    // On va tester les 6 possibilités pour les chemins 
    // On crée une liste avec les positions que peuvent prendre les points obligatoires
    int indices_classement[3] = {1, 2, 3};
    int permutations[6][3];
    permutation(indices_classement, permutations);
    
    // On teste les 6 possibilités
    for(int p= 0; p < 6; p++){
        // On a 4 points donc 5 parcours
        int parcours[5];
        parcours[0] = depart;
        parcours[1] = permutations[p][0];
        parcours[2] = permutations[p][1];
        parcours[3] = permutations[p][2];
        parcours[4] = depart;   // Car il faur revenir sur la case départ

        // Affichage pour vérifier 
        printf("permutation %d: %d -> %d -> %d -> %d -> %d\n", p+1, parcours[0], parcours[1], parcours[2], parcours[3], parcours[4]);

        // Calcul de la distance totale
        int distance_totale = 0;
        int estValide = 1;  // Utilisation comme Booleen

        for(int i = 0; i < 4; i++){
            int debut_parcours_temp = parcours[i];
            int fin_parcours_temp = parcours[i + 1];
            if(distance[debut_parcours_temp][fin_parcours_temp].nb_points == 0){
            // On est dans le cas ou c'est pas possible de relier deux points entre eux
                printf("Les deux points %d et %d ne peuvent pas être reliés entre eux\n", debut_parcours_temp, fin_parcours_temp);
                // Alors la solution pour ce chemin n'est pas valide 
                estValide = 0;
                break;
            }
            int distance_entre_segments = distance[debut_parcours_temp][fin_parcours_temp].nb_points - 1;
            distance_totale = distance_totale + distance_entre_segments;

            // SI ce n'est pas valide = points qui ne peuvent pas être reliéés ensembles
            if(!estValide){
                printf("Chemin impossible");
                continue;
            }

            // Chercher la meilleure solution
            if(distance_totale < meilleure_distance){
                // Si la distance ets plus petite que la meilleure enregistré, on enregistre la nouvelle
                // On sauvegarde l'ordre pour lequel on a trouvé le meilleur chemin
                meilleure_distance = distance_totale;

                for(int i = 0; i < 3; i++){
                    solution.chemin[i] = point_cles[parcours[i + 1]];
                }

                int index = 0;

                for(int i = 0; i < 4; i++){
                    int debut_parcours_temp = parcours[i];
                    int fin_parcours_temp = parcours[i + 1];
                    Chemin* segment = &distance[debut_parcours_temp][fin_parcours_temp];

                    int debut = (i == 0)? 0: 1;

                    for(int j = debut; j < segment->nb_points; j++){
                        solution.chemin_complet[index++] = segment->points[j];
                    }
                }
                
               solution.longueur_chemin_complet = index; 

            }
        }
    }

    return solution;
}