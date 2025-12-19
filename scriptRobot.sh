#!/bin/bash

# Repertoires programmes
ALGO_DIR="Partie_Algo"
ROBOT_DIR="Partie_Electronique"

# Path executables
EXEC_ALGO="$ALGO_DIR/bin/main"
EXEC_ROBOT="$ROBOT_DIR/bin/main_robot"

# Fichier entre labyrinthe
fichier_entree="$1"

if [ $# -lt 1 ]; then
    echo "Utilisation: $0 <fichier_ville.txt>"
    exit 1
fi
if [ ! -f "$fichier_entree" ]; then
    echo "Erreur le fichier de la ville : ${fichier_entree} n'existe pas."
    exit -1
fi

# Compilation des programmes si pas disponibles
if [ ! -f "$EXEC_ALGO" ]; then
    make clean "$ALGO_DIR"
    make all -C "$ALGO_DIR"
fi

if [ ! -f "$EXEC_ROBOT" ]; then
    make clean "$ROBOT_DIR"
    make all -C "$ROBOT_DIR"
fi

echo "Resolution du plus court chemin..."
debut=$(date +%s%3N)

./$EXEC_ALGO $fichier_entree | ./$EXEC_ROBOT

fin=$(date +%s%3N)

secondes=$(( ($fin - $debut) / 1000))
millisecondes=$(( ($fin - $debut) % 1000))

echo "Temps d'exécution: ${secondes}.$(printf "%.3d" $millisecondes) secondes"