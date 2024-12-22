//bibliothèques
#include <stdio.h>
#include <stdlib.h>

//Structures
typedef struct donnees {
    unsigned long id; /*id de la station pour les stations,
    et de la station à laquelle le consommateur est relié pour les consommateurs*/

    unsigned long conso;
    unsigned long produc; //Capacité
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
//supprime l'arbre
void freeAVL(Arbre* a);
//affiche l'arbre
void afficherAVL(Arbre* a, FILE* fichier);
// Fonction qui ajoute les valeurs de consommation de l'AVL des conso dans l'AVL des stations
void ajoutConso(Arbre* AVLstation, Arbre* AVLconso);