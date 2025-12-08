#include "capteurs.h"
#include "configuration_GPIO.h"
#include "detections.h"
#include "moteur.h"

#define AVANCER "avancer"

void avancer(int file) {
  int pastille, intersection, virage;
  moteurs_avancer();
  intersection = detecterIntersection(SUIVEUR_Gauche, SUIVEUR_Droit,
                                      SUIVEUR_Centre_G, SUIVEUR_Centre_D);
  virage = detecterVirage(SUIVEUR_Gauche, SUIVEUR_Droit, SUIVEUR_Centre_G,
                          SUIVEUR_Centre_D);
  while (intersection == 0 && virage == 0) {
    suivreLigne(SUIVEUR_Centre_G, SUIVEUR_Centre_D);
    pastille = detecterPastille(file);
    if (pastille != 0) {
      afficherCouleur(pastille);
    }
    afficherManoeuvre(AVANCER);
    intersection = detecterIntersection(SUIVEUR_Gauche, SUIVEUR_Droit,
                                        SUIVEUR_Centre_G, SUIVEUR_Centre_D);
    virage = detecterVirage(SUIVEUR_Gauche, SUIVEUR_Droit, SUIVEUR_Centre_G,
                            SUIVEUR_Centre_D);
  }

  if (intersection != 0) {
    afficherIntersection(intersection);
  }
  if (virage != 0) {
    afficherVirage(virage);
  }
}
