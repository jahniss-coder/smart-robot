#include "../include/capteurs.h"
#include <lcd.h>
#include <wiringPi.h>

int lcdHandle;

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
    // int c = (buffer[1] << 8) | buffer[0];
    int r = (buffer[3] << 8) | buffer[2];
    int g = (buffer[5] << 8) | buffer[4];
    int b = (buffer[7] << 8) | buffer[6];

    // Conversion en flottants pour la précision des divisions
    // On utilise 'c' (Clear) ou la somme (r+g+b) comme diviseur
    float total = (float)(r + g + b);

    // Éviter la division par zéro si capteur dans le noir
    if (total < 50)
      return 0;

    // Calcul des pourcentages de chaque couleur
    float p_r = r / total;
    float p_g = g / total;
    float p_b = b / total;

    // LOGIQUE AMÉLIORÉE
    // ----------------

    // DÉTECTION ROUGE
    // Le rouge doit être dominant, MAIS il faut aussi que le rouge soit
    // nettement supérieur au vert (ce qui élimine le bois/jaune/orange)
    // Seuil typique : Rouge > 40% du total ET Rouge est 2x plus fort que le
    // vert
    // if (p_r > 0.4 && p_r > (p_g * 1.4)) {
    //   // if (p_r > 0.4) {
    //   return 2; // Rouge confirmé
    // }
    if (r > 1.4 * g && r > 1.4 * b) {
      return 2;
    }

    // DÉTECTION VERT
    // Le vert est souvent moins "puissant" que le rouge sur ces capteurs.
    // On cherche une dominance simple.
    else if (p_g > 0.4 && p_g > p_r && p_g > p_b) {
      return 1; // Vert confirmé
    }
    // else if (g > 1.2 * r && g > 1.2 * b) {
    //   return 1;
    // }

    return 0; // Indéterminé (ou bois)
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
  // delay(50);
  return sensorValue;
}

// Fermer le file descriptor de l'I2C
void color_fermer(int file) {
  if (file >= 0) {
    close(file);
  }
}