#include "capteurs.h"
#include <lcd.h>
#include <wiringPi.h>

int initialisation_globale() {
  wiringPiSetupGpio();
  return 0;
}

int lcd_initialisation() {
  // Initialisation de wiringPi si ce n'est pas déjà fait ailleurs
  if (wiringPiSetup() ==
      -1) { //! Peut être changé par un wiringPiSetupGpio mais après faut voir
            //! comment le code s'adapte par rapport à ce changement.
    return -1;
  }

  // Configuration de l'extension PCF8574 à l'adresse 0x27
  pcf8574Setup(AF_BASE, 0x27);

  // Initialisation de l'écran LCD via wiringPi
  lcdHandle = lcdInit(2, 16, 4, AF_RS, AF_E, AF_DB4, AF_DB5, AF_DB6, AF_DB7, 0,
                      0, 0, 0);

  if (lcdHandle < 0) {
    fprintf(stderr, "Erreur initialisation LCD\n");
    return -1;
  }

  // Allumer le rétroéclairage (LED) et mettre en mode écriture (RW=0)
  for (int i = 0; i < 8; i++)
    pinMode(AF_BASE + i, OUTPUT);
  digitalWrite(AF_LED, 1); // Lumière ON
  digitalWrite(AF_RW, 0);  // Mode écriture

  return 0;
}

void lcd_effacer() { lcdClear(lcdHandle); }

void lcd_afficher(const char *message) {
  // On efface l'écran avant d'écrire pour éviter les restes de texte
  lcdClear(lcdHandle);
  // On se place en haut à gauche
  lcdPosition(lcdHandle, 0, 0);
  // On écrit le message
  lcdPrintf(lcdHandle, message);
}

int color_initialisation() {
  int file;
  char *bus = I2C_BUS;

  // 1. Ouvrir le bus I2C
  if ((file = open(bus, O_RDWR)) < 0) {
    printf("Erreur : Impossible d'ouvrir le bus I2C\n");
    return 1;
  }

  // 2. Se connecter au capteur
  if (ioctl(file, I2C_SLAVE, SENSOR_ADDR) < 0) {
    printf("Erreur : Impossible de trouver le capteur à l'adresse 0x%02X\n",
           SENSOR_ADDR);
    return 1;
  }

  // 3. Initialiser le capteur (Power ON + ADC Enable)
  // On écrit dans le registre 0x00 la valeur 0x03 (PON + AEN)
  uint8_t config[2];
  config[0] = TCS_COMMAND_BIT | TCS_ENABLE;
  config[1] = 0x03;
  write(file, config, 2);

  // Petite pause pour laisser le capteur démarrer
  usleep(20000);

  return file;
}

// renvoie 'vert' 1 ou 'rouge' 2 ou 'bleu' 3 ou 'indetermine' 0 en fonction de
// la couleur lue
int detecterPastille(int file) {
  // 4. Préparer la lecture
  // On demande à lire à partir du registre 0x14
  // 0x20 active l'auto-incrément pour lire les 8 octets à la suite
  uint8_t reg = TCS_COMMAND_BIT | 0x20 | TCS_CDATAL;
  write(file, &reg, 1);

  // 5. Lire 8 octets (Clear L/H, Red L/H, Green L/H, Blue L/H)
  uint8_t buffer[8];
  if (read(file, buffer, 8) != 8) {
    printf("Erreur lors de la lecture des données\n");
    return -1;
  } else {
    // Reconstitution des valeurs sur 16 bits
    int c = (buffer[1] << 8) | buffer[0];
    int r = (buffer[3] << 8) | buffer[2];
    int g = (buffer[5] << 8) | buffer[4];
    int b = (buffer[7] << 8) | buffer[6];

    if (g > 300 && g > r + b) {
      return 1; // rouge
    } else if (r > 300 && r > g + b) {
      return 2; // vert
    } else if (b > 300 && b > r + g) {
      return 3; // bleu
    } else {
      return 0; // indetermine
    }
  }
}

// Inutile car fait dans configuration
// void setup_capteur_contraste() {
//     wiringPiSetupGpio();
//     pinMode(A0, INPUT);
//     pinMode(D0, OUTPUT);
// }

int getSensor(int gpio) {
  int sensorValue = digitalRead(gpio); // lire la valeur du capteur
  delay(50);
  return sensorValue;
}

// Fermer le file descriptor de l'I2C
void color_fermer(int file) {
  if (file >= 0) {
    close(file);
  }
}