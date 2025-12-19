#ifndef __AFFICHAGE__
#define __AFFICHAGE__

#include "actions.h"
#include <lcd.h>
#include <pcf8574.h>
#include <wiringPi.h>

#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#define AF_BASE 64
#define AF_RS (AF_BASE + 0)
#define AF_RW (AF_BASE + 1)
#define AF_E (AF_BASE + 2)
#define AF_LED (AF_BASE + 3)

#define AF_DB4 (AF_BASE + 4)
#define AF_DB5 (AF_BASE + 5)
#define AF_DB6 (AF_BASE + 6)
#define AF_DB7 (AF_BASE + 7)

typedef enum {
  AFFICHER_COULEUR,
  AFFICHER_MANOEUVRE,
  AFFICHER_VIRAGE,
  AFFICHER_INTERSECTION,
  ARRET
} affichage_type;

typedef struct {
  affichage_type type;
  union {
    int couleur;              /* pour AFFICHER_COULEUR */
    int virage;               /* pour AFFICHER_VIRAGE */
    int intersection;         /* pour AFFICHER_INTERSECTION */
    manoeuvre_type manoeuvre; /* pour AFFICHER_MANOEUVRE */
  } data;
} message_type;

#define QUEUE_SIZE 10

extern message_type queue[QUEUE_SIZE];
extern int queue_start;
extern int queue_end;
extern int queue_count;

extern pthread_mutex_t queue_mutex;
extern pthread_cond_t queue_cond;

void initLcd();
void afficherManoeuvre(manoeuvre_type type);
void afficherVirage(int);
void afficherIntersection(int);
void afficherCouleur(int);
void push_queue_affichage(message_type msg);
void *affichage_thread(void *arg);

void afficherContenuFile(void);
#endif
