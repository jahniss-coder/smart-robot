/**
Bibliotèque pour le projet
Celle-ci contient l'ensemble des fonctions utiles pour le projet Smart Robot ce
qui inclut :
    - moteurs_avancer:
    - moteurs_reculer:
    - moteurs_arreter:
    - tournerGauche:
    - tournerDroite:
    - tournerGaucheSansArret:
    - tournerDroiteSansArret:
    - moteur_demi_tour:
    - tourner:
    - calcul_PWM:
**/

#ifndef MOTEURS_H
#define MOTEURS_H
#include "configuration_GPIO.h"

/** @brief Vitesse maximale (100%) **/
#define VITESSE_MAX 100

/** @brief Vitesse moyenne **/
#define VITESSE_MOYENNE 70

/** @brief Vitesse virage **/
#define VITESSE_VIRAGE 65

/** @brief Vitesse minimale **/
#define VITESSE_MIN 35

/** @brief Temps nécessaire pour tourner de 90° **/
#define TEMPS_90_DEGRES 1500

/** @brief Temps nécessaire pour tourner de 180° **/
#define TEMPS_180_DEGRES 3000

/**
    @brief Calculer la valeur pour le PWM
    @param vitesse Vitesse du moteur
    @return la vitesse PWM
**/
int calcul_PWM(int vitesse);

/**
    @brief Faire avancer le robot
**/
void moteurs_avancer();

/**
    @brief Faire reculer le robot
**/
void moteurs_reculer();

/**
    @brief Arrêter tous les moteurs
**/
void moteurs_arreter();

/**
    @brief Faire tourner le robot à gauche sans avancer
**/
void tournerGauche();

/**
    @brief Faire tourner le robot à droite sans avancer
**/
void tournerDroite();

/**
    @brief Faire tourner le robot à gauche sans s'arrêter
**/
void tournerGaucheSansArret();

/**
    @brief Faire tourner le robot à droite sans s'arrêter
**/
void tournerDroiteSansArret();

/**
    @brief Faire un demi tour gauche
**/
void moteurs_demi_tour();

/**
    @brief Tourner de 90° après calibrage
    @param sens sens dans lequel on veut tourner (1: droite, -1: gauche)
**/
void tourner(int sens);

#endif