#include "action.h"
#include "capteurs.h"
#include "configuration_GPIO.h"
#include "detections.h"
#include "moteur.h"
#include <string.h>

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

void faireUnVirageAGauche() {
  tournerGaucheSansArret();
  delay(1000);
  while (!aRetrouveLigne(SUIVEUR_Centre_G, SUIVEUR_Centre_D)) {
    afficherManoeuvre(TOURNER_GAUCHE);
  }
  tournerDroiteSansArret();
  delay(50);
  moteurs_avancer();
}

void faireUnVirageADroite() {
  tournerDroiteSansArret();
  delay(1000);
  while (!aRetrouveLigne(SUIVEUR_Centre_G, SUIVEUR_Centre_D)) {
    afficherManoeuvre(TOURNER_DROITE);
  }
  tournerGaucheSansArret();
  delay(50);
  moteurs_avancer();
}

char **retourneTableauDOrdre(const char *cheminFichier, int nbLigneFichier) {
  char **tableau = malloc(nbLigneFichier * sizeof(char *));
  int indice = 0;

  FILE *f = fopen(cheminFichier, "r");
  if (!f) {
    perror("Erreur d'ouverture");
    return NULL;
  }

  char buffer[16];

  while (fgets(buffer, sizeof(buffer), f) != NULL) {
    buffer[strcspn(buffer, "\n")] = 0;

    if (strcmp(buffer, ".") == 0) {
      break;
    }

    tableau[indice] = malloc(strlen(buffer) + 1);
    strcpy(tableau[indice], buffer);
    indice++;
  }

  fclose(f);

  tableau[indice] = NULL;

  return tableau;
}

void controlerRobotDepuisOrdre(char *cheminFichier, int nbLigneFichier) {
  char **tableau = retourneTableauDOrdre(cheminFichier, nbLigneFichier);
  int fileCapteur = color_initialisation();

  int indice = 0;

  while (tableau[indice] != NULL) {
    if (strcmp(tableau[indice], "AV") == 0) {
      avancer(fileCapteur);
    } else if (strcmp(tableau[indice], "TG") == 0) {
      faireUnVirageAGauche();
    } else if (strcmp(tableau[indice], "TD") == 0) {
      faireUnVirageADroite();
    }
    indice++;
  }

  moteurs_arreter();

  // pour libérer le tableau ensuite
  indice = 0;
  while (tableau[indice]) {
    free(tableau[indice]);
    indice++;
  }
  free(tableau);
}