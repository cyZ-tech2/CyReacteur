//bibliothèques
#include <stdio.h>
#include <stdlib.h>

//Structures

typedef struct arbre{
	int id;
	struct arbre* fg;
	struct arbre* fd;
	int eq;
	int capacite;
	int conso;
	
}Arbre;

//Fonctions

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
