/**
Tests pour les capteurs
**/

// Pour compiler gcc -o test_capteur test_capteur.c capteurs.c -lwiringPi
// -lpthread
#include "capteurs.h"
#include "configuration_GPIO.h"
#include <stdio.h>
#include <wiringPi.h>

// Test 1 pour le LCD
int test_lcd() {
  printf("\n=== TEST 1: ECRAN LCD ===\n");
  // Test si l'initialisation s'est bien passée
  if (lcd_initialisation() == -1) {
    printf("initialisation échouée\n");
    return -1;
  }
  printf("LCD initialisé\n");

  // Test l'affichage sur le LCD
  printf("Affichage: 'Bonjour'\n");
  lcd_afficher("Bonjour");
  delay(2000);

  // Test que le LCD s'affiche bien
  printf("Effacement écran\n");
  lcd_effacer();
  delay(1000);

  // Test que les longs messages s'affichent bien
  printf("Affichage: message long\n");
  lcd_afficher("message tres tres long qui ne se fini pas");
  delay(2000);

  // Test que tous les messages s'écrivent
  printf("Test plusieurs messages\n");
  const char *messages[] = {"Test 1", "Test 2", "Test 3", "Fin tests LCD"};

  for (int i = 0; i < 4; i++) {
    lcd_afficher(messages[i]);
    delay(1000);
  }

  lcd_effacer();
  printf("fin tests LCD\n");
  return 0;
}

// Test 2 pour le capteur RGB
int test_capteur_couleur() {
  printf("\n=== TEST 2: CAPTEUR RGB ===\n");

  // Test l'initialisation du capteur RGB
  int file = color_initialisation();
  if (file < 0) {
    printf("initialisation ne fonctionne pas\n");
    return -1;
  }
  printf("capteur RGB initialisé (file descriptor: %d)\n", file);

  // Test que le capteur reconnaisse plusieurs couleurs
  printf("\n lecture de 3 couleurs differentes :\n");
  printf("Placer differentes couleurs devant le capteur\n\n");

  int compteur_rouge = 0, compteur_vert = 0, compteur_indetermine = 0;

  for (int i = 0; i < 10; i++) {
    int couleur = detecterPastille(file);

    printf("Échantillon %2d: ", i + 1);
    switch (couleur) {
    case 0:
      printf("INDÉTERMINÉ\n");
      compteur_indetermine++;
      break;
    case 1:
      printf("VERT\n");
      compteur_vert++;
      break;
    case 2:
      printf("ROUGE\n");
      compteur_rouge++;
      break;
    default:
      printf("ERREUR (code: %d)\n", couleur);
    }

    delay(1000);
  }

  // Résultat du test précedent
  printf("\n--- Statistiques ---\n");
  printf("Rouge:       %d/10 (%.0f%%)\n", compteur_rouge,
         compteur_rouge * 10.0);
  printf("Vert:        %d/10 (%.0f%%)\n", compteur_vert, compteur_vert * 10.0);
  printf("Indéterminé: %d/10 (%.0f%%)\n", compteur_indetermine,
         compteur_indetermine * 10.0);

  // Fermeture du file
  color_fermer(file);
  printf("\n fin test capteur RGB\n");
  return 0;
}

