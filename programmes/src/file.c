#include "file.h"

void initialisation_file(File* f){
    f->debut = 0;
    f->fin = 0;
}

int estVideFile(File* f){
    return f->debut == f->fin;
}

int estPleineFile(File* f){
    return (f->fin + 1)% MAX_FILE == f->debut;
}

void enfiler(File* f, EtatDuDijkstra etat){
    // On ne peut enfiler que si la file n'est pas pleine
    if (!estPleineFile(f)){
        f->elements[f->fin] = etat;  // Car au depart fin = 0 donc on veut bien ajouer en position 0 en premier
        f->fin = (f->fin + 1) % MAX_FILE;    // On augmente fin qui pointe sur la nouvelle case à enfiler
    }
}

EtatDuDijkstra defiler(File* f){
    // On ne peut défiler que si la pile n'est pas vide
    if (!estVideFile(f)){
        EtatDuDijkstra etat = f->elements[f->debut];   // On défile le premier élement
        f->debut = (f->debut + 1) % MAX_FILE ;  // On augmente le début car pointe sur la nouvelle première valeur
        // Il faut mettre modulo notre nombre max dans la file pour ne pas avoir de dépassement de tableau et donc revenir à 0 sinon
        return etat;
    }
}
