/** 
Tests pour le moteur
**/

#include <stdio.h>
#include <wiringPi.h> 
#include "moteur.h"
#include "configuration_GPIO.h"

int main(){
    printf("--- DEBUT DES TESTS MOTEURS ---\n");

    if (GPIO_initialiserGpio() == -1) {
    fprintf(stderr, "Erreur : Impossible d'initialiser wiringPi\n");
    return 1;
    }
    GPIO_configurerModeGpio();
    printf("Initialisation GPIO : OK\n");

    printf("--- TEST1/2 ---\n");

    // S'assurer que tout est à l'arrêt au début
    moteurs_arreter();
    delay(1000);

    // 1. TEST AVANCER
    printf("1. Avancer (Vitesse Moyenne) pendant 3s\n");
    moteurs_avancer();
    delay(1500);
    moteurs_arreter();
    delay(1000);

    // 2. TEST RECULER
    printf("2. Reculer (Vitesse moyenne) pendant 3s\n");
    moteurs_reculer();
    delay(1500);
    moteurs_arreter();
    delay(1000);

    // 3. TEST ROTATION DROITE
    printf("3. Tourner Droite pendant 1.5s\n");
    tournerDroite();
    delay(1500); // Temps nécessaire pour faire 90 degrés (à calibrer IRL)
    moteurs_arreter();
    delay(1000);

    // 4. TEST ROTATION GAUCHE
    printf("4. Tourner Gauche pendant 1.5s\n");
    tournerGauche();
    delay(1500);
    moteurs_arreter();
    delay(1000);

    // 5. TEST DEMI-TOUR
    printf("5. Demi-tour\n");
    moteurs_demi_tour();
    delay(1000);

    printf("--- TEST2/2 ---\n");
    moteurs_arreter();
    delay(1000);

    // 1. TEST AVANCER
    printf("1. Avancer (Vitesse Moyenne) pendant 3s\n");
    moteurs_avancer();
    delay(1500);

    // 2. TEST ROTATION GAUCHE
    printf("3. Tourner Gauche pendant 1.5s\n");
    tournerGaucheSansArret();
    delay(1500); // Temps nécessaire pour faire 90 degrés (à calibrer IRL)
    moteurs_avancer();
    delay(1500);

    // 3. TEST ROTATION DROITE
    printf("4. Tourner Droite pendant 1.5s\n");
    tournerDroiteSansArret();
    delay(1500);
    moteurs_avancer();
    delay(1500);

    // 4. TEST DEMI-TOUR
    printf("5. Demi-tour\n");
    moteurs_arreter();
    delay(1000);
    moteurs_demi_tour();
    delay(1000);

    printf("--- FIN DES TESTS ---\n");
    moteurs_arreter();

    return 0;
}