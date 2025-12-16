#!/bin/bash

# Vérifier que un fichier est fourni en entrée
if [ $# -ne 1 ]; then
    echo "Usage: $0 <fichier.txt>"
    exit 1
fi

input_file="$1"

# Vérifier que le fichier existe
if [ ! -f "$input_file" ]; then
    echo "Erreur: Le fichier '$input_file' n'existe pas"
    exit 1
fi

# Chemins vers les exécutables
algo_main="./Partie\ Algo/main"
elec_main="./Partie\ Electronique/main"

# Vérifier que les exécutables existent
if [ ! -x "$algo_main" ]; then
    echo "Erreur: $algo_main n'existe pas ou n'est pas exécutable"
    exit 1
fi

if [ ! -x "$elec_main" ]; then
    echo "Erreur: $elec_main n'existe pas ou n'est pas exécutable"
    exit 1
fi

# Exécuter Partie Algo avec le fichier en entrée, puis passer le résultat à Partie Elec
"$algo_main" < "$input_file" | "$elec_main" 