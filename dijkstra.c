#include "dijkstra.h"
#include "file.h"

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
    int points_visites[NB_POINTS_MAX + 1][NB_POINTS_MAX + 1]
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
    File file;
    // initialisation de la file
    initialisation_file(&file);

    // état initial du Dijkstra
    EtatDuDijkstra initial;
    initial.point_actuel = depart;     // On commence bien sur le point de départ du robot
    initial.point_precedent = -1;  // On a pas de point précédent au départ
    initial.chemin[0] = depart;    // Le premier point du chemin que l'on va faire est le point de départ
    initial.nb_points = 1    // Au depart, on a pas avancé de case
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
            return resultat
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
            if(points_visites[voisin][index_precedent] = 1){
                continue;
            }

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

