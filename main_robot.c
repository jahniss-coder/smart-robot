#include "action.h"
#include "affichage.h"
#include "capteurs.h"
#include "configuration_GPIO.h"
#include "moteur.h"
#include <stdio.h>

int main() {
  int fileColor;

  printf("Début programme\n");

  if (GPIO_initialiserGpio() == -1) {
    printf("Erreur Initialisation GPIO\n");
  }

  GPIO_configurerModeGpio();
  printf("Arrêt du moteur\n");
  moteurs_arreter();

  printf("Intialisation affichage LCD\n");
  initLcd();

  fileColor = color_initialisation();

  printf("Récupération fichier texte: test.txt\n");

  printf("Délai 5 secondes\n");
  delay(5000);

  printf("Début mouvement\n");

  // controlerRobotDepuisOrdre("test.txt", 10);
  moteurs_avancer();
  printf("Fin mouvement\n");

  color_fermer(fileColor);

  printf("FIN programme\n");
  return EXIT_SUCCESS;
}