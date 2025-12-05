#include "moteur.h"
#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>


int moteurs_init(void){

// Initialisation de wiringPi
if (wiringPiSetupGpio() == -1) {
    fprintf(stderr, "Erreur: Impossible d'initialiser wiringPi\n");
    // Si l'initialisation n'a pas fonctionné
    return -1;
}

// On met tous les GPIO en OUTPUT
pinMode(MOTEUR_G_IN1, OUTPUT);
pinMode(MOTEUR_G_IN2, OUTPUT);
pinMode(MOTEUR_D_IN3, OUTPUT);
pinMode(MOTEUR_D_IN4, OUTPUT);
    
 // Initialisation du PWM logiciel pour les deux moteurs
if (softPwmCreate(MOTEUR_G_PWM, 0, PWM_RANGE) != 0) {
    fprintf(stderr, "Erreur: Impossible de créer PWM moteur gauche\n");
    // Si on arrive pas à creer le PWM du moteur gauche
    return -1;
}

 if (softPwmCreate(MOTEUR_D_PWM, 0, PWM_RANGE) != 0) {
    fprintf(stderr, "Erreur: Impossible de créer PWM moteur droit\n");
    // Si on arrive pas à creer le PWM du moteur droit
    return -1;
 }
    
// Un fois initialisé, les mpteurs ne roulent pas encore
moteurs_arreter();
    
moteurs_initialises = 1;
printf("Moteurs initialisés avec succès\n");
return 0;
}

int calcul_PWM(int vitesse){

    return (vitesse * 1024) / 100;
}

void moteurs_avancer(void){

    // si le moteur est pas initialisé, erreur
    if (!moteurs_initialises){
        fprint(stderr, "Erreur: moteur non initialisé");
        return;
    }

    // Vérifier que la vitesse est la bonne
    printf("Avancer à vitesse %d%%\n", VITESSE_MOYENNE);
    
    // Calcul de la valeur du PWM
    int pwmValue = calcul_PWM(VITESSE_MOYENNE);

    // Faire avancer le moteur gauche
    digitalWrite(MOTEUR_G_IN1, HIGH);
    digitalWrite(MOTEUR_G_IN2, LOW);
    PwmWrite(MOTEUR_G_PWM, pwmValue);
    
    // Faire avancer le moteur droit
    digitalWrite(MOTEUR_D_IN3, HIGH);
    digitalWrite(MOTEUR_D_IN4, LOW);
    PwmWrite(MOTEUR_D_PWM, pwmValue);
}

void moteurs_tourner_droite(void) {
    // si le moteur est pas initialisé, erreur
    if (!moteurs_initialises) {
        fprintf(stderr, "Erreur: Moteurs non initialisés\n");
        return;
    }
    
    // On ralenti la vitesse dans le virage
    printf("Tourner à droite à vitesse moyenne (%d%%)\n", VITESSE_VIRAGE);
    
    // On s'arrête pour tourner
    moteurs_arreter();
    
    int pwmValue = calcul_PWM(VITESSE_VIRAGE);

    // On avance seulement gauche
    digitalWrite(MOTEUR_G_IN1, HIGH);
    digitalWrite(MOTEUR_G_IN2, LOW);
    PwmWrite(MOTEUR_G_PWM, VITESSE_VIRAGE);
    
    // Le moteur droit ne roule plus
    digitalWrite(MOTEUR_D_IN3, LOW);
    digitalWrite(MOTEUR_D_IN4, LOW);
    softPwmWrite(MOTEUR_D_PWM, 0);
}

void moteurs_tourner_gauche(void) {
    // si le moteur est pas initialisé, erreur
    if (!moteurs_initialises) {
        fprintf(stderr, "Erreur: Moteurs non initialisés\n");
        return;
    }
    
    // On ralenti la vitesse dans le virage
    printf("Tourner à gauche à vitesse moyenne (%d%%)\n", VITESSE_VIRAGE);
    
    // On s'arrête pour tourner
    moteurs_arreter();
    
    int pwmValue = calcul_PWM(VITESSE_VIRAGE);

    // On avance seulement droit
    digitalWrite(MOTEUR_D_IN3, HIGH);
    digitalWrite(MOTEUR_D_IN4, LOW);
    PwmWrite(MOTEUR_D_PWM, VITESSE_VIRAGE);
    
    // Le moteur droit ne roule plus
    digitalWrite(MOTEUR_G_IN1, LOW);
    digitalWrite(MOTEUR_G_IN2, LOW);
    softPwmWrite(MOTEUR_G_PWM, 0);
}

void moteurs_arreter(void){
    // Si le moteur n'a pas été initialisé
    if (!moteurs_initialises) {
        fprintf(stderr, "Erreur: Moteurs non initialisés\n");
        return;
    }

    // Mettre tous les GPIO à LOW
    digitalWrite(MOTEUR_G_IN1, LOW);
    digitalWrite(MOTEUR_G_IN2, LOW);
    digitalWrite(MOTEUR_D_IN3, LOW);
    digitalWrite(MOTEUR_D_IN4, LOW);

    // Mettre tous les PWM à 0
    softPwmWrite(MOTEUR_D_PWM, 0);
    softPwmWrite(MOTEUR_G_PWM, 0);
}