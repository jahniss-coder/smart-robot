#include <stdio.h>
#include <wiringPi.h>
#include "moteurs.h"
#include "config_GPIO" // Pas encore crée


// ============================================
// FONCTIONS PUBLIQUES - INITIALISATION
// ============================================

int moteurs_init(void) {
    if (initialise) {
        fprintf(stderr, "Avertissement : moteurs déjà initialisés\n");
        return 0;
    }
    
    // Initialiser wiringPi en mode BCM
    if (wiringPiSetupGpio() == -1) {
        fprintf(stderr, "Erreur : échec initialisation wiringPi\n");
        return -1;
    }
    
    // Configurer les pins PWM
    pinMode(MOTEUR_GAUCHE_PWM, PWM_OUTPUT);
    pinMode(MOTEUR_DROIT_PWM, PWM_OUTPUT);
    pwmSetRange(PWM_RANGE);
    
    // Configurer les pins de direction en sortie
    pinMode(MOTEUR_GAUCHE_A, OUTPUT);
    pinMode(MOTEUR_GAUCHE_B, OUTPUT);
    pinMode(MOTEUR_DROIT_A, OUTPUT);
    pinMode(MOTEUR_DROIT_B, OUTPUT);
    
    // Initialiser tout à l'arrêt
    pwmWrite(MOTEUR_GAUCHE_PWM, 0);
    pwmWrite(MOTEUR_DROIT_PWM, 0);
    digitalWrite(MOTEUR_GAUCHE_A, LOW);
    digitalWrite(MOTEUR_GAUCHE_B, LOW);
    digitalWrite(MOTEUR_DROIT_A, LOW);
    digitalWrite(MOTEUR_DROIT_B, LOW);
    
    initialise = 1;
    etat_actuel = MOTEUR_ARRET;
    
    printf("[MOTEURS] Initialisation réussie\n");
    return 0;
}

void moteurs_cleanup(void) {
    if (!initialise) return;
    
    moteurs_arreter();
    initialise = 0;
    printf("[MOTEURS] Nettoyage effectué\n");
}

// ============================================
// FONCTIONS PUBLIQUES - DÉPLACEMENT
// ============================================

void moteurs_avancer(int vitesse) {
    if (!initialise) {
        fprintf(stderr, "Erreur : moteurs non initialisés\n");
        return;
    }
    
    controle_moteur(MOTEUR_GAUCHE_PWM, MOTEUR_GAUCHE_A, MOTEUR_GAUCHE_B, 
                    vitesse, correction_gauche);
    controle_moteur(MOTEUR_DROIT_PWM, MOTEUR_DROIT_A, MOTEUR_DROIT_B, 
                    vitesse, correction_droite);
    
    etat_actuel = MOTEUR_AVANCE;
}

void moteurs_reculer(int vitesse) {
    if (!initialise) {
        fprintf(stderr, "Erreur : moteurs non initialisés\n");
        return;
    }
    
    controle_moteur(MOTEUR_GAUCHE_PWM, MOTEUR_GAUCHE_A, MOTEUR_GAUCHE_B, 
                    -vitesse, correction_gauche);
    controle_moteur(MOTEUR_DROIT_PWM, MOTEUR_DROIT_A, MOTEUR_DROIT_B, 
                    -vitesse, correction_droite);
    
    etat_actuel = MOTEUR_RECULE;
}

void moteurs_arreter(void) {
    if (!initialise) return;
    
    pwmWrite(MOTEUR_GAUCHE_PWM, 0);
    pwmWrite(MOTEUR_DROIT_PWM, 0);
    digitalWrite(MOTEUR_GAUCHE_A, LOW);
    digitalWrite(MOTEUR_GAUCHE_B, LOW);
    digitalWrite(MOTEUR_DROIT_A, LOW);
    digitalWrite(MOTEUR_DROIT_B, LOW);
    
    etat_actuel = MOTEUR_ARRET;
}

// ============================================
// FONCTIONS PUBLIQUES - ROTATION
// ============================================

void moteurs_tourner_gauche(int vitesse) {
    if (!initialise) {
        fprintf(stderr, "Erreur : moteurs non initialisés\n");
        return;
    }
    
    // Moteur gauche recule, moteur droit avance
    controle_moteur(MOTEUR_GAUCHE_PWM, MOTEUR_GAUCHE_A, MOTEUR_GAUCHE_B, 
                    -vitesse, correction_gauche);
    controle_moteur(MOTEUR_DROIT_PWM, MOTEUR_DROIT_A, MOTEUR_DROIT_B, 
                    vitesse, correction_droite);
    
    etat_actuel = MOTEUR_TOURNE_GAUCHE;
}

