#include "../include/affichage.h"
#include "../include/actions.h"
#include "../include/buzzer.h"
#include "../include/configuration_GPIO.h"

// Global lcd handle:
static int lcdHandle;

message_type queue[QUEUE_SIZE];
int queue_start = 0;
int queue_end = 0;
int queue_count = 0;

pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t queue_cond = PTHREAD_COND_INITIALIZER;

void initLcd() {
  int i;

  wiringPiSetup();

  pcf8574Setup(AF_BASE, 0x27); // pcf8574 I2C address

  lcdHandle = lcdInit(2, 16, 4, AF_RS, AF_E, AF_DB4, AF_DB5, AF_DB6, AF_DB7, 0,
                      0, 0, 0);

  if (lcdHandle < 0) {
    fprintf(stderr, "lcdInit failed\n");
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < 8; i++)
    pinMode(AF_BASE + i, OUTPUT);
  digitalWrite(AF_LED, 1);
  digitalWrite(AF_RW, 0);
}

void afficherIntersection(int type) {
  // init();
  lcdPosition(lcdHandle, 0, 1);
  switch (type) {
  case 1:

    lcdPrintf(lcdHandle, "Intersection");
    // virage à gauche
    break;
  case 2:
    lcdPrintf(lcdHandle, "Intersection");
    // virage à droite
    break;
  case 3:
    lcdPrintf(lcdHandle, "Intersection");
    break;
  case 4:
    lcdPrintf(lcdHandle, "Intersection");
    break;
  default:
    break;
  }
}

void afficherManoeuvre(manoeuvre_type type) {
  // init();
  lcdPosition(lcdHandle, 0, 0);
  switch (type) {
  case AVANCER:
    lcdPrintf(lcdHandle, "Avancer");
    break;

  case TOURNER_GAUCHE:
    lcdPrintf(lcdHandle, "Tourner Gauche");
    break;

  case TOURNER_DROITE:
    lcdPrintf(lcdHandle, "Tourner Droite");
    break;

  default:
    break;
  }
}

void afficherVirage(int type) {
  // init();
  lcdPosition(lcdHandle, 0, 1);
  switch (type) {
  case 1:
    lcdPrintf(lcdHandle, " virage gauche  ");
    // virage à gauche
    break;
  case 2:
    lcdPrintf(lcdHandle, " virage droite ");
    // virage à droite
    break;
  default:
    break;
  }
}

void afficherCouleur(int couleur) {
  lcdPosition(lcdHandle, 0, 1);
  printf("couleur: %d\n", couleur);
  switch (couleur) {
  case 1:
    lcdPrintf(lcdHandle, "PASTILLE VERT ");
    buzzerPastille(BUZZER);
    break;
  case 2:
    lcdPrintf(lcdHandle, "PASTILLE ROUGE");
    break;
  default:
    break;
  }
}

void push_queue_affichage(message_type msg) {
  pthread_mutex_lock(&queue_mutex); // on empêche de lire/ecriture plus

  if (queue_count < QUEUE_SIZE) {

    if (queue[queue_end].type != msg.type ||
        (queue[queue_end].type == msg.type &&
         queue[queue_end].data.manoeuvre != msg.data.manoeuvre)) {

      if (msg.type == AFFICHER_COULEUR) {
        queue[queue_start] = msg;
      } else {
        queue[queue_end] = msg; // on ajoute le message à la fin de la file
      }

      queue_end = (queue_end + 1) %
                  QUEUE_SIZE; // quand on arrive à la fin on revient au début
      queue_count++;

      pthread_cond_signal(&queue_cond); // on dit au thread d'affichage que y a
                                        // un truc à afficher
    }
  }

  pthread_mutex_unlock(&queue_mutex); // on redonne accès à la lecture/ecriture

  // afficherContenuFile();
}

void *affichage_thread(void *arg) {

  message_type msg;

  while (1) {

    pthread_mutex_lock(
        &queue_mutex); // pour dire qu'on veut plus d'autre lecture/ecriture

    while (queue_count == 0)
      pthread_cond_wait(&queue_cond,
                        &queue_mutex); // si rien dans la file on fait rien

    msg = queue[queue_start]; // on récupère la valeure de la file
    queue_start = (queue_start + 1) %
                  QUEUE_SIZE; // on fait une file circulaire très simple (quand
                              // y a 10 éléments, bah ça reviens à 0)
    queue_count--;            // on a enlevé un message de la queue

    pthread_mutex_unlock(&queue_mutex); // on redonne la dispo de lire/ecriture

    if (msg.type == ARRET) {
      break; // pour sortir de la boucle
    }

    switch (msg.type) {
    case AFFICHER_COULEUR:
      afficherCouleur(msg.data.couleur);
      break;

    case AFFICHER_MANOEUVRE:
      afficherManoeuvre(msg.data.manoeuvre);
      break;

    case AFFICHER_VIRAGE:
      afficherVirage(msg.data.virage);
      break;

    case AFFICHER_INTERSECTION:
      afficherIntersection(msg.data.intersection);
      break;

    default:
      break;
    }
  }

  return NULL;
}

void afficherContenuFile(void) {
  // 1. On verrouille pour avoir une "photo" stable de la file
  pthread_mutex_lock(&queue_mutex);

  printf("\n=== DEBUG FILE (Taille: %d/%d) ===\n", queue_count, QUEUE_SIZE);

  if (queue_count == 0) {
    printf(">> La file est vide.\n");
  } else {
    // 2. On parcourt les éléments logiques de 0 à count
    for (int i = 0; i < queue_count; i++) {
      // Calcul de l'index réel dans le tableau circulaire
      int real_index = (queue_start + i) % QUEUE_SIZE;
      message_type msg = queue[real_index];

      printf("[%d] ", i); // Position dans la file d'attente

      switch (msg.type) {
      case AFFICHER_COULEUR:
        printf("COULEUR      : %d ", msg.data.couleur);
        if (msg.data.couleur == 1)
          printf("(Vert)");
        else if (msg.data.couleur == 2)
          printf("(Rouge)");
        break;

      case AFFICHER_MANOEUVRE:
        printf("MANOEUVRE    : ");
        switch (msg.data.manoeuvre) {
        case AVANCER:
          printf("Avancer");
          break;
        case TOURNER_GAUCHE:
          printf("Gauche");
          break;
        case TOURNER_DROITE:
          printf("Droite");
          break;
        default:
          printf("%d (Autre)", msg.data.manoeuvre);
          break;
        }
        break;

      case AFFICHER_VIRAGE:
        printf("VIRAGE       : %d ", msg.data.virage);
        if (msg.data.virage == 1)
          printf("(Gauche)");
        else if (msg.data.virage == 2)
          printf("(Droite)");
        break;

      case AFFICHER_INTERSECTION:
        printf("INTERSECTION : %d", msg.data.intersection);
        break;

      case ARRET:
        printf("SIGNAL ARRET");
        break;

      default:
        printf("TYPE INCONNU (%d)", msg.type);
        break;
      }
      printf("\n");
    }
  }
  printf("==================================\n");

  // 3. On déverrouille pour laisser les autres threads travailler
  pthread_mutex_unlock(&queue_mutex);
}