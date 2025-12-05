/** 
Bibliotèque pour le projet
Celle-ci contient l'ensemble des fonctions utiles pour le projet Smart Robot ce qui inclut :
    - moteurs_init: permettant d'initialiser les GPIOs
    - moteurs_clean: permettant d'arreter le moteur et liberer les GPIOs
    - moteurs_avancer:
    - moteurs_reculer:
    - moteurs_arreter:
    - moteurs_tourner_gauche:
    - moteurs_tourner_droite:
    - moteur_rotation_90_gauche:
    - moteur_rotation_90_droite:
    - moteurs_demi_tour:
**/


#ifndef MOTEURS_H
#define MOTEURS_H

/** @brief Vitesse maximale (100%) **/
#define VITESSE_MAX        100

/** @brief Vitesse moyenne **/
#define VITESSE_MOYENNE    50

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
    @brief Arrête les moteurs et libère les GPIOs
    @return 0 si succès, -1 si erreur
**/
void moteurs_clean(void);

/**
    @brief Faire avancer le robot
    @param vitesse Vitesse en pourcentage (entre 0 et 100)
**/
void moteurs_avancer(int vitesse);

/**
    @brief Faire reculer le robot
    @param vitesse Vitesse en pourcentage (entre 0 et 100)
**/
void moteurs_reculer(int vitesse);

/**
    @brief Arrêter tous les moteurs rapidement s'il y a un problème
**/
void moteurs_arreter(void);

/**
    @brief Faire tourner le robot à gauche = moteur gauche qui recule et moteur droit qui avance
    @param vitesse Vitesse de rotation (entre 0 et 100)
**/
void moteurs_tourner_gauche(int vitesse);

/**
    @brief Faire tourner le robot à droite = moteur droite qui recule et moteur gauche qui avance
    @param vitesse Vitesse de rotation (0-100)
**/
void moteurs_tourner_droite(int vitesse);

/**
    @brief Tourner à gauche de 90 degrés (on ne roule pas en tournant donc pas de vitesse)
**/
void moteurs_rotation_90_gauche(void);

/**
    @brief Tourner à droite de 90 degrés (on ne roule pas en tournant donc pas de vitesse)
**/
void moteurs_rotation_90_droite(void);

/**
    @brief Faire un demi tour
**/
void moteurs_demi_tour(void);

#endif 