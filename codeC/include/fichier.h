#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "avl.h"

// Fonction pour lire le fichier et construire l'AVL
Arbre* lireFichierEtConstruireAVL(const char* cheminFichier);
// Fonction pour afficher l'AVL dans un fichier
void ecrireAVLDansFichier(Arbre* a, const char* cheminFichier);