void moteurs_tourner_droite(int vitesse) {
    if (!initialise) {
        fprintf(stderr, "Erreur : moteurs non initialisés\n");
        return;
    }
    
    // Moteur gauche avance, moteur droit recule
    controle_moteur(MOTEUR_GAUCHE_PWM, MOTEUR_GAUCHE_A, MOTEUR_GAUCHE_B, 
                    vitesse, correction_gauche);
    controle_moteur(MOTEUR_DROIT_PWM, MOTEUR_DROIT_A, MOTEUR_DROIT_B, 
                    -vitesse, correction_droite);
    
    etat_actuel = MOTEUR_TOURNE_DROITE;
}

void moteurs_rotation_90_gauche(void) {
    printf("[MOTEURS] Rotation 90° gauche...\n");
    moteurs_tourner_gauche(VITESSE_VIRAGE);
    delay(temps_rotation_90);
    moteurs_arreter();
    delay(100); // Stabilisation
}

void moteurs_rotation_90_droite(void) {
    printf("[MOTEURS] Rotation 90° droite...\n");
    moteurs_tourner_droite(VITESSE_VIRAGE);
    delay(temps_rotation_90);
    moteurs_arreter();
    delay(100); // Stabilisation
}

// ============================================
// FONCTIONS PUBLIQUES - CORRECTION
// ============================================

void moteurs_correction_gauche(int vitesse_base) {
    if (!initialise) return;
    
    // Ralentir le moteur gauche de 30%
    int vitesse_gauche = vitesse_base * 0.7;
    int vitesse_droite = vitesse_base;
    
    controle_moteur(MOTEUR_GAUCHE_PWM, MOTEUR_GAUCHE_A, MOTEUR_GAUCHE_B, 
                    vitesse_gauche, correction_gauche);
    controle_moteur(MOTEUR_DROIT_PWM, MOTEUR_DROIT_A, MOTEUR_DROIT_B, 
                    vitesse_droite, correction_droite);
}

void moteurs_correction_droite(int vitesse_base) {
    if (!initialise) return;
    
    // Ralentir le moteur droit de 30%
    int vitesse_gauche = vitesse_base;
    int vitesse_droite = vitesse_base * 0.7;
    
    controle_moteur(MOTEUR_GAUCHE_PWM, MOTEUR_GAUCHE_A, MOTEUR_GAUCHE_B, 
                    vitesse_gauche, correction_gauche);
    controle_moteur(MOTEUR_DROIT_PWM, MOTEUR_DROIT_A, MOTEUR_DROIT_B, 
                    vitesse_droite, correction_droite);
}

// ============================================
// FONCTIONS PUBLIQUES - CONTRÔLE AVANCÉ
// ============================================

void moteurs_set_vitesses(int vitesse_gauche, int vitesse_droite) {
    if (!initialise) return;
    
    controle_moteur(MOTEUR_GAUCHE_PWM, MOTEUR_GAUCHE_A, MOTEUR_GAUCHE_B, 
                    vitesse_gauche, correction_gauche);
    controle_moteur(MOTEUR_DROIT_PWM, MOTEUR_DROIT_A, MOTEUR_DROIT_B, 
                    vitesse_droite, correction_droite);
    
    // Déterminer l'état
    if (vitesse_gauche == 0 && vitesse_droite == 0) {
        etat_actuel = MOTEUR_ARRET;
    } else if (vitesse_gauche > 0 && vitesse_droite > 0) {
        etat_actuel = MOTEUR_AVANCE;
    } else if (vitesse_gauche < 0 && vitesse_droite < 0) {
        etat_actuel = MOTEUR_RECULE;
    } else if (vitesse_gauche < 0 && vitesse_droite > 0) {
        etat_actuel = MOTEUR_TOURNE_GAUCHE;
    } else if (vitesse_gauche > 0 && vitesse_droite < 0) {
        etat_actuel = MOTEUR_TOURNE_DROITE;
    }
}

EtatMoteur moteurs_get_etat(void) {
    return etat_actuel;
}

// ============================================
// FONCTIONS PUBLIQUES - ÉTALONNAGE
// ============================================

void moteurs_set_temps_rotation_90(int temps_ms) {
    temps_rotation_90 = temps_ms;
    printf("[MOTEURS] Temps rotation 90° : %d ms\n", temps_ms);
}

void moteurs_set_correction_gauche(float facteur) {
    correction_gauche = facteur;
    printf("[MOTEURS] Facteur correction gauche : %.2f\n", facteur);
}

void moteurs_set_correction_droite(float facteur) {
    correction_droite = facteur;
    printf("[MOTEURS] Facteur correction droite : %.2f\n", facteur);
}