#include "capteurs.h"
#include "configuration_GPIO.h"
#include "detections.h"
#include "moteur.h"

#define AVANCER "avancer"
#define TOURNER_GAUCHE "virage g"
#define TOURNER_DROITE "virage d"


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

void faireUnVirageAGauche(){
  tournerGaucheSansArret();
  delay(1000);
  while (!aRetrouveLigne(SUIVEUR_Centre_G, SUIVEUR_Centre_D)){
    afficherManoeuvre(TOURNER_GAUCHE);
  }
  tournerDroiteSansArret();
  delay(50);
  moteurs_avancer();
}

void faireUnVirageADroite(){
  tournerDroiteSansArret();
  delay(1000);
  while (!aRetrouveLigne(SUIVEUR_Centre_G, SUIVEUR_Centre_D)){
    afficherManoeuvre(TOURNER_DROITE);
  }
  tournerGaucheSansArret();
  delay(50);
  moteurs_avancer();
}