#include "moteur.h"
#include <softPwm.h>
#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>

#define MOTEUR_G_PWM 12
#define MOTEUR_D_PWM 13
#define MOTEUR_G_IN1 24
#define MOTEUR_G_IN2 25
#define MOTEUR_D_IN3 25
#define MOTEUR_D_IN4 6

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

int calcul_PWM(int vitesse) { return (vitesse * 100) / 100; }

void moteurs_avancer(void) {
  int pwmValue = calcul_PWM(VITESSE_MOYENNE);

  // Moteur gauche
  digitalWrite(MOTEUR_G_IN1, HIGH);
  digitalWrite(MOTEUR_G_IN2, LOW);
  pwmWrite(MOTEUR_G_PWM, pwmValue);

  // Moteur droit
  digitalWrite(MOTEUR_D_IN3, HIGH);
  digitalWrite(MOTEUR_D_IN4, LOW);
  pwmWrite(MOTEUR_D_PWM, pwmValue);
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

int main() {
  printf("--- DEBUT DES TESTS MOTEURS ---\n");

  if (moteurs_init() == -1) {
    return 1; // Quitte si erreur
  }

  // S'assurer que tout est à l'arrêt au début
  moteurs_arreter();
  delay(1000);

  // 1. TEST AVANCER
  printf("1. Avancer (Vitesse Moyenne) pendant 3s\n");
  moteurs_avancer();
  delay(1500);
  moteurs_arreter();
  delay(1000);

  // 2. TEST RECULER
  // printf("2. Reculer (Vitesse Max) pendant 3s\n");
  // moteurs_reculer(VITESSE_MAX);
  // delay(1500);
  // moteurs_arreter();
  // delay(1000);

  // 3. TEST ROTATION GAUCHE
  printf("3. Tourner Droite pendant 1.5s\n");
  moteurs_tourner_droite();
  delay(5000); // Temps nécessaire pour faire 90 degrés (à calibrer IRL)
  moteurs_arreter();
  delay(1000);

  // 4. TEST ROTATION DROITE
  printf("4. Tourner Gauche pendant 1.5s\n");
  moteurs_tourner_gauche();
  delay(5000);
  moteurs_arreter();
  delay(1000);

  // 5. TEST DEMI-TOUR
  // printf("5. Demi-tour\n");
  // moteurs_demi_tour();
  // delay(1000);

  printf("--- FIN DES TESTS ---\n");
  moteurs_arreter();

  return 0;
}