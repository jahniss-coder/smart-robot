
#include "affichage.h"

void initLcd() {
    int i;
    int count;

	wiringPiSetup();

    pcf8574Setup(AF_BASE,0x27); //pcf8574 I2C address

    lcdHandle = lcdInit (2, 16, 4, AF_RS, AF_E, AF_DB4,AF_DB5,AF_DB6,AF_DB7, 0,0,0,0) ;

    if (lcdHandle < 0)
    {
        fprintf (stderr, "lcdInit failed\n") ;
        exit (EXIT_FAILURE) ;
    }

    for(i=0;i<8;i++)
          pinMode(AF_BASE+i,OUTPUT);
    digitalWrite(AF_LED,1);
    digitalWrite(AF_RW,0);
}

void afficherIntersection(int type)
{
    // init();
    lcdPosition(lcdHandle, 0, 1);
    switch (type)
    {
    case 1:
        
        lcdPrintf(lcdHandle,"Intersection");
        //virage à gauche 
        break;
    case 2:
        lcdPrintf(lcdHandle,"Intersection");
        // virage à droite
        break;
    case 3:
        lcdPrintf(lcdHandle,"Intersection");
        break;
    case 4:
        lcdPrintf(lcdHandle,"Intersection");
        break;
    default:
        break;
    }
}

void afficherManoeuvre(char* manoeuvre){
    // init();
    lcdPosition(lcdHandle, 0, 0);
    lcdPrintf(lcdHandle, manoeuvre);
}

void afficherVirage(int type)
{
    // init();
    lcdPosition(lcdHandle, 0, 1);
    switch (type)
    {
    case 1:
        lcdPrintf(lcdHandle," virage gauche  ");
        //virage à gauche 
        break;
    case 2:
        lcdPrintf(lcdHandle," virage droite ");
        // virage à droite
        break;
    default:
        break;
    }
}

void afficherCouleur(int couleur){
    lcdPosition(lcdHandle, 0, 1);
    switch (couleur)
    {
    case 1:
        
        lcdPrintf(lcdHandle,"PASTILLE VERT ");
        break;
    case 2:
        lcdPrintf(lcdHandle,"PASTILLE ROUGE");
        break;
    case 3:
        lcdPrintf(lcdHandle,"PASTILLE BLEU");
        break;
    default:
        break;
    }
}

int main(){
    init();
    while (1)
    {
        // afficherIntersection(2);
        // afficherManoeuvre("TG"); // TG
        // afficherVirage(2); // virage droite
        afficherCouleur(1);
        
        delay(500);
    }
    
}