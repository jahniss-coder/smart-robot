/**
 * @file TAD_robot.c
 * @brief Implémentation des fonctions pour la gestion du robot
 * @author Delacroix-Henrion Mathieu, Diallo Alioune, Malherbe Ylann, Mathieu Ilan, Olivier Neil, Schetrit Jahnis
 * @date 2025-12
 */

#include "TAD_robot.h"


/**
 * @brief Retourne la direction à l'ouest par rapport à la direction actuelle
 * @param direction La direction actuelle
 * @return La direction à l'ouest
 */
tDirection directionOuest(tDirection direction) {
    switch (direction)
    {
    case OUEST : {
        return SUD;
    }
    case SUD :{
        return EST;
    }
    case EST : {
        return NORD;
    }
    case NORD : {
        return OUEST;
    }
    default :
        return NORD;
    }
}

/**
 * @brief Retourne la direction à l'est par rapport à la direction actuelle
 * @param direction La direction actuelle
 * @return La direction à l'est
 */
tDirection directionEst(tDirection direction){
    switch (direction)
    {
    case OUEST : {
        return NORD;
    }
    case SUD : {
        return OUEST;
    }
    case EST : {
        return SUD;
    }
    case NORD : {
        return EST;
    }
    default :
        return NORD;
    }
}

/**
 * @brief Retourne la direction actuelle du robot
 * @param r Le robot
 * @return La direction actuelle du robot
 */
tDirection getDirection(Robot r) { return r.direction; }

/**
 * @brief Définit la direction du robot
 * @param r Pointeur vers le robot
 * @param direction La nouvelle direction du robot
 */
void setDirection(Robot* r, tDirection direction) { r->direction = direction; }

/**
 * @brief Retourne la case actuelle du robot
 * @param r Le robot
 * @return La case actuelle du robot
 */
unsigned int getCaseRobot(Robot r) { return r.caseRobot; }

/**
 * @brief Définit la case actuelle du robot
 * @param r Pointeur vers le robot
 * @param nouvelleCase La nouvelle case du robot
 */
void setCaseRobot(Robot* r, unsigned int nouvelleCase) {
  r->caseRobot = nouvelleCase;
}