// Test 3 pour les capteurs de contraste
int test_getSensor() {
  printf("\n=== TEST 3: CAPTEUR CONTRASTE ===\n");

  // Test que le capteur de contraste soit bien configuré
  GPIO_configurerModeGpio();
  printf("Capteur contraste configuré\n");

  printf("\nDétection de ligne:\n");
  printf("Mettre le capteur au dessus d'une ligne noire\n\n");

  int compteur_ligne = 0;
  int compteur_blanc = 0;

  // Test que le capteur de contraste reconaisse le noir et le reste
  printf("\nTest pour le capteur gauche\n");
  for (int i = 0; i < 20; i++) {
    int valeur = getSensor(SUIVEUR_Gauche);

    printf("Lecture %2d: ", i + 1);
    if (valeur == 1) {
      printf("LIGNE DÉTECTÉE\n");
      compteur_ligne++;
    } else {
      printf(" Autre surfec détectée \n");
      compteur_blanc++;
    }

    delay(500);
  }

  // Resultat du test précedent
  printf("\n--- Statistiques ---\n");
  printf("Ligne détectée: %d/20 (%.0f%%)\n", compteur_ligne,
         compteur_ligne * 5.0);
  printf("Surface blanche: %d/20 (%.0f%%)\n", compteur_blanc,
         compteur_blanc * 5.0);

  printf("\nTest pour le capteur droite\n");
  for (int i = 0; i < 20; i++) {
    int valeur = getSensor(SUIVEUR_Droit);

    printf("Lecture %2d: ", i + 1);
    if (valeur == 1) {
      printf("LIGNE DÉTECTÉE\n");
      compteur_ligne++;
    } else {
      printf(" Autre surfec détectée \n");
      compteur_blanc++;
    }

    delay(500);
  }

  // Resultat du test précedent
  printf("\n--- Statistiques ---\n");
  printf("Ligne détectée: %d/20 (%.0f%%)\n", compteur_ligne,
         compteur_ligne * 5.0);
  printf("Surface blanche: %d/20 (%.0f%%)\n", compteur_blanc,
         compteur_blanc * 5.0);

  printf("\nTest pour le capteur centre gauche\n");
  for (int i = 0; i < 20; i++) {
    int valeur = getSensor(SUIVEUR_Centre_G);

    printf("Lecture %2d: ", i + 1);
    if (valeur == 1) {
      printf("LIGNE DÉTECTÉE\n");
      compteur_ligne++;
    } else {
      printf(" Autre surfec détectée \n");
      compteur_blanc++;
    }

    delay(500);
  }

  // Resultat du test précedent
  printf("\n--- Statistiques ---\n");
  printf("Ligne détectée: %d/20 (%.0f%%)\n", compteur_ligne,
         compteur_ligne * 5.0);
  printf("Surface blanche: %d/20 (%.0f%%)\n", compteur_blanc,
         compteur_blanc * 5.0);

  printf("\nTest pour le capteur centre droite\n");
  for (int i = 0; i < 20; i++) {
    int valeur = getSensor(SUIVEUR_Centre_D);

    printf("Lecture %2d: ", i + 1);
    if (valeur == 1) {
      printf("LIGNE DÉTECTÉE\n");
      compteur_ligne++;
    } else {
      printf(" Autre surfec détectée \n");
      compteur_blanc++;
    }

    delay(500);
  }

  // Resultat du test précedent
  printf("\n--- Statistiques ---\n");
  printf("Ligne détectée: %d/20 (%.0f%%)\n", compteur_ligne,
         compteur_ligne * 5.0);
  printf("Surface blanche: %d/20 (%.0f%%)\n", compteur_blanc,
         compteur_blanc * 5.0);

  printf("\nfin des tests capteurs de lignes\n");
  return 0;
}

// Test 4: Intégration LCD + Capteur couleur
int test_integration_lcd_couleur() {
  printf("\n=== TEST 4: INTÉGRATION LCD + RGB ===\n");

  // Test de l'initialisation du capteur RGB et LCD
  if (lcd_initialisation() == -1) {
    printf("Échec initialisation LCD\n");
    return -1;
  }

  int file = color_initialisation();
  if (file < 0) {
    printf("Échec initialisation capteur RGB\n");
    return -1;
  }

  printf("Systèmes initialisés\n");
  printf("Les couleurs détectées seront affichées sur le LCD\n\n");

  // Test detection de l'affichage
  for (int i = 0; i < 15; i++) {
    int couleur = detecterPastille(file);

    switch (couleur) {
    case 0:
      lcd_afficher("Couleur: ???");
      printf("LCD: Couleur: ???\n");
      break;
    case 1:
      lcd_afficher("Couleur: VERT");
      printf("LCD: Couleur: VERT\n");
      break;
    case 2:
      lcd_afficher("Couleur: ROUGE");
      printf("LCD: Couleur: ROUGE\n");
      break;
    }

    delay(1500);
  }

  lcd_afficher("Test termine!");
  delay(2000);
  lcd_effacer();

  color_fermer(file);
  printf("\nTest intégration terminé\n");
  return 0;
}

