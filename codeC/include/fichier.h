#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <avl.h>

FILE* modifFichier(FILE* fichier);

void ajouterValeur(FILE* fichier, Arbre* racine, char* nom_station, int* h);