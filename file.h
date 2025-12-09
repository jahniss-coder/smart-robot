#ifndef FILE_H
#define FILE_H

# include "dijkstra.h"

#define MAX_FILE 500 // Pour être sûr que jamais on ait autant de points
// Structure pour utiliser la file et regarder par quels points passer
typedef struct{
    EtatDuDijkstra elements[MAX_FILE];   // tableau qui stocke les etats
    int debut;  // indice du premier element de la file
    int fin;    // indice après le dernier element de la file
}File;

/**
   @brief initialisation de la file
   @param f file 
**/
void initialisation_file(File* f);

/**
   @brief va regarder si une file est vide
   @param f file 
   @return 1 si Vrai, 0 sinon 
**/
int estVideFile(File* f);

/**
   @brief va regarder si une file est pleine
   @param f file 
   @return 1 si Vrai, 0 sinon 
**/
int estPleineFile(File* f);

/**
   @brief enfiler l'élement
   @param f file
   @param pD point représenté par les élements de pointDijkstra 
**/
void enfiler(File* f, EtatDuDijkstra pD);

/**
   @brief Défiler le premier élément qui a été ajouté à la file
   @param f file
   @return le point de Dijkstra qui a été défilé 
**/
EtatDuDijkstra defiler(File* f);

#endif
