//bibliothèques
#include <stdio.h>
#include <stdlib.h>

//Structures
typedef struct donnees {
    int id;
    unsigned long conso;
    unsigned long produc;
} Donnees;

// Structure pour l'arbre AVL
typedef struct arbre {
    Donnees donnees;
    struct arbre* fg;
    struct arbre* fd;
    int eq; // équilibre de l'arbre
} Arbre;

//AVL
//Creation
Arbre* creerArbre(Donnees d);
//Rotations simples
Arbre* rotationGauche(Arbre* a);
Arbre* rotationDroite(Arbre* a);
//Rotations doubles
Arbre* doubleRotationGauche(Arbre* a);
Arbre* doubleRotationDroite(Arbre* a);
//equilibrage
Arbre* equilibrerAVL(Arbre* a);
//insertion
Arbre* insertionAVL(Arbre* a, Donnees d, int* h);
//recherche une station dans l'arbre
void rechercheStation(Arbre** station, Donnees d);
//supprime l'arbre
void freeAVL(Arbre* a);
//affiche l'arbre
void afficherAVL(Arbre* a, FILE* fichier);
// Fonction qui parcourt le fichier filtreConso et fait la somme des consommateurs pour chaque station
void sommeConso(Arbre* AVLstation, Arbre* AVLconso);