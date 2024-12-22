#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "avl.h"

// Fonction pour lire le fichier et construire l'AVL
Arbre* construireAVLStation(const char* cheminFichier);
// Parcours le fichier filtreConso et ajoute les consommations de chaque consommateur à l'arbre
void sommeConso(const char* cheminFichier,Arbre* a);
// Fonction pour afficher l'AVL dans un fichier
void AVLDansFichier(Arbre* a, const char* cheminFichier, const char* typeStation, const char* typeConso);
// Fonction qui calcule la différence (production/conso)
void diffCapConso(const char* cheminFichier);
