/**
 * @file TAD_robot.c
 * @brief Fichier de création du TAD_robot documenté avec doxygen
 * @author Delacroix-Henrion Mathieu, Diallo Alioune, Malherbe Ylann, Mathieu Ilan, Olivier Neil, Schetrit Jahnis
 * @date 2025-12
 */

#ifndef __TAD_ROBOT__
#define __TAD_ROBOT__

/** @brief Enumération des directions du robot */
typedef enum { NORD, SUD, EST, OUEST } tDirection;

/** @brief Structure du robot */
typedef struct {
  unsigned int caseRobot;
  tDirection direction;
} Robot;

/**
   @brief obtenir la direction à gauche (ouest)
   @param direction la direction actuelle
   @return la direction à gauche
**/
tDirection directionOuest(tDirection direction);

/**
 * @brief obtenir la direction à droite (est)
 * @param direction la direction actuelle
 * @return la direction à droite
*/
tDirection directionEst(tDirection direction);

/**
   @brief obtenir la direction du robot
   @param r le robot
   @return la direction du robot
**/
tDirection getDirection(Robot r);

/**
   @brief changer la direction du robot
   @param r le robot
   @param direction la nouvelle direction
   @note modifie la direction du robot avec la direction passée en paramètre
**/
void setDirection(Robot* r, tDirection direction);

/**
   @brief obtenir la case du robot
   @param r le robot
   @return la case du robot
**/
unsigned int getCaseRobot(Robot r);

/**
   @brief changer la case du robot
   @param r le robot
   @param nouvelleCase la nouvelle case
   @note modifie la case du robot avec la case passée en paramètre
**/
void setCaseRobot(Robot* r, unsigned int nouvelleCase);

#endif