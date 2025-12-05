#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define SPEED_LEFT 12
#define FORWARD_LEFT 24
#define BACKWARD_LEFT 25

#define SPEED_RIGHT 13
#define FORWARD_RIGHT 5
#define BACKWARD_RIGHT 6

#define VITESSE_MAX 100
#define VITESSE_MOYENNE 50
#define VITESSE_TOURNEE 20
#define VITESSE_MIN 0

int calcul_PWM(int vitesse) { return (vitesse * 1024) / 100; }

int moteurs_init() {
  if (wiringPiSetupGpio() == -1) {
    printf("Setup Error");
  }

  // Configuration de la vitesse
  pinMode(SPEED_RIGHT, PWM_OUTPUT);
  pinMode(SPEED_LEFT, PWM_OUTPUT);

  // Configuration des roues
  pinMode(FORWARD_LEFT, OUTPUT);
  pinMode(BACKWARD_LEFT, OUTPUT);

  pinMode(FORWARD_RIGHT, OUTPUT);
  pinMode(BACKWARD_RIGHT, OUTPUT);
}

// void moteurs_clean();

void moteurs_avancer(int vitesse) {
  int pwmSpeed = calcul_PWM(vitesse);

  pwmWrite(SPEED_LEFT, pwmSpeed);
  pwmWrite(SPEED_RIGHT, pwmSpeed);

  digitalWrite(FORWARD_LEFT, HIGH);
  digitalWrite(FORWARD_RIGHT, HIGH);

  digitalWrite(BACKWARD_LEFT, LOW);
  digitalWrite(BACKWARD_RIGHT, LOW);
}

void moteurs_reculer(int vitesse) {
  int pwmSpeed = calcul_PWM(vitesse);

  pwmWrite(SPEED_LEFT, pwmSpeed);
  pwmWrite(SPEED_RIGHT, pwmSpeed);

  digitalWrite(FORWARD_LEFT, LOW);
  digitalWrite(FORWARD_RIGHT, LOW);

  digitalWrite(BACKWARD_LEFT, HIGH);
  digitalWrite(BACKWARD_RIGHT, HIGH);
}

void moteurs_arreter() {
  // digitalWrite(SPEED_LEFT, LOW);
  // digitalWrite(SPEED_RIGHT, LOW);

  digitalWrite(FORWARD_LEFT, LOW);
  digitalWrite(FORWARD_RIGHT, LOW);

  digitalWrite(BACKWARD_LEFT, LOW);
  digitalWrite(BACKWARD_RIGHT, LOW);
}

void tournerGauche() {
  digitalWrite(FORWARD_LEFT, LOW);
  digitalWrite(BACKWARD_LEFT, HIGH);

  digitalWrite(FORWARD_RIGHT, HIGH);
  digitalWrite(BACKWARD_RIGHT, LOW);

  // Application de la vitesse pour tourner
  int pwmSpeed = calcul_PWM(VITESSE_MOYENNE);

  pwmWrite(SPEED_LEFT, pwmSpeed);
  pwmWrite(SPEED_RIGHT, pwmSpeed);
}

void tournerDroite() {
  digitalWrite(FORWARD_LEFT, HIGH);
  digitalWrite(BACKWARD_LEFT, LOW);

  digitalWrite(FORWARD_RIGHT, LOW);
  digitalWrite(BACKWARD_RIGHT, HIGH);

  // Application de la vitesse pour tourner
  int pwmSpeed = calcul_PWM(VITESSE_MOYENNE);

  pwmWrite(SPEED_LEFT, pwmSpeed);
  pwmWrite(SPEED_RIGHT, pwmSpeed);
}

void tournerGaucheSansArret() {

  digitalWrite(FORWARD_LEFT, HIGH);
  digitalWrite(BACKWARD_LEFT, LOW);

  digitalWrite(FORWARD_RIGHT, HIGH);
  digitalWrite(BACKWARD_RIGHT, LOW);

  // Application de la vitesse pour tourner
  int pwmSpeedLeft = calcul_PWM(VITESSE_TOURNEE);
  int pwmSpeedRight = calcul_PWM(VITESSE_MAX);

  pwmWrite(SPEED_LEFT, pwmSpeedLeft);
  pwmWrite(SPEED_RIGHT, pwmSpeedRight);
}

void tournerDroiteSansArret() {

  digitalWrite(FORWARD_LEFT, HIGH);
  digitalWrite(BACKWARD_LEFT, LOW);

  digitalWrite(FORWARD_RIGHT, HIGH);
  digitalWrite(BACKWARD_RIGHT, LOW);

  // Application de la vitesse pour tourner
  int pwmSpeedLeft = calcul_PWM(VITESSE_MAX);
  int pwmSpeedRight = calcul_PWM(VITESSE_TOURNEE);

  pwmWrite(SPEED_LEFT, pwmSpeedLeft);
  pwmWrite(SPEED_RIGHT, pwmSpeedRight);
}

void moteurs_demi_tour() {
  tournerGauche();
  tournerGauche();
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
  // printf("1. Avancer (Vitesse Moyenne) pendant 3s\n");
  // moteurs_avancer(VITESSE_MOYENNE);
  // delay(1500);
  // moteurs_arreter();
  // delay(1000);

  // 2. TEST RECULER
  // printf("2. Reculer (Vitesse Max) pendant 3s\n");
  // moteurs_reculer(VITESSE_MAX);
  // delay(1500);
  // moteurs_arreter();
  // delay(1000);

  // 3. TEST ROTATION GAUCHE
  printf("3. Tourner Droite pendant 1.5s\n");
  tournerDroiteSansArret();
  delay(1500); // Temps nécessaire pour faire 90 degrés (à calibrer IRL)
  moteurs_arreter();
  delay(1000);

  // 4. TEST ROTATION DROITE
  printf("4. Tourner Gauche pendant 1.5s\n");
  tournerGaucheSansArret();
  delay(1500);
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