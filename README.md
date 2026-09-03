# 🤖 Smart Robot

Projet intégratif réalisé à l' **INSA Rouen Normandie** dans le cadre de la formation ITI3 - Année 2025-2026

## Présentation

Le Smart Robot est un robot autonome capable de se déplacer dans une ville modélisée sous forme de cases.

L'objectif du projet est de permettre au robot de parcourir un itinéraire en passant par plusieurs points obligatoires, tout en déterminant le plus court chemin possible et en revenant à son point de départ.

Le robot doit notamment :

suivre une ligne tracée au sol ;
détecter les intersections et effectuer les changements de direction ;
détecter les pastilles colorées présentes sur le parcours ;
identifier leur couleur ;
afficher les informations sur un écran LCD ;
émettre un signal sonore lors de la détection d'une pastille ;
revenir à son point de départ et s'arrêter sur la pastille rouge.

Le projet combine électronique, algorithmique et programmation en C.

## Partie algorithmique

La ville est représentée sous la forme d'un graphe dont les sommets correspondent aux différentes cases.

Pour déterminer le parcours optimal, nous avons choisi l'algorithme de Dijkstra, adapté à la petite taille du labyrinthe et aux distances uniformes entre les sommets.

Le programme teste les différentes permutations des trois points obligatoires afin de déterminer le parcours valide de distance minimale. Le chemin est ensuite transformé en une suite d'ordres destinés au robot : AV (avancer), TG (tourner à gauche) et TD (tourner à droite).

## Matériel

Le robot est basé sur une Raspberry Pi 4 et intègre notamment :

Raspberry Pi 4;
capteurs infrarouges de suivi de ligne;
capteur de couleur TCS34725;
moteurs et motor drivers L293D;
écran LCD1602 avec interface I2C;
buzzer;
batterie externe pour la Raspberry Pi;
alimentation séparée pour les moteurs;

Les différents composants ont d'abord été testés individuellement avant leur intégration au robot afin de faciliter leur calibration et d'identifier les éventuels composants défectueux.

## Communication

Plusieurs périphériques utilisent les GPIO de la Raspberry Pi.

L'écran LCD et le capteur RGB utilisent notamment le protocole I2C, permettant de limiter le nombre de connexions nécessaires.

## Technologies
C;
Raspberry Pi;
Git / GitHub;
I2C;
PWM;
Algorithmique des graphes;
Algorithme de Dijkstra;

## Organisation du projet
.;
├── programmes/     ;     
  ├── Partie_Algo/  ;    
    ├── src/          # Code source;
    ├── include/      # Fichiers d'en-tête;
    ├── tests/        # Tests;
    ├── bin/         # Fichier d'instruction de la soutenance;
  ├── Partie_Electronique /        # Tests;
    ├── src/          # Code source;
    ├── include/      # Fichiers d'en-tête;
    ├── tests/        # Tests;
    ├── bin/        ;
├── rapport/   ;
├── README.md;
└── .gitignore;


## Difficultés rencontrées

Le passage de la théorie à la réalisation a nécessité plusieurs ajustements, notamment concernant la récupération des informations des capteurs, la stabilité du montage électronique et la détection des couleurs.

La détection des pastilles colorées s'est notamment révélée sensible aux conditions d'éclairage et à la couleur du circuit. Lors de la soutenance, 2 pastilles sur 3 ont été détectées correctement.

## Équipe

Projet réalisé par :

- Mathieu Delacroix-Henrion
- Alioune Diallo
- Ylann Malherbe
- Ilan Mathieu
- Neil Olivier
- Jahnis Schetrit

INSA Rouen Normandie — Département Informatique
Projet Intégratif — Smart Robot
ITI3 — 2025-2026

## Documentation

Le rapport complet du projet est disponible dans rapport/ et présente notamment la conception électronique, l'analyse algorithmique, la conception détaillée et l'implémentation en C.
