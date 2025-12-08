#ifndef __AFFICHAGE__
#define __AFFICHAGE__

#include <wiringPi.h>
#include <pcf8574.h>
#include <lcd.h>

#include <stdio.h>
#include <stdlib.h>

#define        AF_BASE    64
#define        AF_RS                (AF_BASE + 0)
#define        AF_RW                (AF_BASE + 1)
#define        AF_E                 (AF_BASE + 2)
#define        AF_LED               (AF_BASE + 3)

#define        AF_DB4               (AF_BASE + 4)
#define        AF_DB5               (AF_BASE + 5)
#define        AF_DB6               (AF_BASE + 6)
#define        AF_DB7               (AF_BASE + 7)
// Global lcd handle:
static int lcdHandle;

void init();
void afficherManoeuvre(char* manoeuvre);
void afficherVirage(int);
void afficherIntersection(int);
void afficherCoule(int);


#endif
