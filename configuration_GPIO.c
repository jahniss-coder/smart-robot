#include <stdio.h>
#include <wiringPi.h>
#include "configuration_GPIO.h"

void GPIO_configurerModeGpio()
{
    // Moteur
    pinMode(MOTEUR_G_PWM, PWM_OUTPUT);
    pinMode(MOTEUR_D_PWM, PWM_OUTPUT);
    pinMode(MOTEUR_G_IN1, OUTPUT);
    pinMode(MOTEUR_G_IN2, OUTPUT);
    pinMode(MOTEUR_D_IN4, OUTPUT);
    pinMode(MOTEUR_D_IN3, OUTPUT);
    pwmSetClock(96);

    // Capteurs suiveurs lignes
	pinMode(SUIVEUR, INPUT);
	pinMode(SUIVEUR, INPUT);
	pinMode(SUIVEUR, INPUT);
	pinMode(SUIVEUR, INPUT);

    // Capteur couleur
    pinMode(COULEUR, OUTPUT);

    // Buzzeur
    pinMode(BUZZER, OUTPUT);

    // LCD
    pinMode(LCD OUTPUT);
}

int GPIO_initialiserGpio()
{
    return wiringPiSetupGpio();
}