/**
 * @file file.c
 * @brief Implémentation des fonctions pour la gestion des files utilisées dans l'algorithme de Dijkstra
 * @author Delacroix-Henrion Mathieu, Diallo Alioune, Malherbe Ylann, Mathieu Ilan, Olivier Neil, Schetrit Jahnis
 * @date 2025-12
 */

#include "file.h"

/**
 * @brief initialiser une file
 * @param f file
 */
void initialisation_file(File* f){
    f->debut = 0;
    f->fin = 0;
}

/**
 * @brief va regarder si une file est vide
 * @param f file
 * @return 1 si Vrai, 0 sinon
 */
int estVideFile(File* f){
    return f->debut == f->fin;
}

/**
 * @brief va regarder si une file est pleine
 * @param f file
 * @return 1 si Vrai, 0 sinon
 */
int estPleineFile(File* f){
    return (f->fin + 1)% MAX_FILE == f->debut;
}

/**
 * @brief enfiler un état du dijkstra dans la file
 * @param f file
 * @param pD état du dijkstra à enfiler
 */
void enfiler(File* f, EtatDuDijkstra pD){
    // On ne peut enfiler que si la file n'est pas pleine
    if (!estPleineFile(f)){
        f->elements[f->fin] = pD;  // Car au départ fin = 0 donc on veut bien ajouer en position 0 en premier
        f->fin = (f->fin + 1) % MAX_FILE;    // On augmente fin qui pointe sur la nouvelle case à enfiler
    }
}

/**
 * @brief libérer la mémoire allouée pour la file
 * @param f file
 */
void liberer_file(File* f){
    free(f);
}

/**
 * @brief defiler l'élement
 * @param f file
 * @return l'état du dijkstra defilé
*/
EtatDuDijkstra defiler(File* f){
    // On ne peut défiler que si la pile n'est pas vide
    if (!estVideFile(f)){
        EtatDuDijkstra etat = f->elements[f->debut];   // On défile le premier élement
        f->debut = (f->debut + 1) % MAX_FILE ;  // On augmente le début car pointe sur la nouvelle première valeur
        // Il faut mettre modulo notre nombre max dans la file pour ne pas avoir de dépassement de tableau et donc revenir à 0 sinon
        return etat;
    }
}
