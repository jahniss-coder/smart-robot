#ifndef __CAPTEURS__
#define __CAPTEURS__

#include "configuration_GPIO.h"
// librairies néessaires à l'affichage sur écran lcd
#include <lcd.h>
#include <pcf8574.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

// librairies nécessaires au capteur RGB
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <unistd.h>

// Nécessaire pour l'affchage écran lcd
#define AF_BASE 64
#define AF_RS (AF_BASE + 0)
#define AF_RW (AF_BASE + 1)
#define AF_E (AF_BASE + 2)
#define AF_LED (AF_BASE + 3)
#define AF_DB4 (AF_BASE + 4)
#define AF_DB5 (AF_BASE + 5)
#define AF_DB6 (AF_BASE + 6)
#define AF_DB7 (AF_BASE + 7)

// Variable globale interne pour garder la poignée (handle) de l'écran
static int lcdHandle;

// Nécessaire pour le I2C
#define I2C_BUS "/dev/i2c-1"
#define SENSOR_ADDR 0x29 // Adresse standard du TCS34725 (capteur RGB)

// Registres du capteur
#define TCS_COMMAND_BIT 0x80
#define TCS_ENABLE 0x00
#define TCS_CDATAL 0x14 // Adresse de départ des données (Clear Data Low)

/**
   @brief initialiser l'écran lcd
   @return 0 si pas d'erreurs -1 sinon
**/
int lcd_initialisation();

/**
   @brief Efface le contenu de l'écran lcd
**/
void lcd_effacer();

/**
   @brief Affiche un message sur l'écran lcd
   @param *message le message à afficher
**/
void lcd_afficher(const char *message);

/**
   @brief initialise le capteur de couleur rgb
   @return file
**/
int color_initialisation();

/**
   @brief obtenir la couleur détéctée par le capteur
   @param file sortie de l'initialisation du capteur rgb
   @return 0 si couleur indéterminé, 1 si vert, 2 si rouge
**/
int detecterPastille(int file);

/**
   @brief Initialiser le capteur de contraste
**/
void setup_capteur_contraste();

/** (anciennement capteur_contraste() )
   @brief détecter une ligne
   @param GPIO_capteur capteur dont on veut lire la valeur
   @return 0 si aucune ligne détéctée, 1 sinon
**/
int getSensor(int gpio);

/**
   @brief Fermer le file descriptor de l'I2C
   @param file sortie de l'initialisation du capteur rgb
**/
void color_fermer(int file);

#endif __CAPTEURS__
