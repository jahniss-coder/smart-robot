#include "../include/detections.h"
#include "../include/capteurs.h"
#include "../include/moteur.h"
#include <stdbool.h>

bool detecterLigne(int gpio) { return getSensor(gpio) == 1; }

bool detecterVirage(int gpioG, int gpioD, int gpioAG, int gpioAD) {
  // return (getSensor(gpioG) == 1 ^ getSensor(gpioD) == 1) &&
  //        !(getSensor(gpioAG) == 1 || getSensor(gpioAD) == 1);
  return ((getSensor(gpioG) == 1) ^ (getSensor(gpioD) == 1));
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

  // Lecture des capteurs
  int valAG = getSensor(gpioAG);
  int valAD = getSensor(gpioAD);

  // Mise à jour de la mémoire (ton code existant)
  if (valAD || valAG) {
    *d = valAD ? 1 : 0;
    *g = valAG ? 1 : 0;
  }

  // --- CORRECTION LOGIQUE ---

  if (!valAG && valAD) {
    tournerGaucheSansArret();
    printf("sr g\n");
    delay(10);
  }

  if (valAG && !valAD) {
    tournerDroiteSansArret();
    printf("sr d\n");
    delay(10);
  }

  moteurs_avancer();
}

bool aRetrouveLigneGauche(int gpioAG, int gpioAD) {
  return (!getSensor(gpioAG) && getSensor(gpioAD));
}

bool aRetrouveLigneDroit(int gpioAD, int gpioAG) {
  return (!getSensor(gpioAD) && getSensor(gpioAG));
}