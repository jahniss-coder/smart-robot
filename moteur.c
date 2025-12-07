#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "moteur.h"

int calcul_PWM(int vitesse) { return (vitesse * 1024) / 100; }

void moteurs_avancer() {
  int pwmSpeed = calcul_PWM(VITESSE_MOYENNE);

  pwmWrite(MOTEUR_G_PWM, pwmSpeed);
  pwmWrite(MOTEUR_D_PWM, pwmSpeed);

  digitalWrite(MOTEUR_G_IN1, HIGH);
  digitalWrite(MOTEUR_D_IN3, HIGH);

  digitalWrite(MOTEUR_G_IN2, LOW);
  digitalWrite(MOTEUR_D_IN4, LOW);
}

void moteurs_reculer() {
  int pwmSpeed = calcul_PWM(VITESSE_MOYENNE);

  pwmWrite(MOTEUR_G_PWM, pwmSpeed);
  pwmWrite(MOTEUR_D_PWM, pwmSpeed);

  digitalWrite(MOTEUR_G_IN1, LOW);
  digitalWrite(MOTEUR_D_IN3, LOW);

  digitalWrite(MOTEUR_G_IN2, HIGH);
  digitalWrite(MOTEUR_D_IN4, HIGH);
}

void moteurs_arreter() {
  digitalWrite(MOTEUR_G_PWM, 0);
  digitalWrite(MOTEUR_D_PWM, 0);

  digitalWrite(MOTEUR_G_IN1, LOW);
  digitalWrite(MOTEUR_D_IN3, LOW);

  digitalWrite(MOTEUR_G_IN2, LOW);
  digitalWrite(MOTEUR_D_IN4, LOW);
}

void tournerGauche() {
  digitalWrite(MOTEUR_G_IN1, LOW);
  digitalWrite(MOTEUR_G_IN2, HIGH);

  digitalWrite(MOTEUR_D_IN3, HIGH);
  digitalWrite(MOTEUR_D_IN4, LOW);

  // Application de la vitesse pour tourner
  int pwmSpeed = calcul_PWM(VITESSE_MOYENNE);

  pwmWrite(MOTEUR_G_PWM, pwmSpeed);
  pwmWrite(MOTEUR_D_PWM, pwmSpeed);
}

void tournerDroite() {
  digitalWrite(MOTEUR_G_IN1, HIGH);
  digitalWrite(MOTEUR_G_IN2, LOW);

  digitalWrite(MOTEUR_D_IN3, LOW);
  digitalWrite(MOTEUR_D_IN4, HIGH);

  // Application de la vitesse pour tourner
  int pwmSpeed = calcul_PWM(VITESSE_MOYENNE);

  pwmWrite(MOTEUR_G_PWM, pwmSpeed);
  pwmWrite(MOTEUR_D_PWM, pwmSpeed);
}

void tournerGaucheSansArret() {

  digitalWrite(MOTEUR_G_IN1, HIGH);
  digitalWrite(MOTEUR_G_IN2, LOW);

  digitalWrite(MOTEUR_D_IN3, HIGH);
  digitalWrite(MOTEUR_D_IN4, LOW);

  // Application de la vitesse pour tourner
  int pwmSpeedLeft = calcul_PWM(VITESSE_VIRAGE);
  int pwmSpeedRight = calcul_PWM(VITESSE_MAX);

  pwmWrite(MOTEUR_G_PWM, pwmSpeedLeft);
  pwmWrite(MOTEUR_D_PWM, pwmSpeedRight);
}

void tournerDroiteSansArret() {

  digitalWrite(MOTEUR_G_IN1, HIGH);
  digitalWrite(MOTEUR_G_IN2, LOW);

  digitalWrite(MOTEUR_D_IN3, HIGH);
  digitalWrite(MOTEUR_D_IN4, LOW);

  // Application de la vitesse pour tourner
  int pwmSpeedLeft = calcul_PWM(VITESSE_MAX);
  int pwmSpeedRight = calcul_PWM(VITESSE_VIRAGE);

  pwmWrite(MOTEUR_G_PWM, pwmSpeedLeft);
  pwmWrite(MOTEUR_D_PWM, pwmSpeedRight);
}

void moteurs_demi_tour() {
  moteurs_arreter();
  tournerGauche();
  delay(TEMPS_180_DEGRES);  // Temps pour 180°, à calibrer
  moteurs_arreter();
}

// Quand on aura calibré le temps pour la rotation de 90°
void tourner(int sens) {
  // sens: 1=droite, -1=gauche
  if (sens > 0)tournerDroiteSansArret();
  else tournerGauche();
  delay(TEMPS_90_DEGRES);
}