#include "action.h"
#include "affichage.h"
#include "capteurs.h"
#include "configuration_GPIO.h"
#include "detections.h"
#include "moteur.h"
#include <string.h>

void avancer(int file) {
  int g, d, type_intersection, type_virage, type_couleur;
  message_type msgCouleur;
  message_type msgManoeuvre;
  message_type msgVirage;
  message_type msgIntersection;
  if (getSensor(SUIVEUR_Centre_D)) {
    d = 1;
  } else {
    d = 0;
  }

  if (getSensor(SUIVEUR_Centre_G)) {
    g = 1;
  } else {
    g = 0;
  }

  moteurs_avancer();
  type_intersection = detecterIntersection(SUIVEUR_Gauche, SUIVEUR_Droit,
                                           SUIVEUR_Centre_G, SUIVEUR_Centre_D);
  type_virage = detecterVirage(SUIVEUR_Gauche, SUIVEUR_Droit, SUIVEUR_Centre_G,
                               SUIVEUR_Centre_D);
  while (type_intersection == 0 && !type_virage) {
    suivreLigne(SUIVEUR_Centre_G, SUIVEUR_Centre_D, &g, &d);
    type_couleur = detecterPastille(file);
    if (type_couleur != 0) {
      msgCouleur.type = AFFICHER_COULEUR;
      msgCouleur.data.couleur = type_couleur;
      push_queue_affichage(msgCouleur);
    }

    msgManoeuvre.data.manoeuvre = AVANCER;
    msgManoeuvre.type = AFFICHER_MANOEUVRE;
    push_queue_affichage(msgManoeuvre);
    type_intersection = detecterIntersection(
        SUIVEUR_Gauche, SUIVEUR_Droit, SUIVEUR_Centre_G, SUIVEUR_Centre_D);
    type_virage = detecterVirage(SUIVEUR_Gauche, SUIVEUR_Droit,
                                 SUIVEUR_Centre_G, SUIVEUR_Centre_D);
  }

  if (type_intersection != 0) {
    printf("INTERSECTION - Type: %d\n", type_intersection);
    msgIntersection.type = AFFICHER_INTERSECTION;
    msgIntersection.data.intersection = type_intersection;
    push_queue_affichage(msgIntersection);
  } else if (type_virage != 0) {
    printf("VIRAGE\n");
    msgVirage.type = AFFICHER_VIRAGE;
    msgVirage.data.virage = type_virage;
    push_queue_affichage(msgVirage);
  }
}

void faireUnVirageAGauche() {
  message_type msgManoeuvre;

  tournerGauche();
  delay(100);
  while (!aRetrouveLigneDroit(SUIVEUR_Centre_D)) {

    msgManoeuvre.data.manoeuvre = TOURNER_GAUCHE;
    msgManoeuvre.type = AFFICHER_MANOEUVRE;
    push_queue_affichage(msgManoeuvre);
  }
  moteurs_avancer();
}

void faireUnVirageADroite() {
  message_type msgManoeuvre;

  tournerDroite();
  delay(100);
  while (!aRetrouveLigneGauche(SUIVEUR_Centre_G)) {

    msgManoeuvre.data.manoeuvre = TOURNER_DROITE;
    msgManoeuvre.type = AFFICHER_MANOEUVRE;
    push_queue_affichage(msgManoeuvre);
  }
  moteurs_avancer();
}

char **retourneTableauDOrdre(char *cheminFichier, int nbLigneFichier) {
  // char **tableau = malloc((nbLigneFichier + 1) * sizeof(char *));
  char **tableau = malloc(NB_POINTS_MAX * sizeof(char *));
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
    delay(80);
    if (strcmp(tableau[indice], "AV") == 0) {
      printf("avancer\n");
      avancer(fileCapteur);
    } else if (strcmp(tableau[indice], "TG") == 0) {
      printf("virage gauche\n");
      faireUnVirageAGauche();
    } else if (strcmp(tableau[indice], "TD") == 0) {
      printf("virage droit\n");
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

  color_fermer(fileCapteur);
}