// Test 5: Scénario robot suiveur de ligne
int test_scenario_suiveur_ligne() {
  printf("\n=== TEST 5: SCÉNARIO SUIVEUR DE LIGNE ===\n");

  // Test initialisation du LCD
  if (lcd_initialisation() == -1) {
    return -1;
  }
  // Initialisation du capteur de contraste
  GPIO_configurerModeGpio();
  printf("Systèmes prêts\n");

  lcd_afficher("Suiveur ligne");
  delay(2000);

  printf("\nSimulation pendant 30 secondes.\n");
  int temps_ecoule = 0;
  int lignes_detectees = 0;

  while (temps_ecoule < 30) {
    int ligne = getSensor(SUIVEUR_Centre_D);

    if (ligne == 1) {
      lcd_afficher("LIGNE!");
      printf("[%2ds] Ligne détectée\n", temps_ecoule);
      lignes_detectees++;
    } else {
      lcd_afficher("NON LIGNE");
      printf("[%2ds] pas de ligne detectée\n", temps_ecoule);
    }

    delay(1000);
    temps_ecoule++;
  }

  // Resultat du test précedent
  char rapport[32];
  snprintf(rapport, sizeof(rapport), "Lignes: %d", lignes_detectees);
  lcd_afficher(rapport);

  printf("\n--- Rapport final ---\n");
  printf("Lignes détectées: %d en 30 secondes\n", lignes_detectees);
  printf("Taux de détection: %.1f lignes/seconde\n", lignes_detectees / 30.0);

  delay(3000);
  lcd_effacer();

  printf("\nScénario terminé\n");
  return 0;
}

// Programme principal
int main() {

  if (GPIO_initialiserGpio() == -1) {
    printf("IMPOSSIBLE D'INITIALISER WIRINGPI\n");
    return 1;
  }

  printf("WiringPi initialisé en mode GPIO\n");
  printf("-------   TEST DES CAPTEURS   --------\n");

  // Initialisation globale unique
  GPIO_configurerModeGpio();
  printf("WiringPi initialisé en mode GPIO\n");

  int choix;
  do {

    printf("1) Test LCD\n");
    printf("2) Test capteur RGB\n");
    printf("3) Test capteur contraste\n");
    printf("4) Test RGB sur LCD\n");
    printf("5) Test suiveur de ligne\n");
    printf("6) Tous les test\n");
    printf("Choix: ");
    scanf("%d", &choix);

    switch (choix) {
    case 1:
      test_lcd();
      break;
    case 2:
      test_capteur_couleur();
      break;
    case 3:
      test_getSensor();
      break;
    case 4:
      test_integration_lcd_couleur();
      break;
    case 5:
      test_scenario_suiveur_ligne();
      break;
    case 6:
      printf("\n----- EXÉCUTION DE TOUS LES TESTS ----\n");
      test_lcd();
      test_capteur_couleur();
      test_getSensor();
      test_integration_lcd_couleur();
      test_scenario_suiveur_ligne();
      printf("\nTOUS LES TESTS COMPLÉTÉS!\n");
      break;
    case 0:
      break;
    default:
      printf("\nChoix pas possible\n");
    }

    if (choix != 0) {
      printf("\nAppuyer sur Entrée pour continuer...");
      getchar();
      getchar();
    }

  } while (choix != 0);

  return 0;
}