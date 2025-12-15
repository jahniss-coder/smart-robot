typedef enum { NORD, SUD, EST, OUEST } tDirection;

typedef struct {
  unsigned int caseRobot;
  tDirection direction;
} Robot;

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

tDirection getDirection(Robot r) { return r.direction; }

void setDirection(Robot* r, tDirection direction) { r->direction = direction; }

unsigned int getCaseRobot(Robot r) { return r.caseRobot; }

void setCaseRobot(Robot* r, unsigned int nouvelleCase) {
  r->caseRobot = nouvelleCase;
}