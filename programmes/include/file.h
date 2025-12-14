#ifndef FILE_H
#define FILE_H

# include "graphe_dijkstra.h"

#define MAX_FILE 500 // Pour être sûr que jamais on ait autant de points
// Structure pour utiliser la file et regarder par quels points passer
typedef struct{
    EtatDuDijkstra elements[MAX_FILE];   // tableau qui stocke les etats
    int debut;  // indice du premier element de la file
    int fin;    // indice après le dernier element de la file
}File;

/**
 * @brief initialiser une file
 * @param f file 
 */
void initialisation_file(File* f);

/**
 * @brief va regarder si une file est vide
 * @param f file 
 * @return 1 si Vrai, 0 sinon 
 */
int estVideFile(File* f);

/**
 * @brief va regarder si une file est pleine
 * @param f file 
 * @return 1 si Vrai, 0 sinon 
 */
int estPleineFile(File* f);

/**
 * @brief enfiler un état du dijkstra dans la file
 * @param f file 
 * @param pD état du dijkstra à enfiler
 */
void enfiler(File* f, EtatDuDijkstra pD);

/**
 * @brief libérer la mémoire allouée pour la file
 * @param f file
 */
void liberer_file(File* f);

/**
 * @brief defiler l'élement
 * @param f file 
 * @return l'état du dijkstra defilé
*/
EtatDuDijkstra defiler(File* f);



#endif
