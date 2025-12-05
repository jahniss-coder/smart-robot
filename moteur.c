#include "moteur.h"
#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <unistd.h>

int moteurs_init(void) {

    // Initialisation de wiringPi
    if (wiringPiSetupGpio() == -1) {
        return -1;
    }

    // GPIO en sortie
    pinMode(MOTEUR_G_IN1, OUTPUT);
    pinMode(MOTEUR_G_IN2, OUTPUT);
    pinMode(MOTEUR_D_IN3, OUTPUT);
    pinMode(MOTEUR_D_IN4, OUTPUT);

    // On arrête tout au début
    moteurs_arreter();
    return 0;
}

int calcul_PWM(int vitesse) {
    return (vitesse * PWM_RANGE) / 100;
}

void moteurs_avancer(void) {
    int pwmValue = calcul_PWM(VITESSE_MOYENNE);

    // Moteur gauche
    digitalWrite(MOTEUR_G_IN1, HIGH);
    digitalWrite(MOTEUR_G_IN2, LOW);
    PwmWrite(MOTEUR_G_PWM, pwmValue);

    // Moteur droit
    digitalWrite(MOTEUR_D_IN3, HIGH);
    digitalWrite(MOTEUR_D_IN4, LOW);
    PwmWrite(MOTEUR_D_PWM, pwmValue);
}

void moteurs_tourner_droite(void) {

    moteurs_arreter();

    int pwmValue = calcul_PWM(VITESSE_VIRAGE);

    // Moteur gauche avance (ralenti)
    digitalWrite(MOTEUR_G_IN1, HIGH);
    digitalWrite(MOTEUR_G_IN2, LOW);
    softPwmWrite(MOTEUR_G_PWM, pwmValue);

    // Moteur droit arrêté
    digitalWrite(MOTEUR_D_IN3, LOW);
    digitalWrite(MOTEUR_D_IN4, LOW);
    softPwmWrite(MOTEUR_D_PWM, 0);
}

void moteurs_tourner_gauche(void) {

    moteurs_arreter();

    int pwmValue = calcul_PWM(VITESSE_VIRAGE);

    // Moteur droit avance (ralenti)
    digitalWrite(MOTEUR_D_IN3, HIGH);
    digitalWrite(MOTEUR_D_IN4, LOW);
    softPwmWrite(MOTEUR_D_PWM, pwmValue);

    // Moteur gauche arrêté
    digitalWrite(MOTEUR_G_IN1, LOW);
    digitalWrite(MOTEUR_G_IN2, LOW);
    softPwmWrite(MOTEUR_G_PWM, 0);
}

void moteurs_arreter(void) {

    // GPIO à LOW
    digitalWrite(MOTEUR_G_IN1, LOW);
    digitalWrite(MOTEUR_G_IN2, LOW);
    digitalWrite(MOTEUR_D_IN3, LOW);
    digitalWrite(MOTEUR_D_IN4, LOW);

    // PWM à 0
    softPwmWrite(MOTEUR_D_PWM, 0);
    softPwmWrite(MOTEUR_G_PWM, 0);
}
