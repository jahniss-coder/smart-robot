#include "detections.h"
#include "capteurs.h"
#include "moteur.h"
#include <stdbool.h>

bool detecterLigne(int gpio) { return getSensor(gpio) == 1; }

int detecterVirage(int gpioG, int gpioD, int gpioAG, int gpioAD) {
  return (getSensor(gpioG) == 1 ^ getSensor(gpioD) == 1) &&
         !(getSensor(gpioAG) == 1 || getSensor(gpioAD) == 1);
}

int detecterIntersection(int gpioG, int gpioD, int gpioAG, int gpioAD) {
  // << Permet d'avoir un décalage de bit vers la gauche
  int valeur = (getSensor(gpioG) << 3) | (getSensor(gpioD) << 2) |
               (getSensor(gpioAG) << 1) | getSensor(gpioAD);

  // Voir les types d'intersection sur Photo
  switch (valeur) {
  case 0xF: // 1111 -> Intersection type 1
    return 1;
    break;

  case 0xC: // 1100 -> Intersection type 2
    return 2;
    break;

  case 0x7: // 0111 -> Intersection type 3
    return 3;
    break;

  case 0xB: // 1011 -> Intersection type 4
    return 4;
    break;

  default: // pas de virage
    return 0;
  }
}

void suivreLigne(int gpioAG, int gpioAD, int *g, int *d) {
  if (getSensor(gpioAD) ||
      getSensor(gpioAG)) { // pour sauvegarder l'état précédent des capteurs
    if (getSensor(gpioAD)) {
      *d = 1;
    } else {
      *d = 0;
    }
    if (getSensor(gpioAG)) {
      *g = 1;
    } else {
      *g = 0;
    }
  }

  if (getSensor(gpioAG) && !getSensor(gpioAD)) { // perdu à droite
    tournerGaucheSansArret();
    delay(25);
  }

  if (!getSensor(gpioAG) && getSensor(gpioAD)) { // perdu à gauche
    tournerDroiteSansArret();
    delay(25);
  }

  if (!getSensor(gpioAD) && !getSensor(gpioAG)) {
    if (*d == 0 && *g == 1) {
      tournerGaucheSansArret();
      delay(25);
    }
    if (*d == 1 && *g == 0) {
      tournerDroiteSansArret();
      delay(25);
    }

    // pas de cas de les deux à 0
  }

  moteurs_avancer();
}

bool aRetrouveLigne(int gpioAG, int gpioAD) {
  return getSensor(gpioAG) && getSensor(gpioAD);
}