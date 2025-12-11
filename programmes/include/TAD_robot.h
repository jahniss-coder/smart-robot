#ifndef __TAD_ROBOT__
#define __TAD_ROBOT__

typedef enum { NORD, SUD, EST, OUEST } tDirection;

typedef struct {
  unsigned int caseRobot;
  tDirection direction;
} Robot;

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
void setDirection(Robot r, tDirection direction);

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
void setCaseRobot(Robot r, unsigned int nouvelleCase);

#endif