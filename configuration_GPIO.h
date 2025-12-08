/** 
Bibliotèque pour le projet
Celle-ci contient l'ensemble des fonctions utiles pour le projet Smart Robot ce qui inclut :
    - L'initalisation des modes des GPIO
    - L'initialisation des GPIO

**/

#ifndef __GPIO__
#define __GPIO__

// Moteur
#define MOTEUR_G_PWM 12
#define MOTEUR_D_PWM 13
#define MOTEUR_G_IN1 24
#define MOTEUR_G_IN2 25
#define MOTEUR_D_IN3 5
#define MOTEUR_D_IN4 6
// Capteurs suiveurs lignes
#define SUIVEUR_Gauche 27
#define SUIVEUR_Droit 26
#define SUIVEUR_Centre_G 16
#define SUIVEUR_Centre_D 4
// Capteur couleur 
//#define COULEUR_ ?
//#define COULEUR_ ?
// Buzzeur
//#define BUZZER ?
// LCD
#define LCD_DATA 2
#define LCD_CLOCL 3

/**
    @brief Initialiser le Mode des GPIO (OUTPUT ou INPUT)
**/
void GPIO_configurerModeGpio();

/**
    @brief Initialise les GPIO
    @return 0 si succès, -1 si erreur
**/
int GPIO_initialiserGpio();

#endif