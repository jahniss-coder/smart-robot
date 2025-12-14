#include "action.h"
#include "affichage.h"
#include "capteurs.h"
#include "configuration_GPIO.h"
#include "moteur.h"
#include <pthread.h>
#include <stdio.h>

int main() {
  pthread_t display_tid;
  message_type m;

  printf("Début programme\n");

  if (GPIO_initialiserGpio() == -1) {
    printf("Erreur Initialisation GPIO\n");
  }

  GPIO_configurerModeGpio();
  printf("Arrêt du moteur\n");
  moteurs_arreter();

  printf("Intialisation affichage LCD\n");
  initLcd();

  printf("Récupération fichier texte: test.txt\n");

  if (pthread_create(&display_tid, NULL, affichage_thread, NULL) != 0) {
    perror("Erreur création thread affichage");
    return EXIT_FAILURE;
  }

  printf("Délai 10 secondes\n");
  delay(10000);

  printf("Début mouvement\n");

  controlerRobotDepuisOrdre("fichierInstructions.txt", 28);

  printf("Fin mouvement\n");

  m.type = ARRET;
  push_queue_affichage(m);
  pthread_join(display_tid, NULL); // fermeture du thread à la fin

  printf("FIN programme\n");
  return EXIT_SUCCESS;
}