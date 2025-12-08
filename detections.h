#ifndef CAPTEURS_H
#define CAPTEURS_H

#include <stdbool.h>

// Lit un capteur connecté sur un GPIO et renvoie 0 ou 1
int getSensor(int gpio);

// Renvoie vrai si un capteur détecte la ligne
bool detecterLigne(int gpio);

// Détection d’un virage (gauche/droite) selon les capteurs latéraux et avant
int detecterVirage(int gpioG, int gpioD, int gpioAG, int gpioAD);

// Détection d’un type d’intersection selon une combinaison de capteurs
int detecterIntersection(int gpioG, int gpioD, int gpioAG, int gpioAD);

// Suivi de ligne basé sur les capteurs avant gauche/droite
void suivreLigne(int gpioAG, int gpioAD);

// Vérifie si les deux capteurs avant ont retrouvé la ligne
bool aRetrouveLigne(int gpioAG, int gpioAD);

#endif
