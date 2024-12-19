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

//Fonctions
Donnees* creationTMP();

//AVL
//Creation
Arbre* creerArbre(int e, int a, int b);
//Rotations simples
Arbre* rotationGauche(Arbre* a);
Arbre* rotationDroite(Arbre* a);
//Rotations doubles
Arbre* doubleRotationGauche(Arbre* a);
Arbre* doubleRotationDroite(Arbre* a);
//equilibrage
Arbre* equilibrerAVL(Arbre* a);
//insertion
Arbre* insertionAVL(Arbre* a, int e, int* h);
