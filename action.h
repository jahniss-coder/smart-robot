#ifndef __ACTION__
#define __ACTION__

#define AVANCER "avancer"
#define TOURNER_GAUCHE "virage g"
#define TOURNER_DROITE "virage d"

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
   @brief controle le robot suivant les ordres du fichier
   @param cheminFichier la liste des instructions stockées dans un fichier texte
   @param nbLigneFichier le nombre de ligne d'un fichier texte
   @note permet au robot de suivre les instructions placées dans un fichier
texte
**/
void controlerRobotDepuisOrdre(char *cheminFichier, int nbLigneFichier);

#endif