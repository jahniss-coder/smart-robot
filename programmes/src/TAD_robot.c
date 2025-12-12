typedef enum { NORD, SUD, EST, OUEST } tDirection;

typedef struct {
  unsigned int caseRobot;
  tDirection direction;
} Robot;

tDirection getDirection(Robot r) { return r.direction; }

void setDirection(Robot r, tDirection direction) { r.direction = direction; }

unsigned int getCaseRobot(Robot r) { return r.caseRobot; }

void setCaseRobot(Robot r, unsigned int nouvelleCase) {
  r.caseRobot = nouvelleCase;
}