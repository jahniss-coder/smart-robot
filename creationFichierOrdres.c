#include "TAD_robot.h"
#include <stdio.h>

#define MAX_ORDRES                                                             \
  4 // Il ne peut pas y avoir plus de 4 ordres sachant que les demi tour ne sont
    // pas pris en compte car ils feraient perdre trop de temps au
    // directionRobot
#define MAX_CASES 50 // constante pour le plus court chemin.

typedef enum {
  AV,
  TG,
  TD,
  NUL
} Ordre // 0 correspond à aucun ordre

    tDirection directionOuest(tDirection direction) {
  switch (direction)
  case OUEST:
    return SUD;
case SUD:
  return EST;
case EST:
  return NORD;
case NORD:
  return OUEST;
}

tDirection directionEst(tDirection direction) {
  switch (direction)
  case OUEST:
    return NORD;
case SUD:
  return OUEST;
case EST:
  return SUD;
case NORD:
  return EST;
}

Ordre ordreDuChangementDeDirection(tDirection direction,
                                   tDirection nlleDirection) {
  if (direction == nlleDirection)
    return 0;
  else {
    if (direction == directionGauche(nlleDirection))
      return TG;
    else {
      if (direction == directionDroite(nlleDirection))
        return TD;
    }
  }
}

void determinerOrdres(char tabOrdres[MAX_ORDRES],
                      unsigned int plusCourtChemin[MAX_CASES],
                      unsigned int nbCaseChemin, unsigned int debut,
                      unsigned int fin, Robot robot,
                      unsigned int largeurCircuit) {

  Ordre ordre1, ordre2;
  unsigned int i;
  unsigned int j = 0;
  for (i = 0, i < nbCaseChemin - 1, i++) {
    determinerOrdre(plusCourtChemin[i], plusCourtChemin[i + 1],
                    getDirection(robot), largeurCircuit, ordre1,
                    ordre2) if (ordre1 == NUL) tabOrdres[j] = ordre2;
    else {
      tabOrdres[j] = ordre1;
      tabOrdres[j + 1] = ordre2;
      j++;
    }
    j++;
  }
}

void determinerOrdre(unsigned int debut, unsigned int fin tDirection dirRobot,
                     unsigned int largeurCircuit, Ordre ordre1, Ordre ordre2) {

  unsigned int diff = fin - debut;
  tDirection nlleDirection;

  switch (diff) {
  case 1: {
    nlleDirection = EST;
    break;
  }
  case -1: {
    nlleDirection = OUEST;
    break;
  }
  case largeurCircuit: {
    nlleDirection = NORD;
    break;
  }
  case -largeurCircuit: {
    nlleDirection = SUD;
    break;
  }
  default:
    break;
  }

  ordre1 = ordreDuChangementDeDirection(dirRobot, nlleDirection);
  ordre2 = AV;
}
