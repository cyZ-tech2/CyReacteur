//bibliothèques
#include <stdio.h>
#include <stdlib.h>

//Structures

typedef struct donnees{
	int id;
	long unsigned centrale;
    	long unsigned hv_b;
    	long unsigned hv_a;
    	long unsigned lv;
    	long unsigned entrp;
    	long unsigned partc;
    	long unsigned conso;
    	long unsigned produc;
}Donnees;

typedef struct arbre{
	Donnees d;
	struct arbre* fg;
	struct arbre* fd;
	int eq;	
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
