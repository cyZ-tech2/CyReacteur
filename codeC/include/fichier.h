#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "avl.h"

// Fonction pour lire le fichier et construire l'AVL
Arbre* construireAVLStation(const char* cheminFichier);

Arbre* construireAVLConso(const char* cheminFichier);
// Fonction pour afficher l'AVL dans un fichier
void AVLDansFichier(Arbre* a, const char* cheminFichier, const char* typeStation, const char* typeConso);

void diffCapConso(const char* cheminFichier);