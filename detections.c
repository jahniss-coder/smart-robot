#include "detections.h"
#include "capteurs.h"
#include "moteur.h"
#include <stdbool.h>

bool detecterLigne(int gpio) { return getSensor(gpio) == 1; }

bool detecterVirage(int gpioG, int gpioD, int gpioAG, int gpioAD) {
  // return (getSensor(gpioG) == 1 ^ getSensor(gpioD) == 1) &&
  //        !(getSensor(gpioAG) == 1 || getSensor(gpioAD) == 1);
  return getSensor(gpioG) == 1 || getSensor(gpioD) == 1;
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

  if (valAG && !valAD) {
    tournerGaucheSansArret();
    delay(35);
  }

  if (!valAG && valAD) {
    tournerDroiteSansArret();
    delay(35);
  }

  moteurs_avancer();
}

// void suivreLigneTroisCapteurs(int gpioAG, int gpioAD) {
//   if (getSensor(gpioAG) && !getSensor(gpioAD)) { // perdu à droite
//     tournerGaucheSansArret();
//     delay(25);
//   }

//   if (!getSensor(gpioAG) && getSensor(gpioAD)) { // perdu à gauche
//     tournerDroiteSansArret();
//     delay(25);
//   }
//     // pas de cas de les deux à 0
//   moteurs_avancer();
// }

bool aRetrouveLigneGauche(int gpioAG) { return getSensor(gpioAG); }

bool aRetrouveLigneDroit(int gpioAD) { return getSensor(gpioAD); }