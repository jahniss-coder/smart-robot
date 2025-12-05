/** 
Bibliotèque pour le projet
Celle-ci contient l'ensemble des fonctions utiles pour le projet Smart Robot ce qui inclut :
    - moteurs_init: permettant d'initialiser les GPIOs
    - moteurs_clean: permettant d'arreter le moteur et liberer les GPIOs
    - moteurs_avancer:
    - moteurs_arreter:
    - moteurs_tourner_gauche:
    - moteurs_tourner_droite:
**/


#ifndef MOTEURS_H
#define MOTEURS_H

/** @brief Vitesse maximale (100%) **/
#define VITESSE_MAX        100

/** @brief Vitesse moyenne **/
#define VITESSE_MOYENNE    50

/** @brief Vitesse virage **/
#define VITESSE_VIRAGE   25

/** @brief Vitesse minimale **/
#define VITESSE_MIN        0


/**
  @brief Differents états du moteur
**/
typedef enum {
    MOTEUR_ARRET,      
    MOTEUR_AVANCE,     
    MOTEUR_RECULE,     
    MOTEUR_TOURNE_GAUCHE, 
    MOTEUR_TOURNE_DROITE  
} EtatMoteur;

/**
    @brief Initialise le système de contrôle des moteurs = configuration des GPIO en OUTPUT et des PWM
    @return 0 si succès, -1 si erreur
**/
int moteurs_init(void);

/**
    @brief Faire avancer le robot
    @param vitesse Vitesse en pourcentage (entre 0 et 100)
**/
void moteurs_avancer(void);


/**
    @brief Arrêter tous les moteurs rapidement s'il y a un problème
**/
void moteurs_arreter(void);

/**
    @brief Faire tourner le robot à gauche = moteur gauche qui recule et moteur droit qui avance
**/
void moteurs_tourner_gauche(void);

/**
    @brief Faire tourner le robot à droite = moteur droit qui recule et moteur gauche qui avance
**/
void moteurs_tourner_droite(void);

/**
    @brief Calculer la valeur pour le PWM
    @param vitesse Vitesse du moteur
**/
int calcul_PWM(int vitesse)


#endif 