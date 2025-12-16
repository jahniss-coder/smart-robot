#ifndef __ACTION__
#define __ACTION__

#define NB_POINTS_MAX 200

typedef enum { AVANCER, TOURNER_GAUCHE, TOURNER_DROITE } manoeuvre_type;

// extern int type_couleur;
// extern int type_virage;
// extern int type_intersection;
// extern manoeuvre_type type_manoeuvre;

/**
   @brief faire avancer le robot
   @param file fichier necessaire a la detection de la pastille par le capteur
RGB
   @note le robot avance jusqu'a la detection d'un virage ou d'une intersection
**/
void avancer(int file);

/**
   @brief faire un virage a gauche
   @note effectue le virage a gauche jusqu'à ce que le robot retrouve la ligne
**/
void faireUnVirageAGauche();

/**
   @brief faire un virage a droite
   @note effectue le virage a droite jusqu'à ce que le robot retrouve la ligne
**/
void faireUnVirageADroite();

/**
   @brief retourne le tableau avec les ordres de directions
   @param cheminFichier la liste des instructions stockées dans un fichier texte
   @param nbLigneFichier le nombre de ligne d'un fichier texte
   @return un tableau contenant les instructions que doit suivre le robot
**/
char **retourneTableauDOrdre(char *cheminFichier, int nbLigneFichier);

/**
   @brief retourne le tableau avec les ordres de directions depuis l'entrée standard
   @param nbLigne le nombre d'élément du tableau 
   @return un tableau contenant les instructions que doit suivre le robot
**/
char **lireOrdreDepuisStdin(int *nbLignes)

/**
   @brief controle le robot suivant les ordres de l'entré standard
   @note permet au robot de suivre les instructions placées dans un fichier
texte
**/
void controlerRobotDepuisOrdre();

#